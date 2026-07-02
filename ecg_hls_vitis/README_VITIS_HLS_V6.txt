ECG HLS V6 clean project for PYNQ-Z2

This version is no-apfixed and int-only to avoid Vitis 2025.2 Windows CSim floating-point exception caused by ap_fixed/GMP.

Use only these design files:
- src/ecg_fpga_top.cpp
- src/ecg_hls_layers.cpp

Use only this testbench file:
- src/tb_ecg_fpga_top.cpp

Headers are included automatically by the .cpp files:
- src/ecg_fpga_top.h
- src/ecg_hls_layers.h
- src/main5_dense_only_q4_12_weights.h

Do NOT add these old export files in this V6 component:
- combined_q4_12_config.h
- main_5class_q4_12_weights.h
- pair_overlap_refiner_q4_12_weights.h

Top function:
- ecg_fpga_top

Part:
- xc7z020clg400-1

Clock:
- 10 ns

Command line:
1. run_csim.bat
2. run_csynth.bat
3. run_package.bat

Expected CSim console output:
TB_START
pred_class = <0..4>
score5_q12 = ...
TB_PASS
