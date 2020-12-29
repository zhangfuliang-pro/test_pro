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


/*
 * The Watchdog Timer Mode Register can be only written to once. If the
 * timeout need to be set from U-Boot, be sure that the bootstrap doesn't
 * write to this register. Inform Linux to it too
 */

#include <common.h>
#include <watchdog.h>
#include "environment.h"
#include "asm/arch/mach/ms_types.h"
#include "asm/arch/mach/platform.h"
#include "asm/arch/mach/io.h"
#include "ms_version.h"


/* Hardware timeout in seconds */
#define WDT_HW_TIMEOUT 60

void hw_watchdog_disable(void)
{
	OUTREG16(GET_REG_ADDR(REG_ADDR_BASE_WDT, WDT_MAX_PRD_H), (((CONFIG_WDT_CLOCK * WDT_HW_TIMEOUT)>>16) & 0x0));
    OUTREG16(GET_REG_ADDR(REG_ADDR_BASE_WDT, WDT_MAX_PRD_L), ((CONFIG_WDT_CLOCK * WDT_HW_TIMEOUT) & 0x0));
}


void hw_watchdog_reset(void)
{
	OUTREG16(GET_REG_ADDR(REG_ADDR_BASE_WDT, WDT_WDT_CLR), 0x1); //clear
}

void hw_watchdog_init(void)
{
	printf("[WDT] Enalbe WATCHDOG 60s\n");
	OUTREG16(GET_REG_ADDR(REG_ADDR_BASE_WDT, WDT_MAX_PRD_H), (((CONFIG_WDT_CLOCK * WDT_HW_TIMEOUT)>>16) & 0xFFFF));
    OUTREG16(GET_REG_ADDR(REG_ADDR_BASE_WDT, WDT_MAX_PRD_L), ((CONFIG_WDT_CLOCK * WDT_HW_TIMEOUT) & 0xFFFF));
	hw_watchdog_reset();
}


