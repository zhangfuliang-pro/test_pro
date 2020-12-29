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


#define _HAL_DISP_IRQ_C_

//-------------------------------------------------------------------------------------------------
//  Include Files
//-------------------------------------------------------------------------------------------------
#ifdef DISP_OS_TYPE_LINUX_KERNEL
#include <linux/string.h>
#include "cam_os_wrapper.h"
#endif

#include "drv_disp_os.h"
#include "hal_disp_common.h"
#include "disp_debug.h"
#include "hal_disp_util.h"
#include "hal_disp_reg.h"
#include "hal_disp_irq.h"
#include "hal_disp_chip.h"
#include "hal_disp_st.h"
//-------------------------------------------------------------------------------------------------
//  Defines & Macro
//-------------------------------------------------------------------------------------------------
#define HAL_DISP_IRQ_VSYNC_BIT (0x0001)     // BIT0
#define HAL_DISP_IRQ_VSYNC_MSK (0x0001)

#define HAL_DISP_IRQ_VDE_BIT   (0x0000)
#define HAL_DISP_IRQ_VDE_MSK   (0x0000)     //Not Support


#define HAL_DISP_IRQ_MASK_REG  (REG_DISP_MOPG_BK0_0C_L)
#define HAL_DISP_IRQ_FLAG_REG  (REG_DISP_MOPG_BK0_02_L)
#define HAL_DISP_IRQ_CLEAR_REG (REG_DISP_MOPG_BK0_0C_L)

//-------------------------------------------------------------------------------------------------
// Internal Isr for TimeZone
//-------------------------------------------------------------------------------------------------
#define HAL_DISP_IRQ_INTERNAL_MASK_REG  (REG_DISP_TOP_03_L)
#define HAL_DISP_IRQ_INTERNAL_FLAG_REG  (REG_DISP_TOP_02_L)
#define HAL_DISP_IRQ_INTERNAL_CLEAR_REG (REG_DISP_TOP_02_L)


#define HAL_DISP_IRQ_INTERNAL_VSYNC_POSITIVE_BIT    0x08 // BIT3
#define HAL_DISP_IRQ_INTERNAL_VSYNC_POSITIVE_MSK    0x08

#define HAL_DISP_IRQ_INTERNAL_VSYNC_NEGATIVE_BIT    0x04 // BIT2
#define HAL_DISP_IRQ_INTERNAL_VSYNC_NEGATIVE_MSK    0x04

#define HAL_DISP_IRQ_INTERNAL_VDE_POSITIVE_BIT      0x02 // BIT1
#define HAL_DISP_IRQ_INTERNAL_VDE_POSITIVE_MSK      0x02

#define HAL_DISP_IRQ_INTERNAL_VDE_NEGATIVE_BIT      0x01 // BIT0
#define HAL_DISP_IRQ_INTERNAL_VDE_NEGATIVE_MSK      0x01



//-------------------------------------------------------------------------------------------------
//  structure
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Variable
//-------------------------------------------------------------------------------------------------

u32 gu32InternalIsrStatus = 0;
//-------------------------------------------------------------------------------------------------
//  Local Functions
//-------------------------------------------------------------------------------------------------
__inline void _HalDispIrqEnableIsr(HalDispIrqType_e enType, bool *pbEn)
{
    u16 u16Val, u16Msk;
    bool bEnable = *pbEn;

    u16Val = 0;
    u16Msk = 0;

    DISP_DBG(DISP_DBG_LEVEL_IRQ, "%s %d, Type:%x, En:%d\n", __FUNCTION__, __LINE__, enType , bEnable);
    if(enType & E_HAL_DISP_IRQ_TYPE_VSYNC)
    {
        u16Val |= bEnable ?  0 : HAL_DISP_IRQ_VSYNC_BIT;
        u16Msk |= HAL_DISP_IRQ_VSYNC_MSK;
    }

    if(enType & E_HAL_DISP_IRQ_TYPE_VDE)
    {
        u16Val |= bEnable ?  0 : HAL_DISP_IRQ_VDE_BIT;
        u16Msk |= HAL_DISP_IRQ_VDE_MSK;
    }

    W2BYTEMSK(HAL_DISP_IRQ_MASK_REG, u16Val, u16Msk);
}


__inline void _HalDispIrqGetFlag(HalDispIrqType_e enType, u32 *pu32Flag)
{
    u16 u16Val, u16IrqMsk;

    *pu32Flag = 0;

    u16Val = R2BYTE(HAL_DISP_IRQ_FLAG_REG);
    u16IrqMsk = R2BYTE(HAL_DISP_IRQ_MASK_REG);

    if(enType & E_HAL_DISP_IRQ_TYPE_VSYNC)
    {
        *pu32Flag |= (u16Val & HAL_DISP_IRQ_VSYNC_MSK) ? E_HAL_DISP_IRQ_TYPE_VSYNC : 0;
    }

    if(enType & E_HAL_DISP_IRQ_TYPE_VDE)
    {
        *pu32Flag |= (u16Val & HAL_DISP_IRQ_VDE_MSK) ? E_HAL_DISP_IRQ_TYPE_VDE : 0;
    }


    DISP_DBG(DISP_DBG_LEVEL_IRQ, "%s %d, enType:%x, Flag:%lx (%04x %04x)\n", __FUNCTION__, __LINE__, enType, *pu32Flag, u16IrqMsk, u16Val);
}


__inline void _HalDispIrqClear(HalDispIrqType_e enType)
{
    u16 u16Val, u16Msk;

    DISP_DBG(DISP_DBG_LEVEL_IRQ, "%s %d, enType:%x\n", __FUNCTION__, __LINE__, enType);

    u16Val = 0;
    u16Msk = 0;
    if(enType & E_HAL_DISP_IRQ_TYPE_VSYNC)
    {
        u16Val |= HAL_DISP_IRQ_VSYNC_BIT;
        u16Msk |= HAL_DISP_IRQ_VSYNC_MSK;
    }

    if(enType & E_HAL_DISP_IRQ_TYPE_VDE)
    {
        u16Val |= HAL_DISP_IRQ_VDE_BIT;
        u16Msk |= HAL_DISP_IRQ_VDE_MSK;
    }

    // Clear, 1->0
    W2BYTEMSK(HAL_DISP_IRQ_CLEAR_REG, u16Val, u16Msk);
    W2BYTEMSK(HAL_DISP_IRQ_CLEAR_REG, 0, u16Msk);
}

__inline void _HalDispIrqSupportedInternalIsr(bool *pbSupported)
{
    *pbSupported = HAL_DISP_INTERNAL_ISR_SUPPORT;
}

__inline void  _HalDispIrqGetInternalIsrDeviceIdx(u8 *pu8Id)
{
    *pu8Id = HAL_DISP_DEVICE_IRQ_INTERNAL_ISR_IDX;
}


__inline void _HalDispIrqEnableInternalIsr(HalDispIrqType_e enType, bool *pbEn)
{
    u16 u16Val, u16Msk;
    bool bEnable = *pbEn;
    u16Val = 0;
    u16Msk = 0;

    if(enType & E_HAL_DISP_IRQ_TYPE_INTERNAL_VSYNC_POSITIVE)
    {
        u16Val |= bEnable ?  0 : HAL_DISP_IRQ_INTERNAL_VSYNC_POSITIVE_BIT;
        u16Msk |= HAL_DISP_IRQ_INTERNAL_VSYNC_POSITIVE_MSK;
    }

    if(enType & E_HAL_DISP_IRQ_TYPE_INTERNAL_VSYNC_NEGATIVE)
    {
        u16Val |= bEnable ?  0 : HAL_DISP_IRQ_INTERNAL_VSYNC_NEGATIVE_BIT;
        u16Msk |= HAL_DISP_IRQ_INTERNAL_VSYNC_NEGATIVE_MSK;
    }

    if(enType & E_HAL_DISP_IRQ_TYPE_INTERNAL_VDE_POSITIVE)
    {
        u16Val |= bEnable ?  0 : HAL_DISP_IRQ_INTERNAL_VDE_POSITIVE_BIT;
        u16Msk |= HAL_DISP_IRQ_INTERNAL_VDE_POSITIVE_MSK;
    }

    if(enType & E_HAL_DISP_IRQ_TYPE_INTERNAL_VDE_NEGATIVE)
    {
        u16Val |= bEnable ?  0 : HAL_DISP_IRQ_INTERNAL_VDE_NEGATIVE_BIT;
        u16Msk |= HAL_DISP_IRQ_INTERNAL_VDE_NEGATIVE_MSK;
    }

    W2BYTEMSK(HAL_DISP_IRQ_INTERNAL_MASK_REG, u16Val, u16Msk);
}

__inline void _HalDispIrqGetInternalFlag(HalDispIrqType_e enType, u32 *pu32Flag)
{
    u16 u16Val;
    //u16 u16IrqMsk;
    *pu32Flag = 0;

    u16Val = R2BYTE(HAL_DISP_IRQ_INTERNAL_FLAG_REG);
    //u16IrqMsk = R2BYTE(HAL_DISP_IRQ_INTERNAL_MASK_REG);

    if(enType & E_HAL_DISP_IRQ_TYPE_INTERNAL_VSYNC_POSITIVE)
    {
        *pu32Flag |= (u16Val & HAL_DISP_IRQ_INTERNAL_VSYNC_POSITIVE_MSK) ? E_HAL_DISP_IRQ_TYPE_INTERNAL_VSYNC_POSITIVE : 0;
    }

    if(enType & E_HAL_DISP_IRQ_TYPE_INTERNAL_VSYNC_NEGATIVE)
    {
        *pu32Flag |= (u16Val & HAL_DISP_IRQ_INTERNAL_VSYNC_NEGATIVE_BIT) ? E_HAL_DISP_IRQ_TYPE_INTERNAL_VSYNC_NEGATIVE : 0;
    }

    if(enType & E_HAL_DISP_IRQ_TYPE_INTERNAL_VDE_POSITIVE)
    {
        *pu32Flag |= (u16Val & HAL_DISP_IRQ_INTERNAL_VDE_POSITIVE_MSK) ? E_HAL_DISP_IRQ_TYPE_INTERNAL_VDE_POSITIVE : 0;
    }

    if(enType & E_HAL_DISP_IRQ_TYPE_INTERNAL_VDE_NEGATIVE)
    {
        *pu32Flag |= (u16Val & HAL_DISP_IRQ_INTERNAL_VDE_NEGATIVE_MSK) ? E_HAL_DISP_IRQ_TYPE_INTERNAL_VDE_NEGATIVE : 0;
    }

    gu32InternalIsrStatus = *pu32Flag;
    //DISP_DBG(DISP_DBG_LEVEL_IRQ_INTERNAL, "%s %d, enType:%x, Flag:%x (%04x %04x)\n", __FUNCTION__, __LINE__, enType, *pu32Flag, u16IrqMsk, u16Val);
}


__inline void _HalDispIrqClearInternal(HalDispIrqType_e enType)
{
    u16 u16Val, u16Msk;

    DISP_DBG(DISP_DBG_LEVEL_IRQ, "%s %d, enType:%x\n", __FUNCTION__, __LINE__, enType);

    u16Val = 0;
    u16Msk = 0;

    if(enType & E_HAL_DISP_IRQ_TYPE_INTERNAL_VSYNC_POSITIVE)
    {
        u16Val |= HAL_DISP_IRQ_INTERNAL_VSYNC_POSITIVE_BIT;
        u16Msk |= HAL_DISP_IRQ_INTERNAL_VSYNC_POSITIVE_MSK;
    }

    if(enType & E_HAL_DISP_IRQ_TYPE_INTERNAL_VSYNC_NEGATIVE)
    {
        u16Val |= HAL_DISP_IRQ_INTERNAL_VSYNC_NEGATIVE_BIT;
        u16Msk |= HAL_DISP_IRQ_INTERNAL_VSYNC_NEGATIVE_MSK;
    }

    if(enType & E_HAL_DISP_IRQ_TYPE_INTERNAL_VDE_POSITIVE)
    {
        u16Val |= HAL_DISP_IRQ_INTERNAL_VDE_POSITIVE_BIT;
        u16Msk |= HAL_DISP_IRQ_INTERNAL_VDE_POSITIVE_MSK;
    }

    if(enType & E_HAL_DISP_IRQ_TYPE_INTERNAL_VDE_NEGATIVE)
    {
        u16Val |= HAL_DISP_IRQ_INTERNAL_VDE_NEGATIVE_BIT;
        u16Msk |= HAL_DISP_IRQ_INTERNAL_VDE_NEGATIVE_MSK;
    }

    W2BYTEMSK(HAL_DISP_IRQ_INTERNAL_CLEAR_REG, u16Val, u16Msk);

    //DISP_DBG(DISP_DBG_LEVEL_IRQ_INTERNAL, "%s %d, enType:%x \n", __FUNCTION__, __LINE__, enType);
}

__inline void HalDispIrqGetInternalIsrStatus(u32 *pu32Status)
{
    *pu32Status = gu32InternalIsrStatus;
}

//-------------------------------------------------------------------------------------------------
//  Global Functions
//-------------------------------------------------------------------------------------------------
bool HalDispIrqIoCtl(HalDispIrqIoCtlType_e enIoctlType, HalDispIrqType_e enIrqType, void *pCfg)
{
    bool bRet = 1;

    DISP_DBG(DISP_DBG_LEVEL_IRQ, "%s %d, Ioctl:%s, IrqType:%s\n", __FUNCTION__, __LINE__, PARSING_HAL_IRQ_IOCTL(enIoctlType), PARSING_HAL_IRQ_TYPE(enIrqType));
    switch(enIoctlType)
    {
        case E_HAL_DISP_IRQ_IOCTL_ENABLE:
            _HalDispIrqEnableIsr(enIrqType, (bool *)pCfg);
            break;

        case E_HAL_DISP_IRQ_IOCTL_GET_FLAG:
            _HalDispIrqGetFlag(enIrqType,(u32 * )pCfg);
            break;

        case E_HAL_DISP_IRQ_IOCTL_CLEAR:
            _HalDispIrqClear(enIrqType);
            break;

        case E_HAL_DISP_IRQ_IOCTL_INTERNAL_SUPPORTED:
            _HalDispIrqSupportedInternalIsr((bool *)pCfg);
            break;

        case E_HAL_DISP_IRQ_IOCTL_INTERNAL_GET_ID:
            _HalDispIrqGetInternalIsrDeviceIdx((u8 *)pCfg);
            break;

        case E_HAL_DISP_IRQ_IOCTL_INTERNAL_ENABLE:
            _HalDispIrqEnableInternalIsr(enIrqType, (bool *)pCfg);
            break;

        case E_HAL_DISP_IRQ_IOCTL_INTERNAL_GET_FLAG:
            _HalDispIrqGetInternalFlag(enIrqType, (u32 *)pCfg);
            break;

        case E_HAL_DISP_IRQ_IOCTL_INTERNAL_CLEAR:
            _HalDispIrqClearInternal(enIrqType);
            break;

        case E_HAL_DISP_IRQ_IOCTL_INTERNAL_GET_STATUS:
            HalDispIrqGetInternalIsrStatus((u32 *)pCfg);
            break;

        default:
            bRet = FALSE;
            DISP_ERR("%s %d, UnKnown Irq Iocl:%d\n", __FUNCTION__, __LINE__, enIoctlType);
            break;
    }
    return bRet;
}
