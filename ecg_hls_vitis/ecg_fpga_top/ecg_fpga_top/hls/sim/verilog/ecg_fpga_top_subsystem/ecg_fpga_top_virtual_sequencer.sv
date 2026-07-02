//==============================================================
//Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2025.2 (64-bit)
//Tool Version Limit: 2025.11
//Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
//Copyright 2022-2025 Advanced Micro Devices, Inc. All Rights Reserved.
//
//==============================================================
`ifndef ECG_FPGA_TOP_VIRTUAL_SEQUENCER__SV                        
    `define ECG_FPGA_TOP_VIRTUAL_SEQUENCER__SV                    
                                                                       
    class ecg_fpga_top_virtual_sequencer extends uvm_sequencer;         
        axi_pkg::axi_virtual_sequencer gmem0_sqr; 
        axi_pkg::axi_virtual_sequencer gmem1_sqr; 
        axi_pkg::axi_virtual_sequencer gmem2_sqr; 
        axi_pkg::axi_virtual_sequencer CTRL_sqr; 
 
        function new (string name, uvm_component parent);              
            super.new(name, parent);                                   
            //`uvm_info(this.get_full_name(), "new is called", UVM_LOW)
        endfunction                                                    
                                                                       
        `uvm_component_utils_begin(ecg_fpga_top_virtual_sequencer)      
        `uvm_component_utils_end                                       
                                                                       
    endclass

`endif
