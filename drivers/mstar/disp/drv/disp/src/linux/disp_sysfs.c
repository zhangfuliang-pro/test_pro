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


#define _DISP_SYSFS_C_

#include <linux/device.h>
#include "cam_os_wrapper.h"
#include "disp_ut.h"

#ifdef DISP_OS_TYPE_LINUX_TEST

ssize_t check_disptest_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t n)
{
    if(NULL!=buf)
    {
        DispUtStrConfig_t stStringCfg;

        DispUtParsingCommand((char *)buf, &stStringCfg);

        DispTestStore(&stStringCfg);
        return n;
    }
    return 0;
}

ssize_t check_disptest_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    char ShowStr[1024*3];
    memset(ShowStr, '\0', sizeof(1024*3));
    DispTestShow(ShowStr);

    return sprintf(buf, "%s", ShowStr);
}
static DEVICE_ATTR(test,0644, check_disptest_show, check_disptest_store);
#endif

ssize_t check_dispdbgmg_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t n)
{
    if(NULL!=buf)
    {
        DispUtStrConfig_t stStringCfg;

        DispUtParsingCommand((char *)buf, &stStringCfg);
        DispDbgmgStore(&stStringCfg);
        return n;
    }
    return 0;
}

ssize_t check_dispdbgmg_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    char ShowStr[1024*3];
    memset(ShowStr, '\0', sizeof(1024*3));
    DispDbgmgShow(ShowStr);

    return sprintf(buf, "%s", ShowStr);
}

static DEVICE_ATTR(dbgmg,0644, check_dispdbgmg_show, check_dispdbgmg_store);


ssize_t check_dispptgen_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t n)
{
    if(NULL!=buf)
    {
        DispUtStrConfig_t stStringCfg;

        DispUtParsingCommand((char *)buf, &stStringCfg);
        DispPtGenStore(&stStringCfg);
        return n;
    }
    return 0;
}

ssize_t check_dispptgen_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    char ShowStr[1024*3];
    memset(ShowStr, '\0', sizeof(1024*3));
    DispPtGenShow(ShowStr);

    return sprintf(buf, "%s", ShowStr);
}

static DEVICE_ATTR(ptgen,0644, check_dispptgen_show, check_dispptgen_store);


ssize_t check_disppq_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t n)
{
    if(NULL!=buf)
    {
        DispUtStrConfig_t stStringCfg;

        DispUtParsingCommand((char *)buf, &stStringCfg);

        DispPqStore(&stStringCfg);

        return n;
    }
    return 0;
}

ssize_t check_disppq_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    char ShowStr[1024*3];
    memset(ShowStr, '\0', sizeof(1024*3));
    DispPqShow(ShowStr);

    return sprintf(buf, "%s", ShowStr);
}

static DEVICE_ATTR(pq,0644, check_disppq_show, check_disppq_store);



void DrvDispSysfsInit(struct device *device)
{
#ifdef DISP_OS_TYPE_LINUX_TEST
    device_create_file(device, &dev_attr_test);
#endif

    device_create_file(device, &dev_attr_dbgmg);
    device_create_file(device, &dev_attr_ptgen);
    device_create_file(device, &dev_attr_pq);
}
