from __future__ import annotations

import json
import os
import time
import urllib.error
import urllib.request
from pathlib import Path
from typing import Dict, Tuple, List, Optional, Any

import numpy as np

from .config import LABELS, Q_MAX, Q_MIN, Q_SCALE, SIGNAL_LENGTH
from .ecg_processing import normalize_signal

ROOT = Path(__file__).resolve().parents[1]
MODEL_DIR = ROOT / 'models'
COMBINED_ROOT = MODEL_DIR / 'combined_5class_pair_overlap'
COMBINED_FLOAT32_DIR = COMBINED_ROOT / 'cpu_float32'
COMBINED_Q412_DIR = COMBINED_ROOT / 'cpu_q4_12'
COMBINED_HLS_DIR = COMBINED_ROOT / 'vitis_hls_q4_12'
NA_ROOT = COMBINED_ROOT  # legacy name inside older helper functions
NA_FLOAT32_DIR = COMBINED_FLOAT32_DIR
NA_Q412_DIR = COMBINED_Q412_DIR
NA_HLS_DIR = COMBINED_HLS_DIR
FPGA_MODEL_DIR = MODEL_DIR / 'fpga'
FPGA_HLS_DIR = FPGA_MODEL_DIR / 'hls'
FPGA_HLS_OVERLAY_DIR = FPGA_HLS_DIR / 'overlay'
FPGA_HLS_REPORTS_DIR = FPGA_HLS_DIR / 'reports'
FPGA_RTL_DIR = FPGA_MODEL_DIR / 'rtl'
FPGA_RTL_OVERLAY_DIR = FPGA_RTL_DIR / 'overlay'
FPGA_RTL_REPORTS_DIR = FPGA_RTL_DIR / 'reports'
FPGA_OVERLAY_DIR = FPGA_MODEL_DIR / 'overlay'  # legacy fallback

PYNQ_HLS_REMOTE_URL = os.environ.get('PYNQ_HLS_URL', 'http://192.168.2.99:8000').rstrip('/')
PYNQ_HLS_REMOTE_TIMEOUT = float(os.environ.get('PYNQ_HLS_TIMEOUT', '3.0'))


def _remote_json_request(url: str, payload: Optional[Dict[str, Any]] = None, timeout: float = PYNQ_HLS_REMOTE_TIMEOUT) -> Dict[str, Any]:
    data = None
    headers = {'Accept': 'application/json'}
    if payload is not None:
        data = json.dumps(payload).encode('utf-8')
        headers['Content-Type'] = 'application/json'
    req = urllib.request.Request(url, data=data, headers=headers, method='POST' if payload is not None else 'GET')
    try:
        with urllib.request.urlopen(req, timeout=timeout) as resp:
            raw = resp.read().decode('utf-8', errors='replace')
            return json.loads(raw) if raw else {}
    except urllib.error.HTTPError as exc:
        try:
            raw = exc.read().decode('utf-8', errors='replace')
            parsed = json.loads(raw) if raw else {}
            if isinstance(parsed, dict):
                parsed.setdefault('http_status', exc.code)
                return parsed
        except Exception:
            pass
        raise RuntimeError(f'PYNQ remote API HTTP {exc.code}: {exc.reason}')

CONFIG_DIR = MODEL_DIR / 'config'
TWO_STAGE_DIR = MODEL_DIR / 'two_stage'
TWO_STAGE_FLOAT32_DIR = TWO_STAGE_DIR / 'cpu_float32'
TWO_STAGE_Q412_DIR = TWO_STAGE_DIR / 'cpu_q4_12'
TWO_STAGE_CONFIG_DIR = TWO_STAGE_DIR / 'config'


def choose_existing(paths: list[Path]) -> Path:
    for p in paths:
        if p.exists():
            return p
    return paths[0]


def read_model_input_length(default: int = SIGNAL_LENGTH) -> int:
    for path in [CONFIG_DIR / 'preprocess_config.json', CONFIG_DIR / 'ecg_model_config.json']:
        if not path.exists():
            continue
        try:
            data = json.loads(path.read_text(encoding='utf-8'))
            for key in ['segment_len', 'SEGMENT_LEN', 'signal_length', 'input_length', 'window_size']:
                if key in data:
                    return int(data[key])
        except Exception:
            pass
    # File export trước đây thường dùng SEGMENT_LEN = 320.
    # Nếu không có config, vẫn cho phép CNN tự thử với 320 trước.
    return default


def quantize_q4_12(signal: np.ndarray) -> np.ndarray:
    q = np.round(np.asarray(signal, dtype=np.float32) * Q_SCALE)
    q = np.clip(q, Q_MIN, Q_MAX)
    return q.astype(np.int16)


def dequantize_q4_12(q_signal: np.ndarray) -> np.ndarray:
    return np.asarray(q_signal, dtype=np.float32) / float(Q_SCALE)


def softmax(logits: np.ndarray) -> np.ndarray:
    logits = np.asarray(logits, dtype=np.float32)
    logits = logits - np.max(logits)
    exp = np.exp(logits)
    denom = np.sum(exp)
    if denom <= 1e-12:
        return np.ones_like(exp) / len(exp)
    return exp / denom


def _i16_from_u16(v: int) -> int:
    v = int(v) & 0xFFFF
    return v - 0x10000 if v >= 0x8000 else v


def decode_hls_score5_q12(raw_words: Any) -> Tuple[np.ndarray, Dict[str, Any]]:
    raw = np.asarray(raw_words).reshape(-1)
    raw_i64 = raw.astype(np.int64, copy=False)
    meta: Dict[str, Any] = {
        'raw_words': [int(x) for x in raw_i64.tolist()],
        'packing': 'direct_int16',
    }
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
        meta['packing'] = 'packed_i16_in_u32'
        return np.asarray(decoded[:5], dtype=np.int16), meta
    decoded = []
    for x in raw_i64[:5]:
        decoded.append(_i16_from_u16(int(x)))
    while len(decoded) < 5:
        decoded.append(0)
    return np.asarray(decoded[:5], dtype=np.int16), meta


def relu(x: np.ndarray) -> np.ndarray:
    return np.maximum(x, 0.0).astype(np.float32)


def gelu(x: np.ndarray) -> np.ndarray:
    x = np.asarray(x, dtype=np.float32)
    return (0.5 * x * (1.0 + np.tanh(np.sqrt(2.0 / np.pi) * (x + 0.044715 * np.power(x, 3))))).astype(np.float32)


def maxpool1d(x: np.ndarray, pool: int = 2, stride: int = 2) -> np.ndarray:
    # x shape: [C, L]
    c, l = x.shape
    if l < pool:
        return x
    out_len = (l - pool) // stride + 1
    out = np.zeros((c, out_len), dtype=np.float32)
    for i in range(out_len):
        start = i * stride
        out[:, i] = np.max(x[:, start:start + pool], axis=1)
    return out



# -----------------------------------------------------------------------------
# Mini-Inception Q4.12 NPZ engine
# -----------------------------------------------------------------------------
def _maybe_dequant_q12(arr: np.ndarray) -> np.ndarray:
    arr = np.asarray(arr)
    if np.issubdtype(arr.dtype, np.integer):
        return arr.astype(np.float32) / float(Q_SCALE)
    return arr.astype(np.float32)


def conv1d_keras_same_cl(x: np.ndarray, w: np.ndarray, b: np.ndarray, stride: int = 1) -> np.ndarray:
    """Keras-like Conv1D cross-correlation for channels-last tensors.

    x: [length, in_channels]
    w: [kernel, in_channels, out_channels]
    b: [out_channels]
    """
    x = np.asarray(x, dtype=np.float32)
    w = np.asarray(w, dtype=np.float32)
    b = np.asarray(b, dtype=np.float32).reshape(-1)
    if x.ndim != 2 or w.ndim != 3:
        raise ValueError(f'conv1d_keras_same_cl shape sai: x={x.shape}, w={w.shape}')
    L, Cin = x.shape
    K, Win, Cout = w.shape
    if Cin != Win:
        raise ValueError(f'Conv channel mismatch: x={x.shape}, w={w.shape}')
    stride = int(stride or 1)
    out_len = int(np.ceil(L / stride))
    pad_total = max((out_len - 1) * stride + K - L, 0)
    pad_left = pad_total // 2
    pad_right = pad_total - pad_left
    xp = np.pad(x, ((pad_left, pad_right), (0, 0)), mode='constant')
    out = np.empty((out_len, Cout), dtype=np.float32)
    for i in range(out_len):
        st = i * stride
        window = xp[st:st + K, :]
        out[i, :] = np.tensordot(window, w, axes=([0, 1], [0, 1])) + b
    return out


def maxpool1d_keras_same_cl(x: np.ndarray, pool_size: int = 3, stride: int = 1) -> np.ndarray:
    """Keras-like MaxPooling1D with padding='same', channels-last."""
    x = np.asarray(x, dtype=np.float32)
    L, C = x.shape
    out_len = int(np.ceil(L / stride))
    pad_total = max((out_len - 1) * stride + pool_size - L, 0)
    pad_left = pad_total // 2
    pad_right = pad_total - pad_left
    xp = np.pad(x, ((pad_left, pad_right), (0, 0)), mode='constant', constant_values=-np.inf)
    out = np.empty((out_len, C), dtype=np.float32)
    for i in range(out_len):
        st = i * stride
        out[i, :] = np.max(xp[st:st + pool_size, :], axis=0)
    return out


def dense_keras(x: np.ndarray, w: np.ndarray, b: np.ndarray) -> np.ndarray:
    x = np.asarray(x, dtype=np.float32).reshape(-1)
    w = np.asarray(w, dtype=np.float32)
    b = np.asarray(b, dtype=np.float32).reshape(-1)
    if w.ndim == 2 and w.shape[0] == x.shape[0] and w.shape[1] == b.shape[0]:
        return (x @ w + b).astype(np.float32)
    if w.ndim == 2 and w.shape[1] == x.shape[0] and w.shape[0] == b.shape[0]:
        return (w @ x + b).astype(np.float32)
    raise ValueError(f'Dense shape mismatch: x={x.shape}, w={w.shape}, b={b.shape}')

def convert_conv_weight(w: np.ndarray, b: np.ndarray, in_channels: int) -> np.ndarray:
    # Return shape [out_ch, in_ch, kernel]
    w = np.asarray(w, dtype=np.float32)
    b_len = int(np.asarray(b).shape[0])
    if w.ndim != 3:
        raise ValueError(f'Conv weight phải có 3 chiều, nhận {w.shape}')

    # PyTorch Conv1d: [out_ch, in_ch, kernel]
    if w.shape[0] == b_len and w.shape[1] == in_channels:
        return w

    # TensorFlow Conv1D: [kernel, in_ch, out_ch]
    if w.shape[2] == b_len and w.shape[1] == in_channels:
        return np.transpose(w, (2, 1, 0)).astype(np.float32)

    # Một số export có thể là [out_ch, kernel, in_ch]
    if w.shape[0] == b_len and w.shape[2] == in_channels:
        return np.transpose(w, (0, 2, 1)).astype(np.float32)

    raise ValueError(f'Không xác định được format conv weight {w.shape}, bias {b.shape}, in_channels={in_channels}')


def conv1d(x: np.ndarray, w: np.ndarray, b: np.ndarray, padding: str = 'same') -> np.ndarray:
    # x shape [in_ch, L], w shape [out_ch, in_ch, K]
    x = np.asarray(x, dtype=np.float32)
    w = np.asarray(w, dtype=np.float32)
    b = np.asarray(b, dtype=np.float32)

    out_ch, in_ch, k = w.shape
    if x.shape[0] != in_ch:
        raise ValueError(f'Conv input channel mismatch: x={x.shape}, w={w.shape}')

    if padding == 'same':
        left = k // 2
        right = k - 1 - left
        xp = np.pad(x, ((0, 0), (left, right)), mode='constant')
        out_len = x.shape[1]
    elif padding == 'valid':
        xp = x
        out_len = x.shape[1] - k + 1
        if out_len <= 0:
            raise ValueError('Conv valid làm chiều dài <= 0')
    else:
        raise ValueError(f'Unsupported padding: {padding}')

    out = np.zeros((out_ch, out_len), dtype=np.float32)
    for oc in range(out_ch):
        acc = np.full(out_len, b[oc], dtype=np.float32)
        for ic in range(in_ch):
            # Deep-learning Conv1D in Keras/PyTorch is cross-correlation, not mathematical convolution.
            # Do NOT reverse the kernel here. Reversing the kernel can shift/logit-bias the CNN output strongly.
            kernel = w[oc, ic, :]
            acc += np.convolve(xp[ic], kernel, mode='valid')[:out_len]
        out[oc] = acc
    return out


def apply_linear(x: np.ndarray, W: np.ndarray, b: np.ndarray) -> np.ndarray:
    x = np.asarray(x, dtype=np.float32).reshape(-1)
    W = np.asarray(W, dtype=np.float32)
    b = np.asarray(b, dtype=np.float32).reshape(-1)

    # Common: W [in, out]
    if W.ndim == 2 and W.shape[0] == x.shape[0] and W.shape[1] == b.shape[0]:
        return (x @ W + b).astype(np.float32)

    # PyTorch Linear: W [out, in]
    if W.ndim == 2 and W.shape[1] == x.shape[0] and W.shape[0] == b.shape[0]:
        return (W @ x + b).astype(np.float32)

    raise ValueError(f'Linear shape mismatch: x={x.shape}, W={W.shape}, b={b.shape}')


class KerasReferenceModel:
    def __init__(self, path: Path, input_length: int) -> None:
        self.path = path
        self.input_length = int(input_length)
        self.received = path.exists()
        self.loaded = False
        self.warning = ''
        self.model = None
        self.backend = 'missing'
        self.input_shape = None

        if not self.received:
            self.warning = f'Chưa nhận được Keras model: cần đặt file tại {path}'
            return

        try:
            try:
                import tensorflow as tf  # type: ignore
                self.model = tf.keras.models.load_model(str(path), compile=False)
                self.backend = 'tensorflow.keras'
            except Exception as tf_exc:
                try:
                    from keras.models import load_model  # type: ignore
                    self.model = load_model(str(path), compile=False)
                    self.backend = 'keras'
                except Exception as keras_exc:
                    raise RuntimeError(f'Không import/load được TensorFlow/Keras. tensorflow error={tf_exc}; keras error={keras_exc}')

            self.input_shape = getattr(self.model, 'input_shape', None)
            self.loaded = True
        except Exception as exc:
            self.loaded = False
            self.warning = (
                f'Đã nhận {path.name} nhưng chưa load được Keras model: {exc}. '
                f'Nếu muốn dùng Keras reference, cài thêm: python -m pip install -r requirements-keras.txt'
            )

    def status(self) -> Dict:
        return {
            'model_name': 'Keras reference CPU model',
            'expected_path': str(self.path),
            'received': self.received,
            'loaded': self.loaded,
            'backend': self.backend,
            'input_length': self.input_length,
            'input_shape': str(self.input_shape),
            'warning': self.warning,
        }

    def _normal_beat(self, signal: np.ndarray, length: int = 320) -> np.ndarray:
        return normalize_signal(signal, length).astype(np.float32).reshape(1, length, 1)

    def _build_named_inputs(self, signal: np.ndarray):
        """Tạo input đúng cho Keras model.

        Model 5-class có 1 input: (1, 320, 1).
        Model pair-overlap N/A có 4 input có tên cố định:
        - left_beat_input: (1, 320, 1)
        - right_beat_input: (1, 320, 1)
        - overlap_region_input: (1, 160, 1)
        - pair_rr_overlap_features: (1, 15)

        Lỗi cũ xảy ra vì dashboard truyền input theo list sai thứ tự,
        khiến pair_rr_overlap_features nhận nhầm tensor (1,160,1).
        Bản này truyền bằng dict theo tên input để Keras map đúng.
        """
        x320 = self._normal_beat(signal, 320)
        # Với predict 1 beat đơn, chưa có ngữ cảnh trái/phải đầy đủ thì tạo
        # overlap tối thiểu từ vùng giữa của beat hiện tại. Khi predict dataset,
        # backend có thể thay bằng pair-context thật ở lớp quản lý cao hơn.
        sig = normalize_signal(signal, 320).astype(np.float32).reshape(-1)
        mid = len(sig) // 2
        left = max(0, mid - 80)
        overlap_vec = sig[left:left + 160]
        if len(overlap_vec) < 160:
            overlap_vec = np.pad(overlap_vec, (0, 160 - len(overlap_vec)), mode='constant')
        overlap = overlap_vec.astype(np.float32).reshape(1, 160, 1)
        features = np.zeros((1, 15), dtype=np.float32)

        input_shape = getattr(self.model, 'input_shape', None)
        input_names = []
        try:
            input_names = [getattr(t, 'name', '').split(':')[0] for t in getattr(self.model, 'inputs', [])]
        except Exception:
            input_names = []

        if isinstance(input_shape, list) and len(input_shape) > 1:
            named = {}
            for name in input_names:
                if name == 'left_beat_input':
                    named[name] = x320
                elif name == 'right_beat_input':
                    named[name] = x320
                elif name == 'overlap_region_input':
                    named[name] = overlap
                elif name == 'pair_rr_overlap_features':
                    named[name] = features
            if len(named) == len(input_names) and named:
                return named

            # Fallback theo shape nếu model bị đổi tên input.
            values = []
            for idx, shape in enumerate(input_shape):
                shape_tuple = tuple(int(x) if x is not None else -1 for x in shape) if shape is not None else ()
                if len(shape_tuple) == 2 and shape_tuple[-1] == 15:
                    values.append(features)
                elif len(shape_tuple) >= 3 and shape_tuple[1] == 160:
                    values.append(overlap)
                else:
                    values.append(x320)
            return values
        return x320

    def _to_probability_dict(self, y) -> Tuple[str, Dict[str, float]]:
        """Chuẩn hóa output Keras về dict xác suất.

        Hỗ trợ 2 dạng:
        - 5 output: N/L/R/V/A.
        - 2 output hoặc 2 head 2 output: N/A refiner. Khi đó L/R/V = 0.
        """
        outputs = y if isinstance(y, (list, tuple)) else [y]
        arrays = [np.asarray(o, dtype=np.float32).reshape(-1) for o in outputs]

        # Ưu tiên head 5-class nếu model có.
        for arr in arrays:
            if arr.shape[0] == len(LABELS):
                probs_arr = arr
                if not (np.all(probs_arr >= -1e-6) and abs(float(np.sum(probs_arr)) - 1.0) < 1e-3):
                    probs_arr = softmax(probs_arr)
                probs_arr = np.clip(probs_arr, 0.0, 1.0)
                probs_arr = probs_arr / max(float(np.sum(probs_arr)), 1e-12)
                pred = LABELS[int(np.argmax(probs_arr))]
                return pred, {label: float(probs_arr[i]) for i, label in enumerate(LABELS)}

        # Model NA pair-overlap thường có 2 head: left_output và right_output.
        # Với predict beat đơn, dùng head cuối cùng làm kết quả beat hiện tại.
        arr2 = None
        for arr in reversed(arrays):
            if arr.shape[0] == 2:
                arr2 = arr
                break
        if arr2 is None:
            raise ValueError(f'Output Keras không phải 5 lớp hoặc 2 lớp N/A: {[a.shape for a in arrays]}')
        if not (np.all(arr2 >= -1e-6) and abs(float(np.sum(arr2)) - 1.0) < 1e-3):
            arr2 = softmax(arr2)
        arr2 = np.clip(arr2, 0.0, 1.0)
        arr2 = arr2 / max(float(np.sum(arr2)), 1e-12)
        probs = {label: 0.0 for label in LABELS}
        probs['N'] = float(arr2[0])
        probs['A'] = float(arr2[1])
        pred = 'A' if probs['A'] >= probs['N'] else 'N'
        return pred, probs

    def predict(self, signal: np.ndarray) -> Tuple[str, Dict[str, float]]:
        if not self.loaded or self.model is None:
            raise RuntimeError(self.warning or 'Keras model chưa sẵn sàng.')
        x = self._build_named_inputs(signal)
        try:
            y = self.model.predict(x, verbose=0)
            return self._to_probability_dict(y)
        except Exception as exc:
            raise RuntimeError(f'Không chạy được Keras model đã nhận. Lỗi: {exc}')

    def predict_na_pair_inputs(self, left_beat: np.ndarray, right_beat: np.ndarray, overlap_region: np.ndarray, features: np.ndarray, target_side: str = 'left') -> Tuple[str, Dict[str, float]]:
        if not self.loaded or self.model is None:
            raise RuntimeError(self.warning or 'Keras pair-overlap model chưa sẵn sàng.')
        named = {
            'left_beat_input': np.asarray(left_beat, dtype=np.float32).reshape(1, 320, 1),
            'right_beat_input': np.asarray(right_beat, dtype=np.float32).reshape(1, 320, 1),
            'overlap_region_input': np.asarray(overlap_region, dtype=np.float32).reshape(1, 160, 1),
            'pair_rr_overlap_features': np.asarray(features, dtype=np.float32).reshape(1, 15),
        }
        try:
            y = self.model.predict(named, verbose=0)
            outputs = y if isinstance(y, (list, tuple)) else [y]
            output_names = list(getattr(self.model, 'output_names', []) or [])
            target_idx = 0 if target_side == 'left' else min(1, len(outputs) - 1)
            for idx, name in enumerate(output_names):
                if target_side == 'left' and 'left' in str(name).lower():
                    target_idx = idx
                if target_side == 'right' and 'right' in str(name).lower():
                    target_idx = idx
            arr = np.asarray(outputs[target_idx], dtype=np.float32).reshape(-1)
            if arr.shape[0] != 2:
                # fallback: dùng hàm parse chung nếu output không như mong đợi
                return self._to_probability_dict(y)
            if not (np.all(arr >= -1e-6) and abs(float(np.sum(arr)) - 1.0) < 1e-3):
                arr = softmax(arr)
            arr = np.clip(arr, 0.0, 1.0)
            arr = arr / max(float(np.sum(arr)), 1e-12)
            probs = {label: 0.0 for label in LABELS}
            probs['N'] = float(arr[0])
            probs['A'] = float(arr[1])
            pred = 'A' if probs['A'] >= probs['N'] else 'N'
            return pred, probs
        except Exception as exc:
            raise RuntimeError(f'Không chạy được pair-overlap Keras model đã nhận. Lỗi: {exc}')


class NpzModel:
    def __init__(self, path: Path, model_name: str) -> None:
        self.path = path
        self.model_name = model_name
        self.received = path.exists()
        self.loaded = False
        self.warning = ''
        self.mode = 'missing'
        self.data = None
        self.input_length = read_model_input_length(SIGNAL_LENGTH)
        self.cnn_plan = None

        if not self.received:
            self.warning = f'Chưa nhận được {model_name}: cần đặt file tại {path}'
            return

        try:
            data = np.load(path)
            self.data = data
            keys = list(data.files)

            if 'W' in data and 'b' in data:
                W = data['W'].astype(np.float32)
                b = data['b'].astype(np.float32)
                if W.shape[1] != len(LABELS) or b.shape[0] != len(LABELS):
                    raise ValueError(f'W/b không khớp số lớp. W={W.shape}, b={b.shape}, labels={len(LABELS)}')
                self.mode = 'linear_W_b'
                self.loaded = True
                return

            required_cnn = [
                'conv1_w', 'conv1_b', 'conv2_w', 'conv2_b',
                'conv3_w', 'conv3_b', 'conv4_w', 'conv4_b',
                'fc1_w', 'fc1_b', 'fc2_w', 'fc2_b'
            ]
            if all(k in data for k in required_cnn):
                self.mode = 'cnn_conv4_fc2'
                self.cnn_plan = self._discover_cnn_plan()
                self.loaded = True
                return

            required_main5_sep_res = [
                'main5_conv1d_kernel', 'main5_batch_normalization_gamma',
                'main5_conv1d_2_kernel', 'main5_conv1d_4_kernel', 'main5_conv1d_7_kernel', 'main5_conv1d_10_kernel',
                'main5_dense_kernel', 'main5_class_output_kernel', 'main5_class_output_bias'
            ]
            if all(k in data for k in required_main5_sep_res):
                self.mode = 'main5_sep_res_inception_q12_npz'
                self.input_length = 320
                self.loaded = True
                return

            required_mini_inception = [
                'conv1d_0_k7_s2_conv_w_fold', 'conv1d_0_k7_s2_conv_b_fold',
                'mini_inception_0_project_1x1_conv_w_fold', 'mini_inception_0_project_1x1_conv_b_fold',
                'conv1d_11_k5_s2_conv_w_fold', 'conv1d_11_k5_s2_conv_b_fold',
                'mini_inception_1_project_1x1_conv_w_fold', 'mini_inception_1_project_1x1_conv_b_fold',
                'conv1d_22_k3_s2_conv_w_fold', 'conv1d_22_k3_s2_conv_b_fold',
                'mini_inception_2_project_1x1_conv_w_fold', 'mini_inception_2_project_1x1_conv_b_fold',
                'fc1_w', 'fc1_b', 'fc2_logits_w', 'fc2_logits_b'
            ]
            if all(k in data for k in required_mini_inception):
                self.mode = 'mini_inception_q12_npz'
                self.input_length = 320
                self.loaded = True
                return

            required_na_overlap = [
                'shared_beat_sepconv0_depthwise_kernel', 'shared_beat_sepconv0_pointwise_kernel',
                'shared_beat_bn0_gamma', 'shared_beat_bn0_beta', 'shared_beat_bn0_moving_mean', 'shared_beat_bn0_moving_variance',
                'shared_beat_sepconv1_depthwise_kernel', 'shared_beat_sepconv1_pointwise_kernel',
                'shared_beat_bn1_gamma', 'shared_beat_bn1_beta', 'shared_beat_bn1_moving_mean', 'shared_beat_bn1_moving_variance',
                'shared_beat_embed_kernel', 'shared_beat_embed_bias',
                'overlap_sepconv0_depthwise_kernel', 'overlap_sepconv0_pointwise_kernel',
                'overlap_bn0_gamma', 'overlap_bn0_beta', 'overlap_bn0_moving_mean', 'overlap_bn0_moving_variance',
                'overlap_sepconv1_depthwise_kernel', 'overlap_sepconv1_pointwise_kernel',
                'overlap_bn1_gamma', 'overlap_bn1_beta', 'overlap_bn1_moving_mean', 'overlap_bn1_moving_variance',
                'overlap_embed_kernel', 'overlap_embed_bias',
                'feature_fc0_kernel', 'feature_fc0_bias', 'fusion_fc0_kernel', 'fusion_fc0_bias',
                'fusion_fc1_kernel', 'fusion_fc1_bias',
                'left_head_fc0_kernel', 'left_head_fc0_bias', 'right_head_fc0_kernel', 'right_head_fc0_bias',
                'left_output_kernel', 'left_output_bias', 'right_output_kernel', 'right_output_bias'
            ]
            if all((k in data) or (('pair_' + k) in data) for k in required_na_overlap):
                self.mode = 'na_pair_overlap_q12_npz'
                self.input_length = 320
                self.loaded = True
                return

            raise ValueError(f'file .npz chưa được hỗ trợ. Các key hiện có: {keys}')
        except Exception as exc:
            self.loaded = False
            self.warning = f'Đã nhận file {path.name} nhưng không load được: {exc}'

    def status(self) -> Dict:
        return {
            'model_name': self.model_name,
            'expected_path': str(self.path),
            'received': self.received,
            'loaded': self.loaded,
            'mode': self.mode,
            'input_length': self.input_length,
            'warning': self.warning,
        }

    def _prepare_input_candidates(self) -> List[np.ndarray]:
        # Hàm này chỉ tạo shape khi khám phá kiến trúc. Nội dung không quan trọng.
        candidates = []
        for L in [self.input_length, 320, 187, SIGNAL_LENGTH]:
            if L > 0 and L not in [x.shape[-1] for x in candidates]:
                candidates.append(np.zeros((1, L), dtype=np.float32))
        return candidates

    def _forward_conv_stack(self, x: np.ndarray, padding: str, pool_mask: int) -> np.ndarray:
        for i in range(1, 5):
            w_raw = self.data[f'conv{i}_w']
            b = self.data[f'conv{i}_b'].astype(np.float32)
            w = convert_conv_weight(w_raw, b, x.shape[0])
            x = relu(conv1d(x, w, b, padding=padding))
            if (pool_mask >> (i - 1)) & 1:
                x = maxpool1d(x, 2, 2)
        return x

    def _discover_cnn_plan(self) -> Dict:
        fc1_w = self.data['fc1_w']
        fc1_b = self.data['fc1_b']
        fc1_candidates = set()
        if fc1_w.ndim == 2:
            fc1_candidates.add(int(fc1_w.shape[0]))
            fc1_candidates.add(int(fc1_w.shape[1]))

        last_error = None
        for x0 in self._prepare_input_candidates():
            for padding in ['same', 'valid']:
                for pool_mask in range(16):
                    try:
                        x = self._forward_conv_stack(x0.copy(), padding, pool_mask)

                        # Case 1: flatten trực tiếp sau conv stack.
                        flat = x.reshape(-1)
                        if flat.shape[0] in fc1_candidates:
                            h = relu(apply_linear(flat, fc1_w, fc1_b))
                            _ = apply_linear(h, self.data['fc2_w'], self.data['fc2_b'])
                            return {
                                'input_length': int(x0.shape[-1]),
                                'padding': padding,
                                'pool_mask': int(pool_mask),
                                'head': 'flatten',
                                'feature_size': int(flat.shape[0]),
                            }

                        # Case 2: Global Average Pooling sau conv4.
                        # File bạn gửi có conv4 out_channels = 256 và fc1_w = (128, 256),
                        # nên kiến trúc đúng là conv stack -> global average pooling -> fc1 -> fc2.
                        gap = np.mean(x, axis=1).astype(np.float32)
                        if gap.shape[0] in fc1_candidates:
                            h = relu(apply_linear(gap, fc1_w, fc1_b))
                            _ = apply_linear(h, self.data['fc2_w'], self.data['fc2_b'])
                            return {
                                'input_length': int(x0.shape[-1]),
                                'padding': padding,
                                'pool_mask': int(pool_mask),
                                'head': 'global_avg_pool',
                                'feature_size': int(gap.shape[0]),
                            }
                    except Exception as exc:
                        last_error = exc
                        continue
        raise ValueError(f'Không tự khớp được kiến trúc CNN với fc1. Lỗi cuối: {last_error}')

    def _predict_linear(self, signal: np.ndarray) -> Tuple[str, Dict[str, float]]:
        W = self.data['W'].astype(np.float32)
        b = self.data['b'].astype(np.float32)
        x = normalize_signal(signal, W.shape[0]).astype(np.float32)
        logits = apply_linear(x, W, b)
        probs_arr = softmax(logits)
        pred = LABELS[int(np.argmax(probs_arr))]
        return pred, {label: float(probs_arr[i]) for i, label in enumerate(LABELS)}

    def _predict_cnn(self, signal: np.ndarray) -> Tuple[str, Dict[str, float]]:
        plan = self.cnn_plan
        x = normalize_signal(signal, plan['input_length']).astype(np.float32).reshape(1, -1)
        x = self._forward_conv_stack(x, plan['padding'], plan['pool_mask'])

        if plan.get('head') == 'global_avg_pool':
            feat = np.mean(x, axis=1).astype(np.float32)
        else:
            feat = x.reshape(-1).astype(np.float32)

        h = relu(apply_linear(feat, self.data['fc1_w'], self.data['fc1_b']))
        logits = apply_linear(h, self.data['fc2_w'], self.data['fc2_b'])
        probs_arr = softmax(logits)
        pred = LABELS[int(np.argmax(probs_arr))]
        return pred, {label: float(probs_arr[i]) for i, label in enumerate(LABELS)}

    def _q12_w(self, key: str) -> np.ndarray:
        if key in self.data:
            return _maybe_dequant_q12(self.data[key])
        pair_key = 'pair_' + key
        if pair_key in self.data:
            return _maybe_dequant_q12(self.data[pair_key])
        main_key = 'main5_' + key
        if main_key in self.data:
            return _maybe_dequant_q12(self.data[main_key])
        raise KeyError(f'Thiếu key weight: {key}')

    def _conv_cl(self, x: np.ndarray, w_key: str, b_key: str, stride: int = 1) -> np.ndarray:
        return conv1d_keras_same_cl(x, self._q12_w(w_key), self._q12_w(b_key), stride=stride)

    def _mini_inception_block(self, x: np.ndarray, idx: int) -> np.ndarray:
        p = f'mini_inception_{idx}'
        r3 = relu(self._conv_cl(x, f'{p}_reduce_3_conv_w', f'{p}_reduce_3_conv_b', stride=1))
        r5 = relu(self._conv_cl(x, f'{p}_reduce_5_conv_w', f'{p}_reduce_5_conv_b', stride=1))
        r7 = relu(self._conv_cl(x, f'{p}_reduce_7_conv_w_fold', f'{p}_reduce_7_conv_b_fold', stride=1))

        pool = maxpool1d_keras_same_cl(x, pool_size=3, stride=1)
        b_pool = relu(self._conv_cl(pool, f'{p}_pool_1x1_conv_w', f'{p}_pool_1x1_conv_b', stride=1))
        b_1x1 = relu(self._conv_cl(x, f'{p}_1x1_conv_w', f'{p}_1x1_conv_b', stride=1))
        b_3x1 = relu(self._conv_cl(r3, f'{p}_3x1_conv_w', f'{p}_3x1_conv_b', stride=1))
        b_5x1 = relu(self._conv_cl(r5, f'{p}_5x1_conv_w', f'{p}_5x1_conv_b', stride=1))
        b_7x1 = relu(self._conv_cl(r7, f'{p}_7x1_conv_w_fold', f'{p}_7x1_conv_b_fold', stride=1))

        concat = np.concatenate([b_pool, b_1x1, b_3x1, b_5x1, b_7x1], axis=1).astype(np.float32)
        proj = relu(self._conv_cl(concat, f'{p}_project_1x1_conv_w_fold', f'{p}_project_1x1_conv_b_fold', stride=1))
        if proj.shape != x.shape:
            raise ValueError(f'Residual shape mismatch ở {p}: proj={proj.shape}, x={x.shape}')
        return relu(proj + x)

    def _conv_no_bias_main5(self, x: np.ndarray, key: str, stride: int = 1) -> np.ndarray:
        w = self._q12_w(key)
        b = np.zeros((w.shape[-1],), dtype=np.float32)
        return conv1d_keras_same_cl(x, w, b, stride=stride)

    def _sepconv_main5(self, x: np.ndarray, depth_key: str, point_key: str) -> np.ndarray:
        x = np.asarray(x, dtype=np.float32)
        depth = self._q12_w(depth_key)
        point = self._q12_w(point_key)
        L, Cin = x.shape
        K, Dcin, dm = depth.shape
        if Cin != Dcin:
            raise ValueError(f'Main5 sepconv channel mismatch: x={x.shape}, depth={depth.shape}')
        out_len = L
        pad_total = max((out_len - 1) + K - L, 0)
        pad_left = pad_total // 2
        pad_right = pad_total - pad_left
        xp = np.pad(x, ((pad_left, pad_right), (0, 0)), mode='constant')
        dw = np.empty((out_len, Cin * dm), dtype=np.float32)
        idx = 0
        for c in range(Cin):
            for m in range(dm):
                kernel = depth[:, c, m]
                for i in range(out_len):
                    dw[i, idx] = float(np.dot(xp[i:i + K, c], kernel))
                idx += 1
        pw = point.reshape(point.shape[1], point.shape[2])
        return (dw @ pw).astype(np.float32)

    def _bn_main5(self, x: np.ndarray, idx) -> np.ndarray:
        prefix = 'main5_batch_normalization' if idx in (None, '') else f'main5_batch_normalization_{idx}'
        gamma = self._q12_w(prefix + '_gamma').reshape(1, -1)
        beta = self._q12_w(prefix + '_beta').reshape(1, -1)
        mean = self._q12_w(prefix + '_moving_mean').reshape(1, -1)
        var = np.maximum(self._q12_w(prefix + '_moving_variance').reshape(1, -1), 0.0)
        return ((x - mean) / np.sqrt(var + 1e-3) * gamma + beta).astype(np.float32)

    def _main5_inception_res_block(self, x: np.ndarray, sep_ids: Tuple[int, int, int], branch_conv_id: int, bn_ids: Tuple[int, int, int, int], project_conv_id: int, project_bn_id: int, shortcut_conv_id: Optional[int] = None, shortcut_bn_id: Optional[int] = None) -> np.ndarray:
        # 4 nhánh: SepConv k3/k5/k7 và Conv1D 1x1. Sau đó concat, project 1x1, cộng shortcut.
        b0 = gelu(self._bn_main5(self._sepconv_main5(x, f'main5_separable_conv1d{("_" + str(sep_ids[0])) if sep_ids[0] else ""}_depthwise_kernel', f'main5_separable_conv1d{("_" + str(sep_ids[0])) if sep_ids[0] else ""}_pointwise_kernel'), bn_ids[0]))
        b1 = gelu(self._bn_main5(self._sepconv_main5(x, f'main5_separable_conv1d_{sep_ids[1]}_depthwise_kernel', f'main5_separable_conv1d_{sep_ids[1]}_pointwise_kernel'), bn_ids[1]))
        b2 = gelu(self._bn_main5(self._sepconv_main5(x, f'main5_separable_conv1d_{sep_ids[2]}_depthwise_kernel', f'main5_separable_conv1d_{sep_ids[2]}_pointwise_kernel'), bn_ids[2]))
        conv_key = f'main5_conv1d_{branch_conv_id}_kernel'
        b3 = gelu(self._bn_main5(self._conv_no_bias_main5(x, conv_key), bn_ids[3]))
        concat = np.concatenate([b0, b1, b2, b3], axis=1).astype(np.float32)
        proj = self._bn_main5(self._conv_no_bias_main5(concat, f'main5_conv1d_{project_conv_id}_kernel'), project_bn_id)
        if shortcut_conv_id is not None:
            shortcut = self._bn_main5(self._conv_no_bias_main5(x, f'main5_conv1d_{shortcut_conv_id}_kernel'), shortcut_bn_id)
        else:
            shortcut = x
        if proj.shape != shortcut.shape:
            raise ValueError(f'Main5 residual mismatch: proj={proj.shape}, shortcut={shortcut.shape}')
        return gelu(proj + shortcut)

    def _predict_main5_sep_res_inception_q12_npz(self, signal: np.ndarray) -> Tuple[str, Dict[str, float]]:
        # Engine NumPy cho package combined_5class_pair_overlap_CPU_Q4_12_export.
        # Trọng số đọc trực tiếp từ .npz Q4.12, dequantize theo Q4.12 rồi chạy forward bằng NumPy.
        x = normalize_signal(signal, 320).astype(np.float32).reshape(320, 1)
        x = gelu(self._bn_main5(self._conv_no_bias_main5(x, 'main5_conv1d_kernel'), None))
        x = self._main5_inception_res_block(x, (0, 1, 2), 1, (1, 2, 3, 4), 2, 5)
        x = self._main5_inception_res_block(x, (3, 4, 5), 3, (6, 7, 8, 9), 4, 10, shortcut_conv_id=5, shortcut_bn_id=11)
        x = self._main5_inception_res_block(x, (6, 7, 8), 6, (12, 13, 14, 15), 7, 16, shortcut_conv_id=8, shortcut_bn_id=17)
        x = self._main5_inception_res_block(x, (9, 10, 11), 9, (18, 19, 20, 21), 10, 22, shortcut_conv_id=11, shortcut_bn_id=23)
        feat = np.concatenate([np.mean(x, axis=0), np.max(x, axis=0)]).astype(np.float32)
        h = dense_keras(feat, self._q12_w('main5_dense_kernel'), np.zeros((24,), dtype=np.float32))
        h = gelu(self._bn_main5(h.reshape(1, -1), 24).reshape(-1))
        logits = dense_keras(h, self._q12_w('main5_class_output_kernel'), self._q12_w('main5_class_output_bias'))
        probs_arr = softmax(logits)
        pred = LABELS[int(np.argmax(probs_arr))]
        return pred, {label: float(probs_arr[i]) for i, label in enumerate(LABELS)}

    def _predict_mini_inception_q12_npz(self, signal: np.ndarray) -> Tuple[str, Dict[str, float]]:
        # Chế độ này KHÔNG dùng Keras. Nó đọc trực tiếp five_class_weights_q12.npz,
        # dequantize Q4.12 weights/bias rồi chạy NumPy theo kiến trúc Mini-Inception 5-class.
        # Đây là CPU simulation cho Q4.12 NPZ, không phải reference Keras float32.
        x = normalize_signal(signal, 320).astype(np.float32).reshape(320, 1)

        x = relu(self._conv_cl(x, 'conv1d_0_k7_s2_conv_w_fold', 'conv1d_0_k7_s2_conv_b_fold', stride=2))
        x = self._mini_inception_block(x, 0)

        x = relu(self._conv_cl(x, 'conv1d_11_k5_s2_conv_w_fold', 'conv1d_11_k5_s2_conv_b_fold', stride=2))
        x = self._mini_inception_block(x, 1)

        x = relu(self._conv_cl(x, 'conv1d_22_k3_s2_conv_w_fold', 'conv1d_22_k3_s2_conv_b_fold', stride=2))
        x = self._mini_inception_block(x, 2)

        feat = np.mean(x, axis=0).astype(np.float32)
        h = relu(dense_keras(feat, self._q12_w('fc1_w'), self._q12_w('fc1_b')))
        logits = dense_keras(h, self._q12_w('fc2_logits_w'), self._q12_w('fc2_logits_b'))
        probs_arr = softmax(logits)
        pred = LABELS[int(np.argmax(probs_arr))]
        return pred, {label: float(probs_arr[i]) for i, label in enumerate(LABELS)}

    def _maxpool_valid_cl(self, x: np.ndarray, pool_size: int, stride: int) -> np.ndarray:
        x = np.asarray(x, dtype=np.float32)
        L, C = x.shape
        if L < pool_size:
            return x
        out_len = (L - pool_size) // stride + 1
        out = np.empty((out_len, C), dtype=np.float32)
        for i in range(out_len):
            st = i * stride
            out[i, :] = np.max(x[st:st + pool_size, :], axis=0)
        return out

    def _depthwise_sepconv_same(self, x: np.ndarray, depth_key: str, point_key: str) -> np.ndarray:
        x = np.asarray(x, dtype=np.float32)
        depth = self._q12_w(depth_key)      # [K, Cin, depth_multiplier]
        point = self._q12_w(point_key)      # [1, Cin*dm, Cout]
        if depth.ndim != 3 or point.ndim != 3:
            raise ValueError(f'SepConv weight shape sai: {depth_key}={depth.shape}, {point_key}={point.shape}')
        L, Cin = x.shape
        K, Dcin, dm = depth.shape
        if Cin != Dcin:
            raise ValueError(f'SepConv channel mismatch: x={x.shape}, depth={depth.shape}')
        out_len = L
        pad_total = max((out_len - 1) + K - L, 0)
        pad_left = pad_total // 2
        pad_right = pad_total - pad_left
        xp = np.pad(x, ((pad_left, pad_right), (0, 0)), mode='constant')
        dw = np.empty((out_len, Cin * dm), dtype=np.float32)
        idx = 0
        for c in range(Cin):
            for m in range(dm):
                kernel = depth[:, c, m]
                vals = np.zeros(out_len, dtype=np.float32)
                for i in range(out_len):
                    vals[i] = float(np.dot(xp[i:i + K, c], kernel))
                dw[:, idx] = vals
                idx += 1
        pw = point.reshape(point.shape[1], point.shape[2])
        return (dw @ pw).astype(np.float32)

    def _bn_cl(self, x: np.ndarray, prefix: str) -> np.ndarray:
        gamma = self._q12_w(prefix + '_gamma').reshape(1, -1)
        beta = self._q12_w(prefix + '_beta').reshape(1, -1)
        mean = self._q12_w(prefix + '_moving_mean').reshape(1, -1)
        var = self._q12_w(prefix + '_moving_variance').reshape(1, -1)
        # Variance trong một số export Q4.12 có thể rất nhỏ; ép không âm để tránh NaN.
        var = np.maximum(var, 0.0)
        return ((x - mean) / np.sqrt(var + 1e-3) * gamma + beta).astype(np.float32)

    def _encode_beat_na_q12(self, beat: np.ndarray) -> np.ndarray:
        x = np.asarray(beat, dtype=np.float32).reshape(320, 1)
        x = self._depthwise_sepconv_same(x, 'shared_beat_sepconv0_depthwise_kernel', 'shared_beat_sepconv0_pointwise_kernel')
        x = relu(self._bn_cl(x, 'shared_beat_bn0'))
        x = self._maxpool_valid_cl(x, pool_size=4, stride=4)
        x = self._depthwise_sepconv_same(x, 'shared_beat_sepconv1_depthwise_kernel', 'shared_beat_sepconv1_pointwise_kernel')
        x = relu(self._bn_cl(x, 'shared_beat_bn1'))
        x = self._maxpool_valid_cl(x, pool_size=2, stride=2)
        gap = np.mean(x, axis=0)
        gmp = np.max(x, axis=0)
        feat = np.concatenate([gap, gmp]).astype(np.float32)
        return relu(dense_keras(feat, self._q12_w('shared_beat_embed_kernel'), self._q12_w('shared_beat_embed_bias')))

    def _encode_overlap_na_q12(self, overlap: np.ndarray) -> np.ndarray:
        x = np.asarray(overlap, dtype=np.float32).reshape(160, 1)
        x = self._depthwise_sepconv_same(x, 'overlap_sepconv0_depthwise_kernel', 'overlap_sepconv0_pointwise_kernel')
        x = relu(self._bn_cl(x, 'overlap_bn0'))
        x = self._maxpool_valid_cl(x, pool_size=4, stride=4)
        x = self._depthwise_sepconv_same(x, 'overlap_sepconv1_depthwise_kernel', 'overlap_sepconv1_pointwise_kernel')
        x = relu(self._bn_cl(x, 'overlap_bn1'))
        gap = np.mean(x, axis=0)
        gmp = np.max(x, axis=0)
        feat = np.concatenate([gap, gmp]).astype(np.float32)
        return relu(dense_keras(feat, self._q12_w('overlap_embed_kernel'), self._q12_w('overlap_embed_bias')))

    def _predict_na_pair_overlap_q12_npz(self, signal: np.ndarray) -> Tuple[str, Dict[str, float]]:
        # CPU Q4.12 thật theo file .npz: đọc trọng số int16 Q4.12, dequantize và chạy NumPy.
        # Không gọi Keras và không dùng model Float32 để thay thế.
        beat = normalize_signal(signal, 320).astype(np.float32)
        left = beat
        right = beat
        overlap = normalize_signal(signal, 160).astype(np.float32)
        pair_features = np.zeros((15,), dtype=np.float32)

        left_embed = self._encode_beat_na_q12(left)
        right_embed = self._encode_beat_na_q12(right)
        overlap_embed = self._encode_overlap_na_q12(overlap)
        feature_embed = relu(dense_keras(pair_features, self._q12_w('feature_fc0_kernel'), self._q12_w('feature_fc0_bias')))

        pair = np.concatenate([left_embed, right_embed, overlap_embed, feature_embed]).astype(np.float32)
        fusion = relu(dense_keras(pair, self._q12_w('fusion_fc0_kernel'), self._q12_w('fusion_fc0_bias')))
        fusion = relu(dense_keras(fusion, self._q12_w('fusion_fc1_kernel'), self._q12_w('fusion_fc1_bias')))

        right_ctx = np.concatenate([right_embed, overlap_embed, feature_embed, fusion]).astype(np.float32)
        h = relu(dense_keras(right_ctx, self._q12_w('right_head_fc0_kernel'), self._q12_w('right_head_fc0_bias')))
        logits = dense_keras(h, self._q12_w('right_output_kernel'), self._q12_w('right_output_bias'))
        probs2 = softmax(logits)
        probs = {label: 0.0 for label in LABELS}
        probs['N'] = float(probs2[0])
        probs['A'] = float(probs2[1])
        pred = 'A' if probs['A'] >= probs['N'] else 'N'
        return pred, probs

    def predict_na_pair_inputs(self, left_beat: np.ndarray, right_beat: np.ndarray, overlap_region: np.ndarray, features: np.ndarray, target_side: str = 'left') -> Tuple[str, Dict[str, float]]:
        if not self.loaded:
            raise RuntimeError(self.warning or f'{self.model_name} chưa sẵn sàng.')
        if self.mode != 'na_pair_overlap_q12_npz':
            raise RuntimeError(f'Model Q4.12 không phải pair-overlap refiner: mode={self.mode}')
        left = normalize_signal(left_beat, 320).astype(np.float32).reshape(-1)
        right = normalize_signal(right_beat, 320).astype(np.float32).reshape(-1)
        overlap = normalize_signal(overlap_region, 160).astype(np.float32).reshape(-1)
        pair_features = np.asarray(features, dtype=np.float32).reshape(15)

        left_embed = self._encode_beat_na_q12(left)
        right_embed = self._encode_beat_na_q12(right)
        overlap_embed = self._encode_overlap_na_q12(overlap)
        feature_embed = relu(dense_keras(pair_features, self._q12_w('feature_fc0_kernel'), self._q12_w('feature_fc0_bias')))
        pair = np.concatenate([left_embed, right_embed, overlap_embed, feature_embed]).astype(np.float32)
        fusion = relu(dense_keras(pair, self._q12_w('fusion_fc0_kernel'), self._q12_w('fusion_fc0_bias')))
        fusion = relu(dense_keras(fusion, self._q12_w('fusion_fc1_kernel'), self._q12_w('fusion_fc1_bias')))

        if target_side == 'right':
            ctx = np.concatenate([right_embed, overlap_embed, feature_embed, fusion]).astype(np.float32)
            h = relu(dense_keras(ctx, self._q12_w('right_head_fc0_kernel'), self._q12_w('right_head_fc0_bias')))
            logits = dense_keras(h, self._q12_w('right_output_kernel'), self._q12_w('right_output_bias'))
        else:
            ctx = np.concatenate([left_embed, overlap_embed, feature_embed, fusion]).astype(np.float32)
            h = relu(dense_keras(ctx, self._q12_w('left_head_fc0_kernel'), self._q12_w('left_head_fc0_bias')))
            logits = dense_keras(h, self._q12_w('left_output_kernel'), self._q12_w('left_output_bias'))
        arr = softmax(logits)
        probs = {label: 0.0 for label in LABELS}
        probs['N'] = float(arr[0])
        probs['A'] = float(arr[1])
        pred = 'A' if probs['A'] >= probs['N'] else 'N'
        return pred, probs

    def predict(self, signal: np.ndarray) -> Tuple[str, Dict[str, float]]:
        if not self.loaded:
            raise RuntimeError(self.warning or f'{self.model_name} chưa sẵn sàng.')
        if self.mode == 'linear_W_b':
            return self._predict_linear(signal)
        if self.mode == 'cnn_conv4_fc2':
            return self._predict_cnn(signal)
        if self.mode == 'main5_sep_res_inception_q12_npz':
            return self._predict_main5_sep_res_inception_q12_npz(signal)
        if self.mode == 'mini_inception_q12_npz':
            return self._predict_mini_inception_q12_npz(signal)
        if self.mode == 'na_pair_overlap_q12_npz':
            return self._predict_na_pair_overlap_q12_npz(signal)
        raise RuntimeError(f'Model mode chưa hỗ trợ: {self.mode}')


class CpuModelManager:
    def __init__(self) -> None:
        # V53: combined 5-class + pair-overlap N/A refiner package.
        self.float_main_keras = COMBINED_FLOAT32_DIR / 'keras' / 'main_5class_model_CPU_FLOAT.keras'
        self.float_pair_keras = COMBINED_FLOAT32_DIR / 'keras' / 'pair_overlap_NA_refiner_CPU_FLOAT.keras'
        self.float_config = COMBINED_FLOAT32_DIR / 'config' / 'combined_inference_config.json'
        self.float_feature_norm = COMBINED_FLOAT32_DIR / 'features' / 'pair_overlap_feature_norm_float32.npz'

        self.q12_main_npz = COMBINED_Q412_DIR / 'weights' / 'main_5class_q4_12_weights.npz'
        self.q12_pair_npz = COMBINED_Q412_DIR / 'weights' / 'pair_overlap_refiner_q4_12_weights.npz'
        self.q12_config = COMBINED_Q412_DIR / 'config' / 'combined_cpu_q4_12_config.json'
        self.q12_feature_norm = COMBINED_Q412_DIR / 'features' / 'pair_overlap_feature_norm_float32.npz'

        self.hls_config_h = COMBINED_HLS_DIR / 'headers' / 'combined_q4_12_config.h'
        self.hls_main_h = COMBINED_HLS_DIR / 'headers' / 'main_5class_q4_12_weights.h'
        self.hls_pair_h = COMBINED_HLS_DIR / 'headers' / 'pair_overlap_refiner_q4_12_weights.h'

        self.float_main_model = KerasReferenceModel(self.float_main_keras, SIGNAL_LENGTH)
        self.float_pair_model = KerasReferenceModel(self.float_pair_keras, SIGNAL_LENGTH)
        # CPU Q4.12: chỉ dùng file .npz/trọng số lượng tử hóa.
        # Không dùng Keras SIM để tránh hiểu nhầm với CPU Float32.
        self.q12_main_model = NpzModel(self.q12_main_npz, 'Combined 5-class Q4.12 NPZ weights')
        self.q12_pair_model = NpzModel(self.q12_pair_npz, 'Pair-overlap N/A Q4.12 NPZ weights')

        self.threshold_n = 0.20
        self.threshold_a = 0.85
        self.pair_feat_mean = np.zeros(15, dtype=np.float32)
        self.pair_feat_std = np.ones(15, dtype=np.float32)
        self._load_thresholds()
        self._load_pair_feature_norm()

    def _load_thresholds(self) -> None:
        for path in [self.float_config, self.q12_config]:
            if not path.exists():
                continue
            try:
                data = json.loads(path.read_text(encoding='utf-8'))
                th = data.get('thresholds', {}) if isinstance(data, dict) else {}
                self.threshold_n = float(th.get('PAIR_OVERLAP_THRESHOLD_N', self.threshold_n))
                self.threshold_a = float(th.get('PAIR_OVERLAP_THRESHOLD_A', self.threshold_a))
                return
            except Exception:
                pass

    def status(self) -> Dict:
        f_main = self.float_main_model.status()
        f_pair = self.float_pair_model.status()
        q_main = self.q12_main_model.status()
        q_pair = self.q12_pair_model.status()
        float_received = self.float_main_keras.exists() and self.float_pair_keras.exists() and self.float_config.exists()
        float_loaded = bool(f_main.get('loaded')) and bool(f_pair.get('loaded'))
        q12_received = self.q12_main_npz.exists() and self.q12_pair_npz.exists() and self.q12_config.exists()
        q12_loaded = bool(q_main.get('loaded')) and bool(q_pair.get('loaded'))
        q12_warning = ''
        if q12_received and not q12_loaded:
            q12_warning = (
                'Đã nhận đủ file .npz Q4.12 nhưng engine chưa load được. Kiểm tra warning chi tiết của main_model và pair_model.'
            )
        hls_received = self.hls_config_h.exists() and self.hls_main_h.exists() and self.hls_pair_h.exists()
        return {
            'float32': {
                'mode': 'combined_5class_pair_overlap_float32',
                'received': float_received,
                'loaded': float_loaded,
                'main_model': f_main,
                'pair_model': f_pair,
            },
            'q4_12': {
                'model_name': 'Combined CPU Q4.12 NPZ weights',
                'mode': q_main.get('mode') or 'npz_weights_only',
                'received': q12_received,
                'loaded': q12_loaded,
                'weights_received': q12_received,
                'keras_sim_received': False,
                'main_model': q_main,
                'pair_model': q_pair,
                'warning': q12_warning,
            },
            'combined': {
                'float32_received': float_received,
                'float32_loaded': float_loaded,
                'q4_12_received': q12_received,
                'q4_12_loaded': q12_loaded,
                'hls_export_received': hls_received,
                'files': {
                    'float_main_keras': str(self.float_main_keras),
                    'float_pair_keras': str(self.float_pair_keras),
                    'q12_main_npz': str(self.q12_main_npz),
                    'q12_pair_npz': str(self.q12_pair_npz),
                    'hls_config_h': str(self.hls_config_h),
                    'hls_main_h': str(self.hls_main_h),
                    'hls_pair_h': str(self.hls_pair_h),
                },
            },
            'keras_loaded': float_loaded,
            'keras_received': float_received,
            'keras_path': str(self.float_main_keras),
        }

    def _load_pair_feature_norm(self) -> None:
        for path in [self.float_feature_norm, self.q12_feature_norm]:
            if not path.exists():
                continue
            try:
                z = np.load(path, allow_pickle=True)
                mean = z['pair_feat_mean_E'] if 'pair_feat_mean_E' in z.files else z[z.files[0]]
                std = z['pair_feat_std_E'] if 'pair_feat_std_E' in z.files else z[z.files[1]]
                self.pair_feat_mean = np.asarray(mean, dtype=np.float32).reshape(15)
                self.pair_feat_std = np.asarray(std, dtype=np.float32).reshape(15)
                self.pair_feat_std = np.where(np.abs(self.pair_feat_std) < 1e-6, 1.0, self.pair_feat_std).astype(np.float32)
                return
            except Exception:
                pass

    def _segment_center(self, seg):
        if not isinstance(seg, dict):
            return None
        for key in ['center', 'sample', 'r_peak', 'ann_sample']:
            if key in seg and seg.get(key) is not None:
                try:
                    return float(seg.get(key))
                except Exception:
                    pass
        try:
            st = float(seg.get('start'))
            en = float(seg.get('end'))
            return (st + en) / 2.0
        except Exception:
            return None

    def _build_pair_context_inputs(self, signal: np.ndarray, context: Optional[Dict] = None):
        context = context or {}
        beats = context.get('beats')
        beat_index = int(context.get('beat_index', 0) or 0)
        segments = context.get('segments') if isinstance(context.get('segments'), list) else []

        cur = normalize_signal(signal, 320).astype(np.float32).reshape(-1)
        target_side = 'left'
        if isinstance(beats, np.ndarray) and len(beats) > 1:
            if beat_index < len(beats) - 1:
                left_i, right_i, target_side = beat_index, beat_index + 1, 'left'
            else:
                left_i, right_i, target_side = beat_index - 1, beat_index, 'right'
            left = normalize_signal(beats[left_i], 320).astype(np.float32).reshape(-1)
            right = normalize_signal(beats[right_i], 320).astype(np.float32).reshape(-1)
        else:
            left_i, right_i = beat_index, beat_index
            left = cur
            right = cur

        # Overlap region 160 mẫu: nếu không tái dựng được mẫu thô theo record, dùng tail-left/head-right
        # có cùng shape với lúc train. Điều này tránh truyền nhầm tensor 160 vào input feature 15 chiều.
        overlap = ((left[-160:] + right[:160]) * 0.5).astype(np.float32)

        centers = []
        for seg in segments:
            c = self._segment_center(seg)
            if c is not None:
                centers.append(c)
        if len(centers) >= 2:
            diffs = np.diff(np.asarray(centers, dtype=np.float32))
            median_rr = float(np.median(diffs[diffs > 0])) if np.any(diffs > 0) else 273.0
        else:
            median_rr = float(self.pair_feat_mean[12]) if self.pair_feat_mean.shape[0] >= 13 else 273.0
        median_rr = max(median_rr, 1.0)

        def c_at(i):
            if 0 <= i < len(centers):
                return float(centers[i])
            return None

        lc = c_at(left_i)
        rc = c_at(right_i)
        rr_before = (lc - c_at(left_i - 1)) if (lc is not None and c_at(left_i - 1) is not None) else median_rr
        rr_between = (rc - lc) if (lc is not None and rc is not None and right_i != left_i) else median_rr
        rr_after = (c_at(right_i + 1) - rc) if (rc is not None and c_at(right_i + 1) is not None) else median_rr
        rr_before = max(float(rr_before), 1.0)
        rr_between = max(float(rr_between), 1.0)
        rr_after = max(float(rr_after), 1.0)

        rb = rr_before / median_rr
        rmid = rr_between / median_rr
        ra = rr_after / median_rr

        overlap_width = 0.0
        try:
            lseg = segments[left_i] if 0 <= left_i < len(segments) else {}
            rseg = segments[right_i] if 0 <= right_i < len(segments) else {}
            lend = float(lseg.get('end'))
            rstart = float(rseg.get('start'))
            overlap_width = max(0.0, lend - rstart + 1.0)
        except Exception:
            overlap_width = float(self.pair_feat_mean[13]) if self.pair_feat_mean.shape[0] >= 14 else 0.0
        overlap_ratio = overlap_width / 320.0

        raw = np.asarray([
            rr_before, rr_between, rr_after,
            rb, rmid, ra,
            rb, rmid, rmid, ra,
            rmid - rb, ra - rmid,
            median_rr, overlap_width, overlap_ratio,
        ], dtype=np.float32)
        features = ((raw - self.pair_feat_mean) / self.pair_feat_std).astype(np.float32)
        return left, right, overlap, features, target_side

    def _combine_main_and_pair(self, main_model: KerasReferenceModel, pair_model: KerasReferenceModel, signal: np.ndarray, note_prefix: str, context: Optional[Dict] = None) -> Tuple[str, Dict[str, float], str]:
        base_pred, base_probs = main_model.predict(signal)
        if base_pred not in ('N', 'A'):
            return base_pred, base_probs, f'{note_prefix}: main 5-class dự đoán {base_pred}, không gọi N/A pair-overlap refiner'

        left, right, overlap, features, target_side = self._build_pair_context_inputs(signal, context)
        pair_pred, pair_probs = pair_model.predict_na_pair_inputs(left, right, overlap, features, target_side=target_side)
        p_a = float(pair_probs.get('A', 0.0))
        if p_a <= self.threshold_n:
            final = 'N'
        elif p_a >= self.threshold_a:
            final = 'A'
        else:
            final = base_pred

        final_probs = dict(base_probs)
        final_probs['N'] = float(pair_probs.get('N', final_probs.get('N', 0.0)))
        final_probs['A'] = float(pair_probs.get('A', final_probs.get('A', 0.0)))
        s = sum(max(0.0, float(v)) for v in final_probs.values())
        if s > 1e-12:
            final_probs = {k: max(0.0, float(v)) / s for k, v in final_probs.items()}
        note = f'{note_prefix}: main={base_pred}, gọi N/A pair-overlap refiner ({target_side}), pair={pair_pred}, P_A={p_a:.3f}, final={final}'
        return final, final_probs, note

    def predict_float32(self, signal: np.ndarray, context: Optional[Dict] = None) -> Tuple[str, Dict[str, float], str]:
        return self._combine_main_and_pair(self.float_main_model, self.float_pair_model, signal, 'CPU Float32 combined 5-class + N/A pair-overlap refiner', context=context)

    def predict_q4_12(self, signal: np.ndarray, context: Optional[Dict] = None) -> Tuple[str, Dict[str, float], str]:
        if not self.q12_main_model.loaded:
            raise RuntimeError(self.q12_main_model.warning or 'CPU Q4.12 chưa load được main 5-class .npz.')
        if not self.q12_pair_model.loaded:
            raise RuntimeError(self.q12_pair_model.warning or 'CPU Q4.12 chưa load được pair-overlap .npz.')
        return self._combine_main_and_pair(self.q12_main_model, self.q12_pair_model, signal, 'CPU Q4.12 NPZ engine combined 5-class + N/A pair-overlap refiner', context=context)


CPU_MODELS = CpuModelManager()


class CpuFloat32Engine:
    backend_id = 'cpu_float32'

    def predict(self, signal: np.ndarray, context: Optional[Dict] = None) -> Tuple[str, Dict[str, float], str]:
        return CPU_MODELS.predict_float32(signal, context=context)


class CpuQ412Engine:
    backend_id = 'cpu_q4_12'

    def predict(self, signal: np.ndarray, context: Optional[Dict] = None) -> Tuple[str, Dict[str, float], str]:
        return CPU_MODELS.predict_q4_12(signal, context=context)


def _safe_float(value):
    try:
        if value is None or value == '':
            return None
        return float(str(value).replace('%', '').strip())
    except Exception:
        return None


def _resource_item(used=None, available=None, percent=None):
    used_f = _safe_float(used)
    avail_f = _safe_float(available)
    pct_f = _safe_float(percent)
    if pct_f is None and used_f is not None and avail_f and avail_f > 0:
        pct_f = used_f * 100.0 / avail_f
    def compact(x):
        if x is None:
            return None
        if abs(x - int(x)) < 1e-9:
            return int(x)
        return round(x, 3)
    return {
        'used': compact(used_f),
        'available': compact(avail_f),
        'percent': compact(pct_f),
    }


def _normalize_resource_json(data: Dict) -> Dict:
    if not isinstance(data, dict):
        return {}
    out = {
        'source': data.get('source', 'resource_usage.json'),
        'device': data.get('device') or data.get('part') or data.get('fpga_part') or 'PYNQ-Z2 / XC7Z020',
        'clock_mhz': data.get('clock_mhz') or data.get('frequency_mhz') or data.get('target_clock_mhz'),
        'clock_period_ns': data.get('clock_period_ns') or data.get('target_clock_ns'),
        'latency_cycles': data.get('latency_cycles') or data.get('cycles'),
        'latency_us': data.get('latency_us'),
        'ii': data.get('ii') or data.get('initiation_interval'),
        'resources': {},
        'available': bool(data),
    }
    resources = data.get('resources', data)
    alias = {
        'LUT': ['LUT', 'LUTs', 'CLB LUTs', 'Slice LUTs'],
        'FF': ['FF', 'FFs', 'CLB Registers', 'Slice Registers', 'Register'],
        'BRAM': ['BRAM', 'BRAM_18K', 'Block RAM Tile', 'RAMB18', 'RAMB36'],
        'DSP': ['DSP', 'DSP48E', 'DSP48E1', 'DSPs'],
        'URAM': ['URAM', 'URAM288'],
    }
    for key, names in alias.items():
        found = None
        for name in names:
            if isinstance(resources, dict) and name in resources:
                found = resources[name]
                break
        if isinstance(found, dict):
            out['resources'][key] = _resource_item(
                found.get('used') or found.get('Used') or found.get('utilized'),
                found.get('available') or found.get('Available') or found.get('total'),
                found.get('percent') or found.get('Util%') or found.get('utilization_percent')
            )
        elif found is not None:
            out['resources'][key] = _resource_item(found, None, None)
    return out


def _parse_resource_report_text(text: str) -> Dict:
    # Parser nhẹ cho vài report Vivado/HLS phổ biến. Nếu không bắt được, trả resource trống.
    import re
    out = {'source': 'parsed_report', 'device': 'PYNQ-Z2 / XC7Z020', 'resources': {}, 'available': True}
    key_map = [
        ('LUT', [r'CLB LUTs?\s*\|\s*([0-9.]+)\s*\|\s*([0-9.]+)', r'LUT\s*\|\s*([0-9.]+)\s*\|\s*([0-9.]+)']),
        ('FF', [r'CLB Registers?\s*\|\s*([0-9.]+)\s*\|\s*([0-9.]+)', r'FF\s*\|\s*([0-9.]+)\s*\|\s*([0-9.]+)']),
        ('BRAM', [r'Block RAM Tile\s*\|\s*([0-9.]+)\s*\|\s*([0-9.]+)', r'BRAM_18K\s*\|\s*([0-9.]+)\s*\|\s*([0-9.]+)']),
        ('DSP', [r'DSPs?\s*\|\s*([0-9.]+)\s*\|\s*([0-9.]+)', r'DSP48E\w*\s*\|\s*([0-9.]+)\s*\|\s*([0-9.]+)']),
    ]
    for key, patterns in key_map:
        for pat in patterns:
            m = re.search(pat, text, re.IGNORECASE)
            if m:
                out['resources'][key] = _resource_item(m.group(1), m.group(2), None)
                break
    m = re.search(r'(?:Target clock period|Clock Period)\D+([0-9.]+)\s*ns', text, re.IGNORECASE)
    if m:
        out['clock_period_ns'] = float(m.group(1))
    m = re.search(r'(?:Latency[^\n]*?cycles|Latency)\D+([0-9]+)', text, re.IGNORECASE)
    if m:
        out['latency_cycles'] = int(m.group(1))
    return out if out['resources'] else {}


def read_fpga_resource_usage(report_dir: Path) -> Dict:
    json_candidates = [
        report_dir / 'resource_usage.json',
        report_dir / 'utilization.json',
        report_dir / 'fpga_resources.json',
    ]
    for path in json_candidates:
        if path.exists():
            try:
                data = json.loads(path.read_text(encoding='utf-8'))
                out = _normalize_resource_json(data)
                out['source_path'] = str(path.relative_to(ROOT))
                return out
            except Exception as exc:
                return {'available': False, 'error': f'Lỗi đọc {path.name}: {exc}', 'resources': {}}
    for path in list(report_dir.glob('*utilization*.rpt')) + list(report_dir.glob('*csynth*.rpt')) + list(report_dir.glob('*.rpt')):
        try:
            out = _parse_resource_report_text(path.read_text(encoding='utf-8', errors='ignore'))
            if out:
                out['source'] = path.name
                out['source_path'] = str(path.relative_to(ROOT))
                return out
        except Exception:
            pass
    return {
        'available': False,
        'resources': {},
        'expected_files': [
            str((report_dir / 'resource_usage.json').relative_to(ROOT)),
            str((report_dir / 'report_utilization.rpt').relative_to(ROOT)),
            str((report_dir / 'csynth.rpt').relative_to(ROOT)),
        ]
    }


class BaseFpgaQ412Engine:
    backend_id = 'fpga_base_q4_12'

    def __init__(self, kind: str, overlay_dir: Path, bit_names: List[str], hwh_names: List[str], legacy_fallback: bool = False, report_dir: Optional[Path] = None, allow_remote_api: bool = False) -> None:
        self.kind = kind
        self.overlay_dir = overlay_dir
        self.report_dir = report_dir or (overlay_dir.parent / 'reports')
        self.bit_path = choose_existing([overlay_dir / name for name in bit_names] + ([FPGA_OVERLAY_DIR / 'ecg_accel.bit'] if legacy_fallback else []))
        self.hwh_path = choose_existing([overlay_dir / name for name in hwh_names] + ([FPGA_OVERLAY_DIR / 'ecg_accel.hwh'] if legacy_fallback else []))
        self.bit_received = self.bit_path.exists()
        self.hwh_received = self.hwh_path.exists()
        self.overlay = None
        self.ip = None
        self.loaded = False
        self.warning = ''
        self.allow_remote_api = allow_remote_api
        self.remote_url = PYNQ_HLS_REMOTE_URL

        if not self.bit_received or not self.hwh_received:
            missing = []
            if not self.bit_received:
                missing.append(str(self.bit_path))
            if not self.hwh_received:
                missing.append(str(self.hwh_path))
            self.warning = f'Chưa nhận được FPGA {kind} overlay: thiếu ' + ', '.join(missing)
            return

        try:
            from pynq import Overlay  # type: ignore
            self.overlay = Overlay(str(self.bit_path))
            # Tên IP phụ thuộc tên block trong Vivado/HLS. Overlay người dùng vừa gửi có instance ecg_fpga_top_0.
            candidate_ip_names = [
                'ecg_fpga_top_0',
                'ecg_accel_0',
                'ecg_hls_accel_0',
                'ecg_rtl_accel_0',
            ]
            for ip_name in candidate_ip_names:
                self.ip = getattr(self.overlay, ip_name, None)
                if self.ip is not None:
                    self.ip_name = ip_name
                    break
            if self.ip is None and hasattr(self.overlay, 'ip_dict'):
                for ip_name, meta in self.overlay.ip_dict.items():
                    type_text = str(meta.get('type', ''))
                    if 'ecg_fpga_top' in ip_name or 'ecg_fpga_top' in type_text or 'ecg' in ip_name.lower():
                        self.ip = getattr(self.overlay, ip_name, None)
                        if self.ip is not None:
                            self.ip_name = ip_name
                            break
            if self.ip is None:
                available = ', '.join(getattr(self.overlay, 'ip_dict', {}).keys()) if hasattr(self.overlay, 'ip_dict') else 'không đọc được ip_dict'
                raise RuntimeError('Không tìm thấy IP ECG trong overlay. Các IP có trong overlay: ' + available)
            self.loaded = True
            self.warning = ''
        except Exception as exc:
            self.loaded = False
            self.warning = f'Đã nhận .bit/.hwh cho FPGA {kind} nhưng chưa load được trên PYNQ: {exc}'

    def _remote_health(self, timeout: float = 0.8) -> Dict[str, Any]:
        if not self.allow_remote_api:
            return {'ok': False, 'error': 'remote API disabled'}
        try:
            out = _remote_json_request(self.remote_url + '/health', timeout=timeout)
            if isinstance(out, dict):
                return out
            return {'ok': False, 'error': 'remote health response không phải JSON object'}
        except Exception as exc:
            return {'ok': False, 'error': str(exc)}

    def status(self) -> Dict:
        remote_health = self._remote_health(timeout=0.35) if (self.allow_remote_api and not self.loaded) else {'ok': False}
        remote_available = bool(remote_health.get('ok') or remote_health.get('overlay_loaded'))
        runtime_loaded = bool(self.loaded or remote_available)
        warning = self.warning
        if self.allow_remote_api and not self.loaded:
            if remote_available:
                warning = ''
            elif not warning:
                warning = f'Chưa load local PYNQ; remote API {self.remote_url} chưa sẵn sàng: {remote_health.get("error", "unknown")}'
        return {
            'kind': self.kind,
            'overlay_dir': str(self.overlay_dir.relative_to(ROOT)) if self.overlay_dir.exists() else str(self.overlay_dir),
            'hls_dir': str(FPGA_HLS_DIR.relative_to(ROOT)),
            'rtl_dir': str(FPGA_RTL_DIR.relative_to(ROOT)),
            'bit_path': str(self.bit_path),
            'hwh_path': str(self.hwh_path),
            'bit_received': self.bit_received,
            'hwh_received': self.hwh_received,
            'overlay_files_received': self.bit_received and self.hwh_received,
            'runtime_loaded': runtime_loaded,
            'local_runtime_loaded': self.loaded,
            'remote_api_enabled': self.allow_remote_api,
            'remote_url': self.remote_url,
            'remote_available': remote_available,
            'remote_health': remote_health,
            'warning': warning,
            'resource_usage': read_fpga_resource_usage(self.report_dir),
        }

    def predict(self, signal: np.ndarray, context: Optional[Dict] = None) -> Tuple[str, Dict[str, float], str]:
        if self.loaded:
            return self._predict_with_pynq(signal)
        if self.allow_remote_api:
            return self._predict_with_remote_api(signal)
        raise RuntimeError(self.warning or f'FPGA {self.kind} chưa sẵn sàng.')

    def _predict_with_remote_api(self, signal: np.ndarray) -> Tuple[str, Dict[str, float], str]:
        payload = {'signal': np.asarray(signal, dtype=np.float32).reshape(-1).tolist()}
        out = _remote_json_request(self.remote_url + '/predict', payload=payload, timeout=max(PYNQ_HLS_REMOTE_TIMEOUT, 10.0))
        if not out.get('ok', False):
            raise RuntimeError(f'PYNQ remote API lỗi: {out.get("error") or out}')
        pred = str(out.get('predicted_label') or out.get('label') or 'N')
        probs_raw = out.get('probabilities') or {}
        probs = {label: float(probs_raw.get(label, 0.0)) for label in LABELS}
        if not any(probs.values()):
            probs[pred if pred in LABELS else 'N'] = 1.0
        note = str(out.get('note') or '')
        note = f'PYNQ remote HLS API {self.remote_url}: ' + note
        if 'hls_compute_ms' in out:
            note += f', remote_hls_compute_ms={float(out.get("hls_compute_ms") or 0.0):.4f}'
        if 'latency_ms' in out:
            note += f', remote_api_latency_ms={float(out.get("latency_ms") or 0.0):.4f}'
        return pred, probs, note

    def _write_pointer64(self, base_offset: int, addr: int) -> None:
        self.ip.write(base_offset, int(addr) & 0xFFFFFFFF)
        self.ip.write(base_offset + 4, (int(addr) >> 32) & 0xFFFFFFFF)

    def _poll_done(self, timeout_s: float = 5.0) -> int:
        start_t = time.perf_counter()
        last_ctrl = 0
        while True:
            last_ctrl = int(self.ip.read(0x00))
            if last_ctrl & 0x2:  # AP_DONE
                return last_ctrl
            if time.perf_counter() - start_t > timeout_s:
                raise RuntimeError(f'FPGA {self.kind} timeout khi chờ AP_DONE. CTRL=0x{last_ctrl:08x}')
            time.sleep(0.0005)

    def _scores_to_probs(self, scores: np.ndarray, pred_idx: int) -> Dict[str, float]:
        scores = np.asarray(scores[:5], dtype=np.float32)
        if np.all(scores == 0):
            probs = np.zeros(5, dtype=np.float32)
            if 0 <= pred_idx < 5:
                probs[pred_idx] = 1.0
        else:
            # HLS thường trả logits Q4.12, nên dequantize trước khi softmax.
            logits = scores / float(Q_SCALE)
            probs = softmax(logits)
        return {LABELS[i]: float(probs[i]) for i in range(5)}

    def _predict_with_pynq(self, signal: np.ndarray) -> Tuple[str, Dict[str, float], str]:
        try:
            from pynq import allocate  # type: ignore
        except Exception as exc:
            raise RuntimeError(f'Không import được pynq.allocate. Cần chạy backend trực tiếp trên board PYNQ-Z2. Lỗi: {exc}')

        q_signal = quantize_q4_12(normalize_signal(signal, SIGNAL_LENGTH))

        # Register map lấy từ design_1.hwh:
        # 0x10/0x14 beat_in_q12 pointer, 0x1c/0x20 pred_class pointer, 0x28/0x2c score5_q12 pointer.
        in_buf = allocate(shape=(SIGNAL_LENGTH,), dtype=np.int16)
        pred_buf = allocate(shape=(1,), dtype=np.int32)
        score_buf = allocate(shape=(8,), dtype=np.int32)
        try:
            in_buf[:] = q_signal.astype(np.int16)
            pred_buf[:] = 0
            score_buf[:] = 0
            in_buf.flush()
            pred_buf.flush()
            score_buf.flush()

            self._write_pointer64(0x10, in_buf.device_address)
            self._write_pointer64(0x1C, pred_buf.device_address)
            self._write_pointer64(0x28, score_buf.device_address)

            self.ip.write(0x00, 0x01)  # AP_START
            self._poll_done(timeout_s=5.0)

            pred_buf.invalidate()
            score_buf.invalidate()

            raw_pred = int(pred_buf[0])
            raw_score_words = np.asarray(score_buf[:5], dtype=np.int32)
            raw_scores, score_meta = decode_hls_score5_q12(raw_score_words)
            pred_idx = raw_pred if 0 <= raw_pred < len(LABELS) else int(np.argmax(raw_scores))
            pred = LABELS[pred_idx] if 0 <= pred_idx < len(LABELS) else 'N'
            probs = self._scores_to_probs(raw_scores, pred_idx)
            note = (
                f'FPGA {self.kind} PYNQ overlay={self.bit_path.name}, ip={getattr(self, "ip_name", "unknown")}, '
                f'pred_class={raw_pred}, score5_q12={raw_scores.tolist()}, '
                f'raw_score_words={raw_score_words.tolist()}, packing={score_meta.get("packing")}'
            )
            return pred, probs, note
        finally:
            # PYNQ Buffer hỗ trợ freebuffer(); nếu không có thì để GC xử lý.
            for buf in (in_buf, pred_buf, score_buf):
                try:
                    buf.freebuffer()
                except Exception:
                    pass


class FpgaHlsQ412Engine(BaseFpgaQ412Engine):
    backend_id = 'fpga_hls_q4_12'

    def __init__(self) -> None:
        super().__init__(
            kind='HLS Q4.12',
            overlay_dir=FPGA_HLS_OVERLAY_DIR,
            bit_names=['ecg_accel_hls.bit', 'ecg_hls_accel.bit', 'ecg_accel.bit'],
            hwh_names=['ecg_accel_hls.hwh', 'ecg_hls_accel.hwh', 'ecg_accel.hwh'],
            legacy_fallback=True,
            report_dir=FPGA_HLS_REPORTS_DIR,
            allow_remote_api=True,
        )


class FpgaRtlQ412Engine(BaseFpgaQ412Engine):
    backend_id = 'fpga_rtl_q4_12'

    def __init__(self) -> None:
        super().__init__(
            kind='RTL Q4.12',
            overlay_dir=FPGA_RTL_OVERLAY_DIR,
            bit_names=['ecg_accel_rtl.bit', 'ecg_rtl_accel.bit', 'ecg_accel.bit'],
            hwh_names=['ecg_accel_rtl.hwh', 'ecg_rtl_accel.hwh', 'ecg_accel.hwh'],
            legacy_fallback=False,
            report_dir=FPGA_RTL_REPORTS_DIR,
        )


FPGA_HLS_ENGINE = FpgaHlsQ412Engine()
FPGA_RTL_ENGINE = FpgaRtlQ412Engine()

ENGINES = {
    'cpu_float32': CpuFloat32Engine(),
    'cpu_q4_12': CpuQ412Engine(),
    'fpga_hls_q4_12': FPGA_HLS_ENGINE,
    'fpga_rtl_q4_12': FPGA_RTL_ENGINE,
}


def get_system_status() -> Dict:
    return {
        'cpu': CPU_MODELS.status(),
        'fpga_hls': FPGA_HLS_ENGINE.status(),
        'fpga_rtl': FPGA_RTL_ENGINE.status(),
    }


def run_prediction(backend: str, signal: np.ndarray, context: Optional[Dict] = None) -> Dict:
    if backend not in ENGINES:
        raise ValueError(f'Unsupported backend: {backend}')

    start = time.perf_counter()
    pred, probs, note = ENGINES[backend].predict(signal, context=context)
    end = time.perf_counter()

    latency_ms = (end - start) * 1000.0
    throughput_sps = 1000.0 / latency_ms if latency_ms > 1e-12 else 0.0
    confidence = float(max(probs.values())) if probs else 0.0

    return {
        'backend': backend,
        'predicted_label': pred,
        'confidence': confidence,
        'probabilities': probs,
        'latency_ms': latency_ms,
        'throughput_sps': throughput_sps,
        'note': note,
    }



def reload_runtime_models() -> Dict:
    global CPU_MODELS, FPGA_HLS_ENGINE, FPGA_RTL_ENGINE, ENGINES
    CPU_MODELS = CpuModelManager()
    FPGA_HLS_ENGINE = FpgaHlsQ412Engine()
    FPGA_RTL_ENGINE = FpgaRtlQ412Engine()
    ENGINES = {
        'cpu_float32': CpuFloat32Engine(),
        'cpu_q4_12': CpuQ412Engine(),
        'fpga_hls_q4_12': FPGA_HLS_ENGINE,
        'fpga_rtl_q4_12': FPGA_RTL_ENGINE,
    }
    return get_system_status()
