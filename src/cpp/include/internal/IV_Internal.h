/** \defgroup ac_IV Irdeto ActiveCloak Integrity Verification component */
/* @{ */

/* ----------------------------------------------------------------------------*/
/*! \file ac_IV_Internal.h
   Irdeto Canada Corporation

   FILE: ac_IV_Internal.h
   The software and information contained in this package (“Software”) 
   is owned by Irdeto Canada Corporation, its affiliates or licensors 
   (“Software Owners”). The Software is protected by U.S., Canadian, 
   and international intellectual property laws and treaties and may 
   contain patents, trademarks, copyrights, or other intellectual 
   property rights of the Software Owners. If you acquired this package 
   without an appropriate agreement, please contact Irdeto Canada Corporation at:

     phone +1 613 271 9446, email: info@irdeto.com

   The furnishing of this package does not constitute a license, express 
   or implied, by estoppel or otherwise, to any patents, trademarks, copyrights, 
   or other intellectual property rights of the Software Owners. Use of the Software 
   without an appropriate agreement may constitute an infringement of the Software 
   Owners’ intellectual property rights and could subject you to legal action. 

   \brief The private IV-related definitions and function prototypes for the
          ActiveCloak Integrity Verification component.

   Limitations: None

   Thread Safe: Supported via 1 context per thread

   Platform Dependencies: CSS Version 5.1 or newer (i.e., Platform/OS/CSS version)

   Compiler Options:
*/


#ifndef __IV_INTERNAL_H__
#define __IV_INTERNAL_H__

#include "xc/xc_extensions.h"
#include "otsc_iv.h"

#include "xc/xc_pfiv.h"

#ifdef TBAD_CHECK_ENABLED
#include "xc/xc_adb.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef DEBUG

#ifdef FPRINTF
extern XC_FILE *logFile;
#define OUTFILE     logFile,
#define DBG_PRINTF(args) {XC_fprintf args; XC_fflush(0);}
#else
#define OUTFILE
#define DBG_PRINTF(args) {XC_printf args; XC_fflush(0);}
#endif


#else /* Do nothing */
#define DBG_PRINTF(args)
#endif

/*!
<B>Description:</B>
    Enumerated list of IV failure severity levels.
*/
#define  IV_DEV_DISK          1
#define  IV_DEV_MEMORY        2

#define  IV_DATA_HOST         0x100
#define  IV_DATA_FOREIGN      0x101
#define  IV_DATA_EXTERNAL     0x102
#define  IV_DATA_THIRD_PARTY  0x103

/* Mask and shift to return IV + XC error code to the public caller */
/* JB errors are for reference only */
#define JB_ERROR_SET_MASK               0x80000000
#define IV_ERROR_SET_MASK               0x40000000
#define AC_ERROR_SET_MASK               0xFFFF8000
#define XC_ERROR_SET_MASK               0xC0007FFF

#define XC_ERROR_SHIFT                  15
#define JB_ERROR_RIGHT_SHIFT            31
#define IV_ERROR_RIGHT_SHIFT            30

#define AC_ERROR_EXTRACT_MASK           0x7FFF
#define XC_ERROR_EXTRACT_MASK           0x3FFF8000
#define JB_ERROR_EXTRACT_MASK           0x80000000
#define IV_ERROR_EXTRACT_MASK           0x40000000

#define SET_RETURN_ERROR(ivValue, xcValue)     ((ivValue) | ((xcValue) <<XC_ERROR_SHIFT))
#define EXTRACT_XC_ERROR(combo)           (((((combo) & XC_ERROR_EXTRACT_MASK)) >> (XC_ERROR_SHIFT))) /*!< XC fail extract error code*/
#define EXTRACT_AC_ERROR(combo)           ((combo) & AC_ERROR_EXTRACT_MASK)/*!< AC fail extract error code*/
#define EXTRACT_IV_FAIL_DETECTED(combo)  ((((combo) & IV_ERROR_EXTRACT_MASK)) ? IV_ERROR_IV : IV_OK) 	   /*!< IV fail extract error code*/
#define EXTRACT_JB_FAIL_DETECTED(Status)      (((Status & JB_ERROR_EXTRACT_MASK) >> JB_ERROR_RIGHT_SHIFT) ? IV_ERROR_JB_DETECTED : IV_OK)  /*!< JB fail extract error code*/

/* Create masks to fetch SL and level information from SS*/
#define MASK_SL        ((uint32_t) 0x80000000)

/* Number of IV status bytes */
#define IV_NUM_STATUS_BYTES 16

#ifdef TBAD_CHECK_ENABLED
#define INIT_IV_CID_1  0
#define INIT_IV_CID_2  1
#define INIT_IV_VID_1  0

#define INIT_IV_C_DELTA_EXPECTED_1  1000
#define INIT_IV_C_DELTA_EXPECTED_2  2000
#define INIT_IV_C_DELTA_MAX_1       3000  /* All times in millisecs */
#define INIT_IV_C_DELTA_MAX_2       2000
#define INIT_IV_V_DELTA_MAX_1       3000

/* Verify IV TBAD (inner loop) required constants */
#define VERIFY_IVI_CID_1  0
#define VERIFY_IVI_VID_1  0

#define VERIFY_IVI_C_DELTA_EXPECTED_1  3000
#define VERIFY_IVI_C_DELTA_MAX_1       3500  /* All times in millisecs */
#define VERIFY_IVI_V_DELTA_MAX_1       4000

/* Verify IV TBAD (global outer loop) required constants */
#define NUM_VERIFY_IV_COLLECTIONS 2

#define VERIFY_IV_CID_1  0
#define VERIFY_IV_CID_2  1
#define VERIFY_IV_VID_1  0

#define VERIFY_IV_C_DELTA_EXPECTED_1  2000
#define VERIFY_IV_C_DELTA_EXPECTED_2  3000
#define VERIFY_IV_C_DELTA_MAX_1       2500  /* All times in millisecs */
#define VERIFY_IV_C_DELTA_MAX_2       3500
#define VERIFY_IV_V_DELTA_MAX_1       3000
#define VERIFY_IV_V_DELTA_MAX_2       4000

#endif

#include "IV_Internal2.h"

typedef struct  {
    uint32_t              failureIV;                      /*!< Set if fail cb is called */
    uint32_t              *ivByte;                        /*!< IV byte check count. */
} IV_Check;

#define XFORM_CAST(in, xformtype, type) _xc_transformcast(_xc_transformtype(xformtype) type*) (in)
#ifdef __cplusplus
}
#endif 

#endif /* __IV_INTERNAL_H__ */

