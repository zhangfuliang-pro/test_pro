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

#ifndef _MHAL_GPIO_H_
#define _MHAL_GPIO_H_

#ifdef __cplusplus
extern "C" {
#endif

//-------------------------------------------------------------------------------------------------
//  Header
//-------------------------------------------------------------------------------------------------
#include <MsTypes.h>
#include "gpio.h"


//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------
//#define MASK(x)     (((1<<(x##_BITS))-1) << x##_SHIFT)
//#define BIT(_bit_)                  (1 << (_bit_))
#define BIT_(x)                     BIT(x) //[OBSOLETED] //TODO: remove it later
#define BITS(_bits_, _val_)         ((BIT(((1)?_bits_)+1)-BIT(((0)?_bits_))) & (_val_<<((0)?_bits_)))
#define BMASK(_bits_)               (BIT(((1)?_bits_)+1)-BIT(((0)?_bits_)))

#define END_GPIO_NUM                GPIO_NR


//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------



//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------
void MHal_GPIO_Pad_Set(MS_GPIO_NUM u32IndexGPIO);
void MHal_GPIO_Set_High(MS_GPIO_NUM u32IndexGPIO);
void MHal_GPIO_Set_Low(MS_GPIO_NUM u32IndexGPIO);
void MHal_GPIO_Set_Input(MS_GPIO_NUM u32IndexGPIO);
void MHal_GPIO_Set_Output(MS_GPIO_NUM u32IndexGPIO);
int MHal_GPIO_Get_InOut(MS_GPIO_NUM u32IndexGPIO);
int MHal_GPIO_Pad_Level(MS_GPIO_NUM u32IndexGPIO);

void MHal_GPIO_Pad_Oen(MS_GPIO_NUM u32IndexGPIO);
void MHal_GPIO_Pad_Odn(MS_GPIO_NUM u32IndexGPIO);
U8 MHal_GPIO_Pad_InOut(MS_GPIO_NUM u32IndexGPIO);
void MHal_GPIO_Pull_Low(MS_GPIO_NUM u32IndexGPIO);
void MHal_GPIO_Pull_High(MS_GPIO_NUM u32IndexGPIO);


#ifdef __cplusplus
}
#endif

#endif // _MHAL_GPIO_H_
