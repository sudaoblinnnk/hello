#include <jni.h>
#include <stdio.h>
#include <android/log.h>

const char * TAG = "kurt";

#define LOGD(fmt, args...) __android_log_print(ANDROID_LOG_DEBUG,  TAG, fmt, ##args)

//method:0003  access:0x0002
//Lcom/irdeto/j2n/firstapplication/MainActivity;.test3_str_array()Ljava/lang/String;
jstring  Java_com_irdeto_j2n_firstapplication_MainActivity_test3_str_array(JNIEnv * env, jobject  v5)
{
    LOGD("%d", Java_com_irdeto_j2n_firstapplication_MainActivity_test4_switch(1));
//LOCAL_VARIABLE LL0 ~ LL1 v0 -> all // Ljava/lang/String;
//LOCAL_VARIABLE LL2 ~ LL1 v1 -> i // I
//LOCAL_VARIABLE LL3 ~ LL1 v2 -> num // [Ljava/lang/String;
//LOCAL_VARIABLE LL4 ~ LL1 v5 -> this // Lcom/irdeto/j2n/firstapplication/MainActivity;
//LABEL               |  LL4: line 73
L4: ;
//CONST               |     |v3=0x00000003  // int:3   float:0.000000
int v3_0 = 0x00000003;
//NEW_ARRAY           |     |v2=new java.lang.String[][v3]
jobjectArray v2_0 = (*env)->NewObjectArray(env, 3, (*env)->FindClass(env, "java/lang/String"), 0);
//CONST               |     |v3=0x00000000  // int:0   float:0.000000
int v3_1 = 0x00000000;
//CONST_STRING        |     |v4="1"
jstring v4_0 = (*env)->NewStringUTF(env, "1");
//APUT                |     |v2[v3]=v4;
//CONST               |     |v3=0x00000001  // int:1   float:0.000000
int v3_2 = 0x00000001;
//CONST_STRING        |     |v4="2"
jstring v4_1 = (*env)->NewStringUTF(env, "2");
//APUT                |     |v2[v3]=v4;
//CONST               |     |v3=0x00000002  // int:2   float:0.000000
int v3_3 = 0x00000002;
//CONST_STRING        |     |v4="3"
jstring v4_2 = (*env)->NewStringUTF(env, "3");
//APUT                |     |v2[v3]=v4;
//LABEL               |  LL3:
L3: ;
//CONST_STRING        |     |v0=""
jstring v0_0 = (*env)->NewStringUTF(env, "");
//LABEL               |  LL0: line 75
L0: ;
//CONST               |     |v1=0x00000000  // int:0   float:0.000000
int v1_0 = 0x00000000;
//LABEL               |  LL2:
L2:
//ARRAY_LENGTH        |     |v3 = v2.length
//IF_GE               |     |if (v1 >= v3) {  goto L5; }
//if (v1_0 >= v3_3) {  goto L5; }
//LABEL               |  LL6: line 76
L6: ;
//NEW_INSTANCE        |     |v3=NEW Ljava/lang/StringBuilder;
jobject v3_4 = (*env)->AllocObject(env, (*env)->FindClass(env, "java/lang/StringBuilder"));

//INVOKE_DIRECT       |     |v3.<init>()  //Ljava/lang/StringBuilder;.<init>()V
jclass localClass0 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId0 = (*env)->GetMethodID(env, localClass0, "<init>", "()V");
(*env)->CallVoidMethod(env, v3_4, methodId0);
//INVOKE_VIRTUAL      |     |TEMP=v3.append(v0_0)  //Ljava/lang/StringBuilder;.append(Ljava/lang/String;)Ljava/lang/StringBuilder;
jclass localClass1 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId1 = (*env)->GetMethodID(env, localClass1, "append", "(Ljava/lang/String;)Ljava/lang/StringBuilder;");
jobject TEMP0 = (*env)->CallObjectMethod(env, v3_4, methodId1, v0_0);

//MOVE_RESULT         |     |v3=TEMP0
//AGET                |     |v4=v2[v1];
//INVOKE_VIRTUAL      |     |TEMP=v3.append(v4_2)  //Ljava/lang/StringBuilder;.append(Ljava/lang/String;)Ljava/lang/StringBuilder;
jclass localClass2 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId2 = (*env)->GetMethodID(env, localClass2, "append", "(Ljava/lang/String;)Ljava/lang/StringBuilder;");
jobject TEMP1 = (*env)->CallObjectMethod(env, TEMP0, methodId2, v4_2);
//MOVE_RESULT         |     |v3=TEMP1
//INVOKE_VIRTUAL      |     |TEMP=v3.toString()  //Ljava/lang/StringBuilder;.toString()Ljava/lang/String;
jclass localClass3 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId3 = (*env)->GetMethodID(env, localClass3, "toString", "()Ljava/lang/String;");
jstring TEMP2 =  (jstring) (*env)->CallObjectMethod(env, TEMP1, methodId3);
//MOVE_RESULT         |     |v0=TEMP2
//ADD_INT_LIT_X       |     |v1 = v1 + 1;
v1_0 = v1_0 + 1;
//GOTO                |     |goto L2;
//goto L2;
//LABEL               |  LL5: line 78
L5:
//RETURN              |     |return v0
return TEMP2;
//LABEL               |  LL1:
L1:
;

}

jint  Java_com_irdeto_j2n_firstapplication_MainActivity_test4_switch(int v2 )
{

    L2: ;
//CONST               |     |v0=0x00000001  // int:1   float:0.000000
    int v0_0 = 0x00000001;
//LABEL               |  LL0: line 96
    L0:
//IF_EQZ              |     |if (v3 == 0) { goto L3; }
    if (v2 == 0) { goto L3; }
//IF_NEZ              |     |if (v0 != 0) { goto L4; }
    if (v0_0 != 0) { goto L4; }
//LABEL               |  LL3:
    L3: ;
//CONST               |     |v1=0x00000001  // int:1   float:0.000000
    v0_0 = 0x00000001;
//LABEL               |  LL5:
    L5: ;
//RETURN              |     |return v1
    return v0_0;
//LABEL               |  LL4:
    L4:
//CONST               |     |v1=0x00000000  // int:0   float:0.000000
    v0_0 = 0x00000000;
//GOTO                |     |goto L5;
    goto L5;
//LABEL               |  LL1:
    L1:
    ;
/*
//LOCAL_VARIABLE LL0 ~ LL1 v0 -> b // I
//LOCAL_VARIABLE LL2 ~ LL1 v1 -> this // Lcom/irdeto/j2n/firstapplication/MainActivity;
//LOCAL_VARIABLE LL2 ~ LL1 v2 -> a // I
//LABEL               |  LL2: line 100
    L2: ;
//CONST               |     |v0=0x00000000  // int:0   float:0.000000
    int v0_0 = 0x00000000;
//LABEL               |  LL0: line 101
    L0: ;
switch(v2) {
 case 1: goto L3;
 case 2: goto L4;
 default: goto L5;
}
//LABEL               |  LL5: line 109
    L5: ;
//CONST               |     |v0=0x00000003  // int:3   float:0.000000
    int v0_1 = 0x00000003;
//LABEL               |  LL6: line 112
    L6:
//RETURN              |     |return v0
    return v0_1;
//LABEL               |  LL3: line 231
    L3: ;
//CONST               |     |v0=0x00000001  // int:1   float:0.000000
    v0_1 = 0x00000001;
//LABEL               |  LL7: line 232
    L7: ;
//GOTO                |     |goto L6;
    goto L6;
//LABEL               |  LL4: line 234
    L4:  ;
//CONST               |     |v0=0x00000002  // int:2   float:0.000000
    v0_1 = 0x00000002;
//LABEL               |  LL8: line 235
    L8: ;
//GOTO                |     |goto L6;
    goto L6;
//LABEL               |  LL9: line 357
    L9:
//LABEL               |  LL1:
    L1:
    ;
*/
}


static int registerNativeSymbols793367844_33(JNIEnv * env) { int returnVal = JNI_TRUE; JNINativeMethod symbolListApi[] = {

    {"test3_str_array", "()Ljava/lang/String;",  (void *)Java_com_irdeto_j2n_firstapplication_MainActivity_test3_str_array } };
    jclass clazz = (*env)->FindClass(env, "com/irdeto/j2n/firstapplication/MainActivity");
    if (clazz == NULL) { returnVal = JNI_FALSE; }if ((*env)->RegisterNatives(env, clazz, symbolListApi, sizeof(symbolListApi) / sizeof(symbolListApi[0])) < 0) {returnVal = JNI_FALSE; }return returnVal;}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) { JNIEnv *env; jint registerResult = JNI_FALSE; if ((*vm)->GetEnv(vm, (void **) &env, JNI_VERSION_1_4) != JNI_OK) { return -1; }
registerNativeSymbols793367844_33(env);
 return JNI_VERSION_1_4; }
