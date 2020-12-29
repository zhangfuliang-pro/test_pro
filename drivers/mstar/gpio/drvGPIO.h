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

#ifndef __DRVGPIO_H__
#define __DRVGPIO_H__


#ifdef __cplusplus
extern "C"
{
#endif

#include "MsTypes.h"


typedef enum _GPIO_DbgLv
{
    E_GPIO_DBGLV_NONE,                  //no debug message
    E_GPIO_DBGLV_ERR_ONLY,              //show error only
    E_GPIO_DBGLV_REG_DUMP,              //show error & reg dump
    E_GPIO_DBGLV_INFO,                  //show error & informaiton
    E_GPIO_DBGLV_ALL                    //show error, information & funciton name
}GPIO_DbgLv;

typedef enum _GPIO_Result
{
    E_GPIO_NOT_SUPPORT = -1,
    E_GPIO_FAIL = 0,
    E_GPIO_OK = 1
}GPIO_Result;


/// GPIO operations for GPIO extension or IIC implmentation
struct gpio_operations
{
    void (*set_high) (MS_GPIO_NUM gpio);    ///< output high
    void (*set_low)  (MS_GPIO_NUM gpio);    ///< output low
    void (*set_input)(MS_GPIO_NUM gpio);    ///< set to input
    void (*set_output)(MS_GPIO_NUM gpio);   ///< set to output
    int (*get_inout)(MS_GPIO_NUM gpio);     ///< get in or out
    int (*get_level)(MS_GPIO_NUM gpio);     ///< get level
};

void MDrv_GPIO_Pad_Set(MS_GPIO_NUM gpio);
void mdrv_gpio_set_high(MS_GPIO_NUM gpio);
void mdrv_gpio_set_low(MS_GPIO_NUM gpio);
void mdrv_gpio_set_input(MS_GPIO_NUM gpio);
void mdrv_gpio_set_output(MS_GPIO_NUM gpio);
int mdrv_gpio_get_inout(MS_GPIO_NUM gpio);
int mdrv_gpio_get_level(MS_GPIO_NUM gpio);
void MDrv_GPIO_Pad_Odn(MS_GPIO_NUM u32IndexGPIO);
void MDrv_GPIO_Pad_Oen(MS_GPIO_NUM u32IndexGPIO);
void MDrv_GPIO_Pull_High(MS_GPIO_NUM u32IndexGPIO);
void MDrv_GPIO_Pull_Low(MS_GPIO_NUM u32IndexGPIO);
unsigned char MDrv_GPIO_Pad_Read(MS_GPIO_NUM u32IndexGPIO);


#ifdef __cplusplus
}
#endif

#endif /* __DRVGPIO_H__ */
