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


#include "../inc/hal_card_regs.h"

static volatile PortEmType gePort[3];

void Hal_CREG_SET_PORT(IPEmType eIP, PortEmType ePort)
{
	gePort[eIP] = ePort;
}

volatile PortEmType Hal_CREG_GET_PORT(IPEmType eIP)
{
	return gePort[eIP];
}

volatile void* Hal_CREG_GET_REG_BANK(IPEmType eIP, U8_T u8Bank)
{
    void* pIPBANKArr[3][3] =
    {
      { (void*) (A_FCIE1_0_BANK), (void*) (A_FCIE1_1_BANK), (void*) (A_FCIE1_2_BANK) },
      { (void*) (A_FCIE2_0_BANK), (void*) (A_FCIE2_1_BANK), (void*) (A_FCIE2_2_BANK) },
      { (void*) (A_FCIE3_0_BANK), (void*) (A_FCIE3_1_BANK), (void*) (A_FCIE3_2_BANK) }
    };

	return pIPBANKArr[eIP][u8Bank];

}





