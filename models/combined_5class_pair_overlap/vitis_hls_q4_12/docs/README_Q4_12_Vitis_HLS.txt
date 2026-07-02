Combined 5-class + Pair-overlap N/A Refiner - Q4.12 for Vitis HLS
====================================================================================================

File chính:
- combined_q4_12_config.h
- main_5class_q4_12_weights.h
- pair_overlap_refiner_q4_12_weights.h

Include trong Vitis HLS:
#include "combined_q4_12_config.h"
#include "main_5class_q4_12_weights.h"
#include "pair_overlap_refiner_q4_12_weights.h"

Q4.12:
- ap_fixed<16,4>
- scale = 4096
- float ~= int16 / 4096

Lưu ý:
- Đây là weights/config cho HLS, chưa phải code inference C++ hoàn chỉnh.
- Nếu main 5-class là SepResGELU thì không dùng trực tiếp với code HLS cũ mini-inception.
- Nếu cần HLS thật sự dễ build, main 5-class nên là model HLS-compatible.