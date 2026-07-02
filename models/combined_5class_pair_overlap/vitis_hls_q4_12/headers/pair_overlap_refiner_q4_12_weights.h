#ifndef PAIR_OVERLAP_REFINER_Q4_12_WEIGHTS_H
#define PAIR_OVERLAP_REFINER_Q4_12_WEIGHTS_H

#include <stdint.h>
#include "combined_q4_12_config.h"

// Pair-overlap N/A refiner weights Q4.12
// Q4.12: float ~= int16 / 4096

// ---------------------------------------------------------
// index: 0
// raw_name: shared_beat_sepconv0/depthwise_kernel
// c_name: pair_shared_beat_sepconv0_depthwise_kernel
// shape: [7, 1, 1]
// numel: 7
// float_min: -0.5718913078308105
// float_max: 0.37100112438201904
// q_min: -2342
// q_max: 1520
// max_abs_error: 0.00011829286813735962
// mean_abs_error: 7.882608042564243e-05
// ---------------------------------------------------------
#define PAIR_SHARED_BEAT_SEPCONV0_DEPTHWISE_KERNEL_NUMEL 7
#define PAIR_SHARED_BEAT_SEPCONV0_DEPTHWISE_KERNEL_DIM0 7
#define PAIR_SHARED_BEAT_SEPCONV0_DEPTHWISE_KERNEL_DIM1 1
#define PAIR_SHARED_BEAT_SEPCONV0_DEPTHWISE_KERNEL_DIM2 1
static const int16_t pair_shared_beat_sepconv0_depthwise_kernel[7] = {
    125, 1520, -1001, -715, -553, -2342, -517
};

// ---------------------------------------------------------
// index: 1
// raw_name: shared_beat_sepconv0/pointwise_kernel
// c_name: pair_shared_beat_sepconv0_pointwise_kernel
// shape: [1, 1, 6]
// numel: 6
// float_min: -0.8211854696273804
// float_max: 0.9254674315452576
// q_min: -3364
// q_max: 3791
// max_abs_error: 0.0001035928726196289
// mean_abs_error: 6.482998287538067e-05
// ---------------------------------------------------------
#define PAIR_SHARED_BEAT_SEPCONV0_POINTWISE_KERNEL_NUMEL 6
#define PAIR_SHARED_BEAT_SEPCONV0_POINTWISE_KERNEL_DIM0 1
#define PAIR_SHARED_BEAT_SEPCONV0_POINTWISE_KERNEL_DIM1 1
#define PAIR_SHARED_BEAT_SEPCONV0_POINTWISE_KERNEL_DIM2 6
static const int16_t pair_shared_beat_sepconv0_pointwise_kernel[6] = {
    3027, 2402, -2689, 1069, -3364, 3791
};

// ---------------------------------------------------------
// index: 2
// raw_name: shared_beat_bn0/gamma
// c_name: pair_shared_beat_bn0_gamma
// shape: [6]
// numel: 6
// float_min: 0.9709271192550659
// float_max: 1.0574043989181519
// q_min: 3977
// q_max: 4331
// max_abs_error: 4.029273986816406e-05
// mean_abs_error: 2.298752406204585e-05
// ---------------------------------------------------------
#define PAIR_SHARED_BEAT_BN0_GAMMA_NUMEL 6
#define PAIR_SHARED_BEAT_BN0_GAMMA_DIM0 6
static const int16_t pair_shared_beat_bn0_gamma[6] = {
    3977, 4331, 4113, 4055, 3998, 4273
};

// ---------------------------------------------------------
// index: 3
// raw_name: shared_beat_bn0/beta
// c_name: pair_shared_beat_bn0_beta
// shape: [6]
// numel: 6
// float_min: -0.28171494603157043
// float_max: 0.0735817402601242
// q_min: -1154
// q_max: 301
// max_abs_error: 0.00011198222637176514
// mean_abs_error: 6.148467218736187e-05
// ---------------------------------------------------------
#define PAIR_SHARED_BEAT_BN0_BETA_NUMEL 6
#define PAIR_SHARED_BEAT_BN0_BETA_DIM0 6
static const int16_t pair_shared_beat_bn0_beta[6] = {
    -1154, -70, -140, -69, 301, -209
};

// ---------------------------------------------------------
// index: 4
// raw_name: shared_beat_bn0/moving_mean
// c_name: pair_shared_beat_bn0_moving_mean
// shape: [6]
// numel: 6
// float_min: -0.00026872099260799587
// float_max: 0.00023819744819775224
// q_min: -1
// q_max: 1
// max_abs_error: 7.590132008772343e-05
// mean_abs_error: 4.414555223775096e-05
// ---------------------------------------------------------
#define PAIR_SHARED_BEAT_BN0_MOVING_MEAN_NUMEL 6
#define PAIR_SHARED_BEAT_BN0_MOVING_MEAN_DIM0 6
static const int16_t pair_shared_beat_bn0_moving_mean[6] = {
    -1, -1, 1, 0, 1, -1
};

// ---------------------------------------------------------
// index: 5
// raw_name: shared_beat_bn0/moving_variance
// c_name: pair_shared_beat_bn0_moving_variance
// shape: [6]
// numel: 6
// float_min: 0.056207429617643356
// float_max: 0.7044085264205933
// q_min: 230
// q_max: 2885
// max_abs_error: 0.00010663270950317383
// mean_abs_error: 5.06260730617214e-05
// ---------------------------------------------------------
#define PAIR_SHARED_BEAT_BN0_MOVING_VARIANCE_NUMEL 6
#define PAIR_SHARED_BEAT_BN0_MOVING_VARIANCE_DIM0 6
static const int16_t pair_shared_beat_bn0_moving_variance[6] = {
    1837, 1148, 1445, 230, 2268, 2885
};

// ---------------------------------------------------------
// index: 6
// raw_name: shared_beat_sepconv1/depthwise_kernel
// c_name: pair_shared_beat_sepconv1_depthwise_kernel
// shape: [5, 6, 1]
// numel: 30
// float_min: -0.3870600759983063
// float_max: 0.42338863015174866
// q_min: -1585
// q_max: 1734
// max_abs_error: 0.00011960510164499283
// mean_abs_error: 5.476856676978059e-05
// ---------------------------------------------------------
#define PAIR_SHARED_BEAT_SEPCONV1_DEPTHWISE_KERNEL_NUMEL 30
#define PAIR_SHARED_BEAT_SEPCONV1_DEPTHWISE_KERNEL_DIM0 5
#define PAIR_SHARED_BEAT_SEPCONV1_DEPTHWISE_KERNEL_DIM1 6
#define PAIR_SHARED_BEAT_SEPCONV1_DEPTHWISE_KERNEL_DIM2 1
static const int16_t pair_shared_beat_sepconv1_depthwise_kernel[30] = {
    -1297, 103, 162, -285, -1284, -595, -119, -1143, -1585, -1019, -1161, -1180, 1012, -1077, -1268, 1481,
    319, 461, -428, 1734, -1095, 1625, 391, -69, 593, -1167, -1259, 418, -481, 57
};

// ---------------------------------------------------------
// index: 7
// raw_name: shared_beat_sepconv1/pointwise_kernel
// c_name: pair_shared_beat_sepconv1_pointwise_kernel
// shape: [1, 6, 10]
// numel: 60
// float_min: -0.6400548219680786
// float_max: 0.5798486471176147
// q_min: -2622
// q_max: 2375
// max_abs_error: 0.00011858344078063965
// mean_abs_error: 5.6888224207796156e-05
// ---------------------------------------------------------
#define PAIR_SHARED_BEAT_SEPCONV1_POINTWISE_KERNEL_NUMEL 60
#define PAIR_SHARED_BEAT_SEPCONV1_POINTWISE_KERNEL_DIM0 1
#define PAIR_SHARED_BEAT_SEPCONV1_POINTWISE_KERNEL_DIM1 6
#define PAIR_SHARED_BEAT_SEPCONV1_POINTWISE_KERNEL_DIM2 10
static const int16_t pair_shared_beat_sepconv1_pointwise_kernel[60] = {
    81, -1421, -1126, 2110, 183, -63, -1111, 1618, -1911, -2622, 444, -1183, -1778, 2041, -1739, 741,
    -2185, -602, 1387, 59, 385, -1861, 996, 422, 459, -1713, -2110, -2529, -421, -805, 1752, 954,
    683, 2375, -1019, 429, 153, 866, 967, -1537, -1188, 367, -896, -178, 2285, 2192, -116, -180,
    -517, 143, -2117, 2139, -72, 1107, -780, -1534, -955, 1743, 1475, -1423
};

// ---------------------------------------------------------
// index: 8
// raw_name: shared_beat_bn1/gamma
// c_name: pair_shared_beat_bn1_gamma
// shape: [10]
// numel: 10
// float_min: 0.9230905175209045
// float_max: 1.0807369947433472
// q_min: 3781
// q_max: 4427
// max_abs_error: 8.606910705566406e-05
// mean_abs_error: 5.7941673730965704e-05
// ---------------------------------------------------------
#define PAIR_SHARED_BEAT_BN1_GAMMA_NUMEL 10
#define PAIR_SHARED_BEAT_BN1_GAMMA_DIM0 10
static const int16_t pair_shared_beat_bn1_gamma[10] = {
    4068, 3781, 4164, 3967, 4354, 4058, 4138, 4272, 4088, 4427
};

// ---------------------------------------------------------
// index: 9
// raw_name: shared_beat_bn1/beta
// c_name: pair_shared_beat_bn1_beta
// shape: [10]
// numel: 10
// float_min: -0.06808794289827347
// float_max: 0.027400018647313118
// q_min: -279
// q_max: 112
// max_abs_error: 0.0001158127561211586
// mean_abs_error: 5.596406845143065e-05
// ---------------------------------------------------------
#define PAIR_SHARED_BEAT_BN1_BETA_NUMEL 10
#define PAIR_SHARED_BEAT_BN1_BETA_DIM0 10
static const int16_t pair_shared_beat_bn1_beta[10] = {
    -38, 10, 50, 112, 46, -279, -224, -76, -16, -1
};

// ---------------------------------------------------------
// index: 10
// raw_name: shared_beat_bn1/moving_mean
// c_name: pair_shared_beat_bn1_moving_mean
// shape: [10]
// numel: 10
// float_min: -0.12942354381084442
// float_max: 0.32310476899147034
// q_min: -530
// q_max: 1323
// max_abs_error: 0.00010672211647033691
// mean_abs_error: 3.985930379712954e-05
// ---------------------------------------------------------
#define PAIR_SHARED_BEAT_BN1_MOVING_MEAN_NUMEL 10
#define PAIR_SHARED_BEAT_BN1_MOVING_MEAN_DIM0 10
static const int16_t pair_shared_beat_bn1_moving_mean[10] = {
    537, 821, 131, -125, -530, 402, 1323, 1130, 140, 207
};

// ---------------------------------------------------------
// index: 11
// raw_name: shared_beat_bn1/moving_variance
// c_name: pair_shared_beat_bn1_moving_variance
// shape: [10]
// numel: 10
// float_min: 0.03878337889909744
// float_max: 0.4158996045589447
// q_min: 159
// q_max: 1704
// max_abs_error: 0.00011602044105529785
// mean_abs_error: 6.012879384797998e-05
// ---------------------------------------------------------
#define PAIR_SHARED_BEAT_BN1_MOVING_VARIANCE_NUMEL 10
#define PAIR_SHARED_BEAT_BN1_MOVING_VARIANCE_DIM0 10
static const int16_t pair_shared_beat_bn1_moving_variance[10] = {
    187, 756, 242, 255, 652, 511, 1057, 1704, 159, 240
};

// ---------------------------------------------------------
// index: 12
// raw_name: shared_beat_embed/kernel
// c_name: pair_shared_beat_embed_kernel
// shape: [20, 10]
// numel: 200
// float_min: -0.4831811189651489
// float_max: 0.5245717167854309
// q_min: -1979
// q_max: 2149
// max_abs_error: 0.00012201070785522461
// mean_abs_error: 5.927262827754021e-05
// ---------------------------------------------------------
#define PAIR_SHARED_BEAT_EMBED_KERNEL_NUMEL 200
#define PAIR_SHARED_BEAT_EMBED_KERNEL_DIM0 20
#define PAIR_SHARED_BEAT_EMBED_KERNEL_DIM1 10
static const int16_t pair_shared_beat_embed_kernel[200] = {
    -992, 634, -110, -1283, -361, -10, 1602, -1345, -118, 220, 226, -1830, 129, -570, 1407, -946,
    639, -1566, -1094, 11, -931, -1834, -444, 685, 1316, -1534, 117, 1221, 236, -1666, 664, -141,
    1599, 1830, 467, -354, 1072, -1596, 1253, -915, 150, -754, 1167, 760, 1061, -1484, -532, 374,
    774, 1661, -765, -1409, -1317, 45, -1743, -757, 129, 428, 1513, -451, 32, -833, 156, 891,
    -587, -1417, 1203, -1348, -198, 26, 1580, 1229, -693, 1879, 891, 83, -361, -501, 1882, 604,
    237, 1726, 1478, -1571, -1226, -897, -1007, 452, 1570, 899, -615, -1602, 252, 616, 1279, 1404,
    1384, -828, -1261, -853, 539, 922, 64, 342, -1853, -369, 584, -1477, 880, -314, 789, 318,
    -1256, 1145, -1742, -1776, 205, -135, 208, -301, -959, 68, 1455, 1867, -111, -1431, -114, -1569,
    1239, -996, -230, 727, -1282, -1663, 26, -522, -1344, 537, 143, -1495, 1512, -593, -185, -603,
    1625, 1166, 444, 834, 133, 961, 1208, 712, -279, 982, 560, 1548, -1530, 1017, -856, 1445,
    -1640, 1058, -235, 330, 698, -1594, 605, 966, -1094, 1573, -1467, 608, 858, -1352, -1893, 182,
    -1485, 780, 1232, 1981, -440, -1195, 1651, 1536, 1377, -1343, 420, -1490, 657, -29, -1505, -1465,
    -353, -527, -462, -360, -1827, -986, -1979, 2149
};

// ---------------------------------------------------------
// index: 13
// raw_name: shared_beat_embed/bias
// c_name: pair_shared_beat_embed_bias
// shape: [10]
// numel: 10
// float_min: -0.03295345976948738
// float_max: 0.02373729646205902
// q_min: -135
// q_max: 97
// max_abs_error: 7.15162605047226e-05
// mean_abs_error: 2.5496014131931588e-05
// ---------------------------------------------------------
#define PAIR_SHARED_BEAT_EMBED_BIAS_NUMEL 10
#define PAIR_SHARED_BEAT_EMBED_BIAS_DIM0 10
static const int16_t pair_shared_beat_embed_bias[10] = {
    0, -83, 39, -135, -100, 0, 0, -85, 97, -8
};

// ---------------------------------------------------------
// index: 14
// raw_name: overlap_sepconv0/depthwise_kernel
// c_name: pair_overlap_sepconv0_depthwise_kernel
// shape: [5, 1, 1]
// numel: 5
// float_min: -0.36097314953804016
// float_max: 0.6273908019065857
// q_min: -1479
// q_max: 2570
// max_abs_error: 0.00012052059173583984
// mean_abs_error: 8.04997980594635e-05
// ---------------------------------------------------------
#define PAIR_OVERLAP_SEPCONV0_DEPTHWISE_KERNEL_NUMEL 5
#define PAIR_OVERLAP_SEPCONV0_DEPTHWISE_KERNEL_DIM0 5
#define PAIR_OVERLAP_SEPCONV0_DEPTHWISE_KERNEL_DIM1 1
#define PAIR_OVERLAP_SEPCONV0_DEPTHWISE_KERNEL_DIM2 1
static const int16_t pair_overlap_sepconv0_depthwise_kernel[5] = {
    1771, 2570, 94, -1479, 2466
};

// ---------------------------------------------------------
// index: 15
// raw_name: overlap_sepconv0/pointwise_kernel
// c_name: pair_overlap_sepconv0_pointwise_kernel
// shape: [1, 1, 4]
// numel: 4
// float_min: -0.8816912174224854
// float_max: 0.8336542844772339
// q_min: -3611
// q_max: 3415
// max_abs_error: 9.942054748535156e-05
// mean_abs_error: 6.81428937241435e-05
// ---------------------------------------------------------
#define PAIR_OVERLAP_SEPCONV0_POINTWISE_KERNEL_NUMEL 4
#define PAIR_OVERLAP_SEPCONV0_POINTWISE_KERNEL_DIM0 1
#define PAIR_OVERLAP_SEPCONV0_POINTWISE_KERNEL_DIM1 1
#define PAIR_OVERLAP_SEPCONV0_POINTWISE_KERNEL_DIM2 4
static const int16_t pair_overlap_sepconv0_pointwise_kernel[4] = {
    -20, 3415, -2002, -3611
};

// ---------------------------------------------------------
// index: 16
// raw_name: overlap_bn0/gamma
// c_name: pair_overlap_bn0_gamma
// shape: [4]
// numel: 4
// float_min: 0.9606901407241821
// float_max: 1.006957769393921
// q_min: 3935
// q_max: 4124
// max_abs_error: 0.00012183189392089844
// mean_abs_error: 6.316602230072021e-05
// ---------------------------------------------------------
#define PAIR_OVERLAP_BN0_GAMMA_NUMEL 4
#define PAIR_OVERLAP_BN0_GAMMA_DIM0 4
static const int16_t pair_overlap_bn0_gamma[4] = {
    3935, 4060, 4099, 4124
};

// ---------------------------------------------------------
// index: 17
// raw_name: overlap_bn0/beta
// c_name: pair_overlap_bn0_beta
// shape: [4]
// numel: 4
// float_min: -0.07690353691577911
// float_max: 0.08021188527345657
// q_min: -315
// q_max: 329
// max_abs_error: 0.00011038035154342651
// mean_abs_error: 4.16254042647779e-05
// ---------------------------------------------------------
#define PAIR_OVERLAP_BN0_BETA_NUMEL 4
#define PAIR_OVERLAP_BN0_BETA_DIM0 4
static const int16_t pair_overlap_bn0_beta[4] = {
    310, -9, -315, 329
};

// ---------------------------------------------------------
// index: 18
// raw_name: overlap_bn0/moving_mean
// c_name: pair_overlap_bn0_moving_mean
// shape: [4]
// numel: 4
// float_min: -0.003764620516449213
// float_max: 0.0035531858447939157
// q_min: -15
// q_max: 15
// max_abs_error: 0.00011610891669988632
// mean_abs_error: 8.560926653444767e-05
// ---------------------------------------------------------
#define PAIR_OVERLAP_BN0_MOVING_MEAN_NUMEL 4
#define PAIR_OVERLAP_BN0_MOVING_MEAN_DIM0 4
static const int16_t pair_overlap_bn0_moving_mean[4] = {
    0, 15, -9, -15
};

// ---------------------------------------------------------
// index: 19
// raw_name: overlap_bn0/moving_variance
// c_name: pair_overlap_bn0_moving_variance
// shape: [4]
// numel: 4
// float_min: 1.9296465325169265e-05
// float_max: 1.20319402217865
// q_min: 0
// q_max: 4928
// max_abs_error: 6.902217864990234e-05
// mean_abs_error: 4.967661152477376e-05
// ---------------------------------------------------------
#define PAIR_OVERLAP_BN0_MOVING_VARIANCE_NUMEL 4
#define PAIR_OVERLAP_BN0_MOVING_VARIANCE_DIM0 4
static const int16_t pair_overlap_bn0_moving_variance[4] = {
    0, 4391, 1506, 4928
};

// ---------------------------------------------------------
// index: 20
// raw_name: overlap_sepconv1/depthwise_kernel
// c_name: pair_overlap_sepconv1_depthwise_kernel
// shape: [3, 4, 1]
// numel: 12
// float_min: -0.5375675559043884
// float_max: 0.5186855792999268
// q_min: -2202
// q_max: 2125
// max_abs_error: 0.0001156926155090332
// mean_abs_error: 5.536588651011698e-05
// ---------------------------------------------------------
#define PAIR_OVERLAP_SEPCONV1_DEPTHWISE_KERNEL_NUMEL 12
#define PAIR_OVERLAP_SEPCONV1_DEPTHWISE_KERNEL_DIM0 3
#define PAIR_OVERLAP_SEPCONV1_DEPTHWISE_KERNEL_DIM1 4
#define PAIR_OVERLAP_SEPCONV1_DEPTHWISE_KERNEL_DIM2 1
static const int16_t pair_overlap_sepconv1_depthwise_kernel[12] = {
    1885, -2202, 941, -1770, 2097, -340, -1825, 2125, 2046, -436, -2071, 598
};

// ---------------------------------------------------------
// index: 21
// raw_name: overlap_sepconv1/pointwise_kernel
// c_name: pair_overlap_sepconv1_pointwise_kernel
// shape: [1, 4, 6]
// numel: 24
// float_min: -0.7288094162940979
// float_max: 0.7979580760002136
// q_min: -2985
// q_max: 3268
// max_abs_error: 0.00012010335922241211
// mean_abs_error: 7.618249946972355e-05
// ---------------------------------------------------------
#define PAIR_OVERLAP_SEPCONV1_POINTWISE_KERNEL_NUMEL 24
#define PAIR_OVERLAP_SEPCONV1_POINTWISE_KERNEL_DIM0 1
#define PAIR_OVERLAP_SEPCONV1_POINTWISE_KERNEL_DIM1 4
#define PAIR_OVERLAP_SEPCONV1_POINTWISE_KERNEL_DIM2 6
static const int16_t pair_overlap_sepconv1_pointwise_kernel[24] = {
    -897, -606, 2881, -2985, 2596, 1990, 788, 2610, -273, 2438, 522, 2266, 3268, -889, 3015, -2935,
    -1112, -2196, -2599, -157, -1312, 1342, 1223, -1687
};

// ---------------------------------------------------------
// index: 22
// raw_name: overlap_bn1/gamma
// c_name: pair_overlap_bn1_gamma
// shape: [6]
// numel: 6
// float_min: 0.9639825820922852
// float_max: 1.0685731172561646
// q_min: 3948
// q_max: 4377
// max_abs_error: 0.00011742115020751953
// mean_abs_error: 6.316105282166973e-05
// ---------------------------------------------------------
#define PAIR_OVERLAP_BN1_GAMMA_NUMEL 6
#define PAIR_OVERLAP_BN1_GAMMA_DIM0 6
static const int16_t pair_overlap_bn1_gamma[6] = {
    3948, 4029, 4178, 4377, 4376, 4080
};

// ---------------------------------------------------------
// index: 23
// raw_name: overlap_bn1/beta
// c_name: pair_overlap_bn1_beta
// shape: [6]
// numel: 6
// float_min: -0.020178362727165222
// float_max: 0.05467938259243965
// q_min: -83
// q_max: 224
// max_abs_error: 9.915977716445923e-05
// mean_abs_error: 5.773268640041351e-05
// ---------------------------------------------------------
#define PAIR_OVERLAP_BN1_BETA_NUMEL 6
#define PAIR_OVERLAP_BN1_BETA_DIM0 6
static const int16_t pair_overlap_bn1_beta[6] = {
    -83, 138, 224, 43, 217, -77
};

// ---------------------------------------------------------
// index: 24
// raw_name: overlap_bn1/moving_mean
// c_name: pair_overlap_bn1_moving_mean
// shape: [6]
// numel: 6
// float_min: -0.417586088180542
// float_max: 0.17593646049499512
// q_min: -1710
// q_max: 721
// max_abs_error: 0.00011177361011505127
// mean_abs_error: 8.854852057993412e-05
// ---------------------------------------------------------
#define PAIR_OVERLAP_BN1_MOVING_MEAN_NUMEL 6
#define PAIR_OVERLAP_BN1_MOVING_MEAN_DIM0 6
static const int16_t pair_overlap_bn1_moving_mean[6] = {
    -1710, -690, -532, -218, 721, 13
};

// ---------------------------------------------------------
// index: 25
// raw_name: overlap_bn1/moving_variance
// c_name: pair_overlap_bn1_moving_variance
// shape: [6]
// numel: 6
// float_min: 0.08261556923389435
// float_max: 0.20479851961135864
// q_min: 338
// q_max: 839
// max_abs_error: 0.00010055303573608398
// mean_abs_error: 7.490316784242168e-05
// ---------------------------------------------------------
#define PAIR_OVERLAP_BN1_MOVING_VARIANCE_NUMEL 6
#define PAIR_OVERLAP_BN1_MOVING_VARIANCE_DIM0 6
static const int16_t pair_overlap_bn1_moving_variance[6] = {
    839, 404, 386, 839, 338, 672
};

// ---------------------------------------------------------
// index: 26
// raw_name: overlap_embed/kernel
// c_name: pair_overlap_embed_kernel
// shape: [12, 6]
// numel: 72
// float_min: -0.5753189325332642
// float_max: 0.6204664707183838
// q_min: -2357
// q_max: 2541
// max_abs_error: 0.00012063980102539062
// mean_abs_error: 6.852274236734957e-05
// ---------------------------------------------------------
#define PAIR_OVERLAP_EMBED_KERNEL_NUMEL 72
#define PAIR_OVERLAP_EMBED_KERNEL_DIM0 12
#define PAIR_OVERLAP_EMBED_KERNEL_DIM1 6
static const int16_t pair_overlap_embed_kernel[72] = {
    -1518, -681, -1162, 82, 601, -562, -1969, -2357, -398, -358, -525, -285, -778, -616, -2101, 1068,
    -806, -4, 2503, -1616, -2183, 1432, -1365, 262, 1805, -1123, 2209, 646, -577, 1491, 296, 581,
    -1799, -1788, -887, -596, 1228, 1479, -202, 447, -367, 1830, -1847, 620, -726, 412, 2022, -1709,
    1063, 144, -273, -1744, 2505, 1181, 2403, 2187, -363, 1291, 1068, -693, 1808, 294, -249, 297,
    2541, -2143, 1649, -1475, -2279, -2182, 294, 1156
};

// ---------------------------------------------------------
// index: 27
// raw_name: overlap_embed/bias
// c_name: pair_overlap_embed_bias
// shape: [6]
// numel: 6
// float_min: -0.020639320835471153
// float_max: 0.06851392239332199
// q_min: -85
// q_max: 281
// max_abs_error: 0.00011367723345756531
// mean_abs_error: 5.88964503549505e-05
// ---------------------------------------------------------
#define PAIR_OVERLAP_EMBED_BIAS_NUMEL 6
#define PAIR_OVERLAP_EMBED_BIAS_DIM0 6
static const int16_t pair_overlap_embed_bias[6] = {
    78, -85, 0, 133, 281, -28
};

// ---------------------------------------------------------
// index: 28
// raw_name: feature_fc0/kernel
// c_name: pair_feature_fc0_kernel
// shape: [15, 8]
// numel: 120
// float_min: -0.7789124250411987
// float_max: 0.6385712027549744
// q_min: -3190
// q_max: 2616
// max_abs_error: 0.00012069940567016602
// mean_abs_error: 6.437124102376401e-05
// ---------------------------------------------------------
#define PAIR_FEATURE_FC0_KERNEL_NUMEL 120
#define PAIR_FEATURE_FC0_KERNEL_DIM0 15
#define PAIR_FEATURE_FC0_KERNEL_DIM1 8
static const int16_t pair_feature_fc0_kernel[120] = {
    -599, 806, 2085, -1157, 2616, -651, 400, 1109, -140, 1298, -975, 159, -1476, 2085, -531, 2488,
    -162, 468, 630, -2090, -1506, -1880, -199, 77, 447, -1338, -1221, 1863, -1420, -659, 1137, -1987,
    -14, -466, -1490, 2024, -370, -1723, -2073, -918, 926, -68, -377, 681, 2344, -1413, -911, 347,
    218, 988, -836, 927, -428, -981, 848, 552, 1259, 2198, 252, 117, -2370, -1266, -352, -715,
    -135, 1149, -1721, 1068, -1376, 555, 1942, -1098, -1143, 1082, -711, -623, 1616, -624, 623, -2076,
    -1728, 839, -1656, 1457, 1124, -1905, 734, -790, -1546, -1737, 204, 2217, -1263, -92, 1224, 1513,
    -1756, -3190, 1516, -726, -1015, 1315, 1174, -373, -1470, -1270, 1955, 1914, -1871, -1835, 1888, -1902,
    1870, -2440, 1728, 1416, 953, 1479, 954, -1499
};

// ---------------------------------------------------------
// index: 29
// raw_name: feature_fc0/bias
// c_name: pair_feature_fc0_bias
// shape: [8]
// numel: 8
// float_min: -0.11733581870794296
// float_max: 0.1672327071428299
// q_min: -481
// q_max: 685
// max_abs_error: 9.582191705703735e-05
// mean_abs_error: 5.1680486649274826e-05
// ---------------------------------------------------------
#define PAIR_FEATURE_FC0_BIAS_NUMEL 8
#define PAIR_FEATURE_FC0_BIAS_DIM0 8
static const int16_t pair_feature_fc0_bias[8] = {
    -48, 685, -166, -344, -245, 86, -481, -342
};

// ---------------------------------------------------------
// index: 30
// raw_name: fusion_fc0/kernel
// c_name: pair_fusion_fc0_kernel
// shape: [34, 16]
// numel: 544
// float_min: -0.5226415991783142
// float_max: 0.45140978693962097
// q_min: -2141
// q_max: 1849
// max_abs_error: 0.00012201815843582153
// mean_abs_error: 4.966501728631556e-05
// ---------------------------------------------------------
#define PAIR_FUSION_FC0_KERNEL_NUMEL 544
#define PAIR_FUSION_FC0_KERNEL_DIM0 34
#define PAIR_FUSION_FC0_KERNEL_DIM1 16
static const int16_t pair_fusion_fc0_kernel[544] = {
    4, -7, 0, -9, 0, 0, 0, 0, 8, 0, -3, 2, 0, 0, 3, 0,
    1142, 0, -675, 795, 1226, 755, -1018, -434, -618, -801, -804, -170, 407, -162, 375, 1600,
    -524, 24, 942, 1141, -87, -499, -382, 1070, -1068, -392, 66, 989, -167, -799, 841, 596,
    758, -33, 1098, 602, -1415, -1061, -219, -415, -787, 768, -387, 1049, 156, -375, 481, 1392,
    0, 0, 0, 0, -12, 0, 0, 0, 12, 5, 0, 0, 0, 0, 0, 0,
    -5, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, -1, -2, 0, 0, 0,
    0, 0, 0, 0, 0, -1, 9, 2, 0, -9, 0, 0, 0, 0, 1, -2,
    0, -2, -11, -1, -3, 0, 0, -11, 9, 0, 0, 1, 0, 0, 0, -7,
    54, -3, 1025, 1422, 761, 115, -611, 666, 1698, -462, -391, 1306, -1427, -442, 184, 653,
    1253, -22, 527, 243, 849, 618, -59, -308, -331, -128, -1209, 441, 1640, -1046, 674, -1210,
    5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11, 0, 0, -6, 0, 0,
    1330, 0, 155, -940, 404, 765, 420, -244, 938, 33, 144, 630, -517, -512, 919, -312,
    -697, -2, 991, -912, 1128, -440, 711, -1357, 406, -1187, 114, -116, -718, 805, -1074, 232,
    -648, -8, 105, -1192, -1107, -875, 798, 48, 864, 356, -660, -861, 14, 441, 366, 200,
    -6, 0, 3, 0, 0, -3, 0, 2, -1, 0, 0, 5, 0, -8, 0, -7,
    0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 4, 0, 0, 0,
    0, 1, 0, -1, 0, 0, 0, 4, 0, 0, 0, 0, 1, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -3, 0, 0, 0, 0, 0, 0, 0, -1, 0,
    -668, 0, 882, -4, 674, -827, -331, -1098, 1074, -741, 572, -744, -1155, -841, -1268, 1117,
    656, -12, -1062, -319, 344, 900, 223, 901, -776, 1104, -228, -97, 632, -228, 1064, -782,
    -917, -2, 460, -338, 1440, 1280, -1088, -314, 286, -777, -562, -903, 793, -1193, -1064, -364,
    128, 0, 559, 1061, -59, -230, 861, 880, -519, 392, -19, -418, -1033, -12, -482, -788,
    0, -1, -1, 3, 0, 2, 0, 0, 0, 0, 0, -8, 0, 1, -3, 0,
    -563, 0, -943, 346, -309, 84, 367, -22, 411, 205, 297, -415, -1632, -172, -1036, 1220,
    482, -2, -1230, 373, 1445, 457, 658, -925, 1001, 795, 887, 442, -111, 645, 1174, 66,
    -502, 0, -432, 350, 85, -94, -279, 548, -1145, 421, 17, 381, -832, -197, 984, 234,
    -774, 0, 921, 428, -1026, 585, 524, -664, -341, -943, -96, 503, 754, 666, 624, 126,
    -1082, 0, 711, 967, 271, 187, 1673, -805, -49, 324, -104, -998, -261, -3, -1252, 713,
    -135, 0, -445, 338, -1009, -342, 373, 14, -83, -1549, 1224, -802, 537, 325, -1000, 386,
    318, -3, -1755, -476, 715, 1367, 265, -28, -1267, 1573, -90, 1090, 543, -1, 839, -21,
    -37, 1, 1054, 510, -944, -691, 285, -1240, 1263, -439, 1200, -339, 590, -17, -1387, 504,
    -754, 0, -1015, -1159, -247, -681, 754, 65, -573, -387, -407, -247, 1327, 467, 1806, 508,
    -757, -9, 12, 940, -1573, 261, 250, -119, -533, -1362, 689, -551, -925, 505, 355, 1167,
    -1084, -1, 515, -597, 1254, 35, -2141, -332, -379, 1849, 14, 851, -32, -35, 613, -449
};

// ---------------------------------------------------------
// index: 31
// raw_name: fusion_fc0/bias
// c_name: pair_fusion_fc0_bias
// shape: [16]
// numel: 16
// float_min: -0.06713172793388367
// float_max: 0.09283462166786194
// q_min: -275
// q_max: 380
// max_abs_error: 0.00011259689927101135
// mean_abs_error: 5.500653060153127e-05
// ---------------------------------------------------------
#define PAIR_FUSION_FC0_BIAS_NUMEL 16
#define PAIR_FUSION_FC0_BIAS_DIM0 16
static const int16_t pair_fusion_fc0_bias[16] = {
    17, -41, -252, 54, 127, -190, -275, -147, -259, 123, 191, 242, 251, -191, -122, 380
};

// ---------------------------------------------------------
// index: 32
// raw_name: fusion_fc1/kernel
// c_name: pair_fusion_fc1_kernel
// shape: [16, 8]
// numel: 128
// float_min: -0.4582796096801758
// float_max: 0.6523234844207764
// q_min: -1877
// q_max: 2672
// max_abs_error: 0.00012192130088806152
// mean_abs_error: 5.494583456311375e-05
// ---------------------------------------------------------
#define PAIR_FUSION_FC1_KERNEL_NUMEL 128
#define PAIR_FUSION_FC1_KERNEL_DIM0 16
#define PAIR_FUSION_FC1_KERNEL_DIM1 8
static const int16_t pair_fusion_fc1_kernel[128] = {
    318, -53, -46, -1494, 1375, -719, 1448, 999, 66, -3, 0, 0, 30, 0, 48, -36,
    -624, -66, -435, -1507, -738, 122, -930, -1626, 1023, -42, 502, 696, -27, -1213, 1310, -1123,
    -331, -49, 1011, 853, -1304, -474, -1565, 1836, -1524, -71, -986, 960, 502, 558, 774, 417,
    558, -89, -1326, -967, -984, -1648, 530, 874, -29, 0, 130, -20, 868, -126, 1477, 428,
    2249, -82, -146, 768, -1484, -615, -378, -1443, -530, -90, -567, 783, 1503, 1030, 300, 1991,
    1319, 0, -795, -115, 1229, -115, -147, 751, 941, 270, 1171, -1176, 1452, 513, 1100, 1542,
    -206, -40, 438, -1877, -1556, 2672, -1520, 678, -561, 0, -16, 1113, -510, 1099, -687, -16,
    -1107, -36, 570, 626, 1315, 1293, 144, 563, 1816, -5, 1055, -1509, 799, -542, -1020, -850
};

// ---------------------------------------------------------
// index: 33
// raw_name: fusion_fc1/bias
// c_name: pair_fusion_fc1_bias
// shape: [8]
// numel: 8
// float_min: -0.030990077182650566
// float_max: 0.10958300530910492
// q_min: -127
// q_max: 449
// max_abs_error: 8.357688784599304e-05
// mean_abs_error: 4.338903818279505e-05
// ---------------------------------------------------------
#define PAIR_FUSION_FC1_BIAS_NUMEL 8
#define PAIR_FUSION_FC1_BIAS_DIM0 8
static const int16_t pair_fusion_fc1_bias[8] = {
    449, -127, 436, 48, 307, 131, -98, 226
};

// ---------------------------------------------------------
// index: 34
// raw_name: left_head_fc0/kernel
// c_name: pair_left_head_fc0_kernel
// shape: [32, 8]
// numel: 256
// float_min: -0.6296401023864746
// float_max: 0.6963913440704346
// q_min: -2579
// q_max: 2852
// max_abs_error: 0.00012185424566268921
// mean_abs_error: 6.26082401140593e-05
// ---------------------------------------------------------
#define PAIR_LEFT_HEAD_FC0_KERNEL_NUMEL 256
#define PAIR_LEFT_HEAD_FC0_KERNEL_DIM0 32
#define PAIR_LEFT_HEAD_FC0_KERNEL_DIM1 8
static const int16_t pair_left_head_fc0_kernel[256] = {
    726, 101, -1216, -1449, -397, -45, 53, 508, 1228, 646, -799, -259, -1411, -512, 1196, -1441,
    -362, -584, -1317, 1652, -902, 567, 1114, -123, 521, -674, 1040, -958, 1590, 1037, 387, -668,
    416, -1074, -1495, 1362, -313, -1486, -849, 1511, -798, -462, -611, 904, -839, 740, 540, -323,
    -1366, 166, -557, -359, 990, -561, 905, 516, 1461, 1250, 391, -1004, 1498, 1480, 1038, 1273,
    1608, 538, -905, -686, 721, 1727, -199, 867, -1609, 171, 934, 1186, -1349, -419, -459, -872,
    225, -148, 1402, 566, 1152, -476, -1147, -847, -856, 1605, 727, 1437, -1254, -89, 802, -677,
    -1479, 25, 1010, -912, 160, -1199, 414, 1521, -1664, 316, 1125, -266, 598, -373, 871, 963,
    459, 1412, -566, -881, 560, -2, 30, -204, -256, 224, 1344, 1302, -115, -710, 788, 816,
    857, 1418, 1108, 966, -454, 943, 1259, -165, 2073, -1354, -935, -1351, -886, 1074, -1036, -93,
    488, 32, 403, 82, -511, 213, -1650, -1677, -1053, 328, 851, 1463, -1468, -1135, -405, 148,
    276, 7, -1242, -288, 654, -232, 33, -1754, 502, 1085, -596, 176, -902, -593, -818, -1095,
    -224, -1378, -738, 921, 680, 478, 1144, -2465, 5, 1102, -98, 2852, -1354, 579, -784, -2579,
    1643, -645, 335, 38, -1170, 718, -1244, -232, -57, -1273, 450, 1415, 662, 1230, -593, 798,
    -1814, 1591, -57, 723, -895, 1326, -518, 520, -1875, 810, -837, 136, -827, -431, 640, -1403,
    -1567, 1703, 375, 118, 287, 467, -805, 806, 281, 895, 2068, -15, 1770, -1415, 8, 1239,
    1037, -1213, -997, 436, 1219, -1071, -614, -1246, 1197, 346, 1811, 1104, -1216, -1510, -1148, 1500
};

// ---------------------------------------------------------
// index: 35
// raw_name: left_head_fc0/bias
// c_name: pair_left_head_fc0_bias
// shape: [8]
// numel: 8
// float_min: -0.014600761234760284
// float_max: 0.14330929517745972
// q_min: -60
// q_max: 587
// max_abs_error: 0.00011097453534603119
// mean_abs_error: 6.101850885897875e-05
// ---------------------------------------------------------
#define PAIR_LEFT_HEAD_FC0_BIAS_NUMEL 8
#define PAIR_LEFT_HEAD_FC0_BIAS_DIM0 8
static const int16_t pair_left_head_fc0_bias[8] = {
    68, 62, 138, 461, 148, 587, -60, 56
};

// ---------------------------------------------------------
// index: 36
// raw_name: right_head_fc0/kernel
// c_name: pair_right_head_fc0_kernel
// shape: [32, 8]
// numel: 256
// float_min: -0.4372628927230835
// float_max: 0.5839253067970276
// q_min: -1791
// q_max: 2392
// max_abs_error: 0.00012185424566268921
// mean_abs_error: 6.279497756622732e-05
// ---------------------------------------------------------
#define PAIR_RIGHT_HEAD_FC0_KERNEL_NUMEL 256
#define PAIR_RIGHT_HEAD_FC0_KERNEL_DIM0 32
#define PAIR_RIGHT_HEAD_FC0_KERNEL_DIM1 8
static const int16_t pair_right_head_fc0_kernel[256] = {
    -685, 1230, 1068, 589, 1521, 1318, -959, -714, 1202, -1092, 869, -549, -987, -1339, -658, -1245,
    -41, 962, 85, -1230, -255, 1346, 1706, -110, -1375, -712, -333, 166, 1150, -1720, 202, -258,
    1216, 98, 1227, 780, -957, 1550, -296, -1219, 1441, -1151, -464, 966, -282, 867, -539, 1429,
    -1270, -382, -299, -728, 1148, 377, -1291, 131, -1053, 679, 1152, 1124, -755, 545, 473, -930,
    390, -1565, -1492, -894, 566, 258, 2106, -1594, -1232, -823, -157, -217, -1037, 54, -863, 1128,
    1001, -1114, -1546, 1251, 975, 4, 139, 616, -601, -1025, 72, 498, 1077, -563, 7, -1071,
    26, 661, 1333, 308, 240, 815, 387, 1444, -1039, -11, -1443, -65, -1459, -691, 1206, -1047,
    963, -1279, -1112, 1369, -1416, -1578, 570, 401, 75, 422, -830, 596, -872, 1504, 388, -1043,
    567, 65, -635, 1261, 397, -1453, -111, 1462, -649, -996, 935, -1363, 898, -769, 2392, 567,
    -1382, 1017, 1396, -1515, -920, 501, -594, -1071, 1886, 663, 106, 1662, 314, -797, 596, 1598,
    -809, 398, 871, -1210, -278, 553, 1146, -766, -572, 1407, 451, 85, 15, -1414, 540, 1016,
    376, 425, -1261, -1018, 1104, 254, 655, -252, -1454, -1099, -484, 736, 1646, -902, -1130, -121,
    433, 1256, -1438, 807, -1476, 100, 973, 960, 798, -612, 574, 1630, 418, -1122, 1428, -1228,
    285, 1253, 465, -1122, -154, -1044, 1058, 1016, 168, 605, -1482, -335, 285, 374, -1663, 964,
    1063, 36, -224, 1058, 1224, -788, -610, -118, -566, 778, -1203, 1332, 665, -1506, -1791, -249,
    897, -716, 291, 1643, -1173, -213, -972, 156, 292, 233, 238, 868, 1658, -1077, -1436, 1283
};

// ---------------------------------------------------------
// index: 37
// raw_name: right_head_fc0/bias
// c_name: pair_right_head_fc0_bias
// shape: [8]
// numel: 8
// float_min: -0.05174955353140831
// float_max: 0.1343967169523239
// q_min: -212
// q_max: 550
// max_abs_error: 0.00011937320232391357
// mean_abs_error: 7.438892498612404e-05
// ---------------------------------------------------------
#define PAIR_RIGHT_HEAD_FC0_BIAS_NUMEL 8
#define PAIR_RIGHT_HEAD_FC0_BIAS_DIM0 8
static const int16_t pair_right_head_fc0_bias[8] = {
    87, -142, -41, 356, -107, -212, 550, 137
};

// ---------------------------------------------------------
// index: 38
// raw_name: left_output/kernel
// c_name: pair_left_output_kernel
// shape: [8, 2]
// numel: 16
// float_min: -0.811604380607605
// float_max: 1.0744974613189697
// q_min: -3324
// q_max: 4401
// max_abs_error: 0.0001087188720703125
// mean_abs_error: 5.995453102514148e-05
// ---------------------------------------------------------
#define PAIR_LEFT_OUTPUT_KERNEL_NUMEL 16
#define PAIR_LEFT_OUTPUT_KERNEL_DIM0 8
#define PAIR_LEFT_OUTPUT_KERNEL_DIM1 2
static const int16_t pair_left_output_kernel[16] = {
    -3324, 716, 910, -1444, 925, -55, 1953, 92, 2517, 408, -2533, 4401, -2393, -1089, 1279, 2112
};

// ---------------------------------------------------------
// index: 39
// raw_name: left_output/bias
// c_name: pair_left_output_bias
// shape: [2]
// numel: 2
// float_min: -0.017649268731474876
// float_max: 0.01764930598437786
// q_min: -72
// q_max: 72
// max_abs_error: 7.118098437786102e-05
// mean_abs_error: 7.116235792636871e-05
// ---------------------------------------------------------
#define PAIR_LEFT_OUTPUT_BIAS_NUMEL 2
#define PAIR_LEFT_OUTPUT_BIAS_DIM0 2
static const int16_t pair_left_output_bias[2] = {
    72, -72
};

// ---------------------------------------------------------
// index: 40
// raw_name: right_output/kernel
// c_name: pair_right_output_kernel
// shape: [8, 2]
// numel: 16
// float_min: -0.7346664071083069
// float_max: 0.9192721247673035
// q_min: -3009
// q_max: 3765
// max_abs_error: 0.00012183189392089844
// mean_abs_error: 5.835038609802723e-05
// ---------------------------------------------------------
#define PAIR_RIGHT_OUTPUT_KERNEL_NUMEL 16
#define PAIR_RIGHT_OUTPUT_KERNEL_DIM0 8
#define PAIR_RIGHT_OUTPUT_KERNEL_DIM1 2
static const int16_t pair_right_output_kernel[16] = {
    3765, -2306, -103, -3009, 2679, 1146, -727, -2194, 1869, -1623, -706, 139, -2747, 3644, 2330, 137
};

// ---------------------------------------------------------
// index: 41
// raw_name: right_output/bias
// c_name: pair_right_output_bias
// shape: [2]
// numel: 2
// float_min: -0.024077894166111946
// float_max: 0.02407793700695038
// q_min: -99
// q_max: 99
// max_abs_error: 9.20277088880539e-05
// mean_abs_error: 9.200628846883774e-05
// ---------------------------------------------------------
#define PAIR_RIGHT_OUTPUT_BIAS_NUMEL 2
#define PAIR_RIGHT_OUTPUT_BIAS_DIM0 2
static const int16_t pair_right_output_bias[2] = {
    -99, 99
};

#endif