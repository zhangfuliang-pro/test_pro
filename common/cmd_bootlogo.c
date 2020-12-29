

//-------------------------------------------------------------------------------------------------
//  Include Files
//-------------------------------------------------------------------------------------------------
#include <common.h>
#include <command.h>
#include <malloc.h>
#include <stdlib.h>
#include "asm/arch/mach/ms_types.h"
#include "asm/arch/mach/platform.h"
#include "asm/arch/mach/io.h"

#include <ubi_uboot.h>
#include <cmd_osd.h>

#if defined(CONFIG_SSTAR_DISP)
#include "mhal_common.h"
#include "mhal_disp_datatype.h"
#include "mhal_disp.h"
#endif

#if defined(CONFIG_SSTAR_PNL)
#include "mhal_pnl_datatype.h"
#include "mhal_pnl.h"
#endif

#if defined(CONFIG_SSTAR_HDMITX)
#include "apiHDMITx.h"
#endif

#if defined(CONFIG_SSTAR_JPD)
#include "jinclude.h"
#include "jpeglib.h"
#endif

#if defined(CONFIG_MS_PARTITION)
#include "part_mxp.h"
#endif
//-------------------------------------------------------------------------------------------------
//  Defines & Macro
//-------------------------------------------------------------------------------------------------
#define BOOTLOGO_DBG_LEVEL_ERR     0x01
#define BOOTLOGO_DBG_LEVEL_INFO    0x02
#define BOOTLOGO_DBG_LEVEL_JPD     0x04


#define BOOTLOGO_DBG_LEVEL          0 // BOOTLOGO_DBG_LEVEL_INFO

#define BOOTLOGO_DBG(dbglv, _fmt, _args...)    \
    do                                          \
    if(dbglv & u32BootlogDvgLevel)              \
    {                                           \
            printf(_fmt, ## _args);             \
    }while(0)



#define DISP_DEVICE_NULL     0
#define DISP_DEVICE_HDMI     1
#define DISP_DEVICE_VGA      2
#define DISP_DEVICE_LCD      4

#define BOOTLOGO_TIMING_NUM  5


#define HDMITX_ANALOG_TUNING_SD         {0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
#define HDMITX_ANALOG_TUNING_HD         {0x01, 0x00, 0x00, 0x00, 0x00, 0x00}
#define HDMITX_ANALOG_TUNING_DEEP_HD    {0x00, 0x00, 0x00, 0x00, 0x00, 0x07}

//-------------------------------------------------------------------------------------------------
//  structure & Enu
//-------------------------------------------------------------------------------------------------

typedef struct
{
    u32 u32PnlParamCfgSize;
    u8 *pPnlParamCfg;
    u32 u32MipiDsiCfgSize;
    u8 *pMipiDsiCfg;
}PnlConfig_t;


typedef struct
{
    void *pInBuff;
    u64  u64InBuffAddr;
    u32  u32InBuffSize;
    u64  u64OutBuffAddr;
    u32  u32OutBuffSize;
    u16  u16DisplayWidth;
    u16  u16DisplayHeight;
    u8   u8DisplayRate;
    u8   u8Interface;
#if defined(CONFIG_SSTAR_PNL)
    u8 panelname[20];
    MhalPnlParamConfig_t stPnlPara;
    MhalPnlMipiDsiConfig_t stMipiDsiCfg;
#endif
}BootlogoImgConfig_t;


typedef struct
{
    MHAL_DISP_DeviceTiming_e enTiminId;
    u16 u16HsyncWidht;
    u16 u16HsyncBacPorch;

    u16 u16VsyncWidht;
    u16 u16VsyncBacPorch;

    u16 u16Hstart;
    u16 u16Vstart;
    u16 u16Hactive;
    u16 u16Vactive;

    u16 u16Htotal;
    u16 u16Vtotal;
    u16 u16DclkMhz;
}DisplayLogoTimingConfig_t;

//-------------------------------------------------------------------------------------------------
//  Variable
//-------------------------------------------------------------------------------------------------
u32 u32BootlogDvgLevel = BOOTLOGO_DBG_LEVEL_ERR | BOOTLOGO_DBG_LEVEL_INFO | BOOTLOGO_DBG_LEVEL_JPD;

DisplayLogoTimingConfig_t stTimingTable[BOOTLOGO_TIMING_NUM] =
{
    {
        E_MHAL_DISP_OUTPUT_1080P60, //
        48, // u16HsyncWidht
        46, // u16HsyncBacPorch
        4,  // u16VsyncWidht
        23, // u16VsyncBacPorch
        98, // u16Hstart
        27, // u16Vstart
        800,// u16Hactive
        480,// u16Vactive
        928,// u16Htotal
        525,// u16Vtotal
        43, // u16DclkMhz

    },

    {
        E_MHAL_DISP_OUTPUT_1080P50, //
        44,
        148,
        5,
        36,
        44+148,
        0,
        1920,
        1080,
        2200,
        1125,
        148,
    },

    {
        E_MHAL_DISP_OUTPUT_720P50,
        40,
        220,
        5,
        20,
        260,
        0,
        1280,
        720,
        1980,
        750,
        74,
    },
    {
        E_MHAL_DISP_OUTPUT_720P60,
        40,
        220,
        5,
        20,
        260,
        0,
        1280,
        720,
        1650,
        750,
        74,
    },

    {
        E_MHAL_DISP_OUTPUT_USER, // for FPGA
        48, // u16HsyncWidht
        46, // u16HsyncBacPorch
        4,  // u16VsyncWidht
        23, // u16VsyncBacPorch
        98, // u16Hstart
        27, // u16Vstart
        800,// u16Hactive
        480,// u16Vactive
        928,// u16Htotal
        525,// u16Vtotal
        43, // u16DclkMhz
    },
};



#if defined(CONFIG_CMD_MTDPARTS)
#include <jffs2/jffs2.h>
/* partition handling routines */
int mtdparts_init(void);
int find_dev_and_part(const char *id, struct mtd_device **dev,
		u8 *part_num, struct part_info **part);
#endif


//-------------------------------------------------------------------------------------------------
//  Functions
//-------------------------------------------------------------------------------------------------
MS_S32 BootLogoMemAlloc(MS_U8 *pu8Name, MS_U32 size, unsigned long long *pu64PhyAddr)
{
    return 0;
}

MS_S32 BootLogoMemRelease(unsigned long long u64PhyAddr)
{
    return 0;
}

#if defined(CONFIG_SSTAR_DISP)
MHAL_DISP_DeviceTiming_e _BootLogoGetTiminId(u16 u16Width, u16 u16Height, u8 u8Rate)
{
    MHAL_DISP_DeviceTiming_e enTiming;
    enTiming =  ((u16Width) == 1920 && (u16Height) == 1080 && (u8Rate) == 24) ? E_MHAL_DISP_OUTPUT_1080P24 :
                ((u16Width) == 1920 && (u16Height) == 1080 && (u8Rate) == 25) ? E_MHAL_DISP_OUTPUT_1080P25 :
                ((u16Width) == 1920 && (u16Height) == 1080 && (u8Rate) == 30) ? E_MHAL_DISP_OUTPUT_1080P30 :
                ((u16Width) == 1920 && (u16Height) == 1080 && (u8Rate) == 50) ? E_MHAL_DISP_OUTPUT_1080P50 :
                ((u16Width) == 1920 && (u16Height) == 1080 && (u8Rate) == 60) ? E_MHAL_DISP_OUTPUT_1080P60 :
                ((u16Width) == 1280 && (u16Height) == 720  && (u8Rate) == 50) ? E_MHAL_DISP_OUTPUT_720P50  :
                ((u16Width) == 1280 && (u16Height) == 720  && (u8Rate) == 60) ? E_MHAL_DISP_OUTPUT_720P60  :
                ((u16Width) == 720  && (u16Height) == 480  && (u8Rate) == 60) ? E_MHAL_DISP_OUTPUT_480P60  :
                ((u16Width) == 720  && (u16Height) == 576  && (u8Rate) == 60) ? E_MHAL_DISP_OUTPUT_576P50  :
                ((u16Width) == 640  && (u16Height) == 480  && (u8Rate) == 60) ? E_MHAL_DISP_OUTPUT_640x480_60   :
                ((u16Width) == 800  && (u16Height) == 600  && (u8Rate) == 60) ? E_MHAL_DISP_OUTPUT_800x600_60   :
                ((u16Width) == 1280 && (u16Height) == 1024 && (u8Rate) == 60) ? E_MHAL_DISP_OUTPUT_1280x1024_60 :
                ((u16Width) == 1366 && (u16Height) == 768  && (u8Rate) == 60) ? E_MHAL_DISP_OUTPUT_1366x768_60  :
                ((u16Width) == 1440 && (u16Height) == 800  && (u8Rate) == 60) ? E_MHAL_DISP_OUTPUT_1440x900_60  :
                ((u16Width) == 1280 && (u16Height) == 800  && (u8Rate) == 60) ? E_MHAL_DISP_OUTPUT_1280x800_60  :
                ((u16Width) == 3840 && (u16Height) == 2160 && (u8Rate) == 30) ? E_MHAL_DISP_OUTPUT_3840x2160_30 :
                                                                                E_MHAL_DISP_OUTPUT_MAX;
    return enTiming;
}
#endif

#if defined(CONFIG_SSTAR_HDMITX)
HDMITX_VIDEO_TIMING _BootLogoGetHdmitxTimingId(u16 u16Width, u16 u16Height, u8 u8Rate)
{
    HDMITX_VIDEO_TIMING enTiming;
    enTiming =  ((u16Width) == 1920 && (u16Height) == 1080 && (u8Rate) == 24) ? HDMITX_RES_1920x1080p_24Hz :
                ((u16Width) == 1920 && (u16Height) == 1080 && (u8Rate) == 25) ? HDMITX_RES_1920x1080p_25Hz :
                ((u16Width) == 1920 && (u16Height) == 1080 && (u8Rate) == 30) ? HDMITX_RES_1920x1080p_30Hz :
                ((u16Width) == 1920 && (u16Height) == 1080 && (u8Rate) == 50) ? HDMITX_RES_1920x1080p_50Hz :
                ((u16Width) == 1920 && (u16Height) == 1080 && (u8Rate) == 60) ? HDMITX_RES_1920x1080p_60Hz :
                ((u16Width) == 1280 && (u16Height) == 720  && (u8Rate) == 50) ? HDMITX_RES_1280x720p_50Hz  :
                ((u16Width) == 1280 && (u16Height) == 720  && (u8Rate) == 60) ? HDMITX_RES_1280x720p_60Hz  :
                ((u16Width) == 720  && (u16Height) == 480  && (u8Rate) == 60) ? HDMITX_RES_720x480p  :
                ((u16Width) == 720  && (u16Height) == 576  && (u8Rate) == 60) ? HDMITX_RES_720x576p  :
                ((u16Width) == 640  && (u16Height) == 480  && (u8Rate) == 60) ? HDMITX_RES_640x480p   :
                ((u16Width) == 800  && (u16Height) == 600  && (u8Rate) == 60) ? HDMITX_RES_MAX   :
                ((u16Width) == 1280 && (u16Height) == 1024 && (u8Rate) == 60) ? HDMITX_RES_1280x1024p_60Hz :
                ((u16Width) == 1366 && (u16Height) == 768  && (u8Rate) == 60) ? HDMITX_RES_MAX  :
                ((u16Width) == 1440 && (u16Height) == 800  && (u8Rate) == 60) ? HDMITX_RES_MAX  :
                ((u16Width) == 1280 && (u16Height) == 800  && (u8Rate) == 60) ? HDMITX_RES_MAX  :
                ((u16Width) == 3840 && (u16Height) == 2160 && (u8Rate) == 30) ? HDMITX_RES_MAX :
                                                                                E_MHAL_DISP_OUTPUT_MAX;
    return enTiming;
}
#endif




int _BootLogoGetImageConfig(BootlogoImgConfig_t *pCfg)
{

    //Length
    #define LOGO_HEADER_MAGIC_PREFIX_LEN        (4)
    #define LOGO_HEADER_OUT_BUFFER_SIZE_LEN     (4)
    #define LOGO_HEADER_OUT_BUFFER_ADDR_LEN     (8)
    #define LOGO_HEADER_DISPLAY_WIDTH_LEN       (2)
    #define LOGO_HEADER_DISPLAY_HEIGHT_LEN      (2)
    #define LOGO_HEADER_DISPLAY_RATE_LEN        (1)
    #define LOGO_HEADER_DISPLAY_INTERFACE_LEN   (1)
    #define LOGO_HEADER_RESERVED_LEN            (10)

#if defined(CONFIG_SSTAR_PNL)
    #define LOGO_HEADER_PANEL_NAME_LEN          (20)
    #define LOGO_HEADER_PANEL_INIT_PARA_LEN     (sizeof(MhalPnlParamConfig_t))
    #define LOGO_HEADER_PANEL_MIPI_DST_CONFIG_LEN     (sizeof(MhalPnlMipiDsiConfig_t))
    #define LOGO_HEADER_SIZE                    (52 + LOGO_HEADER_PANEL_INIT_PARA_LEN + LOGO_HEADER_PANEL_MIPI_DST_CONFIG_LEN)
#else
    #define LOGO_HEADER_SIZE                    (32)
#endif

    // Offset
    #define LOGO_HEADER_MAGIC_PREFIX_OFFSET             (0)
    #define LOGO_HEADER_OUT_BUFFER_SIZE_OFFSET          (LOGO_HEADER_MAGIC_PREFIX_OFFSET + LOGO_HEADER_MAGIC_PREFIX_LEN)
    #define LOGO_HEADER_OUT_BUFFER_ADDR_OFFSET          (LOGO_HEADER_OUT_BUFFER_SIZE_OFFSET + LOGO_HEADER_OUT_BUFFER_SIZE_LEN)
    #define LOGO_HEADER_DISPLAY_WIDTH_OFFSET            (LOGO_HEADER_OUT_BUFFER_ADDR_OFFSET + LOGO_HEADER_OUT_BUFFER_ADDR_LEN)
    #define LOGO_HEADER_DISPLAY_HEIGHT_OFFSET           (LOGO_HEADER_DISPLAY_WIDTH_OFFSET + LOGO_HEADER_DISPLAY_WIDTH_LEN)
    #define LOGO_HEADER_TIMING_ID_OFFSET                (LOGO_HEADER_DISPLAY_HEIGHT_OFFSET + LOGO_HEADER_DISPLAY_HEIGHT_LEN)
    #define LOGO_HEADER_INTERFACE_ID_OFFSET             (LOGO_HEADER_TIMING_ID_OFFSET + LOGO_HEADER_DISPLAY_RATE_LEN)
    #define LOGO_HEADER_RESERVED_OFFSET                 (LOGO_HEADER_INTERFACE_ID_OFFSET + LOGO_HEADER_DISPLAY_INTERFACE_LEN)
#if defined(CONFIG_SSTAR_PNL)
    #define LOGO_HEADER_PANEL_NAME_OFFSET               (LOGO_HEADER_RESERVED_OFFSET + LOGO_HEADER_RESERVED_LEN)
    #define LOGO_HEADER_PANEL_INIT_PARA_OFFSET          (LOGO_HEADER_PANEL_NAME_OFFSET + LOGO_HEADER_PANEL_NAME_LEN)
    #define LOGO_HEADER_PANEL_MIPI_DST_CONFIG_OFFSET    (LOGO_HEADER_PANEL_INIT_PARA_OFFSET + LOGO_HEADER_PANEL_INIT_PARA_LEN)
#endif

    #define LOGO_FLAHS_BASE     0x14000000

    u64     start, size;
	char strENVName[] = "LOGO";
    int idx;
#if defined(CONFIG_CMD_MTDPARTS) || defined(CONFIG_MS_SPINAND)
    struct mtd_device *dev;
    struct part_info *part;
    u8 pnum;
    int ret;

    ret = mtdparts_init();
    if (ret)
        return ret;

    ret = find_dev_and_part(strENVName, &dev, &pnum, &part);
    if (ret)
        return ret;

    if (dev->id->type != MTD_DEV_TYPE_NAND) {
        puts("not a NAND device\n");
        return -1;
    }

    start = part->offset;
    size = part->size;
#elif defined(CONFIG_MS_PARTITION)
    mxp_record rec;
	mxp_load_table();
	idx=mxp_get_record_index(strENVName);
	if(idx<0)
	{
        BOOTLOGO_DBG(BOOTLOGO_DBG_LEVEL_ERR, "can not found mxp record: %s\n", strENVName);
        return FALSE;
	}

	if(0 != mxp_get_record_by_index(idx,&rec))
    {
        BOOTLOGO_DBG(BOOTLOGO_DBG_LEVEL_ERR, "failed to get MXP record with name: %s\n", strENVName);
        return 0;
    }
    start = rec.start;
    size = rec.size;
#else
    start = 0;
    size = 0;
    return 0;
#endif

	{
		BOOTLOGO_DBG(BOOTLOGO_DBG_LEVEL_INFO, "%s in flash offset=0x%llx size=0x%llx\n",strENVName , start, size);

		pCfg->pInBuff = malloc(size);
		if(pCfg->pInBuff == NULL)
		{
		    BOOTLOGO_DBG(BOOTLOGO_DBG_LEVEL_ERR, "allocate buffer fail\n");
            return 0;
		}
    #if defined(CONFIG_CMD_MTDPARTS) || defined(CONFIG_MS_SPINAND)
        char  cmd_str[128];
        sprintf(cmd_str, "nand read.e 0x%p %s", pCfg->pInBuff, strENVName);
        run_command(cmd_str, 0);
    #else
        //sprintf(cmd_str, "sf probe; sf read 0x%p 0x%p 0x%p", pCfg->pInBuff, start, size);
        //run_command(cmd_str, 0);
        memcpy(pCfg->pInBuff, (void*)(U32)(start | LOGO_FLAHS_BASE), size);
    #endif

        flush_cache((U32)pCfg->pInBuff, size);

        //Parsing Header
        for(idx=0; idx<4; idx++)
        {
            if( strENVName[idx] != *((U8 *)(pCfg->pInBuff+idx)))
            {
                BOOTLOGO_DBG(BOOTLOGO_DBG_LEVEL_ERR, "Header check fail\n");
                return 0;
            }
        }

        pCfg->u32OutBuffSize    = *((u32 *)(pCfg->pInBuff +  LOGO_HEADER_OUT_BUFFER_SIZE_OFFSET));
        pCfg->u64OutBuffAddr    = *((u64 *)(pCfg->pInBuff +  LOGO_HEADER_OUT_BUFFER_ADDR_OFFSET));
        pCfg->u16DisplayWidth   = *((u16 *)(pCfg->pInBuff +  LOGO_HEADER_DISPLAY_WIDTH_OFFSET));
        pCfg->u16DisplayHeight  = *((u16 *)(pCfg->pInBuff +  LOGO_HEADER_DISPLAY_HEIGHT_OFFSET));
        pCfg->u8DisplayRate     = *((u8 *) (pCfg->pInBuff +  LOGO_HEADER_TIMING_ID_OFFSET));
        pCfg->u8Interface       = *((u8 *) (pCfg->pInBuff +  LOGO_HEADER_INTERFACE_ID_OFFSET));
#if defined(CONFIG_SSTAR_PNL)
        memcpy(pCfg->panelname, pCfg->pInBuff + LOGO_HEADER_PANEL_NAME_OFFSET, LOGO_HEADER_PANEL_NAME_LEN);
        memcpy(&pCfg->stPnlPara, pCfg->pInBuff + LOGO_HEADER_PANEL_INIT_PARA_OFFSET, LOGO_HEADER_PANEL_INIT_PARA_LEN);
        memcpy(&pCfg->stMipiDsiCfg, pCfg->pInBuff + LOGO_HEADER_PANEL_MIPI_DST_CONFIG_OFFSET, LOGO_HEADER_PANEL_MIPI_DST_CONFIG_LEN);
        pCfg->u64InBuffAddr     =  (U32)pCfg->pInBuff + LOGO_HEADER_SIZE + pCfg->stMipiDsiCfg.u32CmdBufSize, 32;
        pCfg->u32InBuffSize     =  (U32)(size - LOGO_HEADER_SIZE + pCfg->stMipiDsiCfg.u32CmdBufSize);
        pCfg->stMipiDsiCfg.pu8CmdBuf = malloc(pCfg->stMipiDsiCfg.u32CmdBufSize);
        if (pCfg->stMipiDsiCfg.pu8CmdBuf == NULL)
        {
            printf("mipi dii cfg malloc error!!\n");
            return -1;
        }
        memcpy(pCfg->stMipiDsiCfg.pu8CmdBuf, pCfg->pInBuff + LOGO_HEADER_SIZE, pCfg->stMipiDsiCfg.u32CmdBufSize);
        printf("Panel name %s\n", pCfg->panelname);
        printf("mipi cmd buf size %d\n", pCfg->stMipiDsiCfg.u32CmdBufSize);
        printf("PNL para size %d\n", sizeof(MhalPnlParamConfig_t));
        printf("PNL mipi size %d\n", sizeof(MhalPnlMipiDsiConfig_t));
#else
        pCfg->u64InBuffAddr     =  (U32)pCfg->pInBuff + LOGO_HEADER_SIZE;
        pCfg->u32InBuffSize     =  (U32)(size - LOGO_HEADER_SIZE);
#endif
        BOOTLOGO_DBG(BOOTLOGO_DBG_LEVEL_INFO, "InBuf:(%x), IN(%llx %x), OUT:(%llx, %x), DISP(%x %x %x), Interface:%x\n",
            (u32)pCfg->pInBuff,
            pCfg->u64InBuffAddr, pCfg->u32InBuffSize,
            pCfg->u64OutBuffAddr, pCfg->u32OutBuffSize,
            pCfg->u16DisplayWidth, pCfg->u16DisplayHeight,
            pCfg->u8DisplayRate, pCfg->u8Interface);
    }


    return 1;
}

void _BootLogoPnlInit(void)
{
#if defined(CONFIG_SSTAR_DISP)
    MHAL_DISP_PanelConfig_t stPnlCfg[BOOTLOGO_TIMING_NUM];
    u16 i;


    if( sizeof(stTimingTable)/sizeof(DisplayLogoTimingConfig_t) > BOOTLOGO_TIMING_NUM)
    {
        BOOTLOGO_DBG(BOOTLOGO_DBG_LEVEL_ERR, "%s %d:: Timing Talbe is bigger than %d\n",
            __FUNCTION__, __LINE__, BOOTLOGO_TIMING_NUM);
        return;
    }

    for(i=0; i<BOOTLOGO_TIMING_NUM; i++)
    {
        stPnlCfg[i].bValid = 1;
        stPnlCfg[i].eTiming = stTimingTable[i].enTiminId;
        stPnlCfg[i].stPanelAttr.m_ucPanelHSyncWidth     = stTimingTable[i].u16HsyncWidht;
        stPnlCfg[i].stPanelAttr.m_ucPanelHSyncBackPorch = stTimingTable[i].u16HsyncBacPorch;
        stPnlCfg[i].stPanelAttr.m_ucPanelVSyncWidth     = stTimingTable[i].u16VsyncWidht;
        stPnlCfg[i].stPanelAttr.m_ucPanelVBackPorch     = stTimingTable[i].u16VsyncBacPorch;
        stPnlCfg[i].stPanelAttr.m_wPanelHStart          = stTimingTable[i].u16Hstart;
        stPnlCfg[i].stPanelAttr.m_wPanelVStart          = stTimingTable[i].u16Vstart;
        stPnlCfg[i].stPanelAttr.m_wPanelWidth           = stTimingTable[i].u16Hactive;
        stPnlCfg[i].stPanelAttr.m_wPanelHeight          = stTimingTable[i].u16Vactive;
        stPnlCfg[i].stPanelAttr.m_wPanelHTotal          = stTimingTable[i].u16Htotal;
        stPnlCfg[i].stPanelAttr.m_wPanelVTotal          = stTimingTable[i].u16Vtotal;
        stPnlCfg[i].stPanelAttr.m_dwPanelDCLK           = stTimingTable[i].u16DclkMhz;
    }


    MHAL_DISP_InitPanelConfig(stPnlCfg, BOOTLOGO_TIMING_NUM);
#endif
}


void _BootLogoYuv444ToYuv420(u8 *pu8InBuf, u8 *pu8OutBuf, u16 u16Width, u16 u16Height)
{
    u16 i, j;
    u32 u32YDesIdx, u32UVDesIdx;
    u32 u32YSrcIdx;;
    u8 *pu8DesY = NULL, *pu8DesUV = NULL;;
    u8 *pu8SrcYUV = NULL;

    pu8SrcYUV = pu8InBuf;

    pu8DesY = pu8OutBuf;
    pu8DesUV = pu8DesY + u16Width * u16Height;

    u32UVDesIdx = 0;
    u32YDesIdx = 0;
    u32YSrcIdx = 0;

	BOOTLOGO_DBG(BOOTLOGO_DBG_LEVEL_JPD,"%s %d:: 444 To 422, In:%x, Out:%x, Width:%d, Height:%d\n",
        __FUNCTION__, __LINE__,
	    (u32)pu8InBuf, (u32)pu8OutBuf, u16Width, u16Height);

    for(i=0; i<u16Height; i++)
    {
        for(j=0; j<u16Width; j++)
        {
            //printf("(%d %d):: SrcY:%d, DstY:%d\n", i, j, u32YSrcIdx,u32YDesIdx);
            pu8DesY[u32YDesIdx++] = pu8SrcYUV[u32YSrcIdx];

            if((i & 0x01) && (j & 0x01))
            {
                //printf("(%d %d)::SrcUV:%d, %d DstUV:%d\n", i, j, u32YSrcIdx+1,u32YSrcIdx+2, u32UVDesIdx);
                pu8DesUV[u32UVDesIdx++] = pu8SrcYUV[u32YSrcIdx+1];
                pu8DesUV[u32UVDesIdx++] = pu8SrcYUV[u32YSrcIdx+2];
            }

            u32YSrcIdx += 3;
        }
    }

}


void _BootLogoJpdCtrl(BootlogoImgConfig_t  *pstBootlogoImgCfg, u16 *pu16OutWidth, u16 *pu16OutHeight)
{
#if defined(CONFIG_SSTAR_JPD)
    // Variables for the source jpg
    u32 u32JpgSize;
    u8 *pu8JpgBuffer;

    // Variables for the decompressor itself
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;

    // Variables for the output buffer, and how long each row is
    u32 u32BmpSize;
    u8 *pu8BmpBuffer;

    u32 u32Yuv420Size;
    u8 *pu8Yuv420Buffer;

    u16 u16RowStride, u16Width, u16Height, u16PixelSize;

    int rc; //, i, j;

    u32JpgSize = pstBootlogoImgCfg->u32InBuffSize;
    pu8JpgBuffer = (unsigned char *)((u32)pstBootlogoImgCfg->u64InBuffAddr);

	BOOTLOGO_DBG(BOOTLOGO_DBG_LEVEL_JPD,"%s %d::  Create Decompress struct\n", __FUNCTION__, __LINE__);
	// Allocate a new decompress struct, with the default error handler.
	// The default error handler will exit() on pretty much any issue,
	// so it's likely you'll want to replace it or supplement it with
	// your own.
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);

    BOOTLOGO_DBG(BOOTLOGO_DBG_LEVEL_JPD,"%s %d::  Set memory buffer as source\n", __FUNCTION__, __LINE__);
    // Configure this decompressor to read its data from a memory
    // buffer starting at unsigned char *pu8JpgBuffer, which is u32JpgSize
    // long, and which must contain a complete jpg already.
    //
    // If you need something fancier than this, you must write your
    // own data source manager, which shouldn't be too hard if you know
    // what it is you need it to do. See jpeg-8d/jdatasrc.c for the
    // implementation of the standard jpeg_mem_src and jpeg_stdio_src
    // managers as examples to work from.
    jpeg_mem_src(&cinfo, pu8JpgBuffer, u32JpgSize);

    BOOTLOGO_DBG(BOOTLOGO_DBG_LEVEL_JPD, "%s %d::  Read the JPEG header\n", __FUNCTION__, __LINE__);
    // Have the decompressor scan the jpeg header. This won't populate
    // the cinfo struct output fields, but will indicate if the
    // jpeg is valid.
    rc = jpeg_read_header(&cinfo, TRUE);

    if (rc != 1)
    {
        BOOTLOGO_DBG(BOOTLOGO_DBG_LEVEL_ERR, "%s %d:: File does not seem to be a normal JPEG\n", __FUNCTION__, __LINE__);
        return;
    }


    BOOTLOGO_DBG(BOOTLOGO_DBG_LEVEL_JPD,"%s %d::  Initiate JPEG decompression\n", __FUNCTION__, __LINE__);

    // output color space is yuv444 packet
	cinfo.out_color_space = JCS_YCbCr;

    jpeg_start_decompress(&cinfo);

    u16Width = cinfo.output_width;
    u16Height = cinfo.output_height;
    u16PixelSize = cinfo.output_components;
    *pu16OutWidth = u16Width;
    *pu16OutHeight = u16Height;

    BOOTLOGO_DBG(BOOTLOGO_DBG_LEVEL_JPD, "%s %d::  Image is %d by %d with %d components\n",
        __FUNCTION__, __LINE__, u16Width, u16Height, u16PixelSize);


	u32BmpSize = u16Width * u16Height * u16PixelSize;
	pu8BmpBuffer =(u8 *) malloc(u32BmpSize);

    if(pu8BmpBuffer == NULL)
    {
        BOOTLOGO_DBG(BOOTLOGO_DBG_LEVEL_ERR, "%s %d:: malloc fail\n", __FUNCTION__, __LINE__);
        return;
    }

    BOOTLOGO_DBG(BOOTLOGO_DBG_LEVEL_JPD, "%s %d:: BmpBuffer: 0x%x\n", __FUNCTION__, __LINE__, (u32)pu8BmpBuffer);
    u32Yuv420Size = u16Width * u16Height * 3 / 2;
    pu8Yuv420Buffer = (unsigned char *)((u32)pstBootlogoImgCfg->u64OutBuffAddr);

    if( u32Yuv420Size > pstBootlogoImgCfg->u32OutBuffSize)
    {
        BOOTLOGO_DBG(BOOTLOGO_DBG_LEVEL_ERR,"%s %d:: Output buffer is too big, %d\n",
            __FUNCTION__, __LINE__, u16Width * u16Height * u16PixelSize);
        return;
    }

	u16RowStride = u16Width * u16PixelSize;

    BOOTLOGO_DBG(BOOTLOGO_DBG_LEVEL_JPD,"%s %d:: Start reading scanlines\n", __FUNCTION__, __LINE__);
	while (cinfo.output_scanline < cinfo.output_height)
	{
		unsigned char *buffer_array[1];
		buffer_array[0] = pu8BmpBuffer + \
						   (cinfo.output_scanline) * u16RowStride;

		jpeg_read_scanlines(&cinfo, buffer_array, 1);
	}

    BOOTLOGO_DBG(BOOTLOGO_DBG_LEVEL_JPD,"%s %d:: Done reading scanlines\n", __FUNCTION__, __LINE__);
    jpeg_finish_decompress(&cinfo);

    jpeg_destroy_decompress(&cinfo);

    BOOTLOGO_DBG(BOOTLOGO_DBG_LEVEL_JPD,"%s %d:: End of decompression\n", __FUNCTION__, __LINE__);
    _BootLogoYuv444ToYuv420(pu8BmpBuffer, pu8Yuv420Buffer, u16Width, u16Height);

    free(pu8BmpBuffer);
#endif
}


void _BootLogoDispCtrl(BootlogoImgConfig_t  *pstBootlogoImgCfg, u16 u16JpdWidth, u16 u16JpdHeight)
{
#if defined(CONFIG_SSTAR_DISP)
    MHAL_DISP_AllocPhyMem_t stPhyMem;
    MHAL_DISP_DeviceTimingInfo_t stTimingInfo;
    MHAL_DISP_InputPortAttr_t stInputAttr;
    MHAL_DISP_VideoFrameData_t stVideoFrameBuffer;

    void *pDevCtx, *pVidLayerCtx, *pInputPortCtx;
    u32 u32Interface = 0;

    stPhyMem.alloc = BootLogoMemAlloc;
    stPhyMem.free  = BootLogoMemRelease;

    //Inint Pnl Tbl
    _BootLogoPnlInit();

    if(pstBootlogoImgCfg->u8Interface & DISP_DEVICE_LCD)
    {
        u32Interface = MHAL_DISP_INTF_LCD;
    }
    else
    {
        u32Interface |= (pstBootlogoImgCfg->u8Interface & DISP_DEVICE_HDMI) ? MHAL_DISP_INTF_HDMI : 0;
        u32Interface |= (pstBootlogoImgCfg->u8Interface & DISP_DEVICE_VGA)  ? MHAL_DISP_INTF_VGA : 0;
    }

    if(MHAL_DISP_DeviceCreateInstance(&stPhyMem, 0, &pDevCtx) == FALSE)
    {
        BOOTLOGO_DBG(BOOTLOGO_DBG_LEVEL_ERR, "%s %d, CreateDevice Fail\n", __FUNCTION__, __LINE__);
        return;
    }

    if(MHAL_DISP_VideoLayerCreateInstance(&stPhyMem, 0, &pVidLayerCtx) == FALSE)
    {
        BOOTLOGO_DBG(BOOTLOGO_DBG_LEVEL_ERR, "%s %d, CreateVideoLayer Fail\n", __FUNCTION__, __LINE__);
        return;

    }

    if(MHAL_DISP_InputPortCreateInstance(&stPhyMem, pVidLayerCtx, 0, &pInputPortCtx) == FALSE)
    {
        BOOTLOGO_DBG(BOOTLOGO_DBG_LEVEL_ERR, "%s %d, CreaetInputPort Fail\n", __FUNCTION__, __LINE__);
        return;
    }


    MHAL_DISP_DeviceSetBackGroundColor(pDevCtx, 0x00FFFFFF);
    MHAL_DISP_DeviceEnable(pDevCtx, 0);
    MHAL_DISP_DeviceAddOutInterface(pDevCtx, u32Interface);

    if(u32Interface == MHAL_DISP_INTF_LCD)
    {
        MHAL_DISP_SyncInfo_t stSyncInfo;

        if(pstBootlogoImgCfg->panelname[0] != 0)
        {
            stSyncInfo.u16Vact = pstBootlogoImgCfg->stPnlPara.u16Height;
            stSyncInfo.u16Vbb  = pstBootlogoImgCfg->stPnlPara.u16VSyncBackPorch;
            stSyncInfo.u16Vpw  = pstBootlogoImgCfg->stPnlPara.u16VSyncWidth;
            stSyncInfo.u16Vfb  = pstBootlogoImgCfg->stPnlPara.u16VTotal - stSyncInfo.u16Vact - stSyncInfo.u16Vbb - stSyncInfo.u16Vpw;
            stSyncInfo.u16Hact = pstBootlogoImgCfg->stPnlPara.u16Width;
            stSyncInfo.u16Hbb  = pstBootlogoImgCfg->stPnlPara.u16HSyncBackPorch;
            stSyncInfo.u16Hpw  = pstBootlogoImgCfg->stPnlPara.u16HSyncWidth;
            stSyncInfo.u16Hfb  = pstBootlogoImgCfg->stPnlPara.u16HTotal - stSyncInfo.u16Hact - stSyncInfo.u16Hbb - stSyncInfo.u16Hpw;
            stSyncInfo.u32FrameRate = pstBootlogoImgCfg->u8DisplayRate;

            BOOTLOGO_DBG(BOOTLOGO_DBG_LEVEL_INFO, "%s %d, H(%d %d %d %d) V(%d %d %d %d) Fps:%d\n",
                __FUNCTION__, __LINE__,
                stSyncInfo.u16Hfb, stSyncInfo.u16Hpw, stSyncInfo.u16Hbb, stSyncInfo.u16Hact,
                stSyncInfo.u16Vfb, stSyncInfo.u16Vpw, stSyncInfo.u16Vbb, stSyncInfo.u16Vact,
                stSyncInfo.u32FrameRate);

            stTimingInfo.eTimeType = E_MHAL_DISP_OUTPUT_USER;
            stTimingInfo.pstSyncInfo = &stSyncInfo;
            MHAL_DISP_DeviceSetOutputTiming(pDevCtx, MHAL_DISP_INTF_LCD, &stTimingInfo);
        }
        else
        {
            BOOTLOGO_DBG(BOOTLOGO_DBG_LEVEL_ERR, "%s %d, No stPnlPara Fail\n", __FUNCTION__, __LINE__);
            return;
        }
    }
    else
    {
        stTimingInfo.eTimeType = _BootLogoGetTiminId(pstBootlogoImgCfg->u16DisplayWidth,
                                                     pstBootlogoImgCfg->u16DisplayHeight,
                                                     pstBootlogoImgCfg->u8DisplayRate);
        stTimingInfo.pstSyncInfo = NULL;
        MHAL_DISP_DeviceSetOutputTiming(pDevCtx, u32Interface, &stTimingInfo);
    }
    MHAL_DISP_DeviceEnable(pDevCtx, 1);

    stInputAttr.stDispWin.u16X = 0;
    stInputAttr.stDispWin.u16Y = 0;
    stInputAttr.stDispWin.u16Width = pstBootlogoImgCfg->u16DisplayWidth;
    stInputAttr.stDispWin.u16Height = pstBootlogoImgCfg->u16DisplayHeight;
    stInputAttr.u16SrcWidth = u16JpdWidth;
    stInputAttr.u16SrcHeight = u16JpdHeight;

    stVideoFrameBuffer.aPhyAddr[0] = pstBootlogoImgCfg->u64OutBuffAddr;
    stVideoFrameBuffer.aPhyAddr[1] = pstBootlogoImgCfg->u64OutBuffAddr + u16JpdWidth * u16JpdHeight;
    stVideoFrameBuffer.au32Stride[0] = u16JpdWidth;

    MHAL_DISP_InputPortSetAttr(pInputPortCtx, &stInputAttr);
    MHAL_DISP_InputPortFlip(pInputPortCtx, &stVideoFrameBuffer);
    MHAL_DISP_InputPortEnable(pInputPortCtx, TRUE);
#endif
}

void _BootLogoPnlCtrl(BootlogoImgConfig_t *pstBootLogoImgCfg)
{
#if defined(CONFIG_SSTAR_PNL)
    void *pPnlDev;
    if(pstBootLogoImgCfg->u8Interface == DISP_DEVICE_LCD && pstBootLogoImgCfg->panelname[0] != 0)
    {
        BOOTLOGO_DBG(BOOTLOGO_DBG_LEVEL_INFO, "%s %d, PnlLink:%d\n",
            __FUNCTION__, __LINE__, pstBootLogoImgCfg->stPnlPara.eLinkType);
        if(MhalPnlCreateInstance(&pPnlDev, pstBootLogoImgCfg->stPnlPara.eLinkType) == FALSE)
        {
            BOOTLOGO_DBG(BOOTLOGO_DBG_LEVEL_ERR, "%s %d, PnlCreateInstance Fail\n", __FUNCTION__, __LINE__);
            return;
        }

        MhalPnlSetParamConfig(pPnlDev, &pstBootLogoImgCfg->stPnlPara);

        if(pstBootLogoImgCfg->stPnlPara.eLinkType == E_MHAL_PNL_LINK_MIPI_DSI)
        {
            MhalPnlSetMipiDsiConfig(pPnlDev, &pstBootLogoImgCfg->stMipiDsiCfg);
        }
    }
#endif
}

void _BootLogoHdmitxCtrl(BootlogoImgConfig_t *pstBootLogoImgCfg)
{
#if defined(CONFIG_SSTAR_HDMITX)
    HDMITX_VIDEO_COLOR_FORMAT enInColor;
    HDMITX_VIDEO_COLOR_FORMAT enOutColor;
    HDMITX_OUTPUT_MODE enOutputMode;
    HDMITX_VIDEO_COLORDEPTH_VAL enColorDepth;
    HDMITX_VIDEO_TIMING enOutputTiming;
    HDMITX_ANALOG_TUNING stHDInfo = HDMITX_ANALOG_TUNING_HD;

    if(pstBootLogoImgCfg->u8Interface & DISP_DEVICE_HDMI)
    {
        enInColor = HDMITX_VIDEO_COLOR_RGB444;
        enOutColor = HDMITX_VIDEO_COLOR_RGB444;
        enOutputMode = HDMITX_HDMI;
        enColorDepth = HDMITX_VIDEO_CD_NoID;
        enOutputTiming = _BootLogoGetHdmitxTimingId(pstBootLogoImgCfg->u16DisplayWidth, pstBootLogoImgCfg->u16DisplayHeight, pstBootLogoImgCfg->u8DisplayRate);

        MApi_HDMITx_Init();

        MApi_HDMITx_SetHPDGpioPin(26);

        MApi_HDMITx_UnHDCPRxControl(E_UNHDCPRX_BLUE_SCREEN);
        MApi_HDMITx_HDCPRxFailControl(E_UNHDCPRX_BLUE_SCREEN);

        MApi_HDMITx_SetHDCPOnOff(FALSE);
        MApi_HDMITx_HDCP_StartAuth(FALSE);
        MApi_HDMITx_AnalogTuning(&stHDInfo);

        MApi_HDMITx_SetHDMITxMode(enOutputMode);
        MApi_HDMITx_SetColorFormat(enInColor, enOutColor);
        MApi_HDMITx_SetHDMITxMode_CD(enOutputMode, enColorDepth);
        MApi_HDMITx_SetVideoOutputTiming(enOutputTiming);
        MApi_HDMITx_TurnOnOff(TRUE);
        MApi_HDMITx_SetVideoOnOff(TRUE);

        MApi_HDMITx_SetAudioConfiguration(HDMITX_AUDIO_48K, HDMITX_AUDIO_CH_2, HDMITX_AUDIO_PCM);
        MApi_HDMITx_SetAudioSourceFormat(HDMITX_AUDIO_FORMAT_PCM);
        MApi_HDMITx_SetAudioFrequency(HDMITX_AUDIO_48K);
        MApi_HDMITx_SetAudioOnOff(TRUE);

        //MApi_HDMITx_Exhibit();
    }
#endif
}


int do_display (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    #define BUFFERSIZE (640*480*3)

    BootlogoImgConfig_t  stBootlogoImgCfg;
    u16 u16JpdWidth, u16JpdHeight;
    bool bParamSet = 0;
    static u8 *pu8InBuf = NULL;
    static u8 *pu8OutBuf = NULL;
    static u32 u32InBufSize = BUFFERSIZE;
    static u32 u32OutBufSize = BUFFERSIZE;

    BOOTLOGO_DBG(BOOTLOGO_DBG_LEVEL_INFO,"%s %d, argc =%d\n", __FUNCTION__, __LINE__, argc);

    memset(&stBootlogoImgCfg, 0, sizeof(BootlogoImgConfig_t));
    if(argc == 1)
    {
        if(_BootLogoGetImageConfig(&stBootlogoImgCfg) == FALSE)
        {
            bParamSet = 0;
            BOOTLOGO_DBG(BOOTLOGO_DBG_LEVEL_ERR, "%s %d, GetImage fail\n", __FUNCTION__, __LINE__);
        }
        else
        {
            bParamSet = 1;
        }
    }
    else if(argc == 2)
    {
        if(strcmp(argv[1], "malloc") == 0)
        {
            pu8InBuf = (u8 *) malloc(u32InBufSize);
            pu8OutBuf = (u8 *) malloc(u32OutBufSize);
            printf("InBuffer: 0x%x Size:0x%x OutBuf: 0x%x, Size: 0x%x\n",
                (u32)pu8InBuf, u32InBufSize, (u32)pu8OutBuf, u32OutBufSize);
        }
    }
    else if(argc ==3)
    {
        if(strcmp(argv[1], "insize") == 0)
        {
            u32InBufSize = simple_strtoul(argv[2], NULL, 16);
        }
        else if(strcmp(argv[1], "outsize") == 0)
        {
            u32OutBufSize = simple_strtoul(argv[2], NULL, 16);
        }
    }
    else if(argc == 5)
    {
        if(pu8InBuf == NULL || pu8OutBuf == NULL || u32InBufSize == 0 || u32OutBufSize == 0)
        {
            bParamSet = 0;
            BOOTLOGO_DBG(BOOTLOGO_DBG_LEVEL_ERR, "insize outsize malloc first\n");
        }
        else
        {
            stBootlogoImgCfg.u64InBuffAddr    = (u32)pu8InBuf;
            stBootlogoImgCfg.u32InBuffSize    = u32InBufSize;

            stBootlogoImgCfg.u64OutBuffAddr   = (u32)pu8OutBuf;
            stBootlogoImgCfg.u32OutBuffSize   = u32OutBufSize;

            if(stBootlogoImgCfg.u64OutBuffAddr & 0x0F)
            {   // 16 align
                u64 u64NewAddr;
                u64NewAddr = (stBootlogoImgCfg.u64OutBuffAddr + 0x0F) & 0xFFFFFFF0;
                stBootlogoImgCfg.u32OutBuffSize = u32OutBufSize - (u64NewAddr - stBootlogoImgCfg.u64OutBuffAddr);
                stBootlogoImgCfg.u64OutBuffAddr = u64NewAddr;
            }

            stBootlogoImgCfg.u16DisplayWidth  = simple_strtoul(argv[1], NULL, 10);
            stBootlogoImgCfg.u16DisplayHeight = simple_strtoul(argv[2], NULL, 10);
            stBootlogoImgCfg.u8DisplayRate    = simple_strtoul(argv[3], NULL, 10);
            stBootlogoImgCfg.u8Interface      = simple_strtoul(argv[4], NULL, 10);

            // for FPGA test
            stBootlogoImgCfg.panelname[0] = 1;

            stBootlogoImgCfg.stPnlPara.eLinkType = E_MHAL_PNL_LINK_TTL;
            stBootlogoImgCfg.stPnlPara.u16HSyncWidth = stTimingTable[4].u16HsyncWidht;;
            stBootlogoImgCfg.stPnlPara.u16HSyncBackPorch = stTimingTable[4].u16HsyncBacPorch;

            stBootlogoImgCfg.stPnlPara.u16VSyncWidth = stTimingTable[4].u16VsyncWidht;;
            stBootlogoImgCfg.stPnlPara.u16VSyncBackPorch = stTimingTable[4].u16VsyncBacPorch;

            stBootlogoImgCfg.stPnlPara.u16HStart = stTimingTable[4].u16Hstart;
            stBootlogoImgCfg.stPnlPara.u16VStart = stTimingTable[4].u16Vstart;

            stBootlogoImgCfg.stPnlPara.u16Width = stTimingTable[4].u16Hactive;
            stBootlogoImgCfg.stPnlPara.u16Height = stTimingTable[4].u16Vactive;

            stBootlogoImgCfg.stPnlPara.u16HTotal = stTimingTable[4].u16Htotal;
            stBootlogoImgCfg.stPnlPara.u16VTotal = stTimingTable[4].u16Vtotal;
            stBootlogoImgCfg.stPnlPara.u16DCLK   = (stTimingTable[4].u16Htotal * stTimingTable[4].u16Vtotal * stBootlogoImgCfg.u8DisplayRate)/1000000;

            bParamSet = 1;
        }
    }
    else
    {
        BOOTLOGO_DBG(BOOTLOGO_DBG_LEVEL_ERR, "bootlogo [In Addr] [In Size] [Out Addr] [Out Size] [Disp Width] [Disp Height] [Disp Rate] [Interface]\n");
        bParamSet = 0;
    }

    if(bParamSet)
    {
        BOOTLOGO_DBG(BOOTLOGO_DBG_LEVEL_INFO, "%s %d:: In(%llx %x), Out(%llx %x), Disp(%d %d %d) Interface:%d\n",
            __FUNCTION__, __LINE__,
            stBootlogoImgCfg.u64InBuffAddr, stBootlogoImgCfg.u32InBuffSize,
            stBootlogoImgCfg.u64OutBuffAddr, stBootlogoImgCfg.u32OutBuffSize,
            stBootlogoImgCfg.u16DisplayWidth, stBootlogoImgCfg.u16DisplayHeight, stBootlogoImgCfg.u8DisplayRate,
            stBootlogoImgCfg.u8Interface);

        if(stBootlogoImgCfg.u32InBuffSize && stBootlogoImgCfg.u32OutBuffSize)
        {
            _BootLogoJpdCtrl(&stBootlogoImgCfg, &u16JpdWidth, &u16JpdHeight);
        }

        _BootLogoDispCtrl(&stBootlogoImgCfg, u16JpdWidth, u16JpdHeight);
        _BootLogoHdmitxCtrl(&stBootlogoImgCfg);
        _BootLogoPnlCtrl(&stBootlogoImgCfg);
        return 0;
    }
    else
    {
        return 1;
    }
}

U_BOOT_CMD(
	bootlogo, CONFIG_SYS_MAXARGS, 1,    do_display,
	"show bootlogo",
	NULL
);


