#ifndef __IV_INTERNAL2_H__
#define __IV_INTERNAL2_H__

#include "xc/xc_extensions.h"
#include "otsc_iv.h"

#include "xc/xc_pfiv.h"

#ifdef TBAD_CHECK_ENABLED
#include "xc/xc_adb.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef TBAD_CHECK_ENABLED
/* Init IV TBAD required constants */
#define NUM_INIT_IV_COLLECTIONS_IV         2
#define NUM_VERIFY_IV_COLLECTIONS_IV       2
#define NUM_VERIFY_IVI_COLLECTIONS_IV      1
#endif
typedef struct __IV_ModuleInfo {
    IV_ModuleData iv_ModuleData;
	XC_IV_Handle_t handle;						 /*!< Handle for the PF-IV functions. */
    uint32_t openStatus;						 /*!< Status for signed modules: XC_OK/XC_FAIL(not currently in memory). */
    uint32_t devcieType;					     /*!< device type: on-disk or in-memory. */
    uint32_t maxSignatures;					     /*!< maximum numbers of signatures in this modules. */
    uint32_t signatureCounts;					 /*!< Current level or number of signatures used when verifying this module. */
} IV_ModuleInfo, *pIV_ModuleInfo;


/*! IV related information stored in context */
typedef struct __IV_Context {
    uint32_t              moduleCount;                    /*!< Total number of modules to be IV'd. */
    IV_ModuleInfo         *ivModuleInfo;                  /*!< Pointer structure member to module detail information. */
    uint32_t              signatureCounts;                /*!< Number of signature to be verified. */
    int32_t               enhancedZoneState;              /*!< Enhanced zone's state: 0-disabled, 1-enabled. */
    uint32_t              currentInMemoryIndex;           /*!< index to the next module being processed */
    uint32_t              currentOnDiskIndex;             /*!< index to the next module being processed */
    uint32_t              onDiskModules;                  /*!< Total number of ondisk modules to be IV'd. */
    uint32_t              inMemoryModules;                /*!< Total number of inmemory modules to be IV'd. */
    int32_t               prevDevcieType;                 /*!< Previous operation: disk (0) or memory (1) . */
    int32_t               allInMemoryModulesChecked;      /*!< All modules checked. */
    uint32_t              iv_latched;                     /*!< iv failure was detected, turn on the latch. */
    uint32_t              data_restore;                   /*!< this flag is for iac_IV_memory only for temp solution. */

#ifdef TBAD_CHECK_ENABLED
    XC_ADBTS_DataPointStruct tbad_initializeIV[NUM_INIT_IV_COLLECTIONS_IV];    /* used during initialization */
    XC_ADBTS_DataPointStruct tbad_verifyIV[NUM_VERIFY_IV_COLLECTIONS_IV];      /* Outer loop */
    XC_ADBTS_DataPointStruct tbad_verifyIVI[NUM_VERIFY_IVI_COLLECTIONS_IV];    /* inner loop */
#endif
} IV_Context, *pIV_Context;

#ifdef __cplusplus
}
#endif 

#endif /* __IV_INTERNAL2_H__ */

