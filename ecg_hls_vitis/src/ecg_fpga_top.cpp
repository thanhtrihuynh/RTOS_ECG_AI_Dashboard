#include "ecg_fpga_top.h"
#include "ecg_hls_layers.h"
#include "main5_dense_only_q4_12_weights.h"

void ecg_fpga_top(
    int16_t beat_in_q12[SEGMENT_LEN],
    int32_t pred_class[1],
    int16_t score5_q12[HLS_MAIN_CLASSES]
)
{
#pragma HLS INTERFACE m_axi     port=beat_in_q12 offset=slave bundle=gmem0 depth=320
#pragma HLS INTERFACE m_axi     port=pred_class  offset=slave bundle=gmem1 depth=1
#pragma HLS INTERFACE m_axi     port=score5_q12  offset=slave bundle=gmem2 depth=5

#pragma HLS INTERFACE s_axilite port=beat_in_q12 bundle=CTRL
#pragma HLS INTERFACE s_axilite port=pred_class  bundle=CTRL
#pragma HLS INTERFACE s_axilite port=score5_q12  bundle=CTRL
#pragma HLS INTERFACE s_axilite port=return      bundle=CTRL

    int16_t beat_local[SEGMENT_LEN];
    int16_t feat_q12[HLS_MAIN_FEAT_DIM];
    int16_t hidden_q12[HLS_MAIN_HIDDEN_DIM];
    int16_t score_q12[HLS_MAIN_CLASSES];

#pragma HLS ARRAY_PARTITION variable=feat_q12 complete dim=1
#pragma HLS ARRAY_PARTITION variable=hidden_q12 complete dim=1
#pragma HLS ARRAY_PARTITION variable=score_q12 complete dim=1

    for (int i = 0; i < SEGMENT_LEN; i++) {
#pragma HLS PIPELINE II=1
        beat_local[i] = beat_in_q12[i];
    }

    extract_light_features_40_int(beat_local, feat_q12);

    dense_40x24_relu_int(
        feat_q12,
        (const int16_t *)main5_dense_kernel,
        hidden_q12
    );

    dense_24x5_linear_int(
        hidden_q12,
        (const int16_t *)main5_class_output_kernel,
        main5_class_output_bias,
        score_q12
    );

    pred_class[0] = argmax5_int(score_q12);

    for (int i = 0; i < HLS_MAIN_CLASSES; i++) {
#pragma HLS PIPELINE II=1
        score5_q12[i] = score_q12[i];
    }
}