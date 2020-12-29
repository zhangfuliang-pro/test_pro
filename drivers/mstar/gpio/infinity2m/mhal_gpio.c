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

#ifndef _MHAL_GPIO_C_
#define _MHAL_GPIO_C_


#include <common.h>
#include <command.h>
#include <MsDebug.h>

#include "mhal_gpio.h"
#include "padmux.h"

//-------------------------------------------------------------------------------------------------
//  Local Defines
//-------------------------------------------------------------------------------------------------
///#define GPIO_HAL_ERR(x, args...)        //{printf(x, ##args);}
//#define GPIO_HAL_NOTSUPPORT()           {printf("%s not support!\n", __FUNCTION__);}

#ifndef MS_ASSERT
#define MS_ASSERT(expr)                 do {                                                        \
                                            if(!(expr))                                             \
                                                printf("MVD assert fail %s %d!\n", __FILE__, __LINE__); \
                                        } while(0)
#endif

//PADTOP
#include "GPIO_TABLE.ci"

//  reg Defines
U32 gChipBaseAddr    = 0xFD203C00;
U32 gPmSleepBaseAddr = 0xFD001C00;
U32 gSarBaseAddr     = 0xFD002800;
U32 gRIUBaseAddr     = 0xFD000000;

#define MHal_CHIPTOP_REG(addr)  (*(volatile U8*)(gChipBaseAddr + (((addr) & ~1)<<1) + (addr & 1)))
#define MHal_PM_SLEEP_REG(addr) (*(volatile U8*)(gPmSleepBaseAddr + (((addr) & ~1)<<1) + (addr & 1)))
#define MHal_SAR_GPIO_REG(addr) (*(volatile U8*)(gSarBaseAddr + (((addr) & ~1)<<1) + (addr & 1)))
#define MHal_RIU_REG(addr)      (*(volatile U8*)(gRIUBaseAddr + (((addr) & ~1)<<1) + (addr & 1)))

#define REG_ALL_PAD_IN     0xA1

//-------------------------------------------------------------------------------------------------
//  Global Functions
//-------------------------------------------------------------------------------------------------

void MHal_GPIO_Init(void)
{
    MHal_CHIPTOP_REG(REG_ALL_PAD_IN) &= ~BIT7;
}

void MHal_GPIO_Pad_Set(MS_GPIO_NUM u32IndexGPIO)
{
    if (u32IndexGPIO >= 0 && u32IndexGPIO < END_GPIO_NUM)
    {
        UBOOT_INFO("gpio debug %s:%d\n", __FUNCTION__, __LINE__);
    	HalPadSetVal(u32IndexGPIO, PINMUX_FOR_GPIO_MODE);
    }
    else
    {
        MS_ASSERT(0);
    }
}

void MHal_GPIO_Pad_Oen(MS_GPIO_NUM u32IndexGPIO)
{
    if (u32IndexGPIO >= 0 && u32IndexGPIO < END_GPIO_NUM)
    {
        MHal_RIU_REG(gpio_table[u32IndexGPIO].r_oen) &= (~gpio_table[u32IndexGPIO].m_oen);
    }
    else
    {
        MS_ASSERT(0);
    }
}

void MHal_GPIO_Pad_Odn(MS_GPIO_NUM u32IndexGPIO)
{
    if (u32IndexGPIO >= 0 && u32IndexGPIO < END_GPIO_NUM)
    {
        MHal_RIU_REG(gpio_table[u32IndexGPIO].r_oen) |= gpio_table[u32IndexGPIO].m_oen;
    }
    else
    {
        MS_ASSERT(0);
    }
}

int MHal_GPIO_Pad_Level(MS_GPIO_NUM u32IndexGPIO)
{
    if (u32IndexGPIO >= 0 && u32IndexGPIO < END_GPIO_NUM)
    {
        return ((MHal_RIU_REG(gpio_table[u32IndexGPIO].r_in)&gpio_table[u32IndexGPIO].m_in)? 1 : 0);
    }
    else
    {
        MS_ASSERT(0);
        return 0;
    }
}

U8 MHal_GPIO_Pad_InOut(MS_GPIO_NUM u32IndexGPIO)
{
    if (u32IndexGPIO >= 0 && u32IndexGPIO < END_GPIO_NUM)
    {
        return ((MHal_RIU_REG(gpio_table[u32IndexGPIO].r_oen)&gpio_table[u32IndexGPIO].m_oen)? 1 : 0);
    }
    else
    {
        MS_ASSERT(0);
        return 0;
    }
}

void MHal_GPIO_Pull_High(MS_GPIO_NUM u32IndexGPIO)
{
    if (u32IndexGPIO >= 0 && u32IndexGPIO < END_GPIO_NUM)
    {
        MHal_RIU_REG(gpio_table[u32IndexGPIO].r_out) |= gpio_table[u32IndexGPIO].m_out;
    }
    else
    {
        MS_ASSERT(0);
    }
}

void MHal_GPIO_Pull_Low(MS_GPIO_NUM u32IndexGPIO)
{
    if (u32IndexGPIO >= 0 && u32IndexGPIO < END_GPIO_NUM)
    {
        MHal_RIU_REG(gpio_table[u32IndexGPIO].r_out) &= (~gpio_table[u32IndexGPIO].m_out);
    }
    else
    {
        MS_ASSERT(0);
    }
}

void MHal_GPIO_Set_High(MS_GPIO_NUM u32IndexGPIO)
{
    if (u32IndexGPIO >= 0 && u32IndexGPIO < END_GPIO_NUM)
    {
        MHal_RIU_REG(gpio_table[u32IndexGPIO].r_oen) &= (~gpio_table[u32IndexGPIO].m_oen);
        MHal_RIU_REG(gpio_table[u32IndexGPIO].r_out) |= gpio_table[u32IndexGPIO].m_out;
    }
    else
    {
        MS_ASSERT(0);
    }
}

void MHal_GPIO_Set_Low(MS_GPIO_NUM u32IndexGPIO)
{
    if (u32IndexGPIO >= 0 && u32IndexGPIO < END_GPIO_NUM)
    {
        MHal_RIU_REG(gpio_table[u32IndexGPIO].r_oen) &= (~gpio_table[u32IndexGPIO].m_oen);
        MHal_RIU_REG(gpio_table[u32IndexGPIO].r_out) &= (~gpio_table[u32IndexGPIO].m_out);
    }
    else
    {
        MS_ASSERT(0);
    }
}

void MHal_GPIO_Set_Input(MS_GPIO_NUM u32IndexGPIO)
{
    if (u32IndexGPIO >= 0 && u32IndexGPIO < END_GPIO_NUM)
    {
        MHal_RIU_REG(gpio_table[u32IndexGPIO].r_oen) |= (gpio_table[u32IndexGPIO].m_oen);
    }
    else
    {
        MS_ASSERT(0);
    }
}

void MHal_GPIO_Set_Output(MS_GPIO_NUM u32IndexGPIO)
{
    if (u32IndexGPIO >= 0 && u32IndexGPIO < END_GPIO_NUM)
    {
        MHal_RIU_REG(gpio_table[u32IndexGPIO].r_oen) &= (gpio_table[u32IndexGPIO].m_oen);
    }
    else
    {
        MS_ASSERT(0);
    }
}

int MHal_GPIO_Get_InOut(MS_GPIO_NUM u32IndexGPIO)
{
    if (u32IndexGPIO >= 0 && u32IndexGPIO < END_GPIO_NUM)
    {
        return ((MHal_RIU_REG(gpio_table[u32IndexGPIO].r_oen)&gpio_table[u32IndexGPIO].m_oen)? 1 : 0);
    }
    else
    {
        MS_ASSERT(0);
        return 0;
    }
}

#endif //_MHAL_GPIO_C_
