# ==============================================================
# Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2025.2 (64-bit)
# Tool Version Limit: 2025.11
# Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
# Copyright 2022-2025 Advanced Micro Devices, Inc. All Rights Reserved.
# 
# ==============================================================
source -notrace "T:/SoC/2025.2/Vitis/common/scripts/ipxhls.tcl"
set ip_out_dir "T:/SoC/Project/RTOS/ecg_hls_vitis_clean_project_v6/ecg_fpga_top/ecg_fpga_top/hls/impl/ip"
set data_file "T:/SoC/Project/RTOS/ecg_hls_vitis_clean_project_v6/ecg_fpga_top/ecg_fpga_top/hls/hls_data.json"
set src_dir [file dir $data_file]
set ip_types {vitis sysgen}
set ippack_opts_dict {}
if { [catch {::ipx::utils::package_hls_ip $ip_out_dir $data_file $ip_types $src_dir $ippack_opts_dict} res] } {
  puts "Caught error:\n$::errorInfo"
  error $res
}
