#ifndef _H_THREAD_MANAGER_
#define _H_THREAD_MANAGER_

#include "iso98wrap.h"
#include "irdetoJavaSecurityExtension.h"
#include "dexOperator.h"

#define NUM_THREADS			4

#define THREAD_WAIT_TIME_SECONDS	60
#define THREAD_INIT_WAIT_TIME_SECONDS	3
#define THREAD_EXIT_WAIT_TIME_SECONDS	1

#define THREAD_INIT_COUNTS		20

#define EXIT_HARD			0
#define EXIT_SOFT			1

typedef enum _AppIVPolicy
{
    APP_IV_POLICY_NONE		= 	0,
    APP_IV_POLICY_ALLOW_DVM	= 	1,
    APP_IV_POLICY_STRICT	=	2
}AppIVPolicy;

typedef struct _JACThreadData
{
    int 		index;
    pthread_mutex_t 	mutex;
    pthread_cond_t 	done;
    pthread_cond_t	request;
    pthread_attr_t 	attribute;
    pthread_t 		monitorThread;
    unsigned char 	signature[SIGNATURE_LEN];
    ACCESS_STATUS 	status;
    AppIVPolicy		ivPolicy;
    int			exitType;
    int			memorySignatureDone;
    int 		keepAlive;
    int 		dexLength;
    unsigned char	*dexAddr;
    int                 smemLength;
    unsigned char       *smemAddr;
    unsigned char       *dexBuf;
    JNIEnv		*jniEnv;

}JACThreadData;


#ifdef __cplusplus__
extern "C" {
#endif

int initThread(JNIEnv *env, JACThreadIndex index);
int initThread(JNIEnv *env, AppIVPolicy ivPolicy, DexInternalParams *pIntParam, JACThreadIndex index);
ACCESS_STATUS checkForCompletion2(JNIEnv *env, JACThreadIndex index);
void setThreadJVM(JavaVM *pJvm);
void getThreadJVM(JavaVM **pJvm);
void shutdownThread(JNIEnv *env, JACThreadIndex index); 

#ifdef __cplusplus__
}
#endif
#endif
