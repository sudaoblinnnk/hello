/** \defgroup ac_FP Irdeto ActiveCloak File Poisoning component */
/* @{ */

// ----------------------------------------------------------------------------
/*! \file ac_FP_Internal.h
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
  
   \brief The private definitions and function prototypes for the
          Irdeto ActiveCloak File Poisoning Core component.   
          
   Limitations:
  
   Thread Safe: Supported via 1 context per thread
  
   Platform Dependencies: OpenKode ARM CSS Version 9

   Compiler Options: gcc 4.3 for openkode arm
*/  


#ifndef __ac_FP_INTERNAL_H__
#define __ac_FP_INTERNAL_H__

//#include "xc/xc_extensions.h"

#include "ac_types.h"
#include "ac_Common_Internal.h"
#include "ac_SecureStore_Internal.h"
#include "ac_SecureStore.h"

/* file poisoning transform types */
#define  ac_FP_TYPE_XOR           1
#define  ac_FP_TYPE_HASH          2
#define  ac_FP_TYPE_SPARSE        3
#define  ac_FP_TYPE_PERIODIC      4
#define  ac_FP_TYPE_DATA          5

/* for the file poisoning remove functions table */
#define  ac_FP_REMOVE_FUNC_MAX    8

typedef ac_Status (*ac_REMOVE_FUNCTION_t) (ac_uint8 * pData, ac_uint32 dataLength); 

extern  ac_uint32            ac_detox_function_table_size; 
extern  ac_REMOVE_FUNCTION_t ac_detox_function_table[ac_FP_REMOVE_FUNC_MAX];


#ifdef __cplusplus
extern "C" {
#endif

/* file poisoning transformation functions prototypes, put here for integration test purposes, 
   these functions will be replaced by script-generated h and c modules 
*/

ac_Status ac_apply_hash_t_transform (
    ac_uint8 * pData,
    ac_uint32  dataLength,
    ac_uint32  period,
    ac_uint8 * pKey,
    ac_uint32  keyLength);

ac_Status ac_apply_periodic_t_transform (
    ac_uint8 * pData,
    ac_uint32  dataLength,
    ac_uint32  period,
    ac_uint8 * pKey,
    ac_uint32  keyLength);

ac_Status ac_apply_sparse_t_transform (
    ac_uint8 * pData,
    ac_uint32  dataLength,
    ac_uint32  period,
    ac_uint8 * pKey,
    ac_uint32  keyLength);

ac_Status ac_apply_xor_t_transform (
    ac_uint8 * pData,
    ac_uint32  dataLength,
    ac_uint8 * pKey,
    ac_uint32  keyLength);


/* file poisoning removal functions have the parameters baked in, these for initial testing only, will be replaced */
ac_Status ac_remove_hash_transform (
    ac_uint8 * pData,
    ac_uint32  dataLength);

ac_Status ac_remove_periodic_transform (
    ac_uint8 * pData,
    ac_uint32  dataLength);

ac_Status ac_remove_sparse_transform (
    ac_uint8 * pData,
    ac_uint32  dataLength);

ac_Status ac_remove_xor_transform (
    ac_uint8 * pData,
    ac_uint32  dataLength);


  /*******************************************************************************/


ac_Status ac_FP_PoisonData( ac_uint8   fpType,
                              ac_uint32  period,
                              ac_uint8*  pData,
                              ac_uint32  dataLength,
                              ac_uint8*  pKey,
                              ac_uint32  keyLength );

ac_Status ac_FP_DePoisonData( ac_uint8   tIndex,
                                ac_uint8  *pData,
                                ac_uint32  dataLength );

ac_Status ac_FP_AppendData(ac_Context          context,
                             ac_SS_Data_Handle * pKeyHandle,
                             ac_uint8 *          ID,
                             ac_int32            idLength,
                             ac_uint8 *          pData,
                             ac_int32            dataSize);

ac_Status ac_FP_CreateRecord(ac_Context   context,
                               ac_char*     fpDataName);

ac_Status ac_FP_AppendRecord(ac_Context          context,
                               ac_SS_Data_Handle  *pKeyHandle,
                               ac_Bytes            keyID,
			       ac_Bytes            recBytes);

ac_Status ac_FP_SetDpFuncTable( void );
ac_Status ac_FP_GetDpFuncTable( void );
ac_Status ac_FP_GetDpFuncPtr( ac_uint8 index, ac_uint32 *dpFuncPtr );

#ifdef __cplusplus
}

#endif
#endif /* __ac_FP_INTERNAL_H__ */
