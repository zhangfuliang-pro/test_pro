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


//****************************************************
// Drive Chip           : I2M
// Excel CodeGen Version: 1.05
// Excel SW      Version: 1.01
// Excel update date    : 2019/2/18 12:46
//****************************************************

#ifndef _HAL_DISP_VGA_TIMING_TBL_C_
#define _HAL_DISP_VGA_TIMING_TBL_C_

#include "hal_disp_vga_timing_tbl.h" 

//****************************************************
// INIT_HDMITX_ATOP
//****************************************************
u8 ST_INIT_HDMITX_ATOP_COMMON_TBL[INIT_HDMITX_ATOP_COMMON_REG_NUM][REG_ADDR_SIZE + REG_MASK_SIZE + REG_DATA_SIZE] =
{
 { DRV_REG(REG_CLKGEN_53_L), 0xFF, 0x00,
 },
 { DRV_REG(REG_HDMITX_ATOP_16_L), 0xFF, 0xf0,
 },
 { DRV_REG(REG_HDMITX_ATOP_16_H), 0xFF, 0x00,
 },
 { DRV_REG(REG_HDMITX_ATOP_17_L), 0xFF, 0x08,
 },
 { DRV_REG(REG_HDMITX_ATOP_20_L), 0xFF, 0x00,
 },
 { DRV_REG(REG_HDMITX_ATOP_20_H), 0xFF, 0x00,
 },
 { DRV_REG(REG_HDMITX_ATOP_21_L), 0xFF, 0x00,
 },
 { DRV_REG(REG_HDMITX_ATOP_21_H), 0xFF, 0x00,
 },
 { DRV_REG(REG_HDMITX_ATOP_22_L), 0xFF, 0x14,
 },
 { DRV_REG(REG_HDMITX_ATOP_22_H), 0xFF, 0x14,
 },
 { DRV_REG(REG_HDMITX_ATOP_23_L), 0xFF, 0x14,
 },
 { DRV_REG(REG_HDMITX_ATOP_23_H), 0xFF, 0x14,
 },
 { DRV_REG(REG_HDMITX_ATOP_24_L), 0xFF, 0x00,
 },
 { DRV_REG(REG_HDMITX_ATOP_24_H), 0xFF, 0x00,
 },
 { DRV_REG(REG_HDMITX_ATOP_25_L), 0xFF, 0x00,
 },
 { DRV_REG(REG_HDMITX_ATOP_25_H), 0xFF, 0x00,
 },
 { DRV_REG(REG_HDMITX_ATOP_2C_L), 0xFF, 0x0f,
 },
 { DRV_REG(REG_HDMITX_ATOP_30_L), 0xFF, 0x0f,
 },
 { DRV_REG(REG_HDMITX_ATOP_30_H), 0xFF, 0x0f,
 },
 { DRV_REG(REG_HDMITX_ATOP_31_L), 0xFF, 0x0f,
 },
 { DRV_REG(REG_HDMITX_ATOP_31_H), 0xFF, 0x0f,
 },
 { DRV_REG(REG_HDMITX_ATOP_32_L), 0xFF, 0x0f,
 },
 { DRV_REG(REG_HDMITX_ATOP_32_H), 0xFF, 0x00,
 },
 { DRV_REG(REG_HDMITX_ATOP_33_L), 0xFF, 0x00,
 },
 { DRV_REG(REG_HDMITX_ATOP_34_L), 0xFF, 0x00,
 },
 { DRV_REG(REG_HDMITX_ATOP_35_L), 0xFF, 0x00,
 },
 { DRV_REG(REG_HDMITX_ATOP_39_L), 0xFF, 0x33,
 },
 { DRV_REG(REG_HDMITX_ATOP_39_H), 0xFF, 0x03,
 },
 { DRV_REG(REG_HDMITX_ATOP_3B_L), 0xFF, 0x22,
 },
 { DRV_REG(REG_HDMITX_ATOP_3B_H), 0xFF, 0x22,
 },
 { DRV_REG(REG_HDMITX_ATOP_00_L), 0xFF, 0x00,
 },
 { DRV_REG(REG_HDMITX_ATOP_1C_L), 0xFF, 0x01,
 },
 { DRV_REG(REG_HDMITX_ATOP_1C_H), 0xFF, 0x05,
 },
};

u8 ST_INIT_HDMITX_ATOP_TBL[INIT_HDMITX_ATOP_REG_NUM][REG_ADDR_SIZE + REG_MASK_SIZE + HAL_DISP_VGA_ID_NUM]=
{
 { DRV_REG(REG_HDMITX_ATOP_06_L), 0xFF, 0xc2, /*480_60P*/
                    0x6a, /*720_50P*/
                    0x68, /*720_60P*/
                    0x6a, /*1080_30P*/
                    0x6a, /*1080_50P*/
                    0x6a, /*1080_60P*/
                    0x1d, /*1024x768_60P*/
                    0xba, /*1280x800_60P*/
                    0x83, /*1280x1024_60P*/
                    0xcb, /*1366x768_60P*/
                    0xe4, /*1440x900_60P*/
                    0xe1, /*1680x1050_60P*/
                    0xa3, /*1600x1200_60P*/
 },
 { DRV_REG(REG_HDMITX_ATOP_06_H), 0xFF, 0x01, /*480_60P*/
                    0x02, /*720_50P*/
                    0x02, /*720_60P*/
                    0x02, /*1080_30P*/
                    0x02, /*1080_50P*/
                    0x02, /*1080_60P*/
                    0x02, /*1024x768_60P*/
                    0x02, /*1280x800_60P*/
                    0x03, /*1280x1024_60P*/
                    0x02, /*1366x768_60P*/
                    0x02, /*1440x900_60P*/
                    0x03, /*1680x1050_60P*/
                    0x02, /*1600x1200_60P*/
 },
 { DRV_REG(REG_HDMITX_ATOP_05_L), 0xFF, 0xec, /*480_60P*/
                    0xc8, /*720_50P*/
                    0xd2, /*720_60P*/
                    0xc8, /*1080_30P*/
                    0xc8, /*1080_50P*/
                    0xc8, /*1080_60P*/
                    0x8c, /*1024x768_60P*/
                    0x8a, /*1280x800_60P*/
                    0xbc, /*1280x1024_60P*/
                    0x53, /*1366x768_60P*/
                    0x08, /*1440x900_60P*/
                    0x3d, /*1680x1050_60P*/
                    0xda, /*1600x1200_60P*/
 },
 { DRV_REG(REG_HDMITX_ATOP_05_H), 0xFF, 0x0a, /*480_60P*/
                    0x05, /*720_50P*/
                    0x05, /*720_60P*/
                    0x05, /*1080_30P*/
                    0x05, /*1080_50P*/
                    0x05, /*1080_60P*/
                    0x07, /*1024x768_60P*/
                    0x04, /*1280x800_60P*/
                    0x02, /*1280x1024_60P*/
                    0x04, /*1366x768_60P*/
                    0x04, /*1440x900_60P*/
                    0x02, /*1680x1050_60P*/
                    0x04, /*1600x1200_60P*/
 },
 { DRV_REG(REG_HDMITX_ATOP_1D_L), 0xFF, 0x13, /*480_60P*/
                    0x12, /*720_50P*/
                    0x12, /*720_60P*/
                    0x12, /*1080_30P*/
                    0x11, /*1080_50P*/
                    0x11, /*1080_60P*/
                    0x12, /*1024x768_60P*/
                    0x12, /*1280x800_60P*/
                    0x12, /*1280x1024_60P*/
                    0x12, /*1366x768_60P*/
                    0x12, /*1440x900_60P*/
                    0x12, /*1680x1050_60P*/
                    0x11, /*1600x1200_60P*/
 },
};

//****************************************************
// INIT_IDAC_ATOP
//****************************************************
u8 ST_INIT_IDAC_ATOP_COMMON_TBL[INIT_IDAC_ATOP_COMMON_REG_NUM][REG_ADDR_SIZE + REG_MASK_SIZE + REG_DATA_SIZE] =
{
 { DRV_REG(REG_DAC_ATOP_34_L), 0xFF, 0x02,
 },
 { DRV_REG(REG_DAC_ATOP_35_L), 0xFF, 0x00,
 },
 { DRV_REG(REG_DAC_ATOP_15_L), 0xFF, 0x07,
 },
 { DRV_REG(REG_DAC_ATOP_16_L), 0xFF, 0x01,
 },
 { DRV_REG(REG_DAC_ATOP_1F_L), 0xFF, 0x00,
 },
 { DRV_REG(REG_DAC_ATOP_00_L), 0xFF, 0x00,
 },
};

u8 ST_INIT_IDAC_ATOP_TBL[INIT_IDAC_ATOP_REG_NUM][REG_ADDR_SIZE + REG_MASK_SIZE + HAL_DISP_VGA_ID_NUM]=
{
 { DRV_REG(REG_DAC_ATOP_33_L), 0xFF, 0x00, /*480_60P*/
                    0x00, /*720_50P*/
                    0x00, /*720_60P*/
                    0x00, /*1080_30P*/
                    0x00, /*1080_50P*/
                    0x00, /*1080_60P*/
                    0x00, /*1024x768_60P*/
                    0x00, /*1280x800_60P*/
                    0x01, /*1280x1024_60P*/
                    0x00, /*1366x768_60P*/
                    0x00, /*1440x900_60P*/
                    0x00, /*1680x1050_60P*/
                    0x00, /*1600x1200_60P*/
 },
 { DRV_REG(REG_DAC_ATOP_37_L), 0xFF, 0x04, /*480_60P*/
                    0x02, /*720_50P*/
                    0x02, /*720_60P*/
                    0x02, /*1080_30P*/
                    0x01, /*1080_50P*/
                    0x01, /*1080_60P*/
                    0x02, /*1024x768_60P*/
                    0x02, /*1280x800_60P*/
                    0x01, /*1280x1024_60P*/
                    0x02, /*1366x768_60P*/
                    0x02, /*1440x900_60P*/
                    0x02, /*1680x1050_60P*/
                    0x01, /*1600x1200_60P*/
 },
};

//****************************************************
// INIT_SCALER_CTRL
//****************************************************
u8 ST_INIT_SCALER_CTRL_COMMON_TBL[INIT_SCALER_CTRL_COMMON_REG_NUM][REG_ADDR_SIZE + REG_MASK_SIZE + REG_DATA_SIZE] =
{
 { DRV_REG(REG_SC_GP_CTRL_35_L), 0xFF, 0x00,
 },
 { DRV_REG(REG_SC_GP_CTRL_36_L), 0xFF, 0x00,
 },
 { DRV_REG(REG_DISP__TOP_15_L), 0xFF, 0x01,
 },
};

u8 ST_INIT_SCALER_CTRL_TBL[INIT_SCALER_CTRL_REG_NUM][REG_ADDR_SIZE + REG_MASK_SIZE + HAL_DISP_VGA_ID_NUM]=
{
 { DRV_REG(REG_DISP__TOP_10_L), 0xFF, 0x00, /*480_60P*/
                    0xa2, /*720_50P*/
                    0xe4, /*720_60P*/
                    0xa2, /*1080_30P*/
                    0xa2, /*1080_50P*/
                    0xa2, /*1080_60P*/
                    0x52, /*1024x768_60P*/
                    0x25, /*1280x800_60P*/
                    0xb1, /*1280x1024_60P*/
                    0x7e, /*1366x768_60P*/
                    0x7b, /*1440x900_60P*/
                    0x4a, /*1680x1050_60P*/
                    0xaa, /*1600x1200_60P*/
 },
 { DRV_REG(REG_DISP__TOP_10_H), 0xFF, 0x00, /*480_60P*/
                    0x8b, /*720_50P*/
                    0xb3, /*720_60P*/
                    0x8b, /*1080_30P*/
                    0x8b, /*1080_50P*/
                    0x8b, /*1080_60P*/
                    0x2b, /*1024x768_60P*/
                    0x42, /*1280x800_60P*/
                    0x02, /*1280x1024_60P*/
                    0x47, /*1366x768_60P*/
                    0xe0, /*1440x900_60P*/
                    0xfc, /*1680x1050_60P*/
                    0xaa, /*1600x1200_60P*/
 },
 { DRV_REG(REG_DISP__TOP_11_L), 0xFF, 0x40, /*480_60P*/
                    0x2e, /*720_50P*/
                    0x2e, /*720_60P*/
                    0x2e, /*1080_30P*/
                    0x2e, /*1080_50P*/
                    0x2e, /*1080_60P*/
                    0x35, /*1024x768_60P*/
                    0x29, /*1280x800_60P*/
                    0x20, /*1280x1024_60P*/
                    0x28, /*1366x768_60P*/
                    0x26, /*1440x900_60P*/
                    0x1c, /*1680x1050_60P*/
                    0x2a, /*1600x1200_60P*/
 },
 { DRV_REG(REG_DISP__TOP_1A_L), 0xFF, 0x4f, /*480_60P*/
                    0xa6, /*720_50P*/
                    0xc7, /*720_60P*/
                    0x63, /*1080_30P*/
                    0xd3, /*1080_50P*/
                    0x63, /*1080_60P*/
                    0xbe, /*1024x768_60P*/
                    0x02, /*1280x800_60P*/
                    0xa9, /*1280x1024_60P*/
                    0xdd, /*1366x768_60P*/
                    0xa9, /*1440x900_60P*/
                    0x38, /*1680x1050_60P*/
                    0x1b, /*1600x1200_60P*/
 },
 { DRV_REG(REG_DISP__TOP_1A_H), 0xFF, 0x09, /*480_60P*/
                    0x05, /*720_50P*/
                    0x06, /*720_60P*/
                    0x03, /*1080_30P*/
                    0x02, /*1080_50P*/
                    0x03, /*1080_60P*/
                    0x07, /*1024x768_60P*/
                    0x06, /*1280x800_60P*/
                    0x04, /*1280x1024_60P*/
                    0x05, /*1366x768_60P*/
                    0x05, /*1440x900_60P*/
                    0x04, /*1680x1050_60P*/
                    0x03, /*1600x1200_60P*/
 },
};

HAL_DISP_VGA_INFO stHAL_DISP_VGA_TIMING_TBL[HAL_DISP_VGA_TAB_NUM]=
{
    {*ST_INIT_HDMITX_ATOP_TBL,INIT_HDMITX_ATOP_REG_NUM, HAL_DISP_VGA_IP_NORMAL},
    {*ST_INIT_HDMITX_ATOP_COMMON_TBL,INIT_HDMITX_ATOP_COMMON_REG_NUM, HAL_DISP_VGA_IP_COMMON},
    {*ST_INIT_IDAC_ATOP_TBL,INIT_IDAC_ATOP_REG_NUM, HAL_DISP_VGA_IP_NORMAL},
    {*ST_INIT_IDAC_ATOP_COMMON_TBL,INIT_IDAC_ATOP_COMMON_REG_NUM, HAL_DISP_VGA_IP_COMMON},
    {*ST_INIT_SCALER_CTRL_TBL,INIT_SCALER_CTRL_REG_NUM, HAL_DISP_VGA_IP_NORMAL},
    {*ST_INIT_SCALER_CTRL_COMMON_TBL,INIT_SCALER_CTRL_COMMON_REG_NUM, HAL_DISP_VGA_IP_COMMON},
};
#endif

