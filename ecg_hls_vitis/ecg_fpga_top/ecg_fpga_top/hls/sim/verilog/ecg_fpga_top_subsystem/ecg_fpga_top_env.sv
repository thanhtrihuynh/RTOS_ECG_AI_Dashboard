//==============================================================
//Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2025.2 (64-bit)
//Tool Version Limit: 2025.11
//Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
//Copyright 2022-2025 Advanced Micro Devices, Inc. All Rights Reserved.
//
//==============================================================
`ifndef ECG_FPGA_TOP_ENV__SV                                                                                   
    `define ECG_FPGA_TOP_ENV__SV                                                                               
                                                                                                                    
                                                                                                                    
    class ecg_fpga_top_env extends uvm_env;                                                                          
                                                                                                                    
        ecg_fpga_top_virtual_sequencer ecg_fpga_top_virtual_sqr;                                                      
        ecg_fpga_top_config ecg_fpga_top_cfg;                                                                         
                                                                                                                    
        axi_pkg::axi_env#(64,4,8,3,1) axi_master_gmem0;
        axi_pkg::axi_env#(64,4,8,3,1) axi_master_gmem1;
        axi_pkg::axi_env#(64,4,8,3,1) axi_master_gmem2;
        axi_pkg::axi_env#(6,4,4,3,1) axi_lite_CTRL;
                                                                                                                    
        ecg_fpga_top_reference_model   refm;                                                                         
                                                                                                                    
        ecg_fpga_top_subsystem_monitor subsys_mon;                                                                   
                                                                                                                    
        `uvm_component_utils_begin(ecg_fpga_top_env)                                                                 
        `uvm_field_object (refm, UVM_DEFAULT | UVM_REFERENCE)                                                       
        `uvm_field_object (ecg_fpga_top_virtual_sqr, UVM_DEFAULT | UVM_REFERENCE)                                    
        `uvm_field_object (ecg_fpga_top_cfg        , UVM_DEFAULT)                                                    
        `uvm_component_utils_end                                                                                    
                                                                                                                    
        function new (string name = "ecg_fpga_top_env", uvm_component parent = null);                              
            super.new(name, parent);                                                                                
        endfunction                                                                                                 
                                                                                                                    
        extern virtual function void build_phase(uvm_phase phase);                                                  
        extern virtual function void connect_phase(uvm_phase phase);                                                
        extern virtual task          run_phase(uvm_phase phase);                                                    
                                                                                                                    
    endclass                                                                                                        
                                                                                                                    
    function void ecg_fpga_top_env::build_phase(uvm_phase phase);                                                    
        super.build_phase(phase);                                                                                   
        ecg_fpga_top_cfg = ecg_fpga_top_config::type_id::create("ecg_fpga_top_cfg", this);                           
                                                                                                                    

        ecg_fpga_top_cfg.gmem0_cfg.set_default();
        ecg_fpga_top_cfg.gmem0_cfg.drv_type = axi_pkg::SLAVE;
        ecg_fpga_top_cfg.gmem0_cfg.reset_level = axi_pkg::RESET_LEVEL_LOW;
        ecg_fpga_top_cfg.gmem0_cfg.write_latency_mode = TRANSACTION_FIRST;
        ecg_fpga_top_cfg.gmem0_cfg.read_latency_mode = TRANSACTION_FIRST;
        uvm_config_db#(axi_pkg::axi_cfg)::set(this, "axi_master_gmem0*", "cfg", ecg_fpga_top_cfg.gmem0_cfg);
        axi_master_gmem0 = axi_pkg::axi_env#(64,4,8,3,1)::type_id::create("axi_master_gmem0", this);

        ecg_fpga_top_cfg.gmem1_cfg.set_default();
        ecg_fpga_top_cfg.gmem1_cfg.drv_type = axi_pkg::SLAVE;
        ecg_fpga_top_cfg.gmem1_cfg.reset_level = axi_pkg::RESET_LEVEL_LOW;
        ecg_fpga_top_cfg.gmem1_cfg.write_latency_mode = TRANSACTION_FIRST;
        ecg_fpga_top_cfg.gmem1_cfg.read_latency_mode = TRANSACTION_FIRST;
        uvm_config_db#(axi_pkg::axi_cfg)::set(this, "axi_master_gmem1*", "cfg", ecg_fpga_top_cfg.gmem1_cfg);
        axi_master_gmem1 = axi_pkg::axi_env#(64,4,8,3,1)::type_id::create("axi_master_gmem1", this);

        ecg_fpga_top_cfg.gmem2_cfg.set_default();
        ecg_fpga_top_cfg.gmem2_cfg.drv_type = axi_pkg::SLAVE;
        ecg_fpga_top_cfg.gmem2_cfg.reset_level = axi_pkg::RESET_LEVEL_LOW;
        ecg_fpga_top_cfg.gmem2_cfg.write_latency_mode = TRANSACTION_FIRST;
        ecg_fpga_top_cfg.gmem2_cfg.read_latency_mode = TRANSACTION_FIRST;
        uvm_config_db#(axi_pkg::axi_cfg)::set(this, "axi_master_gmem2*", "cfg", ecg_fpga_top_cfg.gmem2_cfg);
        axi_master_gmem2 = axi_pkg::axi_env#(64,4,8,3,1)::type_id::create("axi_master_gmem2", this);

        ecg_fpga_top_cfg.CTRL_cfg.set_default();
        ecg_fpga_top_cfg.CTRL_cfg.drv_type = axi_pkg::MASTER;
        ecg_fpga_top_cfg.CTRL_cfg.reset_level = axi_pkg::RESET_LEVEL_LOW;
        uvm_config_db#(axi_pkg::axi_cfg)::set(this, "axi_lite_CTRL*", "cfg", ecg_fpga_top_cfg.CTRL_cfg);
        axi_lite_CTRL = axi_pkg::axi_env#(6,4,4,3,1)::type_id::create("axi_lite_CTRL", this);



        refm = ecg_fpga_top_reference_model::type_id::create("refm", this);


        uvm_config_db#(ecg_fpga_top_reference_model)::set(this, "*", "refm", refm);


        `uvm_info(this.get_full_name(), "set reference model by uvm_config_db", UVM_LOW)


        subsys_mon = ecg_fpga_top_subsystem_monitor::type_id::create("subsys_mon", this);


        ecg_fpga_top_virtual_sqr = ecg_fpga_top_virtual_sequencer::type_id::create("ecg_fpga_top_virtual_sqr", this);
        `uvm_info(this.get_full_name(), "build_phase done", UVM_LOW)
    endfunction


    function void ecg_fpga_top_env::connect_phase(uvm_phase phase);
        super.connect_phase(phase);


        if(ecg_fpga_top_cfg.gmem0_cfg.drv_type==axi_pkg::MASTER ||ecg_fpga_top_cfg.gmem0_cfg.drv_type==axi_pkg::SLAVE)
            ecg_fpga_top_virtual_sqr.gmem0_sqr = axi_master_gmem0.vsqr;
        axi_master_gmem0.item_wtr_port.connect(subsys_mon.gmem0_wtr_imp);
        axi_master_gmem0.item_rtr_port.connect(subsys_mon.gmem0_rtr_imp);
        uvm_callbacks#(axi_pkg::axi_state, axi_pkg::axi_state_cbs)::add(axi_master_gmem0.state, refm.axi_memaccess_cb_gmem0);
        if(ecg_fpga_top_cfg.gmem1_cfg.drv_type==axi_pkg::MASTER ||ecg_fpga_top_cfg.gmem1_cfg.drv_type==axi_pkg::SLAVE)
            ecg_fpga_top_virtual_sqr.gmem1_sqr = axi_master_gmem1.vsqr;
        axi_master_gmem1.item_wtr_port.connect(subsys_mon.gmem1_wtr_imp);
        axi_master_gmem1.item_rtr_port.connect(subsys_mon.gmem1_rtr_imp);
        uvm_callbacks#(axi_pkg::axi_state, axi_pkg::axi_state_cbs)::add(axi_master_gmem1.state, refm.axi_memaccess_cb_gmem1);
        if(ecg_fpga_top_cfg.gmem2_cfg.drv_type==axi_pkg::MASTER ||ecg_fpga_top_cfg.gmem2_cfg.drv_type==axi_pkg::SLAVE)
            ecg_fpga_top_virtual_sqr.gmem2_sqr = axi_master_gmem2.vsqr;
        axi_master_gmem2.item_wtr_port.connect(subsys_mon.gmem2_wtr_imp);
        axi_master_gmem2.item_rtr_port.connect(subsys_mon.gmem2_rtr_imp);
        uvm_callbacks#(axi_pkg::axi_state, axi_pkg::axi_state_cbs)::add(axi_master_gmem2.state, refm.axi_memaccess_cb_gmem2);
        if(ecg_fpga_top_cfg.CTRL_cfg.drv_type==axi_pkg::MASTER ||ecg_fpga_top_cfg.CTRL_cfg.drv_type==axi_pkg::SLAVE)
            ecg_fpga_top_virtual_sqr.CTRL_sqr = axi_lite_CTRL.vsqr;
        axi_lite_CTRL.item_wtr_port.connect(subsys_mon.CTRL_wtr_imp);
        axi_lite_CTRL.item_rtr_port.connect(subsys_mon.CTRL_rtr_imp);
        refm.ecg_fpga_top_cfg = ecg_fpga_top_cfg;
        `uvm_info(this.get_full_name(), "connect phase done", UVM_LOW)
    endfunction


    task ecg_fpga_top_env::run_phase(uvm_phase phase);
        `uvm_info(this.get_full_name(), "ecg_fpga_top_env is running", UVM_LOW)
    endtask


`endif
