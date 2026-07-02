//==============================================================
//Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2025.2 (64-bit)
//Tool Version Limit: 2025.11
//Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
//Copyright 2022-2025 Advanced Micro Devices, Inc. All Rights Reserved.
//
//==============================================================

`ifndef SV_MODULE_TOP_SV
`define SV_MODULE_TOP_SV


`timescale 1ns/1ps


`include "uvm_macros.svh"
import uvm_pkg::*;
import file_agent_pkg::*;
import ecg_fpga_top_subsystem_pkg::*;
`include "ecg_fpga_top_subsys_test_sequence_lib.sv"
`include "ecg_fpga_top_test_lib.sv"


module sv_module_top;


    misc_interface              misc_if ( .clock(apatb_ecg_fpga_top_top.AESL_clock), .reset(apatb_ecg_fpga_top_top.AESL_reset) );
    assign misc_if.dut2tb_ap_ready = apatb_ecg_fpga_top_top.AESL_inst_ecg_fpga_top.ap_ready;
    assign misc_if.dut2tb_ap_done_kernel = apatb_ecg_fpga_top_top.AESL_inst_ecg_fpga_top.ap_done;
    initial begin
        uvm_config_db #(virtual misc_interface)::set(null, "uvm_test_top.top_env.*", "misc_if", misc_if);
    end


    axi_if #(64,4,8,3,1)  axi_gmem0_if (.clk  (apatb_ecg_fpga_top_top.AESL_clock), .rst(apatb_ecg_fpga_top_top.AESL_reset));
    assign axi_gmem0_if.AWVALID = apatb_ecg_fpga_top_top.gmem0_AWVALID;
    assign apatb_ecg_fpga_top_top.gmem0_AWREADY = axi_gmem0_if.AWREADY;
    assign axi_gmem0_if.AWADDR = apatb_ecg_fpga_top_top.gmem0_AWADDR;
    assign axi_gmem0_if.AWID = apatb_ecg_fpga_top_top.gmem0_AWID;
    assign axi_gmem0_if.AWLEN = apatb_ecg_fpga_top_top.gmem0_AWLEN;
    assign axi_gmem0_if.AWSIZE = apatb_ecg_fpga_top_top.gmem0_AWSIZE;
    assign axi_gmem0_if.AWBURST = apatb_ecg_fpga_top_top.gmem0_AWBURST;
    assign axi_gmem0_if.AWLOCK = apatb_ecg_fpga_top_top.gmem0_AWLOCK;
    assign axi_gmem0_if.AWCACHE = apatb_ecg_fpga_top_top.gmem0_AWCACHE;
    assign axi_gmem0_if.AWPROT = apatb_ecg_fpga_top_top.gmem0_AWPROT;
    assign axi_gmem0_if.AWQOS = apatb_ecg_fpga_top_top.gmem0_AWQOS;
    assign axi_gmem0_if.AWREGION = apatb_ecg_fpga_top_top.gmem0_AWREGION;
    assign axi_gmem0_if.AWUSER = apatb_ecg_fpga_top_top.gmem0_AWUSER;
    assign axi_gmem0_if.WVALID = apatb_ecg_fpga_top_top.gmem0_WVALID;
    assign apatb_ecg_fpga_top_top.gmem0_WREADY = axi_gmem0_if.WREADY;
    assign axi_gmem0_if.WDATA = apatb_ecg_fpga_top_top.gmem0_WDATA;
    assign axi_gmem0_if.WSTRB = apatb_ecg_fpga_top_top.gmem0_WSTRB;
    assign axi_gmem0_if.WLAST = apatb_ecg_fpga_top_top.gmem0_WLAST;
    assign axi_gmem0_if.WID = apatb_ecg_fpga_top_top.gmem0_WID;
    assign axi_gmem0_if.WUSER = apatb_ecg_fpga_top_top.gmem0_WUSER;
    assign axi_gmem0_if.ARVALID = apatb_ecg_fpga_top_top.gmem0_ARVALID;
    assign apatb_ecg_fpga_top_top.gmem0_ARREADY = axi_gmem0_if.ARREADY;
    assign axi_gmem0_if.ARADDR = apatb_ecg_fpga_top_top.gmem0_ARADDR;
    assign axi_gmem0_if.ARID = apatb_ecg_fpga_top_top.gmem0_ARID;
    assign axi_gmem0_if.ARLEN = apatb_ecg_fpga_top_top.gmem0_ARLEN;
    assign axi_gmem0_if.ARSIZE = apatb_ecg_fpga_top_top.gmem0_ARSIZE;
    assign axi_gmem0_if.ARBURST = apatb_ecg_fpga_top_top.gmem0_ARBURST;
    assign axi_gmem0_if.ARLOCK = apatb_ecg_fpga_top_top.gmem0_ARLOCK;
    assign axi_gmem0_if.ARCACHE = apatb_ecg_fpga_top_top.gmem0_ARCACHE;
    assign axi_gmem0_if.ARPROT = apatb_ecg_fpga_top_top.gmem0_ARPROT;
    assign axi_gmem0_if.ARQOS = apatb_ecg_fpga_top_top.gmem0_ARQOS;
    assign axi_gmem0_if.ARREGION = apatb_ecg_fpga_top_top.gmem0_ARREGION;
    assign axi_gmem0_if.ARUSER = apatb_ecg_fpga_top_top.gmem0_ARUSER;
    assign apatb_ecg_fpga_top_top.gmem0_RVALID = axi_gmem0_if.RVALID;
    assign axi_gmem0_if.RREADY = apatb_ecg_fpga_top_top.gmem0_RREADY;
    assign apatb_ecg_fpga_top_top.gmem0_RDATA = axi_gmem0_if.RDATA;
    assign apatb_ecg_fpga_top_top.gmem0_RLAST = axi_gmem0_if.RLAST;
    assign apatb_ecg_fpga_top_top.gmem0_RID = axi_gmem0_if.RID;
    assign apatb_ecg_fpga_top_top.gmem0_RUSER = axi_gmem0_if.RUSER;
    assign apatb_ecg_fpga_top_top.gmem0_RRESP = axi_gmem0_if.RRESP;
    assign apatb_ecg_fpga_top_top.gmem0_BVALID = axi_gmem0_if.BVALID;
    assign axi_gmem0_if.BREADY = apatb_ecg_fpga_top_top.gmem0_BREADY;
    assign apatb_ecg_fpga_top_top.gmem0_BRESP = axi_gmem0_if.BRESP;
    assign apatb_ecg_fpga_top_top.gmem0_BID = axi_gmem0_if.BID;
    assign apatb_ecg_fpga_top_top.gmem0_BUSER = axi_gmem0_if.BUSER;
    initial begin
        uvm_config_db #( virtual axi_if#(64,4,8,3,1) )::set(null, "uvm_test_top.top_env.axi_master_gmem0.*", "vif", axi_gmem0_if);
    end


    axi_if #(64,4,8,3,1)  axi_gmem1_if (.clk  (apatb_ecg_fpga_top_top.AESL_clock), .rst(apatb_ecg_fpga_top_top.AESL_reset));
    assign axi_gmem1_if.AWVALID = apatb_ecg_fpga_top_top.gmem1_AWVALID;
    assign apatb_ecg_fpga_top_top.gmem1_AWREADY = axi_gmem1_if.AWREADY;
    assign axi_gmem1_if.AWADDR = apatb_ecg_fpga_top_top.gmem1_AWADDR;
    assign axi_gmem1_if.AWID = apatb_ecg_fpga_top_top.gmem1_AWID;
    assign axi_gmem1_if.AWLEN = apatb_ecg_fpga_top_top.gmem1_AWLEN;
    assign axi_gmem1_if.AWSIZE = apatb_ecg_fpga_top_top.gmem1_AWSIZE;
    assign axi_gmem1_if.AWBURST = apatb_ecg_fpga_top_top.gmem1_AWBURST;
    assign axi_gmem1_if.AWLOCK = apatb_ecg_fpga_top_top.gmem1_AWLOCK;
    assign axi_gmem1_if.AWCACHE = apatb_ecg_fpga_top_top.gmem1_AWCACHE;
    assign axi_gmem1_if.AWPROT = apatb_ecg_fpga_top_top.gmem1_AWPROT;
    assign axi_gmem1_if.AWQOS = apatb_ecg_fpga_top_top.gmem1_AWQOS;
    assign axi_gmem1_if.AWREGION = apatb_ecg_fpga_top_top.gmem1_AWREGION;
    assign axi_gmem1_if.AWUSER = apatb_ecg_fpga_top_top.gmem1_AWUSER;
    assign axi_gmem1_if.WVALID = apatb_ecg_fpga_top_top.gmem1_WVALID;
    assign apatb_ecg_fpga_top_top.gmem1_WREADY = axi_gmem1_if.WREADY;
    assign axi_gmem1_if.WDATA = apatb_ecg_fpga_top_top.gmem1_WDATA;
    assign axi_gmem1_if.WSTRB = apatb_ecg_fpga_top_top.gmem1_WSTRB;
    assign axi_gmem1_if.WLAST = apatb_ecg_fpga_top_top.gmem1_WLAST;
    assign axi_gmem1_if.WID = apatb_ecg_fpga_top_top.gmem1_WID;
    assign axi_gmem1_if.WUSER = apatb_ecg_fpga_top_top.gmem1_WUSER;
    assign axi_gmem1_if.ARVALID = apatb_ecg_fpga_top_top.gmem1_ARVALID;
    assign apatb_ecg_fpga_top_top.gmem1_ARREADY = axi_gmem1_if.ARREADY;
    assign axi_gmem1_if.ARADDR = apatb_ecg_fpga_top_top.gmem1_ARADDR;
    assign axi_gmem1_if.ARID = apatb_ecg_fpga_top_top.gmem1_ARID;
    assign axi_gmem1_if.ARLEN = apatb_ecg_fpga_top_top.gmem1_ARLEN;
    assign axi_gmem1_if.ARSIZE = apatb_ecg_fpga_top_top.gmem1_ARSIZE;
    assign axi_gmem1_if.ARBURST = apatb_ecg_fpga_top_top.gmem1_ARBURST;
    assign axi_gmem1_if.ARLOCK = apatb_ecg_fpga_top_top.gmem1_ARLOCK;
    assign axi_gmem1_if.ARCACHE = apatb_ecg_fpga_top_top.gmem1_ARCACHE;
    assign axi_gmem1_if.ARPROT = apatb_ecg_fpga_top_top.gmem1_ARPROT;
    assign axi_gmem1_if.ARQOS = apatb_ecg_fpga_top_top.gmem1_ARQOS;
    assign axi_gmem1_if.ARREGION = apatb_ecg_fpga_top_top.gmem1_ARREGION;
    assign axi_gmem1_if.ARUSER = apatb_ecg_fpga_top_top.gmem1_ARUSER;
    assign apatb_ecg_fpga_top_top.gmem1_RVALID = axi_gmem1_if.RVALID;
    assign axi_gmem1_if.RREADY = apatb_ecg_fpga_top_top.gmem1_RREADY;
    assign apatb_ecg_fpga_top_top.gmem1_RDATA = axi_gmem1_if.RDATA;
    assign apatb_ecg_fpga_top_top.gmem1_RLAST = axi_gmem1_if.RLAST;
    assign apatb_ecg_fpga_top_top.gmem1_RID = axi_gmem1_if.RID;
    assign apatb_ecg_fpga_top_top.gmem1_RUSER = axi_gmem1_if.RUSER;
    assign apatb_ecg_fpga_top_top.gmem1_RRESP = axi_gmem1_if.RRESP;
    assign apatb_ecg_fpga_top_top.gmem1_BVALID = axi_gmem1_if.BVALID;
    assign axi_gmem1_if.BREADY = apatb_ecg_fpga_top_top.gmem1_BREADY;
    assign apatb_ecg_fpga_top_top.gmem1_BRESP = axi_gmem1_if.BRESP;
    assign apatb_ecg_fpga_top_top.gmem1_BID = axi_gmem1_if.BID;
    assign apatb_ecg_fpga_top_top.gmem1_BUSER = axi_gmem1_if.BUSER;
    initial begin
        uvm_config_db #( virtual axi_if#(64,4,8,3,1) )::set(null, "uvm_test_top.top_env.axi_master_gmem1.*", "vif", axi_gmem1_if);
    end


    axi_if #(64,4,8,3,1)  axi_gmem2_if (.clk  (apatb_ecg_fpga_top_top.AESL_clock), .rst(apatb_ecg_fpga_top_top.AESL_reset));
    assign axi_gmem2_if.AWVALID = apatb_ecg_fpga_top_top.gmem2_AWVALID;
    assign apatb_ecg_fpga_top_top.gmem2_AWREADY = axi_gmem2_if.AWREADY;
    assign axi_gmem2_if.AWADDR = apatb_ecg_fpga_top_top.gmem2_AWADDR;
    assign axi_gmem2_if.AWID = apatb_ecg_fpga_top_top.gmem2_AWID;
    assign axi_gmem2_if.AWLEN = apatb_ecg_fpga_top_top.gmem2_AWLEN;
    assign axi_gmem2_if.AWSIZE = apatb_ecg_fpga_top_top.gmem2_AWSIZE;
    assign axi_gmem2_if.AWBURST = apatb_ecg_fpga_top_top.gmem2_AWBURST;
    assign axi_gmem2_if.AWLOCK = apatb_ecg_fpga_top_top.gmem2_AWLOCK;
    assign axi_gmem2_if.AWCACHE = apatb_ecg_fpga_top_top.gmem2_AWCACHE;
    assign axi_gmem2_if.AWPROT = apatb_ecg_fpga_top_top.gmem2_AWPROT;
    assign axi_gmem2_if.AWQOS = apatb_ecg_fpga_top_top.gmem2_AWQOS;
    assign axi_gmem2_if.AWREGION = apatb_ecg_fpga_top_top.gmem2_AWREGION;
    assign axi_gmem2_if.AWUSER = apatb_ecg_fpga_top_top.gmem2_AWUSER;
    assign axi_gmem2_if.WVALID = apatb_ecg_fpga_top_top.gmem2_WVALID;
    assign apatb_ecg_fpga_top_top.gmem2_WREADY = axi_gmem2_if.WREADY;
    assign axi_gmem2_if.WDATA = apatb_ecg_fpga_top_top.gmem2_WDATA;
    assign axi_gmem2_if.WSTRB = apatb_ecg_fpga_top_top.gmem2_WSTRB;
    assign axi_gmem2_if.WLAST = apatb_ecg_fpga_top_top.gmem2_WLAST;
    assign axi_gmem2_if.WID = apatb_ecg_fpga_top_top.gmem2_WID;
    assign axi_gmem2_if.WUSER = apatb_ecg_fpga_top_top.gmem2_WUSER;
    assign axi_gmem2_if.ARVALID = apatb_ecg_fpga_top_top.gmem2_ARVALID;
    assign apatb_ecg_fpga_top_top.gmem2_ARREADY = axi_gmem2_if.ARREADY;
    assign axi_gmem2_if.ARADDR = apatb_ecg_fpga_top_top.gmem2_ARADDR;
    assign axi_gmem2_if.ARID = apatb_ecg_fpga_top_top.gmem2_ARID;
    assign axi_gmem2_if.ARLEN = apatb_ecg_fpga_top_top.gmem2_ARLEN;
    assign axi_gmem2_if.ARSIZE = apatb_ecg_fpga_top_top.gmem2_ARSIZE;
    assign axi_gmem2_if.ARBURST = apatb_ecg_fpga_top_top.gmem2_ARBURST;
    assign axi_gmem2_if.ARLOCK = apatb_ecg_fpga_top_top.gmem2_ARLOCK;
    assign axi_gmem2_if.ARCACHE = apatb_ecg_fpga_top_top.gmem2_ARCACHE;
    assign axi_gmem2_if.ARPROT = apatb_ecg_fpga_top_top.gmem2_ARPROT;
    assign axi_gmem2_if.ARQOS = apatb_ecg_fpga_top_top.gmem2_ARQOS;
    assign axi_gmem2_if.ARREGION = apatb_ecg_fpga_top_top.gmem2_ARREGION;
    assign axi_gmem2_if.ARUSER = apatb_ecg_fpga_top_top.gmem2_ARUSER;
    assign apatb_ecg_fpga_top_top.gmem2_RVALID = axi_gmem2_if.RVALID;
    assign axi_gmem2_if.RREADY = apatb_ecg_fpga_top_top.gmem2_RREADY;
    assign apatb_ecg_fpga_top_top.gmem2_RDATA = axi_gmem2_if.RDATA;
    assign apatb_ecg_fpga_top_top.gmem2_RLAST = axi_gmem2_if.RLAST;
    assign apatb_ecg_fpga_top_top.gmem2_RID = axi_gmem2_if.RID;
    assign apatb_ecg_fpga_top_top.gmem2_RUSER = axi_gmem2_if.RUSER;
    assign apatb_ecg_fpga_top_top.gmem2_RRESP = axi_gmem2_if.RRESP;
    assign apatb_ecg_fpga_top_top.gmem2_BVALID = axi_gmem2_if.BVALID;
    assign axi_gmem2_if.BREADY = apatb_ecg_fpga_top_top.gmem2_BREADY;
    assign apatb_ecg_fpga_top_top.gmem2_BRESP = axi_gmem2_if.BRESP;
    assign apatb_ecg_fpga_top_top.gmem2_BID = axi_gmem2_if.BID;
    assign apatb_ecg_fpga_top_top.gmem2_BUSER = axi_gmem2_if.BUSER;
    initial begin
        uvm_config_db #( virtual axi_if#(64,4,8,3,1) )::set(null, "uvm_test_top.top_env.axi_master_gmem2.*", "vif", axi_gmem2_if);
    end


    axi_if #(6,4,4,3,1)  axi_CTRL_if (.clk  (apatb_ecg_fpga_top_top.AESL_clock), .rst(apatb_ecg_fpga_top_top.AESL_reset));
    assign apatb_ecg_fpga_top_top.CTRL_AWADDR = axi_CTRL_if.AWADDR;
    assign apatb_ecg_fpga_top_top.CTRL_AWVALID = axi_CTRL_if.AWVALID;
    assign axi_CTRL_if.AWREADY = apatb_ecg_fpga_top_top.CTRL_AWREADY;
    assign apatb_ecg_fpga_top_top.CTRL_WVALID = axi_CTRL_if.WVALID;
    assign axi_CTRL_if.WREADY = apatb_ecg_fpga_top_top.CTRL_WREADY;
    assign apatb_ecg_fpga_top_top.CTRL_WDATA = axi_CTRL_if.WDATA;
    assign apatb_ecg_fpga_top_top.CTRL_WSTRB = axi_CTRL_if.WSTRB;
    assign apatb_ecg_fpga_top_top.CTRL_ARADDR = axi_CTRL_if.ARADDR;
    assign apatb_ecg_fpga_top_top.CTRL_ARVALID = axi_CTRL_if.ARVALID;
    assign axi_CTRL_if.ARREADY = apatb_ecg_fpga_top_top.CTRL_ARREADY;
    assign axi_CTRL_if.RVALID = apatb_ecg_fpga_top_top.CTRL_RVALID;
    assign apatb_ecg_fpga_top_top.CTRL_RREADY = axi_CTRL_if.RREADY;
    assign axi_CTRL_if.RDATA = apatb_ecg_fpga_top_top.CTRL_RDATA;
    assign axi_CTRL_if.RRESP = apatb_ecg_fpga_top_top.CTRL_RRESP;
    assign axi_CTRL_if.BVALID = apatb_ecg_fpga_top_top.CTRL_BVALID;
    assign apatb_ecg_fpga_top_top.CTRL_BREADY = axi_CTRL_if.BREADY;
    assign axi_CTRL_if.BRESP = apatb_ecg_fpga_top_top.CTRL_BRESP;
    assign axi_CTRL_if.BID = 0;
    assign axi_CTRL_if.RID = 0;
    assign axi_CTRL_if.RLAST = 1;
    initial begin
        uvm_config_db #( virtual axi_if#(6,4,4,3,1) )::set(null, "uvm_test_top.top_env.axi_lite_CTRL.*", "vif", axi_CTRL_if);
    end


    initial begin
        run_test();
    end
endmodule
`endif
