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

#ifndef _REG_SPINAND_H_
#define _REG_SPINAND_H_
//	#include "asm/arch/mach/platform.h"

//-------------------------------------------------------------------------------------------------
//  Hardware Capability
//-------------------------------------------------------------------------------------------------

// !!! Uranus Serial Flash Notes: !!!
//  - The clock of DMA & Read via XIU operations must be < 3*CPU clock
//  - The clock of DMA & Read via XIU operations are determined by only REG_ISP_CLK_SRC; other operations by REG_ISP_CLK_SRC only
//  - DMA program can't run on DRAM, but in flash ONLY
//  - DMA from SPI to DRAM => size/DRAM start/DRAM end must be 8-B aligned


//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------

#define REG(Reg_Addr)               (*(volatile U16*)(Reg_Addr))
#define REG_OFFSET_SHIFT_BITS       2
#define GET_REG_ADDRESS(x, y)          (x+((y)<<REG_OFFSET_SHIFT_BITS))

// BASEADDR & BK
//------------------------------
#define RIU_PM_BASE                         0x1F000000
#define RIU_BASE                            0x1F200000
//#define BASE_REG_ISP_ADDR			GET_BASE_ADDR_BY_BANK(IO_ADDRESS(MS_BASE_REG_RIU_PA), 0x000800)
//#define BASE_REG_FSP_ADDR			GET_BASE_ADDR_BY_BANK(IO_ADDRESS(MS_BASE_REG_RIU_PA), 0x001600)
//#define BASE_REG_QSPI_ADDR			GET_BASE_ADDR_BY_BANK(IO_ADDRESS(MS_BASE_REG_RIU_PA), 0x001700)
//#define BASE_REG_CHIPTOP_ADDR		GET_BASE_ADDR_BY_BANK(IO_ADDRESS(MS_BASE_REG_RIU_PA), 0x101E00)
//#define BASE_REG_BDMACh0_ADDR	    GET_BASE_ADDR_BY_BANK(IO_ADDRESS(MS_BASE_REG_RIU_PA), 0x100200)

#define BK_ISP                              0x1000
#define BK_FSP                              0x2C00
#define BK_QSPI                             0x2E00
#define BK_PMSLP                            0x1C00
#define BK_CLK0                             0x1600//TBD
#define BK_BDMA                             0x1200
#define BK_CHIP                             0x3C00
//#define FSP_REG_BASE_ADDR                   GET_REG_ADDR(RIU_BASE, BK_FSP)
//#define QSPI_REG_BASE_ADDR                  GET_REG_ADDR(RIU_BASE, BK_QSPI)
//#define PMSLP_REG_BASE_ADDR                 GET_REG_ADDR(RIU_BASE, BK_PMSLP)
//#define CLK0_REG_BASE_ADDR                  GET_REG_ADDR(RIU_BASE, BK_CLK0)
//#define BDMA_REG_BASE_ADDR                  GET_REG_ADDR(RIU_BASE, BK_BDMA)
//#define CHIP_REG_BASE_ADDR                  GET_REG_ADDR(RIU_BASE, BK_CHIP)

#define REG_BANK_TIMER                      (0x1800)
#define TIMER_REG_BASE_ADDR                 GET_REG_ADDRESS(RIU_PM_BASE, REG_BANK_TIMER)
#define TIMER1_ENABLE                       GET_REG_ADDRESS(TIMER_REG_BASE_ADDR, 0x20)
#define TIMER1_HIT                          GET_REG_ADDRESS(TIMER_REG_BASE_ADDR, 0x21)
#define TIMER1_MAX_LOW                      GET_REG_ADDRESS(TIMER_REG_BASE_ADDR, 0x22)
#define TIMER1_MAX_HIGH                     GET_REG_ADDRESS(TIMER_REG_BASE_ADDR, 0x23)
#define TIMER1_CAP_LOW                      GET_REG_ADDRESS(TIMER_REG_BASE_ADDR, 0x24)
#define TIMER1_CAP_HIGH                     GET_REG_ADDRESS(TIMER_REG_BASE_ADDR, 0x25)

//----- Chip flash -------------------------
#include"../drvSPINAND_reg.h"
#endif // _REG_SPINAND_H_
