/** \defgroup ac_General Irdeto ActiveCloak Common components */
/* @{ */

/*! \file ac_Common_Internal.h
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
          Initialization and Cleanup of Irdeto's ActiveCloak Agent.

   Description: Public Header file for Irdeto's ActiveCloak common components of ActiveCloak project.
                This file contains the defined types and the public application programming
                interface (API) definitions for the common components.

   Limitations: None

   Thread Safe: Supported via 1 context per thread

   Platform Dependencies: CSS Version 5.1 or newer      (i.e.: Platform/OS/CSS version)

   Compiler Options:
*/

#ifndef __ac_COMMON_INTERNAL_H__
#define __ac_COMMON_INTERNAL_H__

#define NCV_VALUE       1

#define ac_PUBLIC_TYPED_API(name,type)  extern type name

#define ac_PUBLIC_API(name) ac_PUBLIC_TYPED_API(name, ac_Status)

#define ac_PUBLIC_ITERATOR_API(name) ac_PUBLIC_TYPED_API(name, ac_SS_Iterator)

#define ac_PUBLIC_DATA_HANDLE_API(name) ac_PUBLIC_TYPED_API(name, ac_SS_Data_Handle)

#include "ac_common.h"

#ifdef USE_OTSC_PFIV		/* Not using the IV is in the OTSC */
#include "ac_IV_Internal.h"
#endif /* USE_OTSC_PFIV */


#include "ac_types.h"
//#include "ac_riso_pragmas.h"
#include "xc/xc_errors.h"
#include "xc/xc_extensions.h"
#include "CUtils.h"

#ifdef TBAD_CHECK_ENABLED
#include "xc/xc_adb.h"
#ifdef USE_OTSC_PFIV		/* Using the IV is in the OTSC */
#include "otsc_iv.h"
#endif /* USE_OTSC_PFIV */
#include "ac_TBAD_Internal.h"
#endif

#ifdef __cplusplus
extern "C"
{
#endif

#define  RANDOMIZE_RETURN_CODE() AC_FAIL

#ifndef CUSTOMER_DATA_LENGTH
#define CUSTOMER_DATA_LENGTH 32
#endif

#ifdef GLOBAL_CONTEXT_ENABLED
  extern ac_Context ac_GetGlobalContext (void);
#endif

#define ac_MAX_SS_FILENAME 256

/* Opaque structures for ActiveCloak Agent context data */
  typedef struct __RKM_Context *RKM_Context;
#if defined IV_ENABLED || defined PFIV_ENABLED
#ifndef USE_OTSC_PFIV		/* Not using the IV is in the OTSC */
  typedef struct __IV_Context *IV_Context;
#endif				/* USE_OTSC_PFIV */
#endif

#if defined JB_ENABLED
  typedef struct __JB_Context *JB_Context;
#endif

  struct __ac_Context
  {
    ac_Context parentContext;
#if defined IV_ENABLED || defined PFIV_ENABLED
#ifndef USE_OTSC_PFIV		/* Not using the IV is in the OTSC */
    IV_Context iv_context;
#else				/* is USE_OTSC_PFIV */
    IV_Handle iv_Handle;	/*!< IV handle */
    uint32_t ivRC;
#endif				/* USE_OTSC_PFIV */
#endif				/* IV_ENABLED || defined PFIV_ENABLED */
#if defined JB_ENABLED
    JB_Context jb_context;
#endif
#if defined PFIV_ENABLED && defined IVTHREAD_ENABLED
    void *threadContext;
#endif
    ac_uint32 ac_Error_Status;
    ac_uint32 XC_Error_Status;
    ac_uint32 JB_Error_Status;
    ac_uint32 IV_Error_Status;

    ac_uint8 *customer_data;
    ac_uint32 detail_error;
    ac_uint32 compare_state;
    ac_uint32 isSigned;
    ac_uint32 nldCount;
    ac_Bytes *nldList;
    ac_SS_Data_Handle rkey_service;
#ifdef TBAD_CHECK_ENABLED
#if defined IV_ENABLED || PFIV_ENABLED
    XC_ADBTS_DataPointStruct tbad_initializeIV[NUM_INIT_IV_COLLECTIONS];
    XC_ADBTS_DataPointStruct tbad_verifyIV[NUM_VERIFY_IV_COLLECTIONS];
#endif				/* IV_ENABLED */

    /* Add more tbad data structs based upon the enabled features */

#endif				/* TBAD_CHECK_ENABLED */

    ac_uint32 ac_initMallocBytes;
    ac_uint8 *modulesData;
    ac_uint32 modulesDataSize;
#ifdef USE_OTSC_PFIV		/* Not using the IV is in the OTSC */
    RKM_IV_ModuleData *moduleList;
    ac_uint32 moduleCount;
    XC_V_Handle_t voucherHandle;	/* Voucher handle to use multi-thread */
#endif
  };

#define DETAIL_ERROR(context, ret, detail)                \
    if (detail != XC_OK) {                                \
        context->securityContext->detail_error = detail;  \
        ret = (detail == XC_WB_ERR_INVALID_DATA_SIZE ? AC_ERROR_INVALID_DATA_SIZE : AC_ERROR_INTERNAL); \
        DBG_PRINTF(("\n!!! Error 0x%x, 0x%x [%s:%d] !!!\n\n", ret, detail, __FILE__, __LINE__)); \
        goto return_exit;                                 \
    }

#define DETAIL_ERROR_AC_CONTEXT(context, ret, detail)                \
    if (detail != XC_OK) {                                \
        context->detail_error = detail;  \
        ret = (detail == XC_WB_ERR_INVALID_DATA_SIZE ? AC_ERROR_INVALID_DATA_SIZE : AC_ERROR_INTERNAL); \
        DBG_PRINTF(("\n!!! Error 0x%x, 0x%x [%s:%d] !!!\n\n", ret, detail, __FILE__, __LINE__)); \
        goto return_exit;                                 \
    }

#define AC_ERROR(ret)     \
    if ((EXTRACT_AC_ERROR(ret)) != AC_OK) {   \
        DBG_PRINTF(("\n!!! Error 0x%x [%s:%d] !!!\n\n", ret, __FILE__, __LINE__)); \
        goto return_exit;  \
    }

#define ac_INVOKE(ret, apiName)  \
    if (ret != AC_OK) {          \
        DBG_PRINTF(("\n!!! Error 0x%x [%s:%d] invoking %s !!!\n\n", ret, __FILE__, __LINE__, apiName)); \
        goto return_exit;         \
    }



/*static void SET_JB_FAIL_DETECTED(ac_Status *Status)
{
	*Status |= JB_ERROR_SET_MASK;
}

static void SET_IV_FAIL_DETECTED(ac_Status *Status)
{
	*Status |= IV_ERROR_SET_MASK;
}

static void SET_XC_ERROR(ac_Status *StatusVal, ac_uint32 retValue)
{
	*StatusVal = ((*StatusVal & XC_ERROR_SET_MASK) | (retValue<<XC_ERROR_SHIFT));
}

static void SET_AC_ERROR(ac_Status *StatusVal, ac_uint32 retValue)
{
	*StatusVal = ((*StatusVal & AC_ERROR_SET_MASK) | retValue);
}

static void CLEAR_acJB_ERROR(ac_Status *status)
{
	if( (EXTRACT_AC_ERROR(*status) >= AC_ERROR_JB_DETECTED_LEVEL_ONE) && (EXTRACT_AC_ERROR(*status) <= AC_ERROR_JB_DETECTED_LEVEL_THREE) )	
       	*status &= AC_ERROR_SET_MASK;	
}

static void RESET_ERROR_MASK(ac_Status *Status)
{
	*Status = 0x00000000;
}
*/
#ifndef IS_AGENT
#define UNREFERENCED_AC_PARAM(x) (void)x
#endif

  void SET_JB_FAIL_DETECTED (ac_Status * Status);
  void SET_IV_FAIL_DETECTED (ac_Status * Status);
  void SET_XC_ERROR (ac_Status * StatusVal, ac_uint32 retValue);
  void SET_AC_ERROR (ac_Status * StatusVal, ac_uint32 retValue);
  void CLEAR_acJB_ERROR (ac_Status * status);
  void RESET_ERROR_MASK (ac_Status * Status);

  void CLEAR_JB_ERROR_CONTEXT (ac_Context context);
  void SET_JB_ERROR_CONTEXT (ac_Context context);
  void SET_IV_ERROR_CONTEXT (ac_Context context);
  void SET_XC_ERROR_CONTEXT (ac_Context context, ac_Status XC_Status,
			     ac_Status retVal);
  void SET_AC_ERROR_CONTEXT (ac_Context context, ac_uint32 AC_StatusVar);
  void SET_ERROR_RETURN_CODE (ac_Context context, ac_Status * retValue);
  void RESET_CONTEXT_ERROR_RETURN_CODES (ac_Context context);

#ifdef __cplusplus
}
#endif

#endif				/* __ac_COMMON_INTERNAL_H__ */
/* RISO Converted */
