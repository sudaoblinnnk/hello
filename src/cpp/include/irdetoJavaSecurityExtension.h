#ifndef _H_IRDETOJAVASECURITYEXTENSION__
#define _H_IRDETOJAVASECURITYEXTENSION__

#include "iso98wrap.h"
#include "ac_common.h"
#include "ac_Crypto.h"
#include "irdetoJavaSecurity.h"
#include "ac_Stdlib_Internal.h"

typedef struct _JAVAArchive
{
    ac_Bytes *indexData;
    ac_Bytes *byteCodeData;
    ac_Bytes *optByteCodeData;
    ac_Bytes *archiveData;
    ac_uint8 **archiveId;
    ac_uint8 indexId[HANDLE_ID_LEN + 1];
    ac_uint8 byteCodeId[HANDLE_ID_LEN + 1 ];
    ac_uint8 optByteCodeId[HANDLE_ID_LEN + 1 ];
    ac_uint32 nItems;

}JAVAArchive;

typedef struct _JACConfig
{
    ac_uint32 numJavaArchive;
    ac_uint8 nativeLibDir[FILE_PATH_LEN+1];
    ac_uint8 operationMode[READ_LINE_LEN+1];
    ac_uint8 hmacShaHandle[HANDLE_ID_LEN+1];
    ac_int32 optDex;
    ac_int32 appThread;
    ac_int32 enableAdbg;
    ac_int32 disableStaticIV;

}JACConfig;

#ifdef __cplusplus__
extern "C" {
#endif

ac_Status setIACSecurityContext(JNIEnv *env,ac_char *storePath);
ac_Status retrieveVoucherFromSecureStore(JNIEnv *env, ac_char *storePath, ac_uint8 ***voucher, ac_uint32 *nElements);
ac_Status getJavaDataFromSecureStore(JNIEnv *env, ac_char *storePath, JAVAArchive **pJavaArchive, JACConfig **pJACConfig);
ac_Status setJavaConfig(JNIEnv *env, ac_char *storePath);
ac_Status getHmacSha256ByHandle(JNIEnv *env, ac_uint8 *data, ac_uint32 dataLen, ac_char *storePath, ac_uint8 *digest);
ac_Status getHmacSha256Init(JNIEnv *env, ac_char *storePath, ac_Op_Context *pOperationContext);
ac_Status getHmacSha256Update(JNIEnv *env, ac_uint8 *data, ac_uint32 dataLen, ac_Op_Context pOperationContext);
ac_Status getHmacSha256Finalize(JNIEnv *env, ac_Op_Context pOperationContext, ac_uint8 *digest);
ac_Status shutdownJAC_IAC(JNIEnv *env);
void freeElementMemory(ac_uint8 **entity, ac_uint32 nElements);
ac_Status setJACConfiguration(JNIEnv *env, ac_char *storePath, JACConfig **pJacConfig);

#ifdef __cplusplus__
}
#endif
#endif
