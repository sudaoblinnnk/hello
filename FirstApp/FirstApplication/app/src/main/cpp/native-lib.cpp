/*
package com.irdeto.j2n.firstapplication;

import android.os.Bundle;

//class:0052  access:0x0001
public class MainActivity extends android.app.Activity {

    static {
        System.loadLibrary("native-lib");
    }


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        KeyLogic1.getInstance();
    }

    public static class KeyLogic1 {
        public static native KeyLogic1 getInstance();
    }
}
*/

#include <jni.h>
#include <stdio.h>

static const char* JAVA_CLASS = "com/irdeto/j2n/firstapplication/MainActivity$KeyLogic1";

static jobject Java_com_irdeto_j2n_firstapplication_MainActivity_KeyLogic1_getInstance(JNIEnv *env, jclass type) {

    return 0;

}

static int registerNativeSymbols(JNIEnv * env)
{
    int returnVal = JNI_TRUE;

    /* JNI Symbol table */
    JNINativeMethod symbolListApi[] =
            {
                    { "getInstance",              "()Lcom/irdeto/j2n/firstapplication/MainActivity$KeyLogic1;",  (void *)Java_com_irdeto_j2n_firstapplication_MainActivity_KeyLogic1_getInstance }
            };

    jclass clazz = NULL;

    clazz = env->FindClass(JAVA_CLASS);
    if (clazz == NULL)
    {
        returnVal = JNI_FALSE;
    }

    if (env->RegisterNatives(clazz, symbolListApi, sizeof(symbolListApi) / sizeof(symbolListApi[0])) < 0) {
        returnVal = JNI_FALSE;
    }
    return returnVal;
}

JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM* vm, void* reserved) {
    JNIEnv *env;
    jint result = JNI_VERSION_1_4;
    jint registerResult = JNI_FALSE;

    if (vm->GetEnv((void **) &env, JNI_VERSION_1_4) != JNI_OK) {
        result = -1;
    }

    registerResult = registerNativeSymbols(env);
    if (registerResult == JNI_FALSE)
    {
        result = -1;
    }

    return result;
}
