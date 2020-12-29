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


#ifndef _HAL_DISP_SCALER_E_H_
#define _HAL_DISP_SCALER_E_H_

//-------------------------------------------------------------------------------------------------
//  Defines & Macro
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  structure & Enum
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Prototype
//-------------------------------------------------------------------------------------------------

#ifdef _HAL_DISP_SCALER_E_C_
#define INTERFACE
#else
#define INTERFACE extern
#endif

INTERFACE void HalDispOp2Init(void);
INTERFACE void HalDispSetSwReste(u8 u8Val);
INTERFACE void HalDispSetFifoRest(u8 u8Val);
INTERFACE void HalDispSetMaceSrc(bool bExtVideo);
INTERFACE void HalDispSetPatGenMd(u8 u8Val);
INTERFACE void HalDispSetTgenHtt(u16 u16Val);
INTERFACE void HalDispSetTgenVtt(u16 u16Val);
INTERFACE void HalDispSetTgenHsyncSt(u16 u16Val);
INTERFACE void HalDispSetTgenHsyncEnd(u16 u16Val);
INTERFACE void HalDispSetTgenVsyncSt(u16 u16Val);
INTERFACE void HalDispSetTgenVsyncEnd(u16 u16Val);
INTERFACE void HalDispSetTgenHfdeSt(u16 u16Val);
INTERFACE void HalDispSetTgenHfdeEnd(u16 u16Val);
INTERFACE void HalDispSetTgenVfdeSt(u16 u16Val);
INTERFACE void HalDispSetTgenVfdeEnd(u16 u16Val);
INTERFACE void HalDispSetTgenHdeSt(u16 u16Val);
INTERFACE void HalDispSetTgenHdeEnd(u16 u16Val);
INTERFACE void HalDispSetTgenVdeSt(u16 u16Val);
INTERFACE void HalDispSetTgenVdeEnd(u16 u16Val);;
INTERFACE void HalDispSetTgenDacHsyncSt(u16 u16Val);
INTERFACE void HalDispSetTgenDacHsyncEnd(u16 u16Val);
INTERFACE void HalDispSetTgenDacHdeSt(u16 u16Val);
INTERFACE void HalDispSetTgenDacHdeEnd(u16 u16Val);
INTERFACE void HalDispSetTgenDacVdeSt(u16 u16Val);
INTERFACE void HalDispSetTgenDacVdeEnd(u16 u16Val);
INTERFACE void HalDispSetFrameColor(u8 u8R, u8 u8G, u8 u8B);
INTERFACE void HalDispSetFrameColorForce(u8 u8Val);
INTERFACE void HalDispSetDispWinColor(u8 u8R, u8 u8G, u8 u8B);
INTERFACE void HalDispSetDispWinColorForce(bool bEn);
INTERFACE void HalDispDumpRegTab(u8 *pData, u16 u16RegNum, u16 u16DataSize, u8 u8DataOffset);


#undef INTERFACE
#endif
