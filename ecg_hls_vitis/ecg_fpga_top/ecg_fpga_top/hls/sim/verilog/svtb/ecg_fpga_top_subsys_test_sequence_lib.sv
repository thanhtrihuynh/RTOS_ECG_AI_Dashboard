//==============================================================
//Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2025.2 (64-bit)
//Tool Version Limit: 2025.11
//Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
//Copyright 2022-2025 Advanced Micro Devices, Inc. All Rights Reserved.
//
//==============================================================
`ifndef ECG_FPGA_TOP_SUBSYS_TEST_SEQUENCE_LIB__SV                                              
    `define ECG_FPGA_TOP_SUBSYS_TEST_SEQUENCE_LIB__SV                                          
                                                                                                    
                                                                                                    
    `include "uvm_macros.svh"                                                                     
                                                                                                    
    class ecg_fpga_top_subsys_test_sequence_lib extends uvm_sequence;                                
                                                                                                    
        function new (string name = "ecg_fpga_top_subsys_test_sequence_lib");                      
            super.new(name);                                                                        
            `uvm_info(this.get_full_name(), "new is called", UVM_LOW)                             
        endfunction                                                                                 
                                                                                                    
        `uvm_object_utils(ecg_fpga_top_subsys_test_sequence_lib)                                     
        `uvm_declare_p_sequencer(ecg_fpga_top_virtual_sequencer)                                     
                                                                                                    
        virtual task body();                                                                        
            uvm_phase starting_phase;                                                               
            virtual interface misc_interface misc_if;                                               
            ecg_fpga_top_reference_model refm;                                                       
                                                                                                    
            axi_pkg::axi_slave_sequence#(64,4,8,3,1) axi_slave_gmem0_seq;
            axi_pkg::axi_slave_sequence#(64,4,8,3,1) axi_slave_gmem1_seq;
            axi_pkg::axi_slave_sequence#(64,4,8,3,1) axi_slave_gmem2_seq;
            axi_pkg::axi_busdatas_master_sequence#(6, 32) axi_master_wr_CTRL_seq;
            axi_pkg::axi_busdatas_master_sequence#(6, 32) axi_master_poll_CTRL_seq;

            if (!uvm_config_db#(ecg_fpga_top_reference_model)::get(p_sequencer,"", "refm", refm))
                `uvm_fatal(this.get_full_name(), "No reference model")
            `uvm_info(this.get_full_name(), "get reference model by uvm_config_db", UVM_LOW)

            `uvm_info(this.get_full_name(), "body is called", UVM_LOW)
            starting_phase = this.get_starting_phase();
            if (starting_phase != null) begin
                `uvm_info(this.get_full_name(), "starting_phase not null", UVM_LOW)
                starting_phase.raise_objection(this);
            end
            else
                `uvm_info(this.get_full_name(), "starting_phase null" , UVM_LOW)

            misc_if = refm.misc_if;


            //phase_done.set_drain_time(this, 0ns);
            wait(refm.misc_if.reset === 1);
            ->refm.misc_if.initialed_evt;

            fork
                begin
                    fork
                        begin //axi slave sequence. loop delays
                            `uvm_create_on(axi_slave_gmem0_seq, p_sequencer.gmem0_sqr);
                            axi_slave_gmem0_seq.misc_if = refm.misc_if;
                            axi_slave_gmem0_seq.ap_done    = refm.ap_done_for_nexttrans   ;
                            axi_slave_gmem0_seq.ap_ready   = refm.ap_ready_for_nexttrans  ;
                            axi_slave_gmem0_seq.finish     = refm.finish ;
                            axi_slave_gmem0_seq.isusr_delay = axi_pkg::NO_DELAY;
                            `uvm_send(axi_slave_gmem0_seq);
                        end
                        begin //axi slave sequence. loop delays
                            `uvm_create_on(axi_slave_gmem1_seq, p_sequencer.gmem1_sqr);
                            axi_slave_gmem1_seq.misc_if = refm.misc_if;
                            axi_slave_gmem1_seq.ap_done    = refm.ap_done_for_nexttrans   ;
                            axi_slave_gmem1_seq.ap_ready   = refm.ap_ready_for_nexttrans  ;
                            axi_slave_gmem1_seq.finish     = refm.finish ;
                            axi_slave_gmem1_seq.isusr_delay = axi_pkg::NO_DELAY;
                            `uvm_send(axi_slave_gmem1_seq);
                        end
                        begin //axi slave sequence. loop delays
                            `uvm_create_on(axi_slave_gmem2_seq, p_sequencer.gmem2_sqr);
                            axi_slave_gmem2_seq.misc_if = refm.misc_if;
                            axi_slave_gmem2_seq.ap_done    = refm.ap_done_for_nexttrans   ;
                            axi_slave_gmem2_seq.ap_ready   = refm.ap_ready_for_nexttrans  ;
                            axi_slave_gmem2_seq.finish     = refm.finish ;
                            axi_slave_gmem2_seq.isusr_delay = axi_pkg::NO_DELAY;
                            `uvm_send(axi_slave_gmem2_seq);
                        end
                        begin
                            int CTRL_page_idx_bak;
                            `uvm_create_on(axi_master_wr_CTRL_seq, p_sequencer.CTRL_sqr);
                            axi_master_wr_CTRL_seq.misc_if = refm.misc_if;
                            axi_master_wr_CTRL_seq.ap_done    = refm.ap_done_for_nexttrans   ;
                            axi_master_wr_CTRL_seq.ap_ready   = refm.ap_ready_for_nexttrans  ;
                            axi_master_wr_CTRL_seq.finish     = refm.finish ;
                            axi_master_wr_CTRL_seq.isusr_delay = axi_pkg::NO_DELAY;
                            for(int i=0; i<1; i++) begin
                                logic[63:0] data64bit_beat_in_q12[$];
                                logic[32-1:0] databusbit_beat_in_q12[$];
                                logic[63:0] data64bit_pred_class[$];
                                logic[32-1:0] databusbit_pred_class[$];
                                logic[63:0] data64bit_score5_q12[$];
                                logic[32-1:0] databusbit_score5_q12[$];
                                data64bit_beat_in_q12.delete(); databusbit_beat_in_q12.delete();
                                axi_master_wr_CTRL_seq.StableAxiliteNoUpdate=0;
                                for(int j=0; j < (64+32-1)/32; j++) begin
                                    data64bit_beat_in_q12.push_back( ((refm.mem_blk_pages_gmem0.maxi_bundlevar_offset["beat_in_q12"]+refm.mem_blk_pages_gmem0.page_ofst[refm.mem_blk_pages_gmem0.rd_page_idx])>>(j*32)) & (2**32-1) );
                                end
                                foreach(data64bit_beat_in_q12[s]) databusbit_beat_in_q12[s]=data64bit_beat_in_q12[s][32-1:0];
                                axi_master_wr_CTRL_seq.StableAxiliteNoUpdate=1;
                                axi_master_wr_CTRL_seq.datamerge_inavg(databusbit_beat_in_q12, 0, 16, 1);
                                data64bit_pred_class.delete(); databusbit_pred_class.delete();
                                axi_master_wr_CTRL_seq.StableAxiliteNoUpdate=0;
                                for(int j=0; j < (64+32-1)/32; j++) begin
                                    data64bit_pred_class.push_back( ((refm.mem_blk_pages_gmem1.maxi_bundlevar_offset["pred_class"]+refm.mem_blk_pages_gmem1.page_ofst[refm.mem_blk_pages_gmem1.rd_page_idx])>>(j*32)) & (2**32-1) );
                                end
                                foreach(data64bit_pred_class[s]) databusbit_pred_class[s]=data64bit_pred_class[s][32-1:0];
                                axi_master_wr_CTRL_seq.StableAxiliteNoUpdate=1;
                                axi_master_wr_CTRL_seq.datamerge_inavg(databusbit_pred_class, 0, 28, 1);
                                data64bit_score5_q12.delete(); databusbit_score5_q12.delete();
                                axi_master_wr_CTRL_seq.StableAxiliteNoUpdate=0;
                                for(int j=0; j < (64+32-1)/32; j++) begin
                                    data64bit_score5_q12.push_back( ((refm.mem_blk_pages_gmem2.maxi_bundlevar_offset["score5_q12"]+refm.mem_blk_pages_gmem2.page_ofst[refm.mem_blk_pages_gmem2.rd_page_idx])>>(j*32)) & (2**32-1) );
                                end
                                foreach(data64bit_score5_q12[s]) databusbit_score5_q12[s]=data64bit_score5_q12[s][32-1:0];
                                axi_master_wr_CTRL_seq.StableAxiliteNoUpdate=1;
                                axi_master_wr_CTRL_seq.datamerge_inavg(databusbit_score5_q12, 0, 40, 1);
                                `uvm_send(axi_master_wr_CTRL_seq);
                                refm.write_data_finish_CTRL = 1;
                                `uvm_info("CTRL data writting thread", $sformatf("%0dth(total 1): waiting for all write data finish event",i), UVM_LOW)
                                wait(refm.allaxilite_write_data_finish.triggered);
                                refm.write_data_finish_CTRL = 0;
                                fork
                                    begin // configure start to enable DUT
                                        axi_master_wr_CTRL_seq.wr_addr_data.push_back( (1<<0)+(0<<32) );
                                        `uvm_info("CTRL start dut by axilite", $sformatf("%0dth(total 1): begin to set start bit",i), UVM_LOW)
                                        `uvm_send(axi_master_wr_CTRL_seq);
                                    end
                                    begin
                                        `uvm_info("CTRL wait for ap_ready for next trans", $sformatf("%0dth(total 1): begin to wait",i), UVM_LOW)
                                        wait(refm.dut2tb_ap_ready.triggered);
                                        wait(refm.ap_done_for_nexttrans.triggered);
                                        #0.01; //make sure mem incr_rd_page_idx is called first
                                    end
                                join
                            end
                        end
                        begin
                            for(int j=0; j<1; j=j+refm.ap_done_cnt) begin
                                wait(misc_if.dut2tb_ap_done_kernel == 1);
                                `uvm_info("test finish control", $sformatf("ap_done of kernel is triggered"), UVM_LOW)
                                @(posedge misc_if.clock);
                                fork
                                    forever begin
                                        `uvm_create_on(axi_master_poll_CTRL_seq, p_sequencer.CTRL_sqr);
                                        axi_master_poll_CTRL_seq.isusr_delay = axi_pkg::NO_DELAY;
                                        axi_master_poll_CTRL_seq.misc_if = refm.misc_if;
                                        axi_master_poll_CTRL_seq.rd_addr.push_back(0);
                                        `uvm_send(axi_master_poll_CTRL_seq)
                                        repeat(2) @(posedge misc_if.clock);
                                    end
                                    begin
                                        `uvm_info("test finish control", $sformatf("%0dth(total 1) ap_done_for_nexttrans begin to wait",j), UVM_LOW)
                                        @refm.dut2tb_ap_done;
                                    end
                                join_any
                                disable fork;
                                wait(refm.ap_ready_for_nexttrans.triggered);
                            end
                        end
                    join
                end

                begin
                    for(int j=0; j<1; j=j+refm.ap_done_cnt) @refm.ap_done_for_nexttrans;
                    `uvm_info(this.get_full_name(), "autotb finished", UVM_LOW)
                    -> refm.finish;
                    refm.misc_if.finished = 1;
                    @(posedge refm.misc_if.clock);
                    refm.misc_if.finished = 0;
                    @(posedge refm.misc_if.clock);
                    -> refm.misc_if.finished_evt;
                end
            join_any
            repeat(5) @(posedge refm.misc_if.clock); //5 cycles delay for finish stuff. 5 is haphazard value

            p_sequencer.gmem0_sqr.stop_sequences();
            p_sequencer.gmem1_sqr.stop_sequences();
            p_sequencer.gmem2_sqr.stop_sequences();
            p_sequencer.CTRL_sqr.stop_sequences();
            disable fork;
                                                                                                    
            starting_phase.drop_objection(this);                                                    
                                                                                                    
        endtask                                                                                     
    endclass                                                                                        
                                                                                                    
`endif                                                                                              
