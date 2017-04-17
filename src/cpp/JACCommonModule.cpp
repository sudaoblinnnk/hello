#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "iso98wrap.h"
#include "irdetoJavaSecurity.h"
#include "JACCommonModule.h"
#include "irdetoJavaSecurityExtension.h"
#include "ac_Stdlib_Internal.h"

static char gStorageDir[FILE_PATH_LEN];
pthread_mutex_t storageLock = PTHREAD_MUTEX_INITIALIZER;
char JCAModule2[]="JACCommonModule.cpp";

void hexToBytes(char *inData, unsigned char *outData)
{
    char byteHex[3];
    int pos =0;
    int byteTmp;
    unsigned char *byteArr;

    if(inData == NULL) return;

    byteArr = (unsigned char *) ac_malloc(ac_STRLEN(inData)+1);

    while(inData[0] != '\0'){
        strncpy(byteHex,&inData[0],2);
        byteHex[2] = '\0';
        byteTmp = (int) ac_STRTOUL(byteHex, NULL, 16);
        byteArr[pos] = byteTmp;
        inData++;
        inData++;
        pos++;
    }

    memcpy(outData, byteArr, ac_STRLEN(inData)/2);
    ac_free(byteArr);
}

void bytesToHex(unsigned char *inData, int size,  char *outData)
{
    char *origPtr;
    char *dataHex;
    int pos =0;

    if(inData == NULL) return;

    dataHex = (char *)ac_calloc(size*2+1, sizeof(char *));
    origPtr = dataHex;

    while( pos < size){
        ac_sprintf(dataHex,"%02x",(unsigned char)inData[0]);
        inData++;
        dataHex++;
        dataHex++;
        pos++;
    }

    snprintf(outData, ac_STRLEN(origPtr)+1, "%s", origPtr);
    ac_free(origPtr);
}

/****************************************************************************

   A debug routine at warning level to display text message.

****************************************************************************/
#if defined (_JAC_DEBUG_ANDROID) || defined(_JAC_SIGNING)
void JACDebugWarning(JNIEnv *env, const char *module, const char *func, char *fmt, ...)
{
    va_list ap;
    char myMessage[MESSAGE_LINE_LEN];
    char myTitle[MESSAGE_LINE_LEN];

    jclass classLog = NULL;
    jmethodID midDebug = NULL;
    jstring jMessage = NULL;
    jstring jTitle = NULL;
    jthrowable expFlag = NULL;

    if(env == NULL) {
        goto Exit;
    }

    classLog =  env->FindClass(CLASSNAME_LOG);
    if(expFlag=env->ExceptionOccurred()){
        env->ExceptionClear();
        goto Exit;
    }

    midDebug = env->GetStaticMethodID(classLog,METHOD_DEBUG_WARNING,SIG_DEBUG);
    if(expFlag=env->ExceptionOccurred()){
        env->ExceptionClear();
        goto Exit;
    }

    ac_sprintf(myTitle, "MODULE: %s, FUNCTION: %s", module,func);
    va_start(ap, fmt);
    vsprintf(myMessage, fmt, ap);
    va_end(ap);

    jTitle = env->NewStringUTF(myTitle);
    jMessage = env->NewStringUTF(myMessage);
    env->CallStaticIntMethod(classLog, midDebug, jTitle, jMessage);

Exit:
    if (jTitle) {
        env->DeleteLocalRef(jTitle);
    }

    if (jMessage) {
        env->DeleteLocalRef(jMessage);
    }

    if (classLog) {
        env->DeleteLocalRef(classLog);
    }

    if (expFlag) {
        env->DeleteLocalRef(expFlag);
    }
}
#endif

/****************************************************************************

   A debug routine at debug level to display text message.

****************************************************************************/
#if defined(_JAC_DEBUG_ANDROID) || defined(_JAC_SIGNING)
void JACDebug(JNIEnv *env, const char *module, const char *func, char *fmt, ...)
{
    va_list ap;
    char myMessage[MESSAGE_LINE_LEN];
    char myTitle[MESSAGE_LINE_LEN];

    jclass classLog = NULL;
    jmethodID midDebug = NULL;
    jstring jMessage = NULL;
    jstring jTitle = NULL;
    jthrowable expFlag = NULL;

    if(env == NULL) {
        goto Exit;
    }

    classLog = env->FindClass(CLASSNAME_LOG);
    if(expFlag=env->ExceptionOccurred()){
        env->ExceptionClear();
        goto Exit;
    }

    midDebug = env->GetStaticMethodID(classLog,METHOD_DEBUG,SIG_DEBUG);
    if(expFlag=env->ExceptionOccurred()){
        env->ExceptionClear();
        goto Exit;
    }
    ac_sprintf(myTitle, "MODULE: %s, FUNCTION: %s", module,func);
    va_start(ap, fmt);
    vsprintf(myMessage, fmt, ap);
    va_end(ap);

    jTitle = env->NewStringUTF(myTitle);
    jMessage = env->NewStringUTF(myMessage);
    env->CallStaticIntMethod(classLog, midDebug, jTitle, jMessage);

Exit:
    if (jTitle) {
        env->DeleteLocalRef(jTitle);
    }

    if (jMessage) {
        env->DeleteLocalRef(jMessage);
    }

    if (classLog) {
        env->DeleteLocalRef(classLog);
    }

    if (expFlag) {
        env->DeleteLocalRef(expFlag);
    }
}
#endif

#ifndef _JAC_SIGNING
ACCESS_STATUS saveToFile(JNIEnv *env, char *fileName, unsigned char *data, int length)
{
    ACCESS_STATUS status = ACCESS_STATUS_SUCCESS;
    ac_uint32 bytesWritten = 0;
    ac_FILE *fp = NULL;
    char func[] ="saveToFile";

    if(env == NULL) return ACCESS_STATUS_INVALID_JNI_ENV;

    if((fp=ac_fopen(fileName, "wb+")) == NULL){
 	    JACDebug(env,JCAModule2,func,(char *)"Failed to open: %s\n",fileName);
	    return ACCESS_STATUS_INVALID_JAVA_ARCHIVE;
    }

    if((bytesWritten = ac_fwrite(data, 1, length, fp)) != length){
        JACDebug(env,JCAModule2,func,(char *)"Error to write, bytes: %d",bytesWritten);
        ac_fclose(fp);
        return ACCESS_STATUS_INVALID_JAVA_ARCHIVE;
    }
    ac_fclose(fp);

    return status;
}

/***********************************************************************

  Allocate memory for struct, IRDETO_SECURE_DATA

************************************************************************/
ACCESS_STATUS allocateSecureMemory(IRDETO_SECURE_DATA *data)
{
    int pos;

    data->className = (char **) ac_calloc(data->elementSize, sizeof(char *));
    data->signature = (char **) ac_calloc(data->elementSize, sizeof(char *));
    if(data->className == NULL || data->signature == NULL){
        return ACCESS_STATUS_MEMORY_ALLOCATION_FAILED;
    }

    for (pos =0; pos < data->elementSize; pos++){
        data->className[pos] = (char *) ac_calloc(CLASSNAME_LEN+1,sizeof(char));
        data->signature[pos] = (char *) ac_calloc(SIGNATURE_LEN+1,sizeof(char));
        if(data->className[pos] == NULL || data->signature[pos] == NULL){
            return ACCESS_STATUS_MEMORY_ALLOCATION_FAILED;
        }
    }

    return ACCESS_STATUS_SUCCESS;
}
/****************************************************************************

  To free application data, IRDETO_SECURE_DATA.

****************************************************************************/
void freeSecureMemory(IRDETO_SECURE_DATA *data)
{
    int pos;

    for(pos =0; pos < data->elementSize; pos++){
        if(data->className[pos] != NULL) ac_free(data->className[pos]);
        if(data->signature[pos] != NULL) ac_free(data->signature[pos]);
    }

    if(data->className != NULL) ac_free(data->className);
    if(data->signature != NULL) ac_free(data->signature);
}

ACCESS_STATUS allocateStore(JNIEnv *env, char *storePath)
{
    char filePath[FILE_PATH_LEN+1];
    ACCESS_STATUS status = ACCESS_STATUS_SUCCESS;
    char func[] = "allocateStore";

    if(env == NULL) return ACCESS_STATUS_INVALID_JNI_ENV;
#ifdef _JAC_STANDALONE
    if((status = getStorageBase(env, filePath))!= ACCESS_STATUS_SUCCESS)
	    return status;
    snprintf(storePath,FILE_PATH_LEN, "%s/%s",filePath,JAC_ACV_NAME);
#else
    snprintf(storePath,FILE_PATH_LEN, "%s/%s",VOUCHER_PATH_DEFAULT,JAC_ACV_NAME);
#endif
    DBGWRAP(JACDebug(env, JCAModule2, func,(char *)"Store path, %s, path length: %d\n", storePath, ac_STRLEN(storePath)));

    return ACCESS_STATUS_SUCCESS;
}

/****************************************************************************

   To locate voucher, irdeto_java_access.dat, that resides at directory, 
   "/data/ome/" in system mode and packaged with APK in standalone mode
   THIS FUNCTION IS DEPRECATED.

****************************************************************************/
ACCESS_STATUS allocateVoucher(JNIEnv *env, char *voucherPath)
{
    ACCESS_STATUS status = ACCESS_STATUS_SUCCESS;
    char func[] = "allocateVoucher";

    jclass classMyStub = NULL;
    jmethodID midGetAPKName = NULL;
    jstring jstrName = NULL;
    jbyte *jbyteName = NULL;
    jthrowable expFlag = NULL;

    classMyStub = env->FindClass(CLASSNAME_MYSTUB);
    if(expFlag=env->ExceptionOccurred()){
        env->ExceptionClear();
        status = ACCESS_STATUS_INVALID_JAVA_CLASS;
        goto Exit;
    }

    midGetAPKName= env->GetStaticMethodID(classMyStub,
				METHOD_GET_VOUCHER_PATH,SIG_GET_VOUCHER_PATH);
    if(expFlag=env->ExceptionOccurred()){
        env->ExceptionClear();
        JACDebug(env, JCAModule2, func,(char *) "Failed to get method, %s\n",
                                         METHOD_GET_VOUCHER_PATH);
        status = ACCESS_STATUS_INVALID_JAVA_METHOD;
        goto Exit;
    }

    jstrName = (jstring)env->CallStaticObjectMethod(classMyStub,midGetAPKName);
    if((expFlag=env->ExceptionOccurred()) || jstrName == NULL ){
        env->ExceptionClear();
        JACDebug(env, JCAModule2, func,(char *)"Failed to call, %s\n",
                                	METHOD_GET_VOUCHER_PATH);
        status = ACCESS_STATUS_INVALID_JAVA_METHOD;
        goto Exit;
    }

    jbyteName = (jbyte *) env->GetStringUTFChars(jstrName,NULL);
#ifdef _JAC_STANDALONE
    if(strcmp((char *)jbyteName, "null") == 0) {
	    status = ACCESS_STATUS_INVALID_VOUCHER_PATH;
    }
    ac_sprintf(voucherPath, "%s",jbyteName);
#else
    ac_sprintf(voucherPath, "%s/%s",VOUCHER_PATH_DEFAULT,VOUCHER_NAME);
#endif
    JACDebug(env, JCAModule2, func,(char *)"Voucher path: %s\n",voucherPath);

Exit:
    if (jstrName && jbyteName) {
        env->ReleaseStringUTFChars(jstrName, (const char *)jbyteName);
    }

    if (jstrName) {
        env->DeleteLocalRef(jstrName);
    }

    if (classMyStub) {
        env->DeleteLocalRef(classMyStub);
    }

    if (expFlag) {
        env->DeleteLocalRef(expFlag);
    }

    return status; 
}

/***************************************************************************

   The function is to identify the base for our secure store. The data only
   needs to be instantiated once due to its cost to call Java routine. 

***************************************************************************/
ACCESS_STATUS getStorageBase(JNIEnv *env, char *path)
{
    ACCESS_STATUS status = ACCESS_STATUS_SUCCESS;
    char func[] = "getStorageBase";

    jclass classMyStub = NULL;
    jmethodID midGetAssetDir = NULL;
    jstring jstrName = NULL;
    jbyte *jbyteName = NULL;
    jthrowable expFlag = NULL;


    pthread_mutex_lock(&storageLock);

    if(env == NULL) {
        status = ACCESS_STATUS_INVALID_JNI_ENV;
        goto Exit;
    }

    if(ac_STRLEN(gStorageDir) >  0){
        ac_sprintf(path, "%s", gStorageDir);
        goto Exit;
    }

    classMyStub = env->FindClass(CLASSNAME_MYSTUB);
    if(expFlag=env->ExceptionOccurred()){
        env->ExceptionClear();
        status = ACCESS_STATUS_INVALID_JAVA_CLASS;
        goto Exit;
    }

    midGetAssetDir = env->GetStaticMethodID(classMyStub,
                                METHOD_GET_ASSET_DIR,SIG_GET_ASSET_DIR);
    if(expFlag=env->ExceptionOccurred()){
        env->ExceptionClear();
        JACDebugWarning(env, JCAModule2, func,(char *) "Failed to get method, %s\n",
                                         METHOD_GET_ASSET_DIR);
        status = ACCESS_STATUS_INVALID_JAVA_METHOD;
        goto Exit;
    }

    jstrName = (jstring)env->CallStaticObjectMethod(classMyStub,midGetAssetDir);
    if((expFlag=env->ExceptionOccurred()) || jstrName == NULL ){
        env->ExceptionClear();
        JACDebugWarning(env, JCAModule2, func,(char *)"Failed to call, %s\n",
                                        METHOD_GET_ASSET_DIR);
        status = ACCESS_STATUS_INVALID_JAVA_METHOD;
    }

    jbyteName = (jbyte *) env->GetStringUTFChars(jstrName,NULL);
    if(strcmp((char *)jbyteName, "null") == 0) {
        status = ACCESS_STATUS_INVALID_STORAGE_BASE;
    }

    ac_sprintf(path, "%s",jbyteName);
    JACDebug(env, JCAModule2, func,(char *)" path: %s\n",path);

Exit:
    if (jstrName && jbyteName) {
        env->ReleaseStringUTFChars(jstrName, (const char *)jbyteName);
    }

    if (jstrName) {
        env->DeleteLocalRef(jstrName);
    }

    if (classMyStub) {
        env->DeleteLocalRef(classMyStub);
    }

    if (expFlag) {
        env->DeleteLocalRef(expFlag);
    }

    pthread_mutex_unlock(&storageLock);

    return status;
}

ACCESS_STATUS uncompressSecureData(JNIEnv *env, ac_uint8 **ppSecureData, ac_uint32 *pDataLen)
{    
    ACCESS_STATUS status = ACCESS_STATUS_SUCCESS;
    int iRet = 0;
    char func[] = "uncompressSecureData";
    ac_uint8 *pDestBuf = NULL;
    unsigned long destDataLen = 1024*1024*2;

    
    int bufferErrorCount = 1;

	pDestBuf= (ac_uint8 *)ac_calloc(destDataLen, 1);

	if(pDestBuf == NULL) {
		return ACCESS_STATUS_MEMORY_ALLOCATION_FAILED;
	}

	iRet = uncompress(pDestBuf, &destDataLen, *ppSecureData, (unsigned long)(*pDataLen));

    while(iRet == Z_BUF_ERROR && bufferErrorCount<3)
    {
	    bufferErrorCount++;
	    destDataLen = 2*destDataLen;
        pDestBuf = (ac_uint8 *)realloc(pDestBuf, destDataLen);
	    if (pDestBuf != NULL) {
            iRet = uncompress(pDestBuf, &destDataLen, *ppSecureData, (unsigned long)(*pDataLen));
	    } else {
	        status = ACCESS_STATUS_MEMORY_ALLOCATION_FAILED;
	        break;
	    }
	    DBGWRAP(JACDebugWarning(env, JCAModule2, func,(char *)"uncompress again, the result = %d, the dest data len = %ld, the source data len = %d \n",iRet, destDataLen, *pDataLen));
    }
    
    if(0 != iRet || ACCESS_STATUS_SUCCESS != status)
    {
        ac_free(*ppSecureData);
        *ppSecureData = NULL;
        *pDataLen = 0;
        ac_free(pDestBuf);
        status = ACCESS_STATUS_GENERIC_ERROR;
        DBGWRAP(JACDebugWarning(env, JCAModule2, func,(char *)"uncompress secure data failed"));
	} else {
        ac_free(*ppSecureData);
        *ppSecureData = pDestBuf;
        *pDataLen = (ac_uint32)destDataLen;   
    }
    return status;
}

#endif //NOT _JAC_SIGNING
