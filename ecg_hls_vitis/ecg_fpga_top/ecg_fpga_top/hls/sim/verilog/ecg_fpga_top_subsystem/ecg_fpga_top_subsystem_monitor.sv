//==============================================================
//Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2025.2 (64-bit)
//Tool Version Limit: 2025.11
//Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
//Copyright 2022-2025 Advanced Micro Devices, Inc. All Rights Reserved.
//
//==============================================================

`ifndef ECG_FPGA_TOP_SUBSYSTEM_MONITOR_SV
`define ECG_FPGA_TOP_SUBSYSTEM_MONITOR_SV

`uvm_analysis_imp_decl(_axi_wtr_gmem0)
`uvm_analysis_imp_decl(_axi_rtr_gmem0)
`uvm_analysis_imp_decl(_axi_wtr_gmem1)
`uvm_analysis_imp_decl(_axi_rtr_gmem1)
`uvm_analysis_imp_decl(_axi_wtr_gmem2)
`uvm_analysis_imp_decl(_axi_rtr_gmem2)
`uvm_analysis_imp_decl(_axi_wtr_CTRL)
`uvm_analysis_imp_decl(_axi_rtr_CTRL)

class ecg_fpga_top_subsystem_monitor extends uvm_component;

    ecg_fpga_top_reference_model refm;
    ecg_fpga_top_scoreboard scbd;

    `uvm_component_utils_begin(ecg_fpga_top_subsystem_monitor)
    `uvm_component_utils_end

    uvm_analysis_imp_axi_wtr_gmem0#(axi_pkg::axi_transfer, ecg_fpga_top_subsystem_monitor) gmem0_wtr_imp;
    uvm_analysis_imp_axi_rtr_gmem0#(axi_pkg::axi_transfer, ecg_fpga_top_subsystem_monitor) gmem0_rtr_imp;
    uvm_analysis_imp_axi_wtr_gmem1#(axi_pkg::axi_transfer, ecg_fpga_top_subsystem_monitor) gmem1_wtr_imp;
    uvm_analysis_imp_axi_rtr_gmem1#(axi_pkg::axi_transfer, ecg_fpga_top_subsystem_monitor) gmem1_rtr_imp;
    uvm_analysis_imp_axi_wtr_gmem2#(axi_pkg::axi_transfer, ecg_fpga_top_subsystem_monitor) gmem2_wtr_imp;
    uvm_analysis_imp_axi_rtr_gmem2#(axi_pkg::axi_transfer, ecg_fpga_top_subsystem_monitor) gmem2_rtr_imp;
    uvm_analysis_imp_axi_wtr_CTRL#(axi_pkg::axi_transfer, ecg_fpga_top_subsystem_monitor) CTRL_wtr_imp;
    uvm_analysis_imp_axi_rtr_CTRL#(axi_pkg::axi_transfer, ecg_fpga_top_subsystem_monitor) CTRL_rtr_imp;

    virtual function void build_phase(uvm_phase phase);
        super.build_phase(phase);
        if (!uvm_config_db#(ecg_fpga_top_reference_model)::get(this, "", "refm", refm))
            `uvm_fatal(this.get_full_name(), "No refm from high level")
        `uvm_info(this.get_full_name(), "get reference model by uvm_config_db", UVM_MEDIUM)
        scbd = ecg_fpga_top_scoreboard::type_id::create("scbd", this);
    endfunction

    virtual function void connect_phase(uvm_phase phase);
        super.connect_phase(phase);
    endfunction

    function new (string name = "", uvm_component parent = null);
        super.new(name, parent);
        gmem0_wtr_imp = new("gmem0_wtr_imp", this);
        gmem0_rtr_imp = new("gmem0_rtr_imp", this);
        gmem1_wtr_imp = new("gmem1_wtr_imp", this);
        gmem1_rtr_imp = new("gmem1_rtr_imp", this);
        gmem2_wtr_imp = new("gmem2_wtr_imp", this);
        gmem2_rtr_imp = new("gmem2_rtr_imp", this);
        CTRL_wtr_imp = new("CTRL_wtr_imp", this);
        CTRL_rtr_imp = new("CTRL_rtr_imp", this);
    endfunction

    virtual function void write_axi_wtr_gmem0(axi_transfer tr);
        refm.write_axi_wtr_gmem0(tr);
        scbd.write_axi_wtr_gmem0(tr);
    endfunction

    virtual function void write_axi_rtr_gmem0(axi_transfer tr);
        refm.write_axi_rtr_gmem0(tr);
        scbd.write_axi_rtr_gmem0(tr);
    endfunction

    virtual function void write_axi_wtr_gmem1(axi_transfer tr);
        refm.write_axi_wtr_gmem1(tr);
        scbd.write_axi_wtr_gmem1(tr);
    endfunction

    virtual function void write_axi_rtr_gmem1(axi_transfer tr);
        refm.write_axi_rtr_gmem1(tr);
        scbd.write_axi_rtr_gmem1(tr);
    endfunction

    virtual function void write_axi_wtr_gmem2(axi_transfer tr);
        refm.write_axi_wtr_gmem2(tr);
        scbd.write_axi_wtr_gmem2(tr);
    endfunction

    virtual function void write_axi_rtr_gmem2(axi_transfer tr);
        refm.write_axi_rtr_gmem2(tr);
        scbd.write_axi_rtr_gmem2(tr);
    endfunction

    virtual function void write_axi_wtr_CTRL(axi_transfer tr);
        refm.write_axi_wtr_CTRL(tr);
        scbd.write_axi_wtr_CTRL(tr);
    endfunction

    virtual function void write_axi_rtr_CTRL(axi_transfer tr);
        refm.write_axi_rtr_CTRL(tr);
        scbd.write_axi_rtr_CTRL(tr);
    endfunction
endclass
`endif
