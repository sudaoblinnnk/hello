/** \defgroup ac_Crypto Irdeto ActiveCloak Cryptographic component */
/* @{ */

/*! \file ac_SecureCounter_Internal.h
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


#ifndef __ac_SECURECOUNTER_INTERNAL_H__
#define __ac_SECURECOUNTER_INTERNAL_H__

#include "xc/xc_extensions.h"

#include "ac_types.h"
#include "ac_Common_Internal.h"
#include "ac_SecureStore.h"
#include "ac_SecureCounter.h"

#ifdef __cplusplus
extern "C" {
#endif

ac_PUBLIC_API(iac_SecureCounterCreate)( ac_SS_Context      ss_context, 
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

#ifdef __cplusplus
}
#endif

#endif /* __ac_BODYAPI_INTERNAL_H__ */

