//
// Created by kurt on 17-9-12.
//

#ifndef EXOPLAYER_REGISTERNATIVE_H
#define EXOPLAYER_REGISTERNATIVE_H

#ifdef  XC_ISO98
#include <xc/xc_extensions.h>
#else
#define _xc_preserve_interface
#endif //XC_ISO98

#include <jni.h>
#include <stdio.h>
#include <signal.h>
#include <android/log.h>

static char * AC_DEBUG = "kurt";

#define LOGI(fmt, args...) __android_log_print(ANDROID_LOG_INFO,  AC_DEBUG, fmt, ##args)
#define LOGD(fmt, args...) __android_log_print(ANDROID_LOG_DEBUG, AC_DEBUG, fmt, ##args)
#define LOGE(fmt, args...) __android_log_print(ANDROID_LOG_ERROR, AC_DEBUG, fmt, ##args)



int registerNativeSymbols420217909_442(JNIEnv * env);
int registerNativeSymbols420217909_461(JNIEnv * env);
int registerNativeSymbols420217909_913(JNIEnv * env);
int registerNativeSymbols420217909_914(JNIEnv * env);
#endif //EXOPLAYER_REGISTERNATIVE_H
