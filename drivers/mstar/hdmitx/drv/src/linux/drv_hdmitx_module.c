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


#define _DRV_HDMITX_MODULE_C_

#include <linux/cdev.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/of_address.h>
#include <linux/of_irq.h>

#include "ms_msys.h"
#include "cam_os_wrapper.h"
#include "hdmitx_sysfs.h"
#include "mhal_common.h"
//-------------------------------------------------------------------------------------------------
// Define & Macro
//-------------------------------------------------------------------------------------------------
#define DRV_HDMITX_DEVICE_COUNT    1
#define DRV_HDMITX_DEVICE_NAME     "mhdmitx"
#define DRV_HDMITX_DEVICE_MAJOR    0xEC
#define DRV_HDMITX_DEVICE_MINOR    0x18

//-------------------------------------------------------------------------------------------------
// Prototype
//-------------------------------------------------------------------------------------------------
static int DrvHdmitxModuleProbe(struct platform_device *pdev);
static int DrvHdmitxModuleRemove(struct platform_device *pdev);
static int DrvHdmitxModuleSuspend(struct platform_device *dev, pm_message_t state);
static int DrvHdmitxModuleResume(struct platform_device *dev);

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
}DrvHdmitxModuleDevice_t;

//-------------------------------------------------------------------------------------------------
// Variable
//-------------------------------------------------------------------------------------------------
static DrvHdmitxModuleDevice_t _tHdmitxDevice =
{
    .s32Major = DRV_HDMITX_DEVICE_MAJOR,
    .s32Minor = DRV_HDMITX_DEVICE_MINOR,
    .refCnt = 0,
    .devicenode = NULL,
    .cdev =
    {
        .kobj = {.name= DRV_HDMITX_DEVICE_NAME, },
        .owner = THIS_MODULE,
    },
    /*
    .fops =
    {
        .open = DrvHdmitxModuleOpen,
        .release = DrvHdmitxModuleRelease,
        .unlocked_ioctl = DrvHdmitxModuleIoctl,
        .poll = DrvHdmitxModulePoll,
    },*/
};

static struct class * _tHdmitxClass = NULL;
static char * HdmitxClassName = "m_hdmitx_class";


static const struct of_device_id _HdmitxMatchTable[] =
{
    { .compatible = "sstar,hdmitx" },
    {}
};

static struct platform_driver stDrvHdmitxPlatformDriver =
{
    .probe      = DrvHdmitxModuleProbe,
    .remove     = DrvHdmitxModuleRemove,
    .suspend    = DrvHdmitxModuleSuspend,
    .resume     = DrvHdmitxModuleResume,
    .driver =
    {
        .name   = DRV_HDMITX_DEVICE_NAME,
        .owner  = THIS_MODULE,
        .of_match_table = of_match_ptr(_HdmitxMatchTable),
    },
};

static u64 u64SclHvsp_DmaMask = 0xffffffffUL;

static struct platform_device stDrvHdmitxPlatformDevice =
{
    .name = DRV_HDMITX_DEVICE_NAME,
    .id = 0,
    .dev =
    {
        .of_node = NULL,
        .dma_mask = &u64SclHvsp_DmaMask,
        .coherent_dma_mask = 0xffffffffUL
    }
};

u32 _gu32HdmitxDbgLevel = 0;

//-------------------------------------------------------------------------------------------------
// internal function
//-------------------------------------------------------------------------------------------------


//==============================================================================
static int DrvHdmitxModuleSuspend(struct platform_device *dev, pm_message_t state)
{
    int ret = 0;
    return ret;
}

static int DrvHdmitxModuleResume(struct platform_device *dev)
{
    int ret = 0;
    printk("[HDMITX] %s\n",__FUNCTION__);
    return ret;
}


void _DrvHdmitxRemove(void)
{
    printk("[HDMITX] %s\n",__FUNCTION__);
    if(_tHdmitxDevice.cdev.count)
    {
        cdev_del(&_tHdmitxDevice.cdev);
    }
    stDrvHdmitxPlatformDevice.dev.of_node=NULL;
    _tHdmitxClass = NULL;
}

void _DrvHdmitxGetIrqNum(struct platform_device *pDev, u8 u8Idx, u8 u8DevId)
{
    unsigned int HdmitxIrqId = 0; //INT_IRQ_AU_SYSTEM;
    HdmitxIrqId  = of_irq_to_resource(pDev->dev.of_node, u8Idx, NULL);

    if (!HdmitxIrqId)
    {
        printk("[HDMITXMODULE] Can't Get SCL_IRQ\n");
    }
    else
    {
        //DrvHdmitxIrqSetIsrNum(u8DevId, HdmitxIrqId);
    }
}


void _DrvHdmitxModuleInit(void)
{
    int s32Ret;
    dev_t  dev;

    if(_tHdmitxDevice.s32Major)
    {
        dev     = MKDEV(_tHdmitxDevice.s32Major, _tHdmitxDevice.s32Minor);
        if(!_tHdmitxClass)
        {
        #ifndef CHIP_MV2
            _tHdmitxClass = msys_get_sysfs_class();
        #endif
            if(!_tHdmitxClass)
            {
                _tHdmitxClass = class_create(THIS_MODULE, HdmitxClassName);
            }

        }
        else
        {
            cdev_init(&_tHdmitxDevice.cdev, &_tHdmitxDevice.fops);
            if (0 != (s32Ret= cdev_add(&_tHdmitxDevice.cdev, dev, DRV_HDMITX_DEVICE_COUNT)))
            {
                printk( "[SCLHVSP_1] Unable add a character device\n");
            }
        }
        //ToDo
        if(_tHdmitxDevice.devicenode==NULL)
        {
            _tHdmitxDevice.devicenode = device_create(_tHdmitxClass, NULL, dev,NULL, DRV_HDMITX_DEVICE_NAME);
            DrvHdmitxSysfsInit(_tHdmitxDevice.devicenode);
        }

        if(stDrvHdmitxPlatformDevice.dev.of_node==NULL)
        {
            stDrvHdmitxPlatformDevice.dev.of_node = of_find_compatible_node(NULL, NULL, "sstar,hdmitx");
        }
        if(stDrvHdmitxPlatformDevice.dev.of_node==NULL)
        {
            printk("[VPE INIT] Get Device mode Fail!!\n");
        }

        //Get IRQ
    }
    //_DrvHdmitxGetIrqNum(&stDrvHdmitxPlatformDevice, 1, 0);
}



//-------------------------------------------------------------------------------------------------
// Module functions
//-------------------------------------------------------------------------------------------------
static int DrvHdmitxModuleProbe(struct platform_device *pdev)
{
    //unsigned char ret;
    int s32Ret;
    dev_t  dev;
    //struct resource *res_irq;
    //struct device_node *np;
    printk("[HDMITX] %s:%d\n",__FUNCTION__,__LINE__);

    if(_tHdmitxDevice.s32Major == 0)
    {
        s32Ret                  = alloc_chrdev_region(&dev, _tHdmitxDevice.s32Minor, DRV_HDMITX_DEVICE_COUNT, DRV_HDMITX_DEVICE_NAME);
        _tHdmitxDevice.s32Major  = MAJOR(dev);
    }

#ifndef CHIP_MV2
    _tHdmitxClass = msys_get_sysfs_class();
#endif

    if(!_tHdmitxClass)
    {
        _tHdmitxClass = class_create(THIS_MODULE, HdmitxClassName);
    }
    if(IS_ERR(_tHdmitxClass))
    {
        printk("Failed at class_create().Please exec [mknod] before operate the device/n");
    }
    else
    {
        //_tHdmitxDevice.devicenode->dma_mask=&u64SclHvsp_DmaMask;
        //_tHdmitxDevice.devicenode->coherent_dma_mask=u64SclHvsp_DmaMask;
    }
    //probe
    printk("[HDMITX] %s\n",__FUNCTION__);
    stDrvHdmitxPlatformDevice.dev.of_node = pdev->dev.of_node;

    //create device
    _DrvHdmitxModuleInit();

#if defined(SCLOS_TYPE_LINUX_TEST)
    //UTest_init(); ToDo: [Ryan] UTest_Init
#endif
    return 0;
}
static int DrvHdmitxModuleRemove(struct platform_device *pdev)
{
    printk("[HDMITX] %s\n",__FUNCTION__);
    _DrvHdmitxRemove();
    //ToDo
    device_unregister(_tHdmitxDevice.devicenode);
    return 0;
}

int DrvHdmitxModuleInit(void)
{
    int ret = 0;

    printk("[HDMITX] %s:%d\n",__FUNCTION__,__LINE__);


    ret = platform_driver_register(&stDrvHdmitxPlatformDriver);
    if (!ret)
    {
        printk("[HDMITX] platform_driver_register success\n");
    }
    else
    {
        printk( "[SCLHVSP_1] platform_driver_register failed\n");
        platform_driver_unregister(&stDrvHdmitxPlatformDriver);
    }

    return ret;
}
void DrvHdmitxModuleExit(void)
{
    /*de-initial the who GFLIPDriver */
    printk("[HDMITX] %s\n",__FUNCTION__);
    platform_driver_unregister(&stDrvHdmitxPlatformDriver);
}

module_init(DrvHdmitxModuleInit);
module_exit(DrvHdmitxModuleExit);

MODULE_AUTHOR("SIGMASTAR");
MODULE_DESCRIPTION("sstar sclhvsp ioctrl driver");
MODULE_LICENSE("GPL");
