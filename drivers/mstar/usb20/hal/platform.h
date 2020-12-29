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


#ifndef __PLATFORM_H__
#define __PLATFORM_H__
#define USBHOST_LIB_VER	"2018.01.12"

#include "MsTypes_usb.h"

/* Select a OS Platform */
//#define SERET_ENV
#define MSTAR_UBOOT_ENV

/* General Setting for Mstar Platform USB Portting */
//#ifdef SERET_ENV
//#define CONFIG_USB_STORAGE 1
//#define USB_BAD_DEVICE_RETRY_PATCH 1
/* normal 1 + additional N */
//#define USB_BAD_DEV_MAX_RETRY 2
//#endif
#define USB_WAIT_LOOP_COUNT 0 // for super speed device

/* USB Test Mode */
// #define USB_TEST
#define USB_LEGEND_DATA_TOGGLE_METHOD

/****** Chip variable setting ******/
#if 1	/* Every Mstar chip should appley it */
	#define _USB_FLUSH_BUFFER	1
#else
	#define _USB_FLUSH_BUFFER	0
#endif

//---- 1. change override to hs_txser_en condition (DM always keep high issue)
//	#define ENABLE_HS_DM_KEEP_HIGH_ECO

//---- 2. fix pv2mi bridge mis-behavior
#if 1	/* Every Mstar chip should appley it */
	#define ENABLE_PV2MI_BRIDGE_ECO
#endif

//---- 3. 240's phase as 120's clock
#if 1	/* Every Mstar chip should appley it */
	/* bit<3> for 240's phase as 120's clock set 1, bit<4> for 240Mhz in mac 0 for faraday 1 for etron */
	#define ENABLE_UTMI_240_AS_120_PHASE_ECO
	//#define UTMI_240_AS_120_PHASE_ECO_INV
#endif

//---- 4. change to 55 interface
#if 1	/* Every Mstar chip should appley it */
	#define ENABLE_UTMI_55_INTERFACE
#endif

//---- 5. enabe PVCI i_miwcplt wait for mi2uh_last_done_z
#if 1	/* Every Mstar New chip should appley it */
#define _USB_MIU_WRITE_WAIT_LAST_DONE_Z_PATCH 1
#endif

//------ UTMI disconnect level parameters ---------------------------------
// 0x00: 550mv, 0x20: 575, 0x40: 600, 0x60: 625
#define UTMI_DISCON_LEVEL_2A	(0x62)

//------ UTMI eye diagram parameters ---------------------------------
#if 0
	// for 40nm
	#define UTMI_EYE_SETTING_2C	(0x98)
	#define UTMI_EYE_SETTING_2D	(0x02)
	#define UTMI_EYE_SETTING_2E	(0x10)
	#define UTMI_EYE_SETTING_2F	(0x01)
	#define UTMI_ALL_EYE_SETTING	(0x01100298)
#elif 0
	// for 40nm after Agate, use 55nm setting7
	#define UTMI_EYE_SETTING_2C	(0x90)
	#define UTMI_EYE_SETTING_2D	(0x03)
	#define UTMI_EYE_SETTING_2E	(0x30)
	#define UTMI_EYE_SETTING_2F	(0x81)
	#define UTMI_ALL_EYE_SETTING	(0x81300390)
#elif 0
	// for 40nm after Agate, use 55nm setting6
	#define UTMI_EYE_SETTING_2C	(0x10)
	#define UTMI_EYE_SETTING_2D	(0x03)
	#define UTMI_EYE_SETTING_2E	(0x30)
	#define UTMI_EYE_SETTING_2F	(0x81)
	#define UTMI_ALL_EYE_SETTING	(0x81300310)
#elif 0
	// for 40nm after Agate, use 55nm setting5
	#define UTMI_EYE_SETTING_2C	(0x90)
	#define UTMI_EYE_SETTING_2D	(0x02)
	#define UTMI_EYE_SETTING_2E	(0x30)
	#define UTMI_EYE_SETTING_2F	(0x81)
	#define UTMI_ALL_EYE_SETTING	(0x81300290)
#elif 0
	// for 40nm after Agate, use 55nm setting4
	#define UTMI_EYE_SETTING_2C	(0x90)
	#define UTMI_EYE_SETTING_2D	(0x03)
	#define UTMI_EYE_SETTING_2E	(0x00)
	#define UTMI_EYE_SETTING_2F	(0x81)
	#define UTMI_ALL_EYE_SETTING	(0x81000390)
#elif 0
	// for 40nm after Agate, use 55nm setting3
	#define UTMI_EYE_SETTING_2C	(0x10)
	#define UTMI_EYE_SETTING_2D	(0x03)
	#define UTMI_EYE_SETTING_2E	(0x00)
	#define UTMI_EYE_SETTING_2F	(0x81)
	#define UTMI_ALL_EYE_SETTING	(0x81000310)
#elif 0
	// for 40nm after Agate, use 55nm setting2
	#define UTMI_EYE_SETTING_2C	(0x90)
	#define UTMI_EYE_SETTING_2D	(0x02)
	#define UTMI_EYE_SETTING_2E	(0x00)
	#define UTMI_EYE_SETTING_2F	(0x81)
	#define UTMI_ALL_EYE_SETTING	(0x81000290)
#else
	// for 40nm after Agate, use 55nm setting1, the default
	#define UTMI_EYE_SETTING_2C	(0x10)
	#define UTMI_EYE_SETTING_2D	(0x02)
	#define UTMI_EYE_SETTING_2E	(0x00)
	#define UTMI_EYE_SETTING_2F	(0x81)
	#define UTMI_ALL_EYE_SETTING	(0x81000210)
#endif

#define CONFIG_MIU0_BUSADDR 0x20000000
#define CONFIG_MIU1_BUSADDR 0xC0000000

/****** Porting environment setting ******/
#if defined(SERET_ENV)
	/* Delay Function */
	#include <timer.h>
	#define udelay(us)		udelay(us)

	/* buncing buffer enable for non cache flush API in cache enable system */
	// #define USB_BOUNCING_BUF	1
	#define readb(addr)		*((unsigned char volatile *)(addr))
	#define writeb(val, addr)	(*((unsigned char volatile *)(addr)) = (unsigned char)val)

	#define mdelay(ms)		{	MS_U32 i;		\
						for(i=0;i<ms;i++)	\
						udelay(1000);		\
					}

	#define USB_DELAY(ms)		mdelay(ms)
	#define wait_ms(ms)		mdelay(ms)
#endif

#if defined(MSTAR_UBOOT_ENV)
	extern MS_U32 MsOS_USB_VA2PA(MS_U32 addr);
	extern MS_U32 MsOS_USB_PA2KSEG0(MS_U32 addr);
	extern MS_U32 MsOS_USB_PA2KSEG1(MS_U32 addr);
	extern void Chip_Read_Memory(void);
	extern void Chip_Flush_Memory(void);
	extern void   flush_cache   (unsigned long, unsigned long);

	/* Delay Function */
	void udelay (unsigned long);

	#define readb(addr)			*((unsigned char volatile *)(addr))
	#define writeb(val, addr)	(*((unsigned char volatile *)(addr)) = (unsigned char)val)
	#define readw(addr) 		*((volatile MS_UINT16 *)(addr))
	#define writew(val, addr)	(*((volatile MS_UINT16 *)(addr)) = (MS_UINT16)val)
	#define readl(addr) 		*((volatile MS_UINT32 *)(addr))
	#define writel(val, addr)	(*((volatile MS_UINT32 *)(addr)) = (MS_UINT32)val)
/*
	#define mdelay(ms)		{	MS_U32 i;		\
						for(i=0;i<ms;i++)	\
						udelay(1000);		\
					}
*/
	#define USB_DELAY(ms)		mdelay(ms)

	#if defined(__ARM__)
		#define KSEG02KSEG1(addr)	MsOS_USB_PA2KSEG1(MsOS_USB_VA2PA((MS_U32)addr))
		#define KSEG12KSEG0(addr)	MsOS_USB_PA2KSEG0(MsOS_USB_VA2PA((MS_U32)addr))
	#else
		#define KSEG02KSEG1(addr)	((void *)((MS_U32)(addr)|0x20000000))  //cached -> unchched
		#define KSEG12KSEG0(addr)	((void *)((MS_U32)(addr)&~0x20000000)) //unchched -> cached
	#endif

	/* virtual address to physical address translation */
	#if defined(__ARM__)

		#define ENABLE_USB_NEW_MIU_SEL	1	/* Unit: 4GB / 16 = 256MB */
		#define USB_MIU_SEL0	0x70	/* MIU0: 2GB */
		#define USB_MIU_SEL1	0xF8	/* MIU1: 2GB */
		#define USB_MIU_SEL2	0xEF
		#define USB_MIU_SEL3	0xEF
		#define MIU0_BUS_BASE_ADDR	CONFIG_MIU0_BUSADDR
		#define MIU0_PHY_BASE_ADDR	0x00000000UL
		#define MIU1_BUS_BASE_ADDR	CONFIG_MIU1_BUSADDR
		#define MIU1_PHY_BASE_ADDR	0x80000000UL

		/* transmit between BUS and USB PHY Addr */
		extern unsigned int VA2PA(unsigned int u32_DMAAddr);
		extern unsigned int PA2VA(unsigned int u32_DMAAddr);
	#elif defined(__MIPS__)
		#define VA2PA(a)  (a)
		#define PA2VA(a)  (a)
	#else // ??? which CPU
		#define VA2PA(a)  ((a) & 0x1FFFFFFF)
		#define PA2VA(a)  ((a) | 0xA0000000) //// mapping to uncache address
	#endif
#endif


#endif /* __PLATFORM_H__*/
