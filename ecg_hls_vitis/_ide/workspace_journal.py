# 2026-07-02T12:50:48.053298700
import vitis

client = vitis.create_client()
client.set_workspace(path="ecg_hls_vitis_clean_project_v6")

comp = client.create_hls_component(name = "ecg_fpga_top",cfg_file = ["hls_config.cfg"],template = "empty_hls_component")

comp = client.get_component(name="ecg_fpga_top")
comp.run(operation="C_SIMULATION")

comp.run(operation="SYNTHESIS")

comp.run(operation="CO_SIMULATION")

comp.run(operation="PACKAGE")

vitis.dispose()

