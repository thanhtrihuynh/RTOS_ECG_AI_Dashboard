from __future__ import annotations

import json
import re
import zipfile
from datetime import datetime
from pathlib import Path
from typing import Any, Dict, List, Tuple

ROOT = Path(__file__).resolve().parents[1]
LIB_DIR = ROOT / 'record_library'
INDEX_PATH = LIB_DIR / 'metadata' / 'records_index.json'
SUPPORTED_EXTS = {'.hea': 'hea', '.dat': 'dat', '.atr': 'atr', '.xws': 'xws'}


def ensure_record_library() -> None:
    for sub in ['hea', 'dat', 'atr', 'xws', 'csv', 'exports', 'metadata']:
        (LIB_DIR / sub).mkdir(parents=True, exist_ok=True)
    if not INDEX_PATH.exists():
        save_index({})


def sanitize_record_id(record_id: str) -> str:
    record_id = record_id.strip()
    record_id = re.sub(r'[^A-Za-z0-9_-]', '_', record_id)
    return record_id or 'unknown_record'


def load_index() -> Dict[str, Any]:
    ensure_record_library()
    try:
        return json.loads(INDEX_PATH.read_text(encoding='utf-8'))
    except Exception:
        return {}


def save_index(index: Dict[str, Any]) -> None:
    INDEX_PATH.parent.mkdir(parents=True, exist_ok=True)
    INDEX_PATH.write_text(json.dumps(index, ensure_ascii=False, indent=2), encoding='utf-8')


def infer_record_id(file_payloads: List[Tuple[str, bytes]]) -> str:
    priority = ['.hea', '.dat', '.atr', '.xws']
    by_ext = {Path(name).suffix.lower(): Path(name).stem for name, _ in file_payloads}
    for ext in priority:
        if ext in by_ext:
            return sanitize_record_id(by_ext[ext])
    return sanitize_record_id(Path(file_payloads[0][0]).stem)


def save_wfdb_record(file_payloads: List[Tuple[str, bytes]]) -> Dict[str, Any]:
    ensure_record_library()
    record_id = infer_record_id(file_payloads)
    now = datetime.now().isoformat(timespec='seconds')
    index = load_index()
    old_meta = index.get(record_id, {})
    created_at = old_meta.get('created_at', now)
    files_meta: Dict[str, Any] = {}
    saved_exts = []

    for filename, raw in file_payloads:
        suffix = Path(filename).suffix.lower()
        if suffix not in SUPPORTED_EXTS:
            continue
        ext_name = SUPPORTED_EXTS[suffix]
        stored_name = f'{record_id}{suffix}'
        dest = LIB_DIR / ext_name / stored_name
        dest.parent.mkdir(parents=True, exist_ok=True)
        dest.write_bytes(raw)
        saved_exts.append(ext_name)
        files_meta[ext_name] = {
            'original_filename': filename,
            'stored_filename': stored_name,
            'relative_path': str(dest.relative_to(ROOT)).replace('\\', '/'),
            'size_bytes': len(raw),
        }

    if not files_meta:
        raise ValueError('Không có file WFDB hợp lệ để lưu.')

    meta = {
        'record_id': record_id,
        'created_at': created_at,
        'updated_at': now,
        'source': 'wfdb',
        'files': {**old_meta.get('files', {}), **files_meta},
        'file_types': sorted(set(list(old_meta.get('files', {}).keys()) + saved_exts)),
    }
    index[record_id] = meta
    save_index(index)
    return meta


def list_records(q: str | None = None) -> List[Dict[str, Any]]:
    index = load_index()
    records = list(index.values())
    if q:
        q_lower = q.lower().strip()
        records = [r for r in records if q_lower in r.get('record_id', '').lower()]
    records.sort(key=lambda r: r.get('updated_at', ''), reverse=True)
    return records


def get_record_meta(record_id: str) -> Dict[str, Any]:
    record_id = sanitize_record_id(record_id)
    index = load_index()
    if record_id not in index:
        raise FileNotFoundError(f'Không tìm thấy record {record_id}.')
    return index[record_id]


def get_record_file_payloads(record_id: str) -> List[Tuple[str, bytes]]:
    meta = get_record_meta(record_id)
    payloads: List[Tuple[str, bytes]] = []
    for ext_name in ['hea', 'dat', 'atr', 'xws']:
        file_info = meta.get('files', {}).get(ext_name)
        if not file_info:
            continue
        path = ROOT / file_info['relative_path']
        if path.exists():
            payloads.append((file_info['stored_filename'], path.read_bytes()))
    if not payloads:
        raise FileNotFoundError(f'Record {record_id} không có file hợp lệ trong thư viện.')
    return payloads


def make_record_zip(record_id: str) -> Path:
    meta = get_record_meta(record_id)
    record_id = meta['record_id']
    export_dir = LIB_DIR / 'exports'
    export_dir.mkdir(parents=True, exist_ok=True)
    zip_path = export_dir / f'{record_id}_wfdb_record.zip'
    with zipfile.ZipFile(zip_path, 'w', zipfile.ZIP_DEFLATED) as z:
        for ext_name, file_info in meta.get('files', {}).items():
            path = ROOT / file_info['relative_path']
            if path.exists():
                z.write(path, arcname=file_info['stored_filename'])
        z.writestr(f'{record_id}_metadata.json', json.dumps(meta, ensure_ascii=False, indent=2))
    return zip_path



def delete_record(record_id: str) -> Dict[str, Any]:
    meta = get_record_meta(record_id)
    index = load_index()
    record_id = meta['record_id']

    deleted_files = []
    for ext_name, file_info in meta.get('files', {}).items():
        path = ROOT / file_info['relative_path']
        if path.exists():
            path.unlink()
            deleted_files.append(str(path.relative_to(ROOT)).replace('\\', '/'))

    index.pop(record_id, None)
    save_index(index)

    return {
        'record_id': record_id,
        'deleted_files': deleted_files,
        'deleted': True,
    }
