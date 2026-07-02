#ifndef ECG_FPGA_TOP_H
#define ECG_FPGA_TOP_H

#include <stdint.h>

#define SEGMENT_LEN 320
#define HLS_MAIN_FEAT_DIM 40
#define HLS_MAIN_HIDDEN_DIM 24
#define HLS_MAIN_CLASSES 5

#ifdef __cplusplus
extern "C" {
#endif

void ecg_fpga_top(
    int16_t beat_in_q12[SEGMENT_LEN],
    int32_t pred_class[1],
    int16_t score5_q12[HLS_MAIN_CLASSES]
);

#ifdef __cplusplus
}
#endif

#endif