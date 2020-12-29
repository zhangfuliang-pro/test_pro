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


#ifndef _DRV_AESDMA_H_
#include "drvAESDMA.h"
#endif
#include <common.h>

void MDrv_AESDMA_Run(aesdmaConfig *pConfig)
{
    HAL_AESDMA_Reset();

    HAL_AESDMA_SetFileinAddr(pConfig->u32SrcAddr);
    HAL_AESDMA_SetXIULength(pConfig->u32Size);
    HAL_AESDMA_SetFileoutAddr(pConfig->u32DstAddr, pConfig->u32Size);

    switch(pConfig->eKeyType)
    {
    case E_AESDMA_KEY_CIPHER:
        HAL_AESDMA_UseCipherKey();
        HAL_AESDMA_SetCipherKey(pConfig->pu16Key);
        break;
    case E_AESDMA_KEY_EFUSE:
        HAL_AESDMA_UseEfuseKey();
        break;
    case E_AESDMA_KEY_HW:
        HAL_AESDMA_UseHwKey();
        break;
    default:
        return;
    }

    if(pConfig->bDecrypt)
    {
        HAL_AESDMA_CipherDecrypt();
    }
    else
    {
        HAL_AESDMA_CipherEncrypt();
    }      

    if(pConfig->bSetIV)
    {
        HAL_AESDMA_SetIV(pConfig->pu16IV);
    }

    HAL_AESDMA_Enable();

    switch(pConfig->eChainMode)
    {
    case E_AESDMA_CHAINMODE_ECB:
        HAL_AESDMA_SetChainModeECB();
        HAL_AESDMA_SetXIULength(((pConfig->u32Size+15)/16)*16); // ECB mode size should align 16byte
        break;
    case E_AESDMA_CHAINMODE_CTR:
        HAL_AESDMA_SetChainModeCTR();
        HAL_AESDMA_CipherEncrypt();  // CTR mode can't set cipher_decrypt bit
        break;
    case E_AESDMA_CHAINMODE_CBC:
        HAL_AESDMA_SetChainModeCBC();
        break;
    default:
        return;
    }

    HAL_AESDMA_FileOutEnable(1);

    HAL_AESDMA_Start(1);

    // Wait for ready.
    while((HAL_AESDMA_GetStatus() & AESDMA_CTRL_DMA_DONE) != AESDMA_CTRL_DMA_DONE);
    HAL_AESDMA_Reset();

}

void MDrv_SHA_Run(U32 u32SrcAddr, U32 u32Size, enumShaMode eMode, U16 *pu16Output)
{
    HAL_SHA_Reset();

    HAL_SHA_SetAddress(u32SrcAddr);
    HAL_SHA_SetLength(u32Size);

    switch(eMode)
    {
    case E_SHA_MODE_1:
        HAL_SHA_SelMode(0);
        break;
    case E_SHA_MODE_256:
        HAL_SHA_SelMode(1);
        break;
    default:
        return;
    }

    HAL_SHA_Start();

    // Wait for the SHA done.
    while((HAL_SHA_GetStatus() & SHARNG_CTRL_SHA_READY) != SHARNG_CTRL_SHA_READY);

    HAL_SHA_Out((U32)pu16Output);

    HAL_SHA_Clear();
    HAL_SHA_Reset();
}

void MDrv_RSA_Run(rsaConfig *pConfig)
{
    int nOutSize;
    int i;

    HAL_RSA_Reset();

    HAL_RSA_SetKeyLength((pConfig->u32KeyLen-1) & 0x3F);
    HAL_RSA_SetKeyType(pConfig->bHwKey, pConfig->bPublicKey);

    HAL_RSA_Ind32Ctrl(0);
    HAL_RSA_Ind32Ctrl(1);
    HAL_RSA_LoadSignInverse_2byte((U16*)pConfig->pu32Sig);
    if((!pConfig->bHwKey) && (pConfig->pu32KeyN))
    {
        HAL_RSA_LoadKeyNInverse(pConfig->pu32KeyN);
    }
    if((!pConfig->bHwKey) && (pConfig->pu32KeyE))
    {
        HAL_RSA_LoadKeyEInverse(pConfig->pu32KeyE);
    }

    HAL_RSA_ExponetialStart();

    while((HAL_RSA_GetStatus() & RSA_STATUS_RSA_DONE) != RSA_STATUS_RSA_DONE);

    if((pConfig->bHwKey) || (pConfig->u32KeyLen == 2048))
    {
        nOutSize = (2048/8)/4;
    }
    else
    {
        nOutSize = (1024/8)/4;
    }

    HAL_RSA_Ind32Ctrl(0);
    for( i = 0; i<nOutSize; i++)
    {
        HAL_RSA_SetFileOutAddr(i);
        HAL_RSA_FileOutStart();
        *(pConfig->pu32Output+i) = HAL_RSA_FileOut();
    }
    HAL_RSA_FileOutEnd();
    HAL_RSA_Reset();
}


void runDecrypt(U32 u32ImageAddr, U32 u32ImageSize)
{
    aesdmaConfig config={0};

    config.u32SrcAddr=u32ImageAddr;
    config.u32DstAddr=u32ImageAddr;
    config.u32Size=u32ImageSize;
    //config.eKeyType=E_AESDMA_KEY_EFUSE;  //default use EFUSE key
    config.eKeyType=E_AESDMA_KEY_HW;  //use HW key
    config.bDecrypt=1;
    config.eChainMode=E_AESDMA_CHAINMODE_ECB;  //default use CBC mode
    MDrv_AESDMA_Run(&config);
   // printf("[U-Boot] Decrypt KEY_CUST done!\n\r");
}

BOOL runAuthenticate(U32 u32ImageAddr, U32 u32ImageSize, U32* pu32Key)
{
    U32 sha_out[8], rsa_out[64];
    rsaConfig config={0};
    U8 i;
    //RSA part
    u32ImageSize = u32ImageSize;
    //printf("runAuthenticate: u32ImageAddr = 0x%08X; data size=0x%08X --> MDrv_SHA_Run\n", u32ImageAddr, u32ImageSize);
    MDrv_SHA_Run(u32ImageAddr, u32ImageSize, E_SHA_MODE_256, (U16*)sha_out); //image + SHA-256
    //printf("runAuthenticate: --> MDrv_SHA_Run done\n");
    if(pu32Key == 0 || *pu32Key == 0)
    {
        config.bHwKey=1;
        config.bPublicKey=1;
        config.pu32Sig=(U32*)(u32ImageAddr + u32ImageSize); //change to RSA size
        config.pu32Output=rsa_out;
    }
    else
    {
        //TODO: use customer key
        //printf("use customer key\n");
    	config.pu32KeyN=(U32*)((U32)pu32Key+0x10); //header 0x10 bytes, offset for RSA KeyN
    	config.pu32KeyE=(U32*)((U32)pu32Key+0x110);//offset for RSAKeyE
		config.u32KeyLen=2048;
        config.bHwKey=0;
        config.bPublicKey=0;
        config.pu32Sig=(U32*)(u32ImageAddr + u32ImageSize);
        config.pu32Output=rsa_out;
    }
    //printf("runAuthenticate: compare RSA address is config.pu32Sig=0x%08X --> MDrv_RSA_Run\n", config.pu32Sig);
    MDrv_RSA_Run(&config);

    for(i=0; i<8; i++)
    {
        //printf("runAuthenticate:218: sha_out[%d]=0x%08X, rsa_out[%d]=0x%08X\n", i, sha_out[i], i, rsa_out[i]);
        if( sha_out[i] != rsa_out[i] )
        {
            printf("[U-Boot] RSA check failed.\n");
            return FALSE;
        }
    }
    printf("runAuthenticate: compare RSA address --> MDrv_RSA_Run done\n");
    return TRUE;
}

