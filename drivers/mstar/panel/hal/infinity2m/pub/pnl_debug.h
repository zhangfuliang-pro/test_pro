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


#ifndef _PNL_DEBUG_H_
#define _PNL_DEBUG_H_


//-----------------------------------------------------------------------------------------------------
// Variable Prototype
//-----------------------------------------------------------------------------------------------------

#ifndef _DRV_PNL_IF_C_
extern u32 _gu32PnlDbgLevel;
#endif


//-----------------------------------------------------------------------------------------------------
// Debug Level
//-----------------------------------------------------------------------------------------------------

#define PNL_DBG_LEVEL_NONE              0x00000000
#define PNL_DBG_LEVEL_DRV               0x00000001
#define PNL_DBG_LEVEL_HAL               0x00000002
#define PNL_DBG_LEVEL_MODULE            0x00000004
#define PNL_DBG_LEVEL_CTX               0x00000008
#define PNL_DBG_LEVEL_RW_PACKET         0x00000010

//-----------------------------------------------------------------------------------------------------
// Debug Macro
//-----------------------------------------------------------------------------------------------------
#define PRINT_NONE    "\33[m"
#define PRINT_RED     "\33[1;31m"
#define PRINT_YELLOW  "\33[1;33m"


#define PNL_DBG_EN 1


#ifdef PNL_OS_TYPE_UBOOT
#define CamOsPrintf  printf
#endif


#if PNL_DBG_EN

#define PNL_ASSERT(_con)   \
    do {\
        if (!(_con)) {\
            CamOsPrintf("BUG at %s:%d assert(%s)\n",\
                    __FILE__, __LINE__, #_con);\
            BUG();\
        }\
    } while (0)

#define PNL_DBG(dbglv, _fmt, _args...)          \
    do                                          \
    if(_gu32PnlDbgLevel & dbglv)                   \
    {                                           \
        CamOsPrintf(_fmt, ## _args);       \
    }while(0)

#define PNL_ERR(_fmt, _args...)                 \
    do{                                         \
        CamOsPrintf(PRINT_RED _fmt PRINT_NONE, ## _args);       \
    }while(0)




#else

#define     PNL_ASSERT(arg)
#define     PNL_DBG(dbglv, _fmt, _args...)
#define     PNL_ERR( _fmt, _args...)

#endif

//-----------------------------------------------------------------------------------------------------
// Parsing String
//-----------------------------------------------------------------------------------------------------


#define PARSING_HAL_LINKTYPE(x)     ( x == E_HAL_PNL_LINK_TTL               ? "TTL"              : \
                                      x == E_HAL_PNL_LINK_LVDS              ? "LVDS"             : \
                                      x == E_HAL_PNL_LINK_RSDS              ? "RSDS"             : \
                                      x == E_HAL_PNL_LINK_MINILVDS          ? "MINILVDS"         : \
                                      x == E_HAL_PNL_LINK_ANALOG_MINILVDS   ? "ANALOG_MINILVDS"  : \
                                      x == E_HAL_PNL_LINK_DIGITAL_MINILVDS  ? "DIGITAL_MINILVDS" : \
                                      x == E_HAL_PNL_LINK_MFC               ? "MFC"              : \
                                      x == E_HAL_PNL_LINK_DAC_I             ? "DAC_I"            : \
                                      x == E_HAL_PNL_LINK_DAC_P             ? "DAC_P"            : \
                                      x == E_HAL_PNL_LINK_PDPLVDS           ? "PDPLVDS"          : \
                                      x == E_HAL_PNL_LINK_EXT               ? "EXT"              : \
                                      x == E_HAL_PNL_LINK_MIPI_DSI          ? "MIPI_DSI"         : \
                                                                               "UNKNOWN")


#define PARSING_HAL_TI_BIT(x)       (x == E_HAL_PNL_TI_10BIT_MODE ? "TI_10BIT" :\
                                     x == E_HAL_PNL_TI_8BIT_MODE  ? "TI_8BIT" :\
                                     x == E_HAL_PNL_TI_6BIT_MODE  ? "TI_6BIT" :\
                                                                     "UNKNOWN")

#define PARSING_HAL_CH_SWAP(x)     (x == E_HAL_PNL_CH_SWAP_0 ? "CH_SWAP_0" \
                                     x == E_HAL_PNL_CH_SWAP_1 ? "CH_SWAP_1" \
                                     x == E_HAL_PNL_CH_SWAP_2 ? "CH_SWAP_2" \
                                     x == E_HAL_PNL_CH_SWAP_3 ? "CH_SWAP_3" \
                                     x == E_HAL_PNL_CH_SWAP_4 ? "CH_SWAP_4" \
                                                                 "UNKNOWN")


#define PARSING_HAL_MIPI_DSI_CTRL(x)     ( x == E_HAL_PNL_MIPI_DSI_CMD_MODE   ? "CMD_MODE"   : \
                                           x == E_HAL_PNL_MIPI_DSI_SYNC_PULSE ? "SYNC_PULSE" : \
                                           x == E_HAL_PNL_MIPI_DSI_SYNC_EVENT ? "SYNC_EVENT" : \
                                           x == E_HAL_PNL_MIPI_DSI_BURST_MODE ? "BURST_MODE" : \
                                                                                      "UNKNOWN")

#define PARSING_HAL_MIPI_DSI_FMT(x)      ( x == E_HAL_PNL_MIPI_DSI_RGB565          ? "RGB565" : \
                                           x == E_HAL_PNL_MIPI_DSI_RGB666          ? "RGB666" : \
                                           x == E_HAL_PNL_MIPI_DSI_RGB888          ? "RGB888" : \
                                           x == E_HAL_PNL_MIPI_DSI_LOOSELY_RGB666  ? "LOOSELY_RGB666" : \
                                                                                      "UNKOWN")



#define PARSING_HAL_QUERY_TYPE(x)       ( x == E_HAL_PNL_QUERY_PARAM            ? " PARAM" : \
                                          x == E_HAL_PNL_QUERY_MIPIDSI_PARAM    ? " MIPIDSI_PARAM" : \
                                          x == E_HAL_PNL_QUERY_SSC              ? "TIMING" : \
                                          x == E_HAL_PNL_QUERY_POWER            ? "POWER" : \
                                          x == E_HAL_PNL_QUERY_BACKLIGHT_ONOFF  ? "BACKLIGHT_ONOFF" : \
                                          x == E_HAL_PNL_QUERY_BACKLIGHT_LEVEL  ? "BACKLGIHT_LEVEL" : \
                                          x == E_HAL_PNL_QUERY_CURRENT          ? "CURRENT" :\
                                                                                  "UNKNOWN")

#define PARSING_HAL_QUERY_RET(x)        ( x == E_HAL_PNL_QUERY_RET_OK         ? "RET_OK" : \
                                          x == E_HAL_PNL_QUERY_RET_CFGERR     ? "RET_CFGERR" : \
                                          x == E_HAL_PNL_QUERY_RET_NONEED     ? "RET_NO_NEED" : \
                                          x == E_HAL_PNL_QUERY_RET_NOTSUPPORT ? "RET_NOT_SUPPORT" : \
                                                                                "UNKNOWN")
#endif // #ifndef



