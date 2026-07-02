#ifndef MAIN_5CLASS_Q4_12_WEIGHTS_H
#define MAIN_5CLASS_Q4_12_WEIGHTS_H

#include <stdint.h>
#include "combined_q4_12_config.h"

// Main 5-class model weights Q4.12
// Q4.12: float ~= int16 / 4096

// ---------------------------------------------------------
// index: 0
// raw_name: conv1d/kernel
// c_name: main5_conv1d_kernel
// shape: [7, 1, 8]
// numel: 56
// float_min: -0.4777115285396576
// float_max: 0.49527034163475037
// q_min: -1957
// q_max: 2029
// max_abs_error: 0.0001201629638671875
// mean_abs_error: 6.240738730411977e-05
// ---------------------------------------------------------
#define MAIN5_CONV1D_KERNEL_NUMEL 56
#define MAIN5_CONV1D_KERNEL_DIM0 7
#define MAIN5_CONV1D_KERNEL_DIM1 1
#define MAIN5_CONV1D_KERNEL_DIM2 8
static const int16_t main5_conv1d_kernel[56] = {
    -184, -934, 400, -268, 1079, 2029, 220, -147, 864, 238, -1008, -1034, 207, 774, 430, 404,
    775, 662, -201, -1258, 154, 761, 706, -402, 1263, -615, 660, 87, 754, -254, -727, 394,
    771, -538, 841, -175, -775, -462, -1229, -564, 520, -1036, 1090, -159, 120, -1015, -1201, 32,
    -78, -752, 603, 266, 1121, -840, -101, -1957
};

// ---------------------------------------------------------
// index: 1
// raw_name: batch_normalization/gamma
// c_name: main5_batch_normalization_gamma
// shape: [8]
// numel: 8
// float_min: 0.7291340827941895
// float_max: 1.0175139904022217
// q_min: 2987
// q_max: 4168
// max_abs_error: 0.00011396408081054688
// mean_abs_error: 7.305294275283813e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_GAMMA_NUMEL 8
#define MAIN5_BATCH_NORMALIZATION_GAMMA_DIM0 8
static const int16_t main5_batch_normalization_gamma[8] = {
    4168, 3478, 3764, 3736, 4071, 3781, 3999, 2987
};

// ---------------------------------------------------------
// index: 2
// raw_name: batch_normalization/beta
// c_name: main5_batch_normalization_beta
// shape: [8]
// numel: 8
// float_min: -0.1193862333893776
// float_max: 0.3687096834182739
// q_min: -489
// q_max: 1510
// max_abs_error: 0.00010213255882263184
// mean_abs_error: 4.999898374080658e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_BETA_NUMEL 8
#define MAIN5_BATCH_NORMALIZATION_BETA_DIM0 8
static const int16_t main5_batch_normalization_beta[8] = {
    182, 575, -481, 1301, -489, 81, 994, 1510
};

// ---------------------------------------------------------
// index: 3
// raw_name: batch_normalization/moving_mean
// c_name: main5_batch_normalization_moving_mean
// shape: [8]
// numel: 8
// float_min: -0.0004386256623547524
// float_max: 0.0005214763805270195
// q_min: -2
// q_max: 2
// max_abs_error: 0.00011705979704856873
// mean_abs_error: 5.63148787477985e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_MOVING_MEAN_NUMEL 8
#define MAIN5_BATCH_NORMALIZATION_MOVING_MEAN_DIM0 8
static const int16_t main5_batch_normalization_moving_mean[8] = {
    1, -2, 1, -2, 2, 2, 0, -1
};

// ---------------------------------------------------------
// index: 4
// raw_name: batch_normalization/moving_variance
// c_name: main5_batch_normalization_moving_variance
// shape: [8]
// numel: 8
// float_min: 0.2760477662086487
// float_max: 0.8798704147338867
// q_min: 1131
// q_max: 3604
// max_abs_error: 0.00011208653450012207
// mean_abs_error: 4.532560706138611e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_MOVING_VARIANCE_NUMEL 8
#define MAIN5_BATCH_NORMALIZATION_MOVING_VARIANCE_DIM0 8
static const int16_t main5_batch_normalization_moving_variance[8] = {
    3604, 1868, 1474, 1590, 1401, 1353, 1131, 1202
};

// ---------------------------------------------------------
// index: 5
// raw_name: separable_conv1d/depthwise_kernel
// c_name: main5_separable_conv1d_depthwise_kernel
// shape: [3, 8, 1]
// numel: 24
// float_min: -0.39948102831840515
// float_max: 0.40279653668403625
// q_min: -1636
// q_max: 1650
// max_abs_error: 0.0001191943883895874
// mean_abs_error: 7.226752495625988e-05
// ---------------------------------------------------------
#define MAIN5_SEPARABLE_CONV1D_DEPTHWISE_KERNEL_NUMEL 24
#define MAIN5_SEPARABLE_CONV1D_DEPTHWISE_KERNEL_DIM0 3
#define MAIN5_SEPARABLE_CONV1D_DEPTHWISE_KERNEL_DIM1 8
#define MAIN5_SEPARABLE_CONV1D_DEPTHWISE_KERNEL_DIM2 1
static const int16_t main5_separable_conv1d_depthwise_kernel[24] = {
    932, -996, 1650, -1249, -707, -323, 1351, 359, 692, -923, -1050, -1636, 308, 875, 189, -489,
    -772, -353, 528, 189, 388, 1423, 720, -204
};

// ---------------------------------------------------------
// index: 6
// raw_name: separable_conv1d/pointwise_kernel
// c_name: main5_separable_conv1d_pointwise_kernel
// shape: [1, 8, 4]
// numel: 32
// float_min: -0.40733247995376587
// float_max: 0.5233010649681091
// q_min: -1668
// q_max: 2143
// max_abs_error: 0.0001211017370223999
// mean_abs_error: 6.575316365342587e-05
// ---------------------------------------------------------
#define MAIN5_SEPARABLE_CONV1D_POINTWISE_KERNEL_NUMEL 32
#define MAIN5_SEPARABLE_CONV1D_POINTWISE_KERNEL_DIM0 1
#define MAIN5_SEPARABLE_CONV1D_POINTWISE_KERNEL_DIM1 8
#define MAIN5_SEPARABLE_CONV1D_POINTWISE_KERNEL_DIM2 4
static const int16_t main5_separable_conv1d_pointwise_kernel[32] = {
    -1215, 702, 595, 175, -757, -444, 1466, 326, -849, 1844, -818, -1668, -1, -616, -57, 2143,
    -530, -173, 424, 50, 2051, 2065, -290, -38, 1082, -1522, -838, -1370, -528, -105, -253, -96
};

// ---------------------------------------------------------
// index: 7
// raw_name: separable_conv1d_1/depthwise_kernel
// c_name: main5_separable_conv1d_1_depthwise_kernel
// shape: [5, 8, 1]
// numel: 40
// float_min: -0.3180290162563324
// float_max: 0.3439021408557892
// q_min: -1303
// q_max: 1409
// max_abs_error: 0.00011959671974182129
// mean_abs_error: 7.020686462055892e-05
// ---------------------------------------------------------
#define MAIN5_SEPARABLE_CONV1D_1_DEPTHWISE_KERNEL_NUMEL 40
#define MAIN5_SEPARABLE_CONV1D_1_DEPTHWISE_KERNEL_DIM0 5
#define MAIN5_SEPARABLE_CONV1D_1_DEPTHWISE_KERNEL_DIM1 8
#define MAIN5_SEPARABLE_CONV1D_1_DEPTHWISE_KERNEL_DIM2 1
static const int16_t main5_separable_conv1d_1_depthwise_kernel[40] = {
    1363, -188, -89, 533, 449, 1336, -499, 118, -657, 1169, 433, 133, -1275, 1068, -459, 768,
    766, 1409, -823, 172, -1118, -1214, -373, 853, -211, 877, 880, -762, 148, -106, 598, 80,
    -1303, -196, 779, 929, -1245, -437, -915, -274
};

// ---------------------------------------------------------
// index: 8
// raw_name: separable_conv1d_1/pointwise_kernel
// c_name: main5_separable_conv1d_1_pointwise_kernel
// shape: [1, 8, 4]
// numel: 32
// float_min: -0.5563455820083618
// float_max: 0.497963011264801
// q_min: -2279
// q_max: 2040
// max_abs_error: 0.00012021511793136597
// mean_abs_error: 7.247926259879023e-05
// ---------------------------------------------------------
#define MAIN5_SEPARABLE_CONV1D_1_POINTWISE_KERNEL_NUMEL 32
#define MAIN5_SEPARABLE_CONV1D_1_POINTWISE_KERNEL_DIM0 1
#define MAIN5_SEPARABLE_CONV1D_1_POINTWISE_KERNEL_DIM1 8
#define MAIN5_SEPARABLE_CONV1D_1_POINTWISE_KERNEL_DIM2 4
static const int16_t main5_separable_conv1d_1_pointwise_kernel[32] = {
    224, -449, 896, 1209, 538, 472, -1336, -2279, -927, -985, -10, -282, -762, 699, 471, -414,
    2040, 1355, 1126, -1490, 1587, 251, -1484, 1422, -307, -244, -510, -1073, -1319, -848, -569, -547
};

// ---------------------------------------------------------
// index: 9
// raw_name: separable_conv1d_2/depthwise_kernel
// c_name: main5_separable_conv1d_2_depthwise_kernel
// shape: [7, 8, 1]
// numel: 56
// float_min: -0.4166841208934784
// float_max: 0.3894651234149933
// q_min: -1707
// q_max: 1595
// max_abs_error: 0.00012022256851196289
// mean_abs_error: 6.694900366710499e-05
// ---------------------------------------------------------
#define MAIN5_SEPARABLE_CONV1D_2_DEPTHWISE_KERNEL_NUMEL 56
#define MAIN5_SEPARABLE_CONV1D_2_DEPTHWISE_KERNEL_DIM0 7
#define MAIN5_SEPARABLE_CONV1D_2_DEPTHWISE_KERNEL_DIM1 8
#define MAIN5_SEPARABLE_CONV1D_2_DEPTHWISE_KERNEL_DIM2 1
static const int16_t main5_separable_conv1d_2_depthwise_kernel[56] = {
    -854, -318, -751, -1179, 369, 1034, 53, 422, -583, 160, -1242, 633, 645, -1051, 846, 650,
    -135, -1037, -778, 702, -180, -703, 895, 149, -1062, -684, 842, 601, -487, -142, 951, -724,
    1148, -120, -660, 696, 808, 598, 899, 110, 833, -49, 279, 1153, 696, -312, -540, -1269,
    -202, 1595, -283, 932, 882, -829, -1707, -589
};

// ---------------------------------------------------------
// index: 10
// raw_name: separable_conv1d_2/pointwise_kernel
// c_name: main5_separable_conv1d_2_pointwise_kernel
// shape: [1, 8, 4]
// numel: 32
// float_min: -0.5243799686431885
// float_max: 0.5982459187507629
// q_min: -2148
// q_max: 2450
// max_abs_error: 0.00011897087097167969
// mean_abs_error: 6.642652442678809e-05
// ---------------------------------------------------------
#define MAIN5_SEPARABLE_CONV1D_2_POINTWISE_KERNEL_NUMEL 32
#define MAIN5_SEPARABLE_CONV1D_2_POINTWISE_KERNEL_DIM0 1
#define MAIN5_SEPARABLE_CONV1D_2_POINTWISE_KERNEL_DIM1 8
#define MAIN5_SEPARABLE_CONV1D_2_POINTWISE_KERNEL_DIM2 4
static const int16_t main5_separable_conv1d_2_pointwise_kernel[32] = {
    -1844, -607, -1230, 1296, 203, -2148, -334, -1336, -2075, 100, -1595, 1560, 2084, -869, -661, 1049,
    -1180, -1495, 405, 2370, 1144, 436, -957, 1220, 716, 815, 995, 2428, -458, 2450, 368, -1132
};

// ---------------------------------------------------------
// index: 11
// raw_name: conv1d_1/kernel
// c_name: main5_conv1d_1_kernel
// shape: [1, 8, 4]
// numel: 32
// float_min: -0.5365667939186096
// float_max: 0.500484049320221
// q_min: -2198
// q_max: 2050
// max_abs_error: 0.00012193247675895691
// mean_abs_error: 5.319301271811128e-05
// ---------------------------------------------------------
#define MAIN5_CONV1D_1_KERNEL_NUMEL 32
#define MAIN5_CONV1D_1_KERNEL_DIM0 1
#define MAIN5_CONV1D_1_KERNEL_DIM1 8
#define MAIN5_CONV1D_1_KERNEL_DIM2 4
static const int16_t main5_conv1d_1_kernel[32] = {
    128, -2198, 2050, -435, 268, 1295, -1702, -219, -616, -1142, -608, 326, 911, 265, 227, 1475,
    664, 309, -902, -801, -1861, 1578, 528, -1470, -182, -1916, -547, -1200, 1804, 1528, -1912, -33
};

// ---------------------------------------------------------
// index: 12
// raw_name: batch_normalization_1/gamma
// c_name: main5_batch_normalization_1_gamma
// shape: [4]
// numel: 4
// float_min: 0.9096368551254272
// float_max: 1.1015554666519165
// q_min: 3726
// q_max: 4512
// max_abs_error: 9.02414321899414e-05
// mean_abs_error: 4.3451786041259766e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_1_GAMMA_NUMEL 4
#define MAIN5_BATCH_NORMALIZATION_1_GAMMA_DIM0 4
static const int16_t main5_batch_normalization_1_gamma[4] = {
    3726, 4154, 4512, 4510
};

// ---------------------------------------------------------
// index: 13
// raw_name: batch_normalization_1/beta
// c_name: main5_batch_normalization_1_beta
// shape: [4]
// numel: 4
// float_min: -0.10119720548391342
// float_max: 0.12771625816822052
// q_min: -415
// q_max: 523
// max_abs_error: 0.00012115389108657837
// mean_abs_error: 8.134741801768541e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_1_BETA_NUMEL 4
#define MAIN5_BATCH_NORMALIZATION_1_BETA_DIM0 4
static const int16_t main5_batch_normalization_1_beta[4] = {
    452, -9, -415, 523
};

// ---------------------------------------------------------
// index: 14
// raw_name: batch_normalization_1/moving_mean
// c_name: main5_batch_normalization_1_moving_mean
// shape: [4]
// numel: 4
// float_min: -0.2138027548789978
// float_max: 0.08912723511457443
// q_min: -876
// q_max: 365
// max_abs_error: 8.425861597061157e-05
// mean_abs_error: 4.708673804998398e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_1_MOVING_MEAN_NUMEL 4
#define MAIN5_BATCH_NORMALIZATION_1_MOVING_MEAN_DIM0 4
static const int16_t main5_batch_normalization_1_moving_mean[4] = {
    365, 171, -349, -876
};

// ---------------------------------------------------------
// index: 15
// raw_name: batch_normalization_1/moving_variance
// c_name: main5_batch_normalization_1_moving_variance
// shape: [4]
// numel: 4
// float_min: 0.014136062003672123
// float_max: 0.06745896488428116
// q_min: 58
// q_max: 276
// max_abs_error: 0.00011880695819854736
// mean_abs_error: 7.332745008170605e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_1_MOVING_VARIANCE_NUMEL 4
#define MAIN5_BATCH_NORMALIZATION_1_MOVING_VARIANCE_DIM0 4
static const int16_t main5_batch_normalization_1_moving_variance[4] = {
    161, 276, 58, 212
};

// ---------------------------------------------------------
// index: 16
// raw_name: batch_normalization_2/gamma
// c_name: main5_batch_normalization_2_gamma
// shape: [4]
// numel: 4
// float_min: 0.9530714154243469
// float_max: 1.194092869758606
// q_min: 3904
// q_max: 4891
// max_abs_error: 5.7578086853027344e-05
// mean_abs_error: 3.5509467124938965e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_2_GAMMA_NUMEL 4
#define MAIN5_BATCH_NORMALIZATION_2_GAMMA_DIM0 4
static const int16_t main5_batch_normalization_2_gamma[4] = {
    3904, 4891, 4107, 4411
};

// ---------------------------------------------------------
// index: 17
// raw_name: batch_normalization_2/beta
// c_name: main5_batch_normalization_2_beta
// shape: [4]
// numel: 4
// float_min: -0.38882550597190857
// float_max: 0.19683235883712769
// q_min: -1593
// q_max: 806
// max_abs_error: 9.050965309143066e-05
// mean_abs_error: 5.4046104196459055e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_2_BETA_NUMEL 4
#define MAIN5_BATCH_NORMALIZATION_2_BETA_DIM0 4
static const int16_t main5_batch_normalization_2_beta[4] = {
    806, 7, -1593, -601
};

// ---------------------------------------------------------
// index: 18
// raw_name: batch_normalization_2/moving_mean
// c_name: main5_batch_normalization_2_moving_mean
// shape: [4]
// numel: 4
// float_min: -0.0938878059387207
// float_max: -0.03004067949950695
// q_min: -385
// q_max: -123
// max_abs_error: 0.00010633468627929688
// mean_abs_error: 7.203733548521996e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_2_MOVING_MEAN_NUMEL 4
#define MAIN5_BATCH_NORMALIZATION_2_MOVING_MEAN_DIM0 4
static const int16_t main5_batch_normalization_2_moving_mean[4] = {
    -356, -123, -385, -192
};

// ---------------------------------------------------------
// index: 19
// raw_name: batch_normalization_2/moving_variance
// c_name: main5_batch_normalization_2_moving_variance
// shape: [4]
// numel: 4
// float_min: 0.02973177470266819
// float_max: 0.11131088435649872
// q_min: 122
// q_max: 456
// max_abs_error: 0.00011122971773147583
// mean_abs_error: 4.61614690721035e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_2_MOVING_VARIANCE_NUMEL 4
#define MAIN5_BATCH_NORMALIZATION_2_MOVING_VARIANCE_DIM0 4
static const int16_t main5_batch_normalization_2_moving_variance[4] = {
    456, 223, 122, 345
};

// ---------------------------------------------------------
// index: 20
// raw_name: batch_normalization_3/gamma
// c_name: main5_batch_normalization_3_gamma
// shape: [4]
// numel: 4
// float_min: 0.9195808172225952
// float_max: 1.3360626697540283
// q_min: 3767
// q_max: 5473
// max_abs_error: 0.00011897087097167969
// mean_abs_error: 6.726384162902832e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_3_GAMMA_NUMEL 4
#define MAIN5_BATCH_NORMALIZATION_3_GAMMA_DIM0 4
static const int16_t main5_batch_normalization_3_gamma[4] = {
    4010, 5473, 3767, 4136
};

// ---------------------------------------------------------
// index: 21
// raw_name: batch_normalization_3/beta
// c_name: main5_batch_normalization_3_beta
// shape: [4]
// numel: 4
// float_min: -0.08651470392942429
// float_max: 0.26397719979286194
// q_min: -354
// q_max: 1081
// max_abs_error: 8.892267942428589e-05
// mean_abs_error: 6.22803345322609e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_3_BETA_NUMEL 4
#define MAIN5_BATCH_NORMALIZATION_3_BETA_DIM0 4
static const int16_t main5_batch_normalization_3_beta[4] = {
    256, 789, -354, 1081
};

// ---------------------------------------------------------
// index: 22
// raw_name: batch_normalization_3/moving_mean
// c_name: main5_batch_normalization_3_moving_mean
// shape: [4]
// numel: 4
// float_min: -0.1379971206188202
// float_max: 0.21251879632472992
// q_min: -565
// q_max: 870
// max_abs_error: 0.00011645257472991943
// mean_abs_error: 9.326077997684479e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_3_MOVING_MEAN_NUMEL 4
#define MAIN5_BATCH_NORMALIZATION_3_MOVING_MEAN_DIM0 4
static const int16_t main5_batch_normalization_3_moving_mean[4] = {
    870, -565, 136, 801
};

// ---------------------------------------------------------
// index: 23
// raw_name: batch_normalization_3/moving_variance
// c_name: main5_batch_normalization_3_moving_variance
// shape: [4]
// numel: 4
// float_min: 0.05422034114599228
// float_max: 0.13047271966934204
// q_min: 222
// q_max: 534
// max_abs_error: 0.00010162591934204102
// mean_abs_error: 5.13661652803421e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_3_MOVING_VARIANCE_NUMEL 4
#define MAIN5_BATCH_NORMALIZATION_3_MOVING_VARIANCE_DIM0 4
static const int16_t main5_batch_normalization_3_moving_variance[4] = {
    534, 222, 395, 524
};

// ---------------------------------------------------------
// index: 24
// raw_name: batch_normalization_4/gamma
// c_name: main5_batch_normalization_4_gamma
// shape: [4]
// numel: 4
// float_min: 0.982586681842804
// float_max: 1.1604831218719482
// q_min: 4025
// q_max: 4753
// max_abs_error: 8.273124694824219e-05
// mean_abs_error: 7.478892803192139e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_4_GAMMA_NUMEL 4
#define MAIN5_BATCH_NORMALIZATION_4_GAMMA_DIM0 4
static const int16_t main5_batch_normalization_4_gamma[4] = {
    4025, 4112, 4488, 4753
};

// ---------------------------------------------------------
// index: 25
// raw_name: batch_normalization_4/beta
// c_name: main5_batch_normalization_4_beta
// shape: [4]
// numel: 4
// float_min: -0.3671680688858032
// float_max: 0.3299672305583954
// q_min: -1504
// q_max: 1352
// max_abs_error: 0.00011089444160461426
// mean_abs_error: 7.977895438671112e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_4_BETA_NUMEL 4
#define MAIN5_BATCH_NORMALIZATION_4_BETA_DIM0 4
static const int16_t main5_batch_normalization_4_beta[4] = {
    -1504, 192, 395, 1352
};

// ---------------------------------------------------------
// index: 26
// raw_name: batch_normalization_4/moving_mean
// c_name: main5_batch_normalization_4_moving_mean
// shape: [4]
// numel: 4
// float_min: -0.2382880002260208
// float_max: 0.1931612342596054
// q_min: -976
// q_max: 791
// max_abs_error: 6.933510303497314e-05
// mean_abs_error: 3.667059354484081e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_4_MOVING_MEAN_NUMEL 4
#define MAIN5_BATCH_NORMALIZATION_4_MOVING_MEAN_DIM0 4
static const int16_t main5_batch_normalization_4_moving_mean[4] = {
    791, -60, -976, -453
};

// ---------------------------------------------------------
// index: 27
// raw_name: batch_normalization_4/moving_variance
// c_name: main5_batch_normalization_4_moving_variance
// shape: [4]
// numel: 4
// float_min: 0.1924665868282318
// float_max: 0.3428126573562622
// q_min: 788
// q_max: 1404
// max_abs_error: 0.00010323524475097656
// mean_abs_error: 6.706267595291138e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_4_MOVING_VARIANCE_NUMEL 4
#define MAIN5_BATCH_NORMALIZATION_4_MOVING_VARIANCE_DIM0 4
static const int16_t main5_batch_normalization_4_moving_variance[4] = {
    788, 1404, 1036, 1356
};

// ---------------------------------------------------------
// index: 28
// raw_name: conv1d_2/kernel
// c_name: main5_conv1d_2_kernel
// shape: [1, 16, 8]
// numel: 128
// float_min: -0.4778710901737213
// float_max: 0.434440553188324
// q_min: -1957
// q_max: 1779
// max_abs_error: 0.00012177228927612305
// mean_abs_error: 6.395948003046215e-05
// ---------------------------------------------------------
#define MAIN5_CONV1D_2_KERNEL_NUMEL 128
#define MAIN5_CONV1D_2_KERNEL_DIM0 1
#define MAIN5_CONV1D_2_KERNEL_DIM1 16
#define MAIN5_CONV1D_2_KERNEL_DIM2 8
static const int16_t main5_conv1d_2_kernel[128] = {
    250, -553, -88, 1217, 710, -1069, -666, 138, -1107, -698, -1373, -566, -86, -306, 749, 948,
    -1385, -517, -1055, 658, 1164, -1088, -1002, -130, -1111, 551, -806, -56, 1207, -1041, -632, -1957,
    300, -329, -1430, -466, -133, 1449, -1003, -453, 821, 1098, -863, 974, -675, 706, 590, 780,
    971, 142, -74, 1339, -506, 1093, 717, -57, 491, 1577, -1662, 248, -1199, -1398, -1090, 307,
    -1050, -1010, 1168, 460, 121, 479, -355, -172, 1285, -1263, 273, -1312, 193, -1769, -1554, 997,
    -1758, 1506, 228, 968, -1354, 340, -74, -760, 779, -1132, 267, 767, 1176, 1022, -1428, -1267,
    1337, 24, 252, 1059, -1366, 477, 267, -949, -1072, -202, -1853, -1012, 352, -344, -1411, 800,
    -414, 848, 314, -1823, 1779, 930, 1586, -949, -220, -1549, 756, -808, -1321, 604, -1650, 1440
};

// ---------------------------------------------------------
// index: 29
// raw_name: batch_normalization_5/gamma
// c_name: main5_batch_normalization_5_gamma
// shape: [8]
// numel: 8
// float_min: 0.751885712146759
// float_max: 1.1489667892456055
// q_min: 3080
// q_max: 4706
// max_abs_error: 0.00011098384857177734
// mean_abs_error: 7.278472185134888e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_5_GAMMA_NUMEL 8
#define MAIN5_BATCH_NORMALIZATION_5_GAMMA_DIM0 8
static const int16_t main5_batch_normalization_5_gamma[8] = {
    4706, 4623, 4226, 3080, 3367, 3963, 4041, 4421
};

// ---------------------------------------------------------
// index: 30
// raw_name: batch_normalization_5/beta
// c_name: main5_batch_normalization_5_beta
// shape: [8]
// numel: 8
// float_min: -0.3943532407283783
// float_max: 0.4704417288303375
// q_min: -1615
// q_max: 1927
// max_abs_error: 0.00011289119720458984
// mean_abs_error: 5.639903247356415e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_5_BETA_NUMEL 8
#define MAIN5_BATCH_NORMALIZATION_5_BETA_DIM0 8
static const int16_t main5_batch_normalization_5_beta[8] = {
    141, -95, 633, 672, 1927, -1014, -1615, -1090
};

// ---------------------------------------------------------
// index: 31
// raw_name: batch_normalization_5/moving_mean
// c_name: main5_batch_normalization_5_moving_mean
// shape: [8]
// numel: 8
// float_min: -0.5804741382598877
// float_max: 0.17925283312797546
// q_min: -2378
// q_max: 734
// max_abs_error: 0.00010229647159576416
// mean_abs_error: 7.969001308083534e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_5_MOVING_MEAN_NUMEL 8
#define MAIN5_BATCH_NORMALIZATION_5_MOVING_MEAN_DIM0 8
static const int16_t main5_batch_normalization_5_moving_mean[8] = {
    -408, -985, -1031, -764, 734, -220, -2378, -150
};

// ---------------------------------------------------------
// index: 32
// raw_name: batch_normalization_5/moving_variance
// c_name: main5_batch_normalization_5_moving_variance
// shape: [8]
// numel: 8
// float_min: 0.15237966179847717
// float_max: 0.6186635494232178
// q_min: 624
// q_max: 2534
// max_abs_error: 8.419156074523926e-05
// mean_abs_error: 3.604218363761902e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_5_MOVING_VARIANCE_NUMEL 8
#define MAIN5_BATCH_NORMALIZATION_5_MOVING_VARIANCE_DIM0 8
static const int16_t main5_batch_normalization_5_moving_variance[8] = {
    2534, 2183, 946, 1025, 624, 814, 1428, 674
};

// ---------------------------------------------------------
// index: 33
// raw_name: separable_conv1d_3/depthwise_kernel
// c_name: main5_separable_conv1d_3_depthwise_kernel
// shape: [3, 8, 1]
// numel: 24
// float_min: -0.4204900860786438
// float_max: 0.3506796956062317
// q_min: -1722
// q_max: 1436
// max_abs_error: 0.00011852383613586426
// mean_abs_error: 6.751188630005345e-05
// ---------------------------------------------------------
#define MAIN5_SEPARABLE_CONV1D_3_DEPTHWISE_KERNEL_NUMEL 24
#define MAIN5_SEPARABLE_CONV1D_3_DEPTHWISE_KERNEL_DIM0 3
#define MAIN5_SEPARABLE_CONV1D_3_DEPTHWISE_KERNEL_DIM1 8
#define MAIN5_SEPARABLE_CONV1D_3_DEPTHWISE_KERNEL_DIM2 1
static const int16_t main5_separable_conv1d_3_depthwise_kernel[24] = {
    432, 1124, 1280, 1198, -629, -653, -1722, -1318, 1127, -1114, 172, 930, 805, -484, -1004, 258,
    269, -935, 575, -1323, 412, -953, 245, 1436
};

// ---------------------------------------------------------
// index: 34
// raw_name: separable_conv1d_3/pointwise_kernel
// c_name: main5_separable_conv1d_3_pointwise_kernel
// shape: [1, 8, 6]
// numel: 48
// float_min: -0.49744388461112976
// float_max: 0.4567531943321228
// q_min: -2038
// q_max: 1871
// max_abs_error: 0.00012027844786643982
// mean_abs_error: 6.292892066994682e-05
// ---------------------------------------------------------
#define MAIN5_SEPARABLE_CONV1D_3_POINTWISE_KERNEL_NUMEL 48
#define MAIN5_SEPARABLE_CONV1D_3_POINTWISE_KERNEL_DIM0 1
#define MAIN5_SEPARABLE_CONV1D_3_POINTWISE_KERNEL_DIM1 8
#define MAIN5_SEPARABLE_CONV1D_3_POINTWISE_KERNEL_DIM2 6
static const int16_t main5_separable_conv1d_3_pointwise_kernel[48] = {
    -2038, -400, -1901, 45, -201, -230, -1137, 351, 461, 87, -816, 878, 1743, 614, -927, 1300,
    953, -639, -21, 279, 1828, -1676, 164, -371, -1000, -705, 891, 377, 1043, 112, 783, -1815,
    -723, 1167, 99, -239, 911, 1234, 889, 836, -723, -1253, 947, 153, -189, -592, 1466, 1871
};

// ---------------------------------------------------------
// index: 35
// raw_name: separable_conv1d_4/depthwise_kernel
// c_name: main5_separable_conv1d_4_depthwise_kernel
// shape: [5, 8, 1]
// numel: 40
// float_min: -0.3310365080833435
// float_max: 0.4271456003189087
// q_min: -1356
// q_max: 1750
// max_abs_error: 0.00012119114398956299
// mean_abs_error: 6.878325075376779e-05
// ---------------------------------------------------------
#define MAIN5_SEPARABLE_CONV1D_4_DEPTHWISE_KERNEL_NUMEL 40
#define MAIN5_SEPARABLE_CONV1D_4_DEPTHWISE_KERNEL_DIM0 5
#define MAIN5_SEPARABLE_CONV1D_4_DEPTHWISE_KERNEL_DIM1 8
#define MAIN5_SEPARABLE_CONV1D_4_DEPTHWISE_KERNEL_DIM2 1
static const int16_t main5_separable_conv1d_4_depthwise_kernel[40] = {
    -361, 126, 819, -243, -463, 578, 520, -161, -1044, -550, -1356, -238, -576, -544, -633, -49,
    -680, -176, -1078, 529, 261, 1540, 702, 345, 201, 863, -279, 1199, 284, -178, 685, 851,
    42, 979, 1589, -305, 701, -950, 1750, -375
};

// ---------------------------------------------------------
// index: 36
// raw_name: separable_conv1d_4/pointwise_kernel
// c_name: main5_separable_conv1d_4_pointwise_kernel
// shape: [1, 8, 6]
// numel: 48
// float_min: -0.4906729459762573
// float_max: 0.501994788646698
// q_min: -2010
// q_max: 2056
// max_abs_error: 0.00011949241161346436
// mean_abs_error: 6.411507638404146e-05
// ---------------------------------------------------------
#define MAIN5_SEPARABLE_CONV1D_4_POINTWISE_KERNEL_NUMEL 48
#define MAIN5_SEPARABLE_CONV1D_4_POINTWISE_KERNEL_DIM0 1
#define MAIN5_SEPARABLE_CONV1D_4_POINTWISE_KERNEL_DIM1 8
#define MAIN5_SEPARABLE_CONV1D_4_POINTWISE_KERNEL_DIM2 6
static const int16_t main5_separable_conv1d_4_pointwise_kernel[48] = {
    900, 1274, -1329, 590, 497, -1104, -639, -866, 1474, -388, -1017, -803, 220, 1473, 1384, -2010,
    812, 402, -124, 137, 987, -1249, -119, -1537, -819, -767, -1505, -1055, 181, 719, -45, -52,
    -103, 1415, -1853, 662, 2056, 476, -365, -1706, -483, -1588, -12, -1029, 26, 286, 871, -53
};

// ---------------------------------------------------------
// index: 37
// raw_name: separable_conv1d_5/depthwise_kernel
// c_name: main5_separable_conv1d_5_depthwise_kernel
// shape: [7, 8, 1]
// numel: 56
// float_min: -0.38307633996009827
// float_max: 0.3295653760433197
// q_min: -1569
// q_max: 1350
// max_abs_error: 0.00012154877185821533
// mean_abs_error: 5.7829816796584055e-05
// ---------------------------------------------------------
#define MAIN5_SEPARABLE_CONV1D_5_DEPTHWISE_KERNEL_NUMEL 56
#define MAIN5_SEPARABLE_CONV1D_5_DEPTHWISE_KERNEL_DIM0 7
#define MAIN5_SEPARABLE_CONV1D_5_DEPTHWISE_KERNEL_DIM1 8
#define MAIN5_SEPARABLE_CONV1D_5_DEPTHWISE_KERNEL_DIM2 1
static const int16_t main5_separable_conv1d_5_depthwise_kernel[56] = {
    1211, 1350, -843, 1109, -593, -1060, -874, -881, 1108, -1569, -763, -1188, -817, 433, 113, -389,
    -26, -719, 600, 193, 379, -1262, 561, -568, 570, -615, 441, -286, 416, 777, 507, 230,
    163, -62, -860, 244, 999, 666, -537, 825, 940, 216, 969, 41, 33, 56, 215, 777,
    322, 7, 458, -1092, -737, 603, -734, -608
};

// ---------------------------------------------------------
// index: 38
// raw_name: separable_conv1d_5/pointwise_kernel
// c_name: main5_separable_conv1d_5_pointwise_kernel
// shape: [1, 8, 6]
// numel: 48
// float_min: -0.5249707698822021
// float_max: 0.4223010540008545
// q_min: -2150
// q_max: 1730
// max_abs_error: 0.00012046098709106445
// mean_abs_error: 5.490366675076075e-05
// ---------------------------------------------------------
#define MAIN5_SEPARABLE_CONV1D_5_POINTWISE_KERNEL_NUMEL 48
#define MAIN5_SEPARABLE_CONV1D_5_POINTWISE_KERNEL_DIM0 1
#define MAIN5_SEPARABLE_CONV1D_5_POINTWISE_KERNEL_DIM1 8
#define MAIN5_SEPARABLE_CONV1D_5_POINTWISE_KERNEL_DIM2 6
static const int16_t main5_separable_conv1d_5_pointwise_kernel[48] = {
    -1044, -125, -953, -185, 1730, 187, 65, -1142, 906, -1817, 876, -1804, 1341, 1607, -482, -1787,
    -216, 901, -1427, -139, 896, 1245, -1336, -1309, -403, 733, 331, 1019, -352, -2150, 1446, 1342,
    526, -1470, 605, 65, 1567, -320, 645, 764, -114, -15, 1519, 185, 1564, -1126, 242, -132
};

// ---------------------------------------------------------
// index: 39
// raw_name: conv1d_3/kernel
// c_name: main5_conv1d_3_kernel
// shape: [1, 8, 6]
// numel: 48
// float_min: -0.43602898716926575
// float_max: 0.5694222450256348
// q_min: -1786
// q_max: 2332
// max_abs_error: 0.00011804699897766113
// mean_abs_error: 5.8526391512714326e-05
// ---------------------------------------------------------
#define MAIN5_CONV1D_3_KERNEL_NUMEL 48
#define MAIN5_CONV1D_3_KERNEL_DIM0 1
#define MAIN5_CONV1D_3_KERNEL_DIM1 8
#define MAIN5_CONV1D_3_KERNEL_DIM2 6
static const int16_t main5_conv1d_3_kernel[48] = {
    1086, 1261, 17, 2332, -1348, 341, -1135, -14, 684, -618, -882, 1417, 521, 568, 1007, -1244,
    -1060, 55, 717, 562, 319, 671, 697, -1451, -576, 1123, -1786, 736, 1679, -1396, 868, -142,
    -448, -538, -264, 113, 1689, 532, -77, -1151, -1145, 37, 633, -515, -539, 746, 508, 802
};

// ---------------------------------------------------------
// index: 40
// raw_name: batch_normalization_6/gamma
// c_name: main5_batch_normalization_6_gamma
// shape: [6]
// numel: 6
// float_min: 0.8954294323921204
// float_max: 1.3126214742660522
// q_min: 3668
// q_max: 5376
// max_abs_error: 0.0001214742660522461
// mean_abs_error: 9.058912837645039e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_6_GAMMA_NUMEL 6
#define MAIN5_BATCH_NORMALIZATION_6_GAMMA_DIM0 6
static const int16_t main5_batch_normalization_6_gamma[6] = {
    4920, 4035, 3982, 5376, 3668, 4141
};

// ---------------------------------------------------------
// index: 41
// raw_name: batch_normalization_6/beta
// c_name: main5_batch_normalization_6_beta
// shape: [6]
// numel: 6
// float_min: -0.18433520197868347
// float_max: 0.38025718927383423
// q_min: -755
// q_max: 1558
// max_abs_error: 0.00011390447616577148
// mean_abs_error: 6.029227006365545e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_6_BETA_NUMEL 6
#define MAIN5_BATCH_NORMALIZATION_6_BETA_DIM0 6
static const int16_t main5_batch_normalization_6_beta[6] = {
    -755, 119, 999, 302, -656, 1558
};

// ---------------------------------------------------------
// index: 42
// raw_name: batch_normalization_6/moving_mean
// c_name: main5_batch_normalization_6_moving_mean
// shape: [6]
// numel: 6
// float_min: -0.036360472440719604
// float_max: 0.10208186507225037
// q_min: -149
// q_max: 418
// max_abs_error: 6.152130663394928e-05
// mean_abs_error: 2.6038382202386856e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_6_MOVING_MEAN_NUMEL 6
#define MAIN5_BATCH_NORMALIZATION_6_MOVING_MEAN_DIM0 6
static const int16_t main5_batch_normalization_6_moving_mean[6] = {
    -107, 87, -141, -149, 418, -29
};

// ---------------------------------------------------------
// index: 43
// raw_name: batch_normalization_6/moving_variance
// c_name: main5_batch_normalization_6_moving_variance
// shape: [6]
// numel: 6
// float_min: 0.012820537202060223
// float_max: 0.029121767729520798
// q_min: 53
// q_max: 119
// max_abs_error: 0.00011891592293977737
// mean_abs_error: 7.959936192492023e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_6_MOVING_VARIANCE_NUMEL 6
#define MAIN5_BATCH_NORMALIZATION_6_MOVING_VARIANCE_DIM0 6
static const int16_t main5_batch_normalization_6_moving_variance[6] = {
    53, 116, 119, 115, 79, 93
};

// ---------------------------------------------------------
// index: 44
// raw_name: batch_normalization_7/gamma
// c_name: main5_batch_normalization_7_gamma
// shape: [6]
// numel: 6
// float_min: 0.9905816316604614
// float_max: 1.413671612739563
// q_min: 4057
// q_max: 5790
// max_abs_error: 0.00010311603546142578
// mean_abs_error: 5.287925523589365e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_7_GAMMA_NUMEL 6
#define MAIN5_BATCH_NORMALIZATION_7_GAMMA_DIM0 6
static const int16_t main5_batch_normalization_7_gamma[6] = {
    4279, 4057, 4067, 5021, 5790, 4897
};

// ---------------------------------------------------------
// index: 45
// raw_name: batch_normalization_7/beta
// c_name: main5_batch_normalization_7_beta
// shape: [6]
// numel: 6
// float_min: -0.4054998755455017
// float_max: 0.4558666944503784
// q_min: -1661
// q_max: 1867
// max_abs_error: 0.00011332333087921143
// mean_abs_error: 5.401422458817251e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_7_BETA_NUMEL 6
#define MAIN5_BATCH_NORMALIZATION_7_BETA_DIM0 6
static const int16_t main5_batch_normalization_7_beta[6] = {
    -1661, 290, -666, 366, 345, 1867
};

// ---------------------------------------------------------
// index: 46
// raw_name: batch_normalization_7/moving_mean
// c_name: main5_batch_normalization_7_moving_mean
// shape: [6]
// numel: 6
// float_min: -0.08837182819843292
// float_max: 0.08064132928848267
// q_min: -362
// q_max: 330
// max_abs_error: 9.018927812576294e-05
// mean_abs_error: 3.820409256150015e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_7_MOVING_MEAN_NUMEL 6
#define MAIN5_BATCH_NORMALIZATION_7_MOVING_MEAN_DIM0 6
static const int16_t main5_batch_normalization_7_moving_mean[6] = {
    -56, -332, 330, -362, -214, -242
};

// ---------------------------------------------------------
// index: 47
// raw_name: batch_normalization_7/moving_variance
// c_name: main5_batch_normalization_7_moving_variance
// shape: [6]
// numel: 6
// float_min: 0.014223356731235981
// float_max: 0.0349002368748188
// q_min: 58
// q_max: 143
// max_abs_error: 0.00011200457811355591
// mean_abs_error: 7.513460150221363e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_7_MOVING_VARIANCE_NUMEL 6
#define MAIN5_BATCH_NORMALIZATION_7_MOVING_VARIANCE_DIM0 6
static const int16_t main5_batch_normalization_7_moving_variance[6] = {
    58, 97, 139, 143, 103, 123
};

// ---------------------------------------------------------
// index: 48
// raw_name: batch_normalization_8/gamma
// c_name: main5_batch_normalization_8_gamma
// shape: [6]
// numel: 6
// float_min: 0.9626121520996094
// float_max: 1.260195016860962
// q_min: 3943
// q_max: 5162
// max_abs_error: 0.00011682510375976562
// mean_abs_error: 7.000565528869629e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_8_GAMMA_NUMEL 6
#define MAIN5_BATCH_NORMALIZATION_8_GAMMA_DIM0 6
static const int16_t main5_batch_normalization_8_gamma[6] = {
    4596, 4062, 3943, 5162, 4415, 4601
};

// ---------------------------------------------------------
// index: 49
// raw_name: batch_normalization_8/beta
// c_name: main5_batch_normalization_8_beta
// shape: [6]
// numel: 6
// float_min: -0.2551995515823364
// float_max: 0.41854628920555115
// q_min: -1045
// q_max: 1714
// max_abs_error: 8.925795555114746e-05
// mean_abs_error: 7.390106475213543e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_8_BETA_NUMEL 6
#define MAIN5_BATCH_NORMALIZATION_8_BETA_DIM0 6
static const int16_t main5_batch_normalization_8_beta[6] = {
    1668, -1045, 1714, 360, 282, 1283
};

// ---------------------------------------------------------
// index: 50
// raw_name: batch_normalization_8/moving_mean
// c_name: main5_batch_normalization_8_moving_mean
// shape: [6]
// numel: 6
// float_min: -0.15381024777889252
// float_max: 0.1496962010860443
// q_min: -630
// q_max: 613
// max_abs_error: 0.00011620530858635902
// mean_abs_error: 5.5992743000388145e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_8_MOVING_MEAN_NUMEL 6
#define MAIN5_BATCH_NORMALIZATION_8_MOVING_MEAN_DIM0 6
static const int16_t main5_batch_normalization_8_moving_mean[6] = {
    -226, 82, -630, -31, 613, 541
};

// ---------------------------------------------------------
// index: 51
// raw_name: batch_normalization_8/moving_variance
// c_name: main5_batch_normalization_8_moving_variance
// shape: [6]
// numel: 6
// float_min: 0.033095818012952805
// float_max: 0.08563879877328873
// q_min: 136
// q_max: 351
// max_abs_error: 0.00010730698704719543
// mean_abs_error: 5.7056546211242676e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_8_MOVING_VARIANCE_NUMEL 6
#define MAIN5_BATCH_NORMALIZATION_8_MOVING_VARIANCE_DIM0 6
static const int16_t main5_batch_normalization_8_moving_variance[6] = {
    262, 136, 142, 350, 207, 351
};

// ---------------------------------------------------------
// index: 52
// raw_name: batch_normalization_9/gamma
// c_name: main5_batch_normalization_9_gamma
// shape: [6]
// numel: 6
// float_min: 0.7544585466384888
// float_max: 1.2541477680206299
// q_min: 3090
// q_max: 5137
// max_abs_error: 6.401538848876953e-05
// mean_abs_error: 3.529588502715342e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_9_GAMMA_NUMEL 6
#define MAIN5_BATCH_NORMALIZATION_9_GAMMA_DIM0 6
static const int16_t main5_batch_normalization_9_gamma[6] = {
    4006, 3246, 4750, 3090, 3532, 5137
};

// ---------------------------------------------------------
// index: 53
// raw_name: batch_normalization_9/beta
// c_name: main5_batch_normalization_9_beta
// shape: [6]
// numel: 6
// float_min: -0.18709947168827057
// float_max: 0.6435850858688354
// q_min: -766
// q_max: 2636
// max_abs_error: 8.775293827056885e-05
// mean_abs_error: 5.876272916793823e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_9_BETA_NUMEL 6
#define MAIN5_BATCH_NORMALIZATION_9_BETA_DIM0 6
static const int16_t main5_batch_normalization_9_beta[6] = {
    2007, 1264, -293, 2636, -766, 2435
};

// ---------------------------------------------------------
// index: 54
// raw_name: batch_normalization_9/moving_mean
// c_name: main5_batch_normalization_9_moving_mean
// shape: [6]
// numel: 6
// float_min: -0.24906115233898163
// float_max: 0.4484972059726715
// q_min: -1020
// q_max: 1837
// max_abs_error: 7.426738739013672e-05
// mean_abs_error: 3.7485111533897e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_9_MOVING_MEAN_NUMEL 6
#define MAIN5_BATCH_NORMALIZATION_9_MOVING_MEAN_DIM0 6
static const int16_t main5_batch_normalization_9_moving_mean[6] = {
    1178, 1837, -1020, 1237, 478, -868
};

// ---------------------------------------------------------
// index: 55
// raw_name: batch_normalization_9/moving_variance
// c_name: main5_batch_normalization_9_moving_variance
// shape: [6]
// numel: 6
// float_min: 0.16377678513526917
// float_max: 0.4605391025543213
// q_min: 671
// q_max: 1886
// max_abs_error: 0.00010363757610321045
// mean_abs_error: 5.894402784178965e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_9_MOVING_VARIANCE_NUMEL 6
#define MAIN5_BATCH_NORMALIZATION_9_MOVING_VARIANCE_DIM0 6
static const int16_t main5_batch_normalization_9_moving_variance[6] = {
    1886, 1493, 769, 671, 734, 1048
};

// ---------------------------------------------------------
// index: 56
// raw_name: conv1d_5/kernel
// c_name: main5_conv1d_5_kernel
// shape: [1, 8, 12]
// numel: 96
// float_min: -0.4608045518398285
// float_max: 0.4839882254600525
// q_min: -1887
// q_max: 1982
// max_abs_error: 0.00012147612869739532
// mean_abs_error: 6.837980618001893e-05
// ---------------------------------------------------------
#define MAIN5_CONV1D_5_KERNEL_NUMEL 96
#define MAIN5_CONV1D_5_KERNEL_DIM0 1
#define MAIN5_CONV1D_5_KERNEL_DIM1 8
#define MAIN5_CONV1D_5_KERNEL_DIM2 12
static const int16_t main5_conv1d_5_kernel[96] = {
    -1236, 1385, -1887, 914, -161, 128, 23, 663, 1703, 1084, 355, -863, -499, 1982, 167, 882,
    -222, -1411, -1572, -1522, -796, -758, 1010, -1213, -1475, 873, -1402, 577, 713, -1153, 1201, 305,
    -5, 489, -1205, 806, -1602, 551, 257, -938, 941, 60, 678, -1262, 204, 485, -1615, 999,
    201, -1622, 38, 1054, -106, -788, 390, 1522, 748, -239, -137, 1318, 14, -1023, -222, -1619,
    1411, -582, -379, 1281, -903, 194, -341, 1154, -355, 742, 613, 649, 908, -70, -988, 108,
    246, -638, 566, 298, 624, 43, -362, -866, -891, 1395, -27, -569, -1142, 317, -432, -749
};

// ---------------------------------------------------------
// index: 57
// raw_name: conv1d_4/kernel
// c_name: main5_conv1d_4_kernel
// shape: [1, 24, 12]
// numel: 288
// float_min: -0.4464810788631439
// float_max: 0.5134048461914062
// q_min: -1829
// q_max: 2103
// max_abs_error: 0.0001215469092130661
// mean_abs_error: 6.168770050862804e-05
// ---------------------------------------------------------
#define MAIN5_CONV1D_4_KERNEL_NUMEL 288
#define MAIN5_CONV1D_4_KERNEL_DIM0 1
#define MAIN5_CONV1D_4_KERNEL_DIM1 24
#define MAIN5_CONV1D_4_KERNEL_DIM2 12
static const int16_t main5_conv1d_4_kernel[288] = {
    561, 514, 209, 530, 721, -540, 258, 434, 1482, 470, -146, -543, 804, -431, 730, -675,
    770, 992, 1100, 655, 1264, -897, -485, 219, 242, 644, -1460, -223, 220, -104, 79, 251,
    539, 1112, 361, -960, 1310, 244, -934, -552, -645, -1244, -453, 1284, -651, -171, 187, 54,
    -173, -1248, -774, -638, 0, -994, 15, 1117, -427, 207, 871, -626, 1207, 656, 580, -1620,
    734, 898, -416, 748, -489, 782, -116, 560, 101, 622, 21, 755, -267, 483, -994, -117,
    286, 900, -537, -719, 136, 741, 254, 71, -608, -1064, -298, -683, -379, -591, 975, -374,
    961, -515, 408, -122, 424, 1327, 903, -631, 698, 1273, -967, 653, -1008, 982, -69, 235,
    660, -52, 110, 98, 172, 2103, 483, -241, -1254, 290, -176, -330, -1137, -1786, -192, 439,
    -573, -1117, 619, -259, 34, 1406, -1829, -765, 408, -474, 678, -625, 262, 1490, -1748, -711,
    96, 374, -975, 325, -1033, 84, 1189, -143, -539, -397, 885, 1776, 491, 656, 868, -143,
    1015, 381, -785, 850, 316, 1040, 231, -759, -358, 1141, -909, 517, -659, 643, 207, -724,
    -991, 435, 132, -129, 1366, 815, 963, -795, -447, 1161, -231, 829, 319, 412, -435, -1477,
    -439, -545, 1202, 1021, -566, -472, 978, 180, -1199, 598, 692, -1035, 354, -1134, -91, -1027,
    -440, 872, -772, 1099, -1445, -547, -1217, -388, 870, 1602, -805, -1021, 542, -172, 235, -287,
    -384, -150, -686, -452, -1024, 443, -210, 517, 417, -259, -54, 665, 736, -437, -90, -356,
    324, -1208, -427, 157, 80, 287, 486, 1061, -48, 166, 160, -166, 1046, 541, -881, 455,
    623, -1263, 550, 214, 562, -98, 0, 540, 500, -121, 861, -161, 562, 395, 149, 400,
    -208, 178, 1362, -1070, -692, -809, 386, 1137, 294, -220, -172, 246, 1220, -568, -48, 999
};

// ---------------------------------------------------------
// index: 58
// raw_name: batch_normalization_11/gamma
// c_name: main5_batch_normalization_11_gamma
// shape: [12]
// numel: 12
// float_min: 0.6707319617271423
// float_max: 1.2516441345214844
// q_min: 2747
// q_max: 5127
// max_abs_error: 0.00011849403381347656
// mean_abs_error: 4.958609861205332e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_11_GAMMA_NUMEL 12
#define MAIN5_BATCH_NORMALIZATION_11_GAMMA_DIM0 12
static const int16_t main5_batch_normalization_11_gamma[12] = {
    4265, 4423, 4637, 4090, 3703, 3702, 3211, 3874, 3540, 2906, 5127, 2747
};

// ---------------------------------------------------------
// index: 59
// raw_name: batch_normalization_11/beta
// c_name: main5_batch_normalization_11_beta
// shape: [12]
// numel: 12
// float_min: -0.21815122663974762
// float_max: 0.2811429500579834
// q_min: -894
// q_max: 1152
// max_abs_error: 0.00012053176760673523
// mean_abs_error: 8.547189645469189e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_11_BETA_NUMEL 12
#define MAIN5_BATCH_NORMALIZATION_11_BETA_DIM0 12
static const int16_t main5_batch_normalization_11_beta[12] = {
    1152, 323, -616, -138, 48, -766, 295, -894, -422, -310, 152, -29
};

// ---------------------------------------------------------
// index: 60
// raw_name: batch_normalization_11/moving_mean
// c_name: main5_batch_normalization_11_moving_mean
// shape: [12]
// numel: 12
// float_min: -0.3745152950286865
// float_max: 0.24657635390758514
// q_min: -1534
// q_max: 1010
// max_abs_error: 0.00010707974433898926
// mean_abs_error: 4.721960794995539e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_11_MOVING_MEAN_NUMEL 12
#define MAIN5_BATCH_NORMALIZATION_11_MOVING_MEAN_DIM0 12
static const int16_t main5_batch_normalization_11_moving_mean[12] = {
    -1534, 437, -950, 286, 546, -770, 350, 146, 189, 468, -1188, 1010
};

// ---------------------------------------------------------
// index: 61
// raw_name: batch_normalization_11/moving_variance
// c_name: main5_batch_normalization_11_moving_variance
// shape: [12]
// numel: 12
// float_min: 0.13082635402679443
// float_max: 0.49677643179893494
// q_min: 536
// q_max: 2035
// max_abs_error: 0.00011757016181945801
// mean_abs_error: 6.075327473809011e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_11_MOVING_VARIANCE_NUMEL 12
#define MAIN5_BATCH_NORMALIZATION_11_MOVING_VARIANCE_DIM0 12
static const int16_t main5_batch_normalization_11_moving_variance[12] = {
    1729, 1033, 745, 2035, 1023, 1508, 923, 1094, 536, 686, 1633, 1274
};

// ---------------------------------------------------------
// index: 62
// raw_name: batch_normalization_10/gamma
// c_name: main5_batch_normalization_10_gamma
// shape: [12]
// numel: 12
// float_min: 0.894221305847168
// float_max: 1.458098292350769
// q_min: 3663
// q_max: 5972
// max_abs_error: 0.00011718273162841797
// mean_abs_error: 7.525086402893066e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_10_GAMMA_NUMEL 12
#define MAIN5_BATCH_NORMALIZATION_10_GAMMA_DIM0 12
static const int16_t main5_batch_normalization_10_gamma[12] = {
    4349, 3852, 4097, 3899, 3663, 4513, 3911, 4342, 3685, 4130, 4312, 5972
};

// ---------------------------------------------------------
// index: 63
// raw_name: batch_normalization_10/beta
// c_name: main5_batch_normalization_10_beta
// shape: [12]
// numel: 12
// float_min: -0.21815122663974762
// float_max: 0.2811429500579834
// q_min: -894
// q_max: 1152
// max_abs_error: 0.00012053176760673523
// mean_abs_error: 8.547189645469189e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_10_BETA_NUMEL 12
#define MAIN5_BATCH_NORMALIZATION_10_BETA_DIM0 12
static const int16_t main5_batch_normalization_10_beta[12] = {
    1152, 323, -616, -138, 48, -766, 295, -894, -422, -310, 152, -29
};

// ---------------------------------------------------------
// index: 64
// raw_name: batch_normalization_10/moving_mean
// c_name: main5_batch_normalization_10_moving_mean
// shape: [12]
// numel: 12
// float_min: -0.6017175912857056
// float_max: 0.6224927306175232
// q_min: -2465
// q_max: 2550
// max_abs_error: 0.00010010600090026855
// mean_abs_error: 5.063693970441818e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_10_MOVING_MEAN_NUMEL 12
#define MAIN5_BATCH_NORMALIZATION_10_MOVING_MEAN_DIM0 12
static const int16_t main5_batch_normalization_10_moving_mean[12] = {
    1403, 2550, -2465, -749, 133, -898, 1250, 1754, -216, 1243, -685, -390
};

// ---------------------------------------------------------
// index: 65
// raw_name: batch_normalization_10/moving_variance
// c_name: main5_batch_normalization_10_moving_variance
// shape: [12]
// numel: 12
// float_min: 0.2379758208990097
// float_max: 0.5838934779167175
// q_min: 975
// q_max: 2392
// max_abs_error: 9.274482727050781e-05
// mean_abs_error: 5.6964654504554346e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_10_MOVING_VARIANCE_NUMEL 12
#define MAIN5_BATCH_NORMALIZATION_10_MOVING_VARIANCE_DIM0 12
static const int16_t main5_batch_normalization_10_moving_variance[12] = {
    1927, 1207, 1181, 1251, 975, 2392, 1596, 2388, 1221, 1019, 1106, 1940
};

// ---------------------------------------------------------
// index: 66
// raw_name: separable_conv1d_6/depthwise_kernel
// c_name: main5_separable_conv1d_6_depthwise_kernel
// shape: [3, 12, 1]
// numel: 36
// float_min: -0.39271673560142517
// float_max: 0.3583594262599945
// q_min: -1609
// q_max: 1468
// max_abs_error: 0.00011986494064331055
// mean_abs_error: 5.479974424815737e-05
// ---------------------------------------------------------
#define MAIN5_SEPARABLE_CONV1D_6_DEPTHWISE_KERNEL_NUMEL 36
#define MAIN5_SEPARABLE_CONV1D_6_DEPTHWISE_KERNEL_DIM0 3
#define MAIN5_SEPARABLE_CONV1D_6_DEPTHWISE_KERNEL_DIM1 12
#define MAIN5_SEPARABLE_CONV1D_6_DEPTHWISE_KERNEL_DIM2 1
static const int16_t main5_separable_conv1d_6_depthwise_kernel[36] = {
    1084, 857, -1302, -1609, 869, 233, 14, 1187, -1261, 526, 830, 289, 220, 312, 1362, 128,
    355, 1468, -1320, 194, 520, 1330, 12, 587, -1303, 587, 935, 472, -433, -413, 821, -768,
    -1095, 429, -373, 218
};

// ---------------------------------------------------------
// index: 67
// raw_name: separable_conv1d_6/pointwise_kernel
// c_name: main5_separable_conv1d_6_pointwise_kernel
// shape: [1, 12, 8]
// numel: 96
// float_min: -0.4722177982330322
// float_max: 0.44242173433303833
// q_min: -1934
// q_max: 1812
// max_abs_error: 0.00012162327766418457
// mean_abs_error: 6.721721001667902e-05
// ---------------------------------------------------------
#define MAIN5_SEPARABLE_CONV1D_6_POINTWISE_KERNEL_NUMEL 96
#define MAIN5_SEPARABLE_CONV1D_6_POINTWISE_KERNEL_DIM0 1
#define MAIN5_SEPARABLE_CONV1D_6_POINTWISE_KERNEL_DIM1 12
#define MAIN5_SEPARABLE_CONV1D_6_POINTWISE_KERNEL_DIM2 8
static const int16_t main5_separable_conv1d_6_pointwise_kernel[96] = {
    -918, -474, 1502, 827, -276, 374, -641, -1255, 414, -749, -663, -1304, -1299, 236, 744, -106,
    1665, 605, -254, -958, 30, -759, 105, 1234, 897, -347, -617, 235, -1021, -1934, -33, -793,
    -523, 1130, 611, -1007, -237, -210, -601, -470, -198, 1125, -962, 744, 498, -289, -74, -857,
    8, -531, 1100, 530, -886, 279, -120, 1054, -925, 611, -305, 817, 301, 118, 1812, 117,
    -450, -1090, 1378, 101, 228, -911, -339, -550, 721, 687, 251, -1254, 958, -380, -229, -1160,
    -850, -178, 119, 232, 648, 410, -514, 476, 100, -477, -182, -292, -205, -699, -251, 506
};

// ---------------------------------------------------------
// index: 68
// raw_name: separable_conv1d_7/depthwise_kernel
// c_name: main5_separable_conv1d_7_depthwise_kernel
// shape: [5, 12, 1]
// numel: 60
// float_min: -0.3747042417526245
// float_max: 0.30910104513168335
// q_min: -1535
// q_max: 1266
// max_abs_error: 0.00011383742094039917
// mean_abs_error: 5.55760707356967e-05
// ---------------------------------------------------------
#define MAIN5_SEPARABLE_CONV1D_7_DEPTHWISE_KERNEL_NUMEL 60
#define MAIN5_SEPARABLE_CONV1D_7_DEPTHWISE_KERNEL_DIM0 5
#define MAIN5_SEPARABLE_CONV1D_7_DEPTHWISE_KERNEL_DIM1 12
#define MAIN5_SEPARABLE_CONV1D_7_DEPTHWISE_KERNEL_DIM2 1
static const int16_t main5_separable_conv1d_7_depthwise_kernel[60] = {
    801, 961, 359, -484, 339, -1535, 420, 381, 608, 628, 23, -304, 459, 963, 214, -337,
    -443, 1159, 53, 1045, -495, -376, -1234, -779, 191, 149, -1024, 552, -845, -282, -562, -83,
    648, -407, 395, -445, 8, -85, 343, 233, -31, 781, -966, -760, 167, 23, -104, -73,
    -1025, -1064, 1266, -1363, -1027, -501, 724, 163, 700, 932, 1040, -430
};

// ---------------------------------------------------------
// index: 69
// raw_name: separable_conv1d_7/pointwise_kernel
// c_name: main5_separable_conv1d_7_pointwise_kernel
// shape: [1, 12, 8]
// numel: 96
// float_min: -0.41090986132621765
// float_max: 0.5421474575996399
// q_min: -1683
// q_max: 2221
// max_abs_error: 0.00012151896953582764
// mean_abs_error: 6.531747203553095e-05
// ---------------------------------------------------------
#define MAIN5_SEPARABLE_CONV1D_7_POINTWISE_KERNEL_NUMEL 96
#define MAIN5_SEPARABLE_CONV1D_7_POINTWISE_KERNEL_DIM0 1
#define MAIN5_SEPARABLE_CONV1D_7_POINTWISE_KERNEL_DIM1 12
#define MAIN5_SEPARABLE_CONV1D_7_POINTWISE_KERNEL_DIM2 8
static const int16_t main5_separable_conv1d_7_pointwise_kernel[96] = {
    -1683, 969, 3, 259, -78, 500, -7, -276, -776, 1793, 504, -343, 1196, 28, 437, -1055,
    -330, -1006, -619, -928, -192, -1609, 549, 282, -292, 311, -1291, -224, -501, 525, 717, 996,
    -1232, 47, 1383, -893, -187, -578, -819, 185, -429, -337, 748, 1035, 2221, -88, 487, 377,
    -654, -26, 270, -646, -1042, -878, 558, 44, 4, 190, -521, 361, 392, 166, 759, -946,
    1115, -1331, 402, 393, 587, 581, 278, -162, 153, 441, -83, -553, -247, 1156, 648, -448,
    551, 223, -73, -1579, 920, 142, -757, -687, -321, -658, -1079, -801, -63, -393, -759, 384
};

// ---------------------------------------------------------
// index: 70
// raw_name: separable_conv1d_8/depthwise_kernel
// c_name: main5_separable_conv1d_8_depthwise_kernel
// shape: [7, 12, 1]
// numel: 84
// float_min: -0.5060117840766907
// float_max: 0.40759631991386414
// q_min: -2073
// q_max: 1670
// max_abs_error: 0.0001211315393447876
// mean_abs_error: 6.079434388084337e-05
// ---------------------------------------------------------
#define MAIN5_SEPARABLE_CONV1D_8_DEPTHWISE_KERNEL_NUMEL 84
#define MAIN5_SEPARABLE_CONV1D_8_DEPTHWISE_KERNEL_DIM0 7
#define MAIN5_SEPARABLE_CONV1D_8_DEPTHWISE_KERNEL_DIM1 12
#define MAIN5_SEPARABLE_CONV1D_8_DEPTHWISE_KERNEL_DIM2 1
static const int16_t main5_separable_conv1d_8_depthwise_kernel[84] = {
    859, -456, -784, 804, -175, -544, -207, 135, -1009, -1016, -1632, -2073, 486, -416, -181, 1670,
    349, 54, 935, -458, -105, 124, -338, -867, -775, -392, -236, -420, -306, 58, -49, 1608,
    -786, 497, 244, -425, -573, 51, -475, 254, -290, -301, 127, -765, 271, -528, -31, 379,
    -501, 801, 150, 190, 224, -1194, 788, 498, -636, -29, 375, 406, 342, 597, -743, -405,
    266, -173, 188, -739, 7, -314, 693, 666, 871, -553, 1087, -205, 1353, -1329, -941, 340,
    238, 656, 458, -70
};

// ---------------------------------------------------------
// index: 71
// raw_name: separable_conv1d_8/pointwise_kernel
// c_name: main5_separable_conv1d_8_pointwise_kernel
// shape: [1, 12, 8]
// numel: 96
// float_min: -0.531588613986969
// float_max: 0.5589758157730103
// q_min: -2177
// q_max: 2290
// max_abs_error: 0.00011929124593734741
// mean_abs_error: 5.876777504454367e-05
// ---------------------------------------------------------
#define MAIN5_SEPARABLE_CONV1D_8_POINTWISE_KERNEL_NUMEL 96
#define MAIN5_SEPARABLE_CONV1D_8_POINTWISE_KERNEL_DIM0 1
#define MAIN5_SEPARABLE_CONV1D_8_POINTWISE_KERNEL_DIM1 12
#define MAIN5_SEPARABLE_CONV1D_8_POINTWISE_KERNEL_DIM2 8
static const int16_t main5_separable_conv1d_8_pointwise_kernel[96] = {
    -1, 400, 1348, 149, 433, 1395, 502, -357, 1575, 1167, -234, 551, -649, 199, -1315, 428,
    -1679, 709, -357, -1400, 240, 683, 456, 83, 0, -2036, 585, 628, -390, -641, -1562, -972,
    -535, 259, 37, 151, 25, -1823, 292, 202, -254, -1543, 148, -486, -183, 1420, -505, -9,
    747, 69, 0, -2177, 330, 406, 171, -626, -1100, -947, 926, -950, -927, -169, 1088, -1263,
    -259, 818, 762, 1003, -1043, 488, -869, 237, -381, 497, -563, 745, -1196, -70, 1117, -582,
    -910, -580, -1495, -766, 2030, -462, 850, 1080, -159, -309, 1420, 1244, 291, -848, -728, 2290
};

// ---------------------------------------------------------
// index: 72
// raw_name: conv1d_6/kernel
// c_name: main5_conv1d_6_kernel
// shape: [1, 12, 8]
// numel: 96
// float_min: -0.38949859142303467
// float_max: 0.2978842556476593
// q_min: -1595
// q_max: 1220
// max_abs_error: 0.00011917948722839355
// mean_abs_error: 6.139622564660385e-05
// ---------------------------------------------------------
#define MAIN5_CONV1D_6_KERNEL_NUMEL 96
#define MAIN5_CONV1D_6_KERNEL_DIM0 1
#define MAIN5_CONV1D_6_KERNEL_DIM1 12
#define MAIN5_CONV1D_6_KERNEL_DIM2 8
static const int16_t main5_conv1d_6_kernel[96] = {
    -361, -876, 49, -922, -307, 683, -800, 624, -89, -153, -1249, 347, -1595, -274, -1197, 428,
    192, -508, -1446, -1285, -475, -746, 314, 1180, -343, -693, 253, 96, 880, 1055, -1398, 268,
    217, -516, 947, 162, -921, 513, -340, 528, 574, 367, -140, -1136, 352, 452, -486, 398,
    490, -1355, 449, -522, 587, 729, 135, 443, 27, 1220, 619, 547, 962, -402, -740, 126,
    563, -863, 1112, -942, -101, 103, -1407, -521, 1019, -549, 28, 585, 659, -565, -680, -136,
    -1430, -846, -167, -512, -1499, 1172, 182, -1047, 524, 770, -709, 10, -881, 458, -169, -412
};

// ---------------------------------------------------------
// index: 73
// raw_name: batch_normalization_12/gamma
// c_name: main5_batch_normalization_12_gamma
// shape: [8]
// numel: 8
// float_min: 0.7514569163322449
// float_max: 1.5867856740951538
// q_min: 3078
// q_max: 6499
// max_abs_error: 0.0001157522201538086
// mean_abs_error: 4.4055283069610596e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_12_GAMMA_NUMEL 8
#define MAIN5_BATCH_NORMALIZATION_12_GAMMA_DIM0 8
static const int16_t main5_batch_normalization_12_gamma[8] = {
    3838, 3293, 4592, 6499, 3078, 3777, 3273, 4994
};

// ---------------------------------------------------------
// index: 74
// raw_name: batch_normalization_12/beta
// c_name: main5_batch_normalization_12_beta
// shape: [8]
// numel: 8
// float_min: -0.13687510788440704
// float_max: 0.4243635833263397
// q_min: -561
// q_max: 1738
// max_abs_error: 0.00011213123798370361
// mean_abs_error: 5.786679685115814e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_12_BETA_NUMEL 8
#define MAIN5_BATCH_NORMALIZATION_12_BETA_DIM0 8
static const int16_t main5_batch_normalization_12_beta[8] = {
    -458, 816, 508, 1010, -561, -287, 811, 1738
};

// ---------------------------------------------------------
// index: 75
// raw_name: batch_normalization_12/moving_mean
// c_name: main5_batch_normalization_12_moving_mean
// shape: [8]
// numel: 8
// float_min: -0.16252459585666656
// float_max: 0.0800686925649643
// q_min: -666
// q_max: 328
// max_abs_error: 0.0001193508505821228
// mean_abs_error: 5.596026312559843e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_12_MOVING_MEAN_NUMEL 8
#define MAIN5_BATCH_NORMALIZATION_12_MOVING_MEAN_DIM0 8
static const int16_t main5_batch_normalization_12_moving_mean[8] = {
    191, 328, -258, -666, 98, 72, 123, -24
};

// ---------------------------------------------------------
// index: 76
// raw_name: batch_normalization_12/moving_variance
// c_name: main5_batch_normalization_12_moving_variance
// shape: [8]
// numel: 8
// float_min: 0.019610688090324402
// float_max: 0.15814775228500366
// q_min: 80
// q_max: 648
// max_abs_error: 0.00011486932635307312
// mean_abs_error: 7.563061080873013e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_12_MOVING_VARIANCE_NUMEL 8
#define MAIN5_BATCH_NORMALIZATION_12_MOVING_VARIANCE_DIM0 8
static const int16_t main5_batch_normalization_12_moving_variance[8] = {
    230, 380, 174, 648, 96, 80, 143, 487
};

// ---------------------------------------------------------
// index: 77
// raw_name: batch_normalization_13/gamma
// c_name: main5_batch_normalization_13_gamma
// shape: [8]
// numel: 8
// float_min: 0.7870327234268188
// float_max: 1.2969907522201538
// q_min: 3224
// q_max: 5312
// max_abs_error: 0.0001175999641418457
// mean_abs_error: 8.400529623031616e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_13_GAMMA_NUMEL 8
#define MAIN5_BATCH_NORMALIZATION_13_GAMMA_DIM0 8
static const int16_t main5_batch_normalization_13_gamma[8] = {
    5312, 3754, 4060, 3224, 3763, 3978, 3739, 3886
};

// ---------------------------------------------------------
// index: 78
// raw_name: batch_normalization_13/beta
// c_name: main5_batch_normalization_13_beta
// shape: [8]
// numel: 8
// float_min: -0.25942716002464294
// float_max: 0.571679949760437
// q_min: -1063
// q_max: 2342
// max_abs_error: 9.739398956298828e-05
// mean_abs_error: 7.581739919260144e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_13_BETA_NUMEL 8
#define MAIN5_BATCH_NORMALIZATION_13_BETA_DIM0 8
static const int16_t main5_batch_normalization_13_beta[8] = {
    -929, 1739, 1479, 2342, -1063, 1135, 20, 1236
};

// ---------------------------------------------------------
// index: 79
// raw_name: batch_normalization_13/moving_mean
// c_name: main5_batch_normalization_13_moving_mean
// shape: [8]
// numel: 8
// float_min: -0.10550201684236526
// float_max: 0.10032447427511215
// q_min: -432
// q_max: 411
// max_abs_error: 0.00011870265007019043
// mean_abs_error: 7.52053310861811e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_13_MOVING_MEAN_NUMEL 8
#define MAIN5_BATCH_NORMALIZATION_13_MOVING_MEAN_DIM0 8
static const int16_t main5_batch_normalization_13_moving_mean[8] = {
    294, 121, -6, 271, 296, 162, 411, -432
};

// ---------------------------------------------------------
// index: 80
// raw_name: batch_normalization_13/moving_variance
// c_name: main5_batch_normalization_13_moving_variance
// shape: [8]
// numel: 8
// float_min: 0.046551939100027084
// float_max: 0.1198054701089859
// q_min: 191
// q_max: 491
// max_abs_error: 8.388608694076538e-05
// mean_abs_error: 4.858756437897682e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_13_MOVING_VARIANCE_NUMEL 8
#define MAIN5_BATCH_NORMALIZATION_13_MOVING_VARIANCE_DIM0 8
static const int16_t main5_batch_normalization_13_moving_variance[8] = {
    491, 346, 313, 360, 212, 292, 292, 191
};

// ---------------------------------------------------------
// index: 81
// raw_name: batch_normalization_14/gamma
// c_name: main5_batch_normalization_14_gamma
// shape: [8]
// numel: 8
// float_min: 0.9043788313865662
// float_max: 1.3465991020202637
// q_min: 3704
// q_max: 5516
// max_abs_error: 0.0001157522201538086
// mean_abs_error: 9.118020534515381e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_14_GAMMA_NUMEL 8
#define MAIN5_BATCH_NORMALIZATION_14_GAMMA_DIM0 8
static const int16_t main5_batch_normalization_14_gamma[8] = {
    4238, 5036, 3978, 4613, 4521, 5297, 3704, 5516
};

// ---------------------------------------------------------
// index: 82
// raw_name: batch_normalization_14/beta
// c_name: main5_batch_normalization_14_beta
// shape: [8]
// numel: 8
// float_min: -0.2576799988746643
// float_max: 0.5681039690971375
// q_min: -1055
// q_max: 2327
// max_abs_error: 0.00011163949966430664
// mean_abs_error: 4.211894702166319e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_14_BETA_NUMEL 8
#define MAIN5_BATCH_NORMALIZATION_14_BETA_DIM0 8
static const int16_t main5_batch_normalization_14_beta[8] = {
    529, 278, 57, 704, 1004, 2327, 830, -1055
};

// ---------------------------------------------------------
// index: 83
// raw_name: batch_normalization_14/moving_mean
// c_name: main5_batch_normalization_14_moving_mean
// shape: [8]
// numel: 8
// float_min: -0.18163195252418518
// float_max: 0.05592102184891701
// q_min: -744
// q_max: 229
// max_abs_error: 9.825080633163452e-05
// mean_abs_error: 4.748557694256306e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_14_MOVING_MEAN_NUMEL 8
#define MAIN5_BATCH_NORMALIZATION_14_MOVING_MEAN_DIM0 8
static const int16_t main5_batch_normalization_14_moving_mean[8] = {
    229, -313, 62, -279, 26, -322, 79, -744
};

// ---------------------------------------------------------
// index: 84
// raw_name: batch_normalization_14/moving_variance
// c_name: main5_batch_normalization_14_moving_variance
// shape: [8]
// numel: 8
// float_min: 0.08964494615793228
// float_max: 0.20794950425624847
// q_min: 367
// q_max: 852
// max_abs_error: 9.872019290924072e-05
// mean_abs_error: 4.850327968597412e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_14_MOVING_VARIANCE_NUMEL 8
#define MAIN5_BATCH_NORMALIZATION_14_MOVING_VARIANCE_DIM0 8
static const int16_t main5_batch_normalization_14_moving_variance[8] = {
    417, 681, 367, 852, 446, 677, 487, 742
};

// ---------------------------------------------------------
// index: 85
// raw_name: batch_normalization_15/gamma
// c_name: main5_batch_normalization_15_gamma
// shape: [8]
// numel: 8
// float_min: 0.8233023285865784
// float_max: 1.5502208471298218
// q_min: 3372
// q_max: 6350
// max_abs_error: 9.834766387939453e-05
// mean_abs_error: 6.432086229324341e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_15_GAMMA_NUMEL 8
#define MAIN5_BATCH_NORMALIZATION_15_GAMMA_DIM0 8
static const int16_t main5_batch_normalization_15_gamma[8] = {
    3372, 4697, 3637, 4546, 4041, 3383, 6350, 3984
};

// ---------------------------------------------------------
// index: 86
// raw_name: batch_normalization_15/beta
// c_name: main5_batch_normalization_15_beta
// shape: [8]
// numel: 8
// float_min: -0.3696822226047516
// float_max: 0.606158435344696
// q_min: -1514
// q_max: 2483
// max_abs_error: 0.00010953843593597412
// mean_abs_error: 7.055894820950925e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_15_BETA_NUMEL 8
#define MAIN5_BATCH_NORMALIZATION_15_BETA_DIM0 8
static const int16_t main5_batch_normalization_15_beta[8] = {
    -832, 1304, -1514, -7, 407, -447, 2483, -499
};

// ---------------------------------------------------------
// index: 87
// raw_name: batch_normalization_15/moving_mean
// c_name: main5_batch_normalization_15_moving_mean
// shape: [8]
// numel: 8
// float_min: -0.9906065464019775
// float_max: 0.5819214582443237
// q_min: -4058
// q_max: 2384
// max_abs_error: 0.00011610984802246094
// mean_abs_error: 8.07764008641243e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_15_MOVING_MEAN_NUMEL 8
#define MAIN5_BATCH_NORMALIZATION_15_MOVING_MEAN_DIM0 8
static const int16_t main5_batch_normalization_15_moving_mean[8] = {
    183, -3306, -511, -2224, -2435, 2384, -4058, 1383
};

// ---------------------------------------------------------
// index: 88
// raw_name: batch_normalization_15/moving_variance
// c_name: main5_batch_normalization_15_moving_variance
// shape: [8]
// numel: 8
// float_min: 0.4240570366382599
// float_max: 3.479811906814575
// q_min: 1737
// q_max: 14253
// max_abs_error: 0.00011986494064331055
// mean_abs_error: 5.2597373723983765e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_15_MOVING_VARIANCE_NUMEL 8
#define MAIN5_BATCH_NORMALIZATION_15_MOVING_VARIANCE_DIM0 8
static const int16_t main5_batch_normalization_15_moving_variance[8] = {
    3164, 4361, 2866, 2215, 2049, 1737, 14253, 2760
};

// ---------------------------------------------------------
// index: 89
// raw_name: conv1d_8/kernel
// c_name: main5_conv1d_8_kernel
// shape: [1, 12, 16]
// numel: 192
// float_min: -0.4168640375137329
// float_max: 0.4007568359375
// q_min: -1707
// q_max: 1642
// max_abs_error: 0.0001220703125
// mean_abs_error: 6.458092684624717e-05
// ---------------------------------------------------------
#define MAIN5_CONV1D_8_KERNEL_NUMEL 192
#define MAIN5_CONV1D_8_KERNEL_DIM0 1
#define MAIN5_CONV1D_8_KERNEL_DIM1 12
#define MAIN5_CONV1D_8_KERNEL_DIM2 16
static const int16_t main5_conv1d_8_kernel[192] = {
    -1063, -442, 1015, -624, -1267, 462, -634, -346, 902, 767, 227, 442, 22, -92, 146, -560,
    552, -1083, -1206, -202, 380, 370, 388, 729, -1029, -227, 587, -50, -106, 862, 842, -237,
    121, -553, 1158, 971, -529, 1170, -1707, -580, 299, 871, -761, 1218, 740, -844, 1133, -507,
    -198, -149, 833, -447, -912, -448, -106, 755, -348, 154, -262, -722, -85, 477, -304, -709,
    -665, -547, -916, -1092, 156, 206, -120, 566, 1070, 874, 1455, 489, -990, 694, -16, -544,
    -1011, -587, -599, -372, 220, -282, -481, 511, -201, 1642, 953, 46, 336, 49, 19, -596,
    106, -736, -82, 385, 286, 54, 516, 274, 459, -259, 395, 537, -1399, 469, 458, 148,
    -917, -296, 412, -546, -1002, 1067, -309, 528, 1177, 529, -157, -802, -66, 730, -655, -831,
    -48, -464, 458, 148, 179, 595, 254, 1456, 178, -350, -652, -783, 792, 495, -1227, -797,
    -583, -931, 40, -479, -299, -16, 546, 315, 208, -173, -392, 1349, -532, 652, 1280, -590,
    783, 37, -179, -1057, -1320, 870, 176, -111, 281, -204, -710, 670, 410, 966, 919, -1139,
    486, -86, 489, -580, 464, -232, 13, 467, 882, 738, 1287, 338, -1136, 878, 431, 486
};

// ---------------------------------------------------------
// index: 90
// raw_name: conv1d_7/kernel
// c_name: main5_conv1d_7_kernel
// shape: [1, 32, 16]
// numel: 512
// float_min: -0.4289909601211548
// float_max: 0.4735863208770752
// q_min: -1757
// q_max: 1940
// max_abs_error: 0.0001214444637298584
// mean_abs_error: 6.056164420442656e-05
// ---------------------------------------------------------
#define MAIN5_CONV1D_7_KERNEL_NUMEL 512
#define MAIN5_CONV1D_7_KERNEL_DIM0 1
#define MAIN5_CONV1D_7_KERNEL_DIM1 32
#define MAIN5_CONV1D_7_KERNEL_DIM2 16
static const int16_t main5_conv1d_7_kernel[512] = {
    334, 525, -221, 421, -142, -1247, 572, 651, 850, 121, 334, -860, -508, -321, 851, 228,
    183, -668, 887, -45, -1, -1066, 41, 625, -686, 438, 712, 177, 806, 100, 261, 133,
    24, 504, -127, 577, -624, -1221, -68, 238, -829, 547, 139, 893, 938, 440, 127, 195,
    565, 238, 1940, 474, 738, 1246, -720, 179, -109, 305, -84, -68, -541, -175, -676, 1108,
    -583, 63, -357, 529, -798, -119, -279, 641, 98, 259, 525, -118, 364, 57, -598, 400,
    656, -645, -8, -687, -94, -422, -502, 707, 1120, 383, -114, 406, -452, -718, 644, -198,
    -472, 167, 136, 390, -391, -767, 243, 310, 17, -157, 623, 766, 623, -774, -9, -6,
    -465, -1067, -366, -581, -730, 212, -1673, -689, 853, -434, 134, -125, -683, 246, 389, -1040,
    1008, 482, 978, 23, -971, -915, 508, -479, -739, 258, -1321, -1059, 406, -216, -158, 125,
    -899, 597, 367, -231, 1160, -822, -546, 393, -1235, 201, -76, 642, -329, -27, -745, 679,
    209, -308, -399, 514, 390, 169, -1117, -626, 171, 452, -388, 670, 159, 631, -720, -248,
    945, 557, -168, 400, 476, 1006, -393, -953, 914, 266, -593, 626, -282, 953, -84, 64,
    -705, 976, -424, 624, -670, -502, -100, -195, 545, 762, 448, 342, 731, 312, -251, 837,
    1147, 712, -758, 116, -62, 327, 162, 428, -244, -322, -47, 843, 62, -551, -813, -915,
    -740, -852, 414, 444, 145, 399, -198, 171, 367, -666, -629, 381, 174, -1043, -347, 105,
    909, -41, -209, 278, 249, -767, 566, -458, -90, 790, -81, 345, 801, 527, -253, 290,
    -570, 1383, -950, 1334, -424, 319, -157, -852, -962, -1413, -962, 418, -59, -917, -329, -666,
    -1144, 61, -478, -941, 1041, -35, -184, 991, -894, -470, 584, -765, 1774, 324, 409, -1279,
    451, -208, 387, 541, 1146, -270, 893, -50, -499, -653, -423, -505, -942, 642, -288, -521,
    440, 339, 105, 807, -924, 175, 40, 161, -668, -374, 416, -564, 672, 1301, 1737, 691,
    -53, 669, 931, 110, 184, 150, 1518, -479, -864, -651, -140, 20, 438, 188, -659, -1032,
    506, -1580, -1270, 965, -772, -465, 1200, -1019, 20, -1268, 405, 322, -132, -1070, -225, -275,
    -228, 364, 431, -662, 121, 30, -124, -1171, 81, 1037, -1166, -107, 376, -933, 1505, -1174,
    654, -1259, 1065, 979, -581, -361, -147, 329, 339, 1069, 366, 245, -1202, 195, -1004, -1675,
    223, 55, -490, -603, -686, 507, -557, -1148, 14, -576, 257, 255, -517, -21, -546, 1163,
    -543, -218, -254, -6, -437, -30, -836, -129, 644, 313, 1509, 291, 622, 1158, 444, -99,
    -398, -221, -206, 916, 761, 48, -2, -136, -839, -765, 467, -106, 25, 152, 1092, 44,
    505, -634, 333, 833, -305, -1173, 598, 166, 18, -566, -189, 275, 346, -551, -531, 217,
    -321, 693, 727, -645, 362, 4, 277, -273, -6, -117, -210, 337, 499, -46, 329, -576,
    -1049, -193, 245, -903, -973, 11, 122, 255, 13, -246, 127, -2, 597, -171, -349, -46,
    271, 1020, -371, 868, 1926, -696, -1146, -1757, -960, 954, 1039, -1210, 102, -74, -709, 934,
    543, -1135, -505, -54, -322, -503, -358, 479, 424, -136, -602, -508, 543, 273, 336, -205
};

// ---------------------------------------------------------
// index: 91
// raw_name: batch_normalization_17/gamma
// c_name: main5_batch_normalization_17_gamma
// shape: [16]
// numel: 16
// float_min: 0.5689971446990967
// float_max: 1.0243555307388306
// q_min: 2331
// q_max: 4196
// max_abs_error: 0.00011628866195678711
// mean_abs_error: 5.952268838882446e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_17_GAMMA_NUMEL 16
#define MAIN5_BATCH_NORMALIZATION_17_GAMMA_DIM0 16
static const int16_t main5_batch_normalization_17_gamma[16] = {
    4196, 3494, 2822, 2334, 3408, 2446, 3140, 3321, 3542, 3735, 3618, 3458, 2777, 3039, 2331, 3933
};

// ---------------------------------------------------------
// index: 92
// raw_name: batch_normalization_17/beta
// c_name: main5_batch_normalization_17_beta
// shape: [16]
// numel: 16
// float_min: -0.2910667061805725
// float_max: 0.4773736000061035
// q_min: -1192
// q_max: 1955
// max_abs_error: 0.00012069940567016602
// mean_abs_error: 6.0088641475886106e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_17_BETA_NUMEL 16
#define MAIN5_BATCH_NORMALIZATION_17_BETA_DIM0 16
static const int16_t main5_batch_normalization_17_beta[16] = {
    685, 1955, -170, -606, 658, 707, 45, 38, 1445, -1192, 486, -34, -702, -401, -718, 225
};

// ---------------------------------------------------------
// index: 93
// raw_name: batch_normalization_17/moving_mean
// c_name: main5_batch_normalization_17_moving_mean
// shape: [16]
// numel: 16
// float_min: -0.573344886302948
// float_max: 0.5396076440811157
// q_min: -2348
// q_max: 2210
// max_abs_error: 0.00011005997657775879
// mean_abs_error: 6.154272705316544e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_17_MOVING_MEAN_NUMEL 16
#define MAIN5_BATCH_NORMALIZATION_17_MOVING_MEAN_DIM0 16
static const int16_t main5_batch_normalization_17_moving_mean[16] = {
    -658, -2270, 699, -1760, -1990, 1822, -588, 1300, 1845, 1455, 684, 1577, -1106, 2210, 1738, -2348
};

// ---------------------------------------------------------
// index: 94
// raw_name: batch_normalization_17/moving_variance
// c_name: main5_batch_normalization_17_moving_variance
// shape: [16]
// numel: 16
// float_min: 0.43748530745506287
// float_max: 1.1552164554595947
// q_min: 1792
// q_max: 4732
// max_abs_error: 0.00012159347534179688
// mean_abs_error: 6.0249119997024536e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_17_MOVING_VARIANCE_NUMEL 16
#define MAIN5_BATCH_NORMALIZATION_17_MOVING_VARIANCE_DIM0 16
static const int16_t main5_batch_normalization_17_moving_variance[16] = {
    2303, 4732, 1966, 2441, 3225, 2503, 1976, 3700, 3789, 2635, 2930, 2100, 3618, 4385, 1792, 4172
};

// ---------------------------------------------------------
// index: 95
// raw_name: batch_normalization_16/gamma
// c_name: main5_batch_normalization_16_gamma
// shape: [16]
// numel: 16
// float_min: 0.8935980796813965
// float_max: 1.4165303707122803
// q_min: 3660
// q_max: 5802
// max_abs_error: 0.00011050701141357422
// mean_abs_error: 6.804987788200378e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_16_GAMMA_NUMEL 16
#define MAIN5_BATCH_NORMALIZATION_16_GAMMA_DIM0 16
static const int16_t main5_batch_normalization_16_gamma[16] = {
    3660, 4305, 4706, 4094, 4930, 5403, 5500, 3876, 4723, 4976, 5067, 4703, 4726, 5610, 4114, 5802
};

// ---------------------------------------------------------
// index: 96
// raw_name: batch_normalization_16/beta
// c_name: main5_batch_normalization_16_beta
// shape: [16]
// numel: 16
// float_min: -0.2910667061805725
// float_max: 0.4773736000061035
// q_min: -1192
// q_max: 1955
// max_abs_error: 0.00012069940567016602
// mean_abs_error: 6.0088641475886106e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_16_BETA_NUMEL 16
#define MAIN5_BATCH_NORMALIZATION_16_BETA_DIM0 16
static const int16_t main5_batch_normalization_16_beta[16] = {
    685, 1955, -170, -606, 658, 707, 45, 38, 1445, -1192, 486, -34, -702, -401, -718, 225
};

// ---------------------------------------------------------
// index: 97
// raw_name: batch_normalization_16/moving_mean
// c_name: main5_batch_normalization_16_moving_mean
// shape: [16]
// numel: 16
// float_min: -0.7686017155647278
// float_max: 0.6682899594306946
// q_min: -3148
// q_max: 2737
// max_abs_error: 0.00011272355914115906
// mean_abs_error: 5.749781848862767e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_16_MOVING_MEAN_NUMEL 16
#define MAIN5_BATCH_NORMALIZATION_16_MOVING_MEAN_DIM0 16
static const int16_t main5_batch_normalization_16_moving_mean[16] = {
    1163, 349, 56, 2737, 1255, -1496, -1384, -3148, -1602, -78, 826, 487, 1260, 327, -1047, -879
};

// ---------------------------------------------------------
// index: 98
// raw_name: batch_normalization_16/moving_variance
// c_name: main5_batch_normalization_16_moving_variance
// shape: [16]
// numel: 16
// float_min: 0.22610419988632202
// float_max: 0.5840725302696228
// q_min: 926
// q_max: 2392
// max_abs_error: 0.00010883808135986328
// mean_abs_error: 6.785616278648376e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_16_MOVING_VARIANCE_NUMEL 16
#define MAIN5_BATCH_NORMALIZATION_16_MOVING_VARIANCE_DIM0 16
static const int16_t main5_batch_normalization_16_moving_variance[16] = {
    926, 1275, 1191, 1222, 2392, 1414, 1707, 1065, 1444, 1713, 1397, 1087, 1588, 1670, 1173, 1638
};

// ---------------------------------------------------------
// index: 99
// raw_name: separable_conv1d_9/depthwise_kernel
// c_name: main5_separable_conv1d_9_depthwise_kernel
// shape: [3, 16, 1]
// numel: 48
// float_min: -0.31257137656211853
// float_max: 0.36890920996665955
// q_min: -1280
// q_max: 1511
// max_abs_error: 0.00012107193470001221
// mean_abs_error: 6.227139965631068e-05
// ---------------------------------------------------------
#define MAIN5_SEPARABLE_CONV1D_9_DEPTHWISE_KERNEL_NUMEL 48
#define MAIN5_SEPARABLE_CONV1D_9_DEPTHWISE_KERNEL_DIM0 3
#define MAIN5_SEPARABLE_CONV1D_9_DEPTHWISE_KERNEL_DIM1 16
#define MAIN5_SEPARABLE_CONV1D_9_DEPTHWISE_KERNEL_DIM2 1
static const int16_t main5_separable_conv1d_9_depthwise_kernel[48] = {
    -1280, -924, 420, 1245, -408, -982, 162, -791, -581, 1511, 639, 140, 1231, -538, 188, -831,
    483, 671, -833, -588, 1166, 551, 1056, -7, -19, -243, -206, -903, 565, -35, 187, -711,
    161, -28, -848, -888, 727, -680, 412, -984, -131, -224, 792, -203, -728, 1384, 964, -720
};

// ---------------------------------------------------------
// index: 100
// raw_name: separable_conv1d_9/pointwise_kernel
// c_name: main5_separable_conv1d_9_pointwise_kernel
// shape: [1, 16, 10]
// numel: 160
// float_min: -0.3191229999065399
// float_max: 0.339997261762619
// q_min: -1307
// q_max: 1393
// max_abs_error: 0.00012179207988083363
// mean_abs_error: 5.930350016569719e-05
// ---------------------------------------------------------
#define MAIN5_SEPARABLE_CONV1D_9_POINTWISE_KERNEL_NUMEL 160
#define MAIN5_SEPARABLE_CONV1D_9_POINTWISE_KERNEL_DIM0 1
#define MAIN5_SEPARABLE_CONV1D_9_POINTWISE_KERNEL_DIM1 16
#define MAIN5_SEPARABLE_CONV1D_9_POINTWISE_KERNEL_DIM2 10
static const int16_t main5_separable_conv1d_9_pointwise_kernel[160] = {
    -135, -440, -23, 382, 540, -251, -703, -1131, -901, -140, 482, -409, -373, -169, -31, -511,
    -759, -74, 991, 149, 760, -1080, -43, 834, 166, 260, 269, 1047, -64, 375, 239, -763,
    372, -661, -728, 397, 487, -248, -832, -897, 352, -95, -1059, -1121, 261, 83, 45, 1261,
    -203, -451, -10, -629, -81, 892, -297, -555, -259, -617, -1298, -80, 1168, -373, -629, -197,
    261, 1060, -179, -117, 921, 779, 290, 434, 358, -943, 172, -902, 832, 327, 12, 433,
    -38, -577, 177, 349, 222, 187, 840, -73, -1203, -46, 662, 83, -431, -1236, -142, 11,
    -815, 1084, 828, 323, 423, -589, -555, 826, -154, -398, -549, 191, 208, -436, 1042, 1215,
    -445, 1104, 549, -125, 554, 887, 481, -1136, 329, -446, -904, 1158, -934, 773, 12, -337,
    395, 1393, -456, 368, 581, 533, 671, 353, 356, -357, -4, -1252, -466, -47, -744, -67,
    33, 478, 155, -655, 1168, -141, -642, -24, 395, 513, -1307, -100, -10, -143, 494, 726
};

// ---------------------------------------------------------
// index: 101
// raw_name: separable_conv1d_10/depthwise_kernel
// c_name: main5_separable_conv1d_10_depthwise_kernel
// shape: [5, 16, 1]
// numel: 80
// float_min: -0.28977546095848083
// float_max: 0.36401525139808655
// q_min: -1187
// q_max: 1491
// max_abs_error: 0.00012004375457763672
// mean_abs_error: 5.6670432968530804e-05
// ---------------------------------------------------------
#define MAIN5_SEPARABLE_CONV1D_10_DEPTHWISE_KERNEL_NUMEL 80
#define MAIN5_SEPARABLE_CONV1D_10_DEPTHWISE_KERNEL_DIM0 5
#define MAIN5_SEPARABLE_CONV1D_10_DEPTHWISE_KERNEL_DIM1 16
#define MAIN5_SEPARABLE_CONV1D_10_DEPTHWISE_KERNEL_DIM2 1
static const int16_t main5_separable_conv1d_10_depthwise_kernel[80] = {
    1056, 1000, 334, 584, 878, -559, -856, 230, -639, -581, 585, 373, -1094, -989, -498, -362,
    -122, 400, -376, -89, 496, -589, -672, 659, 237, -357, 1394, 338, -338, -179, -305, -853,
    -384, -788, -198, -348, 535, -341, -250, -437, 772, 53, -545, 76, -9, 249, 564, -77,
    137, -1012, 36, -112, 122, -502, -204, 75, 445, -711, -745, 337, 35, -198, 333, -181,
    -241, 33, 1151, 1491, -1164, 1191, 1355, -929, -349, -1187, 219, -844, 366, -1143, 1311, 1274
};

// ---------------------------------------------------------
// index: 102
// raw_name: separable_conv1d_10/pointwise_kernel
// c_name: main5_separable_conv1d_10_pointwise_kernel
// shape: [1, 16, 10]
// numel: 160
// float_min: -0.4927046298980713
// float_max: 0.4869838058948517
// q_min: -2018
// q_max: 1995
// max_abs_error: 0.00012198090553283691
// mean_abs_error: 6.636581383645535e-05
// ---------------------------------------------------------
#define MAIN5_SEPARABLE_CONV1D_10_POINTWISE_KERNEL_NUMEL 160
#define MAIN5_SEPARABLE_CONV1D_10_POINTWISE_KERNEL_DIM0 1
#define MAIN5_SEPARABLE_CONV1D_10_POINTWISE_KERNEL_DIM1 16
#define MAIN5_SEPARABLE_CONV1D_10_POINTWISE_KERNEL_DIM2 10
static const int16_t main5_separable_conv1d_10_pointwise_kernel[160] = {
    -652, -307, 220, 1029, -266, 4, 116, 1125, 33, 599, 897, 458, -97, 181, -836, 1112,
    702, -1076, -252, -940, -324, -664, -1760, 129, 683, -134, -335, 2, 262, 180, -1587, 46,
    -200, -287, 539, 475, -1445, 1171, 221, 497, -494, -869, -1551, -1193, -126, -290, 671, 454,
    560, 116, 455, 73, -754, 108, 1020, -1438, -88, -878, 265, -554, 560, -1133, 398, 207,
    -1091, 417, -712, 1613, 992, 1296, 247, -126, 601, 1247, -142, 251, 197, -809, -1381, -682,
    -18, 398, 115, -822, 373, 1995, 86, -9, -693, -366, 488, -119, 355, 1531, 323, -231,
    1560, 121, 298, -435, -1197, -1329, 74, -149, -730, 216, -328, 263, 749, -542, -421, 269,
    607, -893, -677, 232, 880, -1282, -992, 327, -219, -1340, -245, -242, -9, -109, 513, 588,
    549, 413, 222, 280, -1496, 480, -985, -408, 1444, -628, 105, 197, 907, 707, -406, -834,
    -178, 1276, -1148, 177, 706, 134, 467, -693, 797, 342, 774, -356, -751, 114, -32, -2018
};

// ---------------------------------------------------------
// index: 103
// raw_name: separable_conv1d_11/depthwise_kernel
// c_name: main5_separable_conv1d_11_depthwise_kernel
// shape: [7, 16, 1]
// numel: 112
// float_min: -0.38806241750717163
// float_max: 0.511771559715271
// q_min: -1590
// q_max: 2096
// max_abs_error: 0.00012117624282836914
// mean_abs_error: 6.262689566938207e-05
// ---------------------------------------------------------
#define MAIN5_SEPARABLE_CONV1D_11_DEPTHWISE_KERNEL_NUMEL 112
#define MAIN5_SEPARABLE_CONV1D_11_DEPTHWISE_KERNEL_DIM0 7
#define MAIN5_SEPARABLE_CONV1D_11_DEPTHWISE_KERNEL_DIM1 16
#define MAIN5_SEPARABLE_CONV1D_11_DEPTHWISE_KERNEL_DIM2 1
static const int16_t main5_separable_conv1d_11_depthwise_kernel[112] = {
    552, 763, 2096, 292, -495, -852, 1261, -421, 1804, 817, 213, 11, 625, -1240, 1045, -1390,
    -125, 1027, 1074, 1213, -13, -403, 782, -69, -762, 238, 47, 182, -32, -435, 118, -816,
    -134, 302, 121, 1621, -241, -271, 216, 64, -487, 714, -751, -316, -294, 375, 218, 317,
    -207, -148, -28, 240, -67, -418, 22, -770, -5, 682, -157, 670, -351, 386, -207, 64,
    279, 385, -388, -289, 1498, 963, 256, 666, 17, -144, -486, -644, 751, -347, -40, 19,
    -1344, -362, 514, 20, -77, 740, -400, -133, -279, -585, 951, -515, -492, -328, 548, 846,
    -145, -1275, -235, 20, -1035, -285, -645, -771, 63, 800, 214, -250, -1020, 900, -1590, 657
};

// ---------------------------------------------------------
// index: 104
// raw_name: separable_conv1d_11/pointwise_kernel
// c_name: main5_separable_conv1d_11_pointwise_kernel
// shape: [1, 16, 10]
// numel: 160
// float_min: -0.48522183299064636
// float_max: 0.43278273940086365
// q_min: -1987
// q_max: 1773
// max_abs_error: 0.00011986494064331055
// mean_abs_error: 5.865005005034618e-05
// ---------------------------------------------------------
#define MAIN5_SEPARABLE_CONV1D_11_POINTWISE_KERNEL_NUMEL 160
#define MAIN5_SEPARABLE_CONV1D_11_POINTWISE_KERNEL_DIM0 1
#define MAIN5_SEPARABLE_CONV1D_11_POINTWISE_KERNEL_DIM1 16
#define MAIN5_SEPARABLE_CONV1D_11_POINTWISE_KERNEL_DIM2 10
static const int16_t main5_separable_conv1d_11_pointwise_kernel[160] = {
    -1058, 65, 536, -1703, 697, -595, 272, 766, 542, 61, -718, 844, 437, 871, -1451, -1261,
    -1451, 42, 79, -233, -685, 680, 23, -203, -341, 76, -1866, -897, -1987, -429, -807, 1038,
    40, 229, 184, -2, -1769, -566, -1501, -238, -1128, 475, 615, 1383, -291, 919, 710, 1112,
    -492, -270, 1534, 803, -700, 323, -807, 1242, -553, 897, 1136, -170, -166, -805, 1295, -449,
    -127, -1047, -971, -211, -679, 1118, 1050, -784, 42, -1344, -937, -88, 158, -1510, -486, 977,
    -1622, 757, -732, 104, -265, -1128, -1004, -91, -175, 89, 912, 712, 1282, 130, 626, 273,
    -625, 619, 573, -1012, 1171, -810, -558, 1014, -22, -736, -605, -338, -337, 1118, -510, -308,
    414, 1044, 677, 757, 299, 679, -252, 918, 823, -1506, 568, -49, -1375, 849, 55, -1515,
    -438, -1297, 215, -1247, -189, 1773, 262, 102, 738, -277, -631, 903, -391, -839, -71, -1238,
    -1345, 782, -1017, -906, -289, -694, 499, -708, 138, 91, 365, 1768, -49, -956, -596, 1427
};

// ---------------------------------------------------------
// index: 105
// raw_name: conv1d_9/kernel
// c_name: main5_conv1d_9_kernel
// shape: [1, 16, 10]
// numel: 160
// float_min: -0.3098328113555908
// float_max: 0.4712066054344177
// q_min: -1269
// q_max: 1930
// max_abs_error: 0.00012192875146865845
// mean_abs_error: 5.9344409237382933e-05
// ---------------------------------------------------------
#define MAIN5_CONV1D_9_KERNEL_NUMEL 160
#define MAIN5_CONV1D_9_KERNEL_DIM0 1
#define MAIN5_CONV1D_9_KERNEL_DIM1 16
#define MAIN5_CONV1D_9_KERNEL_DIM2 10
static const int16_t main5_conv1d_9_kernel[160] = {
    -270, -146, 591, 74, -285, 261, -34, -412, 1930, 500, -914, -544, 532, 266, 369, 725,
    424, -550, -203, 103, 276, -551, -188, -36, -9, -585, 1070, -119, 1145, 407, -156, 340,
    1061, -122, -760, 914, 29, 319, 557, 211, -397, -452, 1087, 1413, 422, -978, 440, 24,
    603, 325, 339, -811, -415, 6, -385, -345, 403, -365, -182, 934, -770, -943, 416, 0,
    254, 295, 1369, 293, 561, -386, -216, -746, 272, -549, -334, -616, 208, 1404, 179, 483,
    -16, -18, 154, 1756, -620, 662, 765, 506, -405, 1549, -1059, -438, 773, -724, -625, -1224,
    -90, 113, 589, 953, -554, 138, 341, 52, 65, 619, 649, 283, -243, 506, -182, 199,
    790, -956, -821, -1191, -643, 511, 0, 311, -643, -312, 1182, 88, 121, 203, 759, 334,
    -148, 898, -1269, 28, 290, 21, -69, -102, -515, 125, -3, 432, 293, -299, 676, -288,
    -666, -493, 516, -216, -405, 649, -654, -5, 623, 449, -613, -642, -106, -119, -119, 124
};

// ---------------------------------------------------------
// index: 106
// raw_name: batch_normalization_18/gamma
// c_name: main5_batch_normalization_18_gamma
// shape: [10]
// numel: 10
// float_min: 0.6396702527999878
// float_max: 1.253297209739685
// q_min: 2620
// q_max: 5134
// max_abs_error: 0.0001207590103149414
// mean_abs_error: 4.9704314733389765e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_18_GAMMA_NUMEL 10
#define MAIN5_BATCH_NORMALIZATION_18_GAMMA_DIM0 10
static const int16_t main5_batch_normalization_18_gamma[10] = {
    4076, 4244, 3987, 2620, 3926, 2864, 5134, 4409, 3038, 3514
};

// ---------------------------------------------------------
// index: 107
// raw_name: batch_normalization_18/beta
// c_name: main5_batch_normalization_18_beta
// shape: [10]
// numel: 10
// float_min: -0.4101937711238861
// float_max: 0.3767172694206238
// q_min: -1680
// q_max: 1543
// max_abs_error: 0.00011821836233139038
// mean_abs_error: 6.097853110986762e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_18_BETA_NUMEL 10
#define MAIN5_BATCH_NORMALIZATION_18_BETA_DIM0 10
static const int16_t main5_batch_normalization_18_beta[10] = {
    -1069, -622, 447, 1543, -449, -1680, 205, 404, 799, -1231
};

// ---------------------------------------------------------
// index: 108
// raw_name: batch_normalization_18/moving_mean
// c_name: main5_batch_normalization_18_moving_mean
// shape: [10]
// numel: 10
// float_min: -0.21181707084178925
// float_max: 0.16365990042686462
// q_min: -868
// q_max: 670
// max_abs_error: 0.00010994821786880493
// mean_abs_error: 6.291908357525244e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_18_MOVING_MEAN_NUMEL 10
#define MAIN5_BATCH_NORMALIZATION_18_MOVING_MEAN_DIM0 10
static const int16_t main5_batch_normalization_18_moving_mean[10] = {
    442, 23, -868, -734, 508, 670, -373, 276, 580, -287
};

// ---------------------------------------------------------
// index: 109
// raw_name: batch_normalization_18/moving_variance
// c_name: main5_batch_normalization_18_moving_variance
// shape: [10]
// numel: 10
// float_min: 0.037742629647254944
// float_max: 0.0915355458855629
// q_min: 155
// q_max: 375
// max_abs_error: 9.916722774505615e-05
// mean_abs_error: 4.970468580722809e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_18_MOVING_VARIANCE_NUMEL 10
#define MAIN5_BATCH_NORMALIZATION_18_MOVING_VARIANCE_DIM0 10
static const int16_t main5_batch_normalization_18_moving_variance[10] = {
    193, 186, 155, 199, 165, 249, 280, 375, 285, 261
};

// ---------------------------------------------------------
// index: 110
// raw_name: batch_normalization_19/gamma
// c_name: main5_batch_normalization_19_gamma
// shape: [10]
// numel: 10
// float_min: 0.7041419744491577
// float_max: 1.857008934020996
// q_min: 2884
// q_max: 7606
// max_abs_error: 0.00012087821960449219
// mean_abs_error: 6.0606002080021426e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_19_GAMMA_NUMEL 10
#define MAIN5_BATCH_NORMALIZATION_19_GAMMA_DIM0 10
static const int16_t main5_batch_normalization_19_gamma[10] = {
    3572, 3458, 4299, 3527, 2884, 3849, 7606, 3654, 3547, 4922
};

// ---------------------------------------------------------
// index: 111
// raw_name: batch_normalization_19/beta
// c_name: main5_batch_normalization_19_beta
// shape: [10]
// numel: 10
// float_min: -0.25561919808387756
// float_max: 0.6214389204978943
// q_min: -1047
// q_max: 2545
// max_abs_error: 0.00011682510375976562
// mean_abs_error: 5.9186957514612004e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_19_BETA_NUMEL 10
#define MAIN5_BATCH_NORMALIZATION_19_BETA_DIM0 10
static const int16_t main5_batch_normalization_19_beta[10] = {
    -1047, -466, 1492, 2261, 2545, 0, 168, 2132, 872, 319
};

// ---------------------------------------------------------
// index: 112
// raw_name: batch_normalization_19/moving_mean
// c_name: main5_batch_normalization_19_moving_mean
// shape: [10]
// numel: 10
// float_min: -0.18830330669879913
// float_max: 0.10838150978088379
// q_min: -771
// q_max: 444
// max_abs_error: 9.704753756523132e-05
// mean_abs_error: 4.7165900468826294e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_19_MOVING_MEAN_NUMEL 10
#define MAIN5_BATCH_NORMALIZATION_19_MOVING_MEAN_DIM0 10
static const int16_t main5_batch_normalization_19_moving_mean[10] = {
    -710, -181, -270, -771, 217, 444, -603, 411, 80, 170
};

// ---------------------------------------------------------
// index: 113
// raw_name: batch_normalization_19/moving_variance
// c_name: main5_batch_normalization_19_moving_variance
// shape: [10]
// numel: 10
// float_min: 0.054245997220277786
// float_max: 0.17400988936424255
// q_min: 222
// q_max: 713
// max_abs_error: 7.978826761245728e-05
// mean_abs_error: 5.343444718164392e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_19_MOVING_VARIANCE_NUMEL 10
#define MAIN5_BATCH_NORMALIZATION_19_MOVING_VARIANCE_DIM0 10
static const int16_t main5_batch_normalization_19_moving_variance[10] = {
    222, 399, 540, 416, 313, 672, 673, 713, 619, 533
};

// ---------------------------------------------------------
// index: 114
// raw_name: batch_normalization_20/gamma
// c_name: main5_batch_normalization_20_gamma
// shape: [10]
// numel: 10
// float_min: 1.0671154260635376
// float_max: 1.3695285320281982
// q_min: 4371
// q_max: 5610
// max_abs_error: 0.00010561943054199219
// mean_abs_error: 5.8853627706412226e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_20_GAMMA_NUMEL 10
#define MAIN5_BATCH_NORMALIZATION_20_GAMMA_DIM0 10
static const int16_t main5_batch_normalization_20_gamma[10] = {
    5610, 5273, 4965, 4590, 4523, 5566, 5431, 4873, 5322, 4371
};

// ---------------------------------------------------------
// index: 115
// raw_name: batch_normalization_20/beta
// c_name: main5_batch_normalization_20_beta
// shape: [10]
// numel: 10
// float_min: -0.6868427395820618
// float_max: 0.5863070487976074
// q_min: -2813
// q_max: 2402
// max_abs_error: 0.00011873245239257812
// mean_abs_error: 7.993988401722163e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_20_BETA_NUMEL 10
#define MAIN5_BATCH_NORMALIZATION_20_BETA_DIM0 10
static const int16_t main5_batch_normalization_20_beta[10] = {
    902, 993, 2402, 1023, 165, -313, -2813, -1820, -1976, 604
};

// ---------------------------------------------------------
// index: 116
// raw_name: batch_normalization_20/moving_mean
// c_name: main5_batch_normalization_20_moving_mean
// shape: [10]
// numel: 10
// float_min: -0.4467642605304718
// float_max: 0.18046651780605316
// q_min: -1830
// q_max: 739
// max_abs_error: 0.00010911375284194946
// mean_abs_error: 5.2374602091731504e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_20_MOVING_MEAN_NUMEL 10
#define MAIN5_BATCH_NORMALIZATION_20_MOVING_MEAN_DIM0 10
static const int16_t main5_batch_normalization_20_moving_mean[10] = {
    -621, 739, 382, 259, -317, -663, -1830, -404, -1115, -360
};

// ---------------------------------------------------------
// index: 117
// raw_name: batch_normalization_20/moving_variance
// c_name: main5_batch_normalization_20_moving_variance
// shape: [10]
// numel: 10
// float_min: 0.12329792976379395
// float_max: 0.4336903393268585
// q_min: 505
// q_max: 1776
// max_abs_error: 0.00011029839515686035
// mean_abs_error: 5.555152893066406e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_20_MOVING_VARIANCE_NUMEL 10
#define MAIN5_BATCH_NORMALIZATION_20_MOVING_VARIANCE_DIM0 10
static const int16_t main5_batch_normalization_20_moving_variance[10] = {
    1414, 924, 505, 674, 539, 802, 1776, 992, 1101, 589
};

// ---------------------------------------------------------
// index: 118
// raw_name: batch_normalization_21/gamma
// c_name: main5_batch_normalization_21_gamma
// shape: [10]
// numel: 10
// float_min: 0.6710628867149353
// float_max: 1.5284290313720703
// q_min: 2749
// q_max: 6260
// max_abs_error: 0.0001087188720703125
// mean_abs_error: 5.2022933232365176e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_21_GAMMA_NUMEL 10
#define MAIN5_BATCH_NORMALIZATION_21_GAMMA_DIM0 10
static const int16_t main5_batch_normalization_21_gamma[10] = {
    3612, 4485, 4850, 2749, 6260, 3469, 3120, 3145, 2862, 4151
};

// ---------------------------------------------------------
// index: 119
// raw_name: batch_normalization_21/beta
// c_name: main5_batch_normalization_21_beta
// shape: [10]
// numel: 10
// float_min: -0.47227317094802856
// float_max: 0.4782857894897461
// q_min: -1934
// q_max: 1959
// max_abs_error: 0.00010520219802856445
// mean_abs_error: 4.2804796976270154e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_21_BETA_NUMEL 10
#define MAIN5_BATCH_NORMALIZATION_21_BETA_DIM0 10
static const int16_t main5_batch_normalization_21_beta[10] = {
    1959, -477, -1232, -59, 628, 1031, -280, 1054, -629, -1934
};

// ---------------------------------------------------------
// index: 120
// raw_name: batch_normalization_21/moving_mean
// c_name: main5_batch_normalization_21_moving_mean
// shape: [10]
// numel: 10
// float_min: -1.5149900913238525
// float_max: 1.886003017425537
// q_min: -6205
// q_max: 7725
// max_abs_error: 0.00011116266250610352
// mean_abs_error: 5.256831718725152e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_21_MOVING_MEAN_NUMEL 10
#define MAIN5_BATCH_NORMALIZATION_21_MOVING_MEAN_DIM0 10
static const int16_t main5_batch_normalization_21_moving_mean[10] = {
    -6205, -4996, 7446, 3660, -3211, -1546, 6126, 1708, 3651, 7725
};

// ---------------------------------------------------------
// index: 121
// raw_name: batch_normalization_21/moving_variance
// c_name: main5_batch_normalization_21_moving_variance
// shape: [10]
// numel: 10
// float_min: 0.504813551902771
// float_max: 6.111291408538818
// q_min: 2068
// q_max: 25032
// max_abs_error: 9.72747802734375e-05
// mean_abs_error: 5.793571472167969e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_21_MOVING_VARIANCE_NUMEL 10
#define MAIN5_BATCH_NORMALIZATION_21_MOVING_VARIANCE_DIM0 10
static const int16_t main5_batch_normalization_21_moving_variance[10] = {
    7221, 4757, 13687, 2173, 8713, 4635, 7669, 8964, 2068, 25032
};

// ---------------------------------------------------------
// index: 122
// raw_name: conv1d_11/kernel
// c_name: main5_conv1d_11_kernel
// shape: [1, 16, 20]
// numel: 320
// float_min: -0.3666127920150757
// float_max: 0.3484419882297516
// q_min: -1502
// q_max: 1427
// max_abs_error: 0.00012196600437164307
// mean_abs_error: 6.52354137855582e-05
// ---------------------------------------------------------
#define MAIN5_CONV1D_11_KERNEL_NUMEL 320
#define MAIN5_CONV1D_11_KERNEL_DIM0 1
#define MAIN5_CONV1D_11_KERNEL_DIM1 16
#define MAIN5_CONV1D_11_KERNEL_DIM2 20
static const int16_t main5_conv1d_11_kernel[320] = {
    534, 137, -549, 434, 356, -16, 438, -202, -75, -953, 33, -614, 192, -268, -149, 35,
    62, 226, -126, -149, 312, -353, -319, 647, 25, 582, -709, 103, -242, 311, 1123, -740,
    277, -195, 404, 314, -111, 276, -398, 149, 205, -101, -252, 223, 275, -15, 477, -127,
    251, -36, -33, 172, 505, 180, 157, 216, 333, -131, -147, -288, 601, -313, -479, 113,
    593, 291, -238, 26, 310, 82, 115, -792, -620, 229, 148, 70, -160, 194, 308, -113,
    -382, 288, -96, -819, -365, -219, -1256, 75, -172, 727, -539, 518, 370, 92, 389, 274,
    -591, 872, 467, -469, 264, -441, -719, -233, -935, -327, 207, -229, 748, -14, -380, -552,
    -658, 137, 28, -144, 94, -447, -32, 63, -919, 163, -972, 662, 12, -235, 26, -1030,
    -168, 624, -392, 333, 630, -810, -253, -122, 335, -252, -640, -577, 986, 523, -100, 1345,
    -332, 1120, 572, -921, -55, -500, 872, 308, -354, -338, -735, 74, 683, 519, -24, -360,
    1016, 1265, -360, 643, -684, 979, 926, 301, 1256, -1502, 97, -858, -1112, 1284, -1401, 1136,
    312, -217, 1232, 62, 427, 789, -99, 1122, -985, 897, 333, 1209, 871, -183, 1427, -1132,
    -573, 1207, -2, 558, 382, -482, 193, -1375, 702, 651, -837, 757, 297, 646, -832, -236,
    7, 773, 459, 587, -441, 714, 35, 39, -803, 267, -635, -184, 678, 672, -782, 242,
    -863, 227, 408, 1080, 1010, -1342, 755, -929, -364, 492, -878, 1327, 1016, -1121, 1069, -223,
    652, 1076, -705, 320, -933, -325, 117, 844, 943, 531, 651, 105, 471, 324, -332, 911,
    816, 440, 268, 165, 337, 123, -1063, 30, 140, 479, 251, -357, -149, -149, -73, 260,
    47, -955, -111, -237, -444, -333, -218, 85, 768, 861, -101, 336, -717, 337, -167, -329,
    883, 418, 237, 108, -501, 619, 83, 881, -425, 349, 614, 81, 497, -926, 180, -368,
    -112, -308, -299, 805, -676, -220, 609, 109, 271, -308, -326, 458, -1006, 63, 77, -107
};

// ---------------------------------------------------------
// index: 123
// raw_name: conv1d_10/kernel
// c_name: main5_conv1d_10_kernel
// shape: [1, 40, 20]
// numel: 800
// float_min: -0.5428780317306519
// float_max: 0.5789998769760132
// q_min: -2224
// q_max: 2372
// max_abs_error: 0.00012201070785522461
// mean_abs_error: 6.246766861295328e-05
// ---------------------------------------------------------
#define MAIN5_CONV1D_10_KERNEL_NUMEL 800
#define MAIN5_CONV1D_10_KERNEL_DIM0 1
#define MAIN5_CONV1D_10_KERNEL_DIM1 40
#define MAIN5_CONV1D_10_KERNEL_DIM2 20
static const int16_t main5_conv1d_10_kernel[800] = {
    129, -311, -451, -385, -573, 832, -326, 511, -136, -335, 155, -857, -450, -118, 70, 70,
    118, 64, 456, 298, -36, -369, 241, 213, 628, -2, -239, 136, 433, 157, 637, 147,
    -188, 164, 590, -480, 118, -383, -1539, -200, -762, -533, 807, 29, -295, 58, -11, -822,
    -249, -275, 673, 140, -505, -396, -329, 272, -313, 184, -274, 411, 325, 90, 280, 530,
    -224, 403, -47, 112, 478, 694, 475, -228, 312, 259, 209, 874, 419, 572, 559, -209,
    -516, -402, -1115, -66, 980, 182, -108, -617, 565, 62, 174, -500, 8, 894, -13, 775,
    -65, -129, 119, -311, 177, 245, 5, -167, -285, -767, -198, -293, 81, 195, -708, -1374,
    -86, 39, -18, -348, -363, -559, -148, -253, 111, 748, -268, 426, 116, 862, -116, 939,
    444, 376, 702, 517, -47, -700, -243, 433, -507, -593, -169, -718, -152, 366, -282, 461,
    493, 146, 412, -381, 263, -744, -858, 43, 540, -432, -653, 251, 552, 717, 977, 731,
    -12, -795, 1178, 309, -94, -466, 692, 926, -34, -179, 476, 673, 81, 235, -438, -38,
    -582, 244, -416, -197, 63, -587, -252, 754, -32, 766, -239, -965, -448, 10, 345, 372,
    -274, -137, 722, -619, -887, -598, -192, -777, 392, -168, -400, -308, -60, -800, 600, -351,
    4, 746, -1110, 224, -454, -264, 812, 408, -261, 350, 611, -372, -859, 467, -108, -516,
    687, -1091, 117, -149, 813, -572, -1077, -117, -298, -356, -707, 680, -285, -107, 641, 123,
    468, -1025, 1, 99, 548, 648, 139, 554, -310, -569, 383, 108, 256, 113, -1066, -1578,
    133, 655, 1058, -108, 512, 867, -466, 723, -658, 622, 806, 726, 591, -251, 227, -437,
    4, 294, -150, 188, -525, -577, 1174, -222, -710, 258, 350, -77, -85, -272, -362, 128,
    318, 32, -308, 379, -1166, -11, 268, -75, -683, -473, -139, -993, -151, -308, 59, -158,
    971, -366, -575, -590, -983, -801, 135, 476, -371, -1234, -20, -898, 816, 207, -422, -666,
    -487, -338, -2181, -167, 396, -289, 18, 424, -235, -1148, 153, -506, -638, -358, 562, 44,
    292, 106, -290, -2224, 447, -346, -30, 87, -611, -230, 401, -1338, -1285, -290, -101, -1201,
    -592, -739, 564, -483, 918, -502, -1302, -119, -483, -176, -848, -1391, -383, -397, 194, 507,
    -230, 465, -323, 666, -894, 226, 780, -611, -130, -315, -327, -36, -679, 736, -366, -168,
    -1353, -164, -28, -366, -18, 100, -508, -636, -139, -11, -3, -249, -794, -674, 1455, -948,
    1078, -499, -1085, 397, -558, 170, -153, -249, -599, -1443, -422, -1730, 727, -1956, -656, -165,
    -81, -376, -993, -526, -257, -1259, 111, -1501, 12, 296, -230, -155, -328, -1582, -1118, -246,
    225, -624, 2, -1188, -126, -869, 751, -446, 39, -179, -621, -1072, 95, -942, 171, -361,
    -896, -1026, -860, -273, -175, -627, -108, -773, -1396, -55, 427, -1287, -2219, -268, 448, -1264,
    225, -273, -484, 876, 450, -461, -409, 210, 10, 658, 173, -640, -1071, -100, -37, 223,
    317, -522, -694, 264, 1112, 869, -350, 545, -884, -435, 705, -199, 321, -275, -870, -251,
    290, -796, -470, -846, -682, -547, -580, -956, -792, -1099, -1055, -294, -621, -879, -131, -1143,
    -1260, -1484, 50, -573, -339, -150, 656, -729, -292, -922, 2372, -817, -774, -1376, -703, -1889,
    -670, 125, 1, -291, -759, 521, 689, 294, -181, 669, 443, 668, -228, -538, 481, -625,
    -664, -631, -463, -689, -724, 135, -1207, 536, -331, 353, -1198, 497, -381, 1468, -473, 1086,
    636, 1876, -592, 585, -871, -834, -67, -470, 347, 986, -281, 403, -762, -711, 861, 1087,
    56, 1431, -485, -164, -284, 697, 129, 398, 215, 647, -976, 1115, -1064, 481, 1266, -117,
    547, 423, 828, 27, -78, 824, -853, 192, 27, -365, -146, 849, 1287, 11, -576, 57,
    -582, -205, 124, -1040, 503, -108, -422, -549, 405, 136, -509, 22, -87, -481, -532, 93,
    -272, -37, -509, 548, -394, 51, 167, -439, -660, -860, 845, -201, -717, 271, 314, 561,
    -893, -487, 855, -234, -864, -159, -585, -751, -967, -1260, -564, -88, 605, -538, 147, -1059,
    -25, -1201, -1104, -1114, 170, 101, 122, 209, -288, 207, 59, -95, 178, -311, 275, -104,
    550, 547, -497, 275, 193, -521, 275, -370, -691, -705, -616, -555, 40, 509, -322, 784,
    -113, -128, -332, -964, -759, -1126, -963, 233, 15, 535, 475, -763, -255, 145, -189, 75,
    693, -100, -102, 111, 233, 725, 70, -763, 50, 168, 746, -297, 37, 165, 303, -161,
    -858, -563, -55, -618, 319, 411, -934, 262, -256, -802, 465, 47, -572, -234, 560, -684,
    -441, 68, 2, 373, -657, -474, -164, -811, -363, -428, -1068, 365, 340, -90, 6, 25,
    617, -14, -143, -113, -779, -348, 158, 526, -140, 469, 32, 140, -564, 59, -156, -782,
    271, 344, -117, -391, -583, 571, 342, -4, -334, 122, -189, 163, -956, -628, -486, -105,
    -617, -1208, -470, -349, -1697, -502, -450, -364, 214, -1002, -1048, -650, -1226, 392, -219, -210
};

// ---------------------------------------------------------
// index: 124
// raw_name: batch_normalization_23/gamma
// c_name: main5_batch_normalization_23_gamma
// shape: [20]
// numel: 20
// float_min: 0.5012888312339783
// float_max: 0.9693620800971985
// q_min: 2053
// q_max: 3971
// max_abs_error: 0.00012034177780151367
// mean_abs_error: 5.1891802286263555e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_23_GAMMA_NUMEL 20
#define MAIN5_BATCH_NORMALIZATION_23_GAMMA_DIM0 20
static const int16_t main5_batch_normalization_23_gamma[20] = {
    3259, 3006, 2053, 3148, 3971, 2888, 2741, 2350, 3210, 2809, 2805, 2411, 3642, 2823, 2560, 2892,
    2317, 2211, 2246, 2210
};

// ---------------------------------------------------------
// index: 125
// raw_name: batch_normalization_23/beta
// c_name: main5_batch_normalization_23_beta
// shape: [20]
// numel: 20
// float_min: -0.753944993019104
// float_max: 0.07187572866678238
// q_min: -3088
// q_max: 294
// max_abs_error: 0.0001105964183807373
// mean_abs_error: 5.784444510936737e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_23_BETA_NUMEL 20
#define MAIN5_BATCH_NORMALIZATION_23_BETA_DIM0 20
static const int16_t main5_batch_normalization_23_beta[20] = {
    -2536, -2493, -3088, -2361, -2270, -2595, -1600, -2442, -1585, -2852, -2768, -2355, -1123, -2702, 294, -2989,
    -2863, -2163, -609, -2895
};

// ---------------------------------------------------------
// index: 126
// raw_name: batch_normalization_23/moving_mean
// c_name: main5_batch_normalization_23_moving_mean
// shape: [20]
// numel: 20
// float_min: -0.9406967163085938
// float_max: 0.7840968370437622
// q_min: -3853
// q_max: 3212
// max_abs_error: 0.00012063980102539062
// mean_abs_error: 5.710124969482422e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_23_MOVING_MEAN_NUMEL 20
#define MAIN5_BATCH_NORMALIZATION_23_MOVING_MEAN_DIM0 20
static const int16_t main5_batch_normalization_23_moving_mean[20] = {
    3212, 1716, -3853, 2793, -1901, 2281, -534, 117, 1695, -1051, 2477, -1781, -551, 913, -1695, 3170,
    -347, 461, 843, -1462
};

// ---------------------------------------------------------
// index: 127
// raw_name: batch_normalization_23/moving_variance
// c_name: main5_batch_normalization_23_moving_variance
// shape: [20]
// numel: 20
// float_min: 0.2878428101539612
// float_max: 2.280449867248535
// q_min: 1179
// q_max: 9341
// max_abs_error: 0.00011986494064331055
// mean_abs_error: 7.170438766479492e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_23_MOVING_VARIANCE_NUMEL 20
#define MAIN5_BATCH_NORMALIZATION_23_MOVING_VARIANCE_DIM0 20
static const int16_t main5_batch_normalization_23_moving_variance[20] = {
    8202, 9341, 3555, 7112, 5227, 5218, 4247, 2898, 8813, 6538, 5005, 3537, 3828, 6087, 6206, 7788,
    4146, 1507, 4527, 1179
};

// ---------------------------------------------------------
// index: 128
// raw_name: batch_normalization_22/gamma
// c_name: main5_batch_normalization_22_gamma
// shape: [20]
// numel: 20
// float_min: 0.8035660982131958
// float_max: 1.3476704359054565
// q_min: 3291
// q_max: 5520
// max_abs_error: 0.00011879205703735352
// mean_abs_error: 5.843639519298449e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_22_GAMMA_NUMEL 20
#define MAIN5_BATCH_NORMALIZATION_22_GAMMA_DIM0 20
static const int16_t main5_batch_normalization_22_gamma[20] = {
    4479, 4647, 3802, 4488, 4131, 4320, 3530, 4674, 3687, 4195, 4109, 4256, 3554, 3530, 3291, 5520,
    5339, 4086, 4855, 3664
};

// ---------------------------------------------------------
// index: 129
// raw_name: batch_normalization_22/beta
// c_name: main5_batch_normalization_22_beta
// shape: [20]
// numel: 20
// float_min: -0.753944993019104
// float_max: 0.07187572866678238
// q_min: -3088
// q_max: 294
// max_abs_error: 0.0001105964183807373
// mean_abs_error: 5.784444510936737e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_22_BETA_NUMEL 20
#define MAIN5_BATCH_NORMALIZATION_22_BETA_DIM0 20
static const int16_t main5_batch_normalization_22_beta[20] = {
    -2536, -2493, -3088, -2361, -2270, -2595, -1600, -2442, -1585, -2852, -2768, -2355, -1123, -2702, 294, -2989,
    -2863, -2163, -609, -2895
};

// ---------------------------------------------------------
// index: 130
// raw_name: batch_normalization_22/moving_mean
// c_name: main5_batch_normalization_22_moving_mean
// shape: [20]
// numel: 20
// float_min: -1.1198184490203857
// float_max: 0.1926676630973816
// q_min: -4587
// q_max: 789
// max_abs_error: 0.0001190081238746643
// mean_abs_error: 4.6171619032975286e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_22_MOVING_MEAN_NUMEL 20
#define MAIN5_BATCH_NORMALIZATION_22_MOVING_MEAN_DIM0 20
static const int16_t main5_batch_normalization_22_moving_mean[20] = {
    -2235, -2153, -3011, -1724, -146, -385, -1721, 789, -2715, -4166, -940, -3659, -1576, -3585, -516, -2833,
    -2189, -632, 592, -4587
};

// ---------------------------------------------------------
// index: 131
// raw_name: batch_normalization_22/moving_variance
// c_name: main5_batch_normalization_22_moving_variance
// shape: [20]
// numel: 20
// float_min: 0.15172065794467926
// float_max: 0.8158101439476013
// q_min: 621
// q_max: 3342
// max_abs_error: 0.00010932981967926025
// mean_abs_error: 6.40548751107417e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_22_MOVING_VARIANCE_NUMEL 20
#define MAIN5_BATCH_NORMALIZATION_22_MOVING_VARIANCE_DIM0 20
static const int16_t main5_batch_normalization_22_moving_variance[20] = {
    2921, 2207, 1742, 2741, 1955, 1668, 1875, 1413, 2408, 3342, 2276, 1262, 621, 1756, 1230, 3114,
    2389, 1121, 1882, 1803
};

// ---------------------------------------------------------
// index: 132
// raw_name: dense/kernel
// c_name: main5_dense_kernel
// shape: [40, 24]
// numel: 960
// float_min: -0.4342907667160034
// float_max: 0.41640597581863403
// q_min: -1779
// q_max: 1706
// max_abs_error: 0.00012201070785522461
// mean_abs_error: 6.383509753504768e-05
// ---------------------------------------------------------
#define MAIN5_DENSE_KERNEL_NUMEL 960
#define MAIN5_DENSE_KERNEL_DIM0 40
#define MAIN5_DENSE_KERNEL_DIM1 24
static const int16_t main5_dense_kernel[960] = {
    -72, 652, -723, 125, 928, 253, 344, 780, 626, 388, -126, -634, 169, 319, 53, 864,
    -345, 1292, -93, 106, 108, 390, 312, -748, -155, -538, 204, 41, 436, -327, -461, 581,
    940, -38, -59, 295, 617, 547, -197, 140, 1236, -461, -31, -90, 615, -371, -486, 235,
    122, -33, -477, -260, -529, 873, 201, 287, -546, 98, -916, -458, 142, -1194, 97, -413,
    -1216, 204, 108, -1062, 65, 62, 134, -525, -136, -338, -84, 726, 121, 120, -306, 697,
    385, -193, 68, 7, 159, 355, -127, 835, 745, 542, -181, -28, 28, -307, -312, 4,
    -230, 1356, -259, -177, 770, -767, 697, -894, -42, 201, 783, -182, -598, 836, -74, 710,
    -301, 815, -316, 1179, -798, 458, 698, -215, -78, -126, 219, 1003, -474, 563, -229, 457,
    -363, -337, 249, 282, -264, 32, -65, 733, 253, 470, 8, 302, -288, -211, -218, 436,
    35, 397, -50, -452, 338, 66, 361, 170, 266, 378, -323, -235, 284, -52, 109, -333,
    -285, 166, 64, -90, 233, 216, 278, -267, -269, 268, 179, 67, 54, -1012, -49, -930,
    -50, -207, 699, 199, -553, 687, -69, 237, 305, -461, -106, 745, -456, -20, 2, 270,
    424, -300, 500, -1092, 24, -199, 180, -113, 159, 473, -852, 551, 1114, -868, 296, -1290,
    -187, -1175, 471, -1035, 1108, 106, 157, 639, -202, -313, 610, 688, -156, -435, -505, 47,
    125, -397, 355, 690, -151, 561, -140, 269, 1095, -410, 28, 468, -48, -282, -405, 771,
    -53, -238, 104, 856, -410, 154, -219, 67, -339, -525, 376, 111, -484, -35, -70, 691,
    162, 446, 9, 302, -472, -185, -159, 259, 502, -14, 311, -998, -353, 984, 392, 111,
    -52, 202, -1572, 389, 631, -1779, 458, -1565, -1226, -240, 555, -1674, 582, 330, 267, 612,
    -336, -674, 471, 960, -1346, -707, -717, -1102, -1349, -832, 1046, 776, -711, 395, -264, 346,
    1333, -1417, -61, 1050, -404, -434, -587, 994, 311, -350, 359, -102, -635, 510, 284, -207,
    -748, 19, -324, 252, 288, -790, 298, -822, -408, -326, 458, -399, 367, 253, 323, 387,
    11, 784, -1094, -473, 785, 164, 614, 614, 509, 634, -386, -1394, 225, 24, 64, 699,
    -655, 815, -96, -234, 192, 416, 529, -1267, -61, -154, -68, -357, 901, -257, -257, 891,
    1085, 315, -605, -89, 907, 527, -76, 186, 974, -252, -67, -559, 794, -236, -204, -159,
    -75, 677, -201, -533, 289, -601, 508, -1057, 41, 186, 413, -244, -496, 222, 100, 69,
    -710, 473, -23, 555, -448, 426, 499, -348, 327, 5, -514, -805, 159, 551, 252, 369,
    71, 296, -1022, -457, 558, -829, 147, -504, -885, 131, 85, -1034, 341, 109, 219, -570,
    -894, 999, 498, 459, 883, -1250, 60, -1036, 89, -435, 1342, 243, -1117, 1484, -464, 1405,
    488, 673, -297, 1706, -789, 206, 87, 73, -12, -267, -250, 368, -37, 995, -161, 1007,
    170, 36, -592, -217, 191, -241, 16, 492, -166, 996, 32, -565, 217, -148, -86, -317,
    -226, 118, -595, 69, 95, 70, 140, 101, 61, 191, -5, -477, 35, 19, -280, 224,
    -93, 60, -513, 6, -57, 2, 116, -327, 8, -342, 22, 36, 25, -220, -605, 89,
    28, -160, -63, 122, 132, 232, -289, 142, 242, -388, 45, -36, 227, -638, -681, 76,
    279, -175, -142, -29, -301, 70, -90, 86, -380, -198, -355, -288, -10, -551, 225, -143,
    -355, 21, 310, -371, 116, -18, -93, -214, -523, -16, -107, 106, 54, -6, -258, 76,
    80, -213, 27, -45, -35, 29, -539, 95, 119, -2, -610, 16, -79, -281, -266, -18,
    -330, 68, 17, 39, 64, -152, 57, -95, 62, 13, 97, -25, -275, 68, -96, 178,
    -6, 94, -33, 129, -294, 97, 57, 6, -350, -181, 7, 127, -218, 35, -406, 31,
    -273, -698, -27, 80, -255, -7, -360, 142, 37, -5, -176, -36, -310, -453, -451, 47,
    220, 24, -164, -382, 61, -20, 75, 48, 123, 191, -139, -453, 57, -32, 300, -60,
    -115, 106, 272, -130, 170, 94, 87, -284, -327, 45, 93, -17, 15, -204, -54, -212,
    35, -278, 49, 110, -214, 41, -46, 29, 30, -84, 84, 39, -137, -3, -79, 71,
    78, -84, -4, -223, 19, -75, -6, 3, 43, 46, -147, 18, 84, -91, -52, -226,
    4, -405, -29, -163, 96, -39, -1, 29, -397, -520, 460, 271, -28, -424, -1028, -14,
    12, -771, 61, 493, 8, 264, -298, 247, 345, -491, 241, 113, 247, -800, -1018, 304,
    -377, -38, -17, 83, -99, -1, -229, -2, -169, -469, 5, 15, -301, -26, -373, 66,
    -11, -11, -227, 27, -351, -280, -262, 12, 15, -25, -10, -9, -47, 75, -6, 62,
    -53, -9, -150, 28, 32, -173, -1, -162, -66, -22, 87, -151, 55, -13, -27, 10,
    27, 0, 8, -49, -83, 22, 7, -40, -90, -46, -43, 23, 8, -59, -13, -81,
    -48, -31, 32, -41, -23, -38, -18, -3, 280, -405, 88, 64, -602, 103, -92, -52,
    -722, -173, -158, 89, -31, -311, 206, -321, -94, -184, 215, -129, 12, -111, -94, 31,
    40, -199, 157, 67, -204, -28, -127, -139, -154, -160, 46, 215, -23, 5, -2, -135,
    110, -180, 20, 32, -27, -104, -111, 184, -127, -66, -818, -430, -16, -297, -761, 136,
    -67, 518, -436, -640, 168, 134, -866, 136, 318, -267, -682, -446, 168, -869, -836, -442,
    -322, -44, -599, -432, -47, -459, 68, -469, 41, 85, 102, -595, -582, 37, 148, 100,
    -338, -87, -386, 145, -633, 149, 90, -386, 96, -63, -93, -143, 61, 4, 43, 57,
    36, 90, -211, -169, 52, -179, 68, -122, -106, 22, 46, -216, 30, -19, 28, -112,
    67, -42, -56, -70, -78, 76, -24, 19, -30, 3, -105, -37, 63, -136, 31, -134,
    -64, -65, 29, -116, 39, -33, -16, -30, 339, -769, -309, 173, 10, 390, -255, 465,
    174, -278, -627, -440, 122, -342, 307, 453, -158, 440, 411, -580, 207, -132, -170, -304
};

// ---------------------------------------------------------
// index: 133
// raw_name: batch_normalization_24/gamma
// c_name: main5_batch_normalization_24_gamma
// shape: [24]
// numel: 24
// float_min: 0.4892711639404297
// float_max: 1.3050178289413452
// q_min: 2004
// q_max: 5345
// max_abs_error: 0.00011867284774780273
// mean_abs_error: 5.22683076269459e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_24_GAMMA_NUMEL 24
#define MAIN5_BATCH_NORMALIZATION_24_GAMMA_DIM0 24
static const int16_t main5_batch_normalization_24_gamma[24] = {
    2334, 4079, 2004, 4757, 3546, 4021, 2613, 3579, 4050, 2501, 4776, 3188, 2806, 3766, 2064, 4222,
    4966, 4170, 2199, 5345, 2455, 2658, 2514, 3408
};

// ---------------------------------------------------------
// index: 134
// raw_name: batch_normalization_24/beta
// c_name: main5_batch_normalization_24_beta
// shape: [24]
// numel: 24
// float_min: -0.7553991675376892
// float_max: 0.2646353244781494
// q_min: -3094
// q_max: 1084
// max_abs_error: 0.00011910498142242432
// mean_abs_error: 4.9921683967113495e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_24_BETA_NUMEL 24
#define MAIN5_BATCH_NORMALIZATION_24_BETA_DIM0 24
static const int16_t main5_batch_normalization_24_beta[24] = {
    264, -3033, 345, -944, -2512, 1084, 325, -541, -3094, 771, -1378, 955, 442, -1188, 175, -292,
    -981, -2752, 194, -1347, 326, 582, 290, 1006
};

// ---------------------------------------------------------
// index: 135
// raw_name: batch_normalization_24/moving_mean
// c_name: main5_batch_normalization_24_moving_mean
// shape: [24]
// numel: 24
// float_min: -0.2389223277568817
// float_max: -0.030254850164055824
// q_min: -979
// q_max: -124
// max_abs_error: 0.00011657178401947021
// mean_abs_error: 6.179705815156922e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_24_MOVING_MEAN_NUMEL 24
#define MAIN5_BATCH_NORMALIZATION_24_MOVING_MEAN_DIM0 24
static const int16_t main5_batch_normalization_24_moving_mean[24] = {
    -175, -677, -588, -498, -836, -229, -726, -435, -979, -875, -631, -618, -436, -771, -463, -623,
    -483, -891, -124, -603, -356, -857, -817, -531
};

// ---------------------------------------------------------
// index: 136
// raw_name: batch_normalization_24/moving_variance
// c_name: main5_batch_normalization_24_moving_variance
// shape: [24]
// numel: 24
// float_min: 0.011468891054391861
// float_max: 0.08044131100177765
// q_min: 47
// q_max: 329
// max_abs_error: 0.00012097880244255066
// mean_abs_error: 6.25108732492663e-05
// ---------------------------------------------------------
#define MAIN5_BATCH_NORMALIZATION_24_MOVING_VARIANCE_NUMEL 24
#define MAIN5_BATCH_NORMALIZATION_24_MOVING_VARIANCE_DIM0 24
static const int16_t main5_batch_normalization_24_moving_variance[24] = {
    321, 55, 119, 71, 76, 59, 199, 47, 93, 329, 85, 118, 116, 137, 301, 164,
    66, 73, 235, 97, 149, 232, 234, 61
};

// ---------------------------------------------------------
// index: 137
// raw_name: class_output/kernel
// c_name: main5_class_output_kernel
// shape: [24, 5]
// numel: 120
// float_min: -1.3076727390289307
// float_max: 0.9895930886268616
// q_min: -5356
// q_max: 4053
// max_abs_error: 0.00011998414993286133
// mean_abs_error: 5.96956888330169e-05
// ---------------------------------------------------------
#define MAIN5_CLASS_OUTPUT_KERNEL_NUMEL 120
#define MAIN5_CLASS_OUTPUT_KERNEL_DIM0 24
#define MAIN5_CLASS_OUTPUT_KERNEL_DIM1 5
static const int16_t main5_class_output_kernel[120] = {
    3183, 82, -1443, -864, -1845, -1333, -793, -348, 2224, -1311, 1092, -4175, -5356, -3612, 2100, -1056,
    -139, 1780, -25, 1421, -3410, 3024, -1309, 2428, -2123, -772, -2434, 721, -2381, -3290, 2186, -2584,
    -1597, 3173, -2715, -876, 1881, 2238, -1559, -1296, -3237, 3279, -1128, 1532, -1680, 1321, 3059, -3560,
    2115, -3610, -1406, -1014, -1065, 1397, 1407, 930, -712, -1396, -1750, 1571, 1968, 3697, -1635, -2092,
    -2503, -4248, 1226, -3221, 932, 848, 3715, -2658, -2813, 554, -1233, -3856, 287, 924, 417, 262,
    -298, 1899, -202, -185, 1811, -1744, -1252, 3708, 2614, -1406, 2253, -2495, -3197, -2537, -462, -1645,
    -1019, -1043, 931, 959, 2498, 4053, -2944, -3140, -1474, 1032, -3367, -3026, 1683, -2031, 2290, -2971,
    -2100, 3195, -2641, 1443, -127, -682, -953, 2024
};

// ---------------------------------------------------------
// index: 138
// raw_name: class_output/bias
// c_name: main5_class_output_bias
// shape: [5]
// numel: 5
// float_min: -1.078855276107788
// float_max: 1.192745327949524
// q_min: -4419
// q_max: 4885
// max_abs_error: 0.00011837482452392578
// mean_abs_error: 5.062818672740832e-05
// ---------------------------------------------------------
#define MAIN5_CLASS_OUTPUT_BIAS_NUMEL 5
#define MAIN5_CLASS_OUTPUT_BIAS_DIM0 5
static const int16_t main5_class_output_bias[5] = {
    4885, -4419, -1768, -3408, -2084
};

#endif