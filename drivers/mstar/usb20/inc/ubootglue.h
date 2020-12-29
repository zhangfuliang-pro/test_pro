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

#ifndef __UBOOTGLUE_USB_H__
#define __UBOOTGLUE_USB_H__

#include <asm/types.h>
#include <usb.h>

/* Requests: bRequest << 8 | bmRequestType */
#define RH_GET_STATUS		0x0080
#define RH_CLEAR_FEATURE	0x0100
#define RH_SET_FEATURE		0x0300
#define RH_SET_ADDRESS		0x0500
#define RH_GET_DESCRIPTOR	0x0680
#define RH_SET_DESCRIPTOR	0x0700
#define RH_GET_CONFIGURATION	0x0880
#define RH_SET_CONFIGURATION	0x0900
#define RH_GET_STATE		0x0280
#define RH_GET_INTERFACE	0x0A80
#define RH_SET_INTERFACE	0x0B00
#define RH_SYNC_FRAME		0x0C80

struct xhc_comp {
	u8	port_index;
	u32	xhci_port_addr;
	u32 u3top_base;
	u32	u3phy_A_base;
	u32	u3phy_D_base;
	u32	xhci_base;
};

struct usb_hcd {
	u32	port_index;
	u32	utmi_base;
	u32	ehc_base;
	u32	usbc_base;
	u32	bc_base;
	u32	init_flag;

	int	ever_inited;

	struct xhc_comp xhci;

	//struct usb_port_status rh_status;
	struct ehci_hcd *ehci;
	u8	bSpeed;
	u32	urb_status;
	u32	total_bytes;
	int	FirstBulkOut;
	int	FirstBulkIn;
	int   FirstIntIn;
	int   IntrIn_Complete;
};

#endif /* __UBOOTGLUE_USB_H__ */
