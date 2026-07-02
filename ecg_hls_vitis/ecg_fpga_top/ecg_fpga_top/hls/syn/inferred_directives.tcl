# Inferred from syn.compile.pipeline_loops=64
set_directive_pipeline ecg_fpga_top/VITIS_LOOP_137_1
# Inferred from performance & pipeline pragmas/directives
set_directive_array_partition ecg_fpga_top/beat_local -dim=1 -type=cyclic -factor=2 beat_local
set_directive_loop_flatten ecg_fpga_top/VITIS_LOOP_52_1
set_directive_array_partition ecg_fpga_top/main5_dense_kernel -dim=1 -type=cyclic -factor=41 main5_dense_kernel
set_directive_array_partition ecg_fpga_top/main5_class_output_kernel -dim=1 -type=cyclic -factor=12 main5_class_output_kernel
