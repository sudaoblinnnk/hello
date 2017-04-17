/**********************************************************************

    OTSC SST 2.0 Wrapper API.

***********************************************************************/

#ifndef __AC_ST_OTSC_INTERNAL_H__
#define __AC_ST_OTSC_INTERNAL_H__

/*******************************************************
 * Portable IDs
 */

#pragma xc_riso_portable_id (WR_API_PRESERVE)


/*******************************************************
 * API related constants
 */

/* Maximum record ID size in bytes */
#define WR_API_MAX_ID_SZ     (0x0400)

/* Maximum value size in bytes */
#define WR_API_MAX_VALUE_SZ  (0x00100000)

/* Maximum option value size in bytes */
#define WR_API_MAX_OPTION_SZ (0x0400)

/* Maximum store buffer size in bytes */
#define WR_API_MAX_STORE_SZ  (0x00100000)

/*******************************************************
 * Wrapper data types and definitions
 */

/* Copy scalar array with transform */
#define WR_COPY(DES, SRC, CNT) { uint32_t i = 0; for(; i < (CNT); i ++) { (DES)[i] = (SRC)[i]; } }

/* Preserve public API */
#ifdef WR_API_PRESERVE
#define WR_PUBLIC_API _xc_preserve_interface
#else
#define WR_PUBLIC_API
#endif

/*******************************************************
 * Wrapper API
 */

/* Context objects factory */
WR_PUBLIC_API ac_Status WR_Create(ac_SS_Context* ppcontext);

/* Close store in context */
WR_PUBLIC_API ac_Status WR_Close(ac_SS_Context pcontext);

/* Delete context object */
WR_PUBLIC_API ac_Status WR_Delete(ac_SS_Context* ppcontext);

/* New key in store */
WR_PUBLIC_API ac_Status WR_RecordNew(ac_SS_Context pcontext, ac_Data_Type type, ac_uint8* pdata, ac_uint32 size, ac_Options* poptions, ac_SS_Data_Handle* phandle);

/* Get key type */
WR_PUBLIC_API ac_Status WR_RecordGetKeyTypeByHandle(ac_SS_Context pcontext, ac_SS_Data_Handle handle, ac_Data_Type *ptype);

/* Get key attributes */
WR_PUBLIC_API ac_Status WR_RecordGetKeyAttributesByHandle(ac_SS_Context pcontext, ac_SS_Data_Handle handle, ac_uint32 *pattributes);

/* Set key attributes */
WR_PUBLIC_API ac_Status WR_RecordSetKeyAttributesByHandle(ac_SS_Context pcontext, ac_SS_Data_Handle handle, ac_uint32 attributes);

/* Append data to record */
WR_PUBLIC_API ac_Status WR_RecordAppendByHandle(ac_SS_Context pcontext, ac_SS_Data_Handle handle, ac_uint8* pdata, ac_uint32 size);

/* Set record data */
WR_PUBLIC_API ac_Status WR_RecordSetByHandle(ac_SS_Context pcontext, ac_SS_Data_Handle handle, ac_uint8* pdata, ac_uint32 size);

/* Get record data */
WR_PUBLIC_API ac_Status WR_RecordGetByHandle(ac_SS_Context pcontext, ac_SS_Data_Handle handle, ac_uint8* pdata, ac_uint32* psize);

/* Get record data size */
WR_PUBLIC_API ac_Status WR_RecordGetSizeByHandle(ac_SS_Context pcontext, ac_SS_Data_Handle handle, ac_uint32* psize);

/* Delete record */
WR_PUBLIC_API ac_Status WR_RecordDeleteByHandle(ac_SS_Context pcontext, ac_SS_Data_Handle handle);

/* Record to key info */
WR_PUBLIC_API ac_Status WR_Record2KeyInfo(ac_SS_Context pcontext, ac_SS_Data_Handle handle, RKM_KeyInfo* pkeyinfo, ac_uint32* pmaxLength);

/* Clear key info structure */
WR_PUBLIC_API ac_Status WR_RecordClearKeyInfo(ac_SS_Context pcontext, ac_SS_Data_Handle handle, RKM_KeyInfo* pkeyinfo);

/* Purge store */
WR_PUBLIC_API ac_Status WR_StorePurge(ac_SS_Context pcontext);

/* Get handle by id */
WR_PUBLIC_API ac_Status WR_RecordGetHandleById(ac_SS_Context pcontext, ac_uint8* pid, ac_uint32 length, ac_SS_Data_Handle* phandle);

/* Set option */
WR_PUBLIC_API ac_Status WR_RecordSetOption(ac_SS_Context pcontext, ac_SS_Data_Handle handle, ac_Set_Options ac_option, ac_uint8* pdata, ac_uint32 size);

/* Get option */
WR_PUBLIC_API ac_Status WR_RecordGetOption(ac_SS_Context pcontext, ac_SS_Data_Handle handle, ac_Set_Options ac_option, ac_uint8** ppdata, ac_uint32* psize);

/* Load store from buffer */
WR_PUBLIC_API ac_Status WR_StoreLoadFromBuffer(ac_SS_Context* ppcontext, ac_uint8* pdata, ac_uint32 size);

/* Save store to file */
WR_PUBLIC_API ac_Status WR_StoreSaveToFile(ac_SS_Context pcontext, ac_char* pfile_name);

/* Create store */
WR_PUBLIC_API ac_Status WR_StoreCreate(ac_SS_Context* ppcontext);

/* Get store state */
WR_PUBLIC_API ac_Status WR_StoreGetState(ac_SS_Context pcontext, ac_uint32* pflags);

/* Set store state */
WR_PUBLIC_API ac_Status WR_StoreSetState(ac_SS_Context pcontext, ac_uint32 flags);

#endif /* __AC_ST_OTSC_INTERNAL_H__ */
