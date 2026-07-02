#!/usr/bin/env python3
from __future__ import annotations

import csv
import json
import math
import os
import sys
import urllib.request
from pathlib import Path

PYNQ_HLS_URL = os.environ.get("PYNQ_HLS_URL", "http://192.168.2.99:8000").rstrip("/")


def read_signal(path: str):
    text = Path(path).read_text(encoding="utf-8", errors="ignore")
    vals = []
    for row in csv.reader(text.replace(";", ",").splitlines()):
        for cell in row:
            cell = cell.strip()
            if not cell:
                continue
            try:
                vals.append(float(cell))
            except Exception:
                pass
    if not vals:
        raise SystemExit("Không đọc được số nào từ file: " + path)
    return vals


def demo_signal(n=320):
    return [math.sin(2.0 * math.pi * 5.0 * i / n) for i in range(n)]


def post_json(path: str, payload: dict):
    data = json.dumps(payload).encode("utf-8")
    req = urllib.request.Request(path, data=data, headers={"Content-Type": "application/json"})
    with urllib.request.urlopen(req, timeout=15.0) as resp:
        return json.loads(resp.read().decode("utf-8"))


if __name__ == "__main__":
    if len(sys.argv) > 1:
        signal = read_signal(sys.argv[1])
    else:
        signal = demo_signal()
    out = post_json(PYNQ_HLS_URL + "/predict", {"signal": signal})
    print(json.dumps(out, indent=2, ensure_ascii=False))
