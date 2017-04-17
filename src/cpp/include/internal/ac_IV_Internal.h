/** 616 \defgroup ac_IV Irdeto ActiveCloak Integrity Verification component */
/* @{ */

/* ----------------------------------------------------------------------------*/
/*! \file ac_IV_Internal.h
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

   \brief The private IV-related definitions and function prototypes for the
          ActiveCloak Integrity Verification component.

   Limitations: None

   Thread Safe: Supported via 1 context per thread

   Platform Dependencies: CSS Version 5.1 or newer (i.e., Platform/OS/CSS version)

   Compiler Options:
*/


#ifndef __ac_IV_INTERNAL_H__
#define __ac_IV_INTERNAL_H__

#ifndef USE_OTSC_PFIV       /* Not using the IV is in the OTSC */

#include "xc/xc_extensions.h"

#include "ac_types.h"
#include "ac_common.h"
#include "ac_SecureStore_Internal.h"
#include "ac_Common_Internal.h"
#include "ac_SecureStore.h"
#ifdef PFIV_ENABLED
#include "xc/xc_pfiv.h"
#endif
#ifdef __cplusplus
extern "C" {
#endif

/*!
<B>Description:</B>
    Enumerated list of IV failure severity levels.
*/
typedef  ac_uint  ac_IV_Fail_Severity;
#define    ac_IV_FAIL_NOTIFY      0x000  /*!< Return IV failure error code. */
#define    ac_IV_FAIL_SOFT_ERROR  0x001  /*!< Induce later operational error. */
#define    ac_IV_FAIL_HARD_ERROR  0x002   /*!< Cause immediate operational crash. */

typedef  ac_uint  acIV_ModuleType;
#define    IV_DATA_HOST         0x100
#define    IV_DATA_FOREIGN      0x101
#define    IV_DATA_EXTERNAL     0x102
#define    IV_DATA_THIRD_PARTY  0x103


/* Create masks to fetch SL and level information from SS*/
#define MASK_SL        0x80000000

#ifdef PFIV_ENABLED
#define MAX_SIGNATURES      10000      /* To make sure the set value is within range. */
#else /* Legacy IV */
#define MAX_SIGNATURES      100        /* For legacy IV, this define indicates the % of signatures in a 
       									  module to be verified */
#endif

#define DEFAULT_SIGNATURES  1   /* used for implicit in-memory test */
#define IV_MODULES_ALL		0


/* Max number of bytes in module path */
#define IV_MOD_PATH_BYTES 256

/*! Internal IV module related information */
typedef struct __RKM_IV_ModuleData {
    ac_uint32       sequence;                  /*!< Module sequence number. */
    acIV_ModuleType type;                      /*!< Module type indicator. */
    ac_uint32 protectionLevel;                 /*!< Protection level (or work factor) for specified module. */
    ac_char   *basename;                       /*!< Module base filename. */
    ac_char   moduleIVPath[IV_MOD_PATH_BYTES]; /*!< IV module path, composed of signing time and dynamic runtime prefix components. */
    ac_char   *pathyName;                      /*!< Filename of module, inclusive of file path, provdied at file signing time. */
    ac_uint8  voucherLocInd;                   /*!< Voucher location indicator (0x00=embedded voucher, 0xFF=external file, 0x01-0xFE=handleID length). */
    ac_char   *voucherRefName;                 /*!< Voucher reference name (either pathyname or handle ID). */
#ifdef PFIV_ENABLED
	XC_IV_Handle_t handle;					   /*!< Handle for the PF-IV functions. */
    ac_uint32 xc_Mode;                         /*!< XC mode */
#endif
    ac_int32 openStatus;					   /*!< Status for signed modules: XC_OK/XC_FAIL(not currently in memory). */
} RKM_IV_ModuleData;

/* Number of IV status bytes */
#define IV_NUM_STATUS_BYTES 16

/*! IV related information stored in context */
typedef struct __IV_Context {
    ac_uint32            moduleCount;                    /*!< Total number of modules to be IV'd. */
    RKM_IV_ModuleData     *modules;                       /*!< Pointer structure member to module detail information. */
    ac_IV_Fail_Severity  ivFailSeverity;                 /*!< Configurable IV fail severity level. */
    ac_uint32            ivWorkFactor;                   /*!< Configurable IV work factor level. */
    ac_Status            ivRC;                           /*!< Return code of last IV operation attempted. */
    ac_uint8             ivStatus[IV_NUM_STATUS_BYTES];  /*!< Tracks IV operational result details. */

#ifndef XC_RESTRICTED_ISO
#ifdef __OPENKODE_ARM__
    ac_JIL_Games_IV_Data *openkodeIVContext;             /*!< Pointer structure member to OPENKODE IV host/module information. */
#endif
#endif

    ac_uint32            signatureCounts;                /*!< Number of signature to be verified. */
                                                         /*!< For legacy IV, this variable indicates the %
                                                              of signatures in a module to be verified */
    ac_int               enhancedZoneState;              /*!< Enhanced zone's state: 0-disabled, 1-enabled. */
    ac_int               lastLoadedModule;               /*!< The last module that was loaded in memory. */
} __IV_Context;

#ifdef IS_AGENT

#if ! defined(IV_FAIL_HARD_ERROR) && ! defined(IV_FAIL_SOFT_ERROR) && ! defined(IV_FAIL_NOTIFY)
extern const ac_IV_Fail_Severity ac_IV_FAIL_SEVERITY_LEVEL_INIT;
#endif

ac_Status acIV_checkResult(ac_Context        context);

ac_Status acIV_Verify(ac_Context      context,
                        void             *pDataHighSeverity,
                        void             *pDataMediumSeverity);

ac_Status acIV_VerifyOnDisk(ac_Context      context,
                        void             *pDataHighSeverity,
                        void             *pDataMediumSeverity);

ac_Status acIV_VerifyInMemory(ac_Context      context,
                        void             *pDataHighSeverity,
                        void             *pDataMediumSeverity,
                        ac_uint32        signatureCounts);

ac_Status acIV_VerifyWithKIPtr(ac_Context        context,
                                 void               *pDataHighSeverity,
                                 void               *pDataMediumSeverity,
                                 RKM_KeyInfo        **pKeyInfo,
                                 ac_SS_Data_Handle handle);

ac_Status acIV_EnhancedZone_Enter(ac_Context      context);

ac_Status acIV_EnhancedZone_Exit(ac_Context      context);

xc_preserve_interface
ac_Status IVVerifyInMemory(ac_Context context,
                           void *pDataHighSeverity,
                           void *pDataMediumSeverity,
                           ac_uint32 signatureCounts,
                           ac_uint32 moduleCounts);

#if defined PFIV_ENABLED && defined IVTHREAD_ENABLED
ac_Status ac_ApiInit(ac_Context context);
ac_Status ac_ApiComplete(ac_Context context);
ac_Status ac_getCurrentThreadStatus(ac_Context context);
#endif

/* IV callback structure for modifying data value and setting KeyInfo pointer */
typedef struct {
    ac_uint32          *pvalue;
    RKM_KeyInfo        **pKeyInfo;
    ac_SS_Data_Handle rkmHandle;
    ac_uint32         currentIVCount;
    ac_uint8          failIVcbCount;
    ac_int            lastLoadedModule;
} IV_WithKIPtr;

#else

/*
ac_Status acIV_SignSecureStore(ac_Context        context,
                                 ac_SS_Data_Handle *pKeyHandle,
                                 ac_char           *hostPath,
                                 ac_char           *voucherName);
*/

ac_Status acIV_AppendModule(ac_SS_Context   context,
                              ac_uint32       protectionLevel,
                              ac_char         *moduleName,
                              ac_char         *modulePath,
                              ac_uint8        *voucherData,
                              ac_uint32       voucherDataLen,
                              ac_char         *voucherFilePath,
                              acIV_ModuleType moduleType);

#endif

#define IVVerifySystem(ctx, cdh, cdm, sig, mod)     \
                acIV_Verify((ctx), (cdh), (cdm))
#define IVVerifyOnDisk(ctx, cdh, cdm, sig, mod)     \
                acIV_VerifyOnDisk((ctx), (cdh), (cdm))

#ifdef __cplusplus
}
#endif

#else /* USE_OTSC_PFIV */

#include "otsc_iv.h"
#include "IV_Internal2.h"

#ifdef __cplusplus
extern "C" {
#endif

    /* Max number of bytes in module path */
#define IV_MOD_PATH_BYTES 256

/*! Internal IV module related information */
typedef struct __RKM_IV_ModuleData {
    uint32_t   sequence;                        /*!< Module sequence number. */
    uint32_t   type;                            /*!< Module type indicator. */
    uint32_t   protectionLevel;                 /*!< Protection level (or work factor) for specified module. */
    int8_t     *basename;                       /*!< Module base filename. */
    int8_t     moduleIVPath[IV_MOD_PATH_BYTES]; /*!< IV module path, composed of signing time and dynamic runtime prefix components. */
    int8_t     *pathyName;                      /*!< Filename of module, inclusive of file path, provdied at file signing time. */
    uint8_t    voucherLocInd;                   /*!< Voucher location indicator (0x00=embedded voucher, 0xFF=external file, 0x01-0xFE=handleID length). */
    int8_t     *voucherRefName;                 /*!< Voucher reference name (either pathyname or handle ID). */

	XC_IV_Handle_t handle;						 /*!< Handle for the PF-IV functions. */
    uint32_t xc_Mode;                           /*!< XC mode */
    XC_V_Handle_t voucherHandle;                /* Voucher handle */
} RKM_IV_ModuleData;

/* OTSC has extra parameters: signature and module counts */
/* We use the severity to decide which callback data to use */
/* For hard severity, we use high callback data */ 
/* For medium and notify severity, we use medium callback data */

#if defined(IV_FAIL_HARD_ERROR)
#define IVVerifySystem(ctx, cd1, cd2, sig, mod)     \
                acIV_VerifySystem(&((ctx)->iv_Handle), (cdh), (sig), (mod))
#define IVVerifyOnDisk(ctx, cd1, cd2, sig, mod)     \
                acIV_VerifyOnDisk(&((ctx)->iv_Handle), (cdh), (sig), (mod))

#else
/*#elif defined(IV_FAIL_SOFT_ERROR)*/
#define IVVerifySystem(ctx, cdh, cdm, sig, mod)     \
                acIV_VerifySystem(&((ctx)->iv_Handle), (cdm), (sig), (mod))
#define IVVerifyOnDisk(ctx, cdh, cdm, sig, mod)     \
                acIV_VerifyOnDisk(&((ctx)->iv_Handle), (cdm), (sig), (mod))
/*#else  IV_FAIL_NOTIFY 
#define IVVerifySystem(ctx, cdh, cdm, sig, mod)     \
                acIV_VerifySystem(&((ctx)->iv_Handle), NULL, (sig), (mod))
#define IVVerifyOnDisk(ctx, cdh, cdm, sig, mod)     \
                acIV_VerifyOnDisk(&((ctx)->iv_Handle), NULL, (sig), (mod))
*/
#endif

#ifdef __cplusplus
}
#endif

#endif        /* USE_OTSC_PFIV Not using the IV is in the OTSC */

#endif /* __ac_IV_INTERNAL_H__ */

