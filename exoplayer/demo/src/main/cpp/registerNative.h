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



int registerNativeSymbols420217909_443(JNIEnv * env);
int registerNativeSymbols420217909_462(JNIEnv * env);
int registerNativeSymbols420217909_915(JNIEnv * env);
int registerNativeSymbols420217909_916(JNIEnv * env);

int registerNativeSymbols420217909_1178(JNIEnv * env);
int registerNativeSymbols420217909_1179(JNIEnv * env);
int registerNativeSymbols420217909_439(JNIEnv * env);
int registerNativeSymbols420217909_913(JNIEnv * env);
#endif //EXOPLAYER_REGISTERNATIVE_H
