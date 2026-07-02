from __future__ import annotations

import csv
import json
import platform
from datetime import datetime
from pathlib import Path
from typing import Dict, List, Optional
from uuid import uuid4

import numpy as np
from fastapi import FastAPI, File, HTTPException, UploadFile
from fastapi.responses import FileResponse, HTMLResponse, StreamingResponse
from fastapi.staticfiles import StaticFiles
from pydantic import BaseModel

from .config import BACKENDS, LABEL_INFO, LABELS, SIGNAL_LENGTH
from .ecg_processing import ParsedDataset, parse_csv_dataset, parse_uploaded_files, parse_wfdb_bundle
from .record_store import delete_record, get_record_file_payloads, list_records, make_record_zip, save_wfdb_record
from .model_store import get_model_file_status, import_fpga_export
from .bulk_dataset import bulk_status, import_dataset_folder, label_record_summary, load_record_segments, load_segment_signal, search_segments
from .inference import get_system_status, reload_runtime_models, run_prediction


ROOT = Path(__file__).resolve().parents[1]
STATIC_DIR = ROOT / "static"
LOG_DIR = ROOT / "benchmark_logs"
LOG_DIR.mkdir(exist_ok=True)

app = FastAPI(
    title="ECG Guided-Input AI Dashboard for PYNQ-Z2",
    version="4.0.0",
)

DATASETS: Dict[str, ParsedDataset] = {}
RESULTS: Dict[str, Dict] = {}


class PredictBeatRequest(BaseModel):
    upload_id: str
    beat_index: int = 0
    backend: str = "cpu_float32"


class PredictDatasetRequest(BaseModel):
    upload_id: str
    backend: str = "cpu_float32"
    max_beats: Optional[int] = None


class PredictDatasetMultiRequest(BaseModel):
    upload_id: str
    backends: List[str] = []
    max_beats: Optional[int] = None


class PredictBeatMultiRequest(BaseModel):
    upload_id: str
    beat_index: int = 0
    backends: List[str] = []


def dataset_to_response(ds: ParsedDataset) -> Dict:
    first_signal = ds.beats[0].round(6).tolist() if len(ds.beats) else []
    return {
        "upload_id": ds.upload_id,
        "filename": ds.filename,
        "format_type": ds.format_type,
        "total_beats": int(len(ds.beats)),
        "raw_rows": int(ds.raw_rows),
        "raw_cols": int(ds.raw_cols),
        "raw_samples_per_beat": int(ds.raw_samples_per_beat),
        "normalized_length": SIGNAL_LENGTH,
        "has_labels": any(x is not None for x in ds.true_labels),
        "label_preview": ds.true_labels[:20],
        "warnings": ds.warnings,
        "info": ds.info,
        "first_signal": first_signal,
        "first_true_label": ds.true_labels[0] if ds.true_labels else None,
        "record_context": get_dataset_record_context(ds),
    }




def validate_wfdb_record_names(payloads):
    from pathlib import Path
    stems = {}
    for filename, _ in payloads:
        suffix = Path(filename).suffix.lower()
        if suffix in {'.hea', '.dat', '.atr', '.xws'}:
            stems[suffix] = Path(filename).stem

    if '.hea' not in stems or '.dat' not in stems:
        raise ValueError('WFDB cần tối thiểu .hea và .dat.')

    base = stems['.hea']
    mismatched = {ext: stem for ext, stem in stems.items() if stem != base}
    if mismatched:
        details = ', '.join([f'{ext}={stem}' for ext, stem in stems.items()])
        raise ValueError(
            'Các file WFDB phải cùng record ID. '
            f'Bạn đang chọn: {details}. '
            f'Hãy chọn cùng một record, ví dụ: {base}.hea, {base}.dat, {base}.atr, {base}.xws.'
        )



def get_dataset_record_context(ds: ParsedDataset) -> Dict:
    info = ds.info if isinstance(ds.info, dict) else {}
    record_ids = []
    if info.get('record_id'):
        record_ids.append(str(info.get('record_id')))
    segments = info.get('segments')
    if isinstance(segments, list):
        for seg in segments:
            rid = seg.get('record_id') if isinstance(seg, dict) else None
            if rid is not None and str(rid) not in record_ids:
                record_ids.append(str(rid))
    records = info.get('records')
    if isinstance(records, list):
        for rec in records:
            rid = rec.get('record') or rec.get('record_id') if isinstance(rec, dict) else None
            if rid is not None and str(rid) not in record_ids:
                record_ids.append(str(rid))
    if not record_ids and ds.filename:
        record_ids.append(str(ds.filename))
    return {
        'record_ids': record_ids,
        'record_text': ', '.join(record_ids[:10]) + (' ...' if len(record_ids) > 10 else ''),
        'format_type': ds.format_type,
        'total_beats': int(len(ds.beats)),
    }

@app.get("/", response_class=HTMLResponse)
def index():
    return (STATIC_DIR / "index.html").read_text(encoding="utf-8")


@app.get("/api/status")
def status():
    return {
        "labels": LABELS,
        "label_info": LABEL_INFO,
        "backends": BACKENDS,
        "signal_length": SIGNAL_LENGTH,
        "system_status": get_system_status(),
        "input_modes": [
            "csv_heartbeat_table",
            "csv_long_ecg",
            "wfdb_guided",
        ],
    }


@app.post("/api/upload_data")
async def upload_data(files: List[UploadFile] = File(...), fs: int = 360):
    if not files:
        raise HTTPException(status_code=400, detail="Chưa upload file nào.")

    payloads = []
    for f in files:
        raw = await f.read()
        if raw:
            payloads.append((f.filename or "uploaded", raw))

    if not payloads:
        raise HTTPException(status_code=400, detail="File upload rỗng.")

    try:
        ds = parse_uploaded_files(payloads, fs=fs)
    except Exception as exc:
        raise HTTPException(status_code=400, detail=str(exc))

    DATASETS[ds.upload_id] = ds
    return dataset_to_response(ds)


@app.post("/api/upload_csv_mode")
async def upload_csv_mode(file: UploadFile = File(...), mode: str = "heartbeat_table", fs: int = 360):
    raw = await file.read()
    if not raw:
        raise HTTPException(status_code=400, detail="File rỗng.")

    try:
        ds = parse_csv_dataset(raw, filename=file.filename or "uploaded.csv", fs=fs)
    except Exception as exc:
        raise HTTPException(status_code=400, detail=str(exc))

    # Ghi đè tên format theo mode UI để giao diện dễ hiểu hơn
    if mode == "heartbeat_table":
        ds.format_type = "csv_heartbeat_table"
    elif mode == "long_ecg":
        ds.format_type = "csv_long_ecg"

    DATASETS[ds.upload_id] = ds
    return dataset_to_response(ds)


@app.post("/api/upload_wfdb_guided")
async def upload_wfdb_guided(
    hea_file: UploadFile = File(...),
    dat_file: UploadFile = File(...),
    atr_file: Optional[UploadFile] = File(None),
    xws_file: Optional[UploadFile] = File(None),
    fs: int = 360,
    save: bool = False,
):
    payloads = []

    for f in [hea_file, dat_file, atr_file, xws_file]:
        if f is None:
            continue
        raw = await f.read()
        if raw:
            payloads.append((f.filename or "uploaded", raw))

    if len(payloads) < 2:
        raise HTTPException(status_code=400, detail="WFDB cần tối thiểu .hea và .dat.")

    try:
        validate_wfdb_record_names(payloads)
        ds = parse_wfdb_bundle(payloads, fs=fs)
        if save:
            saved_meta = save_wfdb_record(payloads)
            ds.info["saved_record"] = saved_meta
            ds.warnings.append(
                f"Record {saved_meta['record_id']} đã được lưu vào record_library theo từng thư mục .hea/.dat/.atr/.xws."
            )
        else:
            ds.warnings.append(
                "Chỉ parse để xem/dự đoán. Record chưa được lưu vào Record Library. Muốn lưu hãy bấm Parse & Save."
            )
    except Exception as exc:
        raise HTTPException(status_code=400, detail=str(exc))

    DATASETS[ds.upload_id] = ds
    return dataset_to_response(ds)


@app.get("/api/dataset/{upload_id}/beat/{beat_index}")
def get_beat(upload_id: str, beat_index: int):
    ds = DATASETS.get(upload_id)
    if ds is None:
        raise HTTPException(status_code=404, detail="Dataset not found")

    if beat_index < 0 or beat_index >= len(ds.beats):
        raise HTTPException(status_code=400, detail="beat_index out of range")

    beat_meta = None
    segments = ds.info.get("segments") if isinstance(ds.info, dict) else None
    if isinstance(segments, list) and beat_index < len(segments):
        beat_meta = segments[beat_index]

    beat = ds.beats[beat_index]
    beat_stats = {
        "shape": list(beat.shape),
        "mean": float(np.mean(beat)),
        "std": float(np.std(beat)),
        "min": float(np.min(beat)),
        "max": float(np.max(beat)),
        "first10": [float(x) for x in beat[:10]],
    }

    return {
        "upload_id": upload_id,
        "beat_index": beat_index,
        "total_beats": int(len(ds.beats)),
        "signal": beat.round(6).tolist(),
        "true_label": ds.true_labels[beat_index],
        "beat_meta": beat_meta,
        "beat_stats": beat_stats,
        "record_id": ds.info.get("record_id") if isinstance(ds.info, dict) else None,
    }



def make_prediction_context(ds: ParsedDataset, beat_index: int) -> Dict:
    segments = ds.info.get("segments") if isinstance(ds.info, dict) else None
    return {
        "beat_index": int(beat_index),
        "beats": ds.beats,
        "true_labels": ds.true_labels,
        "segments": segments if isinstance(segments, list) else [],
        "format_type": ds.format_type,
    }


@app.post("/api/predict_beat")
def predict_beat(req: PredictBeatRequest):
    ds = DATASETS.get(req.upload_id)
    if ds is None:
        raise HTTPException(status_code=404, detail="Dataset not found")

    if req.backend not in BACKENDS:
        raise HTTPException(status_code=400, detail=f"Unsupported backend: {req.backend}")

    if req.beat_index < 0 or req.beat_index >= len(ds.beats):
        raise HTTPException(status_code=400, detail="beat_index out of range")

    try:
        result = run_prediction(req.backend, ds.beats[req.beat_index], context=make_prediction_context(ds, req.beat_index))
    except Exception as exc:
        raise HTTPException(status_code=400, detail=str(exc))

    true_label = ds.true_labels[req.beat_index]

    result.update({
        "upload_id": req.upload_id,
        "beat_index": req.beat_index,
        "true_label": true_label,
        "correct": (result["predicted_label"] == true_label) if true_label else None,
        "signal": ds.beats[req.beat_index].round(6).tolist(),
    })

    return result


@app.post("/api/predict_beat_multi")
def predict_beat_multi(req: PredictBeatMultiRequest):
    ds = DATASETS.get(req.upload_id)
    if ds is None:
        raise HTTPException(status_code=404, detail="Dataset not found")

    if req.beat_index < 0 or req.beat_index >= len(ds.beats):
        raise HTTPException(status_code=400, detail="beat_index out of range")

    requested = req.backends or list(BACKENDS.keys())
    results = []
    errors = []
    true_label = ds.true_labels[req.beat_index]

    for backend in requested:
        if backend not in BACKENDS:
            errors.append({"backend": backend, "backend_name": BACKENDS.get(backend, backend), "error": f"Unsupported backend: {backend}"})
            continue
        try:
            result = run_prediction(backend, ds.beats[req.beat_index], context=make_prediction_context(ds, req.beat_index))
            results.append({
                "backend": backend,
                "backend_name": BACKENDS.get(backend, backend),
                "beat_index": req.beat_index,
                "true_label": true_label,
                "predicted_label": result.get("predicted_label"),
                "confidence": result.get("confidence"),
                "latency_ms": result.get("latency_ms"),
                "throughput_sps": result.get("throughput_sps"),
                "probabilities": result.get("probabilities", {}),
                "note": result.get("note", ""),
                "correct": (result.get("predicted_label") == true_label) if true_label else None,
            })
        except Exception as exc:
            errors.append({"backend": backend, "backend_name": BACKENDS.get(backend, backend), "error": str(exc)})

    return {
        "upload_id": req.upload_id,
        "filename": ds.filename,
        "format_type": ds.format_type,
        "beat_index": req.beat_index,
        "true_label": true_label,
        "record_context": get_dataset_record_context(ds),
        "results": results,
        "errors": errors,
        "system_status": get_system_status(),
        "signal": ds.beats[req.beat_index].round(6).tolist(),
    }


def _predict_dataset_core(ds: ParsedDataset, backend: str, max_beats: Optional[int] = None, store_result: bool = True) -> Dict:
    if backend not in BACKENDS:
        raise HTTPException(status_code=400, detail=f"Unsupported backend: {backend}")

    total_available = len(ds.beats)
    total_to_run = total_available if max_beats is None else min(total_available, max(1, int(max_beats)))

    rows = []
    correct_count = 0
    labeled_count = 0
    latencies = []
    pred_counts = {label: 0 for label in LABELS}
    true_counts = {label: 0 for label in LABELS}
    per_class_stats = {
        label: {"label": label, "true_total": 0, "correct": 0, "accuracy": None, "pred_total": 0}
        for label in LABELS
    }

    for i in range(total_to_run):
        try:
            result = run_prediction(backend, ds.beats[i], context=make_prediction_context(ds, i))
        except Exception as exc:
            raise HTTPException(status_code=400, detail=str(exc))

        true_label = ds.true_labels[i]
        pred_label = result["predicted_label"]
        correct = None

        if pred_label not in pred_counts:
            pred_counts[pred_label] = 0
        pred_counts[pred_label] += 1
        if pred_label in per_class_stats:
            per_class_stats[pred_label]["pred_total"] += 1

        if true_label is not None:
            labeled_count += 1
            if true_label not in true_counts:
                true_counts[true_label] = 0
            true_counts[true_label] += 1
            if true_label not in per_class_stats:
                per_class_stats[true_label] = {"label": true_label, "true_total": 0, "correct": 0, "accuracy": None, "pred_total": 0}
            per_class_stats[true_label]["true_total"] += 1
            correct = pred_label == true_label
            correct_count += int(correct)
            if correct:
                per_class_stats[true_label]["correct"] += 1

        latencies.append(result["latency_ms"])

        rows.append({
            "beat_index": i,
            "true_label": true_label,
            "predicted_label": pred_label,
            "correct": correct,
            "confidence": result["confidence"],
            "latency_ms": result["latency_ms"],
            "throughput_sps": result["throughput_sps"],
            "note": result["note"],
        })

    for item in per_class_stats.values():
        total = item.get("true_total", 0)
        item["accuracy"] = float(item.get("correct", 0) / total) if total > 0 else None

    per_class_rows = [per_class_stats[label] for label in LABELS if label in per_class_stats]

    avg_latency = float(np.mean(latencies)) if latencies else 0.0
    throughput = float(1000.0 / avg_latency) if avg_latency > 1e-12 else 0.0
    accuracy = float(correct_count / labeled_count) if labeled_count > 0 else None

    result_id = uuid4().hex
    created_at = datetime.now().isoformat(timespec="seconds")

    payload = {
        "result_id": result_id,
        "upload_id": ds.upload_id,
        "filename": ds.filename,
        "created_at": created_at,
        "backend": backend,
        "format_type": ds.format_type,
        "total_available": total_available,
        "total_run": total_to_run,
        "labeled_count": labeled_count,
        "correct_count": correct_count,
        "accuracy": accuracy,
        "avg_latency_ms": avg_latency,
        "throughput_sps": throughput,
        "pred_counts": pred_counts,
        "true_counts": true_counts,
        "per_class_stats": per_class_rows,
        "warnings": ds.warnings,
        "system_status": get_system_status(),
        "record_context": get_dataset_record_context(ds),
        "rows": rows,
        "preview_rows": rows[:300],
    }

    if store_result:
        RESULTS[result_id] = payload
        write_result_files(payload)

    return payload


@app.post("/api/predict_dataset")
def predict_dataset(req: PredictDatasetRequest):
    ds = DATASETS.get(req.upload_id)
    if ds is None:
        raise HTTPException(status_code=404, detail="Dataset not found")
    return _predict_dataset_core(ds, req.backend, req.max_beats, store_result=True)


@app.post("/api/predict_dataset_multi")
def predict_dataset_multi(req: PredictDatasetMultiRequest):
    ds = DATASETS.get(req.upload_id)
    if ds is None:
        raise HTTPException(status_code=404, detail="Dataset not found")

    requested = req.backends or list(BACKENDS.keys())
    results = []
    errors = []

    for backend in requested:
        if backend not in BACKENDS:
            errors.append({"backend": backend, "error": f"Unsupported backend: {backend}"})
            continue
        try:
            payload = _predict_dataset_core(ds, backend, req.max_beats, store_result=False)
            results.append({
                "backend": backend,
                "backend_name": BACKENDS.get(backend, backend),
                "total_run": payload["total_run"],
                "labeled_count": payload["labeled_count"],
                "correct_count": payload["correct_count"],
                "accuracy": payload["accuracy"],
                "avg_latency_ms": payload["avg_latency_ms"],
                "throughput_sps": payload["throughput_sps"],
                "pred_counts": payload["pred_counts"],
                "per_class_stats": payload["per_class_stats"],
                "record_context": payload["record_context"],
                "warnings": payload.get("warnings", []),
            })
        except Exception as exc:
            errors.append({"backend": backend, "backend_name": BACKENDS.get(backend, backend), "error": str(exc)})

    return {
        "upload_id": req.upload_id,
        "filename": ds.filename,
        "format_type": ds.format_type,
        "record_context": get_dataset_record_context(ds),
        "total_available": len(ds.beats),
        "max_beats": req.max_beats,
        "results": results,
        "errors": errors,
        "system_status": get_system_status(),
    }


def write_result_files(payload: Dict) -> None:
    result_id = payload["result_id"]
    csv_path = LOG_DIR / f"ecg_predictions_{result_id}.csv"
    json_path = LOG_DIR / f"ecg_predictions_{result_id}.json"

    with csv_path.open("w", newline="", encoding="utf-8") as f:
        fieldnames = [
            "beat_index", "true_label", "predicted_label", "correct",
            "confidence", "latency_ms", "throughput_sps", "note"
        ]
        writer = csv.DictWriter(f, fieldnames=fieldnames)
        writer.writeheader()
        for row in payload["rows"]:
            writer.writerow(row)

    export_payload = dict(payload)
    export_payload.pop("preview_rows", None)

    with json_path.open("w", encoding="utf-8") as f:
        json.dump(export_payload, f, ensure_ascii=False, indent=2)

    payload["csv_file"] = str(csv_path)
    payload["json_file"] = str(json_path)


@app.get("/api/export/{result_id}/csv")
def export_csv(result_id: str):
    payload = RESULTS.get(result_id)
    if not payload:
        raise HTTPException(status_code=404, detail="Result not found")
    csv_file = payload.get("csv_file")
    if not csv_file or not Path(csv_file).exists():
        raise HTTPException(status_code=404, detail="CSV file not found")
    return FileResponse(csv_file, filename=Path(csv_file).name, media_type="text/csv")


@app.get("/api/export/{result_id}/json")
def export_json(result_id: str):
    payload = RESULTS.get(result_id)
    if not payload:
        raise HTTPException(status_code=404, detail="Result not found")
    json_file = payload.get("json_file")
    if not json_file or not Path(json_file).exists():
        raise HTTPException(status_code=404, detail="JSON file not found")
    return FileResponse(json_file, filename=Path(json_file).name, media_type="application/json")




@app.get('/api/records')
def records(q: Optional[str] = None):
    return {'records': list_records(q)}


@app.post('/api/records/{record_id}/load')
def load_saved_record(record_id: str):
    try:
        payloads = get_record_file_payloads(record_id)
        ds = parse_wfdb_bundle(payloads)
    except Exception as exc:
        raise HTTPException(status_code=400, detail=str(exc))
    DATASETS[ds.upload_id] = ds
    ds.info['loaded_from_record_library'] = record_id
    ds.warnings.append(f'Đã load lại record {record_id} từ record_library.')
    return dataset_to_response(ds)


@app.get('/api/records/{record_id}/download')
def download_saved_record(record_id: str):
    try:
        zip_path = make_record_zip(record_id)
    except Exception as exc:
        raise HTTPException(status_code=404, detail=str(exc))
    return FileResponse(zip_path, filename=zip_path.name, media_type='application/zip')





@app.delete('/api/records/{record_id}')
def delete_saved_record(record_id: str):
    try:
        return delete_record(record_id)
    except Exception as exc:
        raise HTTPException(status_code=404, detail=str(exc))




@app.get('/api/bulk/status')
def api_bulk_status():
    try:
        return bulk_status()
    except Exception as exc:
        raise HTTPException(status_code=400, detail=str(exc))


@app.post('/api/bulk/import_folder')
def api_bulk_import_folder():
    try:
        return import_dataset_folder(clear_existing=True)
    except Exception as exc:
        raise HTTPException(status_code=400, detail=str(exc))


@app.get('/api/bulk/label_records')
def api_bulk_label_records():
    try:
        return label_record_summary()
    except Exception as exc:
        raise HTTPException(status_code=400, detail=str(exc))


@app.get('/api/bulk/search')
def api_bulk_search(record_id: Optional[str] = None, label: Optional[str] = None, limit: int = 100):
    try:
        return {'segments': search_segments(record_id=record_id, label=label, limit=limit)}
    except Exception as exc:
        raise HTTPException(status_code=400, detail=str(exc))



@app.post('/api/bulk/records/{record_id}/load')
def api_load_bulk_record(record_id: str):
    try:
        loaded = load_record_segments(record_id)
    except Exception as exc:
        raise HTTPException(status_code=400, detail=str(exc))

    ds = ParsedDataset(
        upload_id=uuid4().hex,
        filename=f"bulk_record_{record_id}",
        format_type='bulk_csv_record_segments',
        beats=loaded['beats'],
        true_labels=loaded['labels'],
        raw_rows=int(len(loaded['beats'])),
        raw_cols=SIGNAL_LENGTH,
        raw_samples_per_beat=SIGNAL_LENGTH,
        warnings=[f"Đã load record {record_id} với {len(loaded['beats'])} beat từ Bulk Dataset."],
        info={
            'record_id': record_id,
            'segments': loaded['segments'],
            'fs': loaded['fs'],
            'selected_channel': loaded.get('selected_channel'),
        },
    )
    DATASETS[ds.upload_id] = ds
    return dataset_to_response(ds)


@app.post('/api/bulk/segments/{segment_id}/load')
def api_load_bulk_segment(segment_id: int):
    try:
        loaded = load_segment_signal(segment_id)
    except Exception as exc:
        raise HTTPException(status_code=400, detail=str(exc))

    seg = loaded['segment']
    ds = ParsedDataset(
        upload_id=uuid4().hex,
        filename=f"bulk_segment_{segment_id}",
        format_type='bulk_csv_segment',
        beats=np.asarray([loaded['signal']], dtype=np.float32),
        true_labels=[seg.get('label')],
        raw_rows=1,
        raw_cols=int(loaded['raw_length']),
        raw_samples_per_beat=int(loaded['raw_length']),
        warnings=[f"Đã load segment {segment_id} từ bulk dataset: record {seg.get('record_id')}, {seg.get('start')}:{seg.get('end')}"],
        info={'segment': seg, 'selected_channel': loaded.get('selected_channel')},
    )
    DATASETS[ds.upload_id] = ds
    return dataset_to_response(ds)



def _read_device_tree_model() -> Optional[str]:
    for raw_path in ["/proc/device-tree/model", "/sys/firmware/devicetree/base/model"]:
        path = Path(raw_path)
        if path.exists():
            try:
                return path.read_bytes().replace(b"\x00", b"").decode(errors="ignore").strip()
            except Exception:
                pass
    return None


def _check_fpga_environment() -> Dict:
    system_status = get_system_status()
    fpga_hls = system_status.get('fpga_hls', {})
    fpga_rtl = system_status.get('fpga_rtl', {})

    pynq_import_ok = False
    pynq_error = ''
    pynq_version = None
    try:
        import pynq  # type: ignore
        pynq_import_ok = True
        pynq_version = getattr(pynq, '__version__', None)
    except Exception as exc:
        pynq_error = str(exc)

    device_model = _read_device_tree_model()
    device_nodes = [p for p in ['/dev/xdevcfg', '/dev/fpga0', '/dev/uio0', '/dev/uio1', '/dev/mem'] if Path(p).exists()]
    model_hint = (device_model or '').lower()
    zynq_model_detected = any(key in model_hint for key in ['pynq', 'zynq', 'xilinx', 'zedboard', 'xc7z'])

    overlay_hls_ready = bool(fpga_hls.get('overlay_files_received'))
    overlay_rtl_ready = bool(fpga_rtl.get('overlay_files_received'))
    runtime_hls_loaded = bool(fpga_hls.get('runtime_loaded'))
    runtime_rtl_loaded = bool(fpga_rtl.get('runtime_loaded'))
    remote_hls_ready = bool(fpga_hls.get('remote_available'))
    remote_hls_url = fpga_hls.get('remote_url') or ''

    environment_detected = bool(pynq_import_ok and (zynq_model_detected or device_nodes or runtime_hls_loaded or runtime_rtl_loaded))
    overlay_ready = bool(overlay_hls_ready or overlay_rtl_ready)
    runtime_ready = bool(runtime_hls_loaded or runtime_rtl_loaded)

    if remote_hls_ready and not environment_detected:
        state = 'remote_ready'
        message = f'Đã kết nối được PYNQ HLS API từ Windows: {remote_hls_url}'
    elif runtime_ready:
        state = 'ready'
        message = 'Đã phát hiện PYNQ runtime hoặc PYNQ remote API và FPGA HLS đã sẵn sàng.'
    elif environment_detected and overlay_ready:
        state = 'overlay_received'
        message = 'Đã phát hiện môi trường PYNQ/Zynq và đã có file overlay, nhưng overlay chưa load thành công.'
    elif environment_detected:
        state = 'board_detected'
        message = 'Đã phát hiện môi trường PYNQ/Zynq, nhưng chưa có đủ overlay .bit/.hwh.'
    elif pynq_import_ok:
        state = 'pynq_imported_no_board_hint'
        message = 'Import được thư viện pynq nhưng chưa thấy dấu hiệu device-tree/Zynq rõ ràng.'
    else:
        state = 'not_detected'
        message = 'Chưa phát hiện môi trường PYNQ. Nếu dashboard đang chạy trên Windows PC thì không thể kiểm tra FPGA cắm trực tiếp; hãy chạy dashboard trên board PYNQ-Z2 hoặc SSH vào board.'

    return {
        'state': state,
        'message': message,
        'python_platform': platform.platform(),
        'pynq_import_ok': pynq_import_ok,
        'pynq_version': pynq_version,
        'pynq_error': pynq_error,
        'device_model': device_model,
        'device_nodes': device_nodes,
        'environment_detected': environment_detected,
        'overlay_ready': overlay_ready,
        'runtime_ready': runtime_ready,
        'hls_overlay_files': overlay_hls_ready,
        'rtl_overlay_files': overlay_rtl_ready,
        'hls_runtime_loaded': runtime_hls_loaded,
        'rtl_runtime_loaded': runtime_rtl_loaded,
        'remote_hls_ready': remote_hls_ready,
        'remote_hls_url': remote_hls_url,
    }


@app.get('/api/fpga_probe')
def fpga_probe():
    return _check_fpga_environment()

@app.get('/api/model_files')
def model_files():
    return get_model_file_status()


@app.post('/api/import_fpga_export')
def import_export_files():
    try:
        result = import_fpga_export()
        result['runtime_status'] = reload_runtime_models()
        return result
    except Exception as exc:
        raise HTTPException(status_code=400, detail=str(exc))


@app.post('/api/reload_models')
def api_reload_models():
    try:
        return {'system_status': reload_runtime_models()}
    except Exception as exc:
        raise HTTPException(status_code=400, detail=str(exc))




@app.post('/api/upload_verilog_registers')
async def upload_verilog_registers(files: List[UploadFile] = File(...)):
    target_dir = ROOT / 'models' / 'fpga' / 'rtl' / 'rtl'
    target_dir.mkdir(parents=True, exist_ok=True)
    saved = []
    for f in files:
        name = f.filename or 'uploaded.v'
        suffix = Path(name).suffix.lower()
        if suffix not in {'.v', '.sv', '.vh'}:
            continue
        raw = await f.read()
        if not raw:
            continue
        safe_name = Path(name).name
        path = target_dir / safe_name
        path.write_bytes(raw)
        saved.append({'filename': safe_name, 'path': str(path.relative_to(ROOT)), 'size_bytes': len(raw)})
    return {'saved': saved, 'count': len(saved), 'target_dir': str(target_dir.relative_to(ROOT))}


app.mount("/static", StaticFiles(directory=STATIC_DIR), name="static")
