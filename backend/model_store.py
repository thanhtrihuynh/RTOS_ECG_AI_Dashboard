from __future__ import annotations

import shutil
import zipfile
from pathlib import Path
from typing import Dict, List, Any

ROOT = Path(__file__).resolve().parents[1]
EXPORT_DIR = ROOT / 'fpga_export'
PACKAGE_DIR = ROOT / 'model_package_input'
INPUT_DIRS = [PACKAGE_DIR, EXPORT_DIR]
MODELS_DIR = ROOT / 'models'
COMBINED_ROOT = MODELS_DIR / 'combined_5class_pair_overlap'

FILE_MAP = {
    # CPU Float32 combined pipeline
    'main_5class_model_CPU_FLOAT.keras': 'combined_5class_pair_overlap/cpu_float32/keras/main_5class_model_CPU_FLOAT.keras',
    'pair_overlap_NA_refiner_CPU_FLOAT.keras': 'combined_5class_pair_overlap/cpu_float32/keras/pair_overlap_NA_refiner_CPU_FLOAT.keras',
    'combined_inference_config.json': 'combined_5class_pair_overlap/cpu_float32/config/combined_inference_config.json',
    'pair_overlap_feature_norm_float32.npz': [
        'combined_5class_pair_overlap/cpu_float32/features/pair_overlap_feature_norm_float32.npz',
        'combined_5class_pair_overlap/cpu_q4_12/features/pair_overlap_feature_norm_float32.npz',
    ],
    'combined_export_summary.txt': 'combined_5class_pair_overlap/cpu_float32/docs/combined_export_summary.txt',

    # CPU Q4.12 package
    'main_5class_q4_12_weights.npz': [
        'combined_5class_pair_overlap/cpu_q4_12/weights/main_5class_q4_12_weights.npz',
        'combined_5class_pair_overlap/vitis_hls_q4_12/weights_npz/main_5class_q4_12_weights.npz',
    ],
    'pair_overlap_refiner_q4_12_weights.npz': [
        'combined_5class_pair_overlap/cpu_q4_12/weights/pair_overlap_refiner_q4_12_weights.npz',
        'combined_5class_pair_overlap/vitis_hls_q4_12/weights_npz/pair_overlap_refiner_q4_12_weights.npz',
    ],
    'combined_cpu_q4_12_config.json': 'combined_5class_pair_overlap/cpu_q4_12/config/combined_cpu_q4_12_config.json',
    'combined_cpu_q4_12_sample_io.npz': 'combined_5class_pair_overlap/cpu_q4_12/test_vectors/combined_cpu_q4_12_sample_io.npz',
    'combined_cpu_q4_12_summary.txt': 'combined_5class_pair_overlap/cpu_q4_12/docs/combined_cpu_q4_12_summary.txt',

    # Vitis HLS Q4.12 export
    'combined_q4_12_config.h': [
        'combined_5class_pair_overlap/vitis_hls_q4_12/headers/combined_q4_12_config.h',
        'fpga/hls/hls_export/combined_q4_12_config.h',
    ],
    'main_5class_q4_12_weights.h': [
        'combined_5class_pair_overlap/vitis_hls_q4_12/headers/main_5class_q4_12_weights.h',
        'fpga/hls/hls_export/main_5class_q4_12_weights.h',
    ],
    'pair_overlap_refiner_q4_12_weights.h': [
        'combined_5class_pair_overlap/vitis_hls_q4_12/headers/pair_overlap_refiner_q4_12_weights.h',
        'fpga/hls/hls_export/pair_overlap_refiner_q4_12_weights.h',
    ],
    'combined_q4_12_metadata.json': 'combined_5class_pair_overlap/vitis_hls_q4_12/config/combined_q4_12_metadata.json',
    'combined_q4_12_sample_io.npz': 'combined_5class_pair_overlap/vitis_hls_q4_12/test_vectors/combined_q4_12_sample_io.npz',
    'README_Q4_12_Vitis_HLS.txt': 'combined_5class_pair_overlap/vitis_hls_q4_12/docs/README_Q4_12_Vitis_HLS.txt',
}

REQUIRED_GROUPS = {
    'combined_cpu_float32': [
        'models/combined_5class_pair_overlap/cpu_float32/keras/main_5class_model_CPU_FLOAT.keras',
        'models/combined_5class_pair_overlap/cpu_float32/keras/pair_overlap_NA_refiner_CPU_FLOAT.keras',
        'models/combined_5class_pair_overlap/cpu_float32/config/combined_inference_config.json',
    ],
    'combined_cpu_q4_12': [
        'models/combined_5class_pair_overlap/cpu_q4_12/weights/main_5class_q4_12_weights.npz',
        'models/combined_5class_pair_overlap/cpu_q4_12/weights/pair_overlap_refiner_q4_12_weights.npz',
        'models/combined_5class_pair_overlap/cpu_q4_12/config/combined_cpu_q4_12_config.json',
    ],
    'combined_vitis_hls_q4_12': [
        'models/combined_5class_pair_overlap/vitis_hls_q4_12/headers/combined_q4_12_config.h',
        'models/combined_5class_pair_overlap/vitis_hls_q4_12/headers/main_5class_q4_12_weights.h',
        'models/combined_5class_pair_overlap/vitis_hls_q4_12/headers/pair_overlap_refiner_q4_12_weights.h',
    ],
}


def ensure_dirs() -> None:
    EXPORT_DIR.mkdir(parents=True, exist_ok=True)
    PACKAGE_DIR.mkdir(parents=True, exist_ok=True)


def _copy_one(src: Path, target_rel: str, copied: List[Dict[str, Any]]) -> None:
    dst = MODELS_DIR / target_rel
    dst.parent.mkdir(parents=True, exist_ok=True)
    shutil.copy2(src, dst)
    copied.append({'source': str(src.relative_to(ROOT)), 'target': str(dst.relative_to(ROOT)), 'size_bytes': dst.stat().st_size})


def _extract_packages_to_input() -> List[str]:
    extracted = []
    for d in INPUT_DIRS:
        if not d.exists():
            continue
        for zp in d.glob('*.zip'):
            try:
                with zipfile.ZipFile(zp) as z:
                    for member in z.namelist():
                        name = Path(member).name
                        if not name:
                            continue
                        if name in FILE_MAP:
                            target = d / name
                            target.write_bytes(z.read(member))
                            extracted.append(f'{zp.name}:{name}')
            except Exception:
                continue
    return extracted


def import_fpga_export() -> Dict[str, Any]:
    ensure_dirs()
    extracted = _extract_packages_to_input()
    copied = []
    missing_from_export = []
    for filename, target_rel in FILE_MAP.items():
        src = next((d / filename for d in INPUT_DIRS if (d / filename).exists() and (d / filename).is_file()), EXPORT_DIR / filename)
        if src.exists() and src.is_file():
            targets = target_rel if isinstance(target_rel, list) else [target_rel]
            for t in targets:
                _copy_one(src, t, copied)
        else:
            missing_from_export.append(filename)
    return {'export_dir': str(EXPORT_DIR), 'package_dir': str(PACKAGE_DIR), 'extracted_from_zip': extracted, 'copied': copied, 'missing_from_export': missing_from_export, 'status': get_model_file_status()}


def file_info(path: Path) -> Dict[str, Any]:
    return {'path': str(path.relative_to(ROOT)), 'exists': path.exists(), 'size_bytes': path.stat().st_size if path.exists() else 0}


def get_model_file_status() -> Dict[str, Any]:
    groups: Dict[str, List[Dict[str, Any]]] = {}
    for group, rel_paths in REQUIRED_GROUPS.items():
        groups[group] = [file_info(ROOT / rel) for rel in rel_paths]
    received = {group: all(item['exists'] for item in items) for group, items in groups.items()}
    return {
        'export_dir': str(EXPORT_DIR.relative_to(ROOT)),
        'package_dir': str(PACKAGE_DIR.relative_to(ROOT)),
        'input_dirs': [str(d.relative_to(ROOT)) for d in INPUT_DIRS],
        'groups': groups,
        'received': received,
        'notes': {},
    }
