#ifndef _XC_HASHH_
#define _XC_HASHH_

#include <xc/xc_stdlib.h>
#include <xc/xc_types.h>

#ifdef __cplusplus
extern "C" {
#endif

#define cat(p1,p2) docat(p1,p2)
#define docat(p1,p2) p1##p2

/* Decide on type of endian checks */
#define XC_RUNTIME_ENDIAN_CHECK   1

/* One byte (8 bit) for XC data types                         */
typedef XC_uint8 XCByte;

/* One word for XC data types                                 */
typedef XC_uint32 XCWord;

/* One 64-bit integer for XC data types			   */
#ifdef XC_SUPPORTS_64_BITS
#if defined _WIN32
typedef unsigned __int64 XCLong;
#else
typedef unsigned long long XCLong;
#endif
#endif

/* MD5 digested data, 128 bit with low order byte first */
typedef XC_uint32 XC_MD5Digest[16/4];

/* SHA-1 digested data, 160 bit with low order byte first        */
typedef XC_uint32 XC_SHA1Digest[20/4];

/* SHA-224 digested data, 224 bit with low order byte first        */
#define XC_SHA224DIGEST_SIZE     28/4
typedef XC_uint32 XC_SHA224Digest[XC_SHA224DIGEST_SIZE];

/* SHA-256 digested data, 256 bit with low order byte first        */
#define XC_SHA256DIGEST_SIZE     32/4
typedef XC_uint32 XC_SHA256Digest[XC_SHA256DIGEST_SIZE];

/* SHA-384 digested data, 384 bit with low order byte first        */
#ifdef XC_SUPPORTS_64_BITS
#define XC_SHA384DIGEST_SIZE     48/8
typedef XCLong XC_SHA384Digest[XC_SHA384DIGEST_SIZE];
#else
#define XC_SHA384DIGEST_SIZE     48/4
typedef XC_uint32 XC_SHA384Digest[XC_SHA384DIGEST_SIZE];
#endif

/* SHA-512 digested data, 512 bit with low order byte first        */
#ifdef XC_SUPPORTS_64_BITS
#define XC_SHA512DIGEST_SIZE     64/8
typedef XCLong XC_SHA512Digest[XC_SHA512DIGEST_SIZE];
#else
#define XC_SHA512DIGEST_SIZE     64/4
typedef XC_uint32 XC_SHA512Digest[XC_SHA512DIGEST_SIZE];
#endif


/***************************************************************/
/*                    Function Prototypes                      */
/***************************************************************/

/* MD5 State Structure                                         */
#define XC_MD5_BLOCKSIZE 64
typedef struct {
    XC_uint32 state[4];      /* MD5 State                   */
    XC_uint32 count[2];      /* length of Message in bits   */
    XC_uint32 buffer[XC_MD5_BLOCKSIZE/4]; /* temporary buffer.  Needs to be */
    /* XC_uint32 aligned, so allocated as XC_uint32 */
} XC_MD5State;

/* SHA-1 State Structure                                         */
#define XC_SHA1_BLOCKSIZE 64
typedef struct {
    XC_uint32 state[5];      /* SHA State                   */
    XC_uint32 count[2];      /* length of Message in bits   */
    XC_Octet buffer[XC_SHA1_BLOCKSIZE];        /* temporary buffer           */
} XC_SHA1State;

/* SHA-224 State Structure                                         */
#define XC_SHA224_BLOCKSIZE 64
typedef struct {
    XC_uint32 state[8];      /* SHA-224 State                   */
    XC_uint32 count[2];      /* length of Message in bits   */
    XC_Octet buffer[XC_SHA224_BLOCKSIZE];        /* temporary buffer           */
} XC_SHA224State;

/* SHA-256 State Structure                                         */
#define XC_SHA256_BLOCKSIZE 64
typedef struct {
    XC_uint32 state[8];      /* SHA-256 State                   */
    XC_uint32 count[2];      /* length of Message in bits   */
    XC_Octet buffer[XC_SHA256_BLOCKSIZE];        /* temporary buffer           */
} XC_SHA256State;


/* SHA-384 State Structure                                         */
#define XC_SHA384_BLOCKSIZE 128
typedef struct {
#ifdef XC_SUPPORTS_64_BITS
    XCLong state[8];          /* SHA-384 State                   */
    XCLong count[2];          /* length of Message in bits   */
#else
    XC_uint32 state[16];        /* SHA-384 State                   */
    XC_uint32 count[4];        /* length of Message in bits   */
#endif

    XC_Octet buffer[XC_SHA384_BLOCKSIZE];   /* temporary buffer           */
} XC_SHA384State;

/* SHA-512 State Structure                                         */
#define XC_SHA512_BLOCKSIZE 128
typedef struct {
#ifdef XC_SUPPORTS_64_BITS
    XCLong state[8];          /* SHA-512 State                   */
    XCLong count[2];          /* length of Message in bits   */
#else
    XC_uint32 state[16];        /* SHA-512 State                   */
    XC_uint32 count[4];        /* length of Message in bits   */
#endif

    XC_Octet buffer[XC_SHA512_BLOCKSIZE];   /* temporary buffer           */
} XC_SHA512State;

extern XC_int32  cat(XC_MD5Begin,UTILS_TYPE)
(XC_MD5State     *MD5State);

extern XC_int32  cat(iac_XC_SHA1Begin,UTILS_TYPE)
(XC_SHA1State     *SHAState);

extern XC_int32  cat(XC_SHA224Begin,UTILS_TYPE)
(XC_SHA224State     *SHAState);

extern XC_int32  cat(XC_SHA256Begin,UTILS_TYPE)
(XC_SHA256State     *SHAState);

extern XC_int32  cat(XC_SHA384Begin,UTILS_TYPE)
(XC_SHA384State     *SHAState);

extern XC_int32  cat(XC_SHA512Begin,UTILS_TYPE)
(XC_SHA512State     *SHAState);


extern XC_int32 cat(XC_MD5Process,UTILS_TYPE)
(XCData            *Message,
 XC_MD5State      *MD5State);

extern XC_int32 cat(iac_XC_SHA1Process,UTILS_TYPE)
(XCData            *Message,
 XC_SHA1State      *SHAState);

extern XC_int32 cat(XC_SHA224Process,UTILS_TYPE)
(XCData            *Message,
 XC_SHA224State      *SHAState);

extern XC_int32 cat(XC_SHA256Process,UTILS_TYPE)
(XCData            *Message,
 XC_SHA256State      *SHAState);

extern XC_int32 cat(XC_SHA384Process,UTILS_TYPE)
(XCData            *Message,
 XC_SHA384State      *SHAState);

extern XC_int32 cat(XC_SHA512Process,UTILS_TYPE)
(XCData            *Message,
 XC_SHA512State      *SHAState);


extern XC_int32 cat(XC_MD5End,UTILS_TYPE)
(XC_MD5State        *MD5State,
 XC_MD5Digest digest);

extern XC_int32 cat(iac_XC_SHA1End,UTILS_TYPE)
(XC_SHA1State        *SHAState,
 XC_SHA1Digest digest);

extern XC_int32 cat(XC_SHA224End,UTILS_TYPE)
(XC_SHA224State        *SHAState,
 XC_SHA224Digest digest);

extern XC_int32 cat(XC_SHA256End,UTILS_TYPE)
(XC_SHA256State        *SHAState,
 XC_SHA256Digest digest);

extern XC_int32 cat(XC_SHA384End,UTILS_TYPE)
(XC_SHA384State        *SHAState,
 XC_SHA384Digest digest);

extern XC_int32 cat(XC_SHA512End,UTILS_TYPE)
(XC_SHA512State        *SHAState,
 XC_SHA512Digest digest);


/* bitwise rotation to the left */
#define rotl(x,n)   (((x)>>(32 - (n))) | ((x) << (n)))

/* bitwise rotation to the right */
#define rotr(x,n)   (((x)<<(32 - (n))) | ((x) >> (n)))

/* bitwise rotation to the left (64 bit) */
#define rotl64(x,n)   (((x)>>(64 - (n))) | ((x) << (n)))

/* same thing, but where input is provided in 2-parts: 32 bit high and low,
   and it returns the high part of the result, and where n is 32 or smaller */
#define rotl64_2p_h(x_high,x_low,n)  (((x_low)>>(32 - (n))) | ((x_high) << (n)))

/* same thing, but where input is provided in 2-parts: 32 bit high and low,
   and it returns the low part of the result, and where n is 32 or smaller */
#define rotl64_2p_l(x_high,x_low,n)  (((x_high)>>(32 - (n))) | ((x_low) << (n)))

/* bitwise rotation to the right (64 bit) */
#define rotr64(x,n)   (((x)<<(64 - (n))) | ((x) >> (n)))

/* same thing, but where input is provided in 2-parts: 32 bit high and low,
   and it returns the high part of the result, and where n is 32 or smaller */
#define rotr64_2p_h(x_high,x_low,n)  (((x_low)<<(32 - (n))) | ((x_high) >> (n)))

/* same thing, but where input is provided in 2-parts: 64 bit high and low,
   and it returns the low part of the result, and where n is 32 or smaller */
#define rotr64_2p_l(x_high,x_low,n)  (((x_high)<<(32 - (n))) | ((x_low) >> (n)))

/* rotation to the right, size specific, with masking */
#define Srotr(x,n,bits)   (((x) << ((bits) - ((n)&((bits)-1))) ) | ((x) >> ((n)&((bits)-1))))

/* rotation to the left, size specific, with masking */
#define Srotl(x,n,bits)   (((x) >> ((bits) - ((n)&((bits)-1))) ) | ((x) << ((n)&((bits)-1))))

/* Adds two 64-bit unsigned numbers, where each 64-bit number is provided in 2-parts: high and low 32 bits. */
#define add64u_2p_h(x_h, x_l, y_h, y_l)   ((x_h) + (y_h) + (((x_l) + (y_l)) < (x_l) ? 1u : 0u))
#define add64u_2p_l(x_h, x_l, y_h, y_l)   ((x_l) + (y_l))

/* Adds second 64-bit number to first, storing result in first, where each 64
   bit number is provided in parts */
#define inc64u_2p(left_h, left_l, right_h, right_l) \
    { \
        left_h = add64u_2p_h(left_h, left_l, right_h, right_l);  \
        left_l = left_l + right_l;  \
    }


/* Basisc for runtime endian checks */
#if XC_RUNTIME_ENDIAN_CHECK

/* Returns true if this is a big endian system */
static const XC_int32 xc_oneValue = 1;
#define isBigEndian()   (*((const XC_uint8 *)(const void *) &xc_oneValue) == 0)

#endif

/* translates little endian <----> big endian */
#if XC_RUNTIME_ENDIAN_CHECK

static XC_uint32 cat(bswap,UTILS_TYPE)(XC_uint32 y)
{
    if(!isBigEndian())
        return ((rotr(y, 8) & 0xff00ff00) | (rotl(y, 8) & 0x00ff00ff));
    return y;
}

#else

#if defined XC_BIG_ENDIAN
#define bswap(y)   (y)
#else
#define bswap(y)   ((rotr(y, 8) & 0xff00ff00) | (rotl(y, 8) & 0x00ff00ff))
#endif
#define bswap_Stub bswap
#define bswap_Smooth bswap
#define bswap_RSA bswap
#define bswap_ECC bswap
#define bswap_Flexbin bswap
#endif

/* translates big endian <----> little endian */
#if XC_RUNTIME_ENDIAN_CHECK

static XC_uint32 cat(lswap,UTILS_TYPE)(XC_uint32 y)
{
    if(isBigEndian())
        return ((rotr(y, 8) & 0xff00ff00) | (rotl(y, 8) & 0x00ff00ff));
    return y;
}

#else

#if defined XC_BIG_ENDIAN
#define lswap(y)   ((rotr(y, 8) & 0xff00ff00) | (rotl(y, 8) & 0x00ff00ff))
#else
#define lswap(y)   (y)
#endif
#define lswap_Stub lswap
#define lswap_Smooth lswap
#define lswap_RSA lswap
#define lswap_ECC lswap
#endif

#ifdef XC_SUPPORTS_64_BITS

#if !defined (XC_RUNTIME_ENDIAN_CHECK) && defined (XC_BIG_ENDIAN)
#undef bswap64
#define bswap64(y)   (y)
#define bswap64_Stub bswap
#define bswap64_Smooth bswap
#define bswap64_RSA bswap
#define bswap64_ECC bswap

#else

static XCLong cat(bswap64,UTILS_TYPE)(XCLong data)
{
#if defined (XC_RUNTIME_ENDIAN_CHECK)
    if(isBigEndian())
        return data;
#endif

    union {
        XCLong ull;
        XC_uint32 ul[2];
    } u;

    u.ul[0] = (XCWord) (data >> 32);
    u.ul[1] = (XCWord) (data & 0xffffffff);
    u.ul[0] = bswap(u.ul[0]);
    u.ul[1] = bswap(u.ul[1]);

    return u.ull;
}

#endif

#endif /* XC_SUPPORTS_64_BITS */

#ifdef __cplusplus
}
#endif

#endif /* _XC_HASHH_ */

