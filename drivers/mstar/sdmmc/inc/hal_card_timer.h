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

#ifndef __HAL_CARD_TIMER_H
#define __HAL_CARD_TIMER_H

#include "hal_card_regs.h"

//###########################################################################################################
#if (D_OS == D_OS__LINUX)
//###########################################################################################################
#include <linux/delay.h>
#include <linux/time.h>
//###########################################################################################################
#endif

U32_T Hal_Timer_mDelay(U32_T u32_msec);
U32_T Hal_Timer_uDelay(U32_T u32_usec);


#endif //End of __HAL_CARD_TIMER_H
