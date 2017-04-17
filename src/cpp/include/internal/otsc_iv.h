/** \defgroup CAT_General Common Components */
/* @{ */

/*! \file otsc_iv.h
   Irdeto Canada Corporation

   FILE: otsc_iv.h
   The software and information contained in this package (�Software�)
   is owned by Irdeto Canada Corporation, its affiliates or licensors
   (�Software Owners�). The Software is protected by U.S., Canadian,
   and international intellectual property laws and treaties and may
   contain patents, trademarks, copyrights, or other intellectual
   property rights of the Software Owners. If you acquired this package
   without an appropriate agreement, please contact Irdeto Canada Corporation at:

     phone +1 613 271 9446, email: info@irdeto.com

   The furnishing of this package does not constitute a license, express
   or implied, by estoppel or otherwise, to any patents, trademarks, copyrights,
   or other intellectual property rights of the Software Owners. Use of the Software
   without an appropriate agreement may constitute an infringement of the Software
   Owners� intellectual property rights and could subject you to legal action.

   \brief The public typesystem used and exported by Irdeto's ActiveCloak Agent.

   Description: The public typesystem used and exported by Irdeto's ActiveCloak Agent.

   Limitations: None

   Compiler Options:
*/

#ifndef _IV_H__
#define _IV_H__

#define PUBLIC_API

#include "xc/xc_stdint.h"
#include "xc/xc_pfiv.h"

#ifdef __cplusplus
extern "C" {
#endif

/*!
<B>Description:</B>
        Enumerated list of error codes that can be returned by the AC API.
*/
enum iv_errorCodes {
/**********************************************************************
    Success and Failure
**********************************************************************/
        IV_FAIL                                    = 0x7FFFFFFF, /*!< unspecified error:  Not to be used for any official errors */
        IV_OK                                      = 0x000, /*!< success return code */
/**********************************************************************
    Gerneral Error Codes
**********************************************************************/
        IV_ERROR_INVALID_PARAMETER                 = 0x001, /*!< bad input parameter */
        IV_ERROR_NULL_INPUT_POINTER                = 0x002, /*!< null pointer provided as input */
        IV_ERROR_HEAP_ALLOCATION_FAILED            = 0x003, /*!< heap allocation Failed */
        IV_ERROR_INVALID_DATA_SIZE                 = 0x004, /*!< invalid input data size, possibly reallocate bigger buffer*/
        IV_ERROR_FILE_OPEN_ERROR                   = 0x005, /*!< file open error */
        IV_ERROR_ALREADY_INITIALIZED               = 0x006, /*!< AC context has already been initialized */
        IV_ERROR_NULL_HANDLE                       = 0x007, /*!< AC context is null */

/**********************************************************************
        Integrity Verification (IV) Error Codes
**********************************************************************/
        IV_ERROR_IV                                = 0x400, /*!< Generic integrity verification failure  */
        IV_ERROR_MODULE_NOT_FOUND                  = 0x404, /*!< Module not found */
        IV_ERROR_NO_ZONE_CHANGE                    = 0x407, /*!< No zone changed during enter or exit */
        IV_ERROR_ENHANCED_ZONE_VIOLATION           = 0x408, /*!< Module(s) not loaded in enhanced state*/
/**********************************************************************
        TBAD Error Codes
**********************************************************************/
        IV_ERROR_TBAD_INITIALIZATION               = 0x40B  /*!< Couldn't set up TBAD */
};

#define IV_DATA_HOST         0x100
#define IV_DATA_FOREIGN      0x101
#define IV_DATA_EXTERNAL     0x102
#define IV_DATA_THIRD_PARTY  0x103

#define DEFAULT_SIGNATURES  1          /* used for implicit in-memory test */
#define MAX_SIGNATURES      10000      /* To make sure the set value is within range. */
#define IV_SIGNATURES_MAX   MAX_SIGNATURES

#define IV_SIGNATURES_ALL	0
#define IV_MODULES_ALL		0

/* Max number of bytes in module path */
#define IV_MOD_PATH_BYTES 256

/* This structure(s) (depending on the numebr of modules signed is used to pass
   from the application to the OTSC PFIV component to be used
   during the iv initialization.
   It is also stored in acv test files during testing for keeping the voucher data to be
   read back during the initialization.
*/
typedef struct __IV_ModuleData {
    uint32_t   size;                            /*!< Size of this structure. */
    uint32_t   protectionLevel;                 /*!< Module sequence number. */
    uint32_t   type;                            /*!< Module type indicator. */
    uint32_t   xc_Mode;                         /*!< XC mode */
    uint32_t   voucherLocInd;                   /*!< Voucher location indicator (0x00=embedded voucher, 0xFF=external file, 0x01-0xFE=handleID length). */
    int8_t     moduleIVPath[IV_MOD_PATH_BYTES]; /*!< IV module path, composed of signing time and dynamic runtime prefix components. */
    int8_t     basename[IV_MOD_PATH_BYTES];     /*!< Module base filename. */
    XC_V_Handle_t voucherHandle;                /* Voucher handle */
} IV_ModuleData;

typedef void * IV_Handle;    /*!< IV handle */

/* The IV_Verify_Type */
/* RISO does not accept enum */
#define IV_IN_MEMORY    0x08
#define IV_ON_DISK      0x04
#define IV_ALL          0x02
#define IV_SECRET_DATA  0xfe234ab

#ifndef DISABLE_FUNCTION_NAME_OBFUSCATION
#define IV_Initialize   OOOOOCCCCOCCOCOCOOOOCCOOOCCCCCOCCCCCCCCCOCCCCCCCCCCCOCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCOOOOO
#define IV_Shutdown     OOOOOCCCCOCCOCOCOOCOCCOOOCCCCCOCCCCCCCCCOCCCCCCCCCCCOCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCOOOOO
#define IV_Verify       OOOOOCOOOOOOOOOOOCOOOOOCOOOOOOOOOOOCOOOOOOOCOOOOOOCOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
#define IV_EnhancedZone_Enter   OOOOOCOOOOOOOOOOOOOOOOOCOOOOCOOOOOOCOOOOOOOCOOOOOOCOOOOOOOOOOOOOOCOOOOOOOOOOOOOOOOOOOOOOO
#define IV_EnhancedZone_Exit    OOOOOCOOOOOCOOOOOOOOOOOCOOOOOOOOOOOCOOOOOOOCOOOOOOCOOOOOOOOOOOOOOCOOCOOOOOOOOOOOOOOOOOOOO
#endif

PUBLIC_API uint32_t IV_Initialize(IV_Handle *ivHandle, uint8_t *inBuffer, uint32_t bufferSize);

PUBLIC_API uint32_t IV_Shutdown(IV_Handle *ivHandle);

typedef void (*IV_CallBack)(void * callBackData);

PUBLIC_API uint32_t IV_Verify(IV_Handle *ivHandle,
				   uint32_t type,
				   IV_CallBack success,
				   IV_CallBack fail,
				   void * callBackData,
				   uint32_t signatureCounts,
				   uint32_t moduleCounts);

PUBLIC_API uint32_t IV_EnhancedZone_Enter(IV_Handle *ivHandle);
PUBLIC_API uint32_t IV_EnhancedZone_Exit(IV_Handle *ivHandle);

#ifdef __cplusplus
}
#endif

#endif  /* _IV_H__ */
/* @} */
