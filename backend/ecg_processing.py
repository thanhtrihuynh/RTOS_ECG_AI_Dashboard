from __future__ import annotations

import csv
import io
import re
from collections import defaultdict
from dataclasses import dataclass
from pathlib import Path
from typing import Any, Dict, List, Optional, Tuple
from uuid import uuid4

import numpy as np

from .config import INDEX_TO_LABEL, LABELS, SIGNAL_LENGTH


@dataclass
class ParsedDataset:
    upload_id: str
    filename: str
    format_type: str
    beats: np.ndarray
    true_labels: List[Optional[str]]
    raw_rows: int
    raw_cols: int
    raw_samples_per_beat: int
    warnings: List[str]
    info: Dict[str, Any]


ANN_CODE_TO_SYMBOL = {
    1: "N", 2: "L", 3: "R", 4: "a", 5: "V", 6: "F", 7: "J", 8: "A",
    9: "S", 10: "E", 11: "j", 12: "/", 13: "Q", 14: "~",
    16: "|", 18: "s", 19: "T", 20: "*", 21: "D", 22: '"',
    23: "=", 24: "p", 25: "B", 26: "^", 27: "t", 28: "+",
    29: "u", 30: "?", 31: "!", 32: "[", 33: "]", 34: "e",
    35: "n", 36: "@", 37: "x", 38: "f", 39: "(", 40: ")",
}

SYMBOL_TO_TARGET = {
    "N": "N",
    "L": "L",
    "R": "R",
    "V": "V",
    "A": "A",
    "a": "A",
}


def format_time(seconds: float) -> str:
    seconds = float(seconds)
    minutes = int(seconds // 60)
    sec = seconds - minutes * 60
    return f"{minutes:02d}:{sec:06.3f}"


def make_segment_meta(record_id: str, channel: str, start: int, end: int, label: str | None, fs: int, ann_sample: int | None = None) -> Dict[str, Any]:
    start_sec = float(start) / float(fs)
    end_sec = float(end) / float(fs)
    return {
        "record_id": record_id,
        "channel": channel,
        "start": int(start),
        "end": int(end),
        "label": label,
        "fs": int(fs),
        "ann_sample": int(ann_sample) if ann_sample is not None else None,
        "start_time_sec": start_sec,
        "end_time_sec": end_sec,
        "start_time": format_time(start_sec),
        "end_time": format_time(end_sec),
    }


def normalize_signal(signal: np.ndarray, length: int = SIGNAL_LENGTH) -> np.ndarray:
    signal = np.asarray(signal, dtype=np.float32).flatten()

    if signal.size == 0:
        return np.zeros(length, dtype=np.float32)

    signal = np.nan_to_num(signal, nan=0.0, posinf=0.0, neginf=0.0)

    if signal.size != length:
        xp = np.linspace(0.0, 1.0, signal.size)
        xnew = np.linspace(0.0, 1.0, length)
        signal = np.interp(xnew, xp, signal).astype(np.float32)

    # Match training pipeline: z-score normalization, not metadata values and not max-abs scaling.
    mean = float(np.mean(signal))
    std = float(np.std(signal))
    signal = signal - mean
    if std > 1e-8:
        signal = signal / std

    return signal.astype(np.float32)


def _numeric_from_cell(cell: str) -> Optional[float]:
    cell = cell.strip()
    if cell == "":
        return None
    try:
        return float(cell)
    except Exception:
        return None


def read_numeric_csv(raw_bytes: bytes) -> Tuple[np.ndarray, List[str]]:
    text = raw_bytes.decode("utf-8", errors="replace")
    reader = csv.reader(io.StringIO(text))

    numeric_rows: List[List[float]] = []
    warnings: List[str] = []
    skipped = 0
    expected_len: Optional[int] = None

    for row in reader:
        if not row:
            continue

        vals = []
        for cell in row:
            v = _numeric_from_cell(cell)
            if v is not None:
                vals.append(v)

        if not vals:
            skipped += 1
            continue

        if expected_len is None:
            expected_len = len(vals)

        if len(vals) != expected_len:
            skipped += 1
            continue

        numeric_rows.append(vals)

    if not numeric_rows:
        raise ValueError("CSV không có dữ liệu số hợp lệ.")

    if skipped:
        warnings.append(f"Đã bỏ qua {skipped} dòng không hợp lệ hoặc khác số cột.")

    return np.asarray(numeric_rows, dtype=np.float32), warnings


def detect_label_column(matrix: np.ndarray) -> Tuple[bool, List[Optional[str]], np.ndarray, List[str], Dict[str, Any]]:
    warnings: List[str] = []
    info: Dict[str, Any] = {}

    if matrix.ndim != 2 or matrix.shape[1] < 2:
        return False, [None] * matrix.shape[0], matrix, warnings, info

    last = matrix[:, -1]
    unique = np.unique(last)
    is_integer_like = np.all(np.abs(unique - np.round(unique)) < 1e-6)
    has_few_unique = len(unique) <= 20

    if not (is_integer_like and has_few_unique):
        return False, [None] * matrix.shape[0], matrix, warnings, info

    unique_int = sorted(int(round(v)) for v in unique.tolist())
    info["label_values_detected"] = unique_int

    labels: List[Optional[str]] = []
    unsupported = sorted(set(unique_int) - set(INDEX_TO_LABEL.keys()))

    if unsupported:
        warnings.append(
            f"Cột cuối giống nhãn nhưng có giá trị ngoài 0..4: {unsupported}. "
            "Các giá trị này sẽ để true_label = unknown."
        )

    if set(unique_int).issubset({0, 1}) and len(unique_int) <= 2:
        warnings.append(
            "CSV có vẻ là nhãn nhị phân 0/1, không đủ 5 lớp N/L/R/V/A. "
            "Accuracy chỉ có ý nghĩa nếu mapping nhãn đúng."
        )

    for v in last:
        iv = int(round(float(v)))
        labels.append(INDEX_TO_LABEL.get(iv))

    return True, labels, matrix[:, :-1], warnings, info


def find_r_peaks(signal: np.ndarray, min_distance: int = 70) -> List[int]:
    x = np.asarray(signal, dtype=np.float32).flatten()
    if x.size < 20:
        return []

    x = x - np.median(x)
    std = float(np.std(x))
    if std < 1e-8:
        return []

    threshold = float(np.mean(x) + 0.75 * std)
    candidates: List[int] = []

    for i in range(1, len(x) - 1):
        if x[i] > threshold and x[i] >= x[i - 1] and x[i] >= x[i + 1]:
            candidates.append(i)

    if not candidates:
        return []

    peaks: List[int] = []
    last_peak = -10**9

    for idx in candidates:
        if idx - last_peak >= min_distance:
            peaks.append(idx)
            last_peak = idx
        else:
            if x[idx] > x[peaks[-1]]:
                peaks[-1] = idx
                last_peak = idx

    return peaks


def segment_long_ecg(signal: np.ndarray, fs: int = 360, left: int = 160, right: int = 159) -> Tuple[np.ndarray, List[int], List[str]]:
    warnings: List[str] = []
    signal = np.asarray(signal, dtype=np.float32).flatten()

    if signal.size < SIGNAL_LENGTH:
        warnings.append("Tín hiệu dài ngắn hơn 187 mẫu, chỉ chuẩn hóa thành 1 heartbeat.")
        return np.asarray([normalize_signal(signal)], dtype=np.float32), [0], warnings

    min_distance = max(30, int(0.22 * fs))
    peaks = find_r_peaks(signal, min_distance=min_distance)

    beats: List[np.ndarray] = []
    used_peaks: List[int] = []

    for p in peaks:
        start = p - left
        end = p + right + 1
        if start < 0 or end > len(signal):
            continue
        beats.append(normalize_signal(signal[start:end]))
        used_peaks.append(p)

    if not beats:
        warnings.append("Không phát hiện được R-peak đủ tốt. Tạm xem toàn bộ CSV là 1 heartbeat.")
        return np.asarray([normalize_signal(signal)], dtype=np.float32), [0], warnings

    return np.asarray(beats, dtype=np.float32), used_peaks, warnings


def parse_csv_dataset(raw_bytes: bytes, filename: str, fs: int = 360) -> ParsedDataset:
    matrix, warnings = read_numeric_csv(raw_bytes)
    raw_rows, raw_cols = matrix.shape
    upload_id = uuid4().hex
    info: Dict[str, Any] = {}

    if raw_cols == 1:
        signal = matrix[:, 0]
        beats, r_peaks, seg_warnings = segment_long_ecg(signal, fs=fs)
        warnings.extend(seg_warnings)
        info["r_peak_count"] = len(r_peaks)
        info["r_peaks_preview"] = r_peaks[:200]
        return ParsedDataset(upload_id, filename, "csv_long_single_column", beats, [None] * len(beats),
                             raw_rows, raw_cols, raw_rows, warnings, info)

    if raw_rows == 1 and raw_cols > 20:
        signal = matrix[0, :]
        beats, r_peaks, seg_warnings = segment_long_ecg(signal, fs=fs)
        warnings.extend(seg_warnings)
        info["r_peak_count"] = len(r_peaks)
        info["r_peaks_preview"] = r_peaks[:200]
        return ParsedDataset(upload_id, filename, "csv_long_single_row", beats, [None] * len(beats),
                             raw_rows, raw_cols, raw_cols, warnings, info)

    has_label, true_labels, samples, label_warnings, label_info = detect_label_column(matrix)
    warnings.extend(label_warnings)
    info.update(label_info)
    info["has_label_column"] = has_label

    beats = np.asarray([normalize_signal(row) for row in samples], dtype=np.float32)

    return ParsedDataset(upload_id, filename, "csv_heartbeat_table", beats, true_labels,
                         raw_rows, raw_cols, samples.shape[1], warnings, info)


def parse_gain(value: str) -> float:
    # Examples: "200", "200/mV", "200(1024)/mV"
    m = re.match(r"([-+]?\d+(\.\d+)?)", value)
    if not m:
        return 200.0
    gain = float(m.group(1))
    return gain if abs(gain) > 1e-12 else 200.0


def parse_hea(raw: bytes) -> Dict[str, Any]:
    text = raw.decode("utf-8", errors="replace")
    lines = [line.strip() for line in text.splitlines() if line.strip() and not line.startswith("#")]
    if not lines:
        raise ValueError("Header .hea rỗng hoặc không hợp lệ.")

    first = lines[0].split()
    record_name = first[0]
    nsig = int(first[1])
    fs = int(float(first[2]))
    nsamp = int(first[3]) if len(first) > 3 else 0

    signals = []
    for line in lines[1:1 + nsig]:
        parts = line.split()
        if len(parts) < 8:
            continue

        sig = {
            "file": parts[0],
            "fmt": parts[1],
            "gain": parse_gain(parts[2]),
            "adc_zero": int(float(parts[4])) if len(parts) > 4 else 0,
            "description": " ".join(parts[8:]) if len(parts) > 8 else f"ch{len(signals)}",
        }
        signals.append(sig)

    if not signals:
        raise ValueError("Không đọc được signal line trong .hea.")

    return {
        "record_name": record_name,
        "nsig": nsig,
        "fs": fs,
        "nsamp": nsamp,
        "signals": signals,
    }


def decode_format_212(raw_dat: bytes, nsig: int = 2, nsamp: int = 0) -> np.ndarray:
    data = np.frombuffer(raw_dat, dtype=np.uint8)
    n_triplets = len(data) // 3
    if n_triplets == 0:
        raise ValueError(".dat quá ngắn hoặc không đúng format 212.")

    triplets = data[:n_triplets * 3].reshape(-1, 3)
    b0 = triplets[:, 0].astype(np.int32)
    b1 = triplets[:, 1].astype(np.int32)
    b2 = triplets[:, 2].astype(np.int32)

    s0 = b0 | ((b1 & 0x0F) << 8)
    s1 = b2 | ((b1 & 0xF0) << 4)

    s0 = np.where(s0 >= 2048, s0 - 4096, s0)
    s1 = np.where(s1 >= 2048, s1 - 4096, s1)

    arr = np.stack([s0, s1], axis=1).astype(np.float32)

    if nsamp and arr.shape[0] > nsamp:
        arr = arr[:nsamp, :]

    if nsig == 1:
        arr = arr[:, :1]

    return arr


def parse_atr_annotations(raw_atr: bytes) -> List[Tuple[int, str]]:
    data = np.frombuffer(raw_atr, dtype=np.uint8)
    annotations: List[Tuple[int, str]] = []
    i = 0
    sample = 0

    while i + 1 < len(data):
        word = int(data[i]) | (int(data[i + 1]) << 8)
        i += 2

        ann_type = word >> 10
        interval = word & 0x03FF

        if ann_type == 0:
            break

        if ann_type == 59:  # SKIP
            if i + 3 < len(data):
                skip = int(data[i]) | (int(data[i + 1]) << 8) | (int(data[i + 2]) << 16) | (int(data[i + 3]) << 24)
                i += 4
                sample += skip
            continue

        if ann_type == 60:  # NUM
            continue

        if ann_type == 61:  # SUB
            continue

        if ann_type == 62:  # CHN
            continue

        if ann_type == 63:  # AUX
            n = interval
            i += n
            if n % 2 == 1:
                i += 1
            continue

        sample += interval
        symbol = ANN_CODE_TO_SYMBOL.get(ann_type, f"code_{ann_type}")
        annotations.append((sample, symbol))

    return annotations


def normalize_channel_name(name: str) -> str:
    return str(name or "").upper().replace(" ", "").replace("-", "").replace("_", "")


def choose_signal_channel(header: Dict[str, Any]) -> int:
    descriptions = [s.get("description", "") for s in header["signals"]]
    normalized = [normalize_channel_name(d) for d in descriptions]
    for target in ["MLII", "ML2"]:
        if target in normalized:
            return normalized.index(target)
    return 0


def parse_single_wfdb_record(stem: str, files: Dict[str, bytes], fs_override: Optional[int] = None) -> Tuple[np.ndarray, List[Optional[str]], List[str], Dict[str, Any]]:
    warnings: List[str] = []
    info: Dict[str, Any] = {"record": stem}

    if ".hea" not in files or ".dat" not in files:
        raise ValueError(f"Record {stem} thiếu .hea hoặc .dat.")

    header = parse_hea(files[".hea"])
    fs = fs_override or header["fs"]
    nsig = header["nsig"]
    nsamp = header["nsamp"]
    info["fs"] = fs
    info["nsig"] = nsig
    info["nsamp"] = nsamp
    info["signals"] = [s.get("description", "") for s in header["signals"]]

    fmt = header["signals"][0]["fmt"]
    if fmt != "212":
        raise ValueError(f"Record {stem} dùng format {fmt}, bản demo hiện hỗ trợ format 212.")

    raw_adc = decode_format_212(files[".dat"], nsig=nsig, nsamp=nsamp)
    ch = choose_signal_channel(header)
    ch = min(ch, raw_adc.shape[1] - 1)
    sig_meta = header["signals"][ch]

    gain = float(sig_meta.get("gain", 200.0))
    adc_zero = float(sig_meta.get("adc_zero", 0.0))
    signal = (raw_adc[:, ch] - adc_zero) / gain
    info["selected_channel"] = sig_meta.get("description", f"ch{ch}")

    beats: List[np.ndarray] = []
    labels: List[Optional[str]] = []
    label_counts: Dict[str, int] = {}
    ignored_counts: Dict[str, int] = {}
    segment_meta: List[Dict[str, Any]] = []

    if ".atr" in files:
        ann = parse_atr_annotations(files[".atr"])
        info["annotation_count"] = len(ann)

        left, right = 160, 159

        for sample_idx, symbol in ann:
            target = SYMBOL_TO_TARGET.get(symbol)
            if target is None:
                ignored_counts[symbol] = ignored_counts.get(symbol, 0) + 1
                continue

            start = sample_idx - left
            end = sample_idx + right + 1
            if start < 0 or end > len(signal):
                continue

            beats.append(normalize_signal(signal[start:end]))
            labels.append(target)
            label_counts[target] = label_counts.get(target, 0) + 1
            segment_meta.append(make_segment_meta(
                record_id=stem,
                channel=str(sig_meta.get("description", f"ch{ch}")),
                start=int(start),
                end=int(end - 1),
                label=target,
                fs=int(fs),
                ann_sample=int(sample_idx),
            ))

        info["target_label_counts"] = label_counts
        info["ignored_annotation_counts"] = ignored_counts

        if not beats:
            warnings.append(f"Record {stem} có annotation nhưng không có beat thuộc N/L/R/V/A. Sẽ thử R-peak segmentation không nhãn.")
            seg_beats, r_peaks, seg_warnings = segment_long_ecg(signal, fs=fs)
            beats = list(seg_beats)
            labels = [None] * len(beats)
            warnings.extend([f"{stem}: {w}" for w in seg_warnings])
            info["r_peak_count"] = len(r_peaks)
            segment_meta = [make_segment_meta(
                record_id=stem,
                channel=str(sig_meta.get("description", f"ch{ch}")),
                start=max(0, int(p - 160)),
                end=min(len(signal) - 1, int(p + 159)),
                label=None,
                fs=int(fs),
                ann_sample=int(p),
            ) for p in r_peaks[:len(beats)]]
    else:
        warnings.append(f"Record {stem} không có .atr, sẽ dùng R-peak segmentation không nhãn.")
        seg_beats, r_peaks, seg_warnings = segment_long_ecg(signal, fs=fs)
        beats = list(seg_beats)
        labels = [None] * len(beats)
        warnings.extend([f"{stem}: {w}" for w in seg_warnings])
        info["r_peak_count"] = len(r_peaks)

    info["segments"] = segment_meta
    return np.asarray(beats, dtype=np.float32), labels, warnings, info


def parse_wfdb_bundle(file_payloads: List[Tuple[str, bytes]], fs: int = 360) -> ParsedDataset:
    groups: Dict[str, Dict[str, bytes]] = defaultdict(dict)
    ignored_files: List[str] = []

    for name, raw in file_payloads:
        suffix = Path(name).suffix.lower()
        stem = Path(name).stem
        if suffix in {".hea", ".dat", ".atr"}:
            groups[stem][suffix] = raw
        else:
            ignored_files.append(name)

    warnings: List[str] = []
    if ignored_files:
        warnings.append(f"Bỏ qua file không cần cho parsing WFDB: {', '.join(ignored_files[:10])}")

    all_beats: List[np.ndarray] = []
    all_labels: List[Optional[str]] = []
    records_info: List[Dict[str, Any]] = []
    all_segments: List[Dict[str, Any]] = []

    for stem in sorted(groups.keys()):
        files = groups[stem]
        if ".hea" not in files or ".dat" not in files:
            warnings.append(f"Bỏ qua {stem}: thiếu .hea hoặc .dat.")
            continue

        try:
            beats, labels, record_warnings, info = parse_single_wfdb_record(stem, files, fs_override=None)
            warnings.extend(record_warnings)
            records_info.append(info)
            all_segments.extend(info.get("segments", []))
            for beat in beats:
                all_beats.append(beat)
            all_labels.extend(labels)
        except Exception as exc:
            warnings.append(f"Bỏ qua record {stem}: {exc}")

    if not all_beats:
        raise ValueError("Không parse được heartbeat nào từ các file WFDB đã upload.")

    beats_arr = np.asarray(all_beats, dtype=np.float32)

    label_counts: Dict[str, int] = {}
    for lab in all_labels:
        if lab is not None:
            label_counts[lab] = label_counts.get(lab, 0) + 1

    info = {
        "records": records_info,
        "record_count": len(records_info),
        "label_counts": label_counts,
        "segments": all_segments,
    }

    return ParsedDataset(
        upload_id=uuid4().hex,
        filename="WFDB upload",
        format_type="wfdb_mitbih",
        beats=beats_arr,
        true_labels=all_labels,
        raw_rows=int(beats_arr.shape[0]),
        raw_cols=SIGNAL_LENGTH,
        raw_samples_per_beat=SIGNAL_LENGTH,
        warnings=warnings,
        info=info,
    )


def labels_from_array(y: np.ndarray) -> List[Optional[str]]:
    y = np.asarray(y).flatten()
    labels: List[Optional[str]] = []

    for value in y:
        if isinstance(value, bytes):
            value = value.decode("utf-8", errors="replace")

        if isinstance(value, str):
            value = value.strip()
            labels.append(value if value in LABELS else None)
        else:
            iv = int(round(float(value)))
            labels.append(INDEX_TO_LABEL.get(iv))

    return labels


def parse_numpy_dataset(file_payloads: List[Tuple[str, bytes]]) -> ParsedDataset:
    warnings: List[str] = []

    if len(file_payloads) != 1:
        warnings.append("NumPy loader hiện chỉ đọc một file .npy hoặc .npz mỗi lần.")

    name, raw = file_payloads[0]
    suffix = Path(name).suffix.lower()

    if suffix == ".npy":
        arr = np.load(io.BytesIO(raw), allow_pickle=False)
        labels = [None] * (arr.shape[0] if arr.ndim > 1 else 1)
    elif suffix == ".npz":
        data = np.load(io.BytesIO(raw), allow_pickle=False)
        if "X" not in data:
            raise ValueError(".npz cần có key X chứa ECG data.")
        arr = data["X"]
        labels = labels_from_array(data["y"]) if "y" in data else [None] * arr.shape[0]
    else:
        raise ValueError("Không phải file NumPy .npy/.npz.")

    arr = np.asarray(arr, dtype=np.float32)

    if arr.ndim == 1:
        beats = np.asarray([normalize_signal(arr)], dtype=np.float32)
        labels = [labels[0] if labels else None]
    elif arr.ndim == 2:
        beats = np.asarray([normalize_signal(row) for row in arr], dtype=np.float32)
        if len(labels) != len(beats):
            warnings.append("Số nhãn y không khớp số heartbeat, bỏ qua nhãn.")
            labels = [None] * len(beats)
    else:
        raise ValueError("NumPy data phải có shape [length] hoặc [n_beats, length].")

    return ParsedDataset(
        upload_id=uuid4().hex,
        filename=name,
        format_type="numpy_npy_npz",
        beats=beats,
        true_labels=labels,
        raw_rows=int(arr.shape[0]) if arr.ndim > 1 else 1,
        raw_cols=int(arr.shape[1]) if arr.ndim > 1 else int(arr.shape[0]),
        raw_samples_per_beat=int(arr.shape[1]) if arr.ndim > 1 else int(arr.shape[0]),
        warnings=warnings,
        info={"source": suffix},
    )


def concat_datasets(datasets: List[ParsedDataset], format_type: str, filename: str) -> ParsedDataset:
    if not datasets:
        raise ValueError("Không có dataset để nối.")

    beats = np.concatenate([d.beats for d in datasets], axis=0)
    labels: List[Optional[str]] = []
    warnings: List[str] = []
    info: Dict[str, Any] = {"sources": []}

    for d in datasets:
        labels.extend(d.true_labels)
        warnings.extend(d.warnings)
        info["sources"].append({
            "filename": d.filename,
            "format_type": d.format_type,
            "total_beats": len(d.beats),
            "info": d.info,
        })

    return ParsedDataset(
        upload_id=uuid4().hex,
        filename=filename,
        format_type=format_type,
        beats=beats,
        true_labels=labels,
        raw_rows=int(beats.shape[0]),
        raw_cols=int(beats.shape[1]),
        raw_samples_per_beat=int(beats.shape[1]),
        warnings=warnings,
        info=info,
    )


def parse_uploaded_files(file_payloads: List[Tuple[str, bytes]], fs: int = 360) -> ParsedDataset:
    if not file_payloads:
        raise ValueError("Chưa upload file nào.")

    suffixes = [Path(name).suffix.lower() for name, _ in file_payloads]

    # WFDB ưu tiên nếu có .hea hoặc .dat.
    if any(s in {".hea", ".dat", ".atr"} for s in suffixes):
        return parse_wfdb_bundle(file_payloads, fs=fs)

    if any(s in {".npy", ".npz"} for s in suffixes):
        return parse_numpy_dataset(file_payloads)

    csv_files = [(name, raw) for name, raw in file_payloads if Path(name).suffix.lower() in {".csv", ".txt"}]
    if csv_files:
        datasets = [parse_csv_dataset(raw, name, fs=fs) for name, raw in csv_files]
        if len(datasets) == 1:
            return datasets[0]
        return concat_datasets(datasets, "multi_csv", "Multiple CSV upload")

    raise ValueError("Định dạng chưa hỗ trợ. Hãy upload .csv, .txt, .npy, .npz hoặc bộ WFDB .hea/.dat/.atr.")
