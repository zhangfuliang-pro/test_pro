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


#define _DRV_DISP_OS_C_
#include <common.h>
#include <command.h>
#include <config.h>
#include <malloc.h>
#include <stdlib.h>

void * DrvDispOsMemAlloc(u32 u32Size)
{
    return malloc(u32Size);
}

void DrvDispOsMemRelease(void *pPtr)
{
    free(pPtr);
}

