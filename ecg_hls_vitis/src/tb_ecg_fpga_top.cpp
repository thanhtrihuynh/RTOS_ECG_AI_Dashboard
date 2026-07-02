#include <iostream>
#include <stdint.h>
#include "ecg_fpga_top.h"

int main()
{
    int16_t beat_in_q12[SEGMENT_LEN];
    int32_t pred_class[1];
    int16_t score5_q12[HLS_MAIN_CLASSES];

    for (int i = 0; i < SEGMENT_LEN; i++) {
        int center = SEGMENT_LEN / 2;
        int d = i - center;
        int ad = d >= 0 ? d : -d;
        int q = 0;

        if (ad <= 3) {
            q = 4096 - ad * 700;
        }

        beat_in_q12[i] = (int16_t)q;
    }

    pred_class[0] = -1;
    for (int i = 0; i < HLS_MAIN_CLASSES; i++) {
        score5_q12[i] = 0;
    }

    std::cout << "TB_START" << std::endl;

    ecg_fpga_top(beat_in_q12, pred_class, score5_q12);

    std::cout << "pred_class = " << pred_class[0] << std::endl;
    std::cout << "score5_q12 = ";

    for (int i = 0; i < HLS_MAIN_CLASSES; i++) {
        std::cout << score5_q12[i] << " ";
    }

    std::cout << std::endl;

    if (pred_class[0] < 0 || pred_class[0] > 4) {
        std::cout << "TB_ERROR: pred_class out of range" << std::endl;
        return 1;
    }

    std::cout << "TB_PASS" << std::endl;
    return 0;
}
