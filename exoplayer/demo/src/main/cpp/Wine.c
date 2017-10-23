#include <jni.h>
#include <stdio.h>
//class:0669  access:0x0001
//public class com.google.android.exoplayer2.demo.Wine
//field:0000  access:0x0002
//Lcom/google/android/exoplayer2/demo/Wine;.name Ljava/lang/String;

//method:0000  access:0x10001
//Lcom/google/android/exoplayer2/demo/Wine;.<init>()V
void  Java_com_google_android_exoplayer2_demo_Wine___initNative_39797(JNIEnv * env, jobject  v0)
{
//LOCAL_VARIABLE LL0 ~ LL1 v0 -> this // Lcom/google/android/exoplayer2/demo/Wine; 
//LABEL               |  LL0: line 16
L0: ;
//INVOKE_DIRECT       |     |v0.<init>()  //Ljava/lang/Object;.<init>()V
//LABEL               |  LL2: line 17
L2: ;
//RETURN_VOID         |     |return
return;
//LABEL               |  LL1:
L1: ;
}


//method:0001  access:0x0001
//Lcom/google/android/exoplayer2/demo/Wine;.drink()Ljava/lang/String;
jstring  Java_com_google_android_exoplayer2_demo_Wine_drink_1942950347(JNIEnv * env, jobject  v2)
{
//LOCAL_VARIABLE LL0 ~ LL1 v2 -> this // Lcom/google/android/exoplayer2/demo/Wine; 
//LABEL               |  LL0: line 20
L0: ;
//NEW_INSTANCE        |     |v0=NEW Ljava/lang/StringBuilder;
jobject v0_0 = (*env)->AllocObject(env, (*env)->FindClass(env, "java/lang/StringBuilder"));

//INVOKE_DIRECT       |     |v0.<init>()  //Ljava/lang/StringBuilder;.<init>()V
jclass localClass0 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId0 = (*env)->GetMethodID(env, localClass0, "<init>", "()V");
(*env)->CallVoidMethod(env, v0_0, methodId0);
//CONST_STRING        |     |v1="喝的是 "
jstring v1_0 = (*env)->NewStringUTF(env, "喝的是 ");
//INVOKE_VIRTUAL      |     |TEMP=v0.append(v1_0)  //Ljava/lang/StringBuilder;.append(Ljava/lang/String;)Ljava/lang/StringBuilder;
jclass localClass1 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId1 = (*env)->GetMethodID(env, localClass1, "append", "(Ljava/lang/String;)Ljava/lang/StringBuilder;");
jobject TEMP0 = (*env)->CallObjectMethod(env, v0_0, methodId1, v1_0);
//MOVE_RESULT         |     |v0=TEMP0
v0_0 = TEMP0;
//INVOKE_VIRTUAL      |     |TEMP=v2.getName()  //Lcom/google/android/exoplayer2/demo/Wine;.getName()Ljava/lang/String;
jclass localClass2 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/Wine");
jmethodID methodId2 = (*env)->GetMethodID(env, localClass2, "getName", "()Ljava/lang/String;");
jstring TEMP1 =  (jstring) (*env)->CallObjectMethod(env, v2, methodId2);
//MOVE_RESULT         |     |v1=TEMP1
v1_0 = TEMP1;
//INVOKE_VIRTUAL      |     |TEMP=v0.append(v1_0)  //Ljava/lang/StringBuilder;.append(Ljava/lang/String;)Ljava/lang/StringBuilder;
jclass localClass3 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId3 = (*env)->GetMethodID(env, localClass3, "append", "(Ljava/lang/String;)Ljava/lang/StringBuilder;");
jobject TEMP2 = (*env)->CallObjectMethod(env, v0_0, methodId3, v1_0);
//MOVE_RESULT         |     |v0=TEMP2
v0_0 = TEMP2;
//INVOKE_VIRTUAL      |     |TEMP=v0.toString()  //Ljava/lang/StringBuilder;.toString()Ljava/lang/String;
jclass localClass4 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId4 = (*env)->GetMethodID(env, localClass4, "toString", "()Ljava/lang/String;");
jstring TEMP3 =  (jstring) (*env)->CallObjectMethod(env, v0_0, methodId4);
//MOVE_RESULT         |     |v0=TEMP3
jstring v0_1 = TEMP3;
//RETURN              |     |return v0
return v0_1;
//LABEL               |  LL1:
L1: ;
}


//method:0002  access:0x0001
//Lcom/google/android/exoplayer2/demo/Wine;.getName()Ljava/lang/String;
jstring  Java_com_google_android_exoplayer2_demo_Wine_getName_1942950347(JNIEnv * env, jobject  v1)
{
//LOCAL_VARIABLE LL0 ~ LL1 v1 -> this // Lcom/google/android/exoplayer2/demo/Wine; 
//LABEL               |  LL0: line 9
L0: ;
//IGET                |     |v0=v1.name  //Lcom/google/android/exoplayer2/demo/Wine;.name Ljava/lang/String;
jclass localClass0 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/Wine");
jfieldID fieldId0 = (*env)->GetFieldID(env, localClass0, "name", "Ljava/lang/String;");
jstring v0_0 = (*env)->GetObjectField(env, v1, fieldId0);

//RETURN              |     |return v0
return v0_0;
//LABEL               |  LL1:
L1: ;
}


//method:0003  access:0x0001
//Lcom/google/android/exoplayer2/demo/Wine;.setName(Ljava/lang/String;)V
void  Java_com_google_android_exoplayer2_demo_Wine_setName_1428966913(JNIEnv * env, jobject  v0, jstring v1)
{
//LOCAL_VARIABLE LL0 ~ LL1 v0 -> this // Lcom/google/android/exoplayer2/demo/Wine; 
//LOCAL_VARIABLE LL0 ~ LL1 v1 -> name // Ljava/lang/String; 
//LABEL               |  LL0: line 13
L0: ;
//IPUT                |     |v0.name=v1  //Lcom/google/android/exoplayer2/demo/Wine;.name Ljava/lang/String;
jclass localClass0 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/Wine");
jfieldID fieldId0 = (*env)->GetFieldID(env, localClass0, "name", "Ljava/lang/String;");
(*env)->SetObjectField(env, v0, fieldId0, v1);

//LABEL               |  LL2: line 14
L2: ;
//RETURN_VOID         |     |return
return;
//LABEL               |  LL1:
L1: ;
}


//method:0004  access:0x0001
//Lcom/google/android/exoplayer2/demo/Wine;.toString()Ljava/lang/String;
jstring  Java_com_google_android_exoplayer2_demo_Wine_toString_1942950347(JNIEnv * env, jobject  v1)
{
//LOCAL_VARIABLE LL0 ~ LL1 v1 -> this // Lcom/google/android/exoplayer2/demo/Wine; 
//LABEL               |  LL0: line 27
L0: ;
//CONST               |     |v0=0x00000000  // int:0   float:0.000000
jint v0_0 = 0x00000000;
//RETURN              |     |return v0
return v0_0;
//LABEL               |  LL1:
L1: ;
}

int registerNativeSymbols420217909_462(JNIEnv * env) { 
int returnVal = JNI_TRUE; JNINativeMethod symbolListApi[] = { 
{"__initNative", "()V",  (void *)Java_com_google_android_exoplayer2_demo_Wine___initNative_39797 },
{"drink", "()Ljava/lang/String;",  (void *)Java_com_google_android_exoplayer2_demo_Wine_drink_1942950347 },
{"getName", "()Ljava/lang/String;",  (void *)Java_com_google_android_exoplayer2_demo_Wine_getName_1942950347 },
{"setName", "(Ljava/lang/String;)V",  (void *)Java_com_google_android_exoplayer2_demo_Wine_setName_1428966913 },
{"toString", "()Ljava/lang/String;",  (void *)Java_com_google_android_exoplayer2_demo_Wine_toString_1942950347 }, 
}; 
jclass clazz = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/Wine");
if (clazz == NULL) { 
 returnVal = JNI_FALSE; 
}
if ((*env)->RegisterNatives(env, clazz, symbolListApi, sizeof(symbolListApi) / sizeof(symbolListApi[0])) < 0) {
returnVal = JNI_FALSE; 
}
return returnVal;
}
