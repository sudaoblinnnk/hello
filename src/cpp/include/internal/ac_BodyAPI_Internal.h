/** \defgroup ac_Crypto Irdeto ActiveCloak Cryptographic component */
/* @{ */

/*  ---------------------------------------------------------------------------- */
/*! \file ac_BodyAPI_Internal.h
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


#ifndef __ac_BODYAPI_INTERNAL_H__
#define __ac_BODYAPI_INTERNAL_H__

/* API parameter transform apply/CW_remove macros
ac_XFORM_CAST
ac_APPLY_XFORM_TO_COPY
ac_REMOVE_XFORM_FROM_COPY

ac_APPLY_XFORM_INPLACE
ac_REMOVE_XFORM_INPLACE
*/
#define ac_XFORM_CAST(in, xformtype, type) _xc_transformcast(_xc_transformtype(xformtype) type*) (in)

#define ac_APPLY_XFORM_TO_COPY(out, in, length) \
{ \
        ac_uint32 ac_APPLY_XFORM_TO_COPY_index; \
        for (ac_APPLY_XFORM_TO_COPY_index = 0; ac_APPLY_XFORM_TO_COPY_index < (ac_uint32)(length); ac_APPLY_XFORM_TO_COPY_index++) \
                (out)[ac_APPLY_XFORM_TO_COPY_index] = (in)[ac_APPLY_XFORM_TO_COPY_index]; \
}

#define ac_REMOVE_XFORM_FROM_COPY(out, in, length) \
{ \
        ac_uint32 ac_REMOVE_XFORM_FROM_COPY_index; \
        for (ac_REMOVE_XFORM_FROM_COPY_index = 0; ac_REMOVE_XFORM_FROM_COPY_index < (ac_uint32)(length); ac_REMOVE_XFORM_FROM_COPY_index++) \
                (out)[ac_REMOVE_XFORM_FROM_COPY_index] = (in)[ac_REMOVE_XFORM_FROM_COPY_index]; \
}

#include "ac_Common_Internal.h"
#include "ac_SecureStore.h"

#ifdef __cplusplus
extern "C" {
#endif

/***
 * agent_common.c
 ***/
ac_Status impl_InitializeFromBuffer(ac_Context      *pContext,
			ac_uint8         *buffer,
			ac_uint32	  bufferSize,
			ac_Init_Options *pOpts);

ac_PUBLIC_API(iac_InitializeFromBuffer)(ac_Context* pContext,
                                ac_uint8*    buffer,
                                ac_uint32    bufferSize,
                               ac_Init_Options* pOpts);

ac_Status impl_Initialize(ac_Context* pContext,
			ac_char*    acvFilename,
			ac_Init_Options* pOpts);

ac_PUBLIC_API(iac_Initialize)(ac_Context* pContext,
				ac_char*    acvFilename,
				ac_Init_Options* pOpts);

ac_Status impl_Shutdown(ac_Context *context);
ac_PUBLIC_API(iac_Shutdown)(ac_Context *context);

ac_PUBLIC_API(iac_Error_Detail)(ac_Context context);

/* impl  */
ac_Status impl_Initialize(ac_Context* pContext,
                          ac_char*    acvFilename,
                          ac_Init_Options* pOpts);

ac_Status impl_Shutdown(ac_Context *context);

ac_Status impl_Error_Detail(ac_Context context);





/***
 * IV_PublicAPI.c
 ***/
#if defined IV_ENABLED || defined PFIV_ENABLED
ac_PUBLIC_API(iac_IV_VerifySystem)(ac_SS_Context ss_context,
                                     void           *pDataHighSeverity,
                                     void           *pDataMediumSeverity);
ac_PUBLIC_API(iac_IV_VerifyOnDisk)(ac_SS_Context ss_context,
                                     void           *pDataHighSeverity,
                                     void           *pDataMediumSeverity);
ac_PUBLIC_API(iac_IV_VerifyInMemory)(ac_SS_Context ss_context,
                                     void           *pDataHighSeverity,
                                     void           *pDataMediumSeverity,
                                     ac_uint32      signatureCounts);
ac_PUBLIC_API(iac_IV_EnhancedZone_Enter)(ac_SS_Context ss_context);
ac_PUBLIC_API(iac_IV_EnhancedZone_Exit)(ac_SS_Context  ss_context);

/* impl  */

ac_Status impl_IV_VerifySystem(ac_SS_Context ss_context,
                                     void           *pDataHighSeverity,
                                     void           *pDataMediumSeverity);
ac_Status impl_IV_VerifyOnDisk(ac_SS_Context ss_context,
                                     void           *pDataHighSeverity,
                                     void           *pDataMediumSeverity);
ac_Status impl_IV_VerifyInMemory(ac_SS_Context ss_context,
                                     void           *pDataHighSeverity,
                                     void           *pDataMediumSeverity,
                                     ac_int        coveragePercent);

ac_Status impl_EnhancedZone_Enter(ac_SS_Context ss_context);

ac_Status impl_EnhancedZone_Enter(ac_SS_Context ss_context);


#endif

#ifdef JB_CHECKS_ENABLED
ac_PUBLIC_API(iac_JB_DetectSystem)(ac_SS_Context ss_context,
                                     void *         pData);
ac_PUBLIC_API(iac_MS_DetectSystem)(ac_SS_Context ss_context,
                                     void *         pData);
#endif

/***
 * ac_NL_PublicAPI.c
 ***/
ac_PUBLIC_API(iac_GenIndivRequest2)(ac_Context context, ac_Bytes* pNLdata);
ac_PUBLIC_API(iac_GenIndivRequestPFP)(ac_Context context, ac_Bytes* pNLdata);
ac_PUBLIC_API(iac_GenIndivRequestHWFP)(ac_Context context, ac_Bytes* pNLdata,
		ac_char assetType[256]);

ac_PUBLIC_API(iac_ProcessIndivResponse)(ac_Context context, ac_char* ssFileName, ac_Bytes nlSSblob);
ac_PUBLIC_API(iac_GetUniqueDeviceID)(ac_Context context, ac_uint8** pIDdata, ac_uint32* pIDdataSize);


/*  impl  */

ac_Status impl_GenIndivRequest(ac_Context context, ac_Bytes* pNLdata); 

ac_Status impl_ProcessIndivResponse(ac_Context context, ac_char* ssFileName, 					    ac_Bytes nlSSblob);

ac_Status impl_GetUniqueDeviceID(ac_Context context, ac_uint8** pIDdata, ac_uint32* pIDdataSize);

/***
 * ac_RKM_EncryptDecrypt.c
 ***/
ac_Status impl_DecryptData(ac_SS_Context     context,
                            ac_SS_Data_Handle keyHandle,
                            ac_uint8*         pCipherText,
                            ac_uint32         cipherTextSize,
                            ac_uint8*         pPlainText,
                            ac_uint32*        pPlainTextSize);
ac_PUBLIC_API(tac_DecryptData)(ac_SS_Context     context,
                            ac_SS_Data_Handle keyHandle,
                            ac_uint8*         pCipherText,
                            ac_uint32         cipherTextSize,
                            ac_uint8*         pPlainText,
                            ac_uint32*        pPlainTextSize);

ac_Status impl_EncryptData(ac_SS_Context     context,
                            ac_SS_Data_Handle keyHandle,
                            ac_uint8*         pPlainText,
                            ac_uint32         plainTextSize,
                            ac_uint8*         pCipherText,
                            ac_uint32*        pCipherTextSize);
ac_PUBLIC_API(tac_EncryptData)(ac_SS_Context     context,
                            ac_SS_Data_Handle keyHandle,
                            ac_uint8*         pPlainText,
                            ac_uint32         plainTextSize,
                            ac_uint8*         pCipherText,
                            ac_uint32*        pCipherTextSize);

/** new Cloaked CA APIs
**/
ac_Status impl_Crypto_Init(ac_SS_Context context,
                         ac_SS_Data_Handle keyHandle,
                         ac_SS_Data_Handle tableHandle,
                         ac_SS_Data_Handle * cryptoContextHandle);

ac_Status tac_Crypto_Init(ac_SS_Context context,
                         ac_SS_Data_Handle keyHandle,
                         ac_SS_Data_Handle tableHandle,
                         ac_SS_Data_Handle * cryptoContextHandle);

ac_Status impl_Crypto_Decrypt(ac_SS_Context context,
                             ac_SS_Data_Handle cryptoContextHandle,
                             ac_uint8* iv,
                             ac_uint32 ivSize,
                             ac_uint8 * cipher,
                             ac_uint32 cipherSize,
                             ac_uint8 * plain,
                             ac_uint32 * plainSize);

ac_Status tac_Crypto_Decrypt(ac_SS_Context context,
                             ac_SS_Data_Handle cryptoContextHandle,
                             ac_uint8* iv,
                             ac_uint32 ivSize,
                             ac_uint8* cipher,
                             ac_uint32 cipherSize,
                             ac_uint8 * plain,
                             ac_uint32 *plainSize);

ac_Status impl_Crypto_UpdateKey(ac_SS_Context context,
                               ac_SS_Data_Handle keyHandle,
                               ac_SS_Data_Handle * pContextHandle);

ac_Status tac_Crypto_UpdateKey(ac_SS_Context context,
                               ac_SS_Data_Handle keyHandle,
                               ac_SS_Data_Handle * pContextHandle);

ac_Status impl_Crypto_Delete(ac_SS_Context context,
                            ac_SS_Data_Handle *pContextHandle);

ac_Status tac_Crypto_Delete(ac_SS_Context context,
                            ac_SS_Data_Handle *pContextHandle);

ac_Status impl_Crypto_DeleteAll(ac_SS_Context context);

ac_Status tac_Crypto_DeleteAll(ac_SS_Context context);

ac_Status impl_EncryptDataWithRandomKeyService(ac_Context context,
                               ac_uint8 * pPlainText,
                               ac_uint32 plainTextSize,
                               ac_uint8 * pCipherText,
                               ac_uint32 * pCipherTextSize);

ac_Status impl_DecryptDataWithRandomKeyService(ac_Context context,
                               ac_uint8 * pCipherText,
                               ac_uint32 cipherTextSize,
                               ac_uint8 * pPlainText,
                               ac_uint32 * pPlainTextSize);

/***
 * ac_RKM_SignVerify.c
 ***/
ac_PUBLIC_API(iac_SignData)(ac_SS_Context     context,
                              ac_SS_Data_Handle keyHandle,
                              ac_uint8*         msg,
                              ac_uint32         msgSize,
                              ac_uint8*         sig,
                              ac_uint32*        pSigSize);

ac_PUBLIC_API(iac_VerifyData)(ac_SS_Context     context,
                               ac_SS_Data_Handle keyHandle,
                               ac_uint8*         msg,
                               ac_uint32         msgSize,
                               ac_uint8*         sig,
                               ac_uint32         sigSize);
/*  impl */ 


ac_Status impl_SignData(ac_SS_Context     context,
                              ac_SS_Data_Handle keyHandle,
                              ac_uint8*         msg,
                              ac_uint32         msgSize,
                              ac_uint8*         sig,
                              ac_uint32*        pSigSize);

/***
 * RKM_PublicAPI.c
 ***/

ac_Status impl_CreateSecureStore(ac_SS_Context* pSSContext, 
				ac_Context context, 
				ac_Create_SS_Options* opts);
ac_PUBLIC_API(iac_CreateSecureStore)(ac_SS_Context* pSSContext, 
				ac_Context context, 
				ac_Create_SS_Options* opts);

ac_PUBLIC_API(tac_StoreInSecureStore)(ac_SS_Context       context,
				_xc_transformtype(DABT11) ac_Data_Type keyType,
				_xc_transformtype(DABT12) ac_uint8 * pKeyData,
				_xc_transformtype(DABT13) ac_uint32 keyDataSize,
				ac_SS_Data_Handle *pKeyHandle);

ac_PUBLIC_API(iac_DecryptAndStoreInSecureStore)(ac_SS_Context       context,
                                                  ac_SS_Data_Handle   keyHandle,
                                                  ac_Data_Type        keyType,
                                                  ac_uint8*           pKeyData,
                                                  ac_uint32           keyDataSize,
                                                  ac_SS_Data_Handle * pNewKeyHandle);

ac_Status impl_Delete_All_HandlesInSecureStore(ac_SS_Context context, ac_Status fibStatus);
ac_PUBLIC_API(iac_Delete_All_HandlesInSecureStore)(ac_SS_Context context);

ac_PUBLIC_API(iac_RemoveHandleFromSecureStore)(ac_SS_Context     context,
                                                 ac_SS_Data_Handle keyHandle);

ac_Status impl_LoadSecureStore(ac_SS_Context* pSSContext, 
				ac_Context context, ac_char* pFileName);


ac_PUBLIC_API(iac_LoadSecureStoreFromBuffer)(ac_SS_Context *pSSContext,
                                               ac_Context     context,
                                               ac_uint8      *pBufferSS,
                                               ac_uint32      bufLength);

ac_PUBLIC_API(iac_LoadSecureStore)(ac_SS_Context* pSSContext,
				   ac_Context context,
				   ac_char* pFileName);

ac_Status impl_GetOption(ac_SS_Context     context,
                               ac_SS_Data_Handle keyHandle,
                               ac_uint8**        pData,
                               ac_uint32*        pDataLength,
                               ac_Set_Options    set);
ac_PUBLIC_API(iac_GetOption)(ac_SS_Context     context,
                               ac_SS_Data_Handle keyHandle,
                               ac_uint8**        pData,
                               ac_uint32*        pDataLength,
                               ac_Set_Options    set);

ac_PUBLIC_API(iac_ReplaceDataInSecureStore)(ac_SS_Context      context,
                                              ac_SS_Data_Handle  dataHandle,
                                              ac_uint8*          pData,
                                              ac_uint32          dataSize);

ac_PUBLIC_API(iac_SaveSecureStoreToFile)(ac_SS_Context context, ac_char* pFileName);

ac_PUBLIC_API(iac_SetOption)(ac_SS_Context     context,
                               ac_SS_Data_Handle keyHandle,
                               ac_uint8*         pData,
                               ac_uint32         dataLength,
                               ac_Set_Options    set);

ac_Status impl_GetHandleByID(ac_SS_Context      context,
                                   ac_uint8*          id,
                                   ac_uint32          idLength,
                                   ac_SS_Data_Handle* pKeyHandle);

ac_PUBLIC_API(iac_GetHandleByID)(ac_SS_Context      context,
                                   ac_uint8*          id,
                                   ac_uint32          idLength,
                                   ac_SS_Data_Handle* pKeyHandle);

ac_Status impl_GetDataLengthFromHandle(ac_SS_Context      context,
                                       ac_SS_Data_Handle  dataHandle,
                                       ac_uint32 * pDataSize);

ac_PUBLIC_API (iac_GetDataLengthFromHandle)(ac_SS_Context      context,
				       ac_SS_Data_Handle  dataHandle,
				       ac_uint32 * pDataSize);

ac_PUBLIC_API(tac_GetDataFromHandleNoAlloc)(ac_SS_Context      context,
                                       ac_SS_Data_Handle  dataHandle,
                                       _xc_transformtype(DABT2) ac_uint8* pData,
                                       _xc_transformtype(DABT3) ac_uint32* pDataSize);

ac_PUBLIC_ITERATOR_API(iac_GetIterator) (ac_SS_Context context);


ac_PUBLIC_API(iac_SecureCompareFragment)(ac_SS_Context context,
                                           ac_uint8* buffer,
                                           ac_uint32 length,
                                           ac_uint32 offset,
                                           ac_SS_Data_Handle keyHandle);
ac_Status impl_SecureCompareFragment(ac_SS_Context context,
                                           ac_uint8* buffer,
                                           ac_uint32 length,
                                           ac_uint32 offset,
                                           ac_SS_Data_Handle keyHandle);

ac_Status impl_SecureCompare(ac_SS_Context context,
                                   ac_uint8* buffer,
                                   ac_uint32 length,
                                   ac_SS_Data_Handle keyHandle);

ac_PUBLIC_API(iac_SecureCompare)(ac_SS_Context context,
                                   ac_uint8* buffer,
                                   ac_uint32 length,
                                   ac_SS_Data_Handle keyHandle);

ac_PUBLIC_API(iac_HasNext)(ac_SS_Iterator iterator);

ac_PUBLIC_DATA_HANDLE_API(iac_GetNext)(ac_SS_Iterator iterator);

ac_PUBLIC_API(iac_FreeIterator)(ac_SS_Iterator iterator);


ac_PUBLIC_API(iac_ConvertKeyType)(ac_SS_Context       context,
                                  ac_SS_Data_Handle * inputKeyHandle,
                                  ac_uint32           keyTypes,
                                  ac_SS_Data_Handle * newKeyHandle);

ac_Status impl_SecureCounterCreate( ac_SS_Context      ss_context,
                                          ac_uint8          *id,
                                          ac_uint32          idLength,
                                          ac_SS_Data_Handle *pDataHandle,
                                          ac_uint32          SCLengthInBytes,
                                          ac_uint8          *pBufSCInitValue,
                                          ac_uint8          *pBufSCMaxValue );
ac_PUBLIC_API(iac_SecureCounterCreate)( ac_SS_Context      ss_context,
                                          ac_uint8          *id,
                                          ac_uint32          idLength,
                                          ac_SS_Data_Handle *pDataHandle,
                                          ac_uint32          SCLengthInBytes,
                                          ac_uint8          *pBufSCInitValue,
                                          ac_uint8          *pBufSCMaxValue );


ac_Status impl_SecureCounterIncrement( ac_SS_Context     ss_context,
                                             ac_SS_Data_Handle dataHandle );
ac_PUBLIC_API(iac_SecureCounterIncrement)( ac_SS_Context     ss_context,
                                             ac_SS_Data_Handle dataHandle );

ac_PUBLIC_API(iac_SecureCounterReset)( ac_SS_Context      ss_context,
                                         ac_SS_Data_Handle  dataHandle,
                                         ac_uint8          *pBufSCResetValue,
                                         ac_uint32          bufLength );

ac_PUBLIC_API(iac_ComputePublicKey)(ac_SS_Context     context,
                                      ac_SS_Data_Handle keyHandle,
                                      ac_uint8 *        pubKey,
                                      ac_uint32 *       pPubKeySize);


/*  impl  */


ac_Status impl_SS_Shutdown(ac_SS_Context *context);

ac_Status impl_CreateSecureStore(ac_SS_Context* pSSContext, ac_Context context, ac_Create_SS_Options* opts);

ac_Status impl_StoreInSecureStore(ac_SS_Context      context,
                                  ac_Data_Type       dataType,
                                  ac_uint8 *         pData,
                                  ac_uint32          dataSize,
                                  ac_SS_Data_Handle* pDataHandle);

ac_Status impl_DecryptAndStoreInSecureStore(ac_SS_Context       context,
                                                  ac_SS_Data_Handle   keyHandle,
                                                  ac_Data_Type        keyType,
                                                  ac_uint8*           pKeyData,
                                                  ac_uint32           keyDataSize,
                                                  ac_SS_Data_Handle * pNewKeyHandle);

ac_Status impl_RemoveHandleFromSecureStore(ac_SS_Context     context,
                                           ac_SS_Data_Handle keyHandle);

ac_Status impl_LoadSecureStore(ac_SS_Context* pSSContext, ac_Context context, ac_char* pFileName);

ac_Status impl_LoadSecureStoreFromBuffer(ac_SS_Context *pSSContext,
                                         ac_Context     context,
                                         ac_uint8      *pBufferSS,
                                         ac_uint32      bufLength);

ac_Status impl_ReplaceDataInSecureStore(ac_SS_Context      context,
                                        ac_SS_Data_Handle  dataHandle,
                                        ac_uint8*          pData,
                                        ac_uint32          dataSize);

ac_Status impl_SaveSecureStoreToFile(ac_SS_Context context, ac_char* pFileName);

struct __ac_SS_Iterator *impl_GetIterator(ac_SS_Context context);

ac_Status impl_HasNext(ac_SS_Iterator iterator);

ac_SS_Data_Handle impl_GetNext(ac_SS_Iterator iterator);

ac_Status impl_FreeIterator(ac_SS_Iterator iterator);

ac_Status impl_SecureCounterCreate( ac_SS_Context      ss_context,
                                    ac_uint8          *id,
                                    ac_uint32          idLength,
                                    ac_SS_Data_Handle *pDataHandle,
                                    ac_uint32          SCLengthInBytes,
                                    ac_uint8          *pBufSCInitValue,
                                    ac_uint8          *pBufSCMaxValue );

ac_Status impl_SecureCounterIncrement( ac_SS_Context     ss_context,
                                       ac_SS_Data_Handle dataHandle );

ac_Status impl_SecureCounterReset(ac_SS_Context ss_context,
				  ac_SS_Data_Handle dataHandle,
				  ac_uint8 *pBufSCresetValue,
				  ac_uint32 bufLength); 

ac_Status impl_SetOption (ac_SS_Context     context,
			  ac_SS_Data_Handle keyHandle,
			  ac_uint8*          pData,
			  ac_uint32          dataLength,
			  ac_Set_Options    set);


ac_Status impl_GetDataFromHandleNoAlloc(ac_SS_Context context,
				 ac_SS_Data_Handle  dataHandle,
				 ac_uint8* pData,
				 ac_uint32* pDataSize);

ac_Status impl_Hash_Init(ac_SS_Context context,
			ac_Data_Type hashType,
			ac_Op_Context *pOperationContext);
			
ac_Status impl_Hash_Update(ac_SS_Context context,
			   ac_Op_Context operationContext,
			   ac_uint8*     pHashData,
			   ac_uint32     hashDataSize);
			   
ac_Status impl_Hash_Finalize(ac_SS_Context context,
			     ac_Op_Context operationContext,
			     ac_uint8 *pDigest);
				 
ac_Status impl_Hash_Finalize_And_Store(ac_SS_Context      context,
	      ac_Op_Context      operationContext,
	      ac_SS_Data_Handle* pDigestHandle);
		  
ac_Status impl_Hash_Compute(ac_SS_Context context,
			    ac_Data_Type  hashType,
			    ac_uint8*     pMessage,
			    ac_uint32     messageSize,
			    ac_uint8*     pDigest);
				
ac_Status impl_Hash_Compute_And_Store(ac_SS_Context      context,
					ac_Data_Type       hashType,
					ac_uint8*          pMessage,
					ac_uint32          messageSize,
					ac_SS_Data_Handle* pDigestHandle);
			
ac_Status impl_HMAC_Init(ac_SS_Context  context,
		       ac_Data_Type   hashType,
		       ac_uint8*      pKeyData,
		       ac_uint32      keyDataSize,
		       ac_Op_Context* pOperationContext);
			   
ac_Status impl_HMAC_Init_From_Store(ac_SS_Context     context,
		                    ac_Data_Type      hashType,
		                    ac_SS_Data_Handle keyHandle,
		                    ac_Op_Context*    pOperationContext);

ac_Status impl_HMAC_Update(ac_SS_Context context,
			   ac_Op_Context operationContext,
		  	   ac_uint8*     pHashData,
			   ac_uint32     hashDataSize);
			   
ac_Status impl_HMAC_Finalize (ac_SS_Context context,
			      ac_Op_Context operationContext,
			      ac_uint8 *pDigest);
				  
ac_Status impl_HMAC_Finalize_And_Store(ac_SS_Context      context,
		                       ac_Op_Context      operationContext,
		                       ac_SS_Data_Handle* pDigestHandle);
							   
ac_Status impl_HMAC_Compute(ac_SS_Context context, 
			    ac_Data_Type  hashType,
			    ac_uint8*     pKeyData,
			    ac_uint32     keySize,
			    ac_uint8*     pMessage,
			    ac_uint32     messageSize,
			    ac_uint8*     pDigest);
				
ac_Status impl_HMAC_Compute_And_Store(ac_SS_Context      context,
		                      ac_Data_Type       hashType,
		                      ac_uint8*          pKeyData,
		                      ac_uint32          keyDataSize,
		                      ac_uint8*          pMessage,
		                      ac_uint32          messageSize,
		                      ac_SS_Data_Handle* pDigestHandle);

ac_Status impl_ConvertKeyType(ac_SS_Context       context,
                              ac_SS_Data_Handle * inputKeyHandle,
                              ac_uint32           keyTypes,
                              ac_SS_Data_Handle * newKeyHandle);
/*  end of RKM impl  */

#ifdef __cplusplus
}
#endif

#endif /* __ac_BODYAPI_INTERNAL_H__ */

/* RISO Converted */

