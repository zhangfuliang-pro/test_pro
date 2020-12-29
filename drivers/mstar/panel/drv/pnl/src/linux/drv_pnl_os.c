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


#define _DRV_PNL_OS_C_

#include "cam_os_wrapper.h"

void * DrvPnlOsMemAlloc(u32 u32Size)
{
    return CamOsMemAlloc(u32Size);
}

void DrvPnlOsMemRelease(void *pPtr)
{
    CamOsMemRelease(pPtr);
}

void DrvPnlOsMsSleep(u32 u32Msec)
{
    CamOsMsSleep(u32Msec);
}

void DrvPnlOsUsSleep(u32 u32Usec)
{
    CamOsUsSleep(u32Usec);
}


