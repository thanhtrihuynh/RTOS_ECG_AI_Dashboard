#ifndef COMBINED_Q4_12_CONFIG_H
#define COMBINED_Q4_12_CONFIG_H

#include <stdint.h>
#include <ap_fixed.h>

typedef ap_fixed<16, 4> q4_12_t;
typedef ap_fixed<32, 16> q16_16_t;

#define Q4_12_TOTAL_BITS 16
#define Q4_12_INT_BITS 4
#define Q4_12_FRAC_BITS 12
#define Q4_12_SCALE 4096

#define SEGMENT_LEN 320
#define OVERLAP_LEN 160
#define PAIR_FEATURE_DIM 15

#define CLASS_N 0
#define CLASS_L 1
#define CLASS_R 2
#define CLASS_V 3
#define CLASS_A 4

#define NA_N 0
#define NA_A 1

static inline q4_12_t q12_to_fixed(int16_t v)
{
    return ((q4_12_t)v) / ((q4_12_t)4096);
}

static inline q16_16_t q16_to_fixed(int32_t v)
{
    return ((q16_16_t)v) / ((q16_16_t)65536);
}

// Thresholds pair-overlap combine
#define PAIR_LEFT_A_THRESHOLD_FLOAT 0.845f
#define PAIR_RIGHT_A_THRESHOLD_FLOAT 0.735f
#define PAIR_OVERLAP_THRESHOLD_N_FLOAT 0.2f
#define PAIR_OVERLAP_THRESHOLD_A_FLOAT 0.85f

#define PAIR_LEFT_A_THRESHOLD_Q12 3461
#define PAIR_RIGHT_A_THRESHOLD_Q12 3011
#define PAIR_OVERLAP_THRESHOLD_N_Q12 819
#define PAIR_OVERLAP_THRESHOLD_A_Q12 3482

static const float PAIR_FEATURE_MEAN_FLOAT[PAIR_FEATURE_DIM] = {
    352.777008f, 247.61586f, 348.830231f, 1.30694556f, 0.917894959f, 1.29205358f, 1.30694556f, 0.917894959f,
    0.917894959f, 1.29205358f, -0.389042914f, 0.374153256f, 273.277008f, 72.38414f, 0.226200819f
};

static const float PAIR_FEATURE_STD_FLOAT[PAIR_FEATURE_DIM] = {
    186.613403f, 39.7615776f, 187.316864f, 0.686276257f, 0.130610079f, 0.68925947f, 0.686276257f, 0.130610079f,
    0.130610079f, 0.68925947f, 0.674870908f, 0.679543674f, 47.1010399f, 39.7615776f, 0.124254517f
};

static const int32_t PAIR_FEATURE_MEAN_Q16[PAIR_FEATURE_DIM] = {
    23119594, 16227753, 22860938, 85652, 60155, 84676, 85652, 60155,
    60155, 84676, -25496, 24521, 17909482, 4743767, 14824
};

static const int32_t PAIR_FEATURE_STD_Q16[PAIR_FEATURE_DIM] = {
    12229896, 2605815, 12275998, 44976, 8560, 45171, 44976, 8560,
    8560, 45171, 44228, 44535, 3086814, 2605815, 8143
};

// Feature order:
// 0: rr_before_left_samples
// 1: rr_between_samples
// 2: rr_after_right_samples
// 3: rr_before_left_norm
// 4: rr_between_norm
// 5: rr_after_right_norm
// 6: left_prematurity
// 7: right_prematurity
// 8: left_post_pause
// 9: right_post_pause
// 10: left_pause_minus_pre
// 11: right_pause_minus_pre
// 12: median_rr_record
// 13: overlap_width
// 14: overlap_ratio

#endif