#ifndef DEX_OPTIMIZE_H
#define DEX_OPTIMIZE_H

#include "iso98wrap.h"

/*!
 * The structure defines an optimizer device
 * with set of functions used for optimization.
 * The use of those functions through function
 * pointers helps to avoid exporting them and
 * also gives flexibility in configuring it
 * with different functions if needed
 */
typedef struct _DexOptimizerDevice
{
	/*!
	 * The function initializing DalvkVM access device
	 */
	void* (*initDalvikVMDevice)(JNIEnv* env);
	/*!
	 * The function destroying DalvkVM access device
	 */
	void  (*destroyDalvikVMDevice)(void* p);
	/*!
	 * The function returning internal native class pointer
	 * for a loaded class by the classname
	 */
	void* (*getClassObject)(void* dvm, const char* className);
	/*!
	 * The function initializing and returning OptConfig handler
	 * The OptConfig handler defines parameters of optimization
	 */
	void* (*getIGetObjectOptConfig)();
	/*!
	 * The function destroying OptConfig handler
	 */
	void  (*destroyOptConfig)(void* p);
	/*!
	 * The function doing bytecode optimization
	 * \param dexByteCodeRecord The record defining the java method
	 * \param bytecode  pointer to method bytecode
	 * \param length    method bytecode length
	 * \param pDvmDevice opaque pointer to dvmDevice
	 * \param pOptConfig pOptConfig opaque pointer OptConfig
	 */
	int   (*optimizeBytecode)(JNIEnv* env,DexByteCodeRecord* dexByteCodeRecord, const char* bytecode,
			unsigned int length,void* classObj, void* pDvmDevice, void* pOptConfig);
}DexOptimizerDevice;

/*!
 * The function initializing DexOptimizerDevice
 */
void initDexOptimizerDevice(JNIEnv* env,DexOptimizerDevice* dexOptimizerDevice);

#endif
