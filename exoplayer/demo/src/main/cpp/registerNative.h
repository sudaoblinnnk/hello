//
// Created by kurt on 17-9-12.
//

#ifndef EXOPLAYER_REGISTERNATIVE_H
#define EXOPLAYER_REGISTERNATIVE_H

#ifdef  XC_ISO98
#include <xc/xc_extensions.h>
#include <jni.h>
#include <stdio.h>
#include <android/log.h>
#else
#include <jni.h>
#include <android/log.h>
#define _xc_preserve_interface
#endif //XC_ISO98


static char * AC_DEBUG = "kurt";

#define LOGI(fmt, args...) __android_log_print(ANDROID_LOG_INFO,  AC_DEBUG, fmt, ##args)
#define LOGD(fmt, args...) __android_log_print(ANDROID_LOG_DEBUG, AC_DEBUG, fmt, ##args)
#define LOGE(fmt, args...) __android_log_print(ANDROID_LOG_ERROR, AC_DEBUG, fmt, ##args)



int registerNativeSymbols420217909_442(JNIEnv * env);

#endif //EXOPLAYER_REGISTERNATIVE_H
