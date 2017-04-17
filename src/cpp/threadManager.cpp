#include <stdio.h>
#include <stdlib.h>
#include "iso98wrap.h"
#include "irdetoJavaSecurityExtension.h"
#include "JACCommonModule.h"
#include "threadManager.h"
#include "networkManager.h"

#ifndef _JAC_SIGNING

#define MAX_MEM_CHANGE_ALLOWED 		1
#define MEM_SKIP_BYTES      		6 + 2

static JavaVM *pgJvm = NULL;
static JACThreadData *pThreadListData[NUM_THREADS];
static int memChangeCount = 0; 
static unsigned char prevTolerantSyms[] = {0xe,0xf,0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1a,0x1b,0x1c,0x1f,0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x44,0x45,0x46,0x47,0x48,0x49,0x4a,0x4b,0x4c,0x4d,0x4e,0x4f,0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5a,0x5b,0x5c,0x5d,0x5e,0x5f,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6a,0x6b,0x6c,0x6d,0x6e,0x6f,0x70,0x71,0x72,0x74,0x75,0x76,0x77,0x78,0x7b,0x7c,0x7d,0x7e,0x7f,0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f};
static unsigned char curTolerantSyms[] = {0x3e,0x3f,0x40,0x41,0x42,0x43,0x73,0x79,0x7a,0xe3,0xe4,0xe5,0xe6,0xe7,0xe8,0xe9,0xea,0xeb,0xec,0xed,0xef,0xf0,0xf1,0xfc,0xfd,0xfe,0xff};
static char JACModule5[] ="threadManager.cpp";

void setThreadJVM(JavaVM *pJvm)
{
    pgJvm = pJvm;
    for(int pos = 0; pos <NUM_THREADS; pos++){
	pThreadListData[pos] = NULL;
    }
}

void getThreadJVM(JavaVM **pJvm)
{
    *pJvm = pgJvm;
}

static int initJVMEnv(JACThreadData *pData)
{
    if(pgJvm == NULL) return -1;
    if(pgJvm->AttachCurrentThread(&pData->jniEnv,NULL) != 0){
	pData->status = ACCESS_STATUS_INVALID_JNI_ENV;
	return -1;
    }
    return 0;
}

static void removeJVMEnv()
{
    if(pgJvm == NULL) return;
    pgJvm->DetachCurrentThread();
}

static void dumpTestFile(JACThreadData *threadData, const char *caller)
{
    char fileName[256];
    FILE *fp = NULL;
    int bytesWritten;
 
    sprintf(fileName,"/data/local/%s_%lu.dat",caller, time(NULL));
    if((fp = fopen(fileName,"w+")) == NULL){
    	JACDebugWarning(threadData->jniEnv,JACModule5,__FUNCTION__,(char *)"can't open %s\n",fileName);
	return;
    }
    bytesWritten = fwrite(threadData->dexAddr, 1, threadData->dexLength, fp);
    if(bytesWritten != threadData->dexLength){
    	DBGWRAP(JACDebugWarning(threadData->jniEnv,JACModule5,__FUNCTION__,(char *)"Length mismatch\n"));
    }
    fflush(fp);
    fclose(fp);
    JACDebug(threadData->jniEnv,JACModule5,__FUNCTION__,(char *)"File %s created\n",fileName);
}

static int checkForTolerance(unsigned char prev, unsigned char cur, int *tokenFound)
{
    int retVal = 0;
    int symbolFound = 0;

    *tokenFound = 0;
    if(prev != cur){
        int retVal = -1;
        for(int pos =0; pos < nelem(prevTolerantSyms); pos++){
            if(prev == prevTolerantSyms[pos]){
		for(int pp = 0; pp < nelem(curTolerantSyms); pp++){
		    if(cur == curTolerantSyms[pp]){
			*tokenFound = 1;
			return 0;
		    }
		}
            }
        }
    }
    return retVal;
}

static int furtherMemoryInspect(JACThreadData *threadData)
{
    int tokenFound = 0;
    int retVal = 0;
    int dexLength = threadData->dexLength;
    unsigned char *dexBuf = threadData->dexBuf;
    unsigned char *dexAddr = threadData->dexAddr;

    for(int pos =0; pos < dexLength; pos++){
        if(checkForTolerance(dexBuf[pos], dexAddr[pos], &tokenFound) == -1){
    	    DBGWRAP(JACDebugWarning(threadData->jniEnv,JACModule5,__FUNCTION__,(char *)"Tempering detected at 0x%x, value: 0x%x 0x%x\n",pos, dexAddr[pos], dexBuf[pos]));
	    retVal = -1;
	    break;
        }else if(tokenFound){
            pos += MEM_SKIP_BYTES;
    	    DBGWRAP(JACDebug(threadData->jniEnv,JACModule5,__FUNCTION__,(char *)"Skipping from 0x%x to 0x%x\n", (pos - MEM_SKIP_BYTES), pos));
        }
    }
    DBGWRAP(JACDebug(threadData->jniEnv,JACModule5,__FUNCTION__,(char *)"done\n"));
    return retVal;
}

static int genMemorySignature(JACThreadData *threadData)
{
    unsigned char digest[SIGNATURE_LEN];
    ac_Status acStatus;
    if(!threadData->memorySignatureDone){ 
    	DBGWRAP(JACDebug(threadData->jniEnv,JACModule5,__FUNCTION__,(char *)"generating memory signature\n"));
	if((acStatus = getHmacSha256ByHandle(threadData->jniEnv, 
			      		     threadData->dexAddr,
			      	             threadData->dexLength, 
			      	             NULL,
			      		     digest)) != AC_OK){
    	    JACDebugWarning(threadData->jniEnv,JACModule5,__FUNCTION__,
				(char *)"AC error code: 0x%x\n",acStatus);
	    return -1;
	}
	memcpy(threadData->dexBuf, threadData->dexAddr, threadData->dexLength);
	memcpy(threadData->signature, digest, SIGNATURE_LEN);
    	threadData->memorySignatureDone = 1;
    	DBGWRAP(JACDebug(threadData->jniEnv,JACModule5,__FUNCTION__,(char *)"done\n"));
    }
    return 0;
}

static int inspectMemory(JACThreadData *threadData)
{
    ac_Status acStatus;
    unsigned char digest[SIGNATURE_LEN];

    DBGWRAP(JACDebug(threadData->jniEnv,JACModule5,__FUNCTION__,(char *)"start...\n"));
    if(threadData->status != ACCESS_STATUS_SUCCESS) {
        DBGWRAP(JACDebugWarning(threadData->jniEnv,JACModule5,__FUNCTION__,
				(char *)"initial problem to start with \n"));
	return -1;
    }
    if((acStatus = getHmacSha256ByHandle(threadData->jniEnv,
                                         threadData->dexAddr,
                                         threadData->dexLength,
                                         NULL,
                                         digest)) != AC_OK){
        JACDebugWarning(threadData->jniEnv,JACModule5,__FUNCTION__,
                                (char *)"AC error code: 0x%x\n",acStatus);
    	threadData->status = ACCESS_STATUS_INVALID_IAC_CONTEXT;
        return -1;
    }
    if(memcmp(threadData->signature, digest, SIGNATURE_LEN) != 0){
	if(threadData->ivPolicy == APP_IV_POLICY_STRICT ||
	   furtherMemoryInspect(threadData) == -1){
	    DBGWRAP(JACDebugWarning(threadData->jniEnv,JACModule5,__FUNCTION__,
                                (char *)"memory IV failed\n"));
            threadData->status = ACCESS_STATUS_APP_IV_FAILED;
            return -1;
	}else {
            DBGWRAP(JACDebug(threadData->jniEnv,JACModule5,__FUNCTION__,
                                (char *)"changes allowed\n"));
	    threadData->memorySignatureDone = 0;
	//Need to remove next line !!
   	//   dumpTestFile(threadData, __FUNCTION__);
	}
    }
    DBGWRAP(JACDebug(threadData->jniEnv,JACModule5,__FUNCTION__,(char *)"IV OK\n"));
    return 0;
}

static void determineExit(JACThreadData *dataPtr)
{
    if(dataPtr->status == ACCESS_STATUS_APP_IV_FAILED || dataPtr->status == ACCESS_STATUS_INVALID_IAC_CONTEXT){
       exit(EXIT_CODE_APP_IV);
    }
}

static void *appIVThread(void *paramPtr)
{
    static struct timespec timeout = {0,0};
    int retCode = 0;

    JACThreadData *dataPtr = (JACThreadData *) paramPtr;
    if((initJVMEnv(dataPtr)) == -1){
	return 0;
    }
    DBGWRAP(JACDebug(dataPtr->jniEnv,JACModule5,__FUNCTION__,(char *)"start..\n"));
    pthread_mutex_lock(&dataPtr->mutex);
    if(genMemorySignature(dataPtr) == -1){
        DBGWRAP(JACDebugWarning(dataPtr->jniEnv,JACModule5,__FUNCTION__,(char *)"Failed to generate signature\n"));
        removeJVMEnv();
        pthread_mutex_unlock(&dataPtr->mutex);
        return 0;
    }
    pthread_mutex_unlock(&dataPtr->mutex);
    while (retCode != -1){
	pthread_mutex_lock(&dataPtr->mutex);
	timeout.tv_sec = time(NULL) + THREAD_WAIT_TIME_SECONDS;
	pthread_cond_timedwait(&dataPtr->request, &dataPtr->mutex, &timeout);
	if(!dataPtr->keepAlive) {
	    pthread_mutex_unlock(&dataPtr->mutex);
	    break;
	}
    	retCode = inspectMemory(dataPtr);
	pthread_mutex_unlock(&dataPtr->mutex);
    }
    determineExit(dataPtr);
    DBGWRAP(JACDebug(dataPtr->jniEnv,JACModule5,__FUNCTION__,(char *)"exiting..\n"));
    removeJVMEnv();
}

static void *appADBGThread(void *paramPtr)
{
    static struct timespec timeout = {0,0};
    int retCode = 0;
    int loops = 0;
    JACThreadData *dataPtr = (JACThreadData *) paramPtr;
    if((initJVMEnv(dataPtr)) == -1){
        return 0;
    }
    DBGWRAP(JACDebug(dataPtr->jniEnv,JACModule5,__FUNCTION__,(char *)"start..\n"));
    while (1){
        pthread_mutex_lock(&dataPtr->mutex);
        retCode = inspectJavaDebugger(dataPtr->jniEnv);
	if(loops < THREAD_INIT_COUNTS){
            timeout.tv_sec = time(NULL) + THREAD_INIT_WAIT_TIME_SECONDS;
	    loops++;
	}else{
            timeout.tv_sec = time(NULL) + THREAD_WAIT_TIME_SECONDS;
	}
        pthread_cond_timedwait(&dataPtr->request, &dataPtr->mutex, &timeout);
        if(!dataPtr->keepAlive) {
            pthread_mutex_unlock(&dataPtr->mutex);
            break;
        }
        pthread_mutex_unlock(&dataPtr->mutex);
    }
    DBGWRAP(JACDebug(dataPtr->jniEnv,JACModule5,__FUNCTION__,(char *)"exiting..\n"));
    removeJVMEnv();
}

ACCESS_STATUS checkForCompletion2(JNIEnv *env, JACThreadIndex index)
{
    int retVal;
    JACThreadData *threadData = pThreadListData[index];
    if(threadData == NULL){
	DBGWRAP(JACDebugWarning(env,JACModule5,__FUNCTION__, 
		(char *)"No thread available"));
	return ACCESS_STATUS_NO_THREAD_AVAILABLE;
    }
    retVal = pthread_kill(threadData->monitorThread, 0); 
    if(retVal != 0 && errno == ESRCH){
	JACDebugWarning(env,JACModule5,__FUNCTION__, 
		(char *)"Thread %d is not running\n",threadData->monitorThread);
        return ACCESS_STATUS_THREAD_SHUTDOWN;
    }
    JACDebug(env,JACModule5,__FUNCTION__, 
		(char *)"thread status: %d\n",threadData->status);
    return threadData->status;
}

void shutdownThread(JNIEnv *env, JACThreadIndex index)
{
    DBGWRAP(JACDebug(env,JACModule5,__FUNCTION__,(char *)"shutting down thread\n"));
    JACThreadData *threadData = pThreadListData[index];
    if(threadData == NULL) {
    	DBGWRAP(JACDebug(env,JACModule5,__FUNCTION__,(char *)"NULL data, ignore...\n"));
    	return;
    }
    pthread_mutex_lock(&threadData->mutex);
    threadData->keepAlive = 0;
    pthread_cond_signal(&threadData->request);
    DBGWRAP(JACDebug(env,JACModule5,__FUNCTION__,(char *)"message sent\n"));
    pthread_mutex_unlock(&threadData->mutex);
    sleep(THREAD_EXIT_WAIT_TIME_SECONDS);
    pthread_mutex_destroy(&threadData->mutex);
    pthread_cond_destroy(&threadData->done);
    pthread_cond_destroy(&threadData->request);
    switch(index){
    	case JAC_THREAD_INDEX_APP_IV:    
    	    if(threadData->dexBuf != NULL) ac_free(threadData->dexBuf);
	    break;
	case JAC_THREAD_INDEX_ADBG:
	    break;
	case JAC_THREAD_INDEX_DYN_IV:
	    DBGWRAP(JACDebug(env,JACModule5,__FUNCTION__,(char *)"to be implemented\n"));
	    return;
	case JAC_THREAD_INDEX_MAIN_IV:
	    DBGWRAP(JACDebug(env,JACModule5,__FUNCTION__,(char *)"to be implemented\n"));
	    return;
	default:
	    DBGWRAP(JACDebug(env,JACModule5,__FUNCTION__,(char*)"Invalide index\n"));
	    return;
    }
    if(threadData != NULL){
  	ac_free(threadData);
	pThreadListData[index] = NULL;
    }
    DBGWRAP(JACDebug(env,JACModule5,__FUNCTION__,(char *)"end of operation\n"));
}

int static initAppIVThread(JNIEnv *env, DexInternalParams *pIntParam, JACThreadData *pData )
{
     int retVal;
     pData->dexAddr = (unsigned char *)pIntParam->dexAddr;
     pData->dexLength = pIntParam->dexLength;
     pData->smemAddr = (unsigned char *) pIntParam->memMapAddr;
     pData->smemLength = pIntParam->memMapLength;
     pData->dexBuf = (unsigned char *)ac_malloc(pData->dexLength); 
     memcpy(pData->dexBuf, pData->dexAddr, pData->dexLength);
//Need to remove next line !!
 //  dumpTestFile(pData, __FUNCTION__);
     retVal=pthread_create(&pData->monitorThread,NULL,appIVThread,(void *)pData);
     JACDebug(env,JACModule5,__FUNCTION__,(char *)"TID: %d created\n",pData->monitorThread);
     return retVal;
}

int static initADBGThread(JNIEnv *env, JACThreadData *pData)
{
     int retVal;
     retVal=pthread_create(&pData->monitorThread,NULL,appADBGThread,(void *)pData);
     JACDebug(env,JACModule5,__FUNCTION__,(char *)"TID: %d created\n",pData->monitorThread);
     return retVal;
}

int initThread(JNIEnv *env, JACThreadIndex index)
{
    return(initThread(env, (AppIVPolicy) 0, NULL, index));
}

int initThread(JNIEnv *env, AppIVPolicy ivPolicy, DexInternalParams *pIntParam, JACThreadIndex index)
{
    int retVal = 0;
    if(ivPolicy == APP_IV_POLICY_NONE && index == JAC_THREAD_INDEX_APP_IV){
	JACDebug(env,JACModule5,__FUNCTION__,(char *)"IV Policy: %d, ignore\n", ivPolicy);
       	return 0;
    }
    if(index >= NUM_THREADS) return -1;
    if(pThreadListData[index] != NULL){
    	DBGWRAP(JACDebug(env,JACModule5,__FUNCTION__,(char *)"already initialized\n"));
	return -1;
    }
    pThreadListData[index] = (JACThreadData *)ac_malloc(sizeof(JACThreadData)); 
    memset(pThreadListData[index], 0, sizeof(JACThreadData));
    JACThreadData *pData = pThreadListData[index]; 
    pData->status = ACCESS_STATUS_SUCCESS;
    pData->keepAlive = 1;
    pthread_cond_init(&pData->done, NULL);
    pthread_cond_init(&pData->request, NULL);
    pthread_mutex_init(&pData->mutex, NULL);
    JACDebug(env,JACModule5,__FUNCTION__,(char *)"about to spawn: %d\n",index);
    switch(index){
    	case JAC_THREAD_INDEX_APP_IV:    
 	    pData->ivPolicy = ivPolicy;
 	    retVal = initAppIVThread(env, pIntParam, pData);
	    break;
	case JAC_THREAD_INDEX_ADBG:
	    retVal = initADBGThread(env, pData);
	    break;
	case JAC_THREAD_INDEX_DYN_IV:
	    DBGWRAP(JACDebug(env,JACModule5,__FUNCTION__,(char *)"to be implemented\n"));
	    break;
	case JAC_THREAD_INDEX_MAIN_IV:
	    DBGWRAP(JACDebug(env,JACModule5,__FUNCTION__,(char *)"to be implemented\n"));
	    break;
	default:
	    DBGWRAP(JACDebug(env,JACModule5,__FUNCTION__,(char*)"Invalide index\n"));
	    retVal = -1;
    }
    return retVal;
}
#endif
