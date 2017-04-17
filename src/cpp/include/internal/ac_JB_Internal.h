/** \defgroup ac_JB Irdeto ActiveCloak Jailbreak Detection component */
/* @{ */

/*! \file ac_JB_Internal.h
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

   \brief The private JB-related definitions and function prototypes for the
          ActiveCloak Jailbreak Detection component.

   Limitations: None

   Thread Safe: Supported via 1 context per thread

   Platform Dependencies: CSS Version 5.1 or newer (i.e., Platform/OS/CSS version)

   Compiler Options:
*/


#ifndef __ac_JB_INTERNAL_H__
#define __ac_JB_INTERNAL_H__

#include "xc/xc_extensions.h"

#include "ac_types.h"
#include "ac_common.h"
#include "ac_SecureStore_Internal.h"
#include "ac_Common_Internal.h"
#include "ac_SecureStore.h"

#ifdef __cplusplus
extern "C" {
#endif

/*!
<B>Description:</B>
    Enumerated list of Jailbreak response severity levels.
*/
typedef  ac_uint  ac_JB_Response_Severity;
#define    ac_JB_RESPONSE_NOTIFY       0x01     /*!< Return error code from JB operation. */
#define    ac_JB_RESPONSE_SOFT_ERROR   0x02     /*!< Induce later operational error. */
#define    ac_JB_RESPONSE_HARD_ERROR   0x03     /*!< Cause immediate operational crash. */

typedef  ac_uint  acJB_CallerType;
#define    JB_CALLER_INITIALIZE  0x001  /*!< Caller is ac_Initialize(). */
#define    JB_CALLER_INTERNAL    0x002  /*!< Caller is a AC API that accesses secure assets. */
#define    JB_CALLER_EXTERNAL    0x003  /*!< Caller is a user invoking ac_JB_DetectSystem() or ac_MS_DetectSystem(). */

typedef  ac_uint  acJB_PhaseCompleted;
#define    JB_DETECT_LEVEL_ONE_PASSED     0x0001  /*!< level 1 jailbreak detection has been completed successfully. */
#define    JB_DETECT_LEVEL_TWO_PASSED     0x0002  /*!< level 2 jailbreak detection has been completed successfully. */
#define    JB_DETECT_LEVEL_THREE_PASSED   0x0003  /*!< level 3 jailbreak detection has been completed successfully. */

/*! Jailbreak detection related information stored in context */
typedef struct __JB_Context {
    void *                    JB_handle;           /*!< handle used in JB detection */
    ac_JB_Response_Severity  jbSeverity;          /*!< severity of JB response */
    acJB_PhaseCompleted      phase_completed;     /*!< passed phases of JB detection */
    ac_Status                JB_detected;         /*!< result from last JB detection */
} __JB_Context;




#ifdef IS_AGENT

#if ! defined(JB_RESPONSE_HARD_ERROR) && ! defined(JB_RESPONSE_SOFT_ERROR) && ! defined(JB_RESPONSE_NOTIFY)
extern const ac_JB_Response_Severity ac_JB_RESPONSE_SEVERITY_LEVEL_INIT;
#endif

ac_Status acJB_checkResult(ac_Context        context);

/* invokes all levels of jailbreak detection */
ac_Status acJB_Detect_All(ac_Context         context,
                            void *              pData);

/* invokes level 3 jailbreak detection */
ac_Status acJB_Detect_Advanced(ac_Context    context,
                                 void *         pData);

/* invokes level 1 and level 2 jailbreak detection */
ac_Status acJB_Detect_Basic(ac_Context       context,
                              void *            pData);

ac_Status acJB_Detection(ac_Context          context,
                           acJB_CallerType     callerType,
                           void *               pData);

ac_Status acJB_Detection_Internal(ac_Context       context,
                                    acJB_CallerType  callerType,
                                    void *            pDataMedSeverity,
                                    void *            pDataHighSeverity);

ac_Status acJB_Detect_Hook(ac_Context         context,
                              void *              pData);

#endif


#ifdef __cplusplus
}
#endif

#endif /* __ac_JB_INTERNAL_H__ */

