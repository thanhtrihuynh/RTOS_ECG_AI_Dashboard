// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2025.2 (64-bit)
// Tool Version Limit: 2025.11
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2025 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#ifdef SDT
#include "xparameters.h"
#endif
#include "xecg_fpga_top.h"

extern XEcg_fpga_top_Config XEcg_fpga_top_ConfigTable[];

#ifdef SDT
XEcg_fpga_top_Config *XEcg_fpga_top_LookupConfig(UINTPTR BaseAddress) {
	XEcg_fpga_top_Config *ConfigPtr = NULL;

	int Index;

	for (Index = (u32)0x0; XEcg_fpga_top_ConfigTable[Index].Name != NULL; Index++) {
		if (!BaseAddress || XEcg_fpga_top_ConfigTable[Index].Ctrl_BaseAddress == BaseAddress) {
			ConfigPtr = &XEcg_fpga_top_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XEcg_fpga_top_Initialize(XEcg_fpga_top *InstancePtr, UINTPTR BaseAddress) {
	XEcg_fpga_top_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XEcg_fpga_top_LookupConfig(BaseAddress);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XEcg_fpga_top_CfgInitialize(InstancePtr, ConfigPtr);
}
#else
XEcg_fpga_top_Config *XEcg_fpga_top_LookupConfig(u16 DeviceId) {
	XEcg_fpga_top_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XECG_FPGA_TOP_NUM_INSTANCES; Index++) {
		if (XEcg_fpga_top_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XEcg_fpga_top_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XEcg_fpga_top_Initialize(XEcg_fpga_top *InstancePtr, u16 DeviceId) {
	XEcg_fpga_top_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XEcg_fpga_top_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XEcg_fpga_top_CfgInitialize(InstancePtr, ConfigPtr);
}
#endif

#endif

