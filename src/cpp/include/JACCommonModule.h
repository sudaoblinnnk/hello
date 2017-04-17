#ifndef _H_JACCOMMON_
#define _H_JACCOMMON_

#include <iso98wrap.h>

#ifdef __cplusplus__
extern "C" {
#endif

ACCESS_STATUS allocateSecureMemory(IRDETO_SECURE_DATA *data);
void freeSecureMemory(IRDETO_SECURE_DATA *data);
ACCESS_STATUS allocateVoucher(JNIEnv *env, char *voucherPath); 
void checkInMemoryContents(JNIEnv *env);
ACCESS_STATUS allocateStore(JNIEnv *env, char *storePath);
ACCESS_STATUS saveToFile(JNIEnv *env, char *fileName, unsigned char *data, int length);
void hexToBytes(char *inData, unsigned char *outData);
void bytesToHex(unsigned char *inData, int size,  char *outData);
#if defined(_JAC_DEBUG_ANDROID) || defined(_JAC_SIGNING)
void JACDebug(JNIEnv *env, const char *module, const char *func, char *fmt, ...);
void JACDebugWarning(JNIEnv *env, const char *module, const char *func, char *fmt, ...);
#define DBGWRAP(x) (x); 
#else
#define JACDebug(env, module, func, string, par )
#define JACDebugWarning(env, module, func, string, par)
#define DBGWRAP(x)
#endif
ACCESS_STATUS getStorageBase(JNIEnv *env, char *path);
ACCESS_STATUS uncompressSecureData(JNIEnv *env,ac_uint8 **ppSecureData, ac_uint32 *pDataLen);

#ifdef __cplusplus__
}
#endif

#endif
