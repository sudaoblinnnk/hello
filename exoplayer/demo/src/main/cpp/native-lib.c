#include "registerNative.h"

_xc_preserve_interface
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved)
{
    JNIEnv *env; jint registerResult = JNI_FALSE;
    if ((*vm)->GetEnv(vm, (void **) &env, JNI_VERSION_1_4) != JNI_OK) { return -1; }

    if (registerNativeSymbols420217909_442(env) == JNI_FALSE) {
        return -1;
    }

    return JNI_VERSION_1_4;
}