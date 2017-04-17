/** \defgroup ac_Crypto Irdeto ActiveCloak Cryptographic component */
/* @{ */

/*! \file ac_SecureStore_Internal.h
   Irdeto B.V.

   The software and information contained in this package ("Software") is owned by
   Irdeto B.V., its affiliates or licensors ("Software Owners"). The Software is
   protected by U.S., Canadian, and international intellectual property laws and
   treaties and may contain patents, trademarks, copyrights, or other intellectual
   property rights of the Software Owners. If you acquired this package without an
   appropriate agreement, please contact Irdeto at:

     phone +1 613 271 9446, email: sales@irdeto.com

   The furnishing of this package does not constitute a license, express or implied,
   by estoppel or otherwise, to any patents, trademarks, copyrights, or other
   intellectual property rights of the Software Owners. Use of the Software without
   an appropriate agreement may constitute an infringement of the Software Owners'
   intellectual property rights and could subject you to legal action. 

   \brief The public application programming interface (API) definitions for the
          ActiveCloak Cryptographic component.

   Description: Public Header file for ActiveCloak Cryptographic component of ActiveCloak project.
                This file contains the defined types and the public application programming
                                interface (API) definitions for the cypto component.

   Limitations: None

   Thread Safe: Supported via 1 context per thread

   Platform Dependencies: CSS Version 5.1 or newer      (i.e.: Platform/OS/CSS version)

   Compiler Options:
*/


#ifndef __ac_SECURESTORE_INTERNAL_H__
#define __ac_SECURESTORE_INTERNAL_H__

#include "xc/xc_extensions.h"

#include "ac_types.h"
#include "ac_Common_Internal.h"
#include "ac_SecureStore.h"
#include "ac_SecureCounter.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Define the size of all serializable length fields */
#define SIZE_LENGTH  4

#define SS_HEADER_SIZE   4*SIZE_LENGTH
#define SS_ENDIAN_BYTES  0x11223344
#define SS_MAGIC_NUMBER  0x2001BEEF

#define SS_VERSION_1  0x00000001
#define SS_VERSION_2  0x00000002
#define SS_VERSION_3  0x00000003

#define SS_VERSION  SS_VERSION_3

#define SS_ENTRY_LENGTH_MIN  0x2C

/* Defines for the Secure Store SKEK state bits */

#define    SS_SKEK_STATE_INIT        0x00000001
#define    SS_SKEK_STATE_WRITEABLE   0x00000002
#define    SS_SKEK_ENABLE_CLIENT_NL  0x00000010
#define    SS_SKEK_ENABLE_SERVER_NL  0x00000020
#define    SS_SKEK_SEK_TRANSFORMED   0x00000040
#define    SS_SKEK_STATE_PROTED      0x00000080
#define    SS_SKEK_STATE_NEEDS_WRITE 0x00000100
#define    SS_SKEK_NODELOCK_POC      0x00000200
#define    SS_SKEK_NODELOCK_HWFPCFV  0x00000400
#define    SS_SKEK_NODELOCK_USERINIT 0x00000800
#define    SS_SKEK_NODELOCK_WIFIMAC  0x00001000
#define    SS_SKEK_NODELOCK_UUID     0x00002000
#define    SS_SKEK_NODELOCK_PFPCFV   0x00004000
#define    SS_SKEK_NODELOCK_NLED     0x00080000

#define ac_SS_STATE_IS_SET(context, flag)      ((((context)->modeFlags) & (flag)) != 0)
#define ac_SS_STATE_SET_FLAG(context, flag)    (((context)->modeFlags) |= (flag))
#define ac_SS_STATE_CLEAR_FLAG(context, flag)  (((context)->modeFlags) &= ~(flag))
#define ac_SS_STATE_CLEAR_ALL(context, flag)   (((context)->modeFlags) &= ~(flag))

/* typedef ac_uint32 ac_SS_Mode; */

enum {
    SS_ATTRIB_PUBLIC   = 0x00000000,
    SS_ATTRIB_PRIVATE  = 0x00000001,
    SS_ATTRIB_MEM_ONLY = 0x00000002
};

struct __ac_SS_Context {
    ac_Context securityContext;
    RKM_Context rkm_context;
    ac_SS_Mode modeFlags;
};

/*! AC Options structure supported by the ActiveCloak secure store data entry. */
typedef struct {
    ac_Bytes ID;         /*!< Key id structure member. */
    ac_Bytes IV;         /*!< IV structure member. */
    ac_Bytes padding;    /*!< Padding structure member. */
    ac_Bytes refData1;   /*!< RefData1 structure member. */
    ac_Bytes refData2;   /*!< Refdata2 structure member. */
    ac_Bytes refData3;   /*!< Refdata3 structure member. */
    ac_Bytes recDigest;  /*!< Record Digest blob member. */
} ac_Options;

/*! Internal secure store information. */
typedef struct __RKM_KeyInfo {
    ac_Data_Type      keyType;       /*!< Key type structure member. */
    ac_uint32         keyAttribute;  /*!< key entry attributes for ones such as in-memory-only|hidden/private, ORable field. */
    ac_uint32         count;         /*!< Count of number of data elements (used by Append operations). */
    ac_uint8          *pKeyData;     /*!< Pointer structure member to key data. */
    ac_uint32         keyDataSize;   /*!< Key data size structure member. */
    ac_Options        optionData;    /*!< Extra optional data */
    ac_SS_Data_Handle pNext;         /*!< Pointer structure member to next member. */
} RKM_KeyInfo;

/*! SecureStore header structure supported by ActiveCloak secure store.  */
typedef struct {
    ac_uint32 endianMagic;    /*!< endianess and magic number variable field. */
    ac_uint32 versionNumber;  /*!< version number variable. */
    ac_uint32 skekState;      /*!< secure store state field. */
    ac_uint32 recCount;       /*!< variable to track number of entries in the secure store. */
} ac_Secure_Store_Header;


#define MAX_ID_LENGTH 128

#ifdef DEBUG_DISABLE_THIS
static const ac_uint8 KS_KEK_INIT_XFORM[] = {(ac_char *)"KS_KEK_INIT_XFORM"};
static const ac_uint8 KS_KEKIV_INIT_XFORM[] = {(ac_char *)"KS_KEKIV_INIT_XFORM"};

static const ac_uint8 KS_KEK_PARENT_INIT_XFORM[] = {(ac_char *)"KS_KEK_PARENT_INIT_XFORM"};
static const ac_uint8 KS_KEKIV_PARENT_INIT_XFORM[] = {(ac_char *)"KS_KEKIV_PARERNT_INIT_XFORM"};

static const ac_uint8 KS_KEK_PROTECTED[] = {(ac_char *)"KS_KEK_PROTECTED"};
static const ac_uint8 KS_KEKIV_PROTECTED[] = {(ac_char *)"KS_KEKIV_PROTECTED"};

static const ac_uint8 KS_KEK_PARENT_PROTECTED[] = {(ac_char *)"KS_KEK_PARENT_PROTECTED"};
static const ac_uint8 KS_KEKIV_PARENT_PROTECTED[] = {(ac_char *)"KS_KEKIV_PARENT_PROTECTED"};

static const ac_uint8 KS_KEK_DERIVED[] = {(ac_char *)"KS_KEK_DERIVED"};
static const ac_uint8 KS_KEKIV_DERIVED[] = {(ac_char *)"KS_KEKIV_DERIVED"};

static const ac_uint8 KS_KEK_NODELOCK[] = {(ac_char *)"KS_KEK_NODELOCK"};
static const ac_uint8 KS_KEKIV_NODELOCK[] = {(ac_char *)"KS_KEKIV_NODELOCK"};

static const ac_uint8 KS_KEK_SUBORDINATE_NAME[] = {(ac_char *)"KS_KEK_SUBORDINATE_NAME"};

static const ac_uint8 KS_Voucher_ID[] = {(ac_char *)"KS_Voucher_ID"};
static const ac_uint8 KS_IV_Vouchers_ID[] = {(ac_char *)"KS_IV_Vouchers_ID"};
static const ac_uint8 KS_IV_Modules_ID[] = {(ac_char *)"KS_IV_Modules_ID"};

static const ac_uint8 KS_PARENT_SIGNATURE[] = {(ac_char *)"KS_PARENT_SIGNATURE"};
static const ac_uint8  KS_NODELOCK_MOFN_TAB[] = {(ac_char *)"KS_NODELOCK_MOFN_TAB"};
#else
static const ac_uint8 KS_KEK_INIT_XFORM[] = {0x19, 0x99, 0x20, 0x10, 0x20, 0xAA};
static const ac_uint8 KS_KEKIV_INIT_XFORM[] = {0x19, 0x99, 0x20, 0x10, 0x20, 0xBB};

static const ac_uint8 KS_KEK_PARENT_INIT_XFORM[] = {0x19, 0x99, 0x24, 0x10, 0x20, 0xAA};
static const ac_uint8 KS_KEKIV_PARENT_INIT_XFORM[] = {0x19, 0x99, 0x24, 0x10, 0x20, 0xBB};

static const ac_uint8 KS_KEK_PROTECTED[] = {0x19, 0xA9, 0x20, 0x10, 0x20, 0xCC};
static const ac_uint8 KS_KEKIV_PROTECTED[] = {0x19, 0xA9, 0x20, 0x10, 0x20, 0xDD};

static const ac_uint8 KS_KEK_PARENT_PROTECTED[] = {0x19, 0x99, 0x20, 0x10, 0x20, 0xCC};
static const ac_uint8 KS_KEKIV_PARENT_PROTECTED[] = {0x19, 0x99, 0x20, 0x10, 0x20, 0xDD};

static const ac_uint8 KS_KEK_DERIVED[] = {0x19, 0x99, 0x20, 0x10, 0x21, 0xCC};
static const ac_uint8 KS_KEKIV_DERIVED[] = {0x19, 0x99, 0x20, 0x10, 0x21, 0xDD};

static const ac_uint8 KS_KEK_NODELOCK[] = {0x19, 0x99, 0x20, 0x10, 0x25, 0xCC};
static const ac_uint8 KS_KEKIV_NODELOCK[] = {0x19, 0x99, 0x20, 0x10, 0x25, 0xDD};

static const ac_uint8 KS_KEK_SUBORDINATE_NAME[] = {0x19, 0x99, 0x20, 0x10, 0x20, 0xEE};

static const ac_uint8 KS_Voucher_ID[] = {0x19, 0x61, 0x19, 0x69, 0x20, 0x10};
static const ac_uint8 KS_IV_Vouchers_ID[] = {0x19, 0x84, 0x20, 0x01, 0x19, 0x99};
static const ac_uint8 KS_IV_Modules_ID[] = {0x19, 0x99, 0x20, 0x10, 0x20, 0x01};

static const ac_uint8 KS_PARENT_SIGNATURE[] = {0x19, 0x14, 0x23, 0x34, 0x19, 0x99};
static const ac_uint8  KS_NODELOCK_MOFN_TAB[] = { 0x19, 0x44, 0x33, 0x34, 0x19, 0x88 };
#endif

/****
 * Needed to allow inlining of CAST_TO_ac_SS_Data_Handle
 * and CAST_TO_RKM_KeyInfo_PTR
 ****/
#define BUFFER_SIZE 0x7AAAAAAA>>2
typedef struct _offset_obj {
    ac_uint32 buffer[BUFFER_SIZE];
} OFFSET_Struct;

_xc_must_inline
ac_SS_Data_Handle CAST_TO_ac_SS_Data_Handle(RKM_KeyInfo *keyInfo);

_xc_must_inline
RKM_KeyInfo* CAST_TO_RKM_KeyInfo_PTR(ac_SS_Data_Handle handle);


ac_Status _SetDataByID(ac_SS_Context   context,
                        const ac_uint8  *id,
                        const ac_uint32 idLength,
                        ac_Bytes        data,
                        ac_Data_Type    keyType,
                        ac_uint32       keyAttrib);

ac_Status _GetDataByID(ac_SS_Context   context,
                        const ac_uint8  *id,
                        const ac_uint32 idLength,
                        ac_Data_Type    *pKeyType,
                        ac_Bytes        *data);

ac_Status ac_AppendToSecureStore(ac_SS_Context     context,
                                   ac_SS_Data_Handle dataHandle,
                                   ac_uint8          *pData,
                                   ac_uint32         dataSize);

ac_Status _ac_SaveSecureStoreToBuffer(ac_SS_Context  ss_context, 
                                        ac_Bytes      *pSSdata);

ac_PUBLIC_API(iac_SecureCompare)(ac_SS_Context     context,
		                           ac_uint8*         buffer,
		                           ac_uint32         length,
		                           ac_SS_Data_Handle keyHandle);

ac_PUBLIC_API(iac_SecureCompareFragment)(ac_SS_Context     context,
		                                   ac_uint8*         buffer,
		                                   ac_uint32         length,
		                                   ac_uint32            offset,
		                                   ac_SS_Data_Handle keyHandle);

ac_PUBLIC_API(iac_ComputePublicKey)(ac_SS_Context     context,
		                              ac_SS_Data_Handle keyHandle,
		                              ac_uint8 *        pubKey,
		                              ac_uint32 *       pPubKeySize);

ac_PUBLIC_API(iac_CreateSymmetricKeyAndStoreInSecureStoreByID)(ac_SS_Context context,
                                                        ac_Data_Type  newKeyType,
                                                        ac_uint8 *    id,
                                                        ac_uint32     idLength,
                                                        ac_SS_Data_Handle* pKeyHandle);
												 
ac_PUBLIC_API(iac_CreateAsymmetricKeyAndStoreInSecureStoreByID)(ac_SS_Context context,
                                                         ac_Data_Type  newKeyType,
                                                         ac_uint8 *    priId,
                                                         ac_uint8 *    pubId,
                                                         ac_uint32     priIdLength,
                                                         ac_uint32     pubIdLength,
                                                         ac_SS_Data_Handle* pPriKeyHandle,
                                                         ac_SS_Data_Handle* pPubKeyHandle);

ac_PUBLIC_API(iac_FreeIterator)(ac_SS_Iterator iterator);

ac_PUBLIC_ITERATOR_API(iac_GetIterator)(ac_SS_Context context);

ac_PUBLIC_DATA_HANDLE_API(iac_GetNext)(ac_SS_Iterator iterator);

ac_PUBLIC_API(iac_HasNext)(ac_SS_Iterator iterator);

/*ac_PUBLIC_API(iac_SecureCounterCreate)( ac_SS_Context      ss_context, 
                                          ac_uint8          *id, 
                                          ac_uint32          idLength, 
                                          ac_SS_Data_Handle *pDataHandle, 
                                          ac_uint32          SCLengthInBytes, 
                                          ac_uint8          *pBufSCInitValue, 
                                          ac_uint8          *pBufSCMaxValue );

ac_PUBLIC_API(iac_SecureCounterIncrement)( ac_SS_Context     ss_context, 
                                             ac_SS_Data_Handle dataHandle );

ac_PUBLIC_API(iac_SecureCounterReset)( ac_SS_Context      ss_context, 
                                         ac_SS_Data_Handle  dataHandle, 
                                         ac_uint8          *pBufSCResetValue,
                                         ac_uint32          bufLength );
*/

#ifdef __cplusplus
}
#endif

#endif /* __ac_SECURESTORE_INTERNAL_H__ */


/* RISO Converted */
