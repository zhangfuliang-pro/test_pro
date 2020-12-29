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

#ifndef __SPINAND_CONFIG_H__
#define __SPINAND_CONFIG_H__

//=====================================================
// select a HW platform:
//   - 1: enable, 0: disable.
//   - only one platform can be 1, others have to be 0.
//=====================================================
#define SPINAND_DRV_TV_MBOOT           1


//=====================================================
// do NOT edit the following content.
//=====================================================
#include <config.h>
#include "../MsTypes.h"

#if defined(SPINAND_DRV_TV_MBOOT) && SPINAND_DRV_TV_MBOOT
  #include <config.h>
#else
  #error "Error! no platform selected."
#endif
//	extern void flush_cache(U32 start_addr, U32 size);

#include "drvSPINAND_uboot.h"



#endif /* __UNFD_CONFIG_H__ */
