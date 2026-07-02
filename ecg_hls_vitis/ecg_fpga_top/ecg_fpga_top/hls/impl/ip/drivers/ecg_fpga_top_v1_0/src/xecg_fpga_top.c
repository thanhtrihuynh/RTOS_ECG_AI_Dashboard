// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2025.2 (64-bit)
// Tool Version Limit: 2025.11
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2025 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
/***************************** Include Files *********************************/
#include "xecg_fpga_top.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XEcg_fpga_top_CfgInitialize(XEcg_fpga_top *InstancePtr, XEcg_fpga_top_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Ctrl_BaseAddress = ConfigPtr->Ctrl_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XEcg_fpga_top_Start(XEcg_fpga_top *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XEcg_fpga_top_ReadReg(InstancePtr->Ctrl_BaseAddress, XECG_FPGA_TOP_CTRL_ADDR_AP_CTRL) & 0x80;
    XEcg_fpga_top_WriteReg(InstancePtr->Ctrl_BaseAddress, XECG_FPGA_TOP_CTRL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XEcg_fpga_top_IsDone(XEcg_fpga_top *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XEcg_fpga_top_ReadReg(InstancePtr->Ctrl_BaseAddress, XECG_FPGA_TOP_CTRL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XEcg_fpga_top_IsIdle(XEcg_fpga_top *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XEcg_fpga_top_ReadReg(InstancePtr->Ctrl_BaseAddress, XECG_FPGA_TOP_CTRL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XEcg_fpga_top_IsReady(XEcg_fpga_top *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XEcg_fpga_top_ReadReg(InstancePtr->Ctrl_BaseAddress, XECG_FPGA_TOP_CTRL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XEcg_fpga_top_EnableAutoRestart(XEcg_fpga_top *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XEcg_fpga_top_WriteReg(InstancePtr->Ctrl_BaseAddress, XECG_FPGA_TOP_CTRL_ADDR_AP_CTRL, 0x80);
}

void XEcg_fpga_top_DisableAutoRestart(XEcg_fpga_top *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XEcg_fpga_top_WriteReg(InstancePtr->Ctrl_BaseAddress, XECG_FPGA_TOP_CTRL_ADDR_AP_CTRL, 0);
}

void XEcg_fpga_top_Set_beat_in_q12(XEcg_fpga_top *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XEcg_fpga_top_WriteReg(InstancePtr->Ctrl_BaseAddress, XECG_FPGA_TOP_CTRL_ADDR_BEAT_IN_Q12_DATA, (u32)(Data));
    XEcg_fpga_top_WriteReg(InstancePtr->Ctrl_BaseAddress, XECG_FPGA_TOP_CTRL_ADDR_BEAT_IN_Q12_DATA + 4, (u32)(Data >> 32));
}

u64 XEcg_fpga_top_Get_beat_in_q12(XEcg_fpga_top *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XEcg_fpga_top_ReadReg(InstancePtr->Ctrl_BaseAddress, XECG_FPGA_TOP_CTRL_ADDR_BEAT_IN_Q12_DATA);
    Data += (u64)XEcg_fpga_top_ReadReg(InstancePtr->Ctrl_BaseAddress, XECG_FPGA_TOP_CTRL_ADDR_BEAT_IN_Q12_DATA + 4) << 32;
    return Data;
}

void XEcg_fpga_top_Set_pred_class(XEcg_fpga_top *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XEcg_fpga_top_WriteReg(InstancePtr->Ctrl_BaseAddress, XECG_FPGA_TOP_CTRL_ADDR_PRED_CLASS_DATA, (u32)(Data));
    XEcg_fpga_top_WriteReg(InstancePtr->Ctrl_BaseAddress, XECG_FPGA_TOP_CTRL_ADDR_PRED_CLASS_DATA + 4, (u32)(Data >> 32));
}

u64 XEcg_fpga_top_Get_pred_class(XEcg_fpga_top *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XEcg_fpga_top_ReadReg(InstancePtr->Ctrl_BaseAddress, XECG_FPGA_TOP_CTRL_ADDR_PRED_CLASS_DATA);
    Data += (u64)XEcg_fpga_top_ReadReg(InstancePtr->Ctrl_BaseAddress, XECG_FPGA_TOP_CTRL_ADDR_PRED_CLASS_DATA + 4) << 32;
    return Data;
}

void XEcg_fpga_top_Set_score5_q12(XEcg_fpga_top *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XEcg_fpga_top_WriteReg(InstancePtr->Ctrl_BaseAddress, XECG_FPGA_TOP_CTRL_ADDR_SCORE5_Q12_DATA, (u32)(Data));
    XEcg_fpga_top_WriteReg(InstancePtr->Ctrl_BaseAddress, XECG_FPGA_TOP_CTRL_ADDR_SCORE5_Q12_DATA + 4, (u32)(Data >> 32));
}

u64 XEcg_fpga_top_Get_score5_q12(XEcg_fpga_top *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XEcg_fpga_top_ReadReg(InstancePtr->Ctrl_BaseAddress, XECG_FPGA_TOP_CTRL_ADDR_SCORE5_Q12_DATA);
    Data += (u64)XEcg_fpga_top_ReadReg(InstancePtr->Ctrl_BaseAddress, XECG_FPGA_TOP_CTRL_ADDR_SCORE5_Q12_DATA + 4) << 32;
    return Data;
}

void XEcg_fpga_top_InterruptGlobalEnable(XEcg_fpga_top *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XEcg_fpga_top_WriteReg(InstancePtr->Ctrl_BaseAddress, XECG_FPGA_TOP_CTRL_ADDR_GIE, 1);
}

void XEcg_fpga_top_InterruptGlobalDisable(XEcg_fpga_top *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XEcg_fpga_top_WriteReg(InstancePtr->Ctrl_BaseAddress, XECG_FPGA_TOP_CTRL_ADDR_GIE, 0);
}

void XEcg_fpga_top_InterruptEnable(XEcg_fpga_top *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XEcg_fpga_top_ReadReg(InstancePtr->Ctrl_BaseAddress, XECG_FPGA_TOP_CTRL_ADDR_IER);
    XEcg_fpga_top_WriteReg(InstancePtr->Ctrl_BaseAddress, XECG_FPGA_TOP_CTRL_ADDR_IER, Register | Mask);
}

void XEcg_fpga_top_InterruptDisable(XEcg_fpga_top *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XEcg_fpga_top_ReadReg(InstancePtr->Ctrl_BaseAddress, XECG_FPGA_TOP_CTRL_ADDR_IER);
    XEcg_fpga_top_WriteReg(InstancePtr->Ctrl_BaseAddress, XECG_FPGA_TOP_CTRL_ADDR_IER, Register & (~Mask));
}

void XEcg_fpga_top_InterruptClear(XEcg_fpga_top *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XEcg_fpga_top_WriteReg(InstancePtr->Ctrl_BaseAddress, XECG_FPGA_TOP_CTRL_ADDR_ISR, Mask);
}

u32 XEcg_fpga_top_InterruptGetEnabled(XEcg_fpga_top *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XEcg_fpga_top_ReadReg(InstancePtr->Ctrl_BaseAddress, XECG_FPGA_TOP_CTRL_ADDR_IER);
}

u32 XEcg_fpga_top_InterruptGetStatus(XEcg_fpga_top *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XEcg_fpga_top_ReadReg(InstancePtr->Ctrl_BaseAddress, XECG_FPGA_TOP_CTRL_ADDR_ISR);
}

