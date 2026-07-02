// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2025.2 (64-bit)
// Tool Version Limit: 2025.11
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2025 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
# 1 "T:/SoC/Project/RTOS/ecg_hls_vitis_clean_project_v6/src/ecg_fpga_top.cpp"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 432 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "T:/SoC/Project/RTOS/ecg_hls_vitis_clean_project_v6/src/ecg_fpga_top.cpp" 2
# 1 "T:/SoC/Project/RTOS/ecg_hls_vitis_clean_project_v6/src/ecg_fpga_top.h" 1



# 1 "T:\\SoC\\2025.2\\Vitis\\win64\\tools\\clang-16\\lib\\clang\\16\\include\\stdint.h" 1 3
# 52 "T:\\SoC\\2025.2\\Vitis\\win64\\tools\\clang-16\\lib\\clang\\16\\include\\stdint.h" 3
# 1 "T:/SoC/2025.2/Vitis/tps/mingw/10.0.0/win64.o/nt\\x86_64-w64-mingw32\\include\\stdint.h" 1 3
# 28 "T:/SoC/2025.2/Vitis/tps/mingw/10.0.0/win64.o/nt\\x86_64-w64-mingw32\\include\\stdint.h" 3
# 1 "T:/SoC/2025.2/Vitis/tps/mingw/10.0.0/win64.o/nt\\x86_64-w64-mingw32\\include\\crtdefs.h" 1 3
# 10 "T:/SoC/2025.2/Vitis/tps/mingw/10.0.0/win64.o/nt\\x86_64-w64-mingw32\\include\\crtdefs.h" 3
# 1 "T:/SoC/2025.2/Vitis/tps/mingw/10.0.0/win64.o/nt\\x86_64-w64-mingw32\\include\\corecrt.h" 1 3
# 10 "T:/SoC/2025.2/Vitis/tps/mingw/10.0.0/win64.o/nt\\x86_64-w64-mingw32\\include\\corecrt.h" 3
# 1 "T:/SoC/2025.2/Vitis/tps/mingw/10.0.0/win64.o/nt\\x86_64-w64-mingw32\\include\\_mingw.h" 1 3
# 10 "T:/SoC/2025.2/Vitis/tps/mingw/10.0.0/win64.o/nt\\x86_64-w64-mingw32\\include\\_mingw.h" 3
# 1 "T:/SoC/2025.2/Vitis/tps/mingw/10.0.0/win64.o/nt\\x86_64-w64-mingw32\\include/_mingw_mac.h" 1 3
# 11 "T:/SoC/2025.2/Vitis/tps/mingw/10.0.0/win64.o/nt\\x86_64-w64-mingw32\\include\\_mingw.h" 2 3
# 1 "T:/SoC/2025.2/Vitis/tps/mingw/10.0.0/win64.o/nt\\x86_64-w64-mingw32\\include/_mingw_secapi.h" 1 3
# 44 "T:/SoC/2025.2/Vitis/tps/mingw/10.0.0/win64.o/nt\\x86_64-w64-mingw32\\include/_mingw_secapi.h" 3
extern "C++" {
template <bool __test, typename __dsttype>
  struct __if_array;
template <typename __dsttype>
  struct __if_array <true, __dsttype> {
    typedef __dsttype __type;
};
}
# 12 "T:/SoC/2025.2/Vitis/tps/mingw/10.0.0/win64.o/nt\\x86_64-w64-mingw32\\include\\_mingw.h" 2 3
# 289 "T:/SoC/2025.2/Vitis/tps/mingw/10.0.0/win64.o/nt\\x86_64-w64-mingw32\\include\\_mingw.h" 3
# 1 "T:\\SoC\\2025.2\\Vitis\\win64\\tools\\clang-16\\lib\\clang\\16\\include\\vadefs.h" 1 3
# 12 "T:\\SoC\\2025.2\\Vitis\\win64\\tools\\clang-16\\lib\\clang\\16\\include\\vadefs.h" 3
# 1 "T:/SoC/2025.2/Vitis/tps/mingw/10.0.0/win64.o/nt\\x86_64-w64-mingw32\\include\\vadefs.h" 1 3








# 1 "T:/SoC/2025.2/Vitis/tps/mingw/10.0.0/win64.o/nt\\x86_64-w64-mingw32\\include\\_mingw.h" 1 3
# 623 "T:/SoC/2025.2/Vitis/tps/mingw/10.0.0/win64.o/nt\\x86_64-w64-mingw32\\include\\_mingw.h" 3
# 1 "T:/SoC/2025.2/Vitis/tps/mingw/10.0.0/win64.o/nt\\x86_64-w64-mingw32\\include/sdks/_mingw_ddk.h" 1 3
# 624 "T:/SoC/2025.2/Vitis/tps/mingw/10.0.0/win64.o/nt\\x86_64-w64-mingw32\\include\\_mingw.h" 2 3
# 10 "T:/SoC/2025.2/Vitis/tps/mingw/10.0.0/win64.o/nt\\x86_64-w64-mingw32\\include\\vadefs.h" 2 3




#pragma pack(push,_CRT_PACKING)



extern "C" {





  typedef __builtin_va_list __gnuc_va_list;






  typedef __gnuc_va_list va_list;
# 99 "T:/SoC/2025.2/Vitis/tps/mingw/10.0.0/win64.o/nt\\x86_64-w64-mingw32\\include\\vadefs.h" 3
}



#pragma pack(pop)
# 13 "T:\\SoC\\2025.2\\Vitis\\win64\\tools\\clang-16\\lib\\clang\\16\\include\\vadefs.h" 2 3
# 290 "T:/SoC/2025.2/Vitis/tps/mingw/10.0.0/win64.o/nt\\x86_64-w64-mingw32\\include\\_mingw.h" 2 3
# 575 "T:/SoC/2025.2/Vitis/tps/mingw/10.0.0/win64.o/nt\\x86_64-w64-mingw32\\include\\_mingw.h" 3
extern "C" {
# 586 "T:/SoC/2025.2/Vitis/tps/mingw/10.0.0/win64.o/nt\\x86_64-w64-mingw32\\include\\_mingw.h" 3
void __attribute__((__cdecl__)) __debugbreak(void);
extern __inline__ __attribute__((__always_inline__,__gnu_inline__)) void __attribute__((__cdecl__)) __debugbreak(void)
{

  __asm__ __volatile__("int {$}3":);







}




const char *__mingw_get_crt_info (void);


}
# 11 "T:/SoC/2025.2/Vitis/tps/mingw/10.0.0/win64.o/nt\\x86_64-w64-mingw32\\include\\corecrt.h" 2 3




#pragma pack(push,_CRT_PACKING)
# 35 "T:/SoC/2025.2/Vitis/tps/mingw/10.0.0/win64.o/nt\\x86_64-w64-mingw32\\include\\corecrt.h" 3
__extension__ typedef unsigned long long size_t;
# 45 "T:/SoC/2025.2/Vitis/tps/mingw/10.0.0/win64.o/nt\\x86_64-w64-mingw32\\include\\corecrt.h" 3
__extension__ typedef long long ssize_t;






typedef size_t rsize_t;
# 62 "T:/SoC/2025.2/Vitis/tps/mingw/10.0.0/win64.o/nt\\x86_64-w64-mingw32\\include\\corecrt.h" 3
__extension__ typedef long long intptr_t;
# 75 "T:/SoC/2025.2/Vitis/tps/mingw/10.0.0/win64.o/nt\\x86_64-w64-mingw32\\include\\corecrt.h" 3
__extension__ typedef unsigned long long uintptr_t;
# 88 "T:/SoC/2025.2/Vitis/tps/mingw/10.0.0/win64.o/nt\\x86_64-w64-mingw32\\include\\corecrt.h" 3
__extension__ typedef long long ptrdiff_t;
# 106 "T:/SoC/2025.2/Vitis/tps/mingw/10.0.0/win64.o/nt\\x86_64-w64-mingw32\\include\\corecrt.h" 3
typedef unsigned short wint_t;
typedef unsigned short wctype_t;





typedef int errno_t;




typedef long __time32_t;




__extension__ typedef long long __time64_t;
# 138 "T:/SoC/2025.2/Vitis/tps/mingw/10.0.0/win64.o/nt\\x86_64-w64-mingw32\\include\\corecrt.h" 3
typedef __time64_t time_t;
# 430 "T:/SoC/2025.2/Vitis/tps/mingw/10.0.0/win64.o/nt\\x86_64-w64-mingw32\\include\\corecrt.h" 3
struct threadlocaleinfostruct;
struct threadmbcinfostruct;
typedef struct threadlocaleinfostruct *pthreadlocinfo;
typedef struct threadmbcinfostruct *pthreadmbcinfo;
struct __lc_time_data;

typedef struct localeinfo_struct {
  pthreadlocinfo locinfo;
  pthreadmbcinfo mbcinfo;
} _locale_tstruct,*_locale_t;



typedef struct tagLC_ID {
  unsigned short wLanguage;
  unsigned short wCountry;
  unsigned short wCodePage;
} LC_ID,*LPLC_ID;




typedef struct threadlocaleinfostruct {





  int refcount;
  unsigned int lc_codepage;
  unsigned int lc_collate_cp;
  unsigned long lc_handle[6];
  LC_ID lc_id[6];
  struct {
    char *locale;
    wchar_t *wlocale;
    int *refcount;
    int *wrefcount;
  } lc_category[6];
  int lc_clike;
  int mb_cur_max;
  int *lconv_intl_refcount;
  int *lconv_num_refcount;
  int *lconv_mon_refcount;
  struct lconv *lconv;
  int *ctype1_refcount;
  unsigned short *ctype1;
  const unsigned short *pctype;
  const unsigned char *pclmap;
  const unsigned char *pcumap;
  struct __lc_time_data *lc_time_curr;

} threadlocinfo;
# 501 "T:/SoC/2025.2/Vitis/tps/mingw/10.0.0/win64.o/nt\\x86_64-w64-mingw32\\include\\corecrt.h" 3
#pragma pack(pop)
# 11 "T:/SoC/2025.2/Vitis/tps/mingw/10.0.0/win64.o/nt\\x86_64-w64-mingw32\\include\\crtdefs.h" 2 3
# 29 "T:/SoC/2025.2/Vitis/tps/mingw/10.0.0/win64.o/nt\\x86_64-w64-mingw32\\include\\stdint.h" 2 3



# 1 "T:\\SoC\\2025.2\\Vitis\\win64\\tools\\clang-16\\lib\\clang\\16\\include\\stddef.h" 1 3
# 33 "T:/SoC/2025.2/Vitis/tps/mingw/10.0.0/win64.o/nt\\x86_64-w64-mingw32\\include\\stdint.h" 2 3


typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef short int16_t;
typedef unsigned short uint16_t;
typedef int int32_t;
typedef unsigned uint32_t;
__extension__ typedef long long int64_t;
__extension__ typedef unsigned long long uint64_t;


typedef signed char int_least8_t;
typedef unsigned char uint_least8_t;
typedef short int_least16_t;
typedef unsigned short uint_least16_t;
typedef int int_least32_t;
typedef unsigned uint_least32_t;
__extension__ typedef long long int_least64_t;
__extension__ typedef unsigned long long uint_least64_t;





typedef signed char int_fast8_t;
typedef unsigned char uint_fast8_t;
typedef short int_fast16_t;
typedef unsigned short uint_fast16_t;
typedef int int_fast32_t;
typedef unsigned int uint_fast32_t;
__extension__ typedef long long int_fast64_t;
__extension__ typedef unsigned long long uint_fast64_t;


__extension__ typedef long long intmax_t;
__extension__ typedef unsigned long long uintmax_t;
# 53 "T:\\SoC\\2025.2\\Vitis\\win64\\tools\\clang-16\\lib\\clang\\16\\include\\stdint.h" 2 3
# 5 "T:/SoC/Project/RTOS/ecg_hls_vitis_clean_project_v6/src/ecg_fpga_top.h" 2







extern "C" {


void ecg_fpga_top(
    int16_t beat_in_q12[320],
    int32_t pred_class[1],
    int16_t score5_q12[5]
);


}
# 2 "T:/SoC/Project/RTOS/ecg_hls_vitis_clean_project_v6/src/ecg_fpga_top.cpp" 2
# 1 "T:/SoC/Project/RTOS/ecg_hls_vitis_clean_project_v6/src/ecg_hls_layers.h" 1






int16_t clip_i16(int32_t x);

void extract_light_features_40_int(
    const int16_t beat_q12[320],
    int16_t feat_q12[40]
);

void dense_40x24_relu_int(
    const int16_t in_q12[40],
    const int16_t *kernel_q12,
    int16_t out_q12[24]
);

void dense_24x5_linear_int(
    const int16_t in_q12[24],
    const int16_t *kernel_q12,
    const int16_t bias_q12[5],
    int16_t out_q12[5]
);

int32_t argmax5_int(
    const int16_t score_q12[5]
);
# 3 "T:/SoC/Project/RTOS/ecg_hls_vitis_clean_project_v6/src/ecg_fpga_top.cpp" 2
# 1 "T:/SoC/Project/RTOS/ecg_hls_vitis_clean_project_v6/src/main5_dense_only_q4_12_weights.h" 1
# 10 "T:/SoC/Project/RTOS/ecg_hls_vitis_clean_project_v6/src/main5_dense_only_q4_12_weights.h"
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

static const int16_t main5_class_output_bias[5] = {
4885, -4419, -1768, -3408, -2084
};
# 4 "T:/SoC/Project/RTOS/ecg_hls_vitis_clean_project_v6/src/ecg_fpga_top.cpp" 2

void ecg_fpga_top(
    int16_t beat_in_q12[320],
    int32_t pred_class[1],
    int16_t score5_q12[5]
)
{
#pragma HLS INTERFACE m_axi port=beat_in_q12 offset=slave bundle=gmem0 depth=320
#pragma HLS INTERFACE m_axi port=pred_class offset=slave bundle=gmem1 depth=1
#pragma HLS INTERFACE m_axi port=score5_q12 offset=slave bundle=gmem2 depth=5

#pragma HLS INTERFACE s_axilite port=beat_in_q12 bundle=CTRL
#pragma HLS INTERFACE s_axilite port=pred_class bundle=CTRL
#pragma HLS INTERFACE s_axilite port=score5_q12 bundle=CTRL
#pragma HLS INTERFACE s_axilite port=return bundle=CTRL

    int16_t beat_local[320];
    int16_t feat_q12[40];
    int16_t hidden_q12[24];
    int16_t score_q12[5];

#pragma HLS ARRAY_PARTITION variable=feat_q12 complete dim=1
#pragma HLS ARRAY_PARTITION variable=hidden_q12 complete dim=1
#pragma HLS ARRAY_PARTITION variable=score_q12 complete dim=1

    for (int i = 0; i < 320; i++) {
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

    for (int i = 0; i < 5; i++) {
#pragma HLS PIPELINE II=1
        score5_q12[i] = score_q12[i];
    }
}
#ifndef HLS_FASTSIM
#ifdef __cplusplus
extern "C"
#endif
void apatb_ecg_fpga_top_ir(short *, int *, short *);
#ifdef __cplusplus
extern "C"
#endif
void ecg_fpga_top_hw_stub(short *beat_in_q12, int *pred_class, short *score5_q12){
ecg_fpga_top(beat_in_q12, pred_class, score5_q12);
return ;
}
#ifdef __cplusplus
extern "C"
#endif
void refine_signal_handler();
#ifdef __cplusplus
extern "C"
#endif
void apatb_ecg_fpga_top_sw(short *beat_in_q12, int *pred_class, short *score5_q12){
refine_signal_handler();
apatb_ecg_fpga_top_ir(beat_in_q12, pred_class, score5_q12);
return ;
}
#endif
# 55 "T:/SoC/Project/RTOS/ecg_hls_vitis_clean_project_v6/src/ecg_fpga_top.cpp"

