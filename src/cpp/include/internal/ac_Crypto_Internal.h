/** \defgroup ac_Crypto Cryptographic Component */
/* @{ */

/*  ---------------------------------------------------------------------------- */
/*! \file ac_Crypto_Internal.h
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


#ifndef __ac_CRYPTO_INTERNAL_H__
#define __ac_CRYPTO_INTERNAL_H__

#include "ac_types.h"
#include "ac_common.h"
#include "ac_SecureStore_Internal.h"
#include "ac_SecureCounter_Internal.h"
#include "ac_Common_Internal.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "../feature_based/ac_Crypto-Encrypt.h"
#include "../feature_based/ac_Crypto-Decrypt.h"
#include "../feature_based/ac_Crypto-Sign.h"
#include "../feature_based/ac_Crypto-Verify.h"
#include "../feature_based/ac_Crypto-Hash.h"
#include "../feature_based/ac_Crypto-HMAC.h"

#ifdef __cplusplus
}
#endif

#endif /* __ac_CRYPTO_INTERNAL_H__ */

/*!
* Compute a complete Hash of an entire message in one pass.  Provided as a convenience on top of the other layers.
*
* @param[in] context Handle for the thread context that keeps track of data structures that need to be thread safe
* @param[in] hashType Type of hash to be computed (SHA1 and SHA2-256 currently supported).
* @param[in] pMessage Pointer to the message to be HMACed.
* @param[in] messageSize Length in bytes of the message to be hashed.
* @param[out] pDigest Pointer to the output digest (must accomodate the output length of the hash (20 or 32 bytes respectively).
  @return               Return value is an enumeration type indicating 
                        success/failure-type for the operation.
                        Possible return values include:
                        - AC_OK
                        - AC_ERROR_NULL_CONTEXT
                        - AC_ERROR_INVALID_HASHTYPE
                        - AC_ERROR_NULL_INPUT_POINTER
                        - AC_ERROR_INVALID_DATA_SIZE
                        - AC_ERROR_INTERNAL
                        - AC_ERROR_HEAP_ALLOCATION_FAILED
*/
ac_PUBLIC_API(iac_Hash_Compute)( ac_SS_Context  context,
		                           ac_Data_Type   hashType,
		                           ac_uint8*      pMessage,
		                           ac_uint32      messageSize,
		                           ac_uint8*      pDigest);
/*!
* Compute a complete Hash of an entire message in one pass.  Provided as a convenience on top of the other layers.
*
* @param[in] context Handle for the thread context that keeps track of data structures that need to be thread safe
* @param[in] hashType Type of hash to be computed (SHA1 and SHA2-256 currently supported).
* @param[in] pMessage Pointer to the message to be hashed.
* @param[in] messageSize Length in bytes of the message to be hashed.
* @param[out] pDigestHandle Pointer to a Secure Store handle where the digest has been stored.
  @return               Return value is an enumeration type indicating 
                        success/failure-type for the operation.
                        Possible return values include:
                        - AC_OK
                        - AC_ERROR_NULL_CONTEXT
                        - AC_ERROR_INVALID_HASHTYPE
                        - AC_ERROR_NULL_INPUT_POINTER
                        - AC_ERROR_INVALID_DATA_SIZE
                        - AC_ERROR_INTERNAL
                        - AC_ERROR_INVALID_DATA_HANDLE
                        - AC_ERROR_HEAP_ALLOCATION_FAILED
*/
ac_PUBLIC_API(iac_Hash_Compute_And_Store)( ac_SS_Context      context,
		                                     ac_Data_Type       hashType,
		                                     ac_uint8*          pMessage,
		                                     ac_uint32          messageSize,
		                                     ac_SS_Data_Handle* pDigestHandle);
/*!
* Initialize a Hash Context for later use.
*
* @param[in] context Handle for the thread context that keeps track of data structures that need to be thread safe
* @param[in] hashType Type of hash to be computed (SHA1 and SHA2-256 currently supported).
* @param[out] pOperationContext Pointer to a context created for the operation, used to hold the scheduled key and other cipher data.
  @return               Return value is an enumeration type indicating 
                        success/failure-type for the operation.
                        Possible return values include:
                        - AC_OK
                        - AC_ERROR_NULL_CONTEXT
                        - AC_ERROR_NULL_INPUT_POINTER
                        - AC_ERROR_INVALID_DATA_SIZE
                        - AC_ERROR_INTERNAL
                        - AC_ERROR_INVALID_HASHTYPE
                        - AC_ERROR_HEAP_ALLOCATION_FAILED
*/

ac_PUBLIC_API(iac_Hash_Init)( ac_SS_Context   context,
                           	    ac_Data_Type    hashType,
                                ac_Op_Context*  pOperationContext);

ac_Status impl_Hash_Init( ac_SS_Context   context,
                           	    ac_Data_Type    hashType,
                                ac_Op_Context*  pOperationContext);
/*!
* Add data to the Hash Context
*
* @param[in] context Handle for the thread context that keeps track of data structures that need to be thread safe
* @param[in] operationContext Context for the operation, used to hold the intermediate data.
* @param[in] pMessage Pointer to the message to be hashed.
* @param[in] messageSize Length in bytes of the message to be hashed.
  @return               Return value is an enumeration type indicating 
                        success/failure-type for the operation.
                        Possible return values include:
                        - AC_OK
                        - AC_ERROR_NULL_CONTEXT
                        - AC_ERROR_NULL_OPERATION_CONTEXT
                        - AC_ERROR_NULL_INPUT_POINTER
                        - AC_ERROR_INVALID_DATA_SIZE
                        - AC_ERROR_INTERNAL
                        - AC_ERROR_INVALID_HASHTYPE
                        - AC_ERROR_HEAP_ALLOCATION_FAILED
*/
ac_PUBLIC_API(iac_Hash_Update)( ac_SS_Context  context,
		                          ac_Op_Context  operationContext,
		                          ac_uint8*      pMessage,
		                          ac_uint32      messageSize);

/*!
* Complete the computation of a message digest.
*
* @param[in] context Handle for the thread context that keeps track of data structures that need to be thread safe
* @param[in] operationContext Context for the operation, used to hold the intermediate data.
* @param[out] pDigest Pointer to the output digest (must accomodate the output length of the hash (20 or 32 bytes respectively).
  @return               Return value is an enumeration type indicating 
                        success/failure-type for the operation.
                        Possible return values include:
                        - AC_OK
                        - AC_ERROR_NULL_CONTEXT
                        - AC_ERROR_NULL_OPERATION_CONTEXT
                        - AC_ERROR_NULL_INPUT_POINTER
                        - AC_ERROR_INVALID_DATA_SIZE
                        - AC_ERROR_INTERNAL
                        - AC_ERROR_INVALID_HASHTYPE
                        - AC_ERROR_HEAP_ALLOCATION_FAILED
*/
ac_PUBLIC_API(iac_Hash_Finalize)( ac_SS_Context  context,
		                            ac_Op_Context  operationContext,
		                            ac_uint8*      pDigest);

/*!
* Complete the computation of a message digest.
*
* @param[in] context Handle for the thread context that keeps track of data structures that need to be thread safe
* @param[in] operationContext Context for the operation, used to hold the intermediate data.
* @param[out] pDigestHandle Pointer to a Secure Store handle where the digest has been stored.
  @return               Return value is an enumeration type indicating 
                        success/failure-type for the operation.
                        Possible return values include:
                        - AC_OK
                        - AC_ERROR_NULL_CONTEXT
                        - AC_ERROR_NULL_OPERATION_CONTEXT
                        - AC_ERROR_INVALID_HASHTYPE
                        - AC_ERROR_INVALID_DATA_SIZE
                        - AC_ERROR_INTERNAL
                        - AC_ERROR_INVALID_DATA_HANDLE
                        - AC_ERROR_HEAP_ALLOCATION_FAILED
*/
ac_PUBLIC_API(iac_Hash_Finalize_And_Store)( ac_SS_Context      context,
		                                      ac_Op_Context      operationContext,
		                                      ac_SS_Data_Handle* pDigestHandle);



/*!
* Compute a complete HMAC digest of an entire message in one pass.  It is the wrapper function that calls ac_HMAC_Init, 
* ac_HMAC_Update, and ac_HMAC_Finalize, provided as a convenience on top of the other layers.
*
* @param[in] context Handle for the thread context that keeps track of data structures that need to be thread safe
* @param[in] hashType Type of hash to be computed (SHA1 and SHA2-256 currently supported).
* @param[in] pKeyData Pointer to the HMAC key .
* @param[in] keySize Length in bytes of the key.
* @param[in] pMessage Pointer to the message to be HMACed.
* @param[in] messageSize Length in bytes of the message to be hashed.
* @param[out] pDigest Pointer to the output digest (must accomodate the output length of the hash (20 or 32 bytes respectively).
  @return               Return value is an enumeration type indicating 
                        success/failure-type for the operation.
                        Possible return values include:
                        - AC_OK
                        - AC_ERROR_NULL_CONTEXT
                        - AC_ERROR_NULL_OPERATION_CONTEXT
                        - AC_ERROR_NULL_INPUT_POINTER
                        - AC_ERROR_INVALID_DATA_SIZE
                        - AC_ERROR_HEAP_ALLOCATION_FAILED
*/
ac_PUBLIC_API(iac_HMAC_Compute)( ac_SS_Context  context,
		                           ac_Data_Type   hashType,
		                           ac_uint8*      pKeyData,
		                           ac_uint32      keySize,
		                           ac_uint8*      pMessage,
		                           ac_uint32      messageSize,
		                           ac_uint8*      pDigest);

/*!
* Compute a complete HMAC digest of an entire message in one pass and store the result in the Secure Store. 
* It is the wrapper function that calls ac_HMAC_Init, ac_HMAC_Update, and ac_HMAC_Finalize, provided 
* as a convenience on top of the other layers.
*
* @param[in] context Handle for the thread context that keeps track of data structures that need to be thread safe
* @param[in] hashType Type of hash to be computed (SHA1 and SHA2-256 currently supported).
* @param[in] pKeyData Pointer to the HMAC key .
* @param[in] keyDataSize Length in bytes of the key.
* @param[in] pMessage Pointer to the message to be HMACed.
* @param[in] messageSize Length in bytes of the message to be hashed.
* @param[out] pDigestHandle Pointer to a Secure Store handle where the digest has been stored.
  @return               Return value is an enumeration type indicating 
                        success/failure-type for the operation.
                        Possible return values include:
                        - AC_OK
                        - AC_ERROR_NULL_CONTEXT
                        - AC_ERROR_NULL_OPERATION_CONTEXT
                        - AC_ERROR_NULL_INPUT_POINTER
                        - AC_ERROR_INVALID_DATA_SIZE
                        - AC_ERROR_HEAP_ALLOCATION_FAILED
*/
ac_PUBLIC_API(iac_HMAC_Compute_And_Store)( ac_SS_Context      context,
		                                     ac_Data_Type       hashType,
		                                     ac_uint8*          pKeyData,
		                                     ac_uint32          keyDataSize,
		                                     ac_uint8*          pMessage,
		                                     ac_uint32          messageSize,
		                                     ac_SS_Data_Handle* pDigestHandle);

/*!
* Initialize an HMAC Context with the specified key and hash type.
*
* @param[in] context Handle for the thread context that keeps track of data structures that need to be thread safe
* @param[in] hashType Type of hash to be computed (SHA1 and SHA2-256 currently supported).
* @param[in] pKeyData Pointer to the HMAC key .
* @param[in] keyDataSize Length in bytes of the key.
* @param[out] pOperationContext Pointer to a context created for the operation, used to hold the scheduled key and other cipher data.
  @return               Return value is an enumeration type indicating 
                        success/failure-type for the operation.
                        Possible return values include:
                        - AC_OK
                        - AC_ERROR_NULL_CONTEXT
                        - AC_ERROR_NULL_OPERATION_CONTEXT
                        - AC_ERROR_NULL_INPUT_POINTER
                        - AC_ERROR_INVALID_DATA_SIZE
                        - AC_ERROR_HEAP_ALLOCATION_FAILED
*/
ac_PUBLIC_API(iac_HMAC_Init)( ac_SS_Context   context,
		                        ac_Data_Type    hashType,
		                        ac_uint8*       pKeyData,
		                        ac_uint32       keyDataSize,
		                        ac_Op_Context*  pOperationContext);


/*!
* Initialize an HMAC Context with the specified key (from the Secure Store) and hash type.
*
* @param[in] context Handle for the thread context that keeps track of data structures that need to be thread safe
* @param[in] hashType Type of hash to be computed (SHA1 and SHA2-256 currently supported).
* @param[in] keyHandle Pointer to a Secure Store handle where the digest has been stored.
* @param[out] pOperationContext Pointer to a context created for the operation, used to hold the scheduled key and other cipher data.
  @return               Return value is an enumeration type indicating 
                        success/failure-type for the operation.
                        Possible return values include:
                        - AC_OK
                        - AC_ERROR_NULL_CONTEXT
                        - AC_ERROR_NULL_OPERATION_CONTEXT
                        - AC_ERROR_NULL_INPUT_POINTER
                        - AC_ERROR_INVALID_DATA_SIZE
                        - AC_ERROR_HEAP_ALLOCATION_FAILED
*/
ac_PUBLIC_API(iac_HMAC_Init_From_Store)(ac_SS_Context     context,
		                                  ac_Data_Type      hashType,
		                                  ac_SS_Data_Handle keyHandle,
		                                  ac_Op_Context*    pOperationContext);
/*!
* Add Message data to an HMAC.
*
* @param[in] context Handle for the thread context that keeps track of data structures that need to be thread safe
* @param[in] operationContext Context for the operation, used to hold the intermediate data.
* @param[in] pMessage Pointer to the message to be HMACed.
* @param[in] messageSize Length in bytes of the message to be hashed.
  @return               Return value is an enumeration type indicating 
                        success/failure-type for the operation.
                        Possible return values include:
                        - AC_OK
                        - AC_ERROR_NULL_CONTEXT
                        - AC_ERROR_NULL_OPERATION_CONTEXT
                        - AC_ERROR_NULL_INPUT_POINTER
                        - AC_ERROR_INVALID_DATA_SIZE
                        - AC_ERROR_HEAP_ALLOCATION_FAILED
*/
ac_PUBLIC_API(iac_HMAC_Update)( ac_SS_Context  context,
		                          ac_Op_Context  operationContext,
		                          ac_uint8*      pMessage,
		                          ac_uint32      messageSize);


/*!
* Generate an HMAC digest value.
*
* @param[in] context Handle for the thread context that keeps track of data structures that need to be thread safe
* @param[in] operationContext Context for the operation, used to hold the intermediate data.
* @param[out] pDigest Pointer to the output digest (must accomodate the output length of the hash (20 or 32 bytes respectively).
  @return               Return value is an enumeration type indicating 
                        success/failure-type for the operation.
                        Possible return values include:
                        - AC_OK
                        - AC_ERROR_NULL_CONTEXT
                        - AC_ERROR_NULL_OPERATION_CONTEXT
                        - AC_ERROR_NULL_INPUT_POINTER
                        - AC_ERROR_INVALID_HASHTYPE
                        - AC_ERROR_HEAP_ALLOCATION_FAILED
*/
ac_PUBLIC_API(iac_HMAC_Finalize)( ac_SS_Context  context,
		                            ac_Op_Context  operationContext,
		                            ac_uint8*      pDigest);


/*!
* Generate an HMAC digest value and store it in the secure store.
*
* @param[in] context Handle for the thread context that keeps track of data structures that need to be thread safe
* @param[in] operationContext Context for the operation, used to hold the intermediate data.
* @param[out] pDigestHandle Pointer to a Secure Store handle where the digest has been stored.
  @return               Return value is an enumeration type indicating 
                        success/failure-type for the operation.
                        Possible return values include:
                        - AC_OK
                        - AC_ERROR_NULL_CONTEXT
                        - AC_ERROR_NULL_OPERATION_CONTEXT
                        - AC_ERROR_NULL_INPUT_POINTER
                        - AC_ERROR_INVALID_HASHTYPE
                        - AC_ERROR_HEAP_ALLOCATION_FAILED
*/
ac_PUBLIC_API(iac_HMAC_Finalize_And_Store)( ac_SS_Context      context,
		                                      ac_Op_Context      operationContext,
		                                      ac_SS_Data_Handle* pDigestHandle);

/* @} */
/* RISO Converted */
