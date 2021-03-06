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

#include <common.h>
#include <usb.h>
#include "drvhostlib.h"
//#include "drvUSB.h"
#include "drvusbmain.h"

//extern Host20_Attach_Device_Structure   sAttachDevice  ;
//static USBCallback _DrvUSB_CBFun = NULL;
extern UINT8 bSpeed;
 int _s32UsbEventId;
int Usb_host_Init(void);
void MDrv_UsbClose(void);






//extern UINT8 bForceSpeed;//0=>All Clear 1=>Full Speed 2=>High Speed
#if 0
//U8 buf1[512];
#define  TEST_SIZE      64*1024
MS_BOOL MDrv_UsbDiskWrite( MS_U32 u32BlockAddr, MS_U32 u32BlockNum,MS_U32 u8Buffer);
MS_BOOL MDrv_UsbDiskRead(MS_U32 u32BlockAddr, MS_U32 u32BlockNum,MS_U32 u8Buffer);

void UsbTest(void)
{
MS_U32 i,j,k=0;
MS_U32 idx=0,xxx;
//U8 maxlun,lunbyte;
U8  *buf1,*buf2;
    //
 //   maxlun=	MDrv_GET_MASS_MAX_LUN();
 //   lunbyte=MDrv_GET_MASS_VALID_LUN();
	printf("usb test\n");
//	printf("maxlun :%02bx lunbyte:%02bx\n",maxlun,lunbyte);

    buf1=(U8*)MsOS_AllocateMemory(TEST_SIZE, gs32NonCachedPoolID );
    buf2=(U8*)MsOS_AllocateMemory(TEST_SIZE, gs32NonCachedPoolID );
    //printf("buf1:%x, buf2:%x\n",(MS_U32)buf1,(MS_U32)buf2);
    for (i=0 ; i < TEST_SIZE ; i++)
        {
            buf1[i]= i & 0xff;
      }

while (1)
	{
	    idx++;
          printf("Loop:%x \n",idx);
		//	MDrv_MIU_Copy
	     xxx=idx % 10000;

        // for (k=0; k < 8 ; k++)
            {
            if (MDrv_UsbDiskWrite(50+xxx+k*128,TEST_SIZE/512,(MS_U32)buf1)==FALSE)
                {
                   printf("write failed\n");
                   return;
                }
            }
         //for (k=0; k < 8 ; k++)
            {
            if (MDrv_UsbDiskRead(50+xxx+k*128,TEST_SIZE/512,(MS_U32)buf2)==FALSE)
                {
                    printf("read failed\n");
                    return;
                }
            }

	 	//MsOS_Delay_Task(10);
            for (j=0 ; j < TEST_SIZE ; j++)
                 {
                  if (buf2[j]!= buf1[j]) printf("data err\n");
                 }
          //  	MsOS_Delay_Task(500);
        }
	//time1=MDrv_Timer_TimeDifference( MDrv_Timer_GetTime0(), time1 ) ;
	//printf("time1:%lx",time1);
	//printf("Performace:%lx kBytes/sec",  (512*400)/time1);
}
#endif


int ever_inited = 0;


//====================================================================
// * Function Name: main
// * Description:
// * Input:
// * OutPut:
//====================================================================
int Usb_host_Init(void)
{
    ever_inited = 1;

    extern void mwHost20Bit_Set2(int bByte,int wBitNum);
    mwHost20Bit_Set(0x81,BIT6); // Data length byte alignment issue
    if (flib_OTGH_Init(0, USB_WAIT_TIME)==0)
    {
        printf("usb init failed\n");
        return -1;
    }
    return bSpeed;
}

int Usb_host_PreInit(void)
{
    extern void mwHost20Bit_Set2(int bByte,int wBitNum);
    mwHost20Bit_Set(0x81,BIT6); // Data length byte alignment issue
   return -1;

}

int Usb_host_PostInit(void)
{
    ever_inited = 1;

    extern void mwHost20Bit_Set2(int bByte,int wBitNum);
    mwHost20Bit_Set(0x81,BIT6); // Data length byte alignment issue
    if (flib_OTGH_Init(0, 0)==0)
    {
        printf("usb init failed\n");
        return -1;
    }
    return bSpeed;
}

#define mdelay(n) ({unsigned long msec=(n); while (msec--) udelay(1000);})
void MDrv_UsbClose(void)
{
    if(ever_inited == 0)
        return;

    flib_Host20_StopRun_Setting(HOST20_Disable);
    //flib_Host20_Close(0);

    //printf("[USB] MDrv_UsvClose, ever_inited == 1\n");
    if (ever_inited == 2)
    {
        printf("[USB] Long time stable device. Waiting .5 second...\n");
        mdelay(500);
    }
}




