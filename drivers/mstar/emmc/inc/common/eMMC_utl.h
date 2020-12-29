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

#ifndef __eMMC_UTL_H__
#define __eMMC_UTL_H__

#include "eMMC.h"


typedef eMMC_PACK0 struct _eMMC_TEST_ALIGN_PACK {

	U8	u8_0;
	U16	u16_0;
	U32	u32_0, u32_1;

} eMMC_PACK1 eMMC_TEST_ALIGN_PACK_t;

extern  U32  eMMC_CheckAlignPack(U8 u8_AlignByteCnt);
extern void  eMMC_dump_mem(unsigned char *buf, int cnt);
extern  U32  eMMC_ComapreData(U8 *pu8_Buf0, U8 *pu8_Buf1, U32 u32_ByteCnt);
extern  U32  eMMC_ChkSum(U8 *pu8_Data, U32 u32_ByteCnt);
extern  U32  eMMC_PrintDeviceInfo(void);
extern  U32  eMMC_CompareCISTag(U8 *tag);
extern  void eMMC_dump_nni(eMMC_NNI_t *peMMCInfo);
extern  void eMMC_dump_pni(eMMC_PNI_t *pPartInfo);
#endif // __eMMC_UTL_H__
