#!/usr/bin/env python3
from __future__ import annotations

import json
import math
import time
from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer
from pathlib import Path
from typing import Any, Dict, Tuple

import numpy as np

SIGNAL_LENGTH = 320
Q_FRAC_BITS = 12
Q_SCALE = 1 << Q_FRAC_BITS
Q_MIN = -32768
Q_MAX = 32767
LABELS = ["N", "L", "R", "V", "A"]

ROOT = Path(__file__).resolve().parent
BIT_PATH = ROOT / "ecg_accel_hls.bit"
HWH_PATH = ROOT / "ecg_accel_hls.hwh"
HOST = "0.0.0.0"
PORT = 8000

_OVERLAY = None
_IP = None
_IP_NAME = ""
_LOAD_ERROR = ""
_HW_CALLS = 0


def _softmax(x: np.ndarray) -> np.ndarray:
    x = np.asarray(x, dtype=np.float64)
    if x.size == 0:
        return np.zeros(0, dtype=np.float64)
    x = x - np.max(x)
    e = np.exp(x)
    s = np.sum(e)
    if not np.isfinite(s) or s <= 0:
        out = np.zeros_like(e)
        out[int(np.argmax(x))] = 1.0
        return out
    return e / s


def _i16_from_u16(v: int) -> int:
    v = int(v) & 0xFFFF
    return v - 0x10000 if v >= 0x8000 else v


def _decode_score5_q12(raw_words: Any) -> Tuple[np.ndarray, Dict[str, Any]]:
    """
    HLS score5_q12 is int16_t[5], but some AXI/DMA paths expose the output
    memory as 32-bit words. In that case each word packs two signed int16 values:
    low16 = score[0], high16 = score[1], ...

    This function returns exactly 5 signed Q4.12 scores so label/probability/chart
    stay consistent with pred_class.
    """
    raw = np.asarray(raw_words).reshape(-1)
    raw_i64 = raw.astype(np.int64, copy=False)
    meta: Dict[str, Any] = {
        "raw_words": [int(x) for x in raw_i64.tolist()],
        "packing": "direct_int16",
    }

    # If any value cannot be a signed int16, treat the buffer as packed 32-bit words.
    # Example: 300149160 = 0x11E3E9A8 contains two int16 scores: -5720 and 4579.
    if raw_i64.size and (np.max(np.abs(raw_i64[:5])) > 32767):
        decoded = []
        for w in raw_i64:
            wi = int(w) & 0xFFFFFFFF
            decoded.append(_i16_from_u16(wi & 0xFFFF))
            if len(decoded) >= 5:
                break
            decoded.append(_i16_from_u16((wi >> 16) & 0xFFFF))
            if len(decoded) >= 5:
                break
        while len(decoded) < 5:
            decoded.append(0)
        meta["packing"] = "packed_i16_in_u32"
        return np.asarray(decoded[:5], dtype=np.int16), meta

    decoded = []
    for x in raw_i64[:5]:
        decoded.append(_i16_from_u16(int(x)))
    while len(decoded) < 5:
        decoded.append(0)
    return np.asarray(decoded[:5], dtype=np.int16), meta


def _normalize_signal(signal: Any, length: int = SIGNAL_LENGTH) -> np.ndarray:
    arr = np.asarray(signal, dtype=np.float32).reshape(-1)
    if arr.size == 0:
        raise ValueError("signal rỗng")
    if arr.size != length:
        src = np.linspace(0.0, 1.0, arr.size, dtype=np.float32)
        dst = np.linspace(0.0, 1.0, length, dtype=np.float32)
        arr = np.interp(dst, src, arr).astype(np.float32)
    mean = float(np.mean(arr))
    std = float(np.std(arr))
    if not np.isfinite(std) or std < 1e-6:
        std = 1.0
    arr = (arr - mean) / std
    return arr.astype(np.float32)


def _quantize_q4_12(signal: Any) -> np.ndarray:
    arr = _normalize_signal(signal, SIGNAL_LENGTH)
    q = np.round(arr * Q_SCALE)
    q = np.clip(q, Q_MIN, Q_MAX).astype(np.int16)
    return q


def _write_pointer64(ip: Any, base_offset: int, addr: int) -> None:
    ip.write(base_offset, int(addr) & 0xFFFFFFFF)
    ip.write(base_offset + 4, (int(addr) >> 32) & 0xFFFFFFFF)


def _poll_done(ip: Any, timeout_s: float = 5.0) -> int:
    start_t = time.perf_counter()
    last_ctrl = 0
    while True:
        last_ctrl = int(ip.read(0x00))
        if last_ctrl & 0x2:
            return last_ctrl
        if time.perf_counter() - start_t > timeout_s:
            raise RuntimeError("timeout khi chờ AP_DONE, CTRL=0x%08x" % last_ctrl)
        time.sleep(0.0005)


def load_overlay(force: bool = False) -> Tuple[Any, str]:
    global _OVERLAY, _IP, _IP_NAME, _LOAD_ERROR
    if _IP is not None and not force:
        return _IP, _IP_NAME

    _LOAD_ERROR = ""
    if not BIT_PATH.exists():
        _LOAD_ERROR = "thiếu file " + str(BIT_PATH)
        raise RuntimeError(_LOAD_ERROR)
    if not HWH_PATH.exists():
        _LOAD_ERROR = "thiếu file " + str(HWH_PATH)
        raise RuntimeError(_LOAD_ERROR)

    try:
        from pynq import Overlay  # type: ignore
    except Exception as exc:
        _LOAD_ERROR = "không import được pynq.Overlay: " + str(exc)
        raise RuntimeError(_LOAD_ERROR)

    try:
        _OVERLAY = Overlay(str(BIT_PATH))
        candidate_ip_names = [
            "ecg_fpga_top_0",
            "ecg_accel_0",
            "ecg_hls_accel_0",
            "ecg_rtl_accel_0",
        ]
        _IP = None
        _IP_NAME = ""
        for name in candidate_ip_names:
            ip = getattr(_OVERLAY, name, None)
            if ip is not None:
                _IP = ip
                _IP_NAME = name
                break
        if _IP is None and hasattr(_OVERLAY, "ip_dict"):
            for name, meta in _OVERLAY.ip_dict.items():
                type_text = str(meta.get("type", ""))
                if "ecg_fpga_top" in name or "ecg_fpga_top" in type_text or "ecg" in name.lower():
                    ip = getattr(_OVERLAY, name, None)
                    if ip is not None:
                        _IP = ip
                        _IP_NAME = name
                        break
        if _IP is None:
            available = list(getattr(_OVERLAY, "ip_dict", {}).keys()) if hasattr(_OVERLAY, "ip_dict") else []
            raise RuntimeError("không tìm thấy IP ECG trong overlay, ip_dict=" + repr(available))
        return _IP, _IP_NAME
    except Exception as exc:
        _LOAD_ERROR = str(exc)
        _OVERLAY = None
        _IP = None
        _IP_NAME = ""
        raise


def health_payload() -> Dict[str, Any]:
    ok = False
    err = ""
    ip_dict = []
    try:
        ip, ip_name = load_overlay(False)
        ok = ip is not None
        if _OVERLAY is not None and hasattr(_OVERLAY, "ip_dict"):
            ip_dict = list(_OVERLAY.ip_dict.keys())
    except Exception as exc:
        err = str(exc)
    return {
        "ok": ok,
        "overlay_loaded": ok,
        "ip_name": _IP_NAME,
        "bit_path": str(BIT_PATH),
        "hwh_path": str(HWH_PATH),
        "bit_exists": BIT_PATH.exists(),
        "hwh_exists": HWH_PATH.exists(),
        "ip_dict": ip_dict,
        "error": err or _LOAD_ERROR,
        "hw_calls": _HW_CALLS,
    }


def predict_signal(signal: Any) -> Dict[str, Any]:
    global _HW_CALLS
    start_total = time.perf_counter()
    ip, ip_name = load_overlay(False)

    try:
        from pynq import allocate  # type: ignore
    except Exception as exc:
        raise RuntimeError("không import được pynq.allocate: " + str(exc))

    q_signal = _quantize_q4_12(signal)
    in_buf = allocate(shape=(SIGNAL_LENGTH,), dtype=np.int16)
    pred_buf = allocate(shape=(1,), dtype=np.int32)
    score_buf = allocate(shape=(8,), dtype=np.int32)
    hls_compute_ms = 0.0
    try:
        in_buf[:] = q_signal.astype(np.int16)
        pred_buf[:] = 0
        score_buf[:] = 0
        in_buf.flush()
        pred_buf.flush()
        score_buf.flush()

        _write_pointer64(ip, 0x10, in_buf.device_address)
        _write_pointer64(ip, 0x1C, pred_buf.device_address)
        _write_pointer64(ip, 0x28, score_buf.device_address)

        start_hls = time.perf_counter()
        ip.write(0x00, 0x01)
        ctrl = _poll_done(ip, timeout_s=5.0)
        hls_compute_ms = (time.perf_counter() - start_hls) * 1000.0

        pred_buf.invalidate()
        score_buf.invalidate()

        raw_pred = int(pred_buf[0])
        raw_score_words = np.asarray(score_buf[:5], dtype=np.int32)
        score5_i16, score_meta = _decode_score5_q12(raw_score_words)

        if 0 <= raw_pred < len(LABELS):
            pred_idx = raw_pred
        else:
            pred_idx = int(np.argmax(score5_i16))
        pred_idx = max(0, min(pred_idx, len(LABELS) - 1))
        label = LABELS[pred_idx]

        if np.all(score5_i16 == 0):
            probs = np.zeros(5, dtype=np.float64)
            probs[pred_idx] = 1.0
        else:
            probs = _softmax(score5_i16.astype(np.float64) / float(Q_SCALE))
        prob_dict = {LABELS[i]: float(probs[i]) for i in range(5)}
        confidence = float(probs[pred_idx]) if probs.size and 0 <= pred_idx < probs.size else 0.0
        _HW_CALLS += 1
        total_ms = (time.perf_counter() - start_total) * 1000.0
        return {
            "ok": True,
            "label": label,
            "predicted_label": label,
            "confidence": confidence,
            "probabilities": prob_dict,
            "latency_ms": total_ms,
            "hls_compute_ms": hls_compute_ms,
            "pred_class": raw_pred,
            "score5_q12": [int(x) for x in score5_i16.tolist()],
            "raw_score_words": [int(x) for x in raw_score_words.tolist()],
            "score_packing": score_meta.get("packing"),
            "ctrl": int(ctrl),
            "ip_name": ip_name,
            "hw_calls": _HW_CALLS,
            "note": "PYNQ-Z2 remote ECG HLS API: ip=%s, pred_class=%s, score5_q12=%s, raw_score_words=%s, packing=%s, hls_compute_ms=%.4f" % (
                ip_name, raw_pred, [int(x) for x in score5_i16.tolist()], [int(x) for x in raw_score_words.tolist()], score_meta.get("packing"), hls_compute_ms
            ),
        }
    finally:
        for buf in (in_buf, pred_buf, score_buf):
            try:
                buf.freebuffer()
            except Exception:
                pass


class Handler(BaseHTTPRequestHandler):
    server_version = "PYNQECGHLS/1.0"

    def _send_json(self, status: int, payload: Dict[str, Any]) -> None:
        body = json.dumps(payload, ensure_ascii=False).encode("utf-8")
        self.send_response(status)
        self.send_header("Content-Type", "application/json; charset=utf-8")
        self.send_header("Content-Length", str(len(body)))
        self.send_header("Access-Control-Allow-Origin", "*")
        self.send_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS")
        self.send_header("Access-Control-Allow-Headers", "Content-Type")
        self.end_headers()
        self.wfile.write(body)

    def do_OPTIONS(self) -> None:
        self._send_json(200, {"ok": True})

    def do_GET(self) -> None:
        if self.path.split("?", 1)[0] == "/health":
            self._send_json(200, health_payload())
            return
        self._send_json(404, {"ok": False, "error": "not found"})

    def do_POST(self) -> None:
        path = self.path.split("?", 1)[0]
        if path not in ("/predict", "/predict_beat"):
            self._send_json(404, {"ok": False, "error": "not found"})
            return
        try:
            length = int(self.headers.get("Content-Length", "0") or "0")
            raw = self.rfile.read(length)
            req = json.loads(raw.decode("utf-8")) if raw else {}
            signal = req.get("signal") or req.get("beat") or req.get("x")
            if signal is None:
                raise ValueError("request thiếu field signal")
            out = predict_signal(signal)
            self._send_json(200, out)
        except Exception as exc:
            self._send_json(400, {"ok": False, "error": str(exc), "health": health_payload()})

    def log_message(self, fmt: str, *args: Any) -> None:
        print("[%s] %s" % (self.log_date_time_string(), fmt % args))


if __name__ == "__main__":
    print("PYNQ ECG HLS API server")
    print("Overlay dir:", ROOT)
    print("BIT:", BIT_PATH)
    print("HWH:", HWH_PATH)
    print("Health check: http://<PYNQ_IP>:%d/health" % PORT)
    print("Predict API : POST http://<PYNQ_IP>:%d/predict" % PORT)
    print("Loading overlay once...")
    print(json.dumps(health_payload(), ensure_ascii=False, indent=2))
    ThreadingHTTPServer((HOST, PORT), Handler).serve_forever()
