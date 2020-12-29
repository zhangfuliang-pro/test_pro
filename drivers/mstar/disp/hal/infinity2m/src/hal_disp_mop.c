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


#define _HAL_DISP_MOP_C_

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
#include "hal_disp_mop.h"

//-------------------------------------------------------------------------------------------------
//  Include Files
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Defines & Macro
//-------------------------------------------------------------------------------------------------
#define HAL_DISP_MOP_MIU_BUS 4
//-------------------------------------------------------------------------------------------------
//  structure
//-------------------------------------------------------------------------------------------------



//-------------------------------------------------------------------------------------------------
//  Variable
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Local Functions
//-------------------------------------------------------------------------------------------------

u32 _HalDispMopgGwinRegBkMap(HalDispMopgGwinId_e eMopgId)
{
    u32 u32RegBk;

    switch(eMopgId)
    {
        case E_HAL_DISP_MOPG_ID_00:
        case E_HAL_DISP_MOPG_ID_01:
        case E_HAL_DISP_MOPG_ID_02:
        case E_HAL_DISP_MOPG_ID_03:
        case E_HAL_DISP_MOPG_ID_04:
        case E_HAL_DISP_MOPG_ID_05:
        case E_HAL_DISP_MOPG_ID_06:
        case E_HAL_DISP_MOPG_ID_07:
            u32RegBk = REG_DISP_MOPG_BK1_BASE;
            break;
        case E_HAL_DISP_MOPG_ID_08:
        case E_HAL_DISP_MOPG_ID_09:
        case E_HAL_DISP_MOPG_ID_10:
        case E_HAL_DISP_MOPG_ID_11:
        case E_HAL_DISP_MOPG_ID_12:
        case E_HAL_DISP_MOPG_ID_13:
        case E_HAL_DISP_MOPG_ID_14:
        case E_HAL_DISP_MOPG_ID_15:
            u32RegBk = REG_DISP_MOPG_BK2_BASE;
            break;
        default:
            DISP_ERR("[HALMOP]%s %d, Mopg ID %d not support\n", __FUNCTION__, __LINE__,eMopgId);
            u32RegBk = REG_DISP_MOPG_BK1_BASE;
            break;
    }
    return u32RegBk;
}

u32 _HalDispMopgGwinRegShiftMap(HalDispMopgGwinId_e eMopgId)
{
    u32 u32GeinRegShift;

    switch(eMopgId)
    {
        case E_HAL_DISP_MOPG_ID_00:
        case E_HAL_DISP_MOPG_ID_08:
            u32GeinRegShift = 0x00;
            break;
        case E_HAL_DISP_MOPG_ID_01:
        case E_HAL_DISP_MOPG_ID_09:
            u32GeinRegShift = 0x20;
            break;
        case E_HAL_DISP_MOPG_ID_02:
        case E_HAL_DISP_MOPG_ID_10:
            u32GeinRegShift = 0x40;
            break;
        case E_HAL_DISP_MOPG_ID_03:
        case E_HAL_DISP_MOPG_ID_11:
            u32GeinRegShift = 0x60;
            break;
        case E_HAL_DISP_MOPG_ID_04:
        case E_HAL_DISP_MOPG_ID_12:
            u32GeinRegShift = 0x80;
            break;
        case E_HAL_DISP_MOPG_ID_05:
        case E_HAL_DISP_MOPG_ID_13:
            u32GeinRegShift = 0xA0;
            break;
        case E_HAL_DISP_MOPG_ID_06:
        case E_HAL_DISP_MOPG_ID_14:
            u32GeinRegShift = 0xC0;
            break;
        case E_HAL_DISP_MOPG_ID_07:
        case E_HAL_DISP_MOPG_ID_15:
            u32GeinRegShift = 0xE0;
            break;
        default:
            DISP_ERR("[HALMOP]%s %d, Mopg ID %d not support\n", __FUNCTION__, __LINE__,eMopgId);
            u32GeinRegShift = 0x00;
            break;
    }
    return u32GeinRegShift;
}


//-------------------------------------------------------------------------------------------------
//  Global Functions
//-------------------------------------------------------------------------------------------------
void HalDispMopDbBfWr(void);

///MOPG
void HalDispMopgSwReset(void)
{
    W2BYTEMSK(REG_DISP_MOPG_BK0_00_L, 0x0001, 0x0001);
    W2BYTEMSK(REG_DISP_MOPG_BK0_00_L, 0x0000, 0x0001);
}

void HalDispMopgSetAutoStretchWinSizeEn(bool bEnAuto)//0: use reg_gw_hsize/vsize; 1: use display size
{
    W2BYTEMSK(REG_DISP_MOPG_BK0_01_L, bEnAuto ? BIT10 : 0, BIT10);
}

void HalDispMopgSetStretchWinSize(u16 u16Width, u16 u16Height)
{
    W2BYTEMSK(REG_DISP_MOPG_BK0_07_L, u16Width, 0x1FFF);//reg_gw_hsize
    W2BYTEMSK(REG_DISP_MOPG_BK0_08_L, u16Height, 0x1FFF);//reg_gw_vsize
}

void HalDispMopgSetPipeDelay(u8 u8PipeDelay)
{
    W2BYTEMSK(REG_DISP_MOPG_BK0_03_L, u8PipeDelay, 0x001F);//reg_gw_hsize
}

void HalDispMopgInit(void)
{
    HalDispMopgSwReset();
    W2BYTEMSK(REG_DISP_MOPG_BK0_01_L, BIT8, BIT8);//clk_miu. 0:use free run; 1:use gated clock
    W2BYTEMSK(REG_DISP_MOPG_BK0_01_L, BIT9, BIT9);//clk_gop. 0:use free run; 1:use gated clock
    HalDispMopgSetAutoStretchWinSizeEn(TRUE);
    W2BYTEMSK(REG_DISP_MOPG_BK0_01_L, BIT11, BIT11);//auto blanking. 0:use reg h15; 1:use display blanking
    HalDispMopgSetPipeDelay(0xA);//set pipe delay (default=0xA)
    W2BYTEMSK(REG_DISP_MOPG_BK0_04_L, 0xF8, 0x00FF);//h04 [7:0]ymd_thd
    W2BYTEMSK(REG_DISP_MOPG_BK0_05_L, 0xF8, 0x00FF);//h05 [7:0]cdma_thd
    W2BYTEMSK(REG_DISP_MOPG_BK0_06_L, 0xF0, 0x00FF);//h06 Luma DMA priority [7]yhp_en [6:0] yhp_thd
    W2BYTEMSK(REG_DISP_MOPG_BK0_0B_L, 0xF0, 0x00FF);//h0b Chroma DMA priority [7]yhp_en [6:0] yhp_thd
    W2BYTEMSK(REG_DISP_MOPG_BK0_15_L, 0x80, 0x1FFF);//h15 [12:0]gw_hext

    //set double buffer write
    HalDispMopDbBfWr();
}

void HalDispMopgGwinEn(HalDispMopgGwinId_e eMopgId, bool bEn)
{
    u32 Mopg_Gwin_Reg_BK = 0;
    u32 Mopg_Gwin_Reg_Shift = 0;
    u32 Mopg_Gwin_Reg_Base = 0;
    Mopg_Gwin_Reg_BK = _HalDispMopgGwinRegBkMap(eMopgId);
    Mopg_Gwin_Reg_Shift = _HalDispMopgGwinRegShiftMap(eMopgId);
    Mopg_Gwin_Reg_Base = (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK2_BASE) ? REG_DISP_MOPG_BK2_00_L:
                                                                        REG_DISP_MOPG_BK1_00_L;
    W2BYTEMSK(Mopg_Gwin_Reg_Base + Mopg_Gwin_Reg_Shift, bEn ? BIT0 : 0, BIT0);

    //set double buffer write
    HalDispMopDbBfWr();
}

void HalDispMopgSetYAddr(HalDispMopgGwinId_e eMopgId, u32 u32PhyAddr)
{
    u32 u32RegVal;
    u32 Mopg_Gwin_Reg_BK = 0;
    u32 Mopg_Gwin_Reg_Shift = 0;
    u32 Mopg_Gwin_Reg_Base = 0;
    u32 Mopg_Gwin_Reg_Base2 = 0;
    Mopg_Gwin_Reg_BK = _HalDispMopgGwinRegBkMap(eMopgId);
    Mopg_Gwin_Reg_Shift = _HalDispMopgGwinRegShiftMap(eMopgId);
    Mopg_Gwin_Reg_Base = (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK2_BASE) ? REG_DISP_MOPG_BK2_02_L:
                                                                        REG_DISP_MOPG_BK1_02_L;
    Mopg_Gwin_Reg_Base2 = (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK2_BASE) ? REG_DISP_MOPG_BK2_03_L:
                                                                         REG_DISP_MOPG_BK1_03_L;
    u32RegVal = u32PhyAddr >> HAL_DISP_MOP_MIU_BUS;
    W2BYTEMSK(Mopg_Gwin_Reg_Base + Mopg_Gwin_Reg_Shift, (u32RegVal & 0xFFFF), 0xFFFF);
    W2BYTEMSK(Mopg_Gwin_Reg_Base2 + Mopg_Gwin_Reg_Shift, ((u32RegVal>>16) & 0x0FFF), 0x0FFF);

    //set double buffer write
    HalDispMopDbBfWr();
}

void HalDispMopgSetAddr16Offset(HalDispMopgGwinId_e eMopgId, u8 u8Offset)
{
    u32 u32RegVal;
    u32 Mopg_Gwin_Reg_BK = 0;
    u32 Mopg_Gwin_Reg_Shift = 0;
    u32 Mopg_Gwin_Reg_Base = 0;
    Mopg_Gwin_Reg_BK = _HalDispMopgGwinRegBkMap(eMopgId);
    Mopg_Gwin_Reg_Shift = _HalDispMopgGwinRegShiftMap(eMopgId);
    Mopg_Gwin_Reg_Base = (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK2_BASE) ? REG_DISP_MOPG_BK2_01_L:
                                                                        REG_DISP_MOPG_BK1_01_L;
    u32RegVal = (u8Offset<<9);
    W2BYTEMSK(Mopg_Gwin_Reg_Base + Mopg_Gwin_Reg_Shift, (u32RegVal & 0x1E00), 0x1E00);

    //set double buffer write
    HalDispMopDbBfWr();
}

void HalDispMopgSetCAddr(HalDispMopgGwinId_e eMopgId, u32 u32PhyAddr)
{
    u32 u32RegVal;
    u32 Mopg_Gwin_Reg_BK = 0;
    u32 Mopg_Gwin_Reg_Shift = 0;
    u32 Mopg_Gwin_Reg_Base = 0;
    u32 Mopg_Gwin_Reg_Base2 = 0;
    Mopg_Gwin_Reg_BK = _HalDispMopgGwinRegBkMap(eMopgId);
    Mopg_Gwin_Reg_Shift = _HalDispMopgGwinRegShiftMap(eMopgId);
    Mopg_Gwin_Reg_Base = (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK2_BASE) ? REG_DISP_MOPG_BK2_04_L:
                                                                        REG_DISP_MOPG_BK1_04_L;
    Mopg_Gwin_Reg_Base2 = (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK2_BASE) ? REG_DISP_MOPG_BK2_05_L:
                                                                         REG_DISP_MOPG_BK1_05_L;
    u32RegVal = u32PhyAddr >> HAL_DISP_MOP_MIU_BUS;
    W2BYTEMSK(Mopg_Gwin_Reg_Base + Mopg_Gwin_Reg_Shift, (u32RegVal & 0xFFFF), 0xFFFF);
    W2BYTEMSK(Mopg_Gwin_Reg_Base2 + Mopg_Gwin_Reg_Shift, ((u32RegVal>>16) & 0x0FFF), 0x0FFF);

    //set double buffer write
    HalDispMopDbBfWr();
}

void HalDispMopgSetGwinParam(HalDispMopgGwinId_e eMopgId, u16 u16Hst, u16 u16Vst, u16 u16Width, u16 u16Height)
{
    u16 u16Hend;
    u16 u16Vend;
    u32 Mopg_Gwin_Reg_BK = 0;
    u32 Mopg_Gwin_Reg_Shift = 0;
    u32 Mopg_Gwin_Reg_Hst_Base = 0;
    u32 Mopg_Gwin_Reg_Hend_Base = 0;
    u32 Mopg_Gwin_Reg_Vst_Base = 0;
    u32 Mopg_Gwin_Reg_Vend_Base = 0;
    Mopg_Gwin_Reg_BK = _HalDispMopgGwinRegBkMap(eMopgId);
    Mopg_Gwin_Reg_Shift = _HalDispMopgGwinRegShiftMap(eMopgId);
    Mopg_Gwin_Reg_Hst_Base  = (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK2_BASE) ? REG_DISP_MOPG_BK2_06_L:
                                                                             REG_DISP_MOPG_BK1_06_L;
    Mopg_Gwin_Reg_Hend_Base = (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK2_BASE) ? REG_DISP_MOPG_BK2_07_L:
                                                                             REG_DISP_MOPG_BK1_07_L;
    Mopg_Gwin_Reg_Vst_Base  = (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK2_BASE) ? REG_DISP_MOPG_BK2_08_L:
                                                                             REG_DISP_MOPG_BK1_08_L;
    Mopg_Gwin_Reg_Vend_Base = (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK2_BASE) ? REG_DISP_MOPG_BK2_09_L:
                                                                             REG_DISP_MOPG_BK1_09_L;
    u16Hend = u16Hst + u16Width -1;
    u16Vend = u16Vst + u16Height -1;
    W2BYTEMSK(Mopg_Gwin_Reg_Hst_Base  + Mopg_Gwin_Reg_Shift, u16Hst,  0x1FFF);
    W2BYTEMSK(Mopg_Gwin_Reg_Hend_Base + Mopg_Gwin_Reg_Shift, u16Hend, 0x1FFF);
    W2BYTEMSK(Mopg_Gwin_Reg_Vst_Base  + Mopg_Gwin_Reg_Shift, u16Vst,  0x1FFF);
    W2BYTEMSK(Mopg_Gwin_Reg_Vend_Base + Mopg_Gwin_Reg_Shift, u16Vend, 0x1FFF);

    //set double buffer write
    HalDispMopDbBfWr();
}

void HalDispMopgSetPitch(HalDispMopgGwinId_e eMopgId, u16 u16Pitch)
{
    u16 u16RegVal;
    u32 Mopg_Gwin_Reg_BK = 0;
    u32 Mopg_Gwin_Reg_Shift = 0;
    u32 Mopg_Gwin_Reg_Base = 0;
    Mopg_Gwin_Reg_BK = _HalDispMopgGwinRegBkMap(eMopgId);
    Mopg_Gwin_Reg_Shift = _HalDispMopgGwinRegShiftMap(eMopgId);
    Mopg_Gwin_Reg_Base = (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK2_BASE) ? REG_DISP_MOPG_BK2_0A_L:
                                                                        REG_DISP_MOPG_BK1_0A_L;
    u16RegVal = u16Pitch >> HAL_DISP_MOP_MIU_BUS;
    W2BYTEMSK(Mopg_Gwin_Reg_Base + Mopg_Gwin_Reg_Shift, u16RegVal, 0x1FFF);

    //set double buffer write
    HalDispMopDbBfWr();
}

void HalDispMopgSetSourceParam(HalDispMopgGwinId_e eMopgId, u16 u16SrcWidth, u16 u16SrcHeight)
{
    u32 Mopg_Gwin_Reg_BK = 0;
    u32 Mopg_Gwin_Reg_Shift = 0;
    u32 Mopg_Gwin_Reg_SrcWidth_Base = 0;
    u32 Mopg_Gwin_Reg_SrcHeight_Base = 0;
    Mopg_Gwin_Reg_BK = _HalDispMopgGwinRegBkMap(eMopgId);
    Mopg_Gwin_Reg_Shift = _HalDispMopgGwinRegShiftMap(eMopgId);
    Mopg_Gwin_Reg_SrcWidth_Base = (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK2_BASE) ? REG_DISP_MOPG_BK2_0B_L:
                                                                                 REG_DISP_MOPG_BK1_0B_L;
    Mopg_Gwin_Reg_SrcHeight_Base = (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK2_BASE) ? REG_DISP_MOPG_BK2_0C_L:
                                                                                  REG_DISP_MOPG_BK1_0C_L;
    W2BYTEMSK(Mopg_Gwin_Reg_SrcWidth_Base  + Mopg_Gwin_Reg_Shift, (u16SrcWidth-1),  0x1FFF);
    W2BYTEMSK(Mopg_Gwin_Reg_SrcHeight_Base + Mopg_Gwin_Reg_Shift, (u16SrcHeight-1), 0x1FFF);

    //set double buffer write
    HalDispMopDbBfWr();
}

void HalDispMopgSetHScaleFac(HalDispMopgGwinId_e eMopgId, u16 u16HRatio)
{
    u32 Mopg_Gwin_Reg_BK = 0;
    u32 Mopg_Gwin_Reg_Shift = 0;
    u32 Mopg_Gwin_Reg_Base = 0;
    Mopg_Gwin_Reg_BK = _HalDispMopgGwinRegBkMap(eMopgId);
    Mopg_Gwin_Reg_Shift = _HalDispMopgGwinRegShiftMap(eMopgId);
    Mopg_Gwin_Reg_Base = (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK2_BASE) ? REG_DISP_MOPG_BK2_0D_L:
                                                                        REG_DISP_MOPG_BK1_0D_L;
    W2BYTEMSK(Mopg_Gwin_Reg_Base + Mopg_Gwin_Reg_Shift, u16HRatio,  0x1FFF);

    //set double buffer write
    HalDispMopDbBfWr();
}

void HalDispMopgSetVScaleFac(HalDispMopgGwinId_e eMopgId, u16 u16VRatio)
{
    u32 Mopg_Gwin_Reg_BK = 0;
    u32 Mopg_Gwin_Reg_Shift = 0;
    u32 Mopg_Gwin_Reg_Base = 0;
    Mopg_Gwin_Reg_BK = _HalDispMopgGwinRegBkMap(eMopgId);
    Mopg_Gwin_Reg_Shift = _HalDispMopgGwinRegShiftMap(eMopgId);
    Mopg_Gwin_Reg_Base = (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK2_BASE) ? REG_DISP_MOPG_BK2_0E_L:
                                                                        REG_DISP_MOPG_BK1_0E_L;
    W2BYTEMSK(Mopg_Gwin_Reg_Base + Mopg_Gwin_Reg_Shift, u16VRatio,  0x1FFF);

    //set double buffer write
    HalDispMopDbBfWr();
}

void HalDispMopgSetRblkHstr(HalDispMopgGwinId_e eMopgId, u8 u8Hshift)
{
    u32 Mopg_Gwin_Reg_BK = 0;
    u32 Mopg_Gwin_Reg_Shift = 0;
    u32 Mopg_Gwin_Reg_Base = 0;
    Mopg_Gwin_Reg_BK = _HalDispMopgGwinRegBkMap(eMopgId);
    Mopg_Gwin_Reg_Shift = _HalDispMopgGwinRegShiftMap(eMopgId);
    Mopg_Gwin_Reg_Base = (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK2_BASE) ? REG_DISP_MOPG_BK2_01_L:
                                                                        REG_DISP_MOPG_BK1_01_L;
    W2BYTEMSK(Mopg_Gwin_Reg_Base + Mopg_Gwin_Reg_Shift, (u8Hshift<<8),  0x0F00);

    //set double buffer write
    HalDispMopDbBfWr();
}


void HalDispMopgSetLineBufStr(HalDispMopgGwinId_e eMopgId, u16 u16GwinHstr, u8 u8WinPri)
{
    u32 Mopg_Gwin_Reg_BK = 0;
    u32 Mopg_Gwin_Reg_Shift = 0;
    u32 Mopg_Gwin_Reg_Base = 0;
    u16 u16RegVal = 0;
    Mopg_Gwin_Reg_BK = _HalDispMopgGwinRegBkMap(eMopgId);
    Mopg_Gwin_Reg_Shift = _HalDispMopgGwinRegShiftMap(eMopgId);
    Mopg_Gwin_Reg_Base = (Mopg_Gwin_Reg_BK == REG_DISP_MOPG_BK2_BASE) ? REG_DISP_MOPG_BK2_01_L:
                                                                        REG_DISP_MOPG_BK1_01_L;
    u16RegVal = ((u16GwinHstr>>3) + 2*u8WinPri) & 0xFF;//lb_str = gwin_hstr/8 + 2*gwin_priority; gwin_priority is the order of the position of display(from left on) 0~15
    W2BYTEMSK(Mopg_Gwin_Reg_Base + Mopg_Gwin_Reg_Shift, u16RegVal,  0x00FF);

    //set double buffer write
    HalDispMopDbBfWr();
}


///MOPS
void HalDispMopsSwReset(void)
{
    W2BYTEMSK(REG_DISP_MOPS_BK0_00_L, 0x0001, 0x0001);
    W2BYTEMSK(REG_DISP_MOPS_BK0_00_L, 0x0000, 0x0001);
}

void HalDispMopsSetAutoStretchWinSizeEn(bool bEnAuto)//0: use reg_gw_hsize/vsize; 1: use display size
{
    W2BYTEMSK(REG_DISP_MOPS_BK0_01_L, bEnAuto ? BIT10 : 0, BIT10);
}

void HalDispMopsSetStretchWinSize(u16 u16Width, u16 u16Height)
{
    W2BYTEMSK(REG_DISP_MOPS_BK0_07_L, u16Width, 0x1FFF);//reg_gw_hsize
    W2BYTEMSK(REG_DISP_MOPS_BK0_08_L, u16Height, 0x1FFF);//reg_gw_vsize
}

void HalDispMopsSetPipeDelay(u8 u8PipeDelay)
{
    W2BYTEMSK(REG_DISP_MOPS_BK0_03_L, u8PipeDelay, 0x001F);//reg_gw_hsize
}

void HalDispMopsInit(void)
{
    HalDispMopsSwReset();
    W2BYTEMSK(REG_DISP_MOPS_BK0_01_L, BIT8, BIT8);//clk_miu. 0:use free run; 1:use gated clock
    W2BYTEMSK(REG_DISP_MOPS_BK0_01_L, BIT9, BIT9);//clk_gop. 0:use free run; 1:use gated clock
    HalDispMopsSetAutoStretchWinSizeEn(TRUE);
    W2BYTEMSK(REG_DISP_MOPS_BK0_01_L, BIT11, BIT11);//auto blanking. 0:use reg h15; 1:use display blanking
    HalDispMopsSetPipeDelay(0xA);//set pipe delay (default=0xA)
    W2BYTEMSK(REG_DISP_MOPS_BK0_04_L, 0xF8, 0x00FF);//h04 [7:0]ymd_thd
    W2BYTEMSK(REG_DISP_MOPS_BK0_05_L, 0xF8, 0x00FF);//h05 [7:0]cdma_thd
    W2BYTEMSK(REG_DISP_MOPS_BK0_06_L, 0xF0, 0x00FF);//h06 Luma DMA priority [7]yhp_en [6:0] yhp_thd
    W2BYTEMSK(REG_DISP_MOPS_BK0_0B_L, 0xF0, 0x00FF);//h0b Chroma DMA priority [7]yhp_en [6:0] yhp_thd
    W2BYTEMSK(REG_DISP_MOPS_BK0_15_L, 0x80, 0x1FFF);//h15 [12:0]gw_hext

    //set double buffer write
    HalDispMopDbBfWr();
}

void HalDispMopsGwinEn(bool bEn)
{
    W2BYTEMSK(REG_DISP_MOPS_BK0_20_L, bEn ? BIT0 : 0, BIT0);

    //set double buffer write
    HalDispMopDbBfWr();
}

void HalDispMopsSetYAddr(u32 u32PhyAddr)
{
    u32 u32RegVal;
    u32RegVal = u32PhyAddr >> HAL_DISP_MOP_MIU_BUS;
    W2BYTEMSK(REG_DISP_MOPS_BK0_22_L, (u32RegVal & 0xFFFF), 0xFFFF);
    W2BYTEMSK(REG_DISP_MOPS_BK0_23_L, ((u32RegVal>>16) & 0x0FFF), 0x0FFF);

    //set double buffer write
    HalDispMopDbBfWr();
}
void HalDispMopsSetAddr16Offset(u8 u8Offset)
{
    u32 u32RegVal;

    u32RegVal = (u8Offset<<9);
    W2BYTEMSK(REG_DISP_MOPS_BK0_21_L, (u32RegVal & 0x1E00), 0x1E00);

    //set double buffer write
    HalDispMopDbBfWr();
}

void HalDispMopsSetCAddr(u32 u32PhyAddr)
{
    u32 u32RegVal;
    u32RegVal = u32PhyAddr >> HAL_DISP_MOP_MIU_BUS;
    W2BYTEMSK(REG_DISP_MOPS_BK0_24_L, (u32RegVal & 0xFFFF), 0xFFFF);
    W2BYTEMSK(REG_DISP_MOPS_BK0_25_L, ((u32RegVal>>16) & 0x0FFF), 0x0FFF);

    //set double buffer write
    HalDispMopDbBfWr();
}

void HalDispMopsSetGwinParam(u16 u16Hst, u16 u16Vst, u16 u16Width, u16 u16Height)
{
    u16 u16Hend;
    u16 u16Vend;
    u16Hend = u16Hst + u16Width -1;
    u16Vend = u16Vst + u16Height -1;
    W2BYTEMSK(REG_DISP_MOPS_BK0_26_L, u16Hst,  0x1FFF);
    W2BYTEMSK(REG_DISP_MOPS_BK0_27_L, u16Hend, 0x1FFF);
    W2BYTEMSK(REG_DISP_MOPS_BK0_28_L, u16Vst,  0x1FFF);
    W2BYTEMSK(REG_DISP_MOPS_BK0_29_L, u16Vend, 0x1FFF);

    //set double buffer write
    HalDispMopDbBfWr();
}

void HalDispMopsSetPitch(u16 u16Pitch)
{
    u16 u16RegVal;
    u16RegVal = u16Pitch >> HAL_DISP_MOP_MIU_BUS;
    W2BYTEMSK(REG_DISP_MOPS_BK0_2A_L, u16RegVal, 0x1FFF);

    //set double buffer write
    HalDispMopDbBfWr();
}

void HalDispMopsSetSourceParam(u16 u16SrcWidth, u16 u16SrcHeight)
{
    W2BYTEMSK(REG_DISP_MOPS_BK0_2B_L, u16SrcWidth,  0x1FFF);
    W2BYTEMSK(REG_DISP_MOPS_BK0_2C_L, u16SrcHeight, 0x1FFF);

    //set double buffer write
    HalDispMopDbBfWr();
}

void HalDispMopsSetHScaleFac(u16 u16HRatio)
{
    W2BYTEMSK(REG_DISP_MOPS_BK0_2D_L, u16HRatio,  0x1FFF);

    //set double buffer write
    HalDispMopDbBfWr();
}

void HalDispMopsSetVScaleFac(u16 u16VRatio)
{
    W2BYTEMSK(REG_DISP_MOPS_BK0_2E_L, u16VRatio,  0x1FFF);

    //set double buffer write
    HalDispMopDbBfWr();
}

void HalDispMopsSetRblkHstr(u8 u8Hshift)
{
    W2BYTEMSK(REG_DISP_MOPS_BK0_21_L, (u8Hshift<<8),  0x0F00);

    //set double buffer write
    HalDispMopDbBfWr();
}


///MOP common
void HalDispMopDbBfWr(void)
{
    W2BYTEMSK(REG_DISP_MOPG_BK0_7F_L, BIT8, BIT8);
    W2BYTEMSK(REG_DISP_MOPG_BK0_7F_L, 0, BIT8);
}
