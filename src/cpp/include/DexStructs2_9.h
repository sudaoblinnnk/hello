#ifndef DEX_STRUCTS_2_9_H
#define DEX_STRUCTS_2_9_H


#define DEX_DEXMEMORY_POINTER
#define DEX_IS_MAPPED_READONLY


/*
 * This structure is commented out in DexFile declaration in the API level 9 and up
 * That should make the trick
 */
typedef struct DexIndexMap {
} DexIndexMap;

static u4 getReducedStringsCount(DexIndexMap* pDexIndexMap) {return 0;}
static u4 getReducedClassCount(DexIndexMap* pDexIndexMap) {return 0;}
static u4 getReducedMethodCount(DexIndexMap* pDexIndexMap) {return 0;}
static u4 getReducedFieldCount(DexIndexMap* pDexIndexMap) {return 0;}

#define DEX_INDEX_MAP_DECLARATION

typedef struct ZipArchive
{
	/* open Zip archive */
	int mFd;

	long mDirectoryOffset;

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


#endif //DEX_STRUCTS_2_9_H
