/* Copyright (c) 2018-2019 Sigmastar Technology Corp.
 All rights reserved.

 Unless otherwise stipulated in writing, any and all information contained
herein regardless in any format shall remain the sole proprietary of
Sigmastar Technology Corp. and be kept in strict confidence
(Sigmastar Confidential Information) by the recipient.
Any unauthorized act including without limitation unauthorized disclosure,
copying, use, reproduction, sale, distribution, modification, disassembling,
reverse engineering and compiling of the contents of Sigmastar Confidential
Information is unlawful and strictly prohibited. Sigmastar hereby reserves the
rights to any and all damages, losses, costs and expenses resulting therefrom.
*/


#define _HAL_DISP_SCALER_E_C_

#ifdef DISP_OS_TYPE_LINUX_KERNEL
#include "cam_os_wrapper.h"
#endif

#include "drv_disp_os.h"
#include "hal_disp_common.h"
#include "disp_debug.h"
#include "hal_disp_util.h"
#include "hal_disp_reg.h"
#include "hal_disp_chip.h"
#include "hal_disp_st.h"
#include "hal_disp_vga_timing_tbl.h"
//-------------------------------------------------------------------------------------------------
//  Include Files
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Defines & Macro
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  structure
//-------------------------------------------------------------------------------------------------



//-------------------------------------------------------------------------------------------------
//  Variable
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Local Functions
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Global Functions
//-------------------------------------------------------------------------------------------------
void HalDispOp2Init(void)
{
    W2BYTE(REG_DISP_TOP_OP2_10_L, 0x80D0);
}

void HalDispSetSwReste(u8 u8Val)
{
    W2BYTEMSK(REG_DISP_TOP_00_L, ((u16)u8Val) << 8, 0xFF00);
}

void HalDispSetFifoRest(u8 u8Val)
{
    W2BYTEMSK(REG_DISP_TOP_30_L, u8Val ? 0x0001 : 0x0000, 0x0001);
}

void HalDispSetMaceSrc(bool bExtVideo)
{
    W2BYTEMSK(REG_DISP_TOP_07_L, bExtVideo ? 1 : 0, 0x0001);
}

void HalDispSetPatGenMd(u8 u8Val)
{
    W2BYTEMSK(REG_DISP_TOP_07_L, u8Val << 1,  0x000E);
}

void HalDispSetTgenHtt(u16 u16Val)
{
    W2BYTEMSK(REG_DISP_TOP_OP2_11_L, u16Val, 0x1FFF);
}

void HalDispSetTgenVtt(u16 u16Val)
{
    W2BYTEMSK(REG_DISP_TOP_OP2_12_L, u16Val, 0x1FFF);
}

void HalDispSetTgenHsyncSt(u16 u16Val)
{
    W2BYTEMSK(REG_DISP_TOP_OP2_13_L, u16Val, 0x1FFF);
}

void HalDispSetTgenHsyncEnd(u16 u16Val)
{
    W2BYTEMSK(REG_DISP_TOP_OP2_14_L, u16Val, 0x1FFF);
}

void HalDispSetTgenVsyncSt(u16 u16Val)
{
    W2BYTEMSK(REG_DISP_TOP_OP2_15_L, u16Val, 0x1FFF);
}

void HalDispSetTgenVsyncEnd(u16 u16Val)
{
    W2BYTEMSK(REG_DISP_TOP_OP2_16_L, u16Val, 0x1FFF);
}

void HalDispSetTgenHfdeSt(u16 u16Val)
{
    W2BYTEMSK(REG_DISP_TOP_OP2_17_L, u16Val, 0x1FFF);
}

void HalDispSetTgenHfdeEnd(u16 u16Val)
{
    W2BYTEMSK(REG_DISP_TOP_OP2_18_L, u16Val, 0x1FFF);
}

void HalDispSetTgenVfdeSt(u16 u16Val)
{
    W2BYTEMSK(REG_DISP_TOP_OP2_19_L, u16Val, 0x1FFF);
}

void HalDispSetTgenVfdeEnd(u16 u16Val)
{
    W2BYTEMSK(REG_DISP_TOP_OP2_1A_L, u16Val, 0x1FFF);
}

void HalDispSetTgenHdeSt(u16 u16Val)
{
    W2BYTEMSK(REG_DISP_TOP_OP2_1C_L, u16Val, 0x1FFF);
}

void HalDispSetTgenHdeEnd(u16 u16Val)
{
    W2BYTEMSK(REG_DISP_TOP_OP2_1D_L, u16Val, 0x1FFF);
}

void HalDispSetTgenVdeSt(u16 u16Val)
{
    W2BYTEMSK(REG_DISP_TOP_OP2_1E_L, u16Val, 0x1FFF);
}

void HalDispSetTgenVdeEnd(u16 u16Val)
{
    W2BYTEMSK(REG_DISP_TOP_OP2_1F_L, u16Val, 0x1FFF);
}

void HalDispSetTgenDacHsyncSt(u16 u16Val)
{
    W2BYTEMSK(REG_DISP_TOP_OP2_23_L, u16Val, 0x1FFF);
}

void HalDispSetTgenDacHsyncEnd(u16 u16Val)
{
    W2BYTEMSK(REG_DISP_TOP_OP2_24_L, u16Val, 0x1FFF);
}

void HalDispSetTgenDacHdeSt(u16 u16Val)
{
    W2BYTEMSK(REG_DISP_TOP_OP2_27_L, u16Val, 0x1FFF);
}

void HalDispSetTgenDacHdeEnd(u16 u16Val)
{
    W2BYTEMSK(REG_DISP_TOP_OP2_28_L, u16Val, 0x1FFF);
}

void HalDispSetTgenDacVdeSt(u16 u16Val)
{
    W2BYTEMSK(REG_DISP_TOP_OP2_29_L, u16Val, 0x1FFF);
}

void HalDispSetTgenDacVdeEnd(u16 u16Val)
{
    W2BYTEMSK(REG_DISP_TOP_OP2_2A_L, u16Val, 0x1FFF);
}


void HalDispSetFrameColor(u8 u8R, u8 u8G, u8 u8B)
{
    u16 u16Val;

    u16Val = (u8B & 0x1F) | (u16)(u8G & 0x1F) << 5 | (u16)(u8R & 0x1F) << 10;
    W2BYTEMSK(REG_DISP_TOP_OP2_1B_L, u16Val, 0x7FFF);
}

void HalDispSetFrameColorForce(u8 u8Val)
{
    W2BYTEMSK(REG_DISP_TOP_OP2_1B_L, u8Val ? 0x8000 : 0x0000, 0x8000);
}

void HalDispSetDispWinColor(u8 u8R, u8 u8G, u8 u8B)
{
    u16 u16Val;

    u16Val = (u8B & 0x1F) | (u16)(u8G & 0x1F) << 5 | (u16)(u8R & 0x1F) << 10;
    W2BYTEMSK(REG_DISP_TOP_OP2_20_L, u16Val, 0x7FFF);
}

void HalDispSetDispWinColorForce(bool bEn)
{
    W2BYTEMSK(REG_DISP_TOP_OP2_20_L, bEn ? 0x8000 : 0x0000, 0x8000);
}

void HalDispDumpRegTab(u8 *pData, u16 u16RegNum, u16 u16DataSize, u8 u8DataOffset)
{
    u16 i, j;

    for(i=0; i< u16RegNum; i++)
    {
        u32 u32Addr;
        u16 u16Mask, u16Value;

        j = i *  (REG_ADDR_SIZE+REG_MASK_SIZE+u16DataSize);

        u32Addr = ((u32)pData[j]) << 16 | ((u32)pData[j+1]) << 8 | pData[j+2];

        if(pData[j+2] & 0x01)
        {
            u16Mask  = (u16)(pData[j+3]) << 8;
            u16Value = (u16)(pData[j+4+u8DataOffset]) << 8;
        }
        else
        {
            u16Mask  = pData[j+3];
            u16Value = pData[j+4+u8DataOffset];
        }

        W2BYTEMSK(u32Addr, u16Value, u16Mask);
    }
}



