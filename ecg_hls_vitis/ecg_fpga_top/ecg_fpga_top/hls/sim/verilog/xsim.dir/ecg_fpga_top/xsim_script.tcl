xsim {ecg_fpga_top} -testplusarg UVM_VERBOSITY=UVM_NONE -testplusarg UVM_TESTNAME=ecg_fpga_top_test_lib -testplusarg UVM_TIMEOUT=20000000000000 -autoloadwcfg -tclbatch {ecg_fpga_top.tcl}
