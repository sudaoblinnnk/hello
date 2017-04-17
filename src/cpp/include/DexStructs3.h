#ifndef DEX_STRUCTS_3_H
#define DEX_STRUCTS_3_H


typedef char boolean;
typedef unsigned int u4;
typedef unsigned short u2;
typedef unsigned char u1;

typedef struct _DexClassDef
{
    u4  classIdx;           /* index into typeIds for this class */
    u4  accessFlags;
    u4  superclassIdx;      /* index into typeIds for superclass */
    u4  interfacesOff;      /* file offset to DexTypeList */
    u4  sourceFileIdx;      /* index into stringIds for source file name */
    u4  annotationsOff;     /* file offset to annotations_directory_item */
    u4  classDataOff;       /* file offset to class_data_item */
    u4  staticValuesOff;    /* file offset to DexEncodedArray */

}DexClassDef;

typedef struct _DexClassLookup {
    int     size;                       // total size, including "size"
    int     numEntries;                 // size of table[]; always power of 2
            struct {
                u4      classDescriptorHash;    // class descriptor hash code
                int     classDescriptorOffset;  // in bytes, from start of DEX
                int     classDefOffset;         // in bytes, from start of DEX
         } table[1];
} DexClassLookup;

typedef struct _DexTypeId {
     u4  descriptorIdx;      /* index into stringIds list for type descriptor */
}DexTypeId;

typedef struct _DexStringId {
     u4 stringDataOff;      /* file offset to string_data_item */
}DexStringId;

typedef struct MemMapping
{
	char* addr; /* start of data */
	int length; /* length of data */

	char* baseAddr; /* page-aligned base address */
	int baseLength; /* length of mapping */
} MemMapping;



/* auxillary data section chunk codes */
enum {
    kDexChunkClassLookup            = 0x434c4b50,   /* CLKP */
    kDexChunkRegisterMaps           = 0x524d4150,   /* RMAP */

    kDexChunkEnd                    = 0x41454e44    /* AEND */
};

enum { kSHA1DigestLen = 20, kSHA1DigestOutputLen = kSHA1DigestLen*2 +1 };


typedef struct _DexOptHeader {
    char  magic[8];           /* includes version number */

    int  dexOffset;          /* file offset of DEX header */
    int  dexLength;
    int  depsOffset;         /* offset of optimized DEX dependency table */
    int  depsLength;
    int  optOffset;          /* file offset of optimized data tables */
    int  optLength;

    int  flags;              /* some info flags */
    int  checksum;           /* adler32 checksum covering deps/opt */

    /* pad for 64-bit alignment if necessary */
} DexOptHeader;

typedef struct _DexHeader {
    u1  magic[8];           /* includes version number */
    u4  checksum;           /* adler32 checksum */
    u1  signature[kSHA1DigestLen]; /* SHA-1 hash */
    u4  fileSize;           /* length of entire file */
    u4  headerSize;         /* offset to start of next section */
    u4  endianTag;
    u4  linkSize;
    u4  linkOff;
    u4  mapOff;
    u4  stringIdsSize;
    u4  stringIdsOff;
    u4  typeIdsSize;
    u4  typeIdsOff;
    u4  protoIdsSize;
    u4  protoIdsOff;
    u4  fieldIdsSize;
    u4  fieldIdsOff;
    u4  methodIdsSize;
    u4  methodIdsOff;
    u4  classDefsSize;
    u4  classDefsOff;
    u4  dataSize;
    u4  dataOff;
} DexHeader;



#endif //DEX_STRUCTS_3_H
