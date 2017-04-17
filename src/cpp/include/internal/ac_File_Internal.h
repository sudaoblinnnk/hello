/** \defgroup ac_File File I/O Components */
/* @{ */

/*  ---------------------------------------------------------------------------- */
/*! \file ac_File_Internal.h
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
  
   \brief The public API exported by Irdeto's ActiveCloak File Protections Component.   
	  
   Description: The public API exported by Irdeto's ActiveCloak File Protections Component.  

   Limitations: None
  
   Thread Safe: Supported via 1 context per thread
  
   Platform Dependencies: CSS Version 5.1 or newer      (i.e.: Platform/OS/CSS version)

   Compiler Options: 
*/

#ifndef __ac_FILE_H__
#define __ac_FILE_H__

#include "ac_types.h"

#include "xc/xc_stdlib.h"

#define TARGET_FILE_PTR                        XC_FILE
#define TARGET_FOPEN(filename, mode)           XC_fopen( (filename), (mode) )
#define TARGET_FCLOSE(pFile)                   XC_fclose( (pFile) )
#define TARGET_FREAD(buffer, size, count, fp)  XC_fread( (buffer), (size), (count), (fp) )
#define TARGET_FTELL(fp)                       XC_ftell( (fp) )
#define TARGET_FSEEK(fp, offset, origin)       XC_fseek( (fp), (offset), (origin) )
#define TARGET_FWRITE(buffer, size, count, fp) XC_fwrite( (buffer), (size), (count), (fp) )

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  /* consider platform dependent FILE descriptor, using void* for now */
    void        *nativefp;
    ac_uint32   fileLength;
    ac_uint8   *curPos;
    ac_uint8    isCached;
    ac_uint8   *cachedBuffer;
    ac_uint8    isPoisoned;
    ac_uint8    dpFuncIndex;
    ac_uint8    dpRecordCount;
    ac_uint32 **dpFuncPtr;
} ac_PFILE;

typedef  ac_uint8	ac_PFILE_MODE;
typedef  ac_uint8	ac_SEEK_ORIG;

/**
 * ac_fileOpen()
 * Open a file for reading. 
 *
 * Takes as inputs a previously established context, a file name and options, and returns
 * a file handle if successful.
 *
 */
ac_Status ac_fileOpen (ac_Context context, ac_char *filename, ac_PFILE_MODE *modes, ac_PFILE *fileHandle);

/**
 * ac_fileClose()
 * Closes a previously opened file. 
 *
 */
ac_Status ac_fileClose (ac_Context context, ac_PFILE* fileHandle, ac_int32* kdInt);

/**
 * ac_FileRead()
 * Copies numBytes of data to the location pointed to by ptr.
 *
 */
ac_Status ac_fileRead (ac_Context context, ac_uint8* buffer, ac_uint32 size, ac_uint32 count, 
                         ac_PFILE* fileHandle, ac_int32* rsize);

/**
 * ac_FileWrite()
 * Copies numBytes of data to the location pointed to by ptr.
 *
 */
ac_Status ac_fileWrite(ac_Context context, ac_uint8* buffer, ac_uint32 size, ac_uint32 count, 
                         ac_PFILE* fileHandle, ac_int32* rsize);

/**
 * ac_fileSeek()
 * Repositions a file-position indicator to "index" bytes from the start of the file 
 *
 */
ac_Status ac_fileSeek (ac_Context context, ac_PFILE* fileHandle, 
                         ac_uint32 offset, ac_SEEK_ORIG orig, ac_int32* pos);

/**
 * ac_fileTell()
 * Repositions a file-position indicator to "index" bytes from the start of the file 
 *
 */
ac_Status ac_fileTell(ac_Context context, ac_PFILE* fileHandle, ac_int32* roff);


/*

- kdGetc(KDFile *file);
- kdPutc(KDFile *file);
- kdFflush(KDFile *file);
- kdFgets();
- kdFEOF();
- kdFerror();
- kdClearerr();
- kdFstat();

*/


#ifdef __cplusplus
}
#endif
#endif /* __ac_FILE_H__ */

/* @}*/
