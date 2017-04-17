#ifndef _H_NETWORKMANAGER_
#define _H_NETWORKMANAGER_

#include <stdio.h>
#include <stdlib.h>
#include "iso98wrap.h"

#define JDWP_TOKEN_ELEM 	2
#define JDWP_TOKEN_LEN  	20
#define NETTOKEN  		"keyinfomationfornetworking"
#define PROC_INFO		"/proc/%d/cmdline"

typedef struct _NetStat
{
    int  (*validate)(int fd);
    int  (*execute)(JNIEnv *env, int fd, int *flag);
    int  (*execute2)(JNIEnv *env, int fd, struct stat fileStat, int *flag);
    void (*getNetInfo)(int fd, char *msg);
    void (*response)(JNIEnv *env, int fd);
    void (*stdVMCheck)(JNIEnv *env, int fd, int *ind);

}NetStat;

#ifdef __cplusplus__
extern "C" {
#endif

int inspectJavaDebugger(JNIEnv *env); 

#ifdef __cplusplus__
}
#endif
#endif

