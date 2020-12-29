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


#ifndef _HAL_DISP_CHIP_H_
#define _HAL_DISP_CHIP_H_

//-------------------------------------------------------------------------------------------------
//  Defines & Macro
//-------------------------------------------------------------------------------------------------
#define HAL_DISP_CTX_MAX_INST   2

// Device Ctx
#define HAL_DISP_DEVICE_MAX     1

// IRQ CTX
#define HAL_DISP_DEVICE_IRQ_MAX 2

// Inernal Isr
#define HAL_DISP_INTERNAL_ISR_SUPPORT           1
#define HAL_DISP_DEVICE_IRQ_INTERNAL_ISR_IDX    1
#define E_HAL_DISP_IRQ_TYPE_INTERNAL_TIMEZONE   (E_HAL_DISP_IRQ_TYPE_INTERNAL_VSYNC_POSITIVE | E_HAL_DISP_IRQ_TYPE_INTERNAL_VDE_POSITIVE | E_HAL_DISP_IRQ_TYPE_INTERNAL_VDE_NEGATIVE)


#define HAL_DISP_VIDLAYER_MAX   2 // MOPG & MOPS

#define HAL_DISP_MOPG_GWIN_NUM  16 //MOPG 16 Gwins
#define HAL_DISP_MOPS_GWIN_NUM  1  //MOPS 1 Gwin

#define HAL_DISP_INPUTPORT_NUM  (HAL_DISP_MOPG_GWIN_NUM+HAL_DISP_MOPS_GWIN_NUM) //I2m MOP: 16Gwin_MOPG + 1Gwin_MOPS
#define HAL_DISP_INPUTPORT_MAX  (HAL_DISP_VIDLAYER_MAX  * HAL_DISP_INPUTPORT_NUM)


//-------------------------------------------------------------------------------------------------
//  Enum
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  structure
//-------------------------------------------------------------------------------------------------

#endif

