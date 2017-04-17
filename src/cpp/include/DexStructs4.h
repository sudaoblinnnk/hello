#ifndef DEX_STRUCTS_4_H
#define DEX_STRUCTS_4_H


#define DEX_DEXMEMORY_POINTER unsigned char* pDexMemory;
#define DEX_IS_MAPPED_READONLY bool isMappedReadOnly;
#define DEX_INDEX_MAP_DECLARATION




typedef struct ZipArchive
{
        /* open Zip archive */
        int mFd;

        long mDirectoryOffset;

        /* mapped file */
        MemMapping mDirectoryMap;

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


#endif //DEX_STRUCTS_4_H
