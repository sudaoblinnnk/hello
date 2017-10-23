#include "registerNative.h"

_xc_preserve_interface
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved)
{
    JNIEnv *env; jint registerResult = JNI_FALSE;
    if ((*vm)->GetEnv(vm, (void **) &env, JNI_VERSION_1_4) != JNI_OK) { return -1; }

    if (registerNativeSymbols420217909_443(env) == JNI_FALSE) {
        return -1;
    }
    if (registerNativeSymbols420217909_462(env) == JNI_FALSE) {
        return -1;
    }
    if (registerNativeSymbols420217909_915(env) == JNI_FALSE) {
        return -1;
    }
    if (registerNativeSymbols420217909_916(env) == JNI_FALSE) {
        return -1;
    }

    if (registerNativeSymbols420217909_1178(env) == JNI_FALSE) {
        return -1;
    }
    if (registerNativeSymbols420217909_1179(env) == JNI_FALSE) {
        return -1;
    }
    if (registerNativeSymbols420217909_439(env) == JNI_FALSE) {
        return -1;
    }
    if (registerNativeSymbols420217909_913(env) == JNI_FALSE) {
        return -1;
    }

    return JNI_VERSION_1_4;
}