SIGNAL_LENGTH = 320
Q_FRAC_BITS = 12
Q_SCALE = 1 << Q_FRAC_BITS
Q_MIN = -32768
Q_MAX = 32767

LABELS = ["N", "L", "R", "V", "A"]

INDEX_TO_LABEL = {
    0: "N",
    1: "L",
    2: "R",
    3: "V",
    4: "A",
}

LABEL_TO_INDEX = {v: k for k, v in INDEX_TO_LABEL.items()}

LABEL_INFO = {
    "N": {
        "name": "Normal beat",
        "vi_name": "Nhịp bình thường",
        "description": "Nhịp bình thường, QRS hẹp và hình thái ổn định."
    },
    "L": {
        "name": "Left bundle branch block beat",
        "vi_name": "Block nhánh trái",
        "description": "QRS thường rộng do dẫn truyền qua nhánh trái bị chậm hoặc bị block."
    },
    "R": {
        "name": "Right bundle branch block beat",
        "vi_name": "Block nhánh phải",
        "description": "QRS rộng hoặc có dạng hai đỉnh do dẫn truyền qua nhánh phải bị chậm."
    },
    "V": {
        "name": "Premature ventricular contraction",
        "vi_name": "Ngoại tâm thu thất",
        "description": "Nhịp đến sớm từ thất, QRS thường rộng, biên độ bất thường."
    },
    "A": {
        "name": "Atrial premature contraction",
        "vi_name": "Ngoại tâm thu nhĩ",
        "description": "Nhịp đến sớm từ nhĩ, QRS thường gần bình thường nhưng chu kỳ nhịp thay đổi."
    },
}

BACKENDS = {
    "cpu_float32": "CPU Float32",
    "cpu_q4_12": "CPU Q4.12",
    "fpga_hls_q4_12": "FPGA HLS Q4.12 / PYNQ-Z2",
    "fpga_rtl_q4_12": "FPGA RTL Q4.12 / PYNQ-Z2",
}
