#include "ecg_hls_layers.h"

int16_t clip_i16(int32_t x)
{
#pragma HLS INLINE
    if (x > 32767) return 32767;
    if (x < -32768) return -32768;
    return (int16_t)x;
}

static int16_t relu_i16(int16_t x)
{
#pragma HLS INLINE
    return (x > 0) ? x : 0;
}

static int16_t abs_i16_safe(int16_t x)
{
#pragma HLS INLINE
    if (x == -32768) return 32767;
    return (x < 0) ? (int16_t)(-x) : x;
}

static int16_t abs_diff_i16(int16_t a, int16_t b)
{
#pragma HLS INLINE
    int32_t d = (int32_t)a - (int32_t)b;
    if (d < 0) d = -d;
    return clip_i16(d);
}

static int32_t q12_mul(int16_t a, int16_t b)
{
#pragma HLS INLINE
    int32_t p = (int32_t)a * (int32_t)b;

    if (p >= 0) {
        return (p + 2048) >> 12;
    } else {
        return -(((-p) + 2048) >> 12);
    }
}

void extract_light_features_40_int(
    const int16_t beat_q12[SEGMENT_LEN],
    int16_t feat_q12[HLS_MAIN_FEAT_DIM]
)
{
    const int BLOCKS = 8;
    const int BLOCK_LEN = 40;

    for (int b = 0; b < BLOCKS; b++) {
        int start = b * BLOCK_LEN;

        int32_t sum = 0;
        int32_t sum_abs = 0;
        int32_t sum_abs_diff = 0;

        int16_t mx = beat_q12[start];
        int16_t mn = beat_q12[start];

        for (int i = 0; i < BLOCK_LEN; i++) {
#pragma HLS PIPELINE II=1
            int16_t v = beat_q12[start + i];

            sum += (int32_t)v;
            sum_abs += (int32_t)abs_i16_safe(v);

            if (v > mx) mx = v;
            if (v < mn) mn = v;

            if (i > 0) {
                int16_t prev = beat_q12[start + i - 1];
                sum_abs_diff += (int32_t)abs_diff_i16(v, prev);
            }
        }

        int16_t mean_q12 = clip_i16(sum / BLOCK_LEN);
        int16_t mean_abs_q12 = clip_i16(sum_abs / BLOCK_LEN);
        int16_t mean_abs_diff_q12 = clip_i16(sum_abs_diff / (BLOCK_LEN - 1));
        int16_t amp_q12 = clip_i16((int32_t)mx - (int32_t)mn);

        feat_q12[b * 5 + 0] = mean_q12;
        feat_q12[b * 5 + 1] = mx;
        feat_q12[b * 5 + 2] = mn;
        feat_q12[b * 5 + 3] = mean_abs_q12;
        feat_q12[b * 5 + 4] = mean_abs_diff_q12;
    }
}

void dense_40x24_relu_int(
    const int16_t in_q12[HLS_MAIN_FEAT_DIM],
    const int16_t *kernel_q12,
    int16_t out_q12[HLS_MAIN_HIDDEN_DIM]
)
{
    for (int j = 0; j < HLS_MAIN_HIDDEN_DIM; j++) {
#pragma HLS PIPELINE II=1
        int32_t acc = 0;

        for (int i = 0; i < HLS_MAIN_FEAT_DIM; i++) {
            int16_t w = kernel_q12[i * HLS_MAIN_HIDDEN_DIM + j];
            acc += q12_mul(in_q12[i], w);
        }

        out_q12[j] = relu_i16(clip_i16(acc));
    }
}

void dense_24x5_linear_int(
    const int16_t in_q12[HLS_MAIN_HIDDEN_DIM],
    const int16_t *kernel_q12,
    const int16_t bias_q12[HLS_MAIN_CLASSES],
    int16_t out_q12[HLS_MAIN_CLASSES]
)
{
    for (int j = 0; j < HLS_MAIN_CLASSES; j++) {
#pragma HLS PIPELINE II=1
        int32_t acc = (int32_t)bias_q12[j];

        for (int i = 0; i < HLS_MAIN_HIDDEN_DIM; i++) {
            int16_t w = kernel_q12[i * HLS_MAIN_CLASSES + j];
            acc += q12_mul(in_q12[i], w);
        }

        out_q12[j] = clip_i16(acc);
    }
}

int32_t argmax5_int(
    const int16_t score_q12[HLS_MAIN_CLASSES]
)
{
    int32_t best_idx = 0;
    int16_t best_val = score_q12[0];

    for (int i = 1; i < HLS_MAIN_CLASSES; i++) {
        if (score_q12[i] > best_val) {
            best_val = score_q12[i];
            best_idx = i;
        }
    }

    return best_idx;
}