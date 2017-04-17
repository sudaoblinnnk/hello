#ifndef DEX_STRUCTS_2_8_H
#define DEX_STRUCTS_2_8_H

#define DEX_DEXMEMORY_POINTER
#define DEX_IS_MAPPED_READONLY

typedef struct DexIndexMap {
    const u2* classMap;         /* map, either expanding or reducing */
    u4  classFullCount;         /* same as typeIdsSize */
    u4  classReducedCount;      /* post-reduction count */
    const u2* methodMap;
    u4  methodFullCount;
    u4  methodReducedCount;
    const u2* fieldMap;
    u4  fieldFullCount;
    u4  fieldReducedCount;
    const u2* stringMap;
    u4  stringFullCount;
    u4  stringReducedCount;
} DexIndexMap;

static u4 getReducedStringsCount(DexIndexMap* pDexIndexMap) {return pDexIndexMap->stringReducedCount;}
static u4 getReducedClassCount(DexIndexMap* pDexIndexMap) {return pDexIndexMap->classReducedCount;}
static u4 getReducedMethodCount(DexIndexMap* pDexIndexMap) {return pDexIndexMap->methodReducedCount;}
static u4 getReducedFieldCount(DexIndexMap* pDexIndexMap) {return pDexIndexMap->fieldReducedCount;}

#define DEX_INDEX_MAP_DECLARATION DexIndexMap indexMap;
#define DEX_INDEX_MAP_DECLARATION_NON_EMPTY 1

typedef struct ZipArchive
{
	/* open Zip archive */
	int mFd;

	/*
	 * UNCOMMENT FOR 2.3
	long mDirectoryOffset;
	*/
	/* mapped file */
	MemMapping mMap;

	/* number of entries in the Zip archive */
	int mNumEntries;

	/*
	 * We know how many entries are in the Zip archive, so we can have a
	 * fixed-size hash table.  We probe on collisions.
	 */
	int mHashTableSize;
	//ZipHashEntry* mHashTable;
	void* mHashTable;
} ZipArchive;


#endif //DEX_STRUCTS_2_8_H
