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
#include "hdmitx_ut.h"

#ifdef HDMITX_OS_TYPE_LINUX_TEST

ssize_t check_hdmitxtest_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t n)
{
    if(NULL!=buf)
    {
        HdmitxUtStrConfig_t stStringCfg;

        HdmitxUtParsingCommand((char *)buf, &stStringCfg);

        HdmitxTestStore(&stStringCfg);
        return n;
    }
    return 0;
}

ssize_t check_hdmitxtest_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    return HdmitxTestShow(buf);
}
static DEVICE_ATTR(test,0644, check_hdmitxtest_show, check_hdmitxtest_store);
#endif

ssize_t check_hdmitxdbgmg_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t n)
{
    if(NULL!=buf)
    {
        HdmitxUtStrConfig_t stStringCfg;

        HdmitxUtParsingCommand((char *)buf, &stStringCfg);
        HdmitxDbgmgStore(&stStringCfg);
        return n;
    }
    return 0;
}

ssize_t check_hdmitxdbgmg_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    return HdmitxDbgmgShow(buf);
}

static DEVICE_ATTR(dbgmg,0644, check_hdmitxdbgmg_show, check_hdmitxdbgmg_store);




void DrvHdmitxSysfsInit(struct device *device)
{
    int ret;
#ifdef HDMITX_OS_TYPE_LINUX_TEST
    ret = device_create_file(device, &dev_attr_test);
#endif

    ret = device_create_file(device, &dev_attr_dbgmg);
}
