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


#ifndef _REG_HDMITX_H_
#define _REG_HDMITX_H_


//-------------------------------------------------------------------------------------------------
//  Hardware Capability
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------
#if defined(CHIP_MV2)
#define HDMITX_DTOP_BASE                (0x000000U)
#else
#define HDMITX_DTOP_BASE                (0x112500U)
#endif

#define HDMITX_ATOP_BASE                (0x112600U)
#define HDMITX_SC_GP_CTRL_BASE          (0x113300U)
#define HDMITX_CLKGEN_BASE              (0x103800U)

#define HDMITX_MISC_REG_BASE            (0x172A00U)
#define HDMITX_HDCP_REG_BASE            (0x172B00U)

//***** Bank 172A - MISC *****//
#define REG_MISC_CONFIG_00               0x00U
#define REG_MISC_CONFIG_01               0x01U
#define REG_MISC_CONFIG_02               0x02U
#define REG_MISC_CONFIG_03               0x03U
#define REG_MISC_CONFIG_04               0x04U
#define REG_MISC_CONFIG_05               0x05U
#define REG_MISC_CONFIG_06               0x06U
#define REG_MISC_CONFIG_07               0x07U
#define REG_MISC_CONFIG_08               0x08U
#define REG_MISC_CONFIG_09               0x09U
#define REG_MISC_STATUS_0A               0x0AU
#define REG_MISC_STATUS_0B               0x0BU
#define REG_MISC_CONFIG_0C               0x0CU
#define REG_MISC_STATUS_0D               0x0DU
#define REG_MISC_STATUS_0E               0x0EU
#define REG_MISC_STATUS_0F               0x0FU
#define REG_MISC_CONFIG_17               0x17U
#define REG_MISC_CONFIG_1B               0x1BU
#define REG_MISC_CONFIG_1C               0x1CU
#define REG_MISC_CONFIG_1D               0x1DU
#define REG_MISC_CONFIG_1E               0x1EU
#define REG_MISC_CONFIG_1F               0x1FU
#define REG_MISC_CONFIG_20               0x20U
#define REG_MISC_CONFIG_21               0x21U
#define REG_MISC_CONFIG_22               0x22U
#define REG_MISC_CONFIG_23               0x23U
#define REG_MISC_CONFIG_24               0x24U
#define REG_MISC_CONFIG_25               0x25U
#define REG_MISC_CONFIG_26               0x26U
#define REG_MISC_CONFIG_27               0x27U
#define REG_MISC_CONFIG_2A               0x2AU
#define REG_MISC_CONFIG_2B               0x2BU
#define REG_MISC_CONFIG_2C               0x2CU
#define REG_MISC_CONFIG_2D               0x2DU
#define REG_MISC_CONFIG_2E               0x2EU
#define REG_MISC_CONFIG_2F               0x2FU
#define REG_MISC_CONFIG_33               0x33U
#define REG_MISC_CONFIG_34               0x34U
#define REG_MISC_CONFIG_36               0x36U
#define REG_MISC_CONFIG_38               0x38U
#define REG_MISC_CONFIG_40               0x40U
#define REG_MISC_CONFIG_41               0x41U
#define REG_MISC_CONFIG_45               0x45U
#define REG_MISC_CONFIG_48               0x48U
#define REG_MISC_CONFIG_4D               0x4DU
#define REG_MISC_CONFIG_52               0x52U
#define REG_MISC_CONFIG_58               0x58U
#define REG_MISC_CONFIG_59               0x59U
#define REG_MISC_CONFIG_5D               0x5DU


//***** Bank 172B - HDCP *****//
#define REG_HDCP_TX_RI_00               0x00U
#define REG_HDCP_TX_MODE_01             0x01U	// Pj[7:0] : 61h[7:0]; Tx_mode[7:0] : 61h[15:8]
#define REG_HDCP_TX_COMMAND_02          0x02U
#define REG_HDCP_TX_RI127_03            0x03U       // RI[15:0] 127th frame : 63[15:0]
#define REG_HDCP_TX_LN_04               0x04U	// Ln[55:0] : 64h[7:0] ~ 67h[7:0]
#define REG_HDCP_TX_LN_SEED_07          0x07U	// Ln seed[7:0] : 67h[15:8]
#define REG_HDCP_TX_AN_08               0x08U	// An[63:0] : 68[7:0] ~ 6B[15:8]
#define REG_HDCP_TX_MI_0C               0x0CU	// Mi[63:0] : 6C[7:0] ~ 6F[15:8]

// --------- BK1125 HDMIA_DTOP ---------- //
#if defined(CHIP_MV2)
#define REG_HDMITX_PD                       0x2008
    #define REG_HDMITX_PD_MSK                   0x0080
    #define REG_HDMITX_PD_EN                    0x0080

#define REG_HDMITX_MODE                     0x2004U
    #define REG_HDMITX_MODE_MSK                 0x0080
    #define REG_HDMITX_MODE_HDMI                0x0080
    #define REG_HDMITX_MODE_DVI                 0x0000


#define REG_HDMITX_AUDIO_LAYOUT             0x2004U
    #define REG_HDMITX_AUDIO_LAYOUT_MSK         0x0040
    #define REG_HDMITX_AUDIO_LAYOUT_2_CH        0x0040
    #define REG_HDMITX_AUDIO_LAYOUT_8_CH        0x0000

#define REG_HDMITX_AUIDO_SP                 0x2007U
    #define REG_HDMITX_AUDIO_SP_MSK             0x000F
    #define REG_HDMITX_AUDIO_SP_SUBPACKET_NONE  0x0000
    #define REG_HDMITX_AUDIO_SP_SUBPACKET_0     0x0001
    #define REG_HDMITX_AUDIO_SP_SUBPACKET_01    0x0003
    #define REG_HDMITX_AUDIO_SP_SUBPACKET_012   0x0007
    #define REG_HDMITX_AUDIO_SP_SUBPACKET_0123  0x000F


#define REG_HDMITX_AUIDO_SF                 0x2024U
    #define REG_HDMITX_AUDIO_SF_MSK     0x000F


#define REG_HDMITX_CH0_MUTE                 0x200AU
    #define REG_HDMITX_CH0_MUTE_MSK             0x0020
    #define REG_HDMITX_CH0_MUTE_ON              0x0020
    #define REG_HDMITX_CH0_MUTE_OFF             0x0000


#define REG_HDMITX_CH1_MUTE                 0x200AU
    #define REG_HDMITX_CH1_MUTE_MSK             0x0040
    #define REG_HDMITX_CH1_MUTE_ON              0x0040
    #define REG_HDMITX_CH1_MUTE_OFF             0x0000

#define REG_HDMITX_CH2_MUTE                 0x200AU
    #define REG_HDMITX_CH2_MUTE_MSK             0x0080
    #define REG_HDMITX_CH2_MUTE_ON              0x0080
    #define REG_HDMITX_CH2_MUTE_OFF             0x0000

#define REG_HDMITX_CSC_SEL                  0x20C0U
    #define REG_HDMITX_CSC_SEL_MSK              0x000F
    #define REG_HDMITX_CSC_SEL_422_10_TO_8      0x0001
    #define REG_HDMITX_CSC_SEL_Y_TO_R           0x0002
    #define REG_HDMITX_CSC_SEL_R_TO_Y           0x0004
    #define REG_HDMITX_CSC_SEL_444_TO_422       0x0008
    #define REG_HDMITX_CSC_SEL_BYPASS           0x0000


#define REG_HDMITX_AVMUTE                   0x2008U
    #define REG_HDMITX_AVMUTE_MSK               0x0001
    #define REG_HDMITX_AVMUTE_ON                0x0001

#define REG_HDMITX_AUDIO_MUTE              0x2008U
    #define REG_HDMITX_AUDIO_MUTE_MSK           0x0002
    #define REG_HDMITX_AUDIO_MUTE_EN            0x0002

#define REG_HDMITX_VIDEO_MUTE               0x2008U
    #define REG_HDMITX_VIDEO_MUTE_MSK           0x0004
    #define REG_HDMITX_VIDEO_MUTE_EN            0x0004


#define REG_HDMITX_DATA_PERIOD_ISLAND       0x2010U
#define REG_HDMITX_DATA_PERIOD_ISLAND_MSK   0x00FF


#define REG_HDMITX_PKT_EN                   0x2023U
    #define REG_HDMITX_PKT_SPD_MSK              0x0001
    #define REG_HDMITX_PKT_SPD_EN               0x0001
    #define REG_HDMITX_PKT_PKT0_MSK             0x0001
    #define REG_HDMITX_PKT_PKT0_EN              0x0001

    #define REG_HDMITX_PKT_VS_MSK               0x0002
    #define REG_HDMITX_PKT_VS_EN                0x0002
    #define REG_HDMITX_PKT_PKT1_MSK             0x0002
    #define REG_HDMITX_PKT_PKT1_EN              0x0002

    #define REG_HDMITX_PKT_AUDIO_MSK            0x0004
    #define REG_HDMITX_PKT_AUDIO_EN             0x0004

    #define REG_HDMITX_PKT_ACR_MSK              0x0008
    #define REG_HDMITX_PKT_ACR_EN               0x0008

    #define REG_HDMITX_PKT_ADO_MSK              0x0010
    #define REG_HDMITX_PKT_ADO_EN               0x0010

    #define REG_HDMITX_PKT_AVI_MSK              0x0020
    #define REG_HDMITX_PKT_AVI_EN               0x0020

    #define REG_HDMITX_PKT_GC_MSK               0x0040
    #define REG_HDMITX_PKT_GC_EN                0x0040

    #define REG_HDMITX_PKT_NULL_MSK             0x0080
    #define REG_HDMITX_PKT_NULL_EN              0x0080

    #define REG_HDMITX_PKT_PKT2_MSK             0x0100
    #define REG_HDMITX_PKT_PKT2_EN              0x0100


#define REG_HDMITX_ACR_MOD                      0x2022U
    #define REG_HDMITX_ACR_MOD_MSK                  0x0008
    #define REG_HDMITX_ACR_MOD_FROM_COUNTER         0x0008
    #define REG_HDMITX_ACR_MOD_FROM_REG             0x0000


#define REG_HDMITX_ACR_CTS_1                    0x202AU
    #define REG_HDMITX_ACR_CTS_1_MSK                0x00FF
    #define REG_HDMITX_ACR_CTS_1_VAL(x)             (x & 0x000FF)

#define REG_HDMITX_ACR_CTS_2                    0x2029U
    #define REG_HDMITX_ACR_CTS_2_MSK                0x00FF
    #define REG_HDMITX_ACR_CTS_2_VAL(x)             ((x & 0x0FF00)>>8)

#define REG_HDMITX_ACR_CTS_3                    0x2028U
    #define REG_HDMITX_ACR_CTS_3_MSK                0x000F
    #define REG_HDMITX_ACR_CTS_3_VAL(x)             ((x & 0xF0000)>>16)

#define REG_HDMITX_ACR_N_1                      0x202DU
    #define REG_HDMITX_ACR_N_1_MSK                  0x00FF
    #define REG_HDMITX_ACR_N_1_VAL(x)               (x & 0x000FF)

#define REG_HDMITX_ACR_N_2                      0x202CU
    #define REG_HDMITX_ACR_N_2_MSK                  0x00FF
    #define REG_HDMITX_ACR_N_2_VAL(x)               ((x &0x0FF00)>>8)

#define REG_HDMITX_ACR_N_3                      0x202BU
    #define REG_HDMITX_ACR_N_3_MSK                  0x000F
    #define REG_HDMITX_ACR_N_3_VAL(x)               ((x &0xF0000)>>16)

#define REG_HDMITX_PKT_AVI_1                    0x2030U
#define REG_HDMITX_PKT_AVI_2                    0x2030U
#define REG_HDMITX_PKT_AVI_3                    0x2032U
#define REG_HDMITX_PKT_AVI_4                    0x2032U
#define REG_HDMITX_PKT_AVI_5                    0x2034U
#define REG_HDMITX_PKT_AVI_6                    0x2034U
#define REG_HDMITX_PKT_AVI_7                    0x2036U
#define REG_HDMITX_PKT_AVI_8                    0x2037U
#define REG_HDMITX_PKT_AVI_9                    0x2037U
#define REG_HDMITX_PKT_AVI_10                   0x2039U
#define REG_HDMITX_PKT_AVI_11                   0x2039U
#define REG_HDMITX_PKT_AVI_12                   0x203BU
#define REG_HDMITX_PKT_AVI_13                   0x203BU
#define REG_HDMITX_PKT_AVI_14                   0x203DU

#define REG_HDMITX_PKT_ADO_1                    0x2040U
#define REG_HDMITX_PKT_ADO_2                    0x2040U
#define REG_HDMITX_PKT_ADO_3                    0x2042U
#define REG_HDMITX_PKT_ADO_4                    0x2042U
#define REG_HDMITX_PKT_ADO_5                    0x2044U
#define REG_HDMITX_PKT_ADO_6                    0x2044U

#define REG_HDMITX_PKT_ASP_CS_1                 0x2048U
#define REG_HDMITX_PKT_ASP_CS_2                 0x2048U
#define REG_HDMITX_PKT_ASP_CS_3                 0x204AU
#define REG_HDMITX_PKT_ASP_CS_4                 0x204AU
#define REG_HDMITX_PKT_ASP_CS_5                 0x204CU
#define REG_HDMITX_PKT_ASP_CS_6                 0x204CU
#define REG_HDMITX_PKT_ASP_CS_7                 0x204EU
#define REG_HDMITX_PKT_ASP_CS_8                 0x204EU
#define REG_HDMITX_PKT_ASP_CS_9                 0x2050U
#define REG_HDMITX_PKT_ASP_CS_10                0x2050U
#define REG_HDMITX_PKT_ASP_CS_11                0x2052U
#define REG_HDMITX_PKT_ASP_CS_12                0x2052U
#define REG_HDMITX_PKT_ASP_CS_13                0x2054U
#define REG_HDMITX_PKT_ASP_CS_14                0x2054U
#define REG_HDMITX_PKT_ASP_CS_15                0x2056U
#define REG_HDMITX_PKT_ASP_CS_16                0x2056U
#define REG_HDMITX_PKT_ASP_CS_17                0x2058U
#define REG_HDMITX_PKT_ASP_CS_18                0x2058U
#define REG_HDMITX_PKT_ASP_CS_19                0x205AU
#define REG_HDMITX_PKT_ASP_CS_20                0x205AU
#define REG_HDMITX_PKT_ASP_CS_21                0x205CU
#define REG_HDMITX_PKT_ASP_CS_22                0x205CU
#define REG_HDMITX_PKT_ASP_CS_23                0x205EU
#define REG_HDMITX_PKT_ASP_CS_24                0x205EU

#define REG_HDMITX_PKT_SPD_HEADER               0x2060U
#define REG_HDMITX_PKT_SPD_LENGTH               0x2062U
#define REG_HDMITX_PKT_SPD_1                    0x2063U
#define REG_HDMITX_PKT_SPD_2                    0x2064U
#define REG_HDMITX_PKT_SPD_3                    0x2065U
#define REG_HDMITX_PKT_SPD_4                    0x2066U
#define REG_HDMITX_PKT_SPD_5                    0x2067U
#define REG_HDMITX_PKT_SPD_6                    0x2068U
#define REG_HDMITX_PKT_SPD_7                    0x2069U
#define REG_HDMITX_PKT_SPD_8                    0x206AU
#define REG_HDMITX_PKT_SPD_9                    0x206BU
#define REG_HDMITX_PKT_SPD_10                   0x206CU
#define REG_HDMITX_PKT_SPD_11                   0x206DU
#define REG_HDMITX_PKT_SPD_12                   0x206EU
#define REG_HDMITX_PKT_SPD_13                   0x206FU
#define REG_HDMITX_PKT_SPD_14                   0x2070U
#define REG_HDMITX_PKT_SPD_15                   0x2071U
#define REG_HDMITX_PKT_SPD_16                   0x2072U
#define REG_HDMITX_PKT_SPD_17                   0x2073U
#define REG_HDMITX_PKT_SPD_18                   0x2074U
#define REG_HDMITX_PKT_SPD_19                   0x2075U
#define REG_HDMITX_PKT_SPD_20                   0x2076U
#define REG_HDMITX_PKT_SPD_21                   0x2077U
#define REG_HDMITX_PKT_SPD_22                   0x2078U
#define REG_HDMITX_PKT_SPD_23                   0x2079U
#define REG_HDMITX_PKT_SPD_24                   0x207AU
#define REG_HDMITX_PKT_SPD_25                   0x207BU
#define REG_HDMITX_PKT_SPD_DATA_LENGTH          25


#define REG_HDMITX_PKT_VS_HEADER                0x2084U
#define REG_HDMITX_PKT_VS_LENGTH                0x2086U
#define REG_HDMITX_PKT_VS_1                     0x2087U
#define REG_HDMITX_PKT_VS_2                     0x2088U
#define REG_HDMITX_PKT_VS_3                     0x2089U
#define REG_HDMITX_PKT_VS_4                     0x208AU
#define REG_HDMITX_PKT_VS_5                     0x208BU
#define REG_HDMITX_PKT_VS_6                     0x208CU
#define REG_HDMITX_PKT_VS_7                     0x208DU
#define REG_HDMITX_PKT_VS_8                     0x208EU
#define REG_HDMITX_PKT_VS_9                     0x208FU
#define REG_HDMITX_PKT_VS_10                    0x2090U
#define REG_HDMITX_PKT_VS_11                    0x2091U
#define REG_HDMITX_PKT_VS_12                    0x2092U
#define REG_HDMITX_PKT_VS_13                    0x2093U
#define REG_HDMITX_PKT_VS_14                    0x2094U
#define REG_HDMITX_PKT_VS_15                    0x2095U
#define REG_HDMITX_PKT_VS_16                    0x2096U
#define REG_HDMITX_PKT_VS_17                    0x2097U
#define REG_HDMITX_PKT_VS_18                    0x2098U
#define REG_HDMITX_PKT_VS_19                    0x2099U
#define REG_HDMITX_PKT_VS_20                    0x209AU
#define REG_HDMITX_PKT_VS_21                    0x209BU
#define REG_HDMITX_PKT_VS_22                    0x209CU
#define REG_HDMITX_PKT_VS_23                    0x209DU
#define REG_HDMITX_PKT_VS_24                    0x209EU
#define REG_HDMITX_PKT_VS_25                    0x209FU
#define REG_HDMITX_PKT_VS_26                    0x20A0U
#define REG_HDMITX_PKT_VS_27                    0x20A1U
#define REG_HDMITX_PKT_VS_DATA_LENGTH           27


#else
#define REG_HDMITX_PD                       0x00U
    #define REG_HDMITX_PD_MSK                   0x0001
    #define REG_HDMITX_PD_EN                    0x0001

#define REG_HDMITX_MODE                     0x01U
    #define REG_HDMITX_MODE_MSK                 0x0001
    #define REG_HDMITX_MODE_HDMI                0x0001
    #define REG_HDMITX_MODE_DVI                 0x0000


#define REG_HDMITX_AUDIO_LAYOUT             0x01U
    #define REG_HDMITX_AUDIO_LAYOUT_MSK         0x0002
    #define REG_HDMITX_AUDIO_LAYOUT_2_CH        0x0000
    #define REG_HDMITX_AUDIO_LAYOUT_8_CH        0x0002

#define REG_HDMITX_AUIDO_SP                 0x01U
    #define REG_HDMITX_AUDIO_SP_MSK             0x0F00
    #define REG_HDMITX_AUDIO_SP_SUBPACKET_NONE  0x0000
    #define REG_HDMITX_AUDIO_SP_SUBPACKET_0     0x0100
    #define REG_HDMITX_AUDIO_SP_SUBPACKET_01    0x0300
    #define REG_HDMITX_AUDIO_SP_SUBPACKET_012   0x0700
    #define REG_HDMITX_AUDIO_SP_SUBPACKET_0123  0x0F00


#define REG_HDMITX_AUIDO_SF                 0x20U
    #define REG_HDMITX_AUDIO_SF_MSK     0x000F


#define REG_HDMITX_AVMUTE                   0x01U
    #define REG_HDMITX_AVMUTE_MSK               0x4000
    #define REG_HDMITX_AVMUTE_ON                0x4000

#define REG_HDMITX_AUDIO_MUTE              0x01U
    #define REG_HDMITX_AUDIO_MUTE_MSK           0x1000
    #define REG_HDMITX_AUDIO_MUTE_EN            0x1000

#define REG_HDMITX_VIDEO_MUTE               0x01U
    #define REG_HDMITX_VIDEO_MUTE_MSK           0x2000
    #define REG_HDMITX_VIDEO_MUTE_EN            0x2000

#define REG_HDMITX_CH0_MUTE                 0x05U
    #define REG_HDMITX_CH0_MUTE_MSK             0x0008
    #define REG_HDMITX_CH0_MUTE_ON              0x0008
    #define REG_HDMITX_CH0_MUTE_OFF             0x0000


#define REG_HDMITX_CH1_MUTE                 0x05U
    #define REG_HDMITX_CH1_MUTE_MSK             0x0010
    #define REG_HDMITX_CH1_MUTE_ON              0x0010
    #define REG_HDMITX_CH1_MUTE_OFF             0x0000

#define REG_HDMITX_CH2_MUTE                 0x05U
    #define REG_HDMITX_CH2_MUTE_MSK             0x0020
    #define REG_HDMITX_CH2_MUTE_ON              0x0020
    #define REG_HDMITX_CH2_MUTE_OFF             0x0000

#define REG_HDMITX_CSC_SEL                  0x06U
    #define REG_HDMITX_CSC_SEL_MSK              0x000F
    #define REG_HDMITX_CSC_SEL_422_10_TO_8      0x0001
    #define REG_HDMITX_CSC_SEL_Y_TO_R           0x0002
    #define REG_HDMITX_CSC_SEL_R_TO_Y           0x0004
    #define REG_HDMITX_CSC_SEL_444_TO_422       0x0008
    #define REG_HDMITX_CSC_SEL_BYPASS           0x0000

#define REG_HDMITX_DATA_PERIOD_ISLAND       0x08U
    #define REG_HDMITX_DATA_PERIOD_ISLAND_MSK   0x00FF


#define REG_HDMITX_PKT_EN                   0x1BU
    #define REG_HDMITX_PKT_SPD_MSK              0x0001
    #define REG_HDMITX_PKT_SPD_EN               0x0001
    #define REG_HDMITX_PKT_PKT0_MSK             0x0001
    #define REG_HDMITX_PKT_PKT0_EN              0x0001

    #define REG_HDMITX_PKT_VS_MSK               0x0002
    #define REG_HDMITX_PKT_VS_EN                0x0002
    #define REG_HDMITX_PKT_PKT1_MSK             0x0002
    #define REG_HDMITX_PKT_PKT1_EN              0x0002

    #define REG_HDMITX_PKT_AUDIO_MSK            0x0004
    #define REG_HDMITX_PKT_AUDIO_EN             0x0004

    #define REG_HDMITX_PKT_ACR_MSK              0x0008
    #define REG_HDMITX_PKT_ACR_EN               0x0008

    #define REG_HDMITX_PKT_ADO_MSK              0x0010
    #define REG_HDMITX_PKT_ADO_EN               0x0010

    #define REG_HDMITX_PKT_AVI_MSK              0x0020
    #define REG_HDMITX_PKT_AVI_EN               0x0020

    #define REG_HDMITX_PKT_GC_MSK               0x0040
    #define REG_HDMITX_PKT_GC_EN                0x0040

    #define REG_HDMITX_PKT_NULL_MSK             0x0080
    #define REG_HDMITX_PKT_NULL_EN              0x0080

    #define REG_HDMITX_PKT_PKT2_MSK             0x0100
    #define REG_HDMITX_PKT_PKT2_EN              0x0100

#define REG_HDMITX_ACR_MOD                      0x30U
    #define REG_HDMITX_ACR_MOD_MSK                  0x0001
    #define REG_HDMITX_ACR_MOD_FROM_COUNTER         0x0001
    #define REG_HDMITX_ACR_MOD_FROM_REG             0x0000

#define REG_HDMITX_ACR_CTS_1                    0x31U
    #define REG_HDMITX_ACR_CTS_1_MSK                0x00FF
    #define REG_HDMITX_ACR_CTS_1_VAL(x)             (x & 0x000FF)

#define REG_HDMITX_ACR_CTS_2                    0x31U
    #define REG_HDMITX_ACR_CTS_2_MSK                0xFF00
    #define REG_HDMITX_ACR_CTS_2_VAL(x)            (x&0x0FF00)

#define REG_HDMITX_ACR_CTS_3                    0x33U
    #define REG_HDMITX_ACR_CTS_3_MSK                0x000F
    #define REG_HDMITX_ACR_CTS_3_VAL(x)            ((x & 0x0F0000) >> 16)

#define REG_HDMITX_ACR_N_1                      0x32U
    #define REG_HDMITX_ACR_N_1_MSK                  0x00FF
    #define REG_HDMITX_ACR_N_1_VAL(x)               (x & 0x000FF)

#define REG_HDMITX_ACR_N_2                      0x32U
    #define REG_HDMITX_ACR_N_2_MSK                  0xFF00
    #define REG_HDMITX_ACR_N_2_VAL(x)               (x & 0x0FF00)

#define REG_HDMITX_ACR_N_3                      0x33U
    #define REG_HDMITX_ACR_N_3_MSK                  0x00F0
    #define REG_HDMITX_ACR_N_3_VAL(x)               ((x & 0xF0000)>>8)

#define REG_HDMITX_PKT_AVI_1                    0x34U
#define REG_HDMITX_PKT_AVI_2                    0x34U
#define REG_HDMITX_PKT_AVI_3                    0x35U
#define REG_HDMITX_PKT_AVI_4                    0x35U
#define REG_HDMITX_PKT_AVI_5                    0x36U
#define REG_HDMITX_PKT_AVI_6                    0x36U
#define REG_HDMITX_PKT_AVI_7                    0x37U
#define REG_HDMITX_PKT_AVI_8                    0x38U
#define REG_HDMITX_PKT_AVI_9                    0x38U
#define REG_HDMITX_PKT_AVI_10                   0x39U
#define REG_HDMITX_PKT_AVI_11                   0x39U
#define REG_HDMITX_PKT_AVI_12                   0x3AU
#define REG_HDMITX_PKT_AVI_13                   0x3AU
#define REG_HDMITX_PKT_AVI_14                   0x3BU

#define REG_HDMITX_PKT_ADO_1                    0x3CU
#define REG_HDMITX_PKT_ADO_2                    0x3CU
#define REG_HDMITX_PKT_ADO_3                    0x3DU
#define REG_HDMITX_PKT_ADO_4                    0x3DU
#define REG_HDMITX_PKT_ADO_5                    0x3EU
#define REG_HDMITX_PKT_ADO_6                    0x3EU

#define REG_HDMITX_PKT_ASP_CS_1                 0x21U
#define REG_HDMITX_PKT_ASP_CS_2                 0x21U
#define REG_HDMITX_PKT_ASP_CS_3                 0x22U
#define REG_HDMITX_PKT_ASP_CS_4                 0x22U
#define REG_HDMITX_PKT_ASP_CS_5                 0x23U
#define REG_HDMITX_PKT_ASP_CS_6                 0x23U
#define REG_HDMITX_PKT_ASP_CS_7                 0x24U
#define REG_HDMITX_PKT_ASP_CS_8                 0x24U
#define REG_HDMITX_PKT_ASP_CS_9                 0x25U
#define REG_HDMITX_PKT_ASP_CS_10                0x25U
#define REG_HDMITX_PKT_ASP_CS_11                0x26U
#define REG_HDMITX_PKT_ASP_CS_12                0x26U
#define REG_HDMITX_PKT_ASP_CS_13                0x27U
#define REG_HDMITX_PKT_ASP_CS_14                0x27U
#define REG_HDMITX_PKT_ASP_CS_15                0x28U
#define REG_HDMITX_PKT_ASP_CS_16                0x28U
#define REG_HDMITX_PKT_ASP_CS_17                0x29U
#define REG_HDMITX_PKT_ASP_CS_18                0x29U
#define REG_HDMITX_PKT_ASP_CS_19                0x2AU
#define REG_HDMITX_PKT_ASP_CS_20                0x2AU
#define REG_HDMITX_PKT_ASP_CS_21                0x2BU
#define REG_HDMITX_PKT_ASP_CS_22                0x2BU
#define REG_HDMITX_PKT_ASP_CS_23                0x2CU
#define REG_HDMITX_PKT_ASP_CS_24                0x2CU

#define REG_HDMITX_PKT_SPD_HEADER               0x40U
#define REG_HDMITX_PKT_SPD_LENGTH               0x41U
#define REG_HDMITX_PKT_SPD_1                    0x42U
#define REG_HDMITX_PKT_SPD_2                    0x42U
#define REG_HDMITX_PKT_SPD_3                    0x43U
#define REG_HDMITX_PKT_SPD_4                    0x43U
#define REG_HDMITX_PKT_SPD_5                    0x44U
#define REG_HDMITX_PKT_SPD_6                    0x44U
#define REG_HDMITX_PKT_SPD_7                    0x45U
#define REG_HDMITX_PKT_SPD_8                    0x46U
#define REG_HDMITX_PKT_SPD_9                    0x46U
#define REG_HDMITX_PKT_SPD_10                   0x47U
#define REG_HDMITX_PKT_SPD_11                   0x47U
#define REG_HDMITX_PKT_SPD_12                   0x48U
#define REG_HDMITX_PKT_SPD_13                   0x48U
#define REG_HDMITX_PKT_SPD_14                   0x49U
#define REG_HDMITX_PKT_SPD_15                   0x4AU
#define REG_HDMITX_PKT_SPD_16                   0x4AU
#define REG_HDMITX_PKT_SPD_17                   0x4BU
#define REG_HDMITX_PKT_SPD_18                   0x4BU
#define REG_HDMITX_PKT_SPD_19                   0x4CU
#define REG_HDMITX_PKT_SPD_20                   0x4CU
#define REG_HDMITX_PKT_SPD_21                   0x4DU
#define REG_HDMITX_PKT_SPD_22                   0x4EU
#define REG_HDMITX_PKT_SPD_23                   0x4EU
#define REG_HDMITX_PKT_SPD_24                   0x4FU
#define REG_HDMITX_PKT_SPD_25                   0x4FU
#define REG_HDMITX_PKT_SPD_DATA_LENGTH          25

#define REG_HDMITX_PKT_VS_HEADER                0x52U
#define REG_HDMITX_PKT_VS_LENGTH                0x53U
#define REG_HDMITX_PKT_VS_1                     0x54U
#define REG_HDMITX_PKT_VS_2                     0x54U
#define REG_HDMITX_PKT_VS_3                     0x55U
#define REG_HDMITX_PKT_VS_4                     0x55U
#define REG_HDMITX_PKT_VS_5                     0x56U
#define REG_HDMITX_PKT_VS_6                     0x56U
#define REG_HDMITX_PKT_VS_7                     0x57U
#define REG_HDMITX_PKT_VS_8                     0x58U
#define REG_HDMITX_PKT_VS_9                     0x58U
#define REG_HDMITX_PKT_VS_10                    0x59U
#define REG_HDMITX_PKT_VS_11                    0x59U
#define REG_HDMITX_PKT_VS_12                    0x5AU
#define REG_HDMITX_PKT_VS_13                    0x5AU
#define REG_HDMITX_PKT_VS_14                    0x5BU
#define REG_HDMITX_PKT_VS_15                    0x5CU
#define REG_HDMITX_PKT_VS_16                    0x5CU
#define REG_HDMITX_PKT_VS_17                    0x5DU
#define REG_HDMITX_PKT_VS_18                    0x5DU
#define REG_HDMITX_PKT_VS_19                    0x5EU
#define REG_HDMITX_PKT_VS_20                    0x5EU
#define REG_HDMITX_PKT_VS_21                    0x5FU
#define REG_HDMITX_PKT_VS_22                    0x60U
#define REG_HDMITX_PKT_VS_23                    0x60U
#define REG_HDMITX_PKT_VS_24                    0x61U
#define REG_HDMITX_PKT_VS_25                    0x61U
#define REG_HDMITX_PKT_VS_26                    0x62U
#define REG_HDMITX_PKT_VS_27                    0x62U
#define REG_HDMITX_PKT_VS_DATA_LENGTH           27
#endif

#define REG_HDMITX_DTOP_00              0x00U


// --------- BK1126 HDMITx ATOP --------- //
#define REG_HDMITX_ATOP_16              0x16U
#define REG_HDMITX_ATOP_18              0x18U
#define REG_HDMITX_ATOP_33              0x33U
#define REG_HDMITX_ATOP_34              0x34U
#define REG_HDMITX_ATOP_35              0x35U
//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------

#endif // _REG_HDMITX_H_

