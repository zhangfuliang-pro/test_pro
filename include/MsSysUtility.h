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

#ifndef __MS_SYS_UTILITY_H__
#define __MS_SYS_UTILITY_H__

#include <MsTypes.h>

MS_U8 ReadByte(MS_U32 u32RegAddr);
MS_U16 Read2Byte(MS_U32 u32RegAddr);
MS_BOOL WriteByte(MS_U32 u32RegAddr, MS_U8 u16Val);
MS_BOOL Write2Byte(MS_U32 u32RegAddr, MS_U16 u16Val);
MS_BOOL WriteRegBit(MS_U32 u32RegAddr, MS_U16 u8Bit, MS_BOOL bEnable);
MS_BOOL WriteRegBitPos(MS_U32 u32RegAddr, MS_U8 u8Bit, MS_BOOL bEnable);

int do_riu(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]);
int do_gpio( cmd_tbl_t * cmdtp, int flag, int argc, char * const argv[]);
int do_sar( cmd_tbl_t * cmdtp, int flag, int argc, char * const argv[]);

#endif  // __MS_SYS_UTILITY_H__

