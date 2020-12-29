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


#define _DRV_DISP_MODULE_C_

#include <linux/cdev.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/of_address.h>
#include <linux/of_irq.h>

#include "ms_msys.h"
#include "cam_os_wrapper.h"
#include "disp_sysfs.h"
#include "disp_debug.h"

#include "mhal_common.h"
#include "mhal_disp_datatype.h"
#include "hal_disp_chip.h"
#include "hal_disp_st.h"
#include "drv_disp_ctx.h"
#include "drv_disp_irq.h"
//-------------------------------------------------------------------------------------------------
// Define & Macro
//-------------------------------------------------------------------------------------------------
#define DRV_DISP_DEVICE_COUNT    1
#define DRV_DISP_DEVICE_NAME     "mdisp"
#define DRV_DISP_DEVICE_MAJOR    0xEC
#define DRV_DISP_DEVICE_MINOR    0x10

//-------------------------------------------------------------------------------------------------
// Prototype
//-------------------------------------------------------------------------------------------------
static int DrvDispModuleProbe(struct platform_device *pdev);
static int DrvDispModuleRemove(struct platform_device *pdev);
static int DrvDispModuleSuspend(struct platform_device *dev, pm_message_t state);
static int DrvDispModuleResume(struct platform_device *dev);

//-------------------------------------------------------------------------------------------------
// Structure
//-------------------------------------------------------------------------------------------------
typedef struct
{
    int s32Major;
    int s32Minor;
    int refCnt;
    struct cdev cdev;
    struct file_operations fops;
    struct device *devicenode;
}DrvDispModuleDevice_t;

//-------------------------------------------------------------------------------------------------
// Variable
//-------------------------------------------------------------------------------------------------
static DrvDispModuleDevice_t _tDispDevice =
{
    .s32Major = DRV_DISP_DEVICE_MAJOR,
    .s32Minor = DRV_DISP_DEVICE_MINOR,
    .refCnt = 0,
    .devicenode = NULL,
    .cdev =
    {
        .kobj = {.name= DRV_DISP_DEVICE_NAME, },
        .owner = THIS_MODULE,
    },
    /*
    .fops =
    {
        .open = DrvDispModuleOpen,
        .release = DrvDispModuleRelease,
        .unlocked_ioctl = DrvDispModuleIoctl,
        .poll = DrvDispModulePoll,
    },*/
};

static struct class * _tDispClass = NULL;
static char * DispClassName = "m_disp_class";


static const struct of_device_id _DispMatchTable[] =
{
    { .compatible = "sstar,disp" },
    {}
};

static struct platform_driver stDrvDispPlatformDriver =
{
    .probe      = DrvDispModuleProbe,
    .remove     = DrvDispModuleRemove,
    .suspend    = DrvDispModuleSuspend,
    .resume     = DrvDispModuleResume,
    .driver =
    {
        .name   = DRV_DISP_DEVICE_NAME,
        .owner  = THIS_MODULE,
        .of_match_table = of_match_ptr(_DispMatchTable),
    },
};

static u64 u64SclHvsp_DmaMask = 0xffffffffUL;

static struct platform_device stDrvDispPlatformDevice =
{
    .name = DRV_DISP_DEVICE_NAME,
    .id = 0,
    .dev =
    {
        .of_node = NULL,
        .dma_mask = &u64SclHvsp_DmaMask,
        .coherent_dma_mask = 0xffffffffUL
    }
};

//-------------------------------------------------------------------------------------------------
// internal function
//-------------------------------------------------------------------------------------------------


//==============================================================================
static int DrvDispModuleSuspend(struct platform_device *dev, pm_message_t state)
{
    int ret = 0;
    return ret;
}

static int DrvDispModuleResume(struct platform_device *dev)
{
    int ret = 0;
    DISP_DBG(DISP_DBG_LEVEL_IO, "[DISP] %s\n",__FUNCTION__);
    return ret;
}


void _DrvDispRemove(void)
{
    DISP_DBG(DISP_DBG_LEVEL_IO, "[DISP] %s\n",__FUNCTION__);
    if(_tDispDevice.cdev.count)
    {
        cdev_del(&_tDispDevice.cdev);
    }
    stDrvDispPlatformDevice.dev.of_node=NULL;
    _tDispClass = NULL;
}

void _DrvDispGetIrqNum(struct platform_device *pDev, u8 u8Idx, u8 u8DevId)
{
    unsigned int DispIrqId = 0; //INT_IRQ_AU_SYSTEM;

    DispIrqId  = of_irq_to_resource(pDev->dev.of_node, u8Idx, NULL);

    if (!DispIrqId)
    {
        DISP_ERR("[DISPMODULE] Can't Get SCL_IRQ, Idx=%d, DevId=%d\n", u8Idx,u8DevId);
    }
    else
    {
        DrvDispIrqSetIsrNum(u8DevId, DispIrqId);
    }
}


void _DrvDispModuleInit(void)
{
    int s32Ret;
    dev_t  dev;

    if(_tDispDevice.s32Major)
    {
        dev     = MKDEV(_tDispDevice.s32Major, _tDispDevice.s32Minor);
        if(!_tDispClass)
        {
            _tDispClass = msys_get_sysfs_class();
            if(!_tDispClass)
            {
                _tDispClass = class_create(THIS_MODULE, DispClassName);
            }

        }
        else
        {
            cdev_init(&_tDispDevice.cdev, &_tDispDevice.fops);
            if (0 != (s32Ret= cdev_add(&_tDispDevice.cdev, dev, DRV_DISP_DEVICE_COUNT)))
            {
                DISP_ERR( "[SCLHVSP_1] Unable add a character device\n");
            }
        }
        //ToDo
        if(_tDispDevice.devicenode==NULL)
        {
            _tDispDevice.devicenode = device_create(_tDispClass, NULL, dev,NULL, DRV_DISP_DEVICE_NAME);
            DrvDispSysfsInit(_tDispDevice.devicenode);
        }

        if(stDrvDispPlatformDevice.dev.of_node==NULL)
        {
            stDrvDispPlatformDevice.dev.of_node = of_find_compatible_node(NULL, NULL, "sstar,disp");
        }
        if(stDrvDispPlatformDevice.dev.of_node==NULL)
        {
            DISP_ERR("[VPE INIT] Get Device mode Fail!!\n");
        }

        //Get IRQ
    }
    _DrvDispGetIrqNum(&stDrvDispPlatformDevice, 0, 0);
    _DrvDispGetIrqNum(&stDrvDispPlatformDevice, 1, 1);
}



//-------------------------------------------------------------------------------------------------
// Module functions
//-------------------------------------------------------------------------------------------------
static int DrvDispModuleProbe(struct platform_device *pdev)
{
    //unsigned char ret;
    int s32Ret;
    dev_t  dev;
    //struct resource *res_irq;
    //struct device_node *np;
    DISP_DBG(DISP_DBG_LEVEL_IO, "[DISP] %s:%d\n",__FUNCTION__,__LINE__);

    if(_tDispDevice.s32Major == 0)
    {
        s32Ret                  = alloc_chrdev_region(&dev, _tDispDevice.s32Minor, DRV_DISP_DEVICE_COUNT, DRV_DISP_DEVICE_NAME);
        _tDispDevice.s32Major  = MAJOR(dev);
    }

    _tDispClass = msys_get_sysfs_class();
    if(!_tDispClass)
    {
        _tDispClass = class_create(THIS_MODULE, DispClassName);
    }
    if(IS_ERR(_tDispClass))
    {
        DISP_ERR("Failed at class_create().Please exec [mknod] before operate the device/n");
    }
    else
    {
        //_tDispDevice.devicenode->dma_mask=&u64SclHvsp_DmaMask;
        //_tDispDevice.devicenode->coherent_dma_mask=u64SclHvsp_DmaMask;
    }
    //probe
    DISP_DBG(DISP_DBG_LEVEL_IO, "[DISP] %s\n",__FUNCTION__);
    stDrvDispPlatformDevice.dev.of_node = pdev->dev.of_node;

    //create device
    _DrvDispModuleInit();

#if defined(SCLOS_TYPE_LINUX_TEST)
    //UTest_init(); ToDo: [Ryan] UTest_Init
#endif
    return 0;
}
static int DrvDispModuleRemove(struct platform_device *pdev)
{
    DISP_DBG(DISP_DBG_LEVEL_IO, "[DISP] %s\n",__FUNCTION__);
    _DrvDispRemove();
    //ToDo
    device_unregister(_tDispDevice.devicenode);
    return 0;
}

int DrvDispModuleInit(void)
{
    int ret = 0;

    DISP_DBG(DISP_DBG_LEVEL_IO, "[DISP] %s:%d\n",__FUNCTION__,__LINE__);


    ret = platform_driver_register(&stDrvDispPlatformDriver);
    if (!ret)
    {
        DISP_DBG(DISP_DBG_LEVEL_IO, "[DISP] platform_driver_register success\n");
    }
    else
    {
        DISP_ERR( "[SCLHVSP_1] platform_driver_register failed\n");
        platform_driver_unregister(&stDrvDispPlatformDriver);
    }

    return ret;
}
void DrvDispModuleExit(void)
{
    /*de-initial the who GFLIPDriver */
    DISP_DBG(DISP_DBG_LEVEL_IO, "[DISP] %s\n",__FUNCTION__);
    platform_driver_unregister(&stDrvDispPlatformDriver);
}

module_init(DrvDispModuleInit);
module_exit(DrvDispModuleExit);

MODULE_AUTHOR("SSTAR");
MODULE_DESCRIPTION("sstar sclhvsp ioctrl driver");
MODULE_LICENSE("GPL");
