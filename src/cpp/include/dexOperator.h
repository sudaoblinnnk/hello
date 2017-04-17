#ifndef _H_DEXOPERATOR_
#define _H_DEXOPERATOR_

#include "iso98wrap.h"
#include "ac_common.h"

static const int DEX_INDEX_STRING_MAX_LENGTH = 256;

/*!
 * The structure encapsulating an index file record
 */
typedef struct _DexByteCodeRecord
{
	/*!
	 * The offset to the method bytecode in bytecode.dat
	 */
	unsigned int   bytecode_offset;
	/*!
	 * The length of the method bytecode in bytecode.dat
	 */
	unsigned int   bytecode_length;
	/*!
	 * Not currently used
	 */
	unsigned int   file_index;
	/*!
	 * The offset to the method bytecode in dex file/memory
	 */
	unsigned int   dex_offset;

	/*!
	 * The five fields below are not currently used
	 */
	unsigned int   register_size;
	unsigned int   ins_size;
	unsigned int   outs_size;
	unsigned int   tries_size;
	char*          instruction;
	/*!
	 * The method's class name
	 */
	char*           class_name;
	/*!
	 * The method's name
	 */
	char*           method_name;
}DexByteCodeRecord;


/*!
 * The structure holding index file records
 */
typedef struct _IndexReaderOutput
{
	/*!
	 * The array of index file records
	 */
	DexByteCodeRecord* dexByteCodeRecords;

	/*!
	 * The number of index file records
	 */
	unsigned int       dexByteCodeRecordNumber;

	/*!
	 * The memory pool handler
	 * THE MEMORY POOL IS NOT USED
	 * SEE COMMENTS IN MEM POOL
	 * DECLARATION
	 */
	//void*              memPool;

	int (*destroyIndexReaderOutput)(JNIEnv *env,struct _IndexReaderOutput* indexReaderOutput);
} IndexReaderOutput;

/*!
 * The structure holding internal parameters
 * passed from processCookie to class walker (for optimization)
 */
typedef struct _DexInternalParams
{
	/*
	 * index records(needed to get the list of methods for optimization)
	 */
	IndexReaderOutput indexReaderOutput;
	/*
	 * The dex memory.
	 * It is stored because the optimizer needs
	 * to change access protection temporarily
	 * to put optimized bytecode in dex memory
	 */
	char* 			  memMapAddr; /* dex memory address */
	int 			  memMapLength;/* dex memory length */

	char* 			  dexAddr;
	int			  dexLength;

} DexInternalParams;


typedef struct _DexOperatorParam
{
	/*
	 * The number of jars
	 */
	int jarsNumber;
	/*
	 * The array of cookies.
	 * Number of elements must be equal to jarsNumber
	 */
	int* cookies;
	/*
	 * Index data referencing to bytecode and poisoned dex data
	 */
	ac_Bytes* indexData;
    /*
    * Bytecode data extracted from original dex data
    */
	ac_Bytes* byteCodeData;

    /*
     * A flag to signal dex operator to use ODEX or not, 0 or 1
     */
    	int useOdex;

    /*
	 * Array of return pointer value
	 * Number of elements must be equal to jarsNumber
	 * Preallocated by the caller
	 * The pointer points to DexFile, but we declare it void here
	 * to reduce dependency on differences in DexFile srtucture
	 * between API levels 8 and 9
	 */
	void** dexFiles;

	/*
	 * Array of dex internal data for optimization
	 */
	DexInternalParams* dexInternalParams;
} DexOperatorParam;



/*
 * Returns error code, 0 if everything's OK
 * This function gets access to dex memory through
 * the cookie obtained in java code and puts
 * the unpoisoned bytecode there
 */
int processCookie (JNIEnv *env,int version, DexOperatorParam* params );


#endif
