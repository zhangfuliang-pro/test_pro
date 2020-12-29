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


#define _DRV_PNL_MODULE_C_
#ifdef PNL_OS_TYPE_LINUX_KERNEL
#include <linux/cdev.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/of_address.h>
#include "cam_os_wrapper.h"
#endif

#include "drv_pnl_os.h"
#include "ms_msys.h"
#include "pnl_sysfs.h"
#include "pnl_debug.h"
//-------------------------------------------------------------------------------------------------
// Define & Macro
//-------------------------------------------------------------------------------------------------
#define DRV_PNL_DEVICE_COUNT    1
#define DRV_PNL_DEVICE_NAME     "mpnl"
#define DRV_PNL_DEVICE_MAJOR    0xEB
#define DRV_PNL_DEVICE_MINOR    0x10

//-------------------------------------------------------------------------------------------------
// Prototype
//-------------------------------------------------------------------------------------------------
static int DrvPnlModuleProbe(struct platform_device *pdev);
static int DrvPnlModuleRemove(struct platform_device *pdev);
static int DrvPnlModuleSuspend(struct platform_device *dev, pm_message_t state);
static int DrvPnlModuleResume(struct platform_device *dev);

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
}DrvPnlModuleDevice_t;

//-------------------------------------------------------------------------------------------------
// Variable
//-------------------------------------------------------------------------------------------------
static DrvPnlModuleDevice_t _tPnlDevice =
{
    .s32Major = DRV_PNL_DEVICE_MAJOR,
    .s32Minor = DRV_PNL_DEVICE_MINOR,
    .refCnt = 0,
    .devicenode = NULL,
    .cdev =
    {
        .kobj = {.name= DRV_PNL_DEVICE_NAME, },
        .owner = THIS_MODULE,
    },
    /*
    .fops =
    {
        .open = DrvPnlModuleOpen,
        .release = DrvPnlModuleRelease,
        .unlocked_ioctl = DrvPnlModuleIoctl,
        .poll = DrvPnlModulePoll,
    },*/
};

static struct class * _tPnlClass = NULL;
static char * PnlClassName = "m_pnl_class";


static const struct of_device_id _PnlMatchTable[] =
{
    { .compatible = "sstar,pnl" },
    {}
};

static struct platform_driver stDrvPnlPlatformDriver =
{
    .probe      = DrvPnlModuleProbe,
    .remove     = DrvPnlModuleRemove,
    .suspend    = DrvPnlModuleSuspend,
    .resume     = DrvPnlModuleResume,
    .driver =
    {
        .name   = DRV_PNL_DEVICE_NAME,
        .owner  = THIS_MODULE,
        .of_match_table = of_match_ptr(_PnlMatchTable),
    },
};

static u64 u64SclHvsp_DmaMask = 0xffffffffUL;

static struct platform_device stDrvPnlPlatformDevice =
{
    .name = DRV_PNL_DEVICE_NAME,
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
static int DrvPnlModuleSuspend(struct platform_device *dev, pm_message_t state)
{
    int ret = 0;
    return ret;
}

static int DrvPnlModuleResume(struct platform_device *dev)
{
    int ret = 0;
    PNL_DBG(PNL_DBG_LEVEL_MODULE, "[PNL] %s\n",__FUNCTION__);
    return ret;
}


void _DrvPnlRemove(void)
{
    PNL_DBG(PNL_DBG_LEVEL_MODULE, "[PNL] %s\n",__FUNCTION__);
    if(_tPnlDevice.cdev.count)
    {
        cdev_del(&_tPnlDevice.cdev);
    }
    stDrvPnlPlatformDevice.dev.of_node=NULL;
    _tPnlClass = NULL;
}

void _DrvPnlModuleInit(void)
{
    int s32Ret;
    dev_t  dev;
    if(_tPnlDevice.s32Major)
    {
        dev     = MKDEV(_tPnlDevice.s32Major, _tPnlDevice.s32Minor);
        if(!_tPnlClass)
        {
            _tPnlClass = msys_get_sysfs_class();
            if(!_tPnlClass)
            {
                _tPnlClass = class_create(THIS_MODULE, PnlClassName);
            }

        }
        else
        {
            cdev_init(&_tPnlDevice.cdev, &_tPnlDevice.fops);
            if (0 != (s32Ret= cdev_add(&_tPnlDevice.cdev, dev, DRV_PNL_DEVICE_COUNT)))
            {
                PNL_ERR( "[SCLHVSP_1] Unable add a character device\n");
            }
        }
        //ToDo
        if(_tPnlDevice.devicenode==NULL)
        {
            _tPnlDevice.devicenode = device_create(_tPnlClass, NULL, dev,NULL, DRV_PNL_DEVICE_NAME);
            DrvPnlSysfsInit(_tPnlDevice.devicenode);
        }

        if(stDrvPnlPlatformDevice.dev.of_node==NULL)
        {
            stDrvPnlPlatformDevice.dev.of_node = of_find_compatible_node(NULL, NULL, "sstar,pnl");
        }
        if(stDrvPnlPlatformDevice.dev.of_node==NULL)
        {
            PNL_ERR("[VPE INIT] Get Device mode Fail!!\n");
        }

    }
}



//-------------------------------------------------------------------------------------------------
// Module functions
//-------------------------------------------------------------------------------------------------
static int DrvPnlModuleProbe(struct platform_device *pdev)
{
    //unsigned char ret;
    int s32Ret;
    dev_t  dev;
    //struct resource *res_irq;
    //struct device_node *np;
    PNL_DBG(PNL_DBG_LEVEL_MODULE, "[PNL] %s:%d\n",__FUNCTION__,__LINE__);

    if(_tPnlDevice.s32Major == 0)
    {
        s32Ret                  = alloc_chrdev_region(&dev, _tPnlDevice.s32Minor, DRV_PNL_DEVICE_COUNT, DRV_PNL_DEVICE_NAME);
        _tPnlDevice.s32Major  = MAJOR(dev);
    }

    _tPnlClass = msys_get_sysfs_class();
    if(!_tPnlClass)
    {
        _tPnlClass = class_create(THIS_MODULE, PnlClassName);
    }
    if(IS_ERR(_tPnlClass))
    {
        PNL_ERR("Failed at class_create().Please exec [mknod] before operate the device/n");
    }
    else
    {
        //_tPnlDevice.devicenode->dma_mask=&u64SclHvsp_DmaMask;
        //_tPnlDevice.devicenode->coherent_dma_mask=u64SclHvsp_DmaMask;
    }
    //probe
    PNL_DBG(PNL_DBG_LEVEL_MODULE, "[PNL] %s\n",__FUNCTION__);
    stDrvPnlPlatformDevice.dev.of_node = pdev->dev.of_node;

    //create device
    _DrvPnlModuleInit();

#if defined(SCLOS_TYPE_LINUX_TEST)
    //UTest_init(); ToDo: [Ryan] UTest_Init
#endif
    return 0;
}
static int DrvPnlModuleRemove(struct platform_device *pdev)
{
    PNL_DBG(PNL_DBG_LEVEL_MODULE, "[PNL] %s\n",__FUNCTION__);
    _DrvPnlRemove();
    //ToDo
    device_unregister(_tPnlDevice.devicenode);
    return 0;
}

int DrvPnlModuleInit(void)
{
    int ret = 0;

    PNL_DBG(PNL_DBG_LEVEL_MODULE, "[PNL] %s:%d\n",__FUNCTION__,__LINE__);


    ret = platform_driver_register(&stDrvPnlPlatformDriver);
    if (!ret)
    {
        PNL_DBG(PNL_DBG_LEVEL_MODULE, "[PNL] platform_driver_register success\n");
    }
    else
    {
        PNL_ERR( "[SCLHVSP_1] platform_driver_register failed\n");
        platform_driver_unregister(&stDrvPnlPlatformDriver);
    }

    return ret;
}
void DrvPnlModuleExit(void)
{
    /*de-initial the who GFLIPDriver */
    PNL_DBG(PNL_DBG_LEVEL_MODULE, "[PNL] %s\n",__FUNCTION__);
    platform_driver_unregister(&stDrvPnlPlatformDriver);
}

module_init(DrvPnlModuleInit);
module_exit(DrvPnlModuleExit);

MODULE_AUTHOR("SIGMASTAR");
MODULE_DESCRIPTION("sstar panel ioctrl driver");
MODULE_LICENSE("GPL");
