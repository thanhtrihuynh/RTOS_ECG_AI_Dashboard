// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2025.2 (64-bit)
// Tool Version Limit: 2025.11
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2025 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
#ifndef XECG_FPGA_TOP_H
#define XECG_FPGA_TOP_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#ifndef __linux__
#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xil_io.h"
#else
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#endif
#include "xecg_fpga_top_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
#else
typedef struct {
#ifdef SDT
    char *Name;
#else
    u16 DeviceId;
#endif
    u64 Ctrl_BaseAddress;
} XEcg_fpga_top_Config;
#endif

typedef struct {
    u64 Ctrl_BaseAddress;
    u32 IsReady;
} XEcg_fpga_top;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XEcg_fpga_top_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XEcg_fpga_top_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XEcg_fpga_top_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XEcg_fpga_top_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1
#endif

/************************** Function Prototypes *****************************/
#ifndef __linux__
#ifdef SDT
int XEcg_fpga_top_Initialize(XEcg_fpga_top *InstancePtr, UINTPTR BaseAddress);
XEcg_fpga_top_Config* XEcg_fpga_top_LookupConfig(UINTPTR BaseAddress);
#else
int XEcg_fpga_top_Initialize(XEcg_fpga_top *InstancePtr, u16 DeviceId);
XEcg_fpga_top_Config* XEcg_fpga_top_LookupConfig(u16 DeviceId);
#endif
int XEcg_fpga_top_CfgInitialize(XEcg_fpga_top *InstancePtr, XEcg_fpga_top_Config *ConfigPtr);
#else
int XEcg_fpga_top_Initialize(XEcg_fpga_top *InstancePtr, const char* InstanceName);
int XEcg_fpga_top_Release(XEcg_fpga_top *InstancePtr);
#endif

void XEcg_fpga_top_Start(XEcg_fpga_top *InstancePtr);
u32 XEcg_fpga_top_IsDone(XEcg_fpga_top *InstancePtr);
u32 XEcg_fpga_top_IsIdle(XEcg_fpga_top *InstancePtr);
u32 XEcg_fpga_top_IsReady(XEcg_fpga_top *InstancePtr);
void XEcg_fpga_top_EnableAutoRestart(XEcg_fpga_top *InstancePtr);
void XEcg_fpga_top_DisableAutoRestart(XEcg_fpga_top *InstancePtr);

void XEcg_fpga_top_Set_beat_in_q12(XEcg_fpga_top *InstancePtr, u64 Data);
u64 XEcg_fpga_top_Get_beat_in_q12(XEcg_fpga_top *InstancePtr);
void XEcg_fpga_top_Set_pred_class(XEcg_fpga_top *InstancePtr, u64 Data);
u64 XEcg_fpga_top_Get_pred_class(XEcg_fpga_top *InstancePtr);
void XEcg_fpga_top_Set_score5_q12(XEcg_fpga_top *InstancePtr, u64 Data);
u64 XEcg_fpga_top_Get_score5_q12(XEcg_fpga_top *InstancePtr);

void XEcg_fpga_top_InterruptGlobalEnable(XEcg_fpga_top *InstancePtr);
void XEcg_fpga_top_InterruptGlobalDisable(XEcg_fpga_top *InstancePtr);
void XEcg_fpga_top_InterruptEnable(XEcg_fpga_top *InstancePtr, u32 Mask);
void XEcg_fpga_top_InterruptDisable(XEcg_fpga_top *InstancePtr, u32 Mask);
void XEcg_fpga_top_InterruptClear(XEcg_fpga_top *InstancePtr, u32 Mask);
u32 XEcg_fpga_top_InterruptGetEnabled(XEcg_fpga_top *InstancePtr);
u32 XEcg_fpga_top_InterruptGetStatus(XEcg_fpga_top *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
