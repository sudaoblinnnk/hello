#ifndef PROCESS_COOKIE_IMPL_H
#define PROCESS_COOKIE_IMPL_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "ac_Stdlib_Internal.h"
#include "dexOperator.h"
#include "antiDebug.h"


//#define DEBUG_MEM_POOL

/*!
 * The structure defining one memory pool bucket
 * (For memory pool see the struct below)
 * A bucket is always filled consecutively from the beginning
 */
typedef struct _MemPoolBucket
{
	/*!
	 * The pointer to the bucket memory
	 */
	char*                 buf;
	/*!
	 * The current offset into the unused memory in the bucket
	 */
	unsigned int          offset;
	/*!
	 * The pointer to the next bucket.Null if this bucket is the last (current) one
	 */
	struct _MemPoolBucket* next;

} MemPoolBucket;

/*!
 * Memory pool is used to prevent
 * memory fragmentation potentially caused
 * by a memory allocation on heap for each string
 * defined in index file
 * Memory pool is essentially a linked list of memory buckets
 * Memory buckets are of fixed size. A new bucket is allocated
 * if no memory left in the existing buckets.
 * MemPool IS CURRENTLY NOT IN USE BECAUSE OF UNEXPLAINED
 * MEMORY CORRUPTION ON OPHONE. NOT CLEAR WHETHER IT IS CAUSED
 * BY MEM POOL FAULTY IMPLEMENTATION OR BY TRANSCODER ISSUES
 * OR BY MEMORY CORRUPTION ELSEWHERE
 */
typedef struct _MemPool
{
	/*!
	 * First bucket in the linked list
	 */
	MemPoolBucket* first;
	/*!
	 * Current (and last) bucket in the linked list
	 */
	MemPoolBucket* current;
	/*!
	 * The bucket size (supposed not
	 * to be changed over memory pool lifetime)
	 */
	unsigned int   bucket_size;
	/*!
	 * The current number of buckets in the pool
	 */
	unsigned int   buckets_number;
} MemPool;

#define MEM_PAD_SIZE 10
#define MEM_PAD_CHAR '*'
#define MIN_INDEX_ELEMENT_LEN	21

static void dumpMem(FILE* f, const void* ptr, int nBytes);

static int checkForDigits(char *inStr)
{
    int retCode = 1;

    for(int pos = 0; pos < ac_STRLEN(inStr); pos++)
    {
	if(!isdigit(inStr[pos]))
	{
	    retCode = 0;
	    break;
	}
    } 
    return retCode;
}
static int checkMemPool(JNIEnv *env,MemPool* memPool)
{
#ifdef DEBUG_MEM_POOL
	static char MEM_PAD[MEM_PAD_SIZE];
	static void* dummyResult = memset(MEM_PAD, MEM_PAD_CHAR, MEM_PAD_SIZE);
	MemPoolBucket* memPoolBucket = memPool->first;
	unsigned int bucket = 1;

	LOGI("Checking mem pool corruption, %d buckets", memPool->buckets_number);
	while(memPoolBucket)
	{
		int memcmpres;
		MemPoolBucket* currentMemPoolBucket = memPoolBucket;
		if(memcmpres = memcmp(&memPoolBucket->buf[memPool->bucket_size], MEM_PAD, MEM_PAD_SIZE))
		{
			LOGE("Found corrupted memory at bucket: %d memcmp returned %d ", bucket, memcmpres);
			dumpMem(stderr, &memPoolBucket->buf[memPool->bucket_size - MEM_PAD_SIZE], MEM_PAD_SIZE * 2);
			assert(0); //temporary
			return -1;
		}
		memPoolBucket = memPoolBucket->next;
		bucket++;
	}
	LOGI("The mem pool has been verrified ");
	return 0;

#endif
}


 static void destroyMemPool(JNIEnv *env,MemPool* memPool)
{
	unsigned int bucket = 1;
	MemPoolBucket* memPoolBucket = memPool->first;

	checkMemPool(env, memPool);
	// TODO COMMENT IT OUT
	LOGI("Destroying mem pool, buckets number %d", memPool->buckets_number);
	while(memPoolBucket)
	{
		MemPoolBucket* currentMemPoolBucket = memPoolBucket;
		ac_free(memPoolBucket->buf);
		memPoolBucket = memPoolBucket->next;
		ac_free(currentMemPoolBucket);
		// TODO COMMENT IT OUT
		LOGI("Destroyed buckets %d", bucket);
		bucket++;
	}
	(LOGI("The mem pool destroyed"));
}


static void initMemPool(JNIEnv *env,MemPool* memPool, unsigned int bucketSize)
{
	MemPoolBucket* memPoolBucket = (MemPoolBucket*)ac_malloc(sizeof(MemPoolBucket));
	memPool->bucket_size = bucketSize;
	memPool->current = memPool->first = memPoolBucket;
#ifdef DEBUG_MEM_POOL
	memPoolBucket->buf = (char*)ac_malloc(bucketSize + MEM_PAD_SIZE);
	memset(&memPoolBucket->buf[memPool->bucket_size], MEM_PAD_CHAR, MEM_PAD_SIZE);
#else
	memPoolBucket->buf = (char*)ac_malloc(bucketSize);
#endif
	memPoolBucket->next = NULL;
	memPoolBucket->offset = 0;
	memPool->buckets_number = 1;
}


static char* allocate(JNIEnv *env,MemPool* memPool, unsigned int size)
{
	char* retValue = NULL;
	MemPoolBucket* memPoolBucket = memPool->current;
	assert(!memPoolBucket->next);
	assert(size <= memPool->bucket_size);
	if(memPoolBucket->offset + size <= memPool->bucket_size)
	{
		retValue = &memPoolBucket->buf[memPoolBucket->offset];
		memPoolBucket->offset += size;
	}
	else
	{
		memPoolBucket->next = (MemPoolBucket*)ac_malloc(sizeof(MemPoolBucket));
		memPoolBucket = memPoolBucket->next;
#ifdef DEBUG_MEM_POOL
		memPoolBucket->buf = (char*)ac_malloc(memPool->bucket_size + MEM_PAD_SIZE);
		memset(&memPoolBucket->buf[memPool->bucket_size], MEM_PAD_CHAR, MEM_PAD_SIZE);
#else
		memPoolBucket->buf = (char*)ac_malloc(memPool->bucket_size);
#endif
		memPoolBucket->next = NULL;
		memPoolBucket->offset = size;
		memPool->current = memPoolBucket;
		retValue = memPoolBucket->buf;
		memPool->buckets_number++;
	}
	return retValue;
}



static void parseIndexWarningHandle(JNIEnv *env,int field, int method)
{
	(LOGE("Warning while parsing field %d, method %d", field, method));
}


static int destroyIndexReaderOutput(JNIEnv *env,IndexReaderOutput* indexReaderOutput)
{
	int i = 0;
	assert(indexReaderOutput);
	//destroyMemPool(env, (MemPool*)indexReaderOutput->memPool);
	//LOGI("deleting dexByteCodeRecords");

	for(i = 0; i < indexReaderOutput->dexByteCodeRecordNumber; i++)
	{
		ac_free(indexReaderOutput->dexByteCodeRecords[i].class_name);
		ac_free(indexReaderOutput->dexByteCodeRecords[i].method_name);
		indexReaderOutput->dexByteCodeRecords[i].class_name = NULL;
		indexReaderOutput->dexByteCodeRecords[i].method_name = NULL;
	}

	ac_free(indexReaderOutput->dexByteCodeRecords);
	//LOGI("deleted dexByteCodeRecords");
	return 0;
}

static int isBigEndianHardware()
{
	int result = 0;
    unsigned short verify = 0x1122;
    if(*((unsigned char*) &verify ) == 0x11)
    {
       result =  1;
    }
	else
	{
		result = 0;;
	}    

	return result;
} 

//covert the 32 bit data as little endian format
static int to32LittleEndian(int bigEndianData)
{
	int b4 = bigEndianData & 0x000000ff;
	b4 <<= 24;
	int b3 = bigEndianData & 0x0000ff00;
	b3 <<= 8;
	bigEndianData >>= 8;
	int b2 = bigEndianData & 0x0000ff00;
	bigEndianData >>= 16;
	int b1 = 0x000000ff & bigEndianData;
	int result = (int) (b4 | b3 | b2 | b1);
	return result;
}


//if return 0, get one string token, otherwise, no token is gotten
static int GetNextStringToken(JNIEnv *env, char **ppszSrc, char **ppToken)
{
	assert(ppszSrc);
	assert(ppToken);
	int iTokenLen = 0;
	char *pTokenBegin = NULL;

	while(**ppszSrc == ' ')
	{
		(*ppszSrc)++;
	}

	pTokenBegin = *ppszSrc;

	//calcuate the token length
	while((**ppszSrc != ' ') && (**ppszSrc != '\0'))
	{
		iTokenLen++;
		(*ppszSrc)++;
	}

	*ppToken = (char *)ac_calloc(iTokenLen + 1, 1);
	
	if(*ppToken == NULL)
	{
		(LOGI("get next token, allocation failed \n"));
		return -1;
	}
	
	memcpy(*ppToken, pTokenBegin, iTokenLen);
	return 0;
}

static int AssembleClassMethod(JNIEnv *env, char *pszSrc, DexByteCodeRecord *pStIndexInfoList)
{
	int result = 0;
	char *pTmp = pszSrc;
	int recordNum = 0;
	
	while (*pTmp != '\0')
	{
		result = GetNextStringToken(env, &pTmp, &(pStIndexInfoList[recordNum].class_name));
		result = GetNextStringToken(env, &pTmp, &(pStIndexInfoList[recordNum].method_name));
		recordNum++;
	}

	return 0;
}


static int poisonerIndexReader (JNIEnv *env,ac_Bytes* indexBuf, IndexReaderOutput* pIndexReaderOutput)
{
	int recordNum = 0;
	int i = 0;
	int result = 0;
	AntiDebugData adbg;
	memcpy(&recordNum, indexBuf->bytes, 4);
	init2ADbg(env, &adbg, V_DELTA_1);
	LOGI("read record number from buffer, the record num = %d\n" , recordNum);
	assert(indexBuf->length > (recordNum * sizeof(DexByteCodeRecord) + 4));
	pIndexReaderOutput->dexByteCodeRecords = (DexByteCodeRecord*)ac_calloc(recordNum, sizeof(DexByteCodeRecord));	

	if(pIndexReaderOutput->dexByteCodeRecords == NULL)
	{
		(LOGI("allocation failed\n"));
		return -1;
	}
		
	memcpy(pIndexReaderOutput->dexByteCodeRecords, indexBuf->bytes + 4, recordNum * sizeof(DexByteCodeRecord));

	if(isBigEndianHardware() == 1)
	{
		for(i = 0; i < pIndexReaderOutput->dexByteCodeRecordNumber; i++)
		{
			pIndexReaderOutput->dexByteCodeRecords[i].bytecode_offset = to32LittleEndian(pIndexReaderOutput->dexByteCodeRecords[i].bytecode_offset);
			pIndexReaderOutput->dexByteCodeRecords[i].bytecode_length = to32LittleEndian(pIndexReaderOutput->dexByteCodeRecords[i].bytecode_length);
			pIndexReaderOutput->dexByteCodeRecords[i].dex_offset = to32LittleEndian(pIndexReaderOutput->dexByteCodeRecords[i].dex_offset);			
		}
	}
	markAndVerifyADbg(env, &adbg,(char *)__FUNCTION__,__LINE__);
	init2ADbg(env, &adbg, V_DELTA_1);
	
	/*all the left content in the index buf must be all characters, no any byte*/
	result = AssembleClassMethod(env, (char *)(indexBuf->bytes + sizeof(int) + recordNum * sizeof(DexByteCodeRecord)),
								pIndexReaderOutput->dexByteCodeRecords);

	pIndexReaderOutput->dexByteCodeRecordNumber = recordNum;
	pIndexReaderOutput->destroyIndexReaderOutput = destroyIndexReaderOutput;
	markAndVerifyADbg(env, &adbg,(char *)__FUNCTION__,__LINE__);
	return result;
}


static void dumpMem(FILE* f, const void* ptr, int nBytes)
{
	static const unsigned int LINE_SIZE = 16;
	int counter = 0;
	const char* tmp = (const char*)ptr;

	fprintf(f, "=====================DUMPING MEM 0x%x %d BYTES==================================\n", ptr, nBytes);
	//LOGI( "=====================DUMPING MEM 0x%x %d BYTES==================================\n", ptr, nBytes);
	while(counter < nBytes)
	{
		int byteCounter;
		for(byteCounter = 0;byteCounter < LINE_SIZE; byteCounter++)
		{
			fprintf(f, "%.2x ", tmp[byteCounter]);
			//LOGI("%.2x ", tmp[byteCounter]);
		}
		fprintf(f, "   ");
		//LOGI("   ");
		for(byteCounter = 0;byteCounter < LINE_SIZE; byteCounter++)
		{
			fprintf(f, "%c", tmp[byteCounter]);
			//LOGI("%c", tmp[byteCounter]);
		}
		fprintf(f, " \n");
		//LOGI(" \n");
		counter += LINE_SIZE;
		tmp += LINE_SIZE;

	}
	fprintf(f, "=====================DUMP END==================================\n");
	//LOGI("=====================DUMP END==================================\n");
}

static void dumpMemToFile(char* fileName, const void* ptr, int nBytes)
{
	FILE* f = fopen(fileName, "rw+");
	if(f < 0)
	{
		fprintf(stderr, "Failed opening file %s \n", fileName);
		return;
	}
	dumpMem(f, ptr, nBytes);

	fclose(f);

}

/*
 * Check to see if a given data pointer is a valid double-word-aligned
 * pointer into the given memory range (from start inclusive to end
 * exclusive). Returns true if valid.
 */
static bool isValidPointer(const void* ptr, const void* start, const void* end)
{
    return (ptr >= start) && (ptr < end) && (((uintptr_t) ptr & 7) == 0);
}

// temp set access flags to test level 7 problem
static inline const DexClassDef* dexGetClassDef(JNIEnv* env,const DexFile* pDexFile, u4 idx) {
    assert(idx < pDexFile->pHeader->classDefsSize);
    return &pDexFile->pClassDefs[idx];
}

static inline const char* dexGetStringData(JNIEnv* env,const DexFile* pDexFile, const DexStringId* pStringId)
{
    const u1* ptr = (const u1*) (pDexFile->baseAddr + pStringId->stringDataOff);
	 //JACDebug(env, JACModule4, "classWalker", (char*)"In dexGetStringData the ptr 0x%x\n", ptr);
    // Skip the uleb128 length.
    while (*(ptr++) > 0x7f) ;

    return (const char*) ptr;
}

static inline const DexStringId* dexGetStringId(JNIEnv* env,const DexFile* pDexFile, u4 idx) {
    assert(idx < pDexFile->pHeader->stringIdsSize);
    return &pDexFile->pStringIds[idx];
}

static inline const char* dexStringById(JNIEnv* env,const DexFile* pDexFile, u4 idx) {
    const DexStringId* pStringId = dexGetStringId(env, pDexFile, idx);
	 //JACDebug(env, JACModule4, "classWalker", (char*)"In dexStringById string data offset %d\n", pStringId->stringDataOff);
    return dexGetStringData(env, pDexFile, pStringId);
}

static inline const DexTypeId* dexGetTypeId(JNIEnv* env,const DexFile* pDexFile, u4 idx) {
    assert(idx < pDexFile->pHeader->typeIdsSize);
    return &pDexFile->pTypeIds[idx];
}

static const char* dexStringByTypeIdx(JNIEnv* env,const DexFile* pDexFile, u4 idx) {
     const DexTypeId* typeId = dexGetTypeId(env,pDexFile, idx);
 	 //JACDebug(env, JACModule4, "classWalker", (char*)"In dexStringByTypeIdx descriptor id %d\n", typeId->descriptorIdx);
     return dexStringById(env, pDexFile, typeId->descriptorIdx);
}


int PROCESS_COOKIE_NAME (JNIEnv *env,DexOperatorParam* param )
{
	int jarN;
	int retVal = 0;
	AntiDebugData adbg;
    AntiDebugData adbgIntercon;
    int methodnum = 0;
	/*
	 * Sanity check
	 */
	init2ADbg(env, &adbg, V_DELTA_1);
	if(!param || !param->cookies || !param->indexData || !param->byteCodeData|| !param->dexFiles)
	{
		(LOGE("processCookie Invalid NULL Paramater MUST NEVER HAPPEN\n"));
		return -1;
	}

	/*
	for(jarN = param->jarsNumber;jarN--;)
	{
		if(!param->gameDexData[jarN].bytes)
		{
			LOGE("processCookie Invalid NULL data for jar %d  MUST NEVER HAPPEN\n", jarN);
			return -1;
		}
	}
	*/
    markAndVerifyADbg(env, &adbg, (char *)__FUNCTION__, __LINE__);
	for(jarN = 0; jarN < param->jarsNumber;jarN++)
	{
		init2ADbg(env, &adbgIntercon, V_DELTA_2);
		DexOrJar* dexOrJar = (DexOrJar*) param->cookies[jarN];
		JarFile* pJarFile;
		RawDexFile* pRawDexFile;
		DvmDex* pDvmDex;
		DexFile* pDexFile = NULL;
		pJarFile = dexOrJar->pJarFile;
		pRawDexFile = (RawDexFile*)dexOrJar->pRawDexFile;

		if (!dexOrJar->isDex)
		{
			int cachedFileNameLen;
			cachedFileNameLen = strlen(pJarFile->cacheFileName);
			(LOGI("processCookie cachedFileName pointer 0x%x name %s its length: %d pDvmDex 0x%x \n", pJarFile->cacheFileName, pJarFile->cacheFileName, cachedFileNameLen, pJarFile->pDvmDex));
			(LOGI("The jar zip: fd %d num entries in zip %d hash table size %d\n", pJarFile->archive.mFd, pJarFile->archive.mNumEntries, pJarFile->archive.mHashTableSize));

			pDvmDex = pJarFile->pDvmDex;
		}
		else if (pRawDexFile)
		{
			(LOGE("processCookie RawDex File \n"));
			pDvmDex = pRawDexFile->pDvmDex;
			pDexFile = pDvmDex->pDexFile;
		}

		pDexFile = pDvmDex->pDexFile;
		(LOGI("processCookie pDexFile 0x%x pHeader 0x%x\n", pDvmDex->pDexFile,  pDvmDex->pHeader));

		//LOGI("Dumping pDvmDex \n");
		//dumpMem(stderr, pDvmDex, 1024);

		(LOGI("processCookie pDexFile itself The header 0x%x pHeader opt header 0x%x mem addr 0x%x dex length %d\n", pDexFile->pHeader, pDexFile->pOptHeader, pDexFile->baseAddr, pDexFile->pHeader->fileSize));
		(LOGI("processCookie pDexFile itself shared mem 0x%x length 0x%x\n", pDvmDex->memMap.addr, pDvmDex->memMap.length));
#ifdef DEX_INDEX_MAP_DECLARATION_NON_EMPTY
		(LOGI("processCookie Before substitution the counts are strings: %d classes %d methods: %d fields %d\nreduced strings: %d classes %d methods: %d fields %d",
				pDexFile->pHeader->stringIdsSize, pDexFile->pHeader->typeIdsSize, pDexFile->pHeader->methodIdsSize, pDexFile->pHeader->fieldIdsSize,
				getReducedStringsCount(&pDexFile->indexMap),getReducedClassCount(&pDexFile->indexMap), getReducedMethodCount(&pDexFile->indexMap),
				getReducedFieldCount(&pDexFile->indexMap)));
#endif
		//dumpMem(stderr, pDvmDex->memMap.addr, 64);
		mprotect(pDvmDex->memMap.addr, pDvmDex->memMap.length, PROT_READ
				| PROT_WRITE);

		(LOGI("Dumping optHeader \n"));
		init2ADbg(env, &adbg, V_DELTA_120);
    	markAndVerifyADbg(env, &adbgIntercon,(char *)__FUNCTION__,__LINE__);
		{

			long bytecodeSize;
			const char* bytecodeBuf = NULL;
			const DexHeader* pHeader = pDexFile->pHeader;
			// dex data
			char* pDex = (char*)pHeader;
			if(!param->indexData || !param->byteCodeData)
			{
				(LOGE("Invalid parameters for cookie processing" ));
				return (-1);
			}

			// read index data
			int retvalue = poisonerIndexReader(env, param->indexData, &param->dexInternalParams[jarN].indexReaderOutput);
			if(retvalue != 0)
			{
			    (LOGE("poisoner index error" ));
				return (-1);
			}
    		markAndVerifyADbg(env, &adbg,(char *)__FUNCTION__,__LINE__);

			bytecodeSize = param->byteCodeData->length;
			bytecodeBuf = (const char*)param->byteCodeData->bytes;

			//LOGI("Dumping pDex header \n");
			//dumpMem(stderr,pDex,64);

			LOGI("unpoisoning methods dex offset: 0x%x" , pDex);

			// The unpoisoning loop below.
			// Iterates over all methods defined in the index file and copies original bytecode into the
			// method bytecode in the memory mapped dex file
		
			(LOGI("copy the byte code begining"));
			int methodnum =  param->dexInternalParams[jarN].indexReaderOutput.dexByteCodeRecordNumber;
			for(int methodN = 0; methodN < methodnum; methodN++)
			{
				if(methodN % 10 == 0)
				{
					init2ADbg(env, &adbg, C_DELTA_1);
				}
				
				memcpy(
						&pDex[param->dexInternalParams[jarN].indexReaderOutput.dexByteCodeRecords[methodN].dex_offset],
						&bytecodeBuf[param->dexInternalParams[jarN].indexReaderOutput.dexByteCodeRecords[methodN].bytecode_offset],
						param->dexInternalParams[jarN].indexReaderOutput.dexByteCodeRecords[methodN].bytecode_length);    			

				if(methodN % 10 == 0)
				{
					markAndVerifyADbg(env, &adbg,(char *)__FUNCTION__,__LINE__);
				}
			}
			(LOGI("copy the byte code end, tiem check"));

			// Level 7 problem workaround,
			// set verification and optimization flags in the access flags on
			// TODO Consider moving this logic to class walker  and doing only to
			// those classes that were optimized
			init2ADbg(env, &adbg, V_DELTA_5);
			if(param->useOdex)
			{
			    int i;
			    DexClassDef* pClassDef;
			    for (i = 0; i < (int)pDexFile->pHeader->classDefsSize; i++)
			    {
			    	DexClassDef* pClassDef = (DexClassDef*)dexGetClassDef(env, pDexFile, i);
		     		pClassDef->accessFlags |= 0x30000;
			    }

			}
			(LOGI("unpoisoning is done returning \n" ));
    		markAndVerifyADbg(env, &adbg,(char *)__FUNCTION__,__LINE__);
		}
		init2ADbg(env, &adbgIntercon, V_DELTA_1);
		// Don't forget to return memory protection flag to the original state
		mprotect(pDvmDex->memMap.addr, pDvmDex->memMap.length, PROT_READ);
		// Store memory address and length in the internal params
		// To be used by the optimizer
		param->dexFiles[jarN] = pDexFile;
		param->dexInternalParams[jarN].memMapAddr = pDvmDex->memMap.addr;
		param->dexInternalParams[jarN].memMapLength = pDvmDex->memMap.length;
		param->dexInternalParams[jarN].dexAddr = (char *) pDexFile->pHeader;
		param->dexInternalParams[jarN].dexLength = (int) pDexFile->pHeader->fileSize;

		(LOGI("processCookie  finished\n"));
    		markAndVerifyADbg(env, &adbgIntercon,(char *)__FUNCTION__,__LINE__);
	}

    return retVal;
}

#endif //PROCESS_COOKIE_IMPL_H
