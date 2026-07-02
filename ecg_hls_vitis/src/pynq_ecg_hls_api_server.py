#!/usr/bin/env python3
import json
import time
from pathlib import Path
from http.server import BaseHTTPRequestHandler, HTTPServer

import numpy as np
from pynq import Overlay, allocate


SEGMENT_LEN = 320
NUM_CLASSES = 5

BIT_FILE = Path(__file__).with_name("ecg_accel_hls.bit")
HWH_FILE = Path(__file__).with_name("ecg_accel_hls.hwh")

IP_CANDIDATES = [
    "ecg_fpga_top_0",
    "ecg_fpga_top",
]

REG_CTRL = 0x00

REG_BEAT_PTR_L = 0x10
REG_BEAT_PTR_H = 0x14

REG_PRED_PTR_L = 0x1C
REG_PRED_PTR_H = 0x20

REG_SCORE_PTR_L = 0x28
REG_SCORE_PTR_H = 0x2C


def q12_to_float(x):
    return float(x) / 4096.0


def softmax_from_q12(score_i16):
    x = np.asarray(score_i16, dtype=np.float32) / 4096.0
    x = x - np.max(x)
    e = np.exp(x)
    s = e / np.sum(e)
    return s.astype(np.float32)


def to_q12_array(payload):
    if "beat_q12" in payload:
        arr = np.asarray(payload["beat_q12"], dtype=np.int32)
    elif "beat" in payload:
        arr = np.asarray(payload["beat"], dtype=np.float32)
        arr = np.rint(arr * 4096.0).astype(np.int32)
    else:
        raise ValueError("Payload phải có beat_q12 hoặc beat")

    if arr.size != SEGMENT_LEN:
        raise ValueError("Input beat phải có đúng 320 mẫu")

    arr = np.clip(arr, -32768, 32767).astype(np.int16)
    return arr


class EcgHlsRunner:
    def __init__(self):
        if not BIT_FILE.exists():
            raise FileNotFoundError("Không tìm thấy file bit: %s" % BIT_FILE)

        self.overlay = Overlay(str(BIT_FILE))
        self.ip_name = self._find_ip_name()
        self.ip = getattr(self.overlay, self.ip_name)

        self.beat_buf = allocate(shape=(SEGMENT_LEN,), dtype=np.int16)
        self.pred_buf = allocate(shape=(1,), dtype=np.int32)
        self.score_buf = allocate(shape=(NUM_CLASSES,), dtype=np.int16)

    def _find_ip_name(self):
        keys = list(self.overlay.ip_dict.keys())

        for name in IP_CANDIDATES:
            if name in keys:
                return name

        for key in keys:
            if "ecg_fpga_top" in key:
                return key

        raise RuntimeError("Không tìm thấy IP ecg_fpga_top trong overlay. IP hiện có: %s" % keys)

    def _write_addr64(self, low_reg, high_reg, addr):
        addr = int(addr)
        self.ip.write(low_reg, addr & 0xFFFFFFFF)
        self.ip.write(high_reg, (addr >> 32) & 0xFFFFFFFF)

    def predict(self, beat_q12):
        beat_q12 = np.asarray(beat_q12, dtype=np.int16)

        if beat_q12.size != SEGMENT_LEN:
            raise ValueError("beat_q12 phải có đúng 320 mẫu")

        self.beat_buf[:] = beat_q12
        self.pred_buf[:] = 0
        self.score_buf[:] = 0

        if hasattr(self.beat_buf, "flush"):
            self.beat_buf.flush()
        if hasattr(self.pred_buf, "flush"):
            self.pred_buf.flush()
        if hasattr(self.score_buf, "flush"):
            self.score_buf.flush()

        self._write_addr64(REG_BEAT_PTR_L, REG_BEAT_PTR_H, self.beat_buf.physical_address)
        self._write_addr64(REG_PRED_PTR_L, REG_PRED_PTR_H, self.pred_buf.physical_address)
        self._write_addr64(REG_SCORE_PTR_L, REG_SCORE_PTR_H, self.score_buf.physical_address)

        t0 = time.perf_counter()

        self.ip.write(REG_CTRL, 0x01)

        timeout_s = 5.0
        while True:
            ctrl = self.ip.read(REG_CTRL)

            ap_done = (ctrl & 0x02) != 0
            ap_idle = (ctrl & 0x04) != 0

            if ap_done or ap_idle:
                break

            if time.perf_counter() - t0 > timeout_s:
                raise TimeoutError("HLS IP timeout sau %.1f giây, CTRL=0x%08X" % (timeout_s, ctrl))

        t1 = time.perf_counter()

        if hasattr(self.pred_buf, "invalidate"):
            self.pred_buf.invalidate()
        if hasattr(self.score_buf, "invalidate"):
            self.score_buf.invalidate()

        pred = int(self.pred_buf[0])
        score_i16 = np.asarray(self.score_buf, dtype=np.int16).copy()

        if pred < 0 or pred >= NUM_CLASSES:
            pred = int(np.argmax(score_i16))

        prob = softmax_from_q12(score_i16)
        confidence = float(prob[pred])

        return {
            "ok": True,
            "backend": "FPGA HLS Dense-only Q4.12",
            "ip_name": self.ip_name,
            "pred_class": pred,
            "score5_q12": [int(x) for x in score_i16.tolist()],
            "score5_float": [q12_to_float(int(x)) for x in score_i16.tolist()],
            "prob5": [float(x) for x in prob.tolist()],
            "confidence": confidence,
            "latency_ms": (t1 - t0) * 1000.0,
            "note": "HLS dense-only: extract_light_features_40_int + Dense 40x24 + Dense 24x5"
        }


RUNNER = None
RUNNER_ERROR = None


def get_runner():
    global RUNNER, RUNNER_ERROR

    if RUNNER is not None:
        return RUNNER

    if RUNNER_ERROR is not None:
        raise RUNNER_ERROR

    try:
        RUNNER = EcgHlsRunner()
        return RUNNER
    except Exception as e:
        RUNNER_ERROR = e
        raise


class Handler(BaseHTTPRequestHandler):
    def _send_json(self, status, obj):
        data = json.dumps(obj, ensure_ascii=False).encode("utf-8")

        self.send_response(status)
        self.send_header("Content-Type", "application/json; charset=utf-8")
        self.send_header("Access-Control-Allow-Origin", "*")
        self.send_header("Access-Control-Allow-Methods", "GET,POST,OPTIONS")
        self.send_header("Access-Control-Allow-Headers", "Content-Type")
        self.send_header("Content-Length", str(len(data)))
        self.end_headers()
        self.wfile.write(data)

    def do_OPTIONS(self):
        self._send_json(200, {"ok": True})

    def do_GET(self):
        if self.path == "/health":
            try:
                runner = get_runner()
                self._send_json(200, {
                    "ok": True,
                    "overlay_loaded": True,
                    "bit_file": str(BIT_FILE),
                    "hwh_file": str(HWH_FILE),
                    "ip_name": runner.ip_name,
                    "ip_dict_keys": list(runner.overlay.ip_dict.keys()),
                    "mode": "FPGA HLS Dense-only Q4.12"
                })
            except Exception as e:
                self._send_json(500, {
                    "ok": False,
                    "overlay_loaded": False,
                    "error": str(e)
                })
            return

        self._send_json(404, {
            "ok": False,
            "error": "Endpoint không tồn tại"
        })

    def do_POST(self):
        if self.path != "/predict":
            self._send_json(404, {
                "ok": False,
                "error": "Endpoint không tồn tại"
            })
            return

        try:
            content_len = int(self.headers.get("Content-Length", "0"))
            raw = self.rfile.read(content_len)
            payload = json.loads(raw.decode("utf-8"))

            beat_q12 = to_q12_array(payload)
            runner = get_runner()
            result = runner.predict(beat_q12)

            self._send_json(200, result)

        except Exception as e:
            self._send_json(500, {
                "ok": False,
                "error": str(e)
            })


def main():
    host = "0.0.0.0"
    port = 8000

    print("ECG PYNQ HLS API server")
    print("BIT:", BIT_FILE)
    print("HWH:", HWH_FILE)
    print("URL: http://0.0.0.0:%d" % port)
    print("Health: /health")
    print("Predict: /predict")

    server = HTTPServer((host, port), Handler)
    server.serve_forever()


if __name__ == "__main__":
    main()