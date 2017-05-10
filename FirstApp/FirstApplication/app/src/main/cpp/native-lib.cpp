#include <jni.h>
#include <string>

#include <android/log.h>

static const char * IAC_AGENT_TAG = "kurt";

#define LOGI(fmt, args...) __android_log_print(ANDROID_LOG_INFO,  IAC_AGENT_TAG, fmt, ##args)
#define LOGD(fmt, args...) __android_log_print(ANDROID_LOG_DEBUG, IAC_AGENT_TAG, fmt, ##args)
#define LOGE(fmt, args...) __android_log_print(ANDROID_LOG_ERROR, IAC_AGENT_TAG, fmt, ##args)

extern "C"
JNIEXPORT jstring JNICALL
Java_com_irdeto_aca_key_KeyLogic_valueAdd(JNIEnv * env, jobject v1,jint v2,jstring v3) {
    jclass localClass0 = env->FindClass("com/irdeto/aca/key/KeyLogic");
    jclass localClass1 = env->FindClass("java/lang/Class");
    jmethodID methodId0 = env->GetMethodID(localClass1, "getSimpleName", "()Ljava/lang/String;");
    //jstring str = (jstring) env->CallNonvirtualObjectMethod(localClass0, localClass1, methodId0);
    jstring str = (jstring) env->CallObjectMethod(localClass0, methodId0);

    jstring TEMP0 = (jstring) env->CallObjectMethod(localClass1, methodId0);
    //MOVE_RESULT         |     |v0=TEMP
    //INVOKE_VIRTUAL      |     |TEMP=v0.hashCode()  //Ljava/lang/String;.hashCode()I
    jclass localClass3 = env->FindClass("java/lang/String");
    jmethodID methodId1 = env->GetMethodID(localClass3, "hashCode", "()I");
    int TEMP1 = env->CallIntMethod(TEMP0, methodId1);
    LOGD("TEMP : %d" , TEMP1);
//    jclass cls = env->FindClass("com/irdeto/aca/key/KeyLogic");
//    jmethodID mid = env->GetMethodID(cls, "getClass", "()Ljava/lang/Class;");
//    jobject clsObj = env->CallObjectMethod((jobject) cls, mid);
//    cls = env->GetObjectClass(clsObj);
//    mid = env->GetMethodID(cls, "getSimpleName", "()Ljava/lang/String;");
//    jstring str = (jstring)env->CallObjectMethod(clsObj, mid);


//    jclass localClass0 = env->FindClass("com/irdeto/aca/key/KeyLogic");
//    jclass localClass1 = env->GetObjectClass(localClass0);
//    jmethodID methodId0 = env->GetMethodID(localClass1, "getSimpleName", "()Ljava/lang/String;");
//    jstring str = (jstring) env->CallObjectMethod(localClass1, methodId0);

    //jclass localClass3 = env->FindClass("java/lang/String");

//    jmethodID methodId1 = env->GetStaticMethodID(localClass0, "value1", "(I)I");
//    jint TEMP1 = env->CallStaticIntMethod(localClass0, methodId1, 1);
//
//    jmethodID methodId2 = env->GetMethodID(localClass0, "value2", "(I)I");
//    env->CallStaticIntMethod(localClass0, methodId2, 1);
//    env->CallNonvirtualIntMethod(localClass0, localClass0, methodId2, 1);
    return str;

}

extern "C"
JNIEXPORT jobject JNICALL
Java_com_irdeto_aca_key_KeyLogic_getInstance(JNIEnv *env, jclass type) {

    jclass localClass0 = env->FindClass("com/irdeto/aca/key/KeyLogic");
    jfieldID fieldId0 = env->GetStaticFieldID(localClass0, "instance", "Lcom/irdeto/aca/key/KeyLogic;");
    jobject v0 = env->GetStaticObjectField(localClass0, fieldId0);

    return v0;


}

extern "C"
JNIEXPORT jint JNICALL
Java_com_irdeto_aca_key_KeyLogic_value1(JNIEnv *env, jclass type, jint a) {

    return a;

}

extern "C"
JNIEXPORT jint JNICALL
Java_com_irdeto_aca_key_KeyLogic_value2(JNIEnv *env, jobject instance, jint b) {

    return b;

}


extern "C"
JNIEXPORT jstring JNICALL
Java_com_irdeto_j2n_firstapplication_MainActivity_staticStringFromJNI(JNIEnv *env, jclass type) {

    // TODO


    return env->NewStringUTF("111");
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_irdeto_j2n_firstapplication_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
