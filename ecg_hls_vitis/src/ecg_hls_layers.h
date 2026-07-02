#ifndef ECG_HLS_LAYERS_H
#define ECG_HLS_LAYERS_H

#include <stdint.h>
#include "ecg_fpga_top.h"

int16_t clip_i16(int32_t x);

void extract_light_features_40_int(
    const int16_t beat_q12[SEGMENT_LEN],
    int16_t feat_q12[HLS_MAIN_FEAT_DIM]
);

void dense_40x24_relu_int(
    const int16_t in_q12[HLS_MAIN_FEAT_DIM],
    const int16_t *kernel_q12,
    int16_t out_q12[HLS_MAIN_HIDDEN_DIM]
);

void dense_24x5_linear_int(
    const int16_t in_q12[HLS_MAIN_HIDDEN_DIM],
    const int16_t *kernel_q12,
    const int16_t bias_q12[HLS_MAIN_CLASSES],
    int16_t out_q12[HLS_MAIN_CLASSES]
);

int32_t argmax5_int(
    const int16_t score_q12[HLS_MAIN_CLASSES]
);

#endif