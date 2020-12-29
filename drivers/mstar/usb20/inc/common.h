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

#ifndef __COMMON_H__
#define __COMMON_H__

#include <linux/string.h>
#include <config.h>
#include <usb.h>

#define __DEBUG_ON__

#if defined(__DEBUG_ON__)
	//#include <stdio.h>
	#define	MS_MSG	printf
#else
	#define	MS_MSG(fmt, ...)
#endif

/* Debuging Message Switch */
#define USB_LIB_DEBUG	1
//#define USB_LIB_BULK_DEBUG	1
#define USB_GLUE_DEBUG	1

#endif /* __COMMON_H__ */
