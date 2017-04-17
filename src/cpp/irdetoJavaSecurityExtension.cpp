#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "iso98wrap.h"
#include "irdetoJavaSecurityExtension.h"
#include "JACCommonModule.h"
#include "dexAdaptor.h"
#include "antiDebug.h"

static ac_Context gContext = NULL;
static ac_SS_Context gSSJacDataContext = NULL;
static ac_SS_Context gSSJacVoucherContext = NULL;
static JAVAArchive *gpJavaArchive= NULL;
static JACConfig *gpJACConfig= NULL;
static int isExtCtx = 0;

static ac_uint8 VOUCHER_ID[] = "PPOJUJ";
static ac_uint8 HMAC_HANDLE_ID[] = "YYT76H";
static ac_uint8 JAVA_CONFIG_HANDLE_ID[] = "JACConfigHandle";
static ac_uint8 JAVA_ARCHIVE_TOKEN[] = "java_archive_id";
static ac_uint8 JAVA_INDEX_TOKEN[] = "java_index_id";
static ac_uint8 JAVA_BYTECODE_TOKEN[] = "java_bytecode_id";
static ac_uint8 JAVA_OPT_BYTECODE_TOKEN[] = "use_odex";
static ac_uint8 NATIVE_LIB_TOKEN[] = "native_lib_dir";
static ac_uint8 OPT_MODE_TOKEN[] = "operation_mode";
static ac_uint8 HMAC_HANDLE_TOKEN[] = "hmacsha_handle";
static ac_uint8 APP_THREAD_TOKEN[] = "app_iv_policy";
static ac_uint8 ENABLE_ADBG_TOKEN[] = "enable_java_adbg";
static ac_uint8 DISABLE_STATIC_IV_TOKEN[] = "disable_static_iv";
char JCAModule3[]="irdetoJavaSecurityExtension.cpp";

static pthread_mutex_t iacContextLocker = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t iacConfigLocker = PTHREAD_MUTEX_INITIALIZER;

#define FURTHER_STATUS_CHECK(myStatus)    if(myStatus != AC_ERROR_JB_DETECTED_LEVEL_ONE && myStatus != AC_ERROR_JB_DETECTED_LEVEL_TWO && myStatus !=  AC_ERROR_JB_DETECTED_LEVEL_THREE){JACDebugWarning(env, JCAModule3, "FURTHER_STATUS_CHECK", (char *)"Problem, return code: 0x%x\n", myStatus); return myStatus;}

#define FURTHER_STATUS_CHECK_MUTEX(myStatus)    if(myStatus != AC_ERROR_JB_DETECTED_LEVEL_ONE && myStatus != AC_ERROR_JB_DETECTED_LEVEL_TWO && myStatus !=  AC_ERROR_JB_DETECTED_LEVEL_THREE){JACDebugWarning(env, JCAModule3, "FURTHER_STATUS_CHECK_MUTEX", (char *)"Problem, return code: 0x%x\n", myStatus);pthread_mutex_unlock(&iacContextLocker); return myStatus;}

static ac_Status getUsefulACStatus(ac_Status myStatus)
{
    if(myStatus != AC_ERROR_JB_DETECTED_LEVEL_ONE && 
       myStatus != AC_ERROR_JB_DETECTED_LEVEL_TWO && 
       myStatus !=  AC_ERROR_JB_DETECTED_LEVEL_THREE){
    	return myStatus;
    }else{	
    	return AC_OK;     
    }
}

static void getArchieveToken(JNIEnv *env, ac_uint8 *archiveToken)
{
    char value[SYSTEM_PROPERTY_LEN];
    char nameSDK[] = "ro.build.version.sdk";
    char func[]="getArchieveToken";

    __system_property_get(nameSDK, value);
    sprintf((char *)archiveToken,"%s_%s",JAVA_OPT_BYTECODE_TOKEN,value);
    JACDebug(env,JCAModule3,func,(char*)"token: %s\n",archiveToken);

}

/*****************************************************************************

  Parse configuration data from secure store for Java archives.

*****************************************************************************/
static void parseJavaConfig(JNIEnv *env, ac_uint8 **configItems, ac_uint32 nElements)
{
    ac_uint8 *tmpStr;
    ac_uint32 count = 0;
    ac_uint8 preserveBuffer[READ_LINE_LEN];
    ac_uint8 realOptBytecodeToken[HANDLE_ID_LEN];
    char func[]="parseJavaConfig";

    if(nElements < 1) return; 

    pthread_mutex_lock(&iacConfigLocker);
    gpJavaArchive = (JAVAArchive *) ac_calloc(1, sizeof(JAVAArchive));
    if(gpJavaArchive == NULL){
    	DBGWRAP(JACDebugWarning(env,JCAModule3,func,(char*)"Invalid memory allocation\n"));
    	pthread_mutex_unlock(&iacConfigLocker);
	    return;
    }
    getArchieveToken(env,realOptBytecodeToken); 
    gpJavaArchive->archiveId=
		(ac_uint8 **)ac_calloc(nElements, sizeof(ac_uint8 *));
    if(gpJavaArchive->archiveId == NULL){
    	DBGWRAP(JACDebugWarning(env,JCAModule3,func,(char*)"Invalid memory allocation\n"));
    	pthread_mutex_unlock(&iacConfigLocker);
	    return;
    }
    gpJACConfig = (JACConfig *) ac_calloc(1, sizeof(JACConfig));
    if(gpJACConfig == NULL){
        DBGWRAP(JACDebugWarning(env,JCAModule3,func,(char*)"Invalid memory allocation\n"));
        pthread_mutex_unlock(&iacConfigLocker);
        return;
    }
    for (int pos = 0; pos < nElements; pos++){
	    memcpy(preserveBuffer, configItems[pos], READ_LINE_LEN);
    	if((tmpStr = 
	     (ac_uint8 *)strtok((char *)preserveBuffer," \t\n")) == NULL) 
	        continue;	
	    if(strcmp((char *)tmpStr, (char *)JAVA_ARCHIVE_TOKEN) == 0){
	        if((tmpStr = (ac_uint8 *)strtok(NULL," \t\n")) == NULL)
	    	    continue;
	        gpJavaArchive->archiveId[count] =
			(ac_uint8 *)ac_calloc(READ_LINE_LEN, sizeof(ac_uint8));
    	    if(gpJavaArchive->archiveId[count] == NULL){
           	    DBGWRAP(JACDebugWarning(env,JCAModule3,func,(char*)"Invalid memory allocation\n"));
        	    pthread_mutex_unlock(&iacConfigLocker);
        	    return;
	        }
	        memcpy(gpJavaArchive->archiveId[count], 
					tmpStr, ac_STRLEN((char *)tmpStr));
	        count++;
            JACDebug(env,JCAModule3,func,(char*)"Found handle: %s\n",tmpStr);
    	}else if (strcmp((char *)tmpStr, (char *)NATIVE_LIB_TOKEN) == 0){
    	    if((tmpStr = (ac_uint8 *)strtok(NULL," \t\n")) == NULL)
                    continue;
    	    snprintf((char *)gpJACConfig->nativeLibDir,FILE_PATH_LEN,"%s",tmpStr);
    	}else if(strcmp((char *)tmpStr, (char *)JAVA_INDEX_TOKEN) == 0) {
    	    if((tmpStr = (ac_uint8 *)strtok(NULL," \t\n")) == NULL)
                    continue;
    	    snprintf((char *)gpJavaArchive->indexId,HANDLE_ID_LEN,"%s",tmpStr);
                JACDebug(env,JCAModule3,func,(char*)"Found handle: %s\n",tmpStr);
    	}else if(strcmp((char *)tmpStr, (char *)JAVA_BYTECODE_TOKEN) == 0) {
    	    if((tmpStr = (ac_uint8 *)strtok(NULL," \t\n")) == NULL)
                    continue;
    	    snprintf((char *)gpJavaArchive->byteCodeId,HANDLE_ID_LEN,"%s",tmpStr);
                JACDebug(env,JCAModule3,func,(char*)"Found handle: %s\n",tmpStr);
    	}else if(strcmp((char *)tmpStr, (char *)realOptBytecodeToken) == 0) {
    	    if((tmpStr = (ac_uint8 *)strtok(NULL," \t\n")) == NULL)
                    continue;
    	    gpJACConfig->optDex = atoi((char *)tmpStr);
                JACDebug(env,JCAModule3,func,(char*)"Opt indicator: %s\n",tmpStr);
      	}else if(strcmp((char *)tmpStr, (char *)APP_THREAD_TOKEN) == 0) {
                if((tmpStr = (ac_uint8 *)strtok(NULL," \t\n")) == NULL)
                    continue;
                gpJACConfig->appThread = atoi((char *)tmpStr);
                JACDebug(env,JCAModule3,func,(char*)"Thread token: %s\n",tmpStr);
      	}else if(strcmp((char *)tmpStr, (char *)ENABLE_ADBG_TOKEN) == 0) {
    	    if((tmpStr = (ac_uint8 *)strtok(NULL," \t\n")) == NULL)
                    continue;
    	    gpJACConfig->enableAdbg = atoi((char *)tmpStr);
            JACDebug(env,JCAModule3,func,(char*)"java adbg token: %s\n",tmpStr);
        }else if(strcmp((char *)tmpStr, (char *)HMAC_HANDLE_TOKEN) == 0){
            if((tmpStr = (ac_uint8 *)strtok(NULL," \t\n")) == NULL)
                continue;
            snprintf((char *)gpJACConfig->hmacShaHandle,HANDLE_ID_LEN,"%s",tmpStr);
        }else if(strcmp((char *)tmpStr, (char *)DISABLE_STATIC_IV_TOKEN) == 0){
            if((tmpStr = (ac_uint8 *)strtok(NULL," \t\n")) == NULL) continue;
            gpJACConfig->disableStaticIV = atoi((char *)tmpStr);
            JACDebug(env,JCAModule3,func,(char*)"static IV token: %s\n",tmpStr);
        }
    }
    
    gpJavaArchive->nItems = count;
    if(count > 0){
    	gpJavaArchive->archiveId = (ac_uint8 **)realloc(
			gpJavaArchive->archiveId, count*sizeof(ac_uint8 *));
    	if(gpJavaArchive->archiveId == NULL){
    	    DBGWRAP(JACDebugWarning(env,JCAModule3,func,(char*)"Invalid memory allocation\n"));
    	}
    }
    pthread_mutex_unlock(&iacConfigLocker);
}


static ac_Status getDataFromHandle(JNIEnv *env, 
                    ac_SS_Context *pSSContext,
				    ac_uint8 *handleId,
    				ac_uint8 **outBuf,
				    ac_uint32 *bufLength) 
{
    ac_SS_Data_Handle myHandle = 0;
    ac_Status status;
    AntiDebugData adbg;
    AntiDebugData adbgIntercon;
    char func[] = "getDataFromHandle";

    JACDebug(env,JCAModule3,func,(char*)"get data from handle enter,handle id = %s\n", handleId);
    init2ADbg(env, &adbg, V_DELTA_2);
    if((EXTRACT_AC_ERROR(status=ac_GetHandleByID(*pSSContext, handleId,
                  (ac_uint32) ac_STRLEN((char *)handleId), &myHandle))) !=AC_OK){
		FURTHER_STATUS_CHECK(EXTRACT_AC_ERROR(status));
    }
    DBGWRAP(JACDebug(env,JCAModule3,func,(char*)"get handle by id time check\n"));
    init2ADbg(env, &adbgIntercon, V_DELTA_2);
    markAndVerifyADbg(env, &adbg, func, __LINE__);
    status = ac_GetDataLengthFromHandle(*pSSContext, myHandle, bufLength);
    if ((status = EXTRACT_AC_ERROR(status)) != AC_OK) {
    	return status;
    }
    DBGWRAP(JACDebug(env,JCAModule3,func,(char*)"get data length from handle time check\n"));    
    init2ADbg(env, &adbg, V_DELTA_15);
    markAndVerifyADbg(env, &adbgIntercon, func, __LINE__);
    *outBuf = (ac_uint8 *) ac_malloc(*bufLength);
    status = ac_GetDataFromHandleNoAlloc(*pSSContext, myHandle, *outBuf, bufLength);
    if(myHandle == 0 || *outBuf == NULL) {
    	DBGWRAP(JACDebugWarning(env,JCAModule3,func,(char*)"Invalid data from CAT\n"));
	    status = AC_FAIL;
    }
    
    status = EXTRACT_AC_ERROR(status);
    JACDebug(env,JCAModule3,func,(char*)"get data from handle time check and leave, status = %d\n", status);
    markAndVerifyADbg(env, &adbg, func, __LINE__);
    
    return status;
}

static void getElements(JNIEnv *env, 
		 ac_uint8 *input, 
		 ac_uint32 inLen, 
         	 ac_uint8 **retArray,
		 ac_uint32 *nElem)
{
    ac_uint8 *tmpPtr;
    ac_uint8 *tmpBuf = NULL;
    ac_uint32 retElems = 0;
    char func[] ="getElements";

    tmpBuf = (ac_uint8 *) ac_calloc(inLen + 1, sizeof(ac_uint8));
    snprintf((char *)tmpBuf, inLen + 1, "%s", (char *)input);
    tmpPtr = (ac_uint8*)strtok((char *)tmpBuf,(char *)"\n\xC\xD\x3");
    do {
        if(tmpPtr == NULL) break;
        if(ac_STRLEN((char *) tmpPtr) < 1 || 
		tmpPtr[0] < 32 || tmpPtr[0] > 125) continue;
        if(retArray != NULL){
            retArray[retElems] = (ac_uint8 *)ac_calloc(READ_LINE_LEN, sizeof(ac_uint8));
   	        if(retArray[retElems] == NULL){
    	    	DBGWRAP(JACDebugWarning(env,JCAModule3,func,(char*)"Invalid memory allocation\n"));
		        if(tmpBuf != NULL) 
		            ac_free(tmpBuf);
	    	    return;
	        }
            snprintf((char *)retArray[retElems], READ_LINE_LEN,"%s", (char*) tmpPtr);
        }
        retElems++;
    } while((tmpPtr = (ac_uint8*)strtok(NULL,(char *)"\n\xC\xD\x3"))!= NULL);

    if(tmpBuf != NULL) 
    	ac_free(tmpBuf);
    *nElem = retElems;
}

static void parseDataFromCAT(JNIEnv *env,
			     ac_uint8 *input,
			     ac_uint32 inputLen,
                             ac_uint8 ***retItem,
                             ac_uint32 *nElements)
{
    ac_uint8 **tmpBuf;
    ac_uint32 myElemLen;
    char func[] = "parseDataFromCAT";
    DBGWRAP(JACDebug(env,JCAModule3,func,(char*)"function enter.... \n"));
    
    getElements(env, input, inputLen, NULL, &myElemLen);
    DBGWRAP(JACDebug(env,JCAModule3,func,(char*)"parse data from cat time1.... \n"));
    tmpBuf = (ac_uint8 **) ac_malloc(myElemLen*sizeof(ac_uint8 *));
    if(tmpBuf == NULL){
   	    DBGWRAP(JACDebugWarning(env,JCAModule3,func,(char*)"Invalid memory allocation\n"));
    	return;
    }
    getElements(env, input, inputLen, tmpBuf ,&myElemLen);
    *retItem = tmpBuf;
    *nElements = myElemLen;
    DBGWRAP(JACDebug(env,JCAModule3,func,(char*)"parse data from cat time2.... \n"));
}
static void testSetContext(JNIEnv *env)
{
    char func[] = "testSetContext";
    ac_Context context = NULL;
    ACCESS_STATUS status;
#ifdef _JAC_SIGNING
    ac_char storePath[] = "/data/app-private/local/jac_store.dat";
#else
    ac_char storePath[] = "/data/data/com.irdeto.security/files/jac_store.dat";
#endif

    if(gContext != NULL) return;
    if((EXTRACT_AC_ERROR(ac_Initialize(&context, storePath, NULL))) != AC_OK){
    	DBGWRAP(JACDebugWarning(env,JCAModule3,func,(char*)"Invalid AC context\n"));
    }
    status = setExternalContext(context);
    JACDebug(env,JCAModule3,func,(char*)"status: %d\n", status);
}
/***************************************************************************

  To initialize the AC security context. It performs once per process.

****************************************************************************/
ac_Status setIACSecurityContext(JNIEnv *env, ac_char *storePath)
{
    ac_Status status = AC_OK;
    ac_uint32 isContextExist = 0;
    ac_uint32 ivCheck2 = 8888;
    ac_char *ivCheck = NULL;
    char func[] = "setIACSecurityContext";

    if(env == NULL) return AC_ERROR_INVALID_PARAMETER;

    DBGWRAP(JACDebug(env,JCAModule3,func,(char*)"set iac security context enter....\n"));

    pthread_mutex_lock(&iacContextLocker);
    if(gContext != NULL && gSSJacVoucherContext != NULL){
    	pthread_mutex_unlock(&iacContextLocker);
    	return AC_OK;
    }

    JACDebug(env,JCAModule3,func,(char*)"ac_initiliaze begin %s\n", func);
    JACDebug(env,JCAModule3,func,(char*)"ac_initiliaze begin %s\n", storePath);

    if(gContext == NULL){
        if((EXTRACT_AC_ERROR(status = ac_Initialize(&gContext, storePath, NULL))) != AC_OK){
    	    FURTHER_STATUS_CHECK_MUTEX(EXTRACT_AC_ERROR(status));    
    	}	
        
    	if(gContext == NULL){
    	    DBGWRAP(JACDebugWarning(env,JCAModule3,func,(char*)"Invalid AC context\n"));
    	    pthread_mutex_unlock(&iacContextLocker);
	        return AC_FAIL;
    	}
    }else{
	    isContextExist = 1;
    	DBGWRAP(JACDebug(env,JCAModule3,func,(char*)"CAT Context exists\n"));
    }
    
    DBGWRAP(JACDebug(env,JCAModule3,func,(char*)"ac_initiliaze end, and load secure store begin\n"));
    status=ac_LoadSecureStore(&gSSJacVoucherContext,gContext,storePath);
    JACDebug(env,JCAModule3,func,(char*)"load secure store end..........%s\n", storePath);
    if((EXTRACT_AC_ERROR(status)) != AC_OK){
        FURTHER_STATUS_CHECK_MUTEX(EXTRACT_AC_ERROR(status));
    }
    DBGWRAP(JACDebug(env,JCAModule3,func,(char*)"on dis iv begin\n"));
#ifndef _JAC_SIGNING
    if(!isContextExist){
        ivCheck = (ac_char *) ac_malloc(10);
        strcpy((char *)ivCheck, "1234567");
        status = ac_IV_VerifySystem(gSSJacVoucherContext, &ivCheck, &ivCheck2);
        ac_free(ivCheck);
        JACDebug(env,JCAModule3,func,(char*)"on-disk iv end, status = %x\n",status);
    }
#endif
    pthread_mutex_unlock(&iacContextLocker);

    return(EXTRACT_AC_ERROR(status));
}

/****************************************************************************

  To retrieve Java voucher from secure store.

****************************************************************************/
ac_Status retrieveVoucherFromSecureStore(JNIEnv *env, 
					  ac_char *storePath, 
					  ac_uint8 ***voucher,
					  ac_uint32 *nElements)
{
    ac_Context context = NULL;
    ac_SS_Context ss_context = NULL;
    ac_SS_Data_Handle myHandle;
    //ac_uint8 *outBuf = NULL;
    ac_uint8 *voucherBuf = NULL;
    ac_uint32 bufLength;
    ac_Status status = AC_OK;
    char func[]= "retrieveVoucherFromSecureStore";
    JACDebugWarning(env,JCAModule3,func,(char*)"retrieveVoucherFromSecureStore %s\n", storePath);

    JACDebug(env,JCAModule3,func,(char*)"retrieveVoucherFromSecureStore  %s\n", storePath);

    if(env == NULL) return AC_ERROR_INVALID_PARAMETER;
    if((EXTRACT_AC_ERROR(status = setIACSecurityContext(env, storePath))) != AC_OK){
        return EXTRACT_AC_ERROR(status);
    }
    if((EXTRACT_AC_ERROR(status = getDataFromHandle(env,&gSSJacVoucherContext, VOUCHER_ID, 
				&voucherBuf, &bufLength))) != AC_OK){
		FURTHER_STATUS_CHECK(EXTRACT_AC_ERROR(status));    
		status = AC_OK;
    }

    parseDataFromCAT(env, voucherBuf, bufLength, voucher, nElements);
    JACDebug(env,JCAModule3,func,(char*)"voucher length: %d\n",bufLength);
    ac_free(voucherBuf);
    
	status = EXTRACT_AC_ERROR(status);
	return status;
}

/****************************************************************************

  To compute HmacSha256 signature using AC algorithm.

****************************************************************************/

ac_Status getHmacSha256ByHandle(JNIEnv *env, ac_uint8 *data, ac_uint32 dataLen, ac_char *storePath, ac_uint8 *digest)
{
    ac_Status status;
    ac_uint8 hmacHandlId[HANDLE_ID_LEN];
    ac_Op_Context pOperationContext = NULL;
    ac_SS_Data_Handle myHandle = 0;  //it is size_t
    ac_uint8 *outBuf = NULL;
    ac_uint32 bufLength = 0;
    char func[] = "getHmacSha256ByHandle";

    if(env == NULL) return AC_ERROR_INVALID_PARAMETER;
    if((EXTRACT_AC_ERROR(status = setIACSecurityContext(env, storePath))) != AC_OK){
	    return EXTRACT_AC_ERROR(status);    
    }
    pthread_mutex_lock(&iacContextLocker);

    JACDebug(env,JCAModule3,func,(char*)"getHmacSha256ByHandle  %s\n", func);


    if((EXTRACT_AC_ERROR(status = ac_GetHandleByID(gSSJacVoucherContext, HMAC_HANDLE_ID,
                  (ac_uint32) ac_STRLEN((char *)HMAC_HANDLE_ID), &myHandle))) != AC_OK)
    {
        FURTHER_STATUS_CHECK_MUTEX(EXTRACT_AC_ERROR(status)); 
    }
    
    if(myHandle == 0) {
    	DBGWRAP(JACDebugWarning(env,JCAModule3,func,(char*)"Invalid data from CAT\n"));
        pthread_mutex_unlock(&iacContextLocker);
	    return AC_FAIL;
    }

    if((EXTRACT_AC_ERROR(status = ac_HMAC_Init_From_Store(gSSJacVoucherContext,
                                    AC_HASH_SHA256,
                                    myHandle,
                                    &pOperationContext))) != AC_OK){
	    FURTHER_STATUS_CHECK_MUTEX(EXTRACT_AC_ERROR(status));    
    }

    if((EXTRACT_AC_ERROR(status = ac_HMAC_Update(gSSJacVoucherContext, pOperationContext, data, dataLen)))
                != AC_OK){
	    FURTHER_STATUS_CHECK_MUTEX(EXTRACT_AC_ERROR(status));    
    }

    if((EXTRACT_AC_ERROR(status = ac_HMAC_Finalize(gSSJacVoucherContext, pOperationContext, digest)))
                != AC_OK){
	    FURTHER_STATUS_CHECK_MUTEX(EXTRACT_AC_ERROR(status));    
    }
    pthread_mutex_unlock(&iacContextLocker);

    return(EXTRACT_AC_ERROR(status));
}


ac_Status getHmacSha256Init(JNIEnv *env, ac_char *storePath, ac_Op_Context *pOperationContext)
{
    ac_Status status;
    ac_uint8 hmacHandlId[HANDLE_ID_LEN];
    ac_SS_Data_Handle myHandle = 0;  //it is size_t
    ac_uint8 *outBuf = NULL;
    ac_uint32 bufLength = 0;
    char func[] = "getHmacSha256ByHandle";

    if(env == NULL) return AC_ERROR_INVALID_PARAMETER;
    if((EXTRACT_AC_ERROR(status = setIACSecurityContext(env, storePath))) != AC_OK){
        return EXTRACT_AC_ERROR(status);
    }

    JACDebug(env,JCAModule3,func,(char*)"getHmacSha256Init  %s\n", func);

    if((EXTRACT_AC_ERROR(status = ac_GetHandleByID(gSSJacVoucherContext, HMAC_HANDLE_ID,
                  (ac_uint32) ac_STRLEN((char *)HMAC_HANDLE_ID), &myHandle))) != AC_OK)
    {
        FURTHER_STATUS_CHECK_MUTEX(EXTRACT_AC_ERROR(status)); 
    }
    
    if(myHandle == 0) {
        DBGWRAP(JACDebugWarning(env,JCAModule3,func,(char*)"Invalid data from CAT\n"));
        status = AC_FAIL;
    }
    if((EXTRACT_AC_ERROR(status =  ac_HMAC_Init_From_Store(gSSJacVoucherContext,
                                    AC_HASH_SHA256,
                                    myHandle,
                                    pOperationContext))) != AC_OK){
        FURTHER_STATUS_CHECK(EXTRACT_AC_ERROR(status));
    }

    status = EXTRACT_AC_ERROR(status);

    return status;
}


ac_Status getHmacSha256Update(JNIEnv *env, ac_uint8 *data, ac_uint32 dataLen, ac_Op_Context pOperationContext)
{
    ac_Status status;
    char func[] = "getHmacSha256Update";

    if((EXTRACT_AC_ERROR(status = ac_HMAC_Update(gSSJacVoucherContext, pOperationContext, data, dataLen)))
                != AC_OK){
        FURTHER_STATUS_CHECK(EXTRACT_AC_ERROR(status));
    }
    status = EXTRACT_AC_ERROR(status);

    return status;
}


ac_Status getHmacSha256Finalize(JNIEnv *env, ac_Op_Context pOperationContext, ac_uint8 *digest)
{
    ac_Status status;
    char func[] = "getHmacSha256Finalize";

    DBGWRAP(JACDebugWarning(env,JCAModule3,func,(char*)"ac_HMAC_Finalize\n"));

    if((EXTRACT_AC_ERROR(status = ac_HMAC_Finalize(gSSJacVoucherContext, pOperationContext, digest))) != AC_OK){
        FURTHER_STATUS_CHECK(EXTRACT_AC_ERROR(status));
    }
    DBGWRAP(JACDebugWarning(env,JCAModule3,func,(char*)"Going out from ac_HMAC_Finalize\n"));
    status = EXTRACT_AC_ERROR(status);

    return status;
}


ac_Status setJavaConfig(JNIEnv *env, ac_char *storePath)
{
    ac_uint8 *outBuf = NULL;
    ac_uint32 bufLength;
    ac_Status status = AC_OK;
    ac_uint8 *configBuf = NULL;
    ac_uint8 **configItems = NULL;
    ac_uint32 nElements;
    char func[] = "setJavaConfig";

    DBGWRAP(JACDebug(env,JCAModule3,func,(char*)"starting...\n"));

    if(env == NULL) return AC_ERROR_INVALID_PARAMETER;
    
    if(gpJavaArchive != NULL && gpJACConfig != NULL) return AC_OK;//already set

    if((EXTRACT_AC_ERROR(status = setIACSecurityContext(env, storePath))) != AC_OK){
        return EXTRACT_AC_ERROR(status);
    }

    if((EXTRACT_AC_ERROR(status = getDataFromHandle(env,&gSSJacVoucherContext, JAVA_CONFIG_HANDLE_ID, 
				&outBuf, &bufLength))) != AC_OK){
        FURTHER_STATUS_CHECK(EXTRACT_AC_ERROR(status));    
        status = AC_OK;
    }

    DBGWRAP(JACDebug(env,JCAModule3,func,
	(char*)"store path: %s,buffer size: %d\n",(char *)storePath,bufLength));
    configBuf = (ac_uint8 *) ac_calloc(bufLength + 1, sizeof(ac_uint8)); 
    if(configBuf == NULL){
    	DBGWRAP(JACDebugWarning(env,JCAModule3,func,(char*)"Invalid memory allocation\n"));
        return AC_ERROR_HEAP_ALLOCATION_FAILED;
    }

    memcpy(configBuf, outBuf, bufLength);
    parseDataFromCAT(env, configBuf, bufLength, &configItems, &nElements);
    parseJavaConfig(env, configItems, nElements);
    ac_free(configBuf);
    freeElementMemory(configItems, nElements);

    return(EXTRACT_AC_ERROR(status));
}

ac_Status setJACConfiguration(JNIEnv *env, 
			      ac_char *storePath, 
			      JACConfig **pJacConfig)
{
    ac_Status status = AC_OK;
    ac_uint32 length;
    ac_uint8 *handleId;
    ac_uint8 *outBuf = NULL;
    char func[] ="setJACConfiguration";

    DBGWRAP(JACDebug(env,JCAModule3,func,(char*)"starting...\n"));
    if(env == NULL) return AC_ERROR_INVALID_PARAMETER;
    if((EXTRACT_AC_ERROR(status = setJavaConfig(env, storePath))) != AC_OK){
        return EXTRACT_AC_ERROR(status);
    }
    *pJacConfig = gpJACConfig;
    DBGWRAP(JACDebug(env,JCAModule3,func,(char*)"Good config data\n"));

    return EXTRACT_AC_ERROR(status);
}

/***************************************************************************

  This function should be called at very begining to initialize Java context
  from the secure store.

****************************************************************************/
ac_Status getJavaDataFromSecureStore(JNIEnv *env, 
                      ac_char *pStorePath,
				      JAVAArchive **pJavaArchive,
				      JACConfig **pJacConfig)
{
    ac_Status status = AC_OK;
    ACCESS_STATUS jacStatus = ACCESS_STATUS_SUCCESS;
    ac_uint32 length;
    ac_uint8 *handleId;
    ac_uint8 *outBuf = NULL;
    AntiDebugData adbg;
    AntiDebugData adbgIntercon;
    char func[] ="getJavaDataFromSecureStore";
    ac_SS_Context tmpSSContext = NULL;
    ac_Context iacContext = NULL;

    init2ADbg(env, &adbg, V_DELTA_1);
    DBGWRAP(JACDebug(env,JCAModule3,func,(char*)"getJavaDataFromSecureStore\n"));
    init2ADbg(env, &adbgIntercon, V_DELTA_5);
    markAndVerifyADbg(env, &adbg, func, __LINE__);

    if(gpJavaArchive == NULL || gpJavaArchive->nItems == 0) return AC_FAIL;

    init2ADbg(env, &adbg, V_DELTA_15);
    gpJavaArchive->archiveData = 
	(ac_Bytes *) ac_calloc(gpJavaArchive->nItems, sizeof(ac_Bytes));

    if(gpJavaArchive->archiveData == NULL){
   	    DBGWRAP(JACDebugWarning(env,JCAModule3,func,(char*)"Invalid memory allocation\n"));
    	return AC_ERROR_HEAP_ALLOCATION_FAILED;
    }

    if (EXTRACT_AC_ERROR(status = ac_LoadSecureStore(&gSSJacDataContext, gContext, pStorePath)) != AC_OK)
    {
        DBGWRAP(JACDebugWarning(env,JCAModule3,func,(char*)"load java data secure store faild\n"));
	    FURTHER_STATUS_CHECK(EXTRACT_AC_ERROR(status));
    }
    
    markAndVerifyADbg(env, &adbgIntercon, func, __LINE__);

    for(int pos = 0; pos < gpJavaArchive->nItems; pos++){
	    outBuf = NULL;
	    handleId = gpJavaArchive->archiveId[pos];
        if((EXTRACT_AC_ERROR(status = 
		    getDataFromHandle(env, &gSSJacDataContext, handleId, &outBuf, &length))) != AC_OK){
	        FURTHER_STATUS_CHECK(EXTRACT_AC_ERROR(status));
        }
        
        gpJavaArchive->archiveData[pos].bytes = outBuf;
        gpJavaArchive->archiveData[pos].length = length;
        DBGWRAP(JACDebug(env,JCAModule3,func,(char*)"Data handle: %s, data length: %d\n", handleId, length));
    }
    init2ADbg(env, &adbgIntercon, V_DELTA_15);
    markAndVerifyADbg(env, &adbg, func, __LINE__);
    outBuf = NULL;
    if((EXTRACT_AC_ERROR(status = getDataFromHandle(env,  &gSSJacDataContext,
					                    gpJavaArchive->indexId,
                                        &outBuf, &length))) != AC_OK){
	    FURTHER_STATUS_CHECK(EXTRACT_AC_ERROR(status));
    }

#ifndef SECURE_DATA_NO_COMPRESS
#ifndef _JAC_SIGNING
    if((jacStatus= uncompressSecureData(env, &outBuf, &length)) != ACCESS_STATUS_SUCCESS)
    {
        FURTHER_STATUS_CHECK(AC_FAIL);
    }    
#endif
#endif

    DBGWRAP(JACDebug(env,JCAModule3,func,(char*)"Data handle: %s, data length: %d\n", gpJavaArchive->indexId, length));
    gpJavaArchive->indexData = (ac_Bytes *) ac_calloc(1, sizeof(ac_Bytes));
    gpJavaArchive->indexData->bytes = outBuf;
    gpJavaArchive->indexData->length = length;
    outBuf = NULL;
    init2ADbg(env, &adbg, V_DELTA_15);
    markAndVerifyADbg(env, &adbgIntercon, func, __LINE__);
    if((EXTRACT_AC_ERROR(status = getDataFromHandle(env, 
                                        &gSSJacDataContext,
					                    gpJavaArchive->byteCodeId,
                                        &outBuf, &length))) != AC_OK){
      	FURTHER_STATUS_CHECK(EXTRACT_AC_ERROR(status));
    }

#ifndef SECURE_DATA_NO_COMPRESS
#ifndef _JAC_SIGNING
    if((jacStatus = uncompressSecureData(env, &outBuf, &length)) != ACCESS_STATUS_SUCCESS)
    {
        FURTHER_STATUS_CHECK(AC_FAIL);
    }    
#endif
#endif

    init2ADbg(env, &adbgIntercon, V_DELTA_1);
    markAndVerifyADbg(env, &adbg, func, __LINE__);
    DBGWRAP(JACDebug(env,JCAModule3,func,(char*)"Data handle: %s, data length: %d\n", gpJavaArchive->byteCodeId, length));
    gpJavaArchive->byteCodeData = (ac_Bytes *) ac_calloc(1, sizeof(ac_Bytes));
    gpJavaArchive->byteCodeData->bytes = outBuf;
    init2ADbg(env,&adbg, V_DELTA_1);
    markAndVerifyADbg(env, &adbgIntercon, func, __LINE__);
    gpJavaArchive->byteCodeData->length = length;
    *pJavaArchive = gpJavaArchive;
    *pJacConfig = gpJACConfig;
    markAndVerifyADbg(env, &adbg, func, __LINE__);
    
    return AC_OK;
}

/***************************************************************************

   To perform memory cleanup including ac_Shutdown

****************************************************************************/
ac_Status shutdownJAC_IAC(JNIEnv *env)
{
    ac_Status status = AC_OK;
    char func[]="shutdownJAC_IAC";

    if(env == NULL) return AC_ERROR_INVALID_PARAMETER;

    if((EXTRACT_AC_ERROR(status = ac_SS_Shutdown(&gSSJacVoucherContext))) != AC_OK) return EXTRACT_AC_ERROR(status);

    gSSJacVoucherContext = NULL;
    if(!isExtCtx){
    	if((EXTRACT_AC_ERROR(status = ac_Shutdown(&gContext))) != AC_OK) return EXTRACT_AC_ERROR(status);
    }

    isExtCtx = 0;
    gContext = NULL;
    if(gpJACConfig != NULL) ac_free(gpJACConfig);
    gpJACConfig = NULL;

    status = EXTRACT_AC_ERROR(status);

    return status;
}

void freeElementMemory(ac_uint8 **entity, ac_uint32 nElements)
{
    for(int pos = 0; pos < nElements; pos++){
        if(entity[pos] != NULL) ac_free (entity[pos]);
    }
    ac_free(entity);
}

ACCESS_STATUS setExternalContext(ac_Context context)
{
    if(gContext != NULL){
        return ACCESS_STATUS_IAC_CONTEXT_EXIST;
    }

    if(context == NULL){
        return ACCESS_STATUS_INVALID_IAC_CONTEXT;
    }

    pthread_mutex_lock(&iacContextLocker);
    gContext = context;
    isExtCtx = 1;
    pthread_mutex_unlock(&iacContextLocker);
    
    return ACCESS_STATUS_SUCCESS;
}

ACCESS_STATUS exportContext(ac_Context *context, ac_SS_Context *sContext)
{
    if(gContext == NULL ||  gSSJacVoucherContext == NULL)
        return ACCESS_STATUS_IAC_CONTEXT_NOT_READY;

    *context = gContext;
    *sContext = gSSJacVoucherContext;

    return ACCESS_STATUS_SUCCESS;
}

