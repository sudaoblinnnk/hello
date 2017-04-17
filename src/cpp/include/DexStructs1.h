#ifndef DEX_STRUCTS_1_H
#define DEX_STRUCTS_1_H

typedef struct DexFile
{
	/* directly-mapped "opt" header */
	//const DexOptHeader* pOptHeader;
	DexOptHeader* pOptHeader;

	/* pointers to directly-mapped structs and arrays in base DEX */
	const DexHeader* pHeader;
	//const void* pHeader;
	const DexStringId* pStringIds;
	//const void* pStringIds;
	const DexTypeId* pTypeIds;
	//const void* pTypeIds;
	//const DexFieldId* pFieldIds;
	const void* pFieldIds;
	//const DexMethodId* pMethodIds;
	const void* pMethodIds;
	//const DexProtoId* pProtoIds;
	const void* pProtoIds;

	const DexClassDef* pClassDefs;
	//const void* pClassDefs;
	//const DexLink* pLinkData;
	const void* pLinkData;

	/* mapped in "auxillary" section */
	//const DexClassLookup* pClassLookup;
	const void* pClassLookup;

	/* mapped in "auxillary" section */
	DEX_INDEX_MAP_DECLARATION// this one will be empty on API level >= 9
	const void* pRegisterMapPool;

	/* points to start of DEX file data */
	const char* baseAddr;

	/* track memory overhead for auxillary structures */
	int         overhead;

/* additional app-specific data structures associated with the DEX */
//void*               auxData;
} DexFile;

typedef struct DvmDex
{
	/* pointer to the DexFile we're associated with */
	DexFile* pDexFile;
	//void* pDexFile;

	/* clone of pDexFile->pHeader (it's used frequently enough) */
	//const DexHeader* pHeader;
	const void* pHeader;

	/* interned strings; parallel to "stringIds" */
	//struct StringObject** pResStrings;
	void** pResStrings;

	/* resolved classes; parallel to "typeIds" */
	//struct ClassObject** pResClasses;
	void** pResClasses;

	/* resolved methods; parallel to "methodIds" */
	//struct Method** pResMethods;
	void** pResMethods;

	/* resolved instance fields; parallel to "fieldIds" */
	/* (this holds both InstField and StaticField) */
	//struct Field** pResFields;
	void** pResFields;

	/* interface method lookup cache */
	//struct AtomicCache* pInterfaceCache;
	void* pInterfaceCache;

	/* shared memory region with file contents */
	DEX_IS_MAPPED_READONLY
	MemMapping memMap;

	int modLock;
} DvmDex;

typedef struct RawDexFile {
	char*       cacheFileName;
	DvmDex*     pDvmDex;
} RawDexFile;


typedef struct JarFile
{
	ZipArchive archive;
	//MemMapping  map;
	char* cacheFileName;
	DvmDex* pDvmDex;
} JarFile;

typedef struct DexOrJar
{
	 char*       fileName;
	 boolean     isDex;
	 boolean     okayToFree;
	 char        dummy1,dummy2;
	 //RawDexFile* pRawDexFile;
	 void*       pRawDexFile;
	 JarFile*    pJarFile;
	 //void*       pJarFile;
	 DEX_DEXMEMORY_POINTER
} DexOrJar;


#endif //DEX_STRUCTS_1_H
