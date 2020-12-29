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


#define _PNL_SYSFS_C_

#include <linux/device.h>
#include "pnl_ut.h"

ssize_t check_pnldbgmg_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t n)
{
    if(NULL!=buf)
    {
        PnlUtStrConfig_t stStrCfg;

        PnlUtParsingString((char *)buf, &stStrCfg);
        PnlDbgmgStore(&stStrCfg);
        return n;
    }
    return 0;
}

ssize_t check_pnldbgmg_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    char TestShowStr[1024*3];

    memset(TestShowStr, '\0', sizeof(1024*3));

    PnlDbgmgShow(TestShowStr);

    return sprintf(buf, "%s", TestShowStr);
}

static DEVICE_ATTR(dbgmg,0644, check_pnldbgmg_show, check_pnldbgmg_store);



#ifdef PNL_OS_TYPE_LINUX_TEST

ssize_t check_pnltest_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t n)
{
    if(NULL!=buf)
    {
        PnlUtStrConfig_t stStrCfg;

        PnlUtParsingString((char *)buf, &stStrCfg);
        PnlTestStore(&stStrCfg);
        return n;
    }
    return 0;
}

ssize_t check_pnltest_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    char TestShowStr[1024*3];

    memset(TestShowStr, '\0', sizeof(1024*3));

    PnlTestShow(TestShowStr);

    return sprintf(buf, "%s", TestShowStr);
}

static DEVICE_ATTR(test,0644, check_pnltest_show, check_pnltest_store);
#endif


void DrvPnlSysfsInit(struct device *device)
{
#ifdef PNL_OS_TYPE_LINUX_TEST
    device_create_file(device, &dev_attr_test);
#endif
    device_create_file(device, &dev_attr_dbgmg);
}
