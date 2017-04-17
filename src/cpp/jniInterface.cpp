#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "iso98wrap.h"
#ifndef _JAC_SIGNING
#include "irdetoJavaSecurity.h"
#include "antiDebug.h"
#else
#include "irdetoJavaSecurityExtension.h"
#endif
#include "JACCommonModule.h"

char JCAModule4[]="jniInterface.cpp";

#ifndef _JAC_SIGNING

#ifdef _JAC_STANDALONE
/***************************************************************************
*
*   An API to access backgroud application thread associated with index
*   JAC_THREAD_INDEX_APP_IV. This thread may not exist depending upon 
*   execution conditions
*
****************************************************************************/
JNIEXPORT jint JNICALL Java_com_ir_app_NativeAppManager_getAppIVStatus(JNIEnv *env, jobject obj, jstring jType, jobject reserve2)
{
    jint retCode;
    jbyte *threadType = NULL;
    int intType = 999;

    DBGWRAP(JACDebug(env, JCAModule4,__FUNCTION__,(char *)"starting...\n"));
    if(jType == NULL){
        return ACCESS_STATUS_INVALID_INVALID_PARAMETER;
    }

    threadType = (jbyte*)env->GetStringUTFChars(jType, NULL);
    intType = atoi((char *)threadType);
    retCode = checkForCompletion(env, (JACThreadIndex) intType);
    env->ReleaseStringUTFChars(jType,(char *)threadType);
    JACDebug(env, JCAModule4,__FUNCTION__,(char *)"return code: %d\n", retCode);
    
    return retCode;
}
/****************************************************************************
*
*   AN JNI function to be called by application and perform backward class
*   tracing.
*
****************************************************************************/
JNIEXPORT jstring JNICALL Java_com_ir_app_NativeAppManager_getPermission(JNIEnv *env, jobject obj, jstring reserve1, jobject reserve2)
{
    jstring retCode;
    ACCESS_STATUS status;
    char myMessage[JNI_RETURN_MESSAGE_LEN];

    status= aCC(env, obj);
    sprintf(myMessage, "%d", status);
    retCode = env->NewStringUTF(myMessage);

    return retCode;
}

static JNINativeMethod gJACNMethods[] = {
  /* name, signature, funcPtr */
   {(char*)"getPermission", (char*)"(Ljava/lang/String;Ljava/lang/Object;)Ljava/lang/String;", (void *) Java_com_ir_app_NativeAppManager_getPermission},
   {(char*)"getAppIVStatus", (char*)"(Ljava/lang/String;Ljava/lang/Object;)I", (void *) Java_com_ir_app_NativeAppManager_getAppIVStatus},
};

/****************************************************************************
*
*   AN JNI function to be loaded when NativeAppManager class is instantiated.
*
****************************************************************************/
jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
    ACCESS_STATUS status = ACCESS_STATUS_SUCCESS;
    AntiDebugData adbgIndv;
    AntiDebugData adbgIndvIntercon;
    char func[] = "JNI_OnLoad";

    JNIEnv* env = NULL;
    jclass cls = NULL;
    jint result = JNI_ERR;

    init2ADbgNoJNI(&adbgIndv, V_DELTA_1);
    if(vm == NULL){
	    return JNI_ERR;
    }

    init2ADbgNoJNI(&adbgIndvIntercon, V_DELTA_1);
    markAndVerifyADbgNoJNI(&adbgIndv);
    if ( vm->GetEnv((void **) &env, JNI_VERSION_1_4) ) {
	    return JNI_ERR;
    }

    init2ADbg(env, &adbgIndv, V_DELTA_1);
    markAndVerifyADbg(env, &adbgIndvIntercon, func, __LINE__);
    DBGWRAP(JACDebug(env, JCAModule4, func, (char *) "Loading library...\n"));

    markAndVerifyADbg(env, &adbgIndv, func, __LINE__);
    status = aARC(env, vm);
    init2ADbg(env, &adbgIndv, V_DELTA_1);

    if (status != ACCESS_STATUS_SUCCESS) {
	    JACDebugWarning(env, JCAModule4, func, (char *)"Test1: %d, exiting....\n", status);
	    exit(EXIT_CODE_STARTUP); //Just crash it
	    return JNI_ERR;
    }

    cls = env->FindClass(CLASSNAME_NATIVE_APP);
    init2ADbg(env, &adbgIndvIntercon, V_DELTA_2);
    markAndVerifyADbg(env, &adbgIndv, func, __LINE__);

    int mySize = sizeof(gJACNMethods)/sizeof(gJACNMethods[0]);
    result = env->RegisterNatives(cls, gJACNMethods, mySize);

    if (cls) {
        env->DeleteLocalRef(cls);
    }

    if (result < 0) {
        return JNI_ERR;
    }

    JACDebug(env, JCAModule4, func, (char *)"Test2: %d\n", status);
    markAndVerifyADbg(env, &adbgIndvIntercon, func, __LINE__);
    return JNI_VERSION_1_4;
}
#endif  //_JAC_STANDALONE

#else //This is _JAC_SIGNING

JNIEXPORT jstring JNICALL Java_com_irdeto_secureaccess_CryptoManager_getHmacShaSignature (JNIEnv *env, jobject obj, jbyteArray jInput, jstring jStorePath, jstring jKeyHandle, jstring jShaType)
{
    char storePath[FILE_PATH_LEN];
    char hexData[SIGNATURE_LEN];
    unsigned char *rawData;
    int length;
    unsigned char digest[SIGNATURE_LEN];
    ac_Status catStatus;
    char func[]="Java_com_irdeto_secureaccess_CryptoManager_getHmacShaSignature";

    jbyte *localStore = NULL;
    jstring retStr = NULL;

    if(env == NULL){
       	retStr = env->NewStringUTF("null");
        JACDebugWarning(env, JCAModule4, func, (char *)"null env\n");
	    return retStr;
    }

    localStore = (jbyte*)env->GetStringUTFChars(jStorePath, NULL);
    rawData = (unsigned char*) env->GetByteArrayElements(jInput, NULL);
    length = env->GetArrayLength(jInput);

    if((catStatus = getHmacSha256ByHandle(env,rawData,
			length,(ac_char*)localStore,digest)) != AC_OK){
       	retStr = env->NewStringUTF("null");
	    JACDebugWarning(env, JCAModule4, func, (char *)"failed to call getHmacSha256ByHandle, return code: %x\n", catStatus);
    }else{
       	bytesToHex(digest, SIGNATURE_LEN/2, hexData);
       	retStr = env->NewStringUTF(hexData);
       	JACDebug(env, JCAModule4, func, (char *)"Hex data: %s\n", hexData);
    }

    env->ReleaseByteArrayElements(jInput, (jbyte*)rawData, 0);
    env->ReleaseStringUTFChars(jStorePath,(char *)localStore);
    JACDebug(env, JCAModule4, func, (char *)"finish retrieving Hmac data\n");

    return retStr;
}

static JNINativeMethod gJACNMethods[] = {
  /* name, signature, funcPtr */
   {(char*)"getHmacShaSignature", (char*)"([BLjava/lang/String;Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;", (void *) Java_com_irdeto_secureaccess_CryptoManager_getHmacShaSignature},
};

jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
    ACCESS_STATUS status = ACCESS_STATUS_SUCCESS;
    char func[] = "JNI_OnLoad";

    JNIEnv* env = NULL;
    jclass cls = NULL;
    jint result = JNI_ERR;

    if(vm == NULL){
        return JNI_ERR;
    }

    if(vm->GetEnv((void **) &env, JNI_VERSION_1_4)){
        return JNI_ERR;
    }

    cls = env->FindClass(CLASSNAME_CM_SIGN);
    int mySize = sizeof(gJACNMethods)/sizeof(gJACNMethods[0]);
    result = env->RegisterNatives(cls, gJACNMethods, mySize);

    if (cls) {
        env->DeleteLocalRef(cls);
    }

    if (result < 0) {
        return JNI_ERR;
    }
    JACDebug(env, JCAModule4, func, (char *)"Loading JAC signing library...\n");

    return JNI_VERSION_1_4;
}

#endif  //_JAC_SIGNING
