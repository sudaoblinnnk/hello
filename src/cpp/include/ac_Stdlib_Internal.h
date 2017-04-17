/** \defgroup ac_General Irdeto ActiveCloak Types Abstraction */
/* @{ */

/*! \file ac_Stdlib_Internal.h
   Irdeto Canada Corporation

   FILE: ac_Stdlib_Internal.h
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
  
   Thread Safe: Supported via 1 context per thread
  
   Platform Dependencies: CSS Version 5.1 or newer      (i.e.: Platform/OS/CSS version)

   Compiler Options: 
*/

#ifndef __ac_STDLIB_INTERNAL_H__
#define __ac_STDLIB_INTERNAL_H__

#include "xc/xc_extensions.h"
#include "xc/xc_stdlib.h"

#include "ac_types.h"

#if defined MEMORY_LEAK_CLEANUP
void ac_RecordKeeping_free (void *ptr, ac_char * fileName,
            ac_int32 lineNumber);
void *ac_RecordKeeping_malloc (ac_int32 size, ac_char * fileName,
            ac_int32 lineNumber);
void *ac_RecordKeeping_calloc(ac_int32 number, ac_int32 size, 
            ac_char * fileName, ac_int32 lineNumber);
void ac_Report_Unfreed_Memory (void);
#endif

#if ! defined XC_RESTRICTED_ISO

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning (disable:4820)
#endif

#ifdef __OPENKODE_ARM__
#include <KD/kd.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ac_NULL      NULL

#define ac_SEEK_SET  SEEK_SET
#define ac_SEEK_END  SEEK_END
#define ac_SEEK_CUR  SEEK_CUR

#ifdef _MSC_VER
#pragma warning( pop )
#endif

/* Memory Funcs */
#if defined MEMORY_LEAK_CLEANUP
#define ac_malloc(x)      ac_RecordKeeping_malloc(x, __FILE__, __LINE__)
#define ac_calloc(n, x)   ac_RecordKeeping_calloc(n, x, __FILE__, __LINE__)
#else
#define ac_malloc(x)      XC_malloc(x)
#define ac_calloc(n, x)   XC_calloc(n, x)
#endif

#ifdef __OPENKODE_ARM__

#define XC_malloc            kdMalloc

#endif

/*
static void* ac_malloc(ac_int32 x)
{
    XC_printf((ac_char *)"Malloc of 0x%x bytes.\n", x);
    return  XC_malloc(x);
}
*/
#ifdef __OPENKODE_ARM__


#define ac_free(x)         kdFree(x)

/* FILE Stuff */
#define ac_FILE            KDFile
#define ac_fopen           kdFopen
#define ac_fread           kdFread
#define ac_fwrite          kdFwrite
#define ac_fseek           kdFseek
#define ac_ftell           kdFtell
#define ac_fclose          kdFclose
#define ac_fflush          kdFflush

/* STDIN/OUT stuff */
#define ac_printf          XC_printf
#define ac_sprintf         XC_sprintf
#define ac_fprintf         XC_fprintf
#define ac_rand            kdRand
#define ac_srand           kdSrand

#else

#if defined MEMORY_LEAK_CLEANUP
#define ac_free(x)         ac_RecordKeeping_free(x, __FILE__, __LINE__)
#else
#define ac_free(x)         free(x)
#endif

/* FILE Stuff */
#define ac_FILE            FILE
#define ac_fopen           fopen
#define ac_fread           fread
#define ac_fwrite          fwrite
#define ac_fseek           fseek
#define ac_ftell           ftell
#define ac_fclose          fclose
#define ac_fflush          fflush

/* STDIN/OUT stuff */
#define ac_printf          printf
#define ac_sprintf         sprintf
#define ac_fprintf         fprintf
#define ac_rand            rand
#define ac_srand           srand
#endif

#ifdef __OPENKODE_ARM__
#define ac_MEMCMP   kdMemcmp
#define ac_STRLEN   kdStrlen
#define ac_STRTOUL  kdStrtoul
#define ac_STRRCHR  kdStrrchr
#define ac_STRCHR   kdStrchr

#else
#define ac_MEMCMP   memcmp
#define ac_STRLEN   strlen
#define ac_STRTOUL  strtoul
#define ac_STRRCHR  strrchr
#define ac_STRCHR   strchr
#endif

#else /* #if ! defined XC_RESTRICTED_ISO */

#define ac_NULL      NULL

#define ac_SEEK_SET  XC_SEEK_SET
#define ac_SEEK_END  XC_SEEK_END
#define ac_SEEK_CUR  XC_SEEK_CUR

/* Memory Funcs */

#if defined MEMORY_LEAK_CLEANUP
#define ac_malloc(x)      ac_RecordKeeping_malloc(x, __FILE__, __LINE__)
#define ac_calloc(n, x)   ac_RecordKeeping_calloc(n, x, __FILE__, __LINE__)
#else
#define ac_malloc(x)      XC_malloc(x)
#define ac_calloc(n, x)   XC_calloc(n, x)
#endif

/* FILE Stuff */
#define ac_FILE            XC_FILE
#define ac_fopen           XC_fopen
#define ac_fread           XC_fread
#define ac_fwrite          XC_fwrite
#define ac_fseek           XC_fseek
#define ac_ftell           XC_ftell
#define ac_fclose          XC_fclose
#define ac_fflush          XC_fflush

/* STDIN/OUT stuff */
#define ac_printf          XC_printf
#define ac_sprintf         XC_sprintf
#define ac_fprintf         XC_fprintf
#define ac_rand            XC_rand
#define ac_srand           XC_srand

#if defined MEMORY_LEAK_CLEANUP
#define ac_free(x)         ac_RecordKeeping_free(x, __FILE__, __LINE__)
#else
#define ac_free(x)         XC_free(x)
#endif

#define ac_MEMCMP          XC_memcmp
#define ac_STRLEN          XC_strlen
#define ac_STRTOUL         XC_strtoul
#define ac_STRRCHR         XC_strrchr
#define ac_STRCHR          XC_strchr

#endif /* if ! defined XC_RESTRICTED_ISO */

#define memcpy_m            ac_MEMCPY
#define memset_m            ac_MEMSET
#define strncpy_m           ac_STRNCPY
#define strnac_m           ac_STRNCAT

static _xc_must_inline_remove ac_int32
ac_memncmp (ac_uint8 * lhs, ac_uint8 * rhs, ac_uint32 length)
{
  ac_uint32 ac_MEMNCMP_index;
  for (ac_MEMNCMP_index = 0;
       ac_MEMNCMP_index < (ac_uint32) (length); ac_MEMNCMP_index++)
    {
      if ((lhs)[ac_MEMNCMP_index] < (rhs)[ac_MEMNCMP_index])
	return 1;
      else if ((lhs)[ac_MEMNCMP_index] > (rhs)[ac_MEMNCMP_index])
	return -1;
    }
  return 0;
}

#define ac_MEMCPY_T(out, in, length)\
{ \
        ac_uint32 index; \
        for ( index = 0; index < length ; index++ ) \
          out[index] = in[index]; \
} \


#define ac_MEMCPY(out, in, length) \
{ \
        ac_uint32 ac_MEMCPY_index; \
        ac_uint8* ac_MEMCPY_pOut = _xc_transformcast(_xc_preservetype ac_uint8* ) (out); \
        ac_uint8* ac_MEMCPY_pIn = _xc_transformcast(_xc_preservetype ac_uint8* ) (in); \
        for (ac_MEMCPY_index = 0; ac_MEMCPY_index < (ac_uint32)(length); ac_MEMCPY_index++) \
                (ac_MEMCPY_pOut)[ac_MEMCPY_index] = (ac_MEMCPY_pIn)[ac_MEMCPY_index]; \
}

#define ac_MEMSET XC_memset

#define ac_STRNCPY(out, in, max) \
{ \
        ac_uint32 strncpy_m_index = 0; \
        while ( (strncpy_m_index < max) && (in[strncpy_m_index] != 0x0) ) { \
                (out)[strncpy_m_index] = (in)[strncpy_m_index]; \
                strncpy_m_index++; \
        } \
}

#define ac_STRNCAT(out, in, max) \
{ \
        ac_uint32 strnac_m_index = 0; \
        ac_uint32 strnac_m_start = 0; \
        while ( (strnac_m_start < max) && ((out)[strnac_m_start] != 0x0) ) \
                strnac_m_start ++; \
        while ( ((strnac_m_start + strnac_m_index) < max) && (in[strnac_m_index] != 0x0) ) { \
                (out)[strnac_m_start + strnac_m_index] = (in)[strnac_m_index]; \
                strnac_m_index++; \
        } \
}

/* Will populate "buffer" with the binary
 * value of the hex-string in "string".
 */
#define ac_ASCII2BIN(string, buffer)                       \
    {                                                       \
        ac_char *s = (string);                              \
        ac_uint8 *b = (buffer);                             \
        while (*s != 0) {                                    \
            ac_char hex[3];                                 \
            hex[0] = s[0];                                   \
            hex[1] = s[1];                                   \
            hex[2] = 0;                                      \
            *b = (ac_uint8)ac_STRTOUL(hex, NULL, 16);      \
            s+=2; b++;                                       \
        }                                                    \
    }

#endif /* __ac_STDLIB_INTERNAL_H__ */


#include <android/log.h>

#define TAG "MODULE"
#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO   , TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG  , TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR  , TAG, __VA_ARGS__)
