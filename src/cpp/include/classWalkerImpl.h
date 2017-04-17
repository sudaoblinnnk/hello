#ifndef CLASS_WALKER_IMPL_H
#define CLASS_WALKER_IMPL_H

#include "dexOptimize.h"
#include "ac_Stdlib_Internal.h"


static char JACModule4[] ="classWalker.cpp";

#ifdef __cplusplus__
extern "C" {
#endif

static inline const char* dexGetStringData(JNIEnv* env,const DexFile* pDexFile, const DexStringId* pStringId)
{
    const u1* ptr = (const u1*) (pDexFile->baseAddr + pStringId->stringDataOff);
	 JACDebug(env, JACModule4, "classWalker", (char*)"In dexGetStringData the ptr 0x%x\n", ptr);
    // Skip the uleb128 length.
    while (*(ptr++) > 0x7f) /* empty */ ;

    return (const char*) ptr;
}

static inline const DexClassDef* dexGetClassDef(JNIEnv* env,const DexFile* pDexFile, u4 idx) {
    assert(idx < pDexFile->pHeader->classDefsSize);
    return &pDexFile->pClassDefs[idx];
}

static inline const DexStringId* dexGetStringId(JNIEnv* env,const DexFile* pDexFile, u4 idx) {
    assert(idx < pDexFile->pHeader->stringIdsSize);
    return &pDexFile->pStringIds[idx];
}

static inline const char* dexStringById(JNIEnv* env,const DexFile* pDexFile, u4 idx) {
    const DexStringId* pStringId = dexGetStringId(env, pDexFile, idx);
	 JACDebug(env, JACModule4, "classWalker", (char*)"In dexStringById string data offset %d\n", pStringId->stringDataOff);
    return dexGetStringData(env, pDexFile, pStringId);
}

static inline const DexTypeId* dexGetTypeId(JNIEnv* env,const DexFile* pDexFile, u4 idx) {
    assert(idx < pDexFile->pHeader->typeIdsSize);
    return &pDexFile->pTypeIds[idx];
}

static inline const char* dexStringByTypeIdx(JNIEnv* env,const DexFile* pDexFile, u4 idx) {
     const DexTypeId* typeId = dexGetTypeId(env,pDexFile, idx);
 	 JACDebug(env, JACModule4, "classWalker", (char*)"In dexStringByTypeIdx descriptor id %d\n", typeId->descriptorIdx);
     return dexStringById(env, pDexFile, typeId->descriptorIdx);
}

//ACCESS_STATUS classWalker(JNIEnv* env, void *pDexFile);
//ACCESS_STATUS getCookies(JNIEnv* env, int **cookies, int length);

#ifdef __cplusplus__
}
#endif

static void repairContextClassLoader(JNIEnv *env, jobject loader)
{
    jclass classThread;
    jobject threadObject;
    jmethodID mid;

    classThread = env->FindClass(CLASSNAME_THREAD);
    mid = env->GetStaticMethodID(classThread, METHOD_CUR_THREAD,SIG_CUR_THREAD);
    threadObject = env->CallStaticObjectMethod(classThread,mid);
    mid = env->GetMethodID(classThread, METHOD_SET_CTX_LDR, SIG_GET_CTX_LDR);
    env->CallVoidMethod(threadObject, mid, loader);
}

static ACCESS_STATUS convertToDotClassName(const char *pName, char **retString)
{
    char *ptr;
    int pos = 0;
    int size = strlen(pName);
    ptr = (char *) ac_calloc(size + 1, sizeof(char));
    memcpy((char *) ptr, pName + 1, size-1);
    while (ptr[pos] != '\0'){
	if(ptr[pos] == '/'){
	    ptr[pos] = '.';
	}else if(ptr[pos] == ';'){
	    ptr[pos] = '\0';
	    break;
	}
  	pos++;
    }
    *retString = ptr;
    return ACCESS_STATUS_SUCCESS;
}

static ACCESS_STATUS convertFromDotClassName(const char *pName, char **retString)
{
    char *ptr;
    int pos = 0;
    int size = strlen(pName);
    ptr = (char *) ac_calloc(size + 3, sizeof(char));// 3 bytes for L<classname>;\0
    *ptr = 'L';
    memcpy((char *) &ptr[1], pName , size);
    while (ptr[pos] != '\0'){
		if(ptr[pos] == '.'){
			ptr[pos] = '/';
		}
		pos++;
    }
    ptr[pos] = ';';
    //ptr[pos + 1] = '\0';
    *retString = ptr;
}



ACCESS_STATUS CLASS_WALKER_NAME(JNIEnv* env, DexOperatorParam* params, int jarN)
{
    int i;
    const DexClassDef* pClassDef;
    const char* pString;
    char *pConvName;
    jmethodID mid;
    jmethodID midLoadClass;
    jclass myClass;
    jclass classDVMLoader;
    jclass classDexFile;
    jobject myLoaderObject;
    jstring jclassName;
    jobject clsObj;
    char func[]="classWalker";
    DexFile* pDexFile = (DexFile*)params->dexFiles[jarN];
    IndexReaderOutput* indexReaderOutput = &params->dexInternalParams[jarN].indexReaderOutput;

#ifdef DEX_INDEX_MAP_DECLARATION_NON_EMPTY
    DBGWRAP(JACDebug(env, JACModule4, func, (char *)"In: %s index map size %d\n", __FUNCTION__,  sizeof(pDexFile->indexMap)));
#endif


    myClass =  env->FindClass(CLASS_APP_DVM);
    mid = env->GetStaticMethodID(myClass, METHOD_GET_DVM_LDR, SIG_GET_DVM_LDR);
    myLoaderObject = env->CallStaticObjectMethod(myClass, mid);
    classDVMLoader = env->FindClass(CLASSNAME_DVMLOADER);
    midLoadClass = env->GetMethodID(classDVMLoader, METHOD_LOAD_CLASS,SIG_LOAD_CLASS);
/* Fixed classloader issue, so don;t need to load each class anymore 
    for (i = 0; i < (int)pDexFile->pHeader->classDefsSize; i++) {
    	pClassDef = dexGetClassDef(env, pDexFile, i);
     	pString = dexStringByTypeIdx(env, pDexFile, pClassDef->classIdx);
     	convertToDotClassName(pString, &pConvName);
        JACDebug(env, JACModule4, func, (char *)"Searched class name: %s\n", pConvName);
    	jclassName = env->NewStringUTF(pConvName);
    	clsObj =env->CallObjectMethod(myLoaderObject, midLoadClass, jclassName);
        if(env->ExceptionOccurred())
        {
            env->ExceptionDescribe ();
            JACDebugWarning(env, JACModule4, func, (char *)"Problem loading class: %s; Continue loading other classes\n", pConvName);
        	env->ExceptionClear();
        }
        else
    		env->DeleteLocalRef(clsObj);
    	env->DeleteLocalRef(jclassName);
        free(pConvName);
    }
*/
    repairContextClassLoader(env, myLoaderObject);

 	LOGE("Finished class walking. Optimizing flag: %d", params->useOdex);

 	// If useOdex flag is on, do bytecode optimization
 	// The bytecode optimization is done in-place in dex memory
 	// Therefore memory protection has to be changed to Read/Write
 	// and back to ReadOnly after the optimization is finished
 	if(params->useOdex)
    {
 		void* dalvikVMdevice = NULL;
 		DexOptimizerDevice dexOptimizerDevice;

 		// Initializations...
 		initDexOptimizerDevice(env, &dexOptimizerDevice);
        dalvikVMdevice = (*dexOptimizerDevice.initDalvikVMDevice)(env);
        // meanwhile there is only one kind of optimization for IGetObject instruction
        void* optConfig = (*dexOptimizerDevice.getIGetObjectOptConfig)();

    	if(!optConfig)
    	{
 	    	DBGWRAP(LOGE("Failed allocating optimization config. Not optimizing..."));
    	}
    	if(dalvikVMdevice && optConfig)
    	{
    		mprotect(params->dexInternalParams[jarN].memMapAddr, params->dexInternalParams[jarN].memMapLength, PROT_READ| PROT_WRITE);
    		// The loop over all methods doing the optimization
    		for(int methodN = 0;methodN < indexReaderOutput->dexByteCodeRecordNumber;methodN++)
    		{
    			void* classObjectPtr;
    			char* pDex = (char*)pDexFile->pHeader;

    			convertFromDotClassName(indexReaderOutput->dexByteCodeRecords[methodN].class_name, &pConvName);

    			classObjectPtr = (*dexOptimizerDevice.getClassObject)(dalvikVMdevice, pConvName);
    			DBGWRAP(LOGI("Class: %s its pointer 0x%x",pConvName, classObjectPtr));
    			if(classObjectPtr)
    			{
    				(*dexOptimizerDevice.optimizeBytecode)(env,&indexReaderOutput->dexByteCodeRecords[methodN],
    						&pDex[indexReaderOutput->dexByteCodeRecords[methodN].dex_offset],
    						indexReaderOutput->dexByteCodeRecords[methodN].bytecode_length,
    						classObjectPtr, dalvikVMdevice, optConfig);
    			}
    	        ac_free(pConvName);
    		}

    		mprotect(params->dexInternalParams[jarN].memMapAddr, params->dexInternalParams[jarN].memMapLength, PROT_READ);
    	}
    	// cleanup
		DBGWRAP(LOGI("Cleaning up optimizer"));
    	(*dexOptimizerDevice.destroyOptConfig)(optConfig);
    	(*dexOptimizerDevice.destroyDalvikVMDevice)(dalvikVMdevice);
    }

	DBGWRAP(LOGI("Cleaning up reader output"));
 	(*indexReaderOutput->destroyIndexReaderOutput)(env, indexReaderOutput);

    return ACCESS_STATUS_SUCCESS;
}

#endif //CLASS_WALKER_IMPL_H
