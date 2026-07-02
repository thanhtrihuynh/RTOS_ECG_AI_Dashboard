@echo off
cd /d %~dp0
vitis-run.bat --mode hls --csynth --config hls_config.cfg --work_dir work\ecg_fpga_top
pause
