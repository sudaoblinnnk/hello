/** \defgroup ac_TBAD Irdeto ActiveCloak Timing Based Anti-Debug component */
/* @{ */

/* ---------------------------------------------------------------------------- */
/*! \file ac_TBAD_Internal.h
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

   \brief The private TBAD-related definitions and function prototypes for the
          ActiveCloak timing-based anti-debug component.

   Limitations: None

   Thread Safe: Supported via 1 context per thread

   Platform Dependencies: CSS Version 5.1 or newer (i.e., Platform/OS/CSS version)

   Compiler Options:
*/


#ifndef __ac_TBAD_INTERNAL_H__
#define __ac_TBAD_INTERNAL_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Init IV TBAD required constants */
#define NUM_INIT_IV_COLLECTIONS 3

#define INIT_IV_CID_1  0
#define INIT_IV_CID_2  1
#define INIT_IV_CID_3  2
#define INIT_IV_VID_1  0

#define INIT_IV_C_DELTA_MAX_1       2000  /* All times in millisecs */
#define INIT_IV_C_DELTA_MAX_2       2000
#define INIT_IV_C_DELTA_MAX_3       5000
#define INIT_IV_C_DELTA_EXPECTED_1  1000
#define INIT_IV_C_DELTA_EXPECTED_2  1000
#define INIT_IV_C_DELTA_EXPECTED_3  2000
#define INIT_IV_V_DELTA_MAX_1       10000


/* Verify IV TBAD required constants */
#define NUM_VERIFY_IV_COLLECTIONS 2

#define VERIFY_IV_CID_1  0
#define VERIFY_IV_CID_2  1
#define VERIFY_IV_VID_1  0

#define VERIFY_IV_C_DELTA_MAX_1       2000  /* All times in millisecs */
#define VERIFY_IV_C_DELTA_MAX_2       2000
#define VERIFY_IV_C_DELTA_EXPECTED_1  1000
#define VERIFY_IV_C_DELTA_EXPECTED_2  1000
#define VERIFY_IV_V_DELTA_MAX_1       10000


/* Initialize TBAD area of the context structure. */
ac_Status _ac_initializeTBAD(ac_Context context);

/* TBAD pass callback. */
_xc_preserve_interface 
ac_uint32 tbadPass(ac_uint32 pData);

#ifdef __cplusplus
}
#endif

#endif /* __ac_TBAD_INTERNAL_H__ */

