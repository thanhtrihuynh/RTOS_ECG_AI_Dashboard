from __future__ import annotations

import csv
import re
import sqlite3
from datetime import datetime
from pathlib import Path
from typing import Any, Dict, List, Optional

import numpy as np

from .config import SIGNAL_LENGTH
from .ecg_processing import decode_format_212, normalize_signal, parse_hea
from .record_store import ROOT, get_record_file_payloads, save_wfdb_record

DATASET_IMPORT_DIR = ROOT / 'dataset_import'
METADATA_DIR = DATASET_IMPORT_DIR / 'metadata'
WFDB_RECORDS_DIR = DATASET_IMPORT_DIR / 'wfdb_records'
DB_PATH = ROOT / 'record_library' / 'metadata' / 'dataset_index.sqlite'


def ensure_bulk_dirs() -> None:
    METADATA_DIR.mkdir(parents=True, exist_ok=True)
    WFDB_RECORDS_DIR.mkdir(parents=True, exist_ok=True)
    DB_PATH.parent.mkdir(parents=True, exist_ok=True)
    init_db()


def init_db() -> None:
    conn = sqlite3.connect(DB_PATH)
    cur = conn.cursor()
    cur.execute('''
        CREATE TABLE IF NOT EXISTS segments (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            record_id TEXT NOT NULL,
            channel TEXT,
            start INTEGER NOT NULL,
            end INTEGER NOT NULL,
            label TEXT,
            record_path TEXT,
            created_at TEXT
        )
    ''')
    cur.execute('''
        CREATE TABLE IF NOT EXISTS records (
            record_id TEXT PRIMARY KEY,
            has_hea INTEGER DEFAULT 0,
            has_dat INTEGER DEFAULT 0,
            has_atr INTEGER DEFAULT 0,
            has_xws INTEGER DEFAULT 0,
            updated_at TEXT
        )
    ''')
    conn.commit()
    conn.close()


def record_id_from_path(record_path: str) -> str:
    s = str(record_path).strip().replace('\\', '/')
    last = s.split('/')[-1]
    if '.' in last:
        last = last.rsplit('.', 1)[0]
    return re.sub(r'[^A-Za-z0-9_-]', '_', last)


def find_metadata_csv() -> Path:
    ensure_bulk_dirs()
    candidates = list(METADATA_DIR.glob('*.csv'))
    if not candidates:
        raise FileNotFoundError(
            f'Không tìm thấy file metadata CSV trong {METADATA_DIR.relative_to(ROOT)}. '
            'Hãy đặt file .csv có cột record_path, channel, start, end, labels vào thư mục này.'
        )
    for p in candidates:
        if p.name.lower() in {'dataset_index.csv', 'metadata.csv', 'segments.csv'}:
            return p
    return candidates[0]


def scan_wfdb_files() -> Dict[str, Dict[str, Path]]:
    ensure_bulk_dirs()
    file_index: Dict[str, Dict[str, Path]] = {}
    for p in WFDB_RECORDS_DIR.rglob('*'):
        if not p.is_file():
            continue
        suffix = p.suffix.lower()
        if suffix not in {'.hea', '.dat', '.atr', '.xws'}:
            continue
        record_id = p.stem
        file_index.setdefault(record_id, {})[suffix] = p
    return file_index


def save_record_from_paths(record_id: str, files: Dict[str, Path]) -> Optional[Dict[str, Any]]:
    if '.hea' not in files or '.dat' not in files:
        return None
    payloads = []
    for ext in ['.hea', '.dat', '.atr', '.xws']:
        p = files.get(ext)
        if p and p.exists():
            payloads.append((p.name, p.read_bytes()))
    return save_wfdb_record(payloads)


def import_dataset_folder(clear_existing: bool = True) -> Dict[str, Any]:
    ensure_bulk_dirs()
    csv_path = find_metadata_csv()
    file_index = scan_wfdb_files()
    now = datetime.now().isoformat(timespec='seconds')

    conn = sqlite3.connect(DB_PATH)
    cur = conn.cursor()
    if clear_existing:
        cur.execute('DELETE FROM segments')
        cur.execute('DELETE FROM records')

    total_rows = 0
    inserted_segments = 0
    missing_records = set()
    saved_records = set()
    labels_count: Dict[str, int] = {}

    with csv_path.open('r', encoding='utf-8-sig', newline='') as f:
        reader = csv.DictReader(f)
        required = {'record_path', 'channel', 'start', 'end', 'labels'}
        lower_map = {name.lower().strip(): name for name in (reader.fieldnames or [])}
        if not required.issubset(set(lower_map.keys())):
            raise ValueError(f'CSV cần có các cột: {sorted(required)}. Cột hiện có: {reader.fieldnames}')

        for row in reader:
            total_rows += 1
            record_path = row[lower_map['record_path']]
            channel = row[lower_map['channel']]
            start = int(float(row[lower_map['start']]))
            end = int(float(row[lower_map['end']]))
            label = str(row[lower_map['labels']]).strip()
            record_id = record_id_from_path(record_path)

            files = file_index.get(record_id)
            if files is None or '.hea' not in files or '.dat' not in files:
                missing_records.add(record_id)
                continue

            if record_id not in saved_records:
                meta = save_record_from_paths(record_id, files)
                if meta is not None:
                    saved_records.add(record_id)
                    cur.execute(
                        'INSERT OR REPLACE INTO records(record_id, has_hea, has_dat, has_atr, has_xws, updated_at) VALUES (?, ?, ?, ?, ?, ?)',
                        (record_id, int('.hea' in files), int('.dat' in files), int('.atr' in files), int('.xws' in files), now)
                    )

            cur.execute(
                'INSERT INTO segments(record_id, channel, start, end, label, record_path, created_at) VALUES (?, ?, ?, ?, ?, ?, ?)',
                (record_id, channel, start, end, label, record_path, now)
            )
            inserted_segments += 1
            labels_count[label] = labels_count.get(label, 0) + 1

    conn.commit()
    conn.close()
    return {
        'metadata_csv': str(csv_path.relative_to(ROOT)),
        'wfdb_records_dir': str(WFDB_RECORDS_DIR.relative_to(ROOT)),
        'total_csv_rows': total_rows,
        'inserted_segments': inserted_segments,
        'saved_records': len(saved_records),
        'missing_records_count': len(missing_records),
        'missing_records_preview': sorted(list(missing_records))[:30],
        'labels_count': labels_count,
        'db_path': str(DB_PATH.relative_to(ROOT)),
    }


def label_record_summary() -> Dict[str, Any]:
    """Return which record IDs contain each target heartbeat label."""
    ensure_bulk_dirs()
    target_labels = ['N', 'L', 'R', 'V', 'A']
    summary: Dict[str, Any] = {
        label: {'label': label, 'record_count': 0, 'beat_count': 0, 'records': [], 'records_text': ''}
        for label in target_labels
    }

    conn = sqlite3.connect(DB_PATH)
    cur = conn.cursor()
    total_segments = int(cur.execute('SELECT COUNT(*) FROM segments').fetchone()[0])
    total_records = int(cur.execute('SELECT COUNT(DISTINCT record_id) FROM segments').fetchone()[0])
    rows = cur.execute(
        """
        SELECT label, record_id, COUNT(*) AS beat_count
        FROM segments
        WHERE label IN ('N', 'L', 'R', 'V', 'A')
        GROUP BY label, record_id
        ORDER BY label ASC, record_id ASC
        """
    ).fetchall()
    conn.close()

    for label, record_id, beat_count in rows:
        label = str(label)
        if label not in summary:
            continue
        item = {'record_id': str(record_id), 'beat_count': int(beat_count)}
        summary[label]['records'].append(item)
        summary[label]['beat_count'] += int(beat_count)

    for label in target_labels:
        records = summary[label]['records']
        summary[label]['record_count'] = len(records)
        summary[label]['records_text'] = ', '.join([r['record_id'] for r in records])

    return {
        'source': 'bulk_dataset_index',
        'db_path': str(DB_PATH.relative_to(ROOT)),
        'labels': target_labels,
        'segment_count': total_segments,
        'record_count': total_records,
        'summary': summary,
    }


def bulk_status() -> Dict[str, Any]:
    ensure_bulk_dirs()
    conn = sqlite3.connect(DB_PATH)
    cur = conn.cursor()
    cur.execute('SELECT COUNT(*) FROM records')
    record_count = cur.fetchone()[0]
    cur.execute('SELECT COUNT(*) FROM segments')
    segment_count = cur.fetchone()[0]
    cur.execute('SELECT label, COUNT(*) FROM segments GROUP BY label')
    labels_count = dict(cur.fetchall())
    conn.close()
    csv_files = [str(p.relative_to(ROOT)) for p in METADATA_DIR.glob('*.csv')]
    wfdb_file_count = len([p for p in WFDB_RECORDS_DIR.rglob('*') if p.is_file() and p.suffix.lower() in {'.hea', '.dat', '.atr', '.xws'}])
    return {
        'metadata_dir': str(METADATA_DIR.relative_to(ROOT)),
        'wfdb_records_dir': str(WFDB_RECORDS_DIR.relative_to(ROOT)),
        'csv_files': csv_files,
        'wfdb_file_count': wfdb_file_count,
        'record_count': record_count,
        'segment_count': segment_count,
        'labels_count': labels_count,
        'db_path': str(DB_PATH.relative_to(ROOT)),
    }


def search_segments(record_id: Optional[str] = None, label: Optional[str] = None, limit: int = 100) -> List[Dict[str, Any]]:
    ensure_bulk_dirs()
    limit = max(1, min(int(limit), 1000))
    query = 'SELECT id, record_id, channel, start, end, label, record_path FROM segments WHERE 1=1'
    params: List[Any] = []
    if record_id:
        query += ' AND record_id LIKE ?'
        params.append(f'%{record_id}%')
    if label:
        query += ' AND label = ?'
        params.append(label)
    query += ' ORDER BY record_id ASC, start ASC LIMIT ?'
    params.append(limit)
    conn = sqlite3.connect(DB_PATH)
    cur = conn.cursor()
    rows = cur.execute(query, params).fetchall()
    conn.close()
    return [
        {'segment_id': r[0], 'record_id': r[1], 'channel': r[2], 'start': r[3], 'end': r[4], 'label': r[5], 'record_path': r[6]}
        for r in rows
    ]


def get_segment(segment_id: int) -> Dict[str, Any]:
    ensure_bulk_dirs()
    conn = sqlite3.connect(DB_PATH)
    cur = conn.cursor()
    row = cur.execute('SELECT id, record_id, channel, start, end, label, record_path FROM segments WHERE id = ?', (int(segment_id),)).fetchone()
    conn.close()
    if row is None:
        raise FileNotFoundError(f'Không tìm thấy segment_id={segment_id}.')
    return {'segment_id': row[0], 'record_id': row[1], 'channel': row[2], 'start': row[3], 'end': row[4], 'label': row[5], 'record_path': row[6]}


def normalize_channel_name(name: str) -> str:
    return str(name or '').upper().replace(' ', '').replace('-', '').replace('_', '')


def _select_channel(header: Dict[str, Any], channel: str) -> int:
    target = normalize_channel_name(channel)
    descriptions = [str(sig.get('description', '')).strip() for sig in header['signals']]
    normalized = [normalize_channel_name(x) for x in descriptions]

    if target and target in normalized:
        return normalized.index(target)

    for fallback in ['MLII', 'ML2']:
        if fallback in normalized:
            return normalized.index(fallback)

    return 0


def load_segment_signal(segment_id: int) -> Dict[str, Any]:
    seg = get_segment(segment_id)
    payloads = get_record_file_payloads(seg['record_id'])
    files = {Path(name).suffix.lower(): raw for name, raw in payloads}
    if '.hea' not in files or '.dat' not in files:
        raise FileNotFoundError(f"Record {seg['record_id']} thiếu .hea hoặc .dat.")
    header = parse_hea(files['.hea'])
    raw_adc = decode_format_212(files['.dat'], nsig=header['nsig'], nsamp=header['nsamp'])
    ch = _select_channel(header, seg['channel'])
    ch = min(ch, raw_adc.shape[1] - 1)
    sig_meta = header['signals'][ch]
    gain = float(sig_meta.get('gain', 200.0))
    adc_zero = float(sig_meta.get('adc_zero', 0.0))
    signal = (raw_adc[:, ch] - adc_zero) / gain
    start = max(0, int(seg['start']))
    end = min(len(signal) - 1, int(seg['end']))
    if end <= start:
        raise ValueError(f'Segment start/end không hợp lệ: {start}, {end}')
    beat = signal[start:end + 1]
    normalized = normalize_signal(beat, SIGNAL_LENGTH)
    
    fs = int(header.get('fs', 360))
    enriched = add_time_to_segment(seg, fs)
    enriched['selected_channel'] = sig_meta.get('description', f'ch{ch}')
    enriched['selected_channel_index'] = int(ch)
    enriched['available_channels'] = [sig.get('description', f'ch{i}') for i, sig in enumerate(header['signals'])]
    enriched['raw_length'] = int(len(beat))
    return {'segment': enriched, 'signal': normalized.astype(np.float32), 'raw_length': int(len(beat)), 'selected_channel': sig_meta.get('description', f'ch{ch}')}



def format_time(seconds: float) -> str:
    seconds = float(seconds)
    minutes = int(seconds // 60)
    sec = seconds - minutes * 60
    return f"{minutes:02d}:{sec:06.3f}"


def _read_record_signal(record_id: str, channel: str) -> Dict[str, Any]:
    payloads = get_record_file_payloads(record_id)
    files = {Path(name).suffix.lower(): raw for name, raw in payloads}
    if '.hea' not in files or '.dat' not in files:
        raise FileNotFoundError(f"Record {record_id} thiếu .hea hoặc .dat.")

    header = parse_hea(files['.hea'])
    raw_adc = decode_format_212(files['.dat'], nsig=header['nsig'], nsamp=header['nsamp'])
    ch = _select_channel(header, channel)
    ch = min(ch, raw_adc.shape[1] - 1)
    sig_meta = header['signals'][ch]
    gain = float(sig_meta.get('gain', 200.0))
    adc_zero = float(sig_meta.get('adc_zero', 0.0))
    signal = (raw_adc[:, ch] - adc_zero) / gain
    return {
        'signal': signal,
        'header': header,
        'fs': int(header.get('fs', 360)),
        'selected_channel': sig_meta.get('description', f'ch{ch}'),
        'selected_channel_index': int(ch),
        'available_channels': [sig.get('description', f'ch{i}') for i, sig in enumerate(header['signals'])],
    }


def add_time_to_segment(seg: Dict[str, Any], fs: int) -> Dict[str, Any]:
    out = dict(seg)
    start_sec = float(out['start']) / float(fs)
    end_sec = float(out['end']) / float(fs)
    out['fs'] = int(fs)
    out['start_time_sec'] = start_sec
    out['end_time_sec'] = end_sec
    out['start_time'] = format_time(start_sec)
    out['end_time'] = format_time(end_sec)
    return out


def get_record_segments(record_id: str, limit: int = 10000) -> List[Dict[str, Any]]:
    ensure_bulk_dirs()
    conn = sqlite3.connect(DB_PATH)
    cur = conn.cursor()
    total_segments = int(cur.execute('SELECT COUNT(*) FROM segments').fetchone()[0])
    total_records = int(cur.execute('SELECT COUNT(DISTINCT record_id) FROM segments').fetchone()[0])
    rows = cur.execute(
        'SELECT id, record_id, channel, start, end, label, record_path FROM segments WHERE record_id = ? ORDER BY start ASC LIMIT ?',
        (str(record_id), int(limit))
    ).fetchall()
    conn.close()
    return [
        {
            'segment_id': r[0], 'record_id': r[1], 'channel': r[2], 'start': r[3],
            'end': r[4], 'label': r[5], 'record_path': r[6]
        }
        for r in rows
    ]


def load_record_segments(record_id: str, limit: int = 10000) -> Dict[str, Any]:
    segments = get_record_segments(record_id, limit=limit)
    if not segments:
        raise FileNotFoundError(f'Không tìm thấy segment nào cho record {record_id}.')

    # Đa số CSV dùng cùng channel cho một record. Lấy channel từ segment đầu.
    rec = _read_record_signal(record_id, segments[0].get('channel'))
    signal = rec['signal']
    fs = rec['fs']

    beats = []
    labels = []
    enriched_segments = []
    for seg in segments:
        start = max(0, int(seg['start']))
        end = min(len(signal) - 1, int(seg['end']))
        if end <= start:
            continue
        beat = signal[start:end + 1]
        beats.append(normalize_signal(beat, SIGNAL_LENGTH))
        labels.append(seg.get('label'))
        enriched = add_time_to_segment(seg, fs)
        enriched['selected_channel'] = rec.get('selected_channel')
        enriched['selected_channel_index'] = rec.get('selected_channel_index')
        enriched['available_channels'] = rec.get('available_channels')
        enriched['raw_length'] = int(len(beat))
        enriched_segments.append(enriched)

    if not beats:
        raise ValueError(f'Record {record_id} không có beat hợp lệ sau khi cắt start/end.')

    return {
        'record_id': record_id,
        'beats': np.asarray(beats, dtype=np.float32),
        'labels': labels,
        'segments': enriched_segments,
        'fs': fs,
        'selected_channel': rec.get('selected_channel'),
    }
