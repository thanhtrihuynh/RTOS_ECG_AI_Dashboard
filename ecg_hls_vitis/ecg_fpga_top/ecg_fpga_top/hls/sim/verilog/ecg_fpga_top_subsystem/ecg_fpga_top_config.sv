//==============================================================
//Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2025.2 (64-bit)
//Tool Version Limit: 2025.11
//Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
//Copyright 2022-2025 Advanced Micro Devices, Inc. All Rights Reserved.
//
//==============================================================
`ifndef ECG_FPGA_TOP_CONFIG__SV                        
    `define ECG_FPGA_TOP_CONFIG__SV                    
                                                            
    class ecg_fpga_top_config extends uvm_object;            
                                                            
        int check_ena;                                      
        int cover_ena;                                      
        axi_pkg::axi_cfg gmem0_cfg;
        axi_pkg::axi_cfg gmem1_cfg;
        axi_pkg::axi_cfg gmem2_cfg;
        axi_pkg::axi_cfg CTRL_cfg;

        `uvm_object_utils_begin(ecg_fpga_top_config)         
        `uvm_field_object(gmem0_cfg, UVM_DEFAULT);
        `uvm_field_object(gmem1_cfg, UVM_DEFAULT);
        `uvm_field_object(gmem2_cfg, UVM_DEFAULT);
        `uvm_field_object(CTRL_cfg, UVM_DEFAULT);
        `uvm_field_int   (check_ena , UVM_DEFAULT)          
        `uvm_field_int   (cover_ena , UVM_DEFAULT)          
        `uvm_object_utils_end                               

        function new (string name = "ecg_fpga_top_config");
            super.new(name);                                
            gmem0_cfg = new("gmem0_cfg", 1);
            gmem1_cfg = new("gmem1_cfg", 1);
            gmem2_cfg = new("gmem2_cfg", 1);
            CTRL_cfg = axi_pkg::axi_cfg::type_id::create("CTRL_cfg");
        endfunction                                         
                                                            
    endclass                                                
                                                            
`endif                                                      
