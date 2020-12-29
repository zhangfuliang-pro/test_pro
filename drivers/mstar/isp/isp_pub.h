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

#ifndef ISP_H

typedef enum { //for reg_sr_mode
  SR_PAD_CFG_1 = 1,
  SR_PAD_CFG_2 = 2,
  SR_PAD_CFG_3 = 3,
  SR_PAD_CFG_10BITS = 4,
  SR_PAD_CFG_4 = 4,
  SR_PAD_CFG_12BITS = 5,
  SR_PAD_CFG_5 = 5,
  SR_PAD_CFG_6 = 6,
}SR_PAD_CFG;

void Select_SR_IOPad(SR_PAD_CFG cfg);
void Set_SR_MCLK(u8 enable, u8 mclk_speed);
void ISP_SrPwdn(int id,int val);
void ISP_SrRst(int id,int val);

#endif
