#include <jni.h>
#include <stdio.h>
//class:1238  access:0x0001
//public class com.google.android.exoplayer2.demo.B extends com.google.android.exoplayer2.demo.A

//method:0000  access:0x10001
//Lcom/google/android/exoplayer2/demo/B;.<init>()V
void  Java_com_google_android_exoplayer2_demo_B___initNative_39797(JNIEnv * env, jobject  v0)
{
//LOCAL_VARIABLE LL0 ~ LL1 v0 -> this // Lcom/google/android/exoplayer2/demo/B; 
//LABEL               |  LL0: line 3
L0: ;
//INVOKE_DIRECT       |     |v0.<init>()  //Lcom/google/android/exoplayer2/demo/A;.<init>()V
//RETURN_VOID         |     |return
return;
//LABEL               |  LL1:
L1: ;
}


//method:0001  access:0x0001
//Lcom/google/android/exoplayer2/demo/B;.show(Lcom/google/android/exoplayer2/demo/A;)Ljava/lang/String;
jstring  Java_com_google_android_exoplayer2_demo_B_show_1128237027(JNIEnv * env, jobject  v1, jobject v2)
{
//LOCAL_VARIABLE LL0 ~ LL1 v1 -> this // Lcom/google/android/exoplayer2/demo/B; 
//LOCAL_VARIABLE LL0 ~ LL1 v2 -> obj // Lcom/google/android/exoplayer2/demo/A; 
//LABEL               |  LL0: line 9
L0: ;
//CONST_STRING        |     |v0="B and A"
jstring v0_0 = (*env)->NewStringUTF(env, "B and A");
//RETURN              |     |return v0
return v0_0;
//LABEL               |  LL1:
L1: ;
}


//method:0002  access:0x0001
//Lcom/google/android/exoplayer2/demo/B;.show(Lcom/google/android/exoplayer2/demo/B;)Ljava/lang/String;
jstring  Java_com_google_android_exoplayer2_demo_B_show_1339587940(JNIEnv * env, jobject  v1, jobject v2)
{
//LOCAL_VARIABLE LL0 ~ LL1 v1 -> this // Lcom/google/android/exoplayer2/demo/B; 
//LOCAL_VARIABLE LL0 ~ LL1 v2 -> obj // Lcom/google/android/exoplayer2/demo/B; 
//LABEL               |  LL0: line 5
L0: ;
//CONST_STRING        |     |v0="B and B"
jstring v0_0 = (*env)->NewStringUTF(env, "B and B");
//RETURN              |     |return v0
return v0_0;
//LABEL               |  LL1:
L1: ;
}

int registerNativeSymbols420217909_913(JNIEnv * env) { 
int returnVal = JNI_TRUE; JNINativeMethod symbolListApi[] = { 
{"__initNative", "()V",  (void *)Java_com_google_android_exoplayer2_demo_B___initNative_39797 },
{"show", "(Lcom/google/android/exoplayer2/demo/A;)Ljava/lang/String;",  (void *)Java_com_google_android_exoplayer2_demo_B_show_1128237027 },
{"show", "(Lcom/google/android/exoplayer2/demo/B;)Ljava/lang/String;",  (void *)Java_com_google_android_exoplayer2_demo_B_show_1339587940 }, 
}; 
jclass clazz = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/B");
if (clazz == NULL) { 
 returnVal = JNI_FALSE; 
}
if ((*env)->RegisterNatives(env, clazz, symbolListApi, sizeof(symbolListApi) / sizeof(symbolListApi[0])) < 0) {
returnVal = JNI_FALSE; 
}
return returnVal;
}
