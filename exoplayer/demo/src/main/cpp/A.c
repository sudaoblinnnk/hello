#include <jni.h>
#include <stdio.h>
//class:0646  access:0x0001
//public class com.google.android.exoplayer2.demo.A

//method:0000  access:0x10001
//Lcom/google/android/exoplayer2/demo/A;.<init>()V
void  Java_com_google_android_exoplayer2_demo_A___initNative_39797(JNIEnv * env, jobject  v0)
{
//LOCAL_VARIABLE LL0 ~ LL1 v0 -> this // Lcom/google/android/exoplayer2/demo/A; 
//LABEL               |  LL0: line 3
L0: ;
//INVOKE_DIRECT       |     |v0.<init>()  //Ljava/lang/Object;.<init>()V
//RETURN_VOID         |     |return
return;
//LABEL               |  LL1:
L1: ;
}


//method:0001  access:0x0001
//Lcom/google/android/exoplayer2/demo/A;.show(Lcom/google/android/exoplayer2/demo/A;)Ljava/lang/String;
jstring  Java_com_google_android_exoplayer2_demo_A_show_1128237027(JNIEnv * env, jobject  v1, jobject v2)
{
//LOCAL_VARIABLE LL0 ~ LL1 v1 -> this // Lcom/google/android/exoplayer2/demo/A; 
//LOCAL_VARIABLE LL0 ~ LL1 v2 -> obj // Lcom/google/android/exoplayer2/demo/A; 
//LABEL               |  LL0: line 9
L0: ;
//CONST_STRING        |     |v0="A and A"
jstring v0_0 = (*env)->NewStringUTF(env, "A and A");
//RETURN              |     |return v0
return v0_0;
//LABEL               |  LL1:
L1: ;
}


//method:0002  access:0x0001
//Lcom/google/android/exoplayer2/demo/A;.show(Lcom/google/android/exoplayer2/demo/D;)Ljava/lang/String;
jstring  Java_com_google_android_exoplayer2_demo_A_show_1762289766(JNIEnv * env, jobject  v1, jobject v2)
{
//LOCAL_VARIABLE LL0 ~ LL1 v1 -> this // Lcom/google/android/exoplayer2/demo/A; 
//LOCAL_VARIABLE LL0 ~ LL1 v2 -> obj // Lcom/google/android/exoplayer2/demo/D; 
//LABEL               |  LL0: line 5
L0: ;
//CONST_STRING        |     |v0="A and D"
jstring v0_0 = (*env)->NewStringUTF(env, "A and D");
//RETURN              |     |return v0
return v0_0;
//LABEL               |  LL1:
L1: ;
}

int registerNativeSymbols420217909_439(JNIEnv * env) { 
int returnVal = JNI_TRUE; JNINativeMethod symbolListApi[] = { 
{"__initNative", "()V",  (void *)Java_com_google_android_exoplayer2_demo_A___initNative_39797 },
{"show", "(Lcom/google/android/exoplayer2/demo/A;)Ljava/lang/String;",  (void *)Java_com_google_android_exoplayer2_demo_A_show_1128237027 },
{"show", "(Lcom/google/android/exoplayer2/demo/D;)Ljava/lang/String;",  (void *)Java_com_google_android_exoplayer2_demo_A_show_1762289766 }, 
}; 
jclass clazz = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/A");
if (clazz == NULL) { 
 returnVal = JNI_FALSE; 
}
if ((*env)->RegisterNatives(env, clazz, symbolListApi, sizeof(symbolListApi) / sizeof(symbolListApi[0])) < 0) {
returnVal = JNI_FALSE; 
}
return returnVal;
}
