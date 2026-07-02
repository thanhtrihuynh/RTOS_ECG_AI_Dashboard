@echo off
cd /d %~dp0
vitis-run.bat --mode hls --csim --config hls_config.cfg --work_dir work\ecg_fpga_top
pause
