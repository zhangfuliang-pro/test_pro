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


#define _DRV_HDMITX_OS_C_
//-------------------------------------------------------------------------------------------------
//  Include Files
//-------------------------------------------------------------------------------------------------
#include <linux/sched.h>
#include <linux/gpio.h>
#include <linux/i2c.h>

#include "mhal_common.h"
#include "drv_hdmitx_os.h"
//-------------------------------------------------------------------------------------------------
//  Defines & Macro
//-------------------------------------------------------------------------------------------------
#define TICK_PER_ONE_MS             (1) //Note: confirm Kernel fisrt
#define HDMITX_OS_WAIT_FOREVER      (0xffffff00/TICK_PER_ONE_MS)


#define HDMITX_OS_ID_PREFIX         0x76540000
#define HDMITX_OS_ID_PREFIX_MASK    0xFFFF0000
#define HDMITX_OS_ID_MASK           0x0000FFFF //~HDMITX_OS_ID_PREFIX_MASK

#define HAS_FLAG(flag, bit)         ((flag) & (bit))
#define SET_FLAG(flag, bit)         ((flag)|= (bit))
#define RESET_FLAG(flag, bit)       ((flag)&= (~(bit)))

#if CAM_OS_EVENTGROUP
#define EVENT_MUTEX_LOCK()      CamOsTsemDown(&_tHdmitxOsMutex.EventGroup)
#define EVENT_MUTEX_UNLOCK()    CamOsTsemUp(&_tHdmitxOsMutex.EventGroup)
#else
#define EVENT_MUTEX_LOCK()      spin_lock(&_EventGroup_Mutex)
#define EVENT_MUTEX_UNLOCK()    spin_unlock(&_EventGroup_Mutex)
#endif

#define EN_EVENT_GROUP           0
//-------------------------------------------------------------------------------------------------
//  Structure
//-------------------------------------------------------------------------------------------------
typedef struct
{
    void (*pfnFunc)(unsigned long nDataAddr);
}DrvHdmitxOsTimerNotifyFunc_t;

typedef struct
{
    MS_U32 u32Dummy;
    CamOsTsem_t EventGroup;
}DrvHdmitxOsMutext_t;

//-------------------------------------------------------------------------------------------------
//  Variable
//-------------------------------------------------------------------------------------------------
MS_BOOL                             bHdmitxOsInit = 0;
DrvHdmitxOsEventGroupInfoConfig_t   _HdmitxOs_EventGroup_Info[HDMITX_OS_EVENTGROUP_MAX];


#if CAM_OS_EVENTGROUP
DrvHdmitxOsMutext_t _tHdmitxOsMutex;
#else
static  DEFINE_SPINLOCK(_EventGroup_Mutex);
static struct workqueue_struct* pstWorkQueue;
#endif


struct i2c_adapter* gI2cAdpa = NULL;



//-------------------------------------------------------------------------------------------------
//  Internal Functions
//-------------------------------------------------------------------------------------------------
static void _DrvHdmitxOsTimerNotify(unsigned long nDataAddr)
{
    DrvHdmitxOsTimerConfig_t * pTimerCfg = (DrvHdmitxOsTimerConfig_t *)nDataAddr;
    DrvHdmitxOsTimerNotifyFunc_t stNotify;

    stNotify.pfnFunc = _DrvHdmitxOsTimerNotify;
    CamOsTimerAdd(&pTimerCfg->stTimerCfg, pTimerCfg->u32TimerOut, pTimerCfg, stNotify.pfnFunc);

    if(pTimerCfg->pfnFunc)
    {
        pTimerCfg->pfnFunc(0,0);
    }
}

#if (CAM_OS_EVENTGROUP == 0)
static int irqContext(struct work_struct *work)
{
    struct work_data * pstWorkData = container_of(work, struct work_data, stWork);
    DrvHdmitxOsEventGroupInfoConfig_t*  pEventGroup_Info = container_of(pstWorkData, DrvHdmitxOsEventGroupInfoConfig_t, stWorkData);

    spin_lock(&pEventGroup_Info->stMutexEvent);
    SET_FLAG(pEventGroup_Info->u32EventGroup, pstWorkData->u32EventFlag);
    wake_up_all(&pEventGroup_Info->stEventWaitQueue);
    spin_unlock(&pEventGroup_Info->stMutexEvent);

    return 0;
}
#endif

//-------------------------------------------------------------------------------------------------
//  Public Functions
//-------------------------------------------------------------------------------------------------
MS_BOOL DrvHdmitxOsInit(void)
{
    MS_U32 u32I;

    if(bHdmitxOsInit == 0)
    {
        // Event Group
    #if CAM_OS_EVENTGROUP
        if(CamOsTsemInit(&_tHdmitxOsMutex.EventGroup, 1) != CAM_OS_OK)
        {
            CamOsPrintf( PRINT_RED "%s %d: EventGroup Mutex Create Fail\n" PRINT_NONE);
            return FALSE;
        }
    #endif

        for( u32I=0; u32I<HDMITX_OS_EVENTGROUP_MAX; u32I++)
        {
            _HdmitxOs_EventGroup_Info[u32I].bUsed = FALSE;

        #if (CAM_OS_EVENTGROUP == 0)
              pstWorkQueue = create_singlethread_workqueue("EventGroupWorkQueue");
              INIT_WORK(&_HdmitxOs_EventGroup_Info[u32I].stWorkData.stWork, (void *)irqContext);
        #endif
        }

        bHdmitxOsInit = 1;
    }
    else
    {

    }
    return TRUE;
}

void* DrvHdmitxOsMemAlloc(MS_U32 u32Size)
{
    return CamOsMemAlloc(u32Size);
}

void DrvHdmitxOsMemRelease(void *pPtr)
{
    CamOsMemRelease(pPtr);
}

MS_U32 DrvHdmitxOsGetSystemTime (void)
{
    CamOsTimespec_t ts;
    CamOsGetTimeOfDay(&ts);
    return ts.nSec* 1000+ ts.nNanoSec/1000000;
}
MS_U64 DrvHdmitxOsGetSystemTimeStamp (void)
{
    MS_U64 u64TimeStamp;
    CamOsTimespec_t stRes;
    CamOsGetMonotonicTime(&stRes);
    u64TimeStamp =(MS_U64)stRes.nSec* 1000000ULL+ (MS_U64)(stRes.nNanoSec/1000LL);
    return u64TimeStamp;
}

MS_U32 DrvHdmitxOsTimerDiffTimeFromNow(MS_U32 u32TaskTimer) //unit = ms
{
    return (DrvHdmitxOsGetSystemTime() - u32TaskTimer);
}

MS_BOOL DrvHdmitxOsCreateTimer(DrvHdmitxOsTimerConfig_t *pTimerCfg)
{
    MS_BOOL bRet;
    DrvHdmitxOsTimerNotifyFunc_t stNotify;
    stNotify.pfnFunc = _DrvHdmitxOsTimerNotify;

    if(CamOsTimerInit(&pTimerCfg->stTimerCfg) == CAM_OS_OK)
    {
        if(CamOsTimerAdd(&pTimerCfg->stTimerCfg, pTimerCfg->u32TimerOut, pTimerCfg, stNotify.pfnFunc) == CAM_OS_OK)
        {
            pTimerCfg->s32Id = 1;
            bRet = TRUE;
        }
        else
        {
            pTimerCfg->s32Id = 0;
            bRet = FALSE;
            CamOsPrintf(PRINT_RED "%s %d, TimerAdd Fail\n" PRINT_NONE, __FUNCTION__, __LINE__);
        }
    }
    else
    {
        pTimerCfg->s32Id = -1;
        bRet = FALSE;
        CamOsPrintf(PRINT_RED "%s %d, TimerInit Fail\n" PRINT_NONE, __FUNCTION__, __LINE__);
    }

    return bRet;
}

MS_BOOL DrvHmidtxOsDeleteTimer(DrvHdmitxOsTimerConfig_t *pCfg)
{
    if(CamOsTimerDelete(&pCfg->stTimerCfg) == CAM_OS_OK)
    {
        pCfg->s32Id = -1;
        return TRUE;
    }
    else
    {
        CamOsPrintf(PRINT_RED "%s %d, TimerDelete Fail\n" PRINT_NONE, __FUNCTION__, __LINE__);
        return FALSE;
    }
}

MS_BOOL DrvHdmitxOsStopTimer(DrvHdmitxOsTimerConfig_t *pCfg)
{
    if(CamOsTimerDelete(&pCfg->stTimerCfg) == CAM_OS_OK)
    {
        return TRUE;
    }
    else
    {
        CamOsPrintf(PRINT_RED "%s %d, TimerDelete Fail\n" PRINT_NONE, __FUNCTION__, __LINE__);
        return FALSE;
    }
}

MS_BOOL DrvHdmitxOsStartTimer(DrvHdmitxOsTimerConfig_t *pTimerCfg)
{
    DrvHdmitxOsTimerNotifyFunc_t stNotify;
    stNotify.pfnFunc = _DrvHdmitxOsTimerNotify;

    if(CamOsTimerAdd(&pTimerCfg->stTimerCfg, pTimerCfg->u32TimerOut, pTimerCfg, stNotify.pfnFunc ) == CAM_OS_OK)
    {
        return TRUE;
    }
    else
    {
        CamOsPrintf(PRINT_RED "%s %d, TimerAdd Fail\n" PRINT_NONE, __FUNCTION__, __LINE__);
        return FALSE;
    }
}

MS_BOOL DrvHdmitxOsCreateSemaphore(DrvHdmitxOsSemConfig_t *pstSemaphoreCfg, MS_U32 u32InitVal)
{
    MS_BOOL bRet = TRUE;

    if(CamOsTsemInit(&pstSemaphoreCfg->stSemCfg, u32InitVal) == CAM_OS_OK)
    {
        pstSemaphoreCfg->s32Id = 1;
        bRet = TRUE;
    }
    else
    {
        pstSemaphoreCfg->s32Id = -1;
        bRet = FALSE;
        CamOsPrintf(PRINT_RED "%s %d, Semaphore Create Fail\n" PRINT_NONE, __FUNCTION__, __LINE__);
    }
    return bRet;
}

MS_BOOL DrvHdmitxOsDestroySemaphore(DrvHdmitxOsSemConfig_t *pstSemaphoreCfg)
{
    MS_BOOL bRet = TRUE;

    if(CamOsTsemDeinit(&pstSemaphoreCfg->stSemCfg) == CAM_OS_OK)
    {
        pstSemaphoreCfg->s32Id = -1;
        bRet = TRUE;
    }
    else
    {
        bRet = FALSE;
        CamOsPrintf(PRINT_RED "%s %d, Semaphore Destroy Fail\n" PRINT_NONE, __FUNCTION__, __LINE__);
    }
    return bRet;
}

void DrvHdmitxOsObtainSemaphore(DrvHdmitxOsSemConfig_t *pstSemaphoreCfg)
{
    CamOsTsemDown(&pstSemaphoreCfg->stSemCfg);

}

void DrvHdmitxOsReleaseSemaphore(DrvHdmitxOsSemConfig_t *pstSemaphoreCfg)
{
    CamOsTsemUp(&pstSemaphoreCfg->stSemCfg);
}


MS_BOOL DrvHdmitxOsCreateMutex(DrvHdmitxOsMutexConfig_t *pstMutexCfg)
{
    MS_BOOL bRet = TRUE;

    if(CamOsMutexInit(&pstMutexCfg->stMutxCfg) == CAM_OS_OK)
    {
        pstMutexCfg->s32Id = 1;
        bRet = TRUE;
    }
    else
    {
        pstMutexCfg->s32Id  = -1;

        CamOsPrintf(PRINT_RED "%s %d, MutexCreate Fail\n" PRINT_NONE, __FUNCTION__, __LINE__);
        bRet = FALSE;
    }
    return bRet;
}

MS_BOOL DrvHdmitxOsDestroyMutex(DrvHdmitxOsMutexConfig_t *pstMutexCfg)
{
    MS_BOOL bRet;

    if(CamOsMutexDestroy(&pstMutexCfg->stMutxCfg) == CAM_OS_OK)
    {
        pstMutexCfg->s32Id = -1;
        bRet = TRUE;
    }
    else
    {
        CamOsPrintf(PRINT_RED "%s %d, Mutex Destroy Fail\n" PRINT_NONE, __FUNCTION__, __LINE__);
        bRet = FALSE;
    }
    return bRet;
}

MS_BOOL DrvHdmitxOsObtainMutex(DrvHdmitxOsMutexConfig_t *pstMutexCfg)
{
    if(CamOsMutexLock(&pstMutexCfg->stMutxCfg) == CAM_OS_OK)
    {
        return TRUE;
    }
    else
    {

        CamOsPrintf(PRINT_RED "%s %d, Mutex Lock Fail\n" PRINT_NONE, __FUNCTION__, __LINE__);
        return FALSE;
    }
}


MS_BOOL DrvHdmitxOsReleaseMutex(DrvHdmitxOsMutexConfig_t *pstMutexCfg)
{
    if(CamOsMutexUnlock(&pstMutexCfg->stMutxCfg) == CAM_OS_OK)
    {
        return TRUE;
    }
    else
    {

        CamOsPrintf(PRINT_RED "%s %d, Mutex UnLock Fail\n" PRINT_NONE, __FUNCTION__, __LINE__);
        return FALSE;
    }
}

MS_S32 DrvHdmitxOsCreateEventGroup (char *pEventName)
{
    MS_S32 s32Id;

#if (CAM_OS_EVENTGROUP == 0)

    EVENT_MUTEX_LOCK();

    for(s32Id = 0; s32Id < HDMITX_OS_EVENTGROUP_MAX; s32Id++)
    {
        if(_HdmitxOs_EventGroup_Info[s32Id].bUsed == FALSE)
        {
            break;
        }
    }

    if(s32Id >= HDMITX_OS_EVENTGROUP_MAX)
    {
        EVENT_MUTEX_UNLOCK();
        return -1;
    }

    spin_lock_init(&_HdmitxOs_EventGroup_Info[s32Id].stMutexEvent);
    _HdmitxOs_EventGroup_Info[s32Id].bUsed = TRUE;
    _HdmitxOs_EventGroup_Info[s32Id].u32Waiting = 0;
    spin_lock(&_HdmitxOs_EventGroup_Info[s32Id].stMutexEvent);
    _HdmitxOs_EventGroup_Info[s32Id].u32EventGroup = 0;
    spin_unlock(&_HdmitxOs_EventGroup_Info[s32Id].stMutexEvent);

    EVENT_MUTEX_UNLOCK();

    init_waitqueue_head(&_HdmitxOs_EventGroup_Info[s32Id].stEventWaitQueue);
    s32Id |= HDMITX_OS_ID_PREFIX;
    return s32Id;

#else
    EVENT_MUTEX_LOCK();
    for(s32Id=0; s32Id<HDMITX_OS_EVENTGROUP_MAX; s32Id++)
    {
        if(_HdmitxOs_EventGroup_Info[s32Id].bUsed == FALSE)
        {
            break;
        }
    }
    if(s32Id < HDMITX_OS_EVENTGROUP_MAX)
    {
        _HdmitxOs_EventGroup_Info[s32Id].bUsed = TRUE;
        _HdmitxOs_EventGroup_Info[s32Id].u32EventGroup= 0;
    }
    EVENT_MUTEX_UNLOCK();

    if(s32Id >= HDMITX_OS_EVENTGROUP_MAX)
    {
        CamOsPrintf(PRINT_RED "%s %d, No Empty EventGroup\n" PRINT_NONE, __FUNCTION__, __LINE__);
        return -1;
    }

    if(CamOsTcondInit(&_HdmitxOs_EventGroup_Info[s32Id].stSemaphore) == CAM_OS_OK)
    {
        if(CamOsTsemInit(&_HdmitxOs_EventGroup_Info[s32Id].stMutexEvent, 1) == CAM_OS_OK)
        {
            s32Id |= HDMITX_OS_ID_PREFIX;
        }
        else
        {
            s32Id = -1;
            CamOsPrintf(PRINT_RED "%s %d, CamOsTsemInit Fail\n" PRINT_NONE, __FUNCTION__, __LINE__);
        }
    }
    else
    {
        CamOsPrintf(PRINT_RED "%s %d, CamOsTcondInit Fail\n" PRINT_NONE, __FUNCTION__, __LINE__);
        s32Id = -1;
    }

    return s32Id;
#endif
}

MS_BOOL DrvHdmitxOsDeleteEventGroup (MS_S32 s32EventGroupId)
{
#if (CAM_OS_EVENTGROUP == 0)
    if ( (s32EventGroupId & HDMITX_OS_ID_PREFIX_MASK) != HDMITX_OS_ID_PREFIX )
    {
        return FALSE;
    }
    else
    {
        s32EventGroupId &= HDMITX_OS_ID_MASK;
    }

    EVENT_MUTEX_LOCK();
    if (!_HdmitxOs_EventGroup_Info[s32EventGroupId].bUsed)
    {
        EVENT_MUTEX_UNLOCK();
        return FALSE;
    }

    if (0 < _HdmitxOs_EventGroup_Info[s32EventGroupId].u32Waiting)
    {
        EVENT_MUTEX_UNLOCK();
        CamOsPrintf("\033[35m[%s][%d] EventGroup Delete FAIL : Event was still waiting.\033[m\n", __func__, __LINE__);
        return FALSE;
    }

    spin_lock(&_HdmitxOs_EventGroup_Info[s32EventGroupId].stMutexEvent);
    _HdmitxOs_EventGroup_Info[s32EventGroupId].u32EventGroup = 0;
    spin_unlock(&_HdmitxOs_EventGroup_Info[s32EventGroupId].stMutexEvent);
    _HdmitxOs_EventGroup_Info[s32EventGroupId].bUsed = FALSE;
    _HdmitxOs_EventGroup_Info[s32EventGroupId].u32Waiting = 0;
    EVENT_MUTEX_UNLOCK();

    init_waitqueue_head(&_HdmitxOs_EventGroup_Info[s32EventGroupId].stEventWaitQueue);
    return TRUE;

#else
    MS_S32 s32Id;

    s32Id = s32EventGroupId & HDMITX_OS_ID_MASK;
    CamOsTcondDeinit(&_HdmitxOs_EventGroup_Info[s32Id].stSemaphore);

    EVENT_MUTEX_LOCK();
    _HdmitxOs_EventGroup_Info[s32Id].u32EventGroup= 0;
    _HdmitxOs_EventGroup_Info[s32Id].bUsed = FALSE;
    EVENT_MUTEX_UNLOCK();
    return TRUE;
#endif
}


MS_BOOL DrvHdmitxOsSetEvent (MS_S32 s32EventGroupId, MS_U32 u32EventFlag)
{
#if (CAM_OS_EVENTGROUP == 0)
    if ( (s32EventGroupId & HDMITX_OS_ID_PREFIX_MASK) != HDMITX_OS_ID_PREFIX )
    {
        return FALSE;
    }
    else
    {
        s32EventGroupId &= HDMITX_OS_ID_MASK;
    }

    //
    //workqueue
    //
    if(in_interrupt())
    {
        if (!_HdmitxOs_EventGroup_Info[s32EventGroupId].bUsed)
        {
            return FALSE;
        }

        _HdmitxOs_EventGroup_Info[s32EventGroupId].stWorkData.u32EventFlag = u32EventFlag;
        queue_work(pstWorkQueue, &_HdmitxOs_EventGroup_Info[s32EventGroupId].stWorkData.stWork);
    }
    else
    {
        EVENT_MUTEX_LOCK();
        if (!_HdmitxOs_EventGroup_Info[s32EventGroupId].bUsed)
        {
            EVENT_MUTEX_UNLOCK();
            return FALSE;
        }
        EVENT_MUTEX_UNLOCK();

        spin_lock(&_HdmitxOs_EventGroup_Info[s32EventGroupId].stMutexEvent);
        SET_FLAG(_HdmitxOs_EventGroup_Info[s32EventGroupId].u32EventGroup, u32EventFlag);
        wake_up_all(&_HdmitxOs_EventGroup_Info[s32EventGroupId].stEventWaitQueue);
        spin_unlock(&_HdmitxOs_EventGroup_Info[s32EventGroupId].stMutexEvent);
    }

    return TRUE;

#else
    if ( (s32EventGroupId & HDMITX_OS_ID_PREFIX_MASK) != HDMITX_OS_ID_PREFIX )
    {
        return FALSE;
    }
    else
    {
        s32EventGroupId &= HDMITX_OS_ID_MASK;
    }

    CamOsTsemDown(&_HdmitxOs_EventGroup_Info[s32EventGroupId].stMutexEvent);
    SET_FLAG(_HdmitxOs_EventGroup_Info[s32EventGroupId].u32EventGroup, u32EventFlag);
    CamOsTsemUp(&_HdmitxOs_EventGroup_Info[s32EventGroupId].stMutexEvent);

    CamOsTcondSignalAll(&_HdmitxOs_EventGroup_Info[s32EventGroupId].stSemaphore);
    return TRUE;
#endif
}

MS_U32 DrvHdmitxOsGetEvent(MS_S32 s32EventGroupId)
{
    MS_U32 u32Event = 0;
    if ( (s32EventGroupId & HDMITX_OS_ID_PREFIX_MASK) != HDMITX_OS_ID_PREFIX )
    {
        return FALSE;
    }
    else
    {
        s32EventGroupId &= HDMITX_OS_ID_MASK;
    }
    u32Event = HAS_FLAG(_HdmitxOs_EventGroup_Info[s32EventGroupId].u32EventGroup, 0xFFFFFFFF);

    return u32Event;
}

MS_BOOL DrvHdmitxOsWaitEvent (MS_S32 s32EventGroupId,
                     MS_U32 u32WaitEventFlag,
                     MS_U32 *pu32RetrievedEventFlag,
                     DrvHdmitxOsEventWaitMoodeType_e eWaitMode,
                     MS_U32 u32WaitMs)
{
#if (CAM_OS_EVENTGROUP == 0)
    MS_BOOL bRet = FALSE;
    MS_BOOL bAnd;
    MS_BOOL bClear;

    *pu32RetrievedEventFlag = 0;

    if (!u32WaitEventFlag)
    {
        return FALSE;
    }

    if ( (s32EventGroupId & HDMITX_OS_ID_PREFIX_MASK) != HDMITX_OS_ID_PREFIX )
    {
        return FALSE;
    }
    else
    {
        s32EventGroupId &= HDMITX_OS_ID_MASK;
    }

    EVENT_MUTEX_LOCK();
    if (!_HdmitxOs_EventGroup_Info[s32EventGroupId].bUsed)
    {
        EVENT_MUTEX_UNLOCK();
        return FALSE;
    }
    _HdmitxOs_EventGroup_Info[s32EventGroupId].u32Waiting++;
    EVENT_MUTEX_UNLOCK();

    bClear = ((E_DRV_HDMITX_OS_EVENT_MD_AND_CLEAR == eWaitMode) || (E_DRV_HDMITX_OS_EVENT_MD_OR_CLEAR == eWaitMode)) ? TRUE : FALSE;
    bAnd = ((E_DRV_HDMITX_OS_EVENT_MD_AND == eWaitMode) || (E_DRV_HDMITX_OS_EVENT_MD_AND_CLEAR == eWaitMode)) ? TRUE : FALSE;

    spin_lock(&_HdmitxOs_EventGroup_Info[s32EventGroupId].stMutexEvent);

    do
    {
        if (u32WaitMs == HDMITX_OS_WAIT_FOREVER) //blocking wait
        {
            if (bAnd)
            {
                spin_unlock(&_HdmitxOs_EventGroup_Info[s32EventGroupId].stMutexEvent);
                wait_event(_HdmitxOs_EventGroup_Info[s32EventGroupId].stEventWaitQueue,
                           ((_HdmitxOs_EventGroup_Info[s32EventGroupId].u32EventGroup & u32WaitEventFlag) == u32WaitEventFlag));
                spin_lock(&_HdmitxOs_EventGroup_Info[s32EventGroupId].stMutexEvent);
            }
            else
            {
                spin_unlock(&_HdmitxOs_EventGroup_Info[s32EventGroupId].stMutexEvent);
                wait_event(_HdmitxOs_EventGroup_Info[s32EventGroupId].stEventWaitQueue,
                           ((_HdmitxOs_EventGroup_Info[s32EventGroupId].u32EventGroup & u32WaitEventFlag) != 0));
                spin_lock(&_HdmitxOs_EventGroup_Info[s32EventGroupId].stMutexEvent);
            }
        }
        else if (u32WaitMs == 0)
        {
            *pu32RetrievedEventFlag = HAS_FLAG(_HdmitxOs_EventGroup_Info[s32EventGroupId].u32EventGroup, u32WaitEventFlag);
            break;
        }
        else
        {
            u32WaitMs = msecs_to_jiffies(u32WaitMs);

            if (bAnd)
            {
                spin_unlock(&_HdmitxOs_EventGroup_Info[s32EventGroupId].stMutexEvent);
                wait_event_timeout(_HdmitxOs_EventGroup_Info[s32EventGroupId].stEventWaitQueue,
                                   ((_HdmitxOs_EventGroup_Info[s32EventGroupId].u32EventGroup & u32WaitEventFlag) == u32WaitEventFlag),
                                   u32WaitMs);
                spin_lock(&_HdmitxOs_EventGroup_Info[s32EventGroupId].stMutexEvent);
            }
            else
            {
                spin_unlock(&_HdmitxOs_EventGroup_Info[s32EventGroupId].stMutexEvent);
                wait_event_timeout(_HdmitxOs_EventGroup_Info[s32EventGroupId].stEventWaitQueue,
                                   ((_HdmitxOs_EventGroup_Info[s32EventGroupId].u32EventGroup & u32WaitEventFlag) != 0),
                                   u32WaitMs);
                spin_lock(&_HdmitxOs_EventGroup_Info[s32EventGroupId].stMutexEvent);
            }
        }
        *pu32RetrievedEventFlag = HAS_FLAG(_HdmitxOs_EventGroup_Info[s32EventGroupId].u32EventGroup, u32WaitEventFlag);
    }
    while (0);

    //spin_lock(&_HdmitxOs_EventGroup_Info[s32EventGroupId].stMutexEvent);
    bRet = (bAnd) ? (*pu32RetrievedEventFlag == u32WaitEventFlag) : (0 != *pu32RetrievedEventFlag);
    if (bRet && bClear)
    {
        RESET_FLAG(_HdmitxOs_EventGroup_Info[s32EventGroupId].u32EventGroup, *pu32RetrievedEventFlag);
    }
    spin_unlock(&_HdmitxOs_EventGroup_Info[s32EventGroupId].stMutexEvent);

    EVENT_MUTEX_LOCK();
    _HdmitxOs_EventGroup_Info[s32EventGroupId].u32Waiting--;
    EVENT_MUTEX_UNLOCK();

    return bRet;
#else
    MS_BOOL bRet= FALSE;
    MS_BOOL bAnd;
    MS_BOOL bClear;
    MS_BOOL bTimeout=0;
    MS_U64 u64TimeStamp;
    MS_S32 s32TimeDiff;


    u64TimeStamp = DrvHdmitxOsGetSystemTimeStamp();
    *pu32RetrievedEventFlag = 0;
    if (!u32WaitEventFlag)
    {
        CamOsPrintf(PRINT_RED "%s %d, WaitEventFlag is 0\n" PRINT_NONE,  __FUNCTION__, __LINE__);
        return FALSE;
    }

    if ( (s32EventGroupId & HDMITX_OS_ID_PREFIX_MASK) != HDMITX_OS_ID_PREFIX )
    {
        CamOsPrintf(PRINT_RED "%s %d, GoupId Is Not Correct\n" PRINT_NONE,  __FUNCTION__, __LINE__);
        return FALSE;
    }
    else
    {
        s32EventGroupId &= HDMITX_OS_ID_MASK;
    }

    bClear= ((E_DRV_HDMITX_OS_EVENT_MD_AND_CLEAR == eWaitMode) || (E_DRV_HDMITX_OS_EVENT_MD_OR_CLEAR == eWaitMode))? TRUE: FALSE;
    bAnd= ((E_DRV_HDMITX_OS_EVENT_MD_AND == eWaitMode)|| (E_DRV_HDMITX_OS_EVENT_MD_AND_CLEAR == eWaitMode))? TRUE: FALSE;

    do{
        if (u32WaitMs== HDMITX_OS_WAIT_FOREVER) //blocking wait
        {
            CamOsTcondWait(&_HdmitxOs_EventGroup_Info[s32EventGroupId].stSemaphore);

            if (bAnd)
            {
                if(((_HdmitxOs_EventGroup_Info[s32EventGroupId].u32EventGroup & u32WaitEventFlag) != u32WaitEventFlag))
                {
                    CamOsTcondWait(&_HdmitxOs_EventGroup_Info[s32EventGroupId].stSemaphore);
                }
            }
            else
            {
                if(((_HdmitxOs_EventGroup_Info[s32EventGroupId].u32EventGroup & u32WaitEventFlag) == 0))
                {
                    CamOsTcondWait(&_HdmitxOs_EventGroup_Info[s32EventGroupId].stSemaphore);
                }
            }
        }
        else
        {
            bTimeout = (CamOsTcondTimedWait(&_HdmitxOs_EventGroup_Info[s32EventGroupId].stSemaphore,u32WaitMs) == CAM_OS_OK) ? 0 : 1;

            if(!bTimeout)
            {
                if (bAnd)
                {
                    while(((_HdmitxOs_EventGroup_Info[s32EventGroupId].u32EventGroup & u32WaitEventFlag) != u32WaitEventFlag))
                    {
                        s32TimeDiff = (MS_S32)((MS_U32)DrvHdmitxOsGetSystemTimeStamp()-(MS_U32)u64TimeStamp)/1000;
                        if(s32TimeDiff<=0)
                        {
                            bTimeout = 1;
                            break;
                        }
                        CamOsTcondTimedWait(&_HdmitxOs_EventGroup_Info[s32EventGroupId].stSemaphore,s32TimeDiff);
                    }
                }
                else
                {
                    while(((_HdmitxOs_EventGroup_Info[s32EventGroupId].u32EventGroup & u32WaitEventFlag) == 0))
                    {
                        s32TimeDiff = (MS_U32)((MS_U32)DrvHdmitxOsGetSystemTimeStamp()-(MS_U32)u64TimeStamp)/1000;
                        if(s32TimeDiff<=0)
                        {
                            bTimeout = 1;
                            break;
                        }
                        CamOsTcondTimedWait(&_HdmitxOs_EventGroup_Info[s32EventGroupId].stSemaphore,u32WaitMs);
                    }
                }
            }

            if(bTimeout)
            {
                s32TimeDiff = (MS_U32)DrvHdmitxOsGetSystemTimeStamp()-(MS_U32)u64TimeStamp;
                CamOsPrintf(PRINT_RED "[HDMITX_OS] %s %d:: wait timeout @%llu diff:@%lu\n" PRINT_NONE, __FUNCTION__, __LINE__, u64TimeStamp,s32TimeDiff);
            }
        }
        *pu32RetrievedEventFlag= HAS_FLAG(_HdmitxOs_EventGroup_Info[s32EventGroupId].u32EventGroup, u32WaitEventFlag);
    } while (0);

    bRet= (bAnd)? (*pu32RetrievedEventFlag== u32WaitEventFlag): (0!= *pu32RetrievedEventFlag);
    if (bRet && bClear)
    {
        CamOsTsemDown(&_HdmitxOs_EventGroup_Info[s32EventGroupId].stMutexEvent);
        RESET_FLAG(_HdmitxOs_EventGroup_Info[s32EventGroupId].u32EventGroup, *pu32RetrievedEventFlag);
        CamOsTsemUp(&_HdmitxOs_EventGroup_Info[s32EventGroupId].stMutexEvent);
    }

    return bRet;
#endif
}


MS_BOOL DrvHdmitxOsAttachInterrupt (MS_U32 u32IntNum, InterruptCallBack pIntCb)
{
    return TRUE;
}

MS_BOOL DrvHdmitxOsDetachInterrupt (MS_U32 u32IntNum)
{
    return TRUE;
}


MS_BOOL DrvHdmitxOsEnableInterrupt (MS_U32 u32IntNum)
{
    return TRUE;
}

MS_BOOL DrvHdmitxOsDisableInterrupt (MS_U32 u32IntNum)
{
    return TRUE;
}

MS_U32 DrvHdmitxOsDisableAllInterrupts(void)
{
    return 0;
}


MS_BOOL DrvHdmitxOsRestoreAllInterrupts(MS_U32 u32OldInterrupts)
{
    return TRUE;
}


MS_BOOL DrvHdmitxOsCreateTask(DrvHdmitxOsTaskConfig_t *pstTaskCfg, TaskEntryCb pTaskEntry, void *pDataPtr, char *pTaskName, MS_BOOL bAuotStart)
{
    CamOsThreadAttrb_t stThreadAttrCfg;
    MS_BOOL bRet = TRUE;

    stThreadAttrCfg.nPriority = 50;
    stThreadAttrCfg.nStackSize = 0;
    stThreadAttrCfg.szName = pTaskName;

    if(CamOsThreadCreate(&pstTaskCfg->stThreadCfg, &stThreadAttrCfg, pTaskEntry, pDataPtr) == CAM_OS_OK)
    {

        if(bAuotStart)
        {
            if(CamOsThreadWakeUp(pstTaskCfg->stThreadCfg) == CAM_OS_OK)
            {
                bRet = TRUE;
                pstTaskCfg->s32Id = 1;

            }
            else
            {
                bRet = FALSE;
                pstTaskCfg->s32Id = -1;
                CamOsPrintf(PRINT_RED "%s %d, CamOsThreadWakeUp Fail\n" PRINT_NONE, __FUNCTION__, __LINE__);
            }
        }
    }
    else
    {
        pstTaskCfg->s32Id = -1;
        bRet = FALSE;
        CamOsPrintf(PRINT_RED "%s %d, CamOsThreadCreate Fail\n" PRINT_NONE, __FUNCTION__, __LINE__);
    }
    return bRet;
}


MS_BOOL DrvHdmitxOsDestroyTask(DrvHdmitxOsTaskConfig_t *pstTaskCfg)
{
    if(CamOsThreadStop(pstTaskCfg->stThreadCfg) == CAM_OS_OK)
    {
        pstTaskCfg->s32Id = -1;
        return TRUE;
    }
    else
    {
        CamOsPrintf(PRINT_RED "%s %d, CamOsThreadStop Fail\n" PRINT_NONE, __FUNCTION__, __LINE__);
        return FALSE;
    }
}


MS_BOOL DrvHdmitxOsGetMmioBase(MS_VIRT *pu32BaseAddr, MS_PHY *pu32BaseSize, DrvHdmitxOsMmioType_e enType)
{
    MS_BOOL bRet = TRUE;

    switch(enType)
    {
        case E_HDMITX_OS_MMIO_PM:
            *pu32BaseAddr = 0xfd000000UL;
            *pu32BaseSize = 0x00400000UL;
             break;

        case E_HDMITX_OS_MMIO_NONEPM:
            *pu32BaseAddr = 0xfd200000UL;
            *pu32BaseSize = 0x00200000UL;
             break;

        default:
            bRet = FALSE;
            break;
    }
    return TRUE;
}

MS_BOOL DrvHdmitxOsRequestGpio(MS_U8 u8GpioNum)
{
    int ret = ret = gpio_request(u8GpioNum, "HDMITX_HPD");

    return 1;

    if(ret < 0)
    {
        CamOsPrintf(PRINT_RED "%s %d, gpio_request(%d) fail\n" PRINT_NONE, __FUNCTION__, __LINE__);
    }
    else
    {
        ret = gpio_direction_input(u8GpioNum);

        if(ret < 0)
        {
            CamOsPrintf(PRINT_RED "%s %d, gpio_direction_input (%d) fail\n" PRINT_NONE, __FUNCTION__, __LINE__);
        }
    }

    return ret < 0 ? FALSE : TRUE;
}

MS_BOOL DrvHdmitxOsGetGpioValue(MS_U8 u8GpioNum)
{
    int ret;
    MS_BOOL bHPD = 0;
    return 1;
    ret = gpio_get_value(u8GpioNum);
    bHPD = ret ? 1 : 0;
    return bHPD;
}

MS_BOOL DrvHdmitxOsSetI2cAdapter(MS_U16 u16Id)
{
    gI2cAdpa = i2c_get_adapter(u16Id);

    if(gI2cAdpa == NULL)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}


MS_BOOL DrvHdmitxOsSetI2cReadBytes(MS_U8 u8SlaveAdr, MS_U8 u8SubAdr, MS_U8 *pBuf, MS_U16 u16BufLen)
{
    struct i2c_msg msg[2];
    MS_U8 u8Data[4];

    u8Data[0] = u8SubAdr;
    msg[0].addr = u8SlaveAdr;
    msg[0].flags = 0;
    msg[0].buf= u8Data;
    msg[0].len = 1;

    msg[1].addr = u8SlaveAdr;
    msg[1].flags = 1;
    msg[1].buf = pBuf;
    msg[1].len = u16BufLen;

    if(i2c_transfer(gI2cAdpa, msg, 2)<0)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

MS_BOOL DrvHdmitxOsSetI2cWriteBytes(MS_U8 u8SlaveAdr, MS_U8 u8SubAdr, MS_U8 *pBuf, MS_U16 u16BufLen)
{
    struct i2c_msg msg[1];
    MS_U8 *pu8Data;
    MS_BOOL bRet;

    pu8Data =(MS_U8 *)DrvHdmitxOsMemAlloc(u16BufLen+1);

    if(pu8Data == NULL)
    {
        bRet = FALSE;
    }
    else
    {
        pu8Data[0] = u8SubAdr;
        memcpy(&pu8Data[1], pBuf, u16BufLen);

        msg[0].addr = u8SlaveAdr;
        msg[0].flags = 0;
        msg[0].buf= pu8Data;
        msg[0].len = u16BufLen+1;

        if(i2c_transfer(gI2cAdpa, msg, 1)<0)
        {
            bRet = FALSE;
        }
        else
        {
            bRet = TRUE;
        }

        CamOsMemRelease(pu8Data);
    }
    return bRet;
}

void DrvHdmitxOsMsSleep(u32 u32Msec)
{
    CamOsMsSleep(u32Msec);
}

void DrvHdmitxOsUsSleep(u32 u32Usec)
{
    CamOsUsSleep(u32Usec);
}

