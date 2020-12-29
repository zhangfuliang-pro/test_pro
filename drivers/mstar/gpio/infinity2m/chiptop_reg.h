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

#ifndef ___CHIPTOP_H
#define ___CHIPTOP_H

#define REG_FUART_MODE                  0x03
	#define REG_FUART_MODE_MASK             BIT0|BIT1|BIT2
#define REG_UART0_MODE                  0x03
	#define REG_UART0_MODE_MASK             BIT4|BIT5|BIT6
#define REG_UART1_MODE                  0x03
	#define REG_UART1_MODE_MASK             BIT8|BIT9|BIT10
#define REG_UART2_MODE                  0x03
	#define REG_UART2_MODE_MASK             BIT12|BIT13|BIT14
#define REG_PWM0_MODE                   0x07
	#define REG_PWM0_MODE_MASK              BIT0|BIT1|BIT2
#define REG_PWM1_MODE                   0x07
	#define REG_PWM1_MODE_MASK              BIT3|BIT4|BIT5
#define REG_PWM2_MODE                   0x07
	#define REG_PWM2_MODE_MASK              BIT6|BIT7|BIT8
#define REG_PWM3_MODE                   0x07
	#define REG_PWM3_MODE_MASK              BIT9|BIT10|BIT11
#define REG_SDIO_MODE                   0x08
	#define REG_SDIO_MODE_MASK              BIT8|BIT9
#define REG_I2C0_MODE                   0x09
	#define REG_I2C0_MODE_MASK              BIT0|BIT1|BIT2
#define REG_I2C1_MODE                   0x09
	#define REG_I2C1_MODE_MASK              BIT4|BIT5|BIT6
#define REG_IDAC_MODE                   0x0a
	#define REG_IDAC_MODE_MASK              BIT0
#define REG_PM_SPICZ2_MODE              0x0a
	#define REG_PM_SPICZ2_MODE_MASK         BIT4|BIT5
#define REG_SATA_LED_MODE               0x0b
	#define REG_SATA_LED_MODE_MASK          BIT0
#define REG_SPI0_MODE                   0x0c
	#define REG_SPI0_MODE_MASK              BIT0|BIT1|BIT2
#define REG_BT1120_MODE                 0x0d
	#define REG_BT1120_MODE_MASK            BIT0|BIT1
#define REG_TTL_MODE                    0x0d
	#define REG_TTL_MODE_MASK               BIT8|BIT9|BIT10|BIT11
#define REG_TX_MIPI_MODE                0x0d
	#define REG_TX_MIPI_MODE_MASK           BIT12|BIT13
#define REG_ETH0_MODE                   0x0e
	#define REG_ETH0_MODE_MASK              BIT0
#define REG_ETH1_MODE                   0x0e
	#define REG_ETH1_MODE_MASK              BIT8|BIT9|BIT10|BIT11
#define REG_EJ_MODE                     0x0f
	#define REG_EJ_MODE_MASK                BIT0|BIT1
#define REG_DMIC_MODE                   0x0f
	#define REG_DMIC_MODE_MASK              BIT8|BIT9|BIT10
#define REG_I2S_MODE                    0x0f
	#define REG_I2S_MODE_MASK               BIT12|BIT13
#define REG_TEST_IN_MODE                0x12
	#define REG_TEST_IN_MODE_MASK           BIT0|BIT1
#define REG_TEST_OUT_MODE               0x12
	#define REG_TEST_OUT_MODE_MASK          BIT4|BIT5

#endif
