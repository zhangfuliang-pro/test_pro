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


#ifndef _SPINAND_H_
#define _SPINAND_H_

#include "drvSPINAND.h"
#define printk	printf

#if 0
#define spi_nand_msg(fmt, ...) printk(KERN_NOTICE "SPINAND: %s: " fmt "\n", __func__, ##__VA_ARGS__)
#else
#define spi_nand_msg(fmt, ...)
#endif

#if 0
#define spi_nand_debug(fmt, ...) printk(KERN_NOTICE "SPINAND: %s: " fmt "\n", __func__, ##__VA_ARGS__)
#else
#define spi_nand_debug(fmt, ...)
#endif

#define spi_nand_warn(fmt, ...) printk(KERN_WARNING "SPINAND: %s:warning, " fmt "\n", __func__, ##__VA_ARGS__)
#define spi_nand_err(fmt, ...) printk(KERN_ERR "SPINAND: %s: " fmt "\n", __func__, ##__VA_ARGS__)

#define UNFD_LOGI_PART    0x8000 // bit-or if the partition needs Wear-Leveling
#define UNFD_HIDDEN_PART  0x4000 // bit-or if this partition is hidden, normally it is set for the LOGI PARTs.

//#define UNFD_PART_MIU			1
#define UNFD_PART_IPL_CUST      0x01
#define UNFD_PART_BOOTLOGO      0x02
#define UNFD_PART_IPL           0x03
#define UNFD_PART_OS            0x04
#define UNFD_PART_CUS           0x05
#define UNFD_PART_UBOOT         0x06
#define UNFD_PART_SECINFO       0x07
#define UNFD_PART_OTP           0x08
#define UNFD_PART_RECOVERY      0x09
#define UNFD_PART_E2PBAK        0x0A
#define UNFD_PART_NVRAMBAK      0x0B
#define UNFD_PART_NPT           0x0C
#define UNFD_PART_ENV           0x0D
#define UNFD_PART_MISC          0x0E

#define UNFD_PART_RTOS          0x10
#define UNFD_PART_RTOS_BAK      0X11
#define UNFD_PART_KERNEL        0x12
#define UNFD_PART_KERNEL_BAK    0x13

#define UNFD_PART_CIS           0x20
#define UNFD_PART_UBI           0x21

#define UNFD_PART_CUST0         0x30
#define UNFD_PART_CUST1         0x31
#define UNFD_PART_CUST2         0x32
#define UNFD_PART_CUST3         0x33
#define UNFD_PART_CUSTf         0x3F


#define CIS_DEFAULT_BACKUP 3
#define CIS_MAX_BACKUP 5
#define IPL_BACKUP 3
#define IPL_CUST_BACKUP 3
#define UBOOT_BACKUP 2
#define SBOOT_MAXBLOCK 1
#define UBOOT_MAXBLOCK 3



typedef struct
{
    U16 u16_StartBlk;		// the start block index
    U16 u16_BlkCnt;			// project team defined
    U16 u16_PartType;		// project team defined
    U16 u16_BackupBlkCnt;	// reserved good blocks count for backup, UNFD internal use.
    // e.g. u16BackupBlkCnt  = u16BlkCnt * 0.03 + 2
} PARTITION_RECORD_t;

typedef struct
{
    U32 u32_ChkSum;
    U16	u16_SpareByteCnt;
    U16	u16_PageByteCnt;
    U16	u16_BlkPageCnt;
    U16	u16_BlkCnt;
    U16 u16_PartCnt;
    U16 u16_UnitByteCnt;
    PARTITION_RECORD_t records[62];

} PARTITION_INFO_t;

typedef struct _SPI_NAND_DRIVER
{
    SPINAND_FLASH_INFO_t tSpinandInfo;

    PARTITION_INFO_t tPartInfo;
    U8 u8_HasPNI;
    U8 *pu8_pagebuf;
    U8 *pu8_sparebuf;
    U8 *pu8_statusbuf;
    U8 u8_statusRequest;
    U32 u32_column;
    U8 u8_status;
    U8  u8_SectorByteCntBits;
    U8  u8_PageSectorCntBits;
    U8  u8_PageByteCntBits;
    U8  u8_BlkPageCntBits;
    U16 u16_PageSectorCnt;
} SPI_NAND_DRIVER_t;

typedef struct
{
    U8  au8_Tag[16];
    SPINAND_FLASH_INFO_t tSpiNandInfo;
//	    U8 au8_Reserved[];

} SPINAND_FLASH_INFO_TAG_t;

#define SPINAND_FLASH_INFO_TAG "MSTARSEMIUSFDCIS"

// this definition is used to measure nand read/write speed
#define NAND_SPEED_TEST                     0
void *drvSPINAND_get_DrvContext_address(void);
U8 MDrv_SPINAND_CountBits(U32 u32_x);
extern void dump_mem(unsigned char *buf, int cnt);

#endif
