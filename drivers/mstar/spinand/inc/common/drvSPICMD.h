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

#ifndef _DRV_SPICMD_H_
#define _DRV_SPICMD_H_

//	typedef enum
//	{
//	    E_SPINAND_DBGLV_NONE,    //disable all the debug message
//	    E_SPINAND_DBGLV_INFO,    //information
//	    E_SPINAND_DBGLV_NOTICE,  //normal but significant condition
//	    E_SPINAND_DBGLV_WARNING, //warning conditions
//	    E_SPINAND_DBGLV_ERR,     //error conditions
//	    E_SPINAND_DBGLV_CRIT,    //critical conditions
//	    E_SPINAND_ALERT,   //action must be taken immediately
//	    E_SPINAND_DBGLV_EMERG,   //system is unusable
//	    E_SPINAND_DBGLV_DEBUG,   //debug-level messages
//	} SPINAND_DbgLv;


/*SPINAND_FLASH_INFO_t _gtSpinandInfo;
#define SPARE_SIZE       _gtSpinandInfo.u16_SpareByteCnt
#define BLOCK_SIZE       _gtSpinandInfo.u16_BlkPageCnt
#define SECTOR_SIZE      _gtSpinandInfo.u16_SectorByteCnt
#define PAGE_SIZE_BYTE   _gtSpinandInfo.u16_PageByteCnt
#define PLANE            _gtSpinandInfo.u8PlaneCnt
#define CLKCFG           _gtSpinandInfo.u8CLKConfig
#define READ_MODE        _gtSpinandInfo.u8ReadMode
#define WRITE_MODE       _gtSpinandInfo.u8WriteMode
*/
//#define RIU_FLAG    _gtSpinandInfo.bRIURead
// SPI NAND COMMAND
#define SPI_NAND_CMD_PGRD                        0x13
#define SPI_NAND_CMD_RDID                        0x9F
#define SPI_NAND_CMD_WREN                        0x06
#define SPI_NAND_CMD_WRDIS                       0x04
#define SPI_NAND_CMD_RFC                         0x03
#define SPI_NAND_CMD_PP                          0x02
#define SPI_NAND_CMD_QPP                         0x32
#define SPI_NAND_CMD_RPL                         0x84
#define SPI_NAND_CMD_PE                          0x10
#define SPI_NAND_CMD_GF                          0x0F
#define SPI_NAND_CMD_RESET                       0xFF
#define SPI_NAND_CMD_DIESELECT                   0xC2

        #define SPI_NAND_REG_PROT                0xA0
        #define SPI_NAND_REG_FEAT                0xB0
                #define QUAD_ENABLE              1
        #define SPI_NAND_REG_STAT                0xC0
                #define SPI_NAND_STAT_OIP        (0x01 << 0)
                #define E_FAIL                   (0x01 << 2)
                #define P_FAIL                   (0x01 << 3)
                #define ECC_STATUS_PASS          (0x00 << 4)
                #define ECC_STATUS_ERR           (0x02 << 4)
                #define ECC_STATUS_BITFLIP    (0x01 << 4)
        #define SPI_NAND_REG_FUT                 0xD0
#define SPI_NAND_CMD_SF                          0x1F
#define SPI_NAND_CMD_BE                          0xD8
#define SPI_NAND_CMD_CE                          0xC7
#define SPI_NAND_ADDR_LEN                        3
#define SPI_NAND_PAGE_ADDR_LEN                   2
#define SPI_NAND_PLANE_OFFSET                    6
#define SPI_PLANE_ADDR_MASK                      0x40

#endif