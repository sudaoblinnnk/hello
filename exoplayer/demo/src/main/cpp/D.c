#include <jni.h>
#include <stdio.h>
//class:1514  access:0x0001
//public class com.google.android.exoplayer2.demo.D extends com.google.android.exoplayer2.demo.B

//method:0000  access:0x10001
//Lcom/google/android/exoplayer2/demo/D;.<init>()V
void  Java_com_google_android_exoplayer2_demo_D___initNative_39797(JNIEnv * env, jobject  v0)
{
//LOCAL_VARIABLE LL0 ~ LL1 v0 -> this // Lcom/google/android/exoplayer2/demo/D; 
//LABEL               |  LL0: line 3
L0: ;
//INVOKE_DIRECT       |     |v0.<init>()  //Lcom/google/android/exoplayer2/demo/B;.<init>()V
//RETURN_VOID         |     |return
return;
//LABEL               |  LL1:
L1: ;
}

int registerNativeSymbols420217909_1179(JNIEnv * env) { 
int returnVal = JNI_TRUE; JNINativeMethod symbolListApi[] = { 
{"__initNative", "()V",  (void *)Java_com_google_android_exoplayer2_demo_D___initNative_39797 }, 
}; 
jclass clazz = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/D");
if (clazz == NULL) { 
 returnVal = JNI_FALSE; 
}
if ((*env)->RegisterNatives(env, clazz, symbolListApi, sizeof(symbolListApi) / sizeof(symbolListApi[0])) < 0) {
returnVal = JNI_FALSE; 
}
return returnVal;
}
