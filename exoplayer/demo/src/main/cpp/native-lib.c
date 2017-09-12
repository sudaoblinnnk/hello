#include <jni.h>
#include <stdio.h>
#include <android/log.h>
#include "registerNative.h"

char * AC_DEBUG = "kurt";

#define LOGI(fmt, args...) __android_log_print(ANDROID_LOG_INFO,  AC_DEBUG, fmt, ##args)
#define LOGD(fmt, args...) __android_log_print(ANDROID_LOG_DEBUG, AC_DEBUG, fmt, ##args)
#define LOGE(fmt, args...) __android_log_print(ANDROID_LOG_ERROR, AC_DEBUG, fmt, ##args)



JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved)
{
    JNIEnv *env; jint registerResult = JNI_FALSE;
    if ((*vm)->GetEnv(vm, (void **) &env, JNI_VERSION_1_4) != JNI_OK) { return -1; }

    registerNativeSymbols420217909_442(env);

    return JNI_VERSION_1_4;
}