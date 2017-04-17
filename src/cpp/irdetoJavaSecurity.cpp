#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "iso98wrap.h"
#include "irdetoJavaSecurity.h"
#include "JACCommonModule.h"
#include "irdetoJavaSecurityExtension.h"
#include "dexAdaptor.h"
#include "dexOperator.h"
#include "antiDebug.h"
#include "threadManager.h"
#include "networkManager.h"

#ifdef _JAC_DEBUG_FILE
ac_FILE *fpTest = NULL;   
#endif

static IRDETO_SECURE_DATA gData;
static JAC_SECURITY_POLICY gPolicy = JAC_SECURITY_POLICY_NORMAL;
static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

static char stdClassPackages[][50]={
   "android.",
   "com.android.",
   "dalvik.",
   "java.",
   "javax."
};
char JCAModule1[]="irdetoJavaSecurity.cpp";

#ifndef _JAC_SIGNING
static void convertClassName(char *myClassName)
{
    int pos;
    for(pos=0; pos < ac_STRLEN(myClassName); pos++){
        if(myClassName[pos] == '.'){
            myClassName[pos] = '/';
        }
    }
}

static int isActivityClass(JNIEnv *env, char *className)
{
    char func[]="isActivityClass";
    int found = 0;

    jclass myClass = NULL;
    jclass boundaryClass = NULL;
    jstring superClaaName = NULL;
    jbyte *myJByte = NULL;
    jmethodID mtGetClassName = NULL;
    jthrowable expFlag = NULL;
    jclass classClass = env->FindClass(CLASS_CLASS);

    if(gPolicy != JAC_SECURITY_POLICY_HIGHEST){
        goto Exit;
    }

    convertClassName(className);
    myClass = env->FindClass(className);
    if(expFlag=env->ExceptionOccurred()){
        env->ExceptionClear();
        JACDebug(env,JCAModule1,func,(char *)"Failed to load B.class: %s\n",
                                className);
        goto Exit;
    }

    if((boundaryClass = env->GetSuperclass(myClass)) == NULL){
        JACDebug(env,JCAModule1,func,
                (char *)"Unable to get super class for: %s\n", className);
        goto Exit;
    }

    mtGetClassName = env->GetMethodID(classClass,
                        METHOD_GET_NAME_FOR_CLS,SIG_GET_NAME_FOR_CLS);
    if(expFlag=env->ExceptionOccurred()){
        env->ExceptionClear();
        JACDebug(env,JCAModule1,func,(char *)"Unable to get method: %s\n",
                                METHOD_GET_NAME_FOR_CLS);
        goto Exit;
    }

    superClaaName=(jstring)env->CallObjectMethod(boundaryClass, mtGetClassName);
    if(expFlag=env->ExceptionOccurred()){
        env->ExceptionClear();
        JACDebug(env,JCAModule1,func,(char *)"Unable to execute method: %s\n",
                                METHOD_GET_NAME_FOR_CLS);
        goto Exit;
    }

    myJByte =(jbyte*)env->GetStringUTFChars(superClaaName, NULL);
    if(strcmp((char *)myJByte, CLASS_BOUNDARY_STD_NAME) == 0){
        found = 1;
        JACDebug(env,JCAModule1,func,(char *)"Super class name: %s\n",myJByte);
    }

Exit:
    if (myJByte && superClaaName) {
        env->ReleaseStringUTFChars(superClaaName, (const char *)myJByte);
    }

    if (superClaaName) {
        env->DeleteLocalRef(superClaaName);
    }

    if (classClass) {
        env->DeleteLocalRef(classClass);
    }

    if (myClass) {
        env->DeleteLocalRef(myClass);
    }

    if (boundaryClass) {
        env->DeleteLocalRef(boundaryClass);
    }

    if (expFlag) {
        env->DeleteLocalRef(expFlag);
    }

    return found;
}

/****************************************************************************

  The function is trying to allocate bytes from a class.

****************************************************************************/
static ACCESS_STATUS getClassBytes(JNIEnv *env, char *className, unsigned char **data,int *length, jbyteArray *retJBArray)
{
    ACCESS_STATUS status = ACCESS_STATUS_SUCCESS;
    char func[] = "getClassBytes";

    jclass classCryptoManager = NULL;
    jmethodID midGetClassBytes = NULL;
    jstring jstrClassName = NULL;
    jbyteArray jBArray = NULL;
    jthrowable expFlag = NULL;

    classCryptoManager = env->FindClass(CLASSNAME_CRYPTOMANAGER);
    midGetClassBytes =env->GetStaticMethodID(classCryptoManager,
                                METHOD_GET_CLASS_BYTES, SIG_GET_CLASS_BYTES);
    if(expFlag=env->ExceptionOccurred()){
        env->ExceptionClear();
        JACDebugWarning(env, JCAModule1, func,(char *) "Failed to get method, %s\n",
                                METHOD_GET_APK_BYTES);
        status = ACCESS_STATUS_INVALID_JAVA_METHOD;
        goto Exit;
    }

    jstrClassName = env->NewStringUTF(className);
    jBArray = (jbyteArray) env->CallStaticObjectMethod(classCryptoManager,
                                        midGetClassBytes, jstrClassName);
    if(jBArray == NULL){
    	DBGWRAP(JACDebugWarning(env, JCAModule1, func,(char *)"NULL jBArray\n"));
        status = ACCESS_STATUS_GENERIC_ERROR;
        goto Exit;
    }

    *length = env->GetArrayLength(jBArray);
    *data = (unsigned char*) env->GetByteArrayElements(jBArray, NULL);
    *retJBArray = jBArray;

Exit:
    if (classCryptoManager) {
        env->DeleteLocalRef(classCryptoManager);
    }

    if (jstrClassName) {
        env->DeleteLocalRef(jstrClassName);
    }

    if (expFlag) {
        env->DeleteLocalRef(expFlag);
    }

    return status;
}
/************************************************************************

  Perform backward stack trace to allocate classes in the calling chain.

************************************************************************/
static int searchCallingClasses(JNIEnv *env, IRDETO_SECURE_DATA *data)
{
    IRDETO_SECURE_DATA localData;
    int pos;
    int realCount = 0;
    char lastClassName[CLASSNAME_LEN];
    char curClassName[CLASSNAME_LEN];
    jsize stackTraceLength = 0;
    char func[]="searchCallingClasses";

    jobject clsObj = NULL;
    jclass classStackTraceElement = NULL;
    jclass classThrowable = NULL;
    jmethodID methodTmp = NULL;
    jmethodID methodToString = NULL;
    jmethodID methodGetStackTrace = NULL;
    jmethodID methodGetClassName = NULL;
    jobjectArray stackTrace = NULL;
    jobject curStackTraceElement = NULL;
    jstring stackElementString = NULL;
    jbyte *myJByte = NULL;

    memset((IRDETO_SECURE_DATA*) &localData,0, sizeof(IRDETO_SECURE_DATA));
    classStackTraceElement=env->FindClass(CLASS_STACK_TRACE_ELEM);
    classThrowable = env->FindClass(CLASS_THROWABLE);
    methodGetStackTrace = env->GetMethodID(classThrowable,
                        METHOD_GET_STACK_TRACE,SIG_GET_STACKTRACE);
    methodToString = env->GetMethodID(classStackTraceElement,
                                METHOD_TO_STRING, SIG_TO_STRING);
    methodGetClassName = env->GetMethodID(classStackTraceElement,
                        METHOD_GET_CLASS_NAME, SIG_GET_CLASS_NAME);
    methodTmp = env->GetMethodID(classThrowable,
                        METHOD_THROWABLE_CONST,SIG_THROWABLE_CONST);
    clsObj = env->NewObject(classThrowable, methodTmp);
    stackTrace = (jobjectArray) env->CallObjectMethod( clsObj,
                                        methodGetStackTrace);
    localData.elementSize = env->GetArrayLength(stackTrace);
    allocateSecureMemory(&localData);
    localData.boundaryClassIdx = -1;

    for(pos = 0; pos < localData.elementSize; pos++){
        curStackTraceElement = env->GetObjectArrayElement(stackTrace, pos);
        stackElementString = (jstring) env->CallObjectMethod(
                         curStackTraceElement, methodGetClassName);
        myJByte = (jbyte*)env->GetStringUTFChars(stackElementString, NULL);

        if (curStackTraceElement) {
            env->DeleteLocalRef(curStackTraceElement);
            curStackTraceElement = NULL;
        }

        if(myJByte) {
            snprintf(curClassName,CLASSNAME_LEN,"%s", myJByte);
            if (stackElementString) {
                env->ReleaseStringUTFChars(stackElementString, (const char *)myJByte);
                env->DeleteLocalRef(stackElementString);
                stackElementString = NULL;
            }

        } else {
            if (stackElementString) {
                env->DeleteLocalRef(stackElementString);
                stackElementString = NULL;
            }

            continue;
        }

        if( strcmp(lastClassName, curClassName) != 0){
            snprintf(localData.className[realCount],CLASSNAME_LEN,"%s", curClassName);
            ac_sprintf(lastClassName,"%s", curClassName);
            if(isActivityClass(env, curClassName)){
                localData.boundaryClassIdx = realCount;
                JACDebug(env,JCAModule1,func,(char *) "B. class index: %d\n",
                                localData.boundaryClassIdx);
            }
            JACDebug(env, JCAModule1,func,(char *)"name: %s\n",localData.className[realCount]);
            realCount++;
        }
    }

    data->elementSize = realCount;
    data->boundaryClassIdx = localData.boundaryClassIdx;
    allocateSecureMemory(data);

    for(pos =0; pos < data->elementSize; pos++){
        ac_sprintf(data->className[pos],"%s",localData.className[pos]);
        ac_sprintf(data->signature[pos],"%s", "null");
    }
    freeSecureMemory(&localData);

    if (clsObj) {
        env->DeleteLocalRef(clsObj);
    }

    if (classStackTraceElement) {
        env->DeleteLocalRef(classStackTraceElement);
    }

    if (classThrowable) {
        env->DeleteLocalRef(classThrowable);
    }

    if (stackTrace) {
        env->DeleteLocalRef(stackTrace);
    }

    return data->elementSize;
}

static void  cleanupStorage(JAVAArchive *javaArchive, DexOperatorParam dexParam)
{
    for(int pos =0; pos < javaArchive->nItems; pos++){
	    if(javaArchive->archiveData[pos].bytes != NULL){
            ac_free(javaArchive->archiveData[pos].bytes);
	    }
    }
    if(javaArchive->archiveData != NULL)
    	ac_free(javaArchive->archiveData);
    if(dexParam.dexFiles != NULL)
    	ac_free(dexParam.dexFiles);
    if(dexParam.dexInternalParams)
    	ac_free(dexParam.dexInternalParams);
    if(dexParam.cookies != NULL)
        ac_free(dexParam.cookies);
    if(javaArchive->byteCodeData != NULL ){
	    if(javaArchive->byteCodeData->bytes != NULL){
	        ac_free(javaArchive->byteCodeData->bytes);
	    }
	    ac_free(javaArchive->byteCodeData);
    }
    if(javaArchive->indexData != NULL ){
	    if(javaArchive->indexData->bytes != NULL){
	        ac_free(javaArchive->indexData->bytes);
	    }
	    ac_free(javaArchive->indexData);
    }
}

/****************************************************************************

  The function is to manage to initialize the java archive files from 
  secure store. Any invalid data from the secure stire will cause the 
  function to ignore resulting at empty class loader. 

****************************************************************************/
static ACCESS_STATUS initializeJavaStorage(JNIEnv *env)
{
    ACCESS_STATUS status = ACCESS_STATUS_SUCCESS;
#ifdef _JAC_STANDALONE
    char storageDir[FILE_PATH_LEN+1];
    char storePath[FILE_PATH_LEN+1];
    char filePath[FILE_PATH_LEN+1];
    char jarFilePath[FILE_PATH_LEN+1];
    char level[SYSTEM_PROPERTY_LEN+1];
    JAVAArchive *javaArchive = NULL;
    JACConfig *jacConfig = NULL;
    ac_Status catStatus;
    int *cookies;
    DexOperatorParam dexOperatorParam;
    AntiDebugData adbg;
    AntiDebugData adbgIntercon;
    char func[] = "initializeJavaStorage";

    jmethodID appMid = NULL;
    jclass appCls = NULL;
    jstring jStrJarPath = NULL;
    jstring jStrNativeLibPath = NULL;
    jthrowable expFlag = NULL;

    init2ADbg(env, &adbg, V_DELTA_1);
    if((status = getStorageBase(env, storageDir)) != ACCESS_STATUS_SUCCESS){
        goto Exit;
    }
 
    init2ADbg(env, &adbgIntercon, V_DELTA_20);
    markAndVerifyADbg(env, &adbg, func, __LINE__);
    snprintf(storePath,FILE_PATH_LEN, "%s/%s",storageDir,JAC_DATA_NAME);
    if((catStatus = getJavaDataFromSecureStore(env,
                (ac_char *)storePath, &javaArchive, &jacConfig)) != AC_OK){
	    JACDebug(env,JCAModule1,func,(char*)"No valid archives. IAC status: 0x%x, ignore...\n", catStatus);
        status = ACCESS_STATUS_SUCCESS;
        goto Exit;
    }
    
    init2ADbg(env, &adbg, V_DELTA_5);
    markAndVerifyADbg(env, &adbgIntercon, func, __LINE__);
    DBGWRAP(JACDebug(env, JCAModule1, func, (char *)"write the archieve data begin...\n"));
    appCls  = env->FindClass(CLASS_APP_DVM);
    appMid = env->GetStaticMethodID(appCls, METHOD_SET_LDR_ENV, SIG_SET_LDR_ENV);
    memset(jarFilePath,0, FILE_PATH_LEN);
    for(int pos =0; pos < javaArchive->nItems; pos++){
        ac_sprintf(filePath,"%s/%s%d_.%s",storageDir, "app", pos, "jar");
    	strncat(jarFilePath,filePath,FILE_PATH_LEN -1);
    	strncat(jarFilePath,":",1);
    	saveToFile(env, filePath,
    			javaArchive->archiveData[pos].bytes, 
    			javaArchive->archiveData[pos].length);
    }
    
    JACDebug(env, JCAModule1, func, (char *)"write the archieve data end, path = %s\n", filePath);
    init2ADbg(env, &adbgIntercon, V_DELTA_10);
    markAndVerifyADbg(env, &adbg, func, __LINE__);
    jStrJarPath = env->NewStringUTF(jarFilePath);
    jStrNativeLibPath = env->NewStringUTF((char *)jacConfig->nativeLibDir);
    env->CallStaticVoidMethod(appCls, appMid, jStrJarPath, jStrNativeLibPath);
    if(expFlag=env->ExceptionOccurred()){
        env->ExceptionClear();
    	DBGWRAP(JACDebugWarning(env,JCAModule1,func,
		(char *)"Unable to setup loader environment\n"));
    }
    __system_property_get("ro.build.version.sdk", level);
    markAndVerifyADbg(env, &adbgIntercon, func, __LINE__);
    if(getCookies(env, &cookies, javaArchive->nItems) != ACCESS_STATUS_SUCCESS){
        status = ACCESS_STATUS_SUCCESS;
        goto Exit;
    }
    
    init2ADbg(env, &adbg, V_DELTA_2);
    dexOperatorParam.jarsNumber = javaArchive->nItems;
    dexOperatorParam.cookies = cookies;
    dexOperatorParam.indexData = javaArchive->indexData;
    dexOperatorParam.byteCodeData = javaArchive->byteCodeData;
    dexOperatorParam.useOdex = jacConfig->optDex;
    JACDebug(env,JCAModule1,func,(char *)"Optimize DEX indicator: %d\n", dexOperatorParam.useOdex);
    JACDebug(env,JCAModule1,func,(char*)"jarsNumbe: %d\n", dexOperatorParam.jarsNumber);
    dexOperatorParam.dexFiles = (void **)ac_calloc(javaArchive->nItems, sizeof(void *));
    dexOperatorParam.dexInternalParams = (DexInternalParams*)ac_malloc((javaArchive->nItems) *sizeof(DexInternalParams));
    markAndVerifyADbg(env, &adbg, func, __LINE__);
    if(processCookie(env, atoi(level), &dexOperatorParam) == -1){
         DBGWRAP(JACDebugWarning(env,JCAModule1,func, (char *)"Unable to process cookies\n"));
        status = ACCESS_STATUS_SUCCESS;
        goto Exit;
    }

    for(int pos =0; pos < javaArchive->nItems; pos++){
 	    init2ADbg(env, &adbg, V_DELTA_2);
        if (dexOperatorParam.dexFiles[pos] == NULL ){
            JACDebugWarning(env,JCAModule1,func, (char *)"Invalid dex pointers for index: %d\n",pos);
            break;
        }
	    markAndVerifyADbg(env, &adbg, func, __LINE__);
        classWalker(env, atoi(level),&dexOperatorParam, pos);
    }

    init2ADbg(env, &adbg, V_DELTA_2);
    initThread(env, (AppIVPolicy)jacConfig->appThread, &dexOperatorParam.dexInternalParams[0],JAC_THREAD_INDEX_APP_IV);
    markAndVerifyADbg(env, &adbg, func, __LINE__);
    init2ADbg(env, &adbgIntercon, V_DELTA_2);
    cleanupStorage(javaArchive, dexOperatorParam);
    markAndVerifyADbg(env, &adbgIntercon, func, __LINE__);
    JACDebug(env,JCAModule1,func,(char *)"Java archive path: %s\n",jarFilePath);

Exit:

    if (appCls) {
        env->DeleteLocalRef(appCls);
    }

    if (jStrJarPath) {
        env->DeleteLocalRef(jStrJarPath);
    }

    if (jStrNativeLibPath) {
        env->DeleteLocalRef(jStrNativeLibPath);
    }

    if (expFlag) {
        env->DeleteLocalRef(expFlag);
    }

#endif

    return status;
}

/***************************************************************************

  The section below forms part of JAC framework to work with JAVA project.
  Developer needs to add new entries of functions supporting new JVMs into
  the function table.

****************************************************************************/
static JAC_FUNCTION gFunctionTables[] = {
  {TYPE_JVM_DALVIK, searchCallingClasses,getClassBytes,initializeJavaStorage},
};

static int callSearchClasses(JNIEnv *env, IRDETO_SECURE_DATA *data)
{
    int status = 0;
    for(int pos = 0; pos < nelem(gFunctionTables); pos ++){
  	if(strcmp(TYPE_JVM, gFunctionTables[pos].typeJVM) == 0){
	    status = gFunctionTables[pos].fPtrSearchClasses(env,data);
	    break;
	}
    }
    return status;
}

static ACCESS_STATUS callGetClassBytes(JNIEnv *env, char *className, unsigned char **data, int *length, jbyteArray *retJBArray)
{
    ACCESS_STATUS status = ACCESS_STATUS_FAILED_TO_ALLOCATE_FUNCTION;
    for(int pos = 0; pos < nelem(gFunctionTables); pos ++){
  	if(strcmp(TYPE_JVM, gFunctionTables[pos].typeJVM) == 0){
	    status = gFunctionTables[pos].fPtrGetClassBytes(
			env, className,data,length,retJBArray);
	    break;
	}
    }
    return status;
}
static ACCESS_STATUS callInitializeJavaStorage(JNIEnv *env)
{
    ACCESS_STATUS status = ACCESS_STATUS_FAILED_TO_ALLOCATE_FUNCTION;
    for(int pos = 0; pos < nelem(gFunctionTables); pos ++){
        if(strcmp(TYPE_JVM, gFunctionTables[pos].typeJVM) == 0){
            status = gFunctionTables[pos].fPtrInitializeJavaStorage(env);
	    break;
	}
    }
    return status;
}
// end of section of function table

static ACCESS_STATUS validateJACEnv()
{
    ACCESS_STATUS status = ACCESS_STATUS_SUCCESS;

    if(gPolicy != JAC_SECURITY_POLICY_NORMAL &&
       gPolicy != JAC_SECURITY_POLICY_STRICT_STUB_CHECK &&
       gPolicy != JAC_SECURITY_POLICY_STATIC_ONLY &&
       gPolicy != JAC_SECURITY_POLICY_HIGHEST){
	    status = ACCESS_STATUS_INVALID_JAC_POLITY;
    }

    if ( (gData.elementSize == 0) && (gPolicy != JAC_SECURITY_POLICY_STATIC_ONLY) )
	    status = ACCESS_STATUS_EMPTY_VOUCHER;

    return status;
}

static ACCESS_STATUS validateVoucherIntegrity(JNIEnv *env, char *fileName, char *inSig)
{
    ACCESS_STATUS status = ACCESS_STATUS_SUCCESS;
    char func[] = "validateVoucherIntegrity";
    
    jclass classCryptoManager = NULL;
    jmethodID midHashVoucher = NULL;   
    jstring jstrSignature = NULL;
    jstring jstrFileName = NULL;
    jbyte *myJBytes = NULL;
    jthrowable expFlag = NULL;

    if(inSig == NULL || ac_STRLEN(inSig) == 0){
	    status = ACCESS_STATUS_INVALID_VOUCHER_INVALID_SIGNATURE;
        goto Exit;
    }

    classCryptoManager = env->FindClass(CLASSNAME_CRYPTOMANAGER);
    if(expFlag=env->ExceptionOccurred()){
        env->ExceptionClear();
        status = ACCESS_STATUS_INVALID_JAVA_CLASS;
        goto Exit;
    }

    midHashVoucher = env->GetStaticMethodID(classCryptoManager,
				METHOD_HASH_FILE,SIG_HASH_FILE);
    if(expFlag=env->ExceptionOccurred()){
        env->ExceptionClear();
        JACDebug(env, JCAModule1, func,(char *) "Failed to get method, %s\n",
						METHOD_HASH_FILE);
        status = ACCESS_STATUS_INVALID_JAVA_METHOD;
        goto Exit;
    }

    jstrFileName = env->NewStringUTF(fileName);
    jstrSignature = (jstring)env->CallStaticObjectMethod(classCryptoManager,
			midHashVoucher, jstrFileName);
    if((expFlag=env->ExceptionOccurred()) || jstrSignature == NULL ){
        env->ExceptionClear();
        JACDebug(env, JCAModule1, func,(char *)"Failed to call, %s\n", 
					METHOD_HASH_FILE);
	    status = ACCESS_STATUS_INVALID_JAVA_METHOD;
        goto Exit;
    }

    myJBytes = (jbyte *) env->GetStringUTFChars(jstrSignature,NULL);
    JACDebug(env, JCAModule1, func,(char *)"File Signature: %s\n", myJBytes);
    JACDebug(env, JCAModule1, func,(char *)"File Signature2: %s\n", inSig);
    if(strncmp((char *)myJBytes, inSig, 40) != 0 )
	    status = ACCESS_STATUS_INVALID_VOUCHER_INVALID_SIGNATURE;

Exit:
    if (myJBytes && jstrSignature) {
        env->ReleaseStringUTFChars(jstrSignature, (const char *)myJBytes);
    }

    if (jstrSignature) {
        env->DeleteLocalRef(jstrSignature);
    }

    if (classCryptoManager) {
        env->DeleteLocalRef(classCryptoManager);
    }

    if (jstrFileName) {
        env->DeleteLocalRef(jstrFileName);
    }

    if (expFlag) {
        env->DeleteLocalRef(expFlag);
    }

    return status;
}

/****************************************************************************

  The function loads the data from secure store containing the Java voucher.

****************************************************************************/
static ACCESS_STATUS retrieveVoucherFromIAC(JNIEnv *env, char *filePath)
{
    ACCESS_STATUS status = ACCESS_STATUS_SUCCESS;
    int wasClassName = 0;
    int wasStubClassName = 0;
    int wasAPKName = 0;
    int pos = 0;
    char *strPtr;
    unsigned char **voucher = NULL;
    char tmpBuf[READ_LINE_LEN];
    unsigned int nElements = 0;;
    ac_Status catStatus;
    char func[] = "retrieveVoucherFromIAC";

    pthread_mutex_lock(&lock);
    memset((IRDETO_SECURE_DATA *) &gData,0,sizeof(IRDETO_SECURE_DATA));

    if((catStatus = retrieveVoucherFromSecureStore(env, (ac_char*)filePath, 
			&voucher, &nElements)) != AC_OK || nElements < 5){
        DBGWRAP(JACDebugWarning(env,JCAModule1,func,(char *)"CAT status: 0x%x number of elements: %d\n", catStatus, nElements));
        pthread_mutex_unlock(&lock);
	    return ACCESS_STATUS_INVALID_VOUCHER_FROM_IAC;
    }
    JACDebugWarning(env,JCAModule1,func,(char *)"CAT status: 0x%x \n", catStatus);
    JACDebugWarning(env,JCAModule1,func,(char *)"number of elements: %d\n", nElements);
    
    for(int i =0; i < nElements; i++){
    	memcpy(tmpBuf, voucher[i], READ_LINE_LEN);
    	if((strPtr = strtok(tmpBuf," :\t\n")) == NULL || ac_STRLEN(strPtr) < 1 ) 
    	    continue;
            if(strncmp(strPtr, TOKEN_CLASS_NAME, 4) == 0){
                gData.elementSize++;
    	}
    }
    JACDebugWarning(env,JCAModule1,func,(char *)"element size: %d\n", gData.elementSize);
    
    if((status = allocateSecureMemory(&gData)) != ACCESS_STATUS_SUCCESS){
        pthread_mutex_unlock(&lock);
	    return status;
    }
    for(int i = 0; i < nElements; i++){
	    memcpy(tmpBuf, voucher[i], READ_LINE_LEN);
        if((strPtr = strtok(tmpBuf," :\t\n")) != NULL && ac_STRLEN(strPtr) > 0){ 
            if(strncmp(strPtr, TOKEN_CLASS_NAME, 4) == 0){
        		if(wasClassName){
        		    status = 
        			ACCESS_STATUS_INVALID_VOUCHER_CLASS_SIGNATURE_MISMATCH;
        		    break;
        		}  
        	        if((strPtr = strtok(NULL, " :\t\n")) != NULL){
        		    snprintf(gData.className[pos],CLASSNAME_LEN,"%s", strPtr);
        		    wasClassName = 1;
        		}
            }else if (strncmp(strPtr, TOKEN_STUB_CLASS_NAME, 8) == 0){
                if(wasStubClassName){
                    status =
                        ACCESS_STATUS_INVALID_VOUCHER_CLASS_SIGNATURE_MISMATCH;
                    break;
                }
                
                if((strPtr = strtok(NULL, " :\t\n")) != NULL){
                    snprintf(gData.stubClassName,CLASSNAME_LEN,"%s", strPtr);
                    wasStubClassName = 1;
                    JACDebug(env, JCAModule1, func, (char *)"Stub: %s\n", 
							gData.stubClassName);
                }
            }else if (strncmp(strPtr, TOKEN_APK_NAME, 7) == 0){
                if(wasAPKName){
                    status =
                        ACCESS_STATUS_INVALID_VOUCHER_APK_SIGNATURE_MISMATCH;
                    break;
                }
                if((strPtr = strtok(NULL, " :\t\n")) != NULL){
                    snprintf(gData.APKName,CLASSNAME_LEN,"%s", strPtr);
                    wasAPKName = 1;
                    JACDebug(env, JCAModule1, func, (char *)"APK: %s\n", 
								gData.APKName);
                }
            }else if (strncmp(strPtr, TOKEN_SIGNATURE, 9) == 0){
                if(!wasClassName && !wasStubClassName && !wasAPKName){
                    status =
                        ACCESS_STATUS_INVALID_VOUCHER_CLASS_SIGNATURE_MISMATCH;
                    break;
                }
                
                if((strPtr = strtok(NULL, " :\t\n")) != NULL){
                    if(wasClassName){
                        snprintf(gData.signature[pos],SIGNATURE_LEN,"%s",strPtr);
                        pos++;
                        wasClassName = 0;
                    }else if (wasStubClassName){
                        snprintf(gData.stubSignature,SIGNATURE_LEN,"%s", strPtr);
                        gData.stubClassIsSet = 1;
                        wasStubClassName = 0;
                        JACDebug(env, JCAModule1, func, (char *)"Stub: %s\n",
                                                gData.stubSignature);
                    }else{ // Must be APK
                        snprintf(gData.APKSignature,SIGNATURE_LEN,"%s", strPtr);
                        gData.APKIsSet = 1;
                        wasAPKName = 0;
                        JACDebug(env, JCAModule1, func, (char *)"APK: %s\n",
                                                gData.APKSignature);
                    }
                }else{
                    status =
                        ACCESS_STATUS_INVALID_VOUCHER_INVALID_CLASS_SIGNATURE;
                }
            }else if(strncmp(strPtr, TOKEN_POLICY, 6) == 0){
                if((strPtr = strtok(NULL, " :\t\n")) != NULL){
                    gPolicy = (JAC_SECURITY_POLICY) atoi(strPtr);
                    if((status = validateJACEnv())
                                != ACCESS_STATUS_SUCCESS) break;
                }
            }
        }
    }
    JACDebug(env,JCAModule1, func, (char *)"Policy: %d\n", gPolicy);
    pthread_mutex_unlock(&lock);

    return status;
}

/***********************************************************************

  Retrieve voucher stored in the "filePath". Use mutex locking to prevent 
  possible data corruption. THIS FUNCTION IS DEPRECATED.

************************************************************************/
static ACCESS_STATUS retrieveVoucher(JNIEnv *env, char *filePath)
{
    ACCESS_STATUS status = ACCESS_STATUS_SUCCESS;
    char tmpBuf[READ_LINE_LEN];
    char *strPtr;
    FILE *fp = NULL;
    int wasClassName = 0;
    int wasStubClassName = 0;
    int wasAPKName = 0;
    int integrityFieldFound = 0;
    int pos = 0;
    char func[] = "retrieveVoucher";

    pthread_mutex_lock(&lock);
    memset((IRDETO_SECURE_DATA *) &gData,0,sizeof(IRDETO_SECURE_DATA));
    fp= ac_fopen(filePath, "r");
    if(fp == NULL) return ACCESS_STATUS_NO_VOUCHER_FOUND;   

    while(fgets(tmpBuf, READ_LINE_LEN, fp) != NULL){
	if((strPtr = strtok(tmpBuf," :\t\n")) == NULL ){
	    continue;
  	}

    if(strncmp(strPtr, TOKEN_CLASS_NAME, 4) == 0){
	    gData.elementSize++;
	}else if(strncmp(strPtr, TOKEN_JAC_SIGNARURE, 13) == 0){
	    integrityFieldFound = 1;
	    strPtr = strtok(NULL," :\t\n");
	    if((status = validateVoucherIntegrity(env,filePath,strPtr))
			!= ACCESS_STATUS_SUCCESS){
	        ac_fclose(fp);
	        return status;
	    }
	}
    }
    if(gData.elementSize == 0){ 
	ac_fclose(fp);
	return ACCESS_STATUS_EMPTY_VOUCHER;
    }
    if(!integrityFieldFound)
	return ACCESS_STATUS_INVALID_VOUCHER_INVALID_SIGNATURE;

    status = allocateSecureMemory(&gData);
    if(status != ACCESS_STATUS_SUCCESS){
	ac_fclose(fp);
	return status;   
    }
    ac_fseek(fp, 0, SEEK_SET);
    while(fgets(tmpBuf, READ_LINE_LEN, fp) != NULL){
        if((strPtr = strtok(tmpBuf," :\t\n")) != NULL && ac_STRLEN(strPtr) > 0){ 
            if(strncmp(strPtr, TOKEN_CLASS_NAME, 4) == 0){
		if(wasClassName){
		    status = 
			ACCESS_STATUS_INVALID_VOUCHER_CLASS_SIGNATURE_MISMATCH;
		    break;
		}  
	        if((strPtr = strtok(NULL, " :\t\n")) != NULL){
		    ac_sprintf(gData.className[pos],"%s", strPtr);
		    wasClassName = 1;
		}
            }else if (strncmp(strPtr, TOKEN_STUB_CLASS_NAME, 8) == 0){
		if(wasStubClassName){
                    status = 
			ACCESS_STATUS_INVALID_VOUCHER_CLASS_SIGNATURE_MISMATCH;
                    break;
                }
                if((strPtr = strtok(NULL, " :\t\n")) != NULL){
                    ac_sprintf(gData.stubClassName,"%s", strPtr);
                    wasStubClassName = 1;
    		    JACDebug(env, JCAModule1, func, (char *)"Stub: %s\n", gData.stubClassName);
                }
	    }else if (strncmp(strPtr, TOKEN_APK_NAME, 7) == 0){
    		if(wasAPKName){
                    status = 
			ACCESS_STATUS_INVALID_VOUCHER_APK_SIGNATURE_MISMATCH;
                    break;
		} 
		if((strPtr = strtok(NULL, " :\t\n")) != NULL){
                    ac_sprintf(gData.APKName,"%s", strPtr);
                    wasAPKName = 1;
                    JACDebug(env, JCAModule1, func, (char *)"APK: %s\n", gData.APKName);
                }
	    }else if (strncmp(strPtr, TOKEN_SH1_HASH, 8) == 0){
		if(!wasClassName && !wasStubClassName && !wasAPKName){
		    status = 
			ACCESS_STATUS_INVALID_VOUCHER_CLASS_SIGNATURE_MISMATCH;
		    break;
		} 
		if((strPtr = strtok(NULL, " :\t\n")) != NULL){
		    if(wasClassName){
                    	ac_sprintf(gData.signature[pos],"%s", strPtr);
		    	pos++;
                    	wasClassName = 0;
		    }else if (wasStubClassName){ 
			ac_sprintf(gData.stubSignature,"%s", strPtr);
			gData.stubClassIsSet = 1;
			wasStubClassName = 0;
    		        JACDebug(env, JCAModule1, func, (char *)"Stub: %s\n", 
						gData.stubSignature);
		    }else{ // Must be APK
			ac_sprintf(gData.APKSignature,"%s", strPtr);
			gData.APKIsSet = 1;
			wasAPKName = 0;
			JACDebug(env, JCAModule1, func, (char *)"APK: %s\n",
                                                gData.APKSignature);
		    }
 		}else{
		    status = 
			ACCESS_STATUS_INVALID_VOUCHER_INVALID_CLASS_SIGNATURE;
		}
	    }else if(strncmp(strPtr, TOKEN_POLICY, 6) == 0){
		if((strPtr = strtok(NULL, " :\t\n")) != NULL){
                    gPolicy = (JAC_SECURITY_POLICY) atoi(strPtr);
    		    if((status = validateJACEnv()) 
				!= ACCESS_STATUS_SUCCESS) break;
                }
	    }
        }
    }
    JACDebug(env,JCAModule1, func, (char *)"Policy: %d\n", gPolicy);
    ac_fclose(fp);
    pthread_mutex_unlock(&lock);

    return status;
}
/**********************************************************************

  THIS FUNCTION IS DEPRECATED.

***********************************************************************/
static jstring getSignature(JNIEnv *env, char *className, jclass classCryptoManager, jmethodID midGetDigitalSignature, int *isException)
{
    char func[] = "getSignature";
    jboolean isNative = 1;
    jstring signature = NULL;
    jstring jstringTmp = NULL;
    jthrowable expFlag = NULL;

    jstringTmp = env->NewStringUTF(className);
    signature = (jstring)env->CallStaticObjectMethod(
	classCryptoManager,midGetDigitalSignature,jstringTmp,isNative);	
    if((expFlag=env->ExceptionOccurred()) || signature == NULL ){
	*isException = 1;
        env->ExceptionClear();
        JACDebug(env, JCAModule1, func,
		(char *) "%s\n","Failed to call getDigitalSignature");

    }

    if (jstringTmp) {
        env->DeleteLocalRef(jstringTmp);
    }

    if (expFlag) {
        env->DeleteLocalRef(expFlag);
    }

    return signature;
}
/***********************************************************************

  Generate digital signature for each class stored in IRDETO_SECURE_DATA  

************************************************************************/
static ACCESS_STATUS generateDigitalSignature(JNIEnv *env, IRDETO_SECURE_DATA *data)
{
    ACCESS_STATUS status = ACCESS_STATUS_SUCCESS;
    unsigned char *rawData = NULL;
    unsigned char digest[SIGNATURE_LEN];
    char hexData[SIGNATURE_LEN];
    char storePath[FILE_PATH_LEN];
    int length;
    ac_Status catStatus;
    char func[] = "generateDigitalSignature";

    jbyteArray jBytes = NULL; 

    if((status = allocateStore(env, storePath)) != ACCESS_STATUS_SUCCESS){
        goto Exit;
    } 
    
    DBGWRAP(JACDebug(env,JCAModule1,func,(char *)"about to check classes\n"));
    for(int pos =0; pos < data->elementSize; pos++){
        if(callGetClassBytes(env,data->className[pos],&rawData,&length,&jBytes) 
		!= ACCESS_STATUS_SUCCESS  ||
	        getHmacSha256ByHandle(env,rawData,length,(ac_char*)storePath,digest)
 		!= AC_OK) {
    	    ac_sprintf(data->signature[pos],"%s","null");
	        JACDebugWarning(env,JCAModule1,func,(char *)"Fail to get digital signature for class: %s\n", data->className[pos]);
	    }else{
            bytesToHex(digest, SIGNATURE_LEN/2, hexData);
	        ac_sprintf(data->signature[pos],"%s", hexData); 
	    }
        
	    if(jBytes && rawData){
            env->ReleaseByteArrayElements(jBytes, (jbyte*)rawData, 0);
	    }

	    if(jBytes){
    	    env->DeleteLocalRef(jBytes);
	    }

        rawData = NULL;
        jBytes = NULL;

        DBGWRAP(JACDebug(env,JCAModule1, func,(char *) "ClassName: %s, signature: %s\n",
                        data->className[pos], data->signature[pos]));
    }

Exit:

    return status;
}
/***********************************************************************

  Check digital signature of class against voucher which is stored in
  gData.  

************************************************************************/
static int matchClassSignature(char *className,char *signature,int *foundClass)
{
    int pos;
    int signatureMatch = 0;

    for(pos = 0; pos < gData.elementSize; pos++){
	    if(strcmp(gData.className[pos], className) == 0){
	        *foundClass = 1;
	        if(strcmp(gData.signature[pos], signature) == 0 ){
    		    signatureMatch = 1;
	        }
	        break;
	    }
    }
	
    return signatureMatch;
}
/***********************************************************************
*
*  Check digital signature of stub class against voucher which is stored in
*  gData.  
*
************************************************************************/
static ACCESS_STATUS checkStubClassSignature(IRDETO_SECURE_DATA *data)
{
    int pos;
    ACCESS_STATUS status = ACCESS_STATUS_AUTHENTICATION_FAILED_STUB_CLASS;

    for(pos = 0; pos < data->elementSize; pos++){
	    if(strcmp(data->className[pos], gData.stubClassName) == 0 &&
	        strcmp(data->signature[pos], gData.stubSignature) == 0){
	        status = ACCESS_STATUS_SUCCESS;
	        break;
	    }
    }

    return status;
}

static int isStandardPackage(char *className)
{
    int found = 0;
    int pos =0;
    int upperLoop = sizeof(stdClassPackages)/50;

    for(pos = 0; pos < upperLoop; pos++){
	    if(strncmp(className, stdClassPackages[pos], 
		    ac_STRLEN(stdClassPackages[pos])) == 0){
	        found = 1;
	         break;
	    }
    }

    return found;
}

static ACCESS_STATUS validateClassRange(JNIEnv *env, IRDETO_SECURE_DATA *data)
{
    ACCESS_STATUS status = ACCESS_STATUS_SUCCESS;
    int pos = 0 ;
    int foundClass = 0;
    int upperLimit = 0;
    char func[] ="validateClassRange";

    if(gPolicy != JAC_SECURITY_POLICY_HIGHEST){
	    return status;
    }

    if(data->boundaryClassIdx == -1){
    	upperLimit = data->elementSize;
    }else{
    	upperLimit =  data->boundaryClassIdx+1;
    }

    for (pos = 0; pos < upperLimit; pos++){
    	foundClass = 0;
    	if(!matchClassSignature(data->className[pos], 
			        data->signature[pos], &foundClass)){ 
    	    if(foundClass){
        		status=ACCESS_STATUS_AUTHENTICATION_FAILED_SIG_MISMATCH;
    	    }else{
    	    	if(isStandardPackage(data->className[pos])){
        		    continue;
    	    	}
        		status=ACCESS_STATUS_AUTHENTICATION_FAILED_CLASS_NOT_REGISTERED;
    	    }
            DBGWRAP(JACDebug(env, JCAModule1, func,
        		(char *) "Failed class: %s, signature: %s\n", 
    			data->className[pos], data->signature[pos]));
    	    break;
    	}
    }

    return status;
}    

static ACCESS_STATUS validateStubClass(IRDETO_SECURE_DATA *data)
{
    ACCESS_STATUS status = ACCESS_STATUS_SUCCESS;
    int pos;
    int matchSignature = 0;
    int foundClass = 0;

    if(gPolicy == JAC_SECURITY_POLICY_STRICT_STUB_CHECK){
    	if(!gData.stubClassIsSet){ // check immediate calling class
  	         matchSignature = matchClassSignature(data->className[0], 
				data->signature[0], &foundClass);
	        if(!matchSignature){
	        	status = ACCESS_STATUS_AUTHENTICATION_FAILED_STUB_CLASS;
	        }
        }else{
	        status = checkStubClassSignature(data);
	    }
    }

    return status;
}

static ACCESS_STATUS getAPKBytes(JNIEnv *env, unsigned char **data, int *length,jbyteArray *retJArray)
{
    ACCESS_STATUS status = ACCESS_STATUS_SUCCESS;
#ifdef _JAC_STANDALONE
    char func[] = "getAPKBytes";

    jclass classMyStub = NULL;
    jclass classCryptoManager = NULL;
    jmethodID midGetAPKBytes = NULL;
    jmethodID midGetAPKPath = NULL;
    jstring jstrAPKPath = NULL;
    jbyteArray jBArray = NULL;
    jthrowable expFlag = NULL;

    if(!gData.APKIsSet) {
        status = ACCESS_STATUS_NO_APK_ENTRY;
        goto Exit;
    }

    classMyStub = env->FindClass(CLASSNAME_MYSTUB);
    if(expFlag=env->ExceptionOccurred()){
        env->ExceptionClear();
        status = ACCESS_STATUS_INVALID_JAVA_CLASS;
        goto Exit;
    }

    midGetAPKPath = env->GetStaticMethodID(classMyStub,
                        METHOD_GET_APKPATH, SIG_GET_APKPATH);
    if(expFlag=env->ExceptionOccurred()){
        env->ExceptionClear();
        JACDebugWarning(env, JCAModule1, func,(char *) "Failed to get method, %s\n",
                                         METHOD_GET_APKPATH);
        status = ACCESS_STATUS_INVALID_JAVA_METHOD;
        goto Exit;
    }

    jstrAPKPath = (jstring)env->CallStaticObjectMethod(
                                        classMyStub,midGetAPKPath);
    if((expFlag=env->ExceptionOccurred()) || jstrAPKPath == NULL ){
        env->ExceptionClear();
        JACDebugWarning(env, JCAModule1, func,(char *)"Failed to call, %s\n",
                                        METHOD_GET_APKPATH);
        status = ACCESS_STATUS_INVALID_JAVA_METHOD;
        goto Exit;
    }

    classCryptoManager = env->FindClass(CLASSNAME_CRYPTOMANAGER);
    if(expFlag=env->ExceptionOccurred()){
        env->ExceptionClear();
        status = ACCESS_STATUS_INVALID_JAVA_CLASS;
    }

    midGetAPKBytes =env->GetStaticMethodID(classCryptoManager,
				METHOD_GET_APK_BYTES, SIG_GET_APK_BYTES);
    if(expFlag=env->ExceptionOccurred()){
        env->ExceptionClear();
        JACDebugWarning(env, JCAModule1, func,(char *) "Failed to get method, %s\n",
                                METHOD_GET_APK_BYTES);
        status = ACCESS_STATUS_INVALID_JAVA_METHOD;
        goto Exit;
    }

    jBArray = (jbyteArray) env->CallStaticObjectMethod(classCryptoManager,
					midGetAPKBytes, jstrAPKPath);
    if(jBArray == NULL){
	    DBGWRAP(JACDebugWarning(env, JCAModule1, func,(char *) "NULL jBArray\n"));
	    status = ACCESS_STATUS_GENERIC_ERROR;
        goto Exit;
    }

    *length = env->GetArrayLength(jBArray);
    *data = (unsigned char*) env->GetByteArrayElements(jBArray, NULL);
    *retJArray = jBArray;

Exit:
    if (classMyStub) {
        env->DeleteLocalRef(classMyStub);
    }

    if (classCryptoManager) {
        env->DeleteLocalRef(classCryptoManager);
    }

    if (jstrAPKPath) {
        env->DeleteLocalRef(jstrAPKPath);
    }

    if (expFlag) {
        env->DeleteLocalRef(expFlag);
    }

#endif

    return status;
}


static ACCESS_STATUS matchAPKSignature(JNIEnv *env)
{
    ACCESS_STATUS status = ACCESS_STATUS_SUCCESS;
#ifdef _JAC_STANDALONE
    int length = 0;
    int totalLength = 0;
    unsigned char *rawData = NULL;
    unsigned char digest[SIGNATURE_LEN];
    char hexData[SIGNATURE_LEN] = {'\0'};
    char storageDir[FILE_PATH_LEN];
    char storePath[FILE_PATH_LEN];
    ac_Status catStatus;
    ac_Op_Context pOperationContext = NULL;
    int iterationNum = 0;
    char func[] = "matchAPKSignature";

    jboolean isNative = 1;
    jbyteArray retJBytes = NULL;

    if(!gData.APKIsSet) {
        status = ACCESS_STATUS_NO_APK_ENTRY;
        goto Exit;
    }

    if((status = allocateStore(env, storePath)) != ACCESS_STATUS_SUCCESS){
        goto Exit;
    }

    DBGWRAP(JACDebug(env, JCAModule1, func,(char *)"about to call getAPKBytes\n"));
    if((status = getAPKBytes(env,&rawData,&length,&retJBytes))
                != ACCESS_STATUS_SUCCESS){
        goto Exit;
    }

    DBGWRAP(JACDebug(env, JCAModule1, func,(char *)"Calling getHmacSha256Init\n"));
    if(getHmacSha256Init(env, (ac_char*)storePath, &pOperationContext) != AC_OK){
        DBGWRAP(JACDebugWarning(env, JCAModule1, func,(char *)"Fail to perform HmacShaInit operation\n"));
        status = ACCESS_STATUS_GENERIC_ERROR;
        goto Exit;
    }

    iterationNum++;
    JACDebug(env, JCAModule1, func,(char *)"Current iteration is - %d\n", iterationNum);

    DBGWRAP(JACDebug(env, JCAModule1, func,(char *)"Calling getHmacSha256Init end and update begin...\n"));
    if(getHmacSha256Update(env, rawData, length, pOperationContext) != AC_OK){
        DBGWRAP(JACDebugWarning(env, JCAModule1, func,(char *)"Fail to perform HmacShaUpdate operation\n"));
        status = ACCESS_STATUS_GENERIC_ERROR;
        goto Exit;
    }

    totalLength = totalLength + length;

    DBGWRAP(JACDebug(env, JCAModule1, func,(char *)"Calling getHmacSha256Update end...\n"));
    DBGWRAP(JACDebug(env, JCAModule1, func,(char *)"Total data length after the iteration %d is %d\n", iterationNum, totalLength));

    if(retJBytes && rawData){
        DBGWRAP(JACDebugWarning(env, JCAModule1, func,(char *)"Releasing JBByte and RawData\n"));
        env->ReleaseByteArrayElements(retJBytes, (jbyte*)rawData, 0);
    }

    if(retJBytes){
        env->DeleteLocalRef(retJBytes);
    }

    rawData = NULL;
    retJBytes = NULL;
    DBGWRAP(JACDebug(env, JCAModule1, func,(char *)"Further iteration for getAPKBytes and HMACUpdate\n"));
    while (status != ACCESS_STATUS_GENERIC_ERROR)
    {
        length = 0;
        iterationNum++;
        JACDebug(env, JCAModule1, func,(char *)"Current iteration is - %d\n", iterationNum);

        DBGWRAP(JACDebug(env, JCAModule1, func,(char *)"about to call getAPKBytes in the loop\n"));
        status = getAPKBytes(env,&rawData,&length,&retJBytes);
        if((status != ACCESS_STATUS_SUCCESS) && (status != ACCESS_STATUS_GENERIC_ERROR)) {
            goto Exit;
        }

        if(status != ACCESS_STATUS_GENERIC_ERROR) {
            DBGWRAP(JACDebug(env, JCAModule1, func,(char *)"Calling getHmacSha256Update in the loop \n"));
            if(getHmacSha256Update(env, rawData, length, pOperationContext) != AC_OK){
                DBGWRAP(JACDebugWarning(env, JCAModule1, func,(char *)"Fail to perform HmacShaUpdate operation\n"));
                status = ACCESS_STATUS_GENERIC_ERROR;
                goto Exit;
            }

            totalLength = totalLength + length;
            JACDebug(env, JCAModule1, func,(char *)"data byte length read in current iteration is %d\n", length);
            DBGWRAP(JACDebug(env, JCAModule1, func,(char *)"Total data length after the iteration %d is %d\n", iterationNum, totalLength));
        }

        if(retJBytes && rawData){
            DBGWRAP(JACDebugWarning(env, JCAModule1, func,(char *)"Releasing JBByte and RawData\n"));
            env->ReleaseByteArrayElements(retJBytes, (jbyte*)rawData, 0);
        }

        if(retJBytes){
            env->DeleteLocalRef(retJBytes);
        }

        rawData = NULL;
        retJBytes = NULL;
    }

    JACDebug(env, JCAModule1, func,(char *)"Calling getHmacSha256Finalize %s\n", func);
    if(getHmacSha256Finalize(env, pOperationContext, digest) != AC_OK){
        DBGWRAP(JACDebugWarning(env, JCAModule1, func,(char *)"Fail to perform HmacShaFinalize operation\n"));
        status = ACCESS_STATUS_GENERIC_ERROR;
        return status;
    }

    bytesToHex(digest, SIGNATURE_LEN/2, hexData);
    JACDebug(env, JCAModule1, func,(char *)"digest: %s\n", hexData);
    if(strcmp(hexData, gData.APKSignature) != 0)
    {
        JACDebug(env, JCAModule1, func,(char *)"Authentication failed, Signature Extracted: %s \n", hexData);
        JACDebug(env, JCAModule1, func,(char *)"                       Signature from gData: %s\n", gData.APKSignature);
        status = ACCESS_STATUS_AUTHENTICATION_FAILED_CLASSES_SIGNATURE_MISMATCH;
    }
    else
    {

        JACDebugWarning(env, JCAModule1, func,(char *)"Authentication success, the result = %d\n", status);
        JACDebug(env, JCAModule1, func,(char *)"Authentication success, the result = %d\n", status);
        status = ACCESS_STATUS_SUCCESS;
    }
    
    DBGWRAP(JACDebug(env, JCAModule1, func,(char *)"Signature Extracted : %s, the result = %d\n", hexData, status));

Exit:
    if(retJBytes && rawData){
        env->ReleaseByteArrayElements(retJBytes, (jbyte*)rawData, 0);
    }

    if(retJBytes){
        env->DeleteLocalRef(retJBytes);
    }

#endif

    return status;
}

/****************************************************************************

  Public API routine (authenticateAllRegisteredClasses in original full name)

  This function should be called from JNI_OnLoad() or whenever a JNI 
  shared object is instantiated to gain access to JAC system. Check enum 
  ACCESS_STATUS for possible return code. This function should be called 
  only once. 

***************************************************************************/
ACCESS_STATUS aARC(JNIEnv *env, JavaVM *vm)
{
    setThreadJVM(vm);
    return aARC(env);
}

ACCESS_STATUS aARC(JNIEnv *env)
{
    ACCESS_STATUS status = ACCESS_STATUS_SUCCESS;
    IRDETO_SECURE_DATA data;
    int pos, foundClass;
    char myVoucherPath[VOUCHER_PATH_LEN];
    JACConfig *pJacConfig = NULL;
    AntiDebugData adbg;
    char func[] = "aARC";

    init2ADbg(env, &adbg, V_DELTA_120);
    if(env == NULL) return ACCESS_STATUS_INVALID_JNI_ENV;
    if((status = allocateStore(env, myVoucherPath)) != ACCESS_STATUS_SUCCESS)
	    return status;
    if((status = retrieveVoucherFromIAC(env, myVoucherPath)) 
					!= ACCESS_STATUS_SUCCESS)
     	return status; 
    if(setJACConfiguration(env, (ac_char *) myVoucherPath, &pJacConfig)==AC_OK 
		&& pJacConfig != NULL && pJacConfig->enableAdbg){
    	initThread(env, JAC_THREAD_INDEX_ADBG);
    }
    if(pJacConfig != NULL && pJacConfig->disableStaticIV){ 
        DBGWRAP(JACDebugWarning(env, JCAModule1, func,
			           (char *) "Static IV checking is disabled"));
    }else{
        if((status = matchAPKSignature(env)) != ACCESS_STATUS_SUCCESS) 
            return status;
    }    
    markAndVerifyADbg(env, &adbg, func, __LINE__);

#ifndef _JAC_ONLOAD_DYNAMIC_IV_OFF
    memset((IRDETO_SECURE_DATA *) &data,0,sizeof(IRDETO_SECURE_DATA));
    data.elementSize = gData.elementSize;
    status = allocateSecureMemory(&data);
    if(status != ACCESS_STATUS_SUCCESS) return status;

    for(pos = 0; pos < data.elementSize; pos++){
	    strcpy(data.className[pos], gData.className[pos]);
    }

    if((status = generateDigitalSignature(env, &data))!=ACCESS_STATUS_SUCCESS){
	    freeSecureMemory(&data);
	    return status;
    }

    for(pos = 0; pos < data.elementSize; pos++){
	    if(strcmp(gData.signature[pos], data.signature[pos]) != 0){
	        status = ACCESS_STATUS_AUTHENTICATION_FAILED_SIG_MISMATCH;
	        break;
	    }
    }
    freeSecureMemory(&data);

    if(status != ACCESS_STATUS_SUCCESS) return status;
#endif

    init2ADbg(env, &adbg, V_DELTA_180);
    status = callInitializeJavaStorage(env);
    markAndVerifyADbg(env, &adbg, func, __LINE__);

    return status;
}
/**********************************************************************

  Public API routine (authenticateCallingClasses in original full name)

  Perform backward class tracing when is called.. 

***********************************************************************/
ACCESS_STATUS aCC(JNIEnv *env, jobject obj)
{
    ACCESS_STATUS status = ACCESS_STATUS_SUCCESS;
    int pos;
    int foundClass;
    int matchSignature;
    IRDETO_SECURE_DATA data;
    char func[]="aCC";

    if(env == NULL) return ACCESS_STATUS_INVALID_JNI_ENV;

    if (gPolicy == JAC_SECURITY_POLICY_STATIC_ONLY) return status;

    if((status = validateJACEnv()) != ACCESS_STATUS_SUCCESS){
    	return status;
    }

    memset((IRDETO_SECURE_DATA *) &data,0,sizeof(IRDETO_SECURE_DATA));
    callSearchClasses(env, &data); 
    if(data.elementSize == 0) return ACCESS_STATUS_FAILED_STACK_TRACE;
    if((status=generateDigitalSignature(env, &data)) != ACCESS_STATUS_SUCCESS){
        freeSecureMemory(&data);
        return status; 
    }

    for(pos = 0; pos < data.elementSize; pos++){
	    foundClass = 0;
  	    matchSignature = matchClassSignature(data.className[pos], 
				data.signature[pos], &foundClass);
	    if(!matchSignature && foundClass) {
            DBGWRAP(JACDebugWarning(env, JCAModule1, func,
			(char *) "Troubled class: %s, hash: %s\n",
                        data.className[pos], data.signature[pos]));
	        status = ACCESS_STATUS_AUTHENTICATION_FAILED_SIG_MISMATCH;
	        break;
	    }
    }

    if(status == ACCESS_STATUS_SUCCESS){
	    if((status = validateStubClass(&data)) == ACCESS_STATUS_SUCCESS){
	        status = validateClassRange(env, &data);
	    }
    }
    freeSecureMemory(&data);

    return status;
}

/**************************************************************************

  Public API routine to clean up all the memory allocated including thoes
  by AC Agent.

***************************************************************************/
ACCESS_STATUS JAC_Shutdown(JNIEnv *env)
{
    ac_Status catStatus;
    char func[] ="JAC_Shutdown";

    pthread_mutex_lock(&lock);
    for(int pos = 0; pos < NUM_THREADS; pos++){
	    shutdownThread(env, (JACThreadIndex) pos);
    }

    if((catStatus=shutdownJAC_IAC(env)) != AC_OK){
	    return ACCESS_STATUS_SHUTDOWN_ERROR;
    }

    freeSecureMemory(&gData);
    pthread_mutex_unlock(&lock);
    DBGWRAP(JACDebugWarning(env, JCAModule1, func, (char *) "Shutting down JAC\n"));

    return ACCESS_STATUS_SUCCESS;
}

ACCESS_STATUS checkForCompletion(JNIEnv *env, JACThreadIndex threadIndex)
{
    return checkForCompletion2(env, threadIndex);
}
#endif
