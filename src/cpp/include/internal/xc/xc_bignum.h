/**********************************************************************************
Irdeto B.V.
June 11, 2013
FILE: xc_bignum.h

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

**********************************************************************************/

#if !defined ( __XC_BIGNUM_H__ )
#define __XC_BIGNUM_H__

#define cat(p1,p2) docat(p1,p2)
#define docat(p1,p2) p1##p2

#define ac_2(p1,p2) doac_2(p1,p2)
#define doac_2(p1,p2) p1##p2


#include <xc/xc_extensions.h>
#include <xc/xc_stdlib.h>
#include <xc/xc_types.h>
#include <xc/xc_errors.h>
#include <xc/xc_hash.h>

#include "ac_Stdlib_Internal.h"

/*
   These have to change for RISO
*/

typedef XC_uint16 XC_INT16;
typedef XC_uint32 XC_BigInt;


#define XC_BIGINT_BITS        ((XC_uint32)( sizeof(XC_BigInt) * 8 ))
#define XC_BIGINT_BYTES       ((XC_uint32)( sizeof(XC_BigInt) ))
#define XC_BIGINT_MASK        0xFFFFFFFF
#define XC_BIGINT_HIGH_BIT    0x80000000

#define XC_INT16_BITS   ((XC_uint32)(sizeof(XC_INT16) * 8))
#define XC_INT16_BYTES  ((XC_uint32)(sizeof(XC_INT16)))
#define XC_INT16_MASK   0xFFFF


/**
   The base type for all big number operations, XC_BigNum, is an array of 4-byte integers, stored LSB to MSB, such that array[0] is the LSB.
 */

#define XC_BigNum XC_BigInt *


/*********** Signs type for bignums *********/
typedef XC_int32 XC_BigNum_Sign;
enum {
    XC_NEGATIVE,
    XC_ZERO,
    XC_POSITIVE
};


#define HIGH_BN(x) ((x >> XC_BIGINT_BITS))
#define LOW_BN(x) ((x) & 0x00000000FFFFFFFF)

#define HIGH_16(t) (((t) >> XC_INT16_BITS) & XC_INT16_MASK)



#define XC_BigNum_Free(data) \
    XC_free(data)


#define XC_BigNum_Secure_Free(data, size) \
    { \
        if ((data != 0) && (size > 0)) \
        { \
            XC_secure_free(data, (size * sizeof(XC_BigInt))); \
        } \
    }


#define XC_BigNum_DblInt_Secure_Free(data, size) \
    { \
        if ((data != 0) && (size > 0)) \
        { \
            XC_secure_free(data, (size * sizeof(XC_BigDblInt))); \
        } \
    }


#define XC_BigNum_Alloc(length) \
    ((XC_BigNum) (XC_malloc(((length) * ((XC_uint32)sizeof(XC_BigInt))))) )

#define XC_BigDblInt_Alloc(length) \
    (_xc_transformcast(_xc_transform XC_BigDblInt *) (XC_malloc(((length) * ((XC_uint32)sizeof(XC_BigDblInt))))) )

#if XC_WB_DEBUG_LEVEL > 0
static void cat(XC_BigNum_Dump,UTILS_TYPE)(_xc_transform XC_BigNum data, XC_int32 length, XC_char * description);
#else
#define XC_BigNum_Dump( data, length, description )
#define XC_BigNum_Dump_RSA XC_BigNum_Dump
#define XC_BigNum_Dump_ECC XC_BigNum_Dump
#define XC_BigNum_Dump_Smooth XC_BigNum_Dump
#endif /* XC_WB_DEBUG_LEVEL > 0 */


static XC_int32 cat(XC_BigNum_IsZero,UTILS_TYPE)(_xc_transform XC_BigNum in, XC_int32 length)
{
    XC_int32 i;
    for (i=0; i<(length); i++)
        if (in[i] != 0x0)
            return 0;

    return 1;
}


XC_int32 cat(XC_BigNum_Shift,UTILS_TYPE)(_xc_transform XC_BigNum output, _xc_transform XC_BigNum input, XC_int32 shiftamt, XC_int32 length);

XC_int32 cat(XC_BigNum_Multiply,UTILS_TYPE)(_xc_transform XC_BigNum product, _xc_transform XC_BigNum multiplicand, _xc_transform XC_BigNum multiplier, XC_int32 inputLength);

XC_int32 cat(XC_BigNum_Add,UTILS_TYPE)(_xc_transform XC_BigNum out, _xc_transform XC_BigNum addend, _xc_transform XC_BigNum augend, XC_int32 length);

/* NB: This is a temporary function.  We can get rid of it as soon as we implement robust DK WBECC. */
_xc_preserve_interface XC_int32 cat(XC_BigNum_Add_Untransformed,UTILS_TYPE)(XC_BigNum out, XC_BigNum addend, XC_BigNum augend, XC_int32 length);

XC_int32 cat(XC_BigNum_ModAdd,UTILS_TYPE)(_xc_transform XC_BigNum out, _xc_transform XC_BigNum addend, _xc_transform XC_BigNum augend, _xc_transform XC_BigNum modulus, XC_int32 length);

XC_int32 cat(XC_BigNum_Compare,UTILS_TYPE)(_xc_transform XC_BigNum lhs, _xc_transform XC_BigNum rhs, XC_int32 length);

#define XC_BIGNUM_GREATER(A, B, length) (cat(XC_BigNum_Compare,UTILS_TYPE)(A, B, length) > 0)
#define XC_BIGNUM_LESS(A, B, length) ( (cat(XC_BigNum_Compare,UTILS_TYPE)(A, B, length) < 0 ) )
#define XC_BIGNUM_EQUAL(A, B, length) ( (cat(XC_BigNum_Compare,UTILS_TYPE)(A, B, length) == 0 ) )

XC_int32 cat(XC_BigNum_Signed_Subtract,UTILS_TYPE)(_xc_transform XC_BigNum out, XC_BigNum_Sign * poutputSign, _xc_transform XC_BigNum minuend, XC_BigNum_Sign minuendsign, _xc_transform XC_BigNum subtrahend, XC_BigNum_Sign subtrahendSign, XC_int32 inputLength);

XC_int32 cat(XC_BigNum_Subtract,UTILS_TYPE)(_xc_transform XC_BigNum difference, _xc_transform XC_BigNum minuend, _xc_transform XC_BigNum subtrahend, XC_int32 inputLength);

XC_int32 cat(XC_BigNum_ModSubtract,UTILS_TYPE)(_xc_transform XC_BigNum output, _xc_transform XC_BigNum minuend, _xc_transform XC_BigNum subtrahend, _xc_transform XC_BigNum modulus, XC_int32 length);

XC_int32 cat(XC_BigNum_ModInverse,UTILS_TYPE)(_xc_transform XC_BigNum inverse, _xc_transform XC_BigNum value, _xc_transform XC_BigNum modulus, XC_int32 inputLength);

XC_int32 cat(XC_BigNum_ModInverse_Prime,UTILS_TYPE)(_xc_transform XC_BigNum inverse, _xc_transform XC_BigNum value, _xc_transform XC_BigNum modulus, XC_int32 inputLength);

XC_int32 cat(XC_BigNum_DivMod,UTILS_TYPE)(_xc_transform XC_BigNum remainder, _xc_transform XC_BigNum quotient, _xc_transform XC_BigNum dividend, _xc_transform XC_BigNum divisor, XC_int32 inputLength);

XC_int32 cat(XC_BigNum_ModMul,UTILS_TYPE)(_xc_transform XC_BigNum output, _xc_transform XC_BigNum multiplicand, _xc_transform XC_BigNum multiplier, _xc_transform XC_BigNum modulus, XC_int32 inputlength);

XC_int32 cat(XC_BigNum_ModMul_Special,UTILS_TYPE)(XC_int32 ellipticCurve, _xc_transform XC_BigNum output, _xc_transform XC_BigNum multiplicand, _xc_transform XC_BigNum multiplier, _xc_transform XC_BigNum modulus, XC_int32 inputlength);

#define XC_BIGNUM_MOD(A, B, C, len) (cat(XC_BigNum_DivMod,UTILS_TYPE)(A, NULL, B, C, len)) /*This one should no longer be used, since XC_BigNum_DivMod returns a quotient now.*/

_xc_preserve_interface XC_int32 cat(XC_BigNum_ModExp,UTILS_TYPE)(XC_BigNum result, XC_BigNum base, XC_BigNum exponent,  XC_BigNum modulus, XC_int32 length);

_xc_preserve_interface XC_int32 cat(XC_BigNum_Multiply_Preserved,UTILS_TYPE)(XC_BigNum product, XC_BigNum multiplicand, XC_BigNum multiplier, XC_int32 inputLength);

_xc_preserve_interface XC_int32 cat(XC_BigNum_Subtract_Preserved,UTILS_TYPE)(XC_BigNum output, XC_BigNum minuend, XC_BigNum subtrahend, XC_int32 inputLength);

_xc_preserve_interface XC_int32 cat(XC_BigNum_DivMod_Preserved,UTILS_TYPE)(XC_BigNum remainder, XC_BigNum quotient, XC_BigNum dividend, XC_BigNum divisor, XC_int32 length);



XC_int32 cat(XC_BigNum_Mod_P192,UTILS_TYPE)(_xc_transform XC_BigNum remainder, _xc_transform XC_BigNum a, XC_int32 length);
XC_int32 cat(XC_BigNum_Mod_P224,UTILS_TYPE)(_xc_transform XC_BigNum remainder, _xc_transform XC_BigNum a, XC_int32 length);
XC_int32 cat(XC_BigNum_Mod_P256,UTILS_TYPE)(_xc_transform XC_BigNum remainder, _xc_transform XC_BigNum a, XC_int32 length);
XC_int32 cat(XC_BigNum_Mod_P384,UTILS_TYPE)(_xc_transform XC_BigNum remainder, _xc_transform XC_BigNum a, XC_int32 length);
XC_int32 cat(XC_BigNum_Mod_P521,UTILS_TYPE)(_xc_transform XC_BigNum remainder, _xc_transform XC_BigNum a, XC_int32 length);



/* This is only in the header file for testing. */
/*_xc_must_inline int32_t cat(XC_BigNum_MontgomeryMultiplication,UTILS_TYPE)(_xc_transform XC_BigInt * product, _xc_transform XC_BigInt * X, _xc_transform  XC_BigInt * Y, _xc_transform  XC_BigNum M, _xc_transform  XC_BigNum A, int32_t mPrime, int32_t length);*/


#define XC_BigNum_GetWordFromPosition(data, position, length) \
    ( \
        ( ((data)[position / XC_BIGINT_BITS] << (XC_BIGINT_BITS - ((position % XC_BIGINT_BITS) + 1))) | ((data)[(position / XC_BIGINT_BITS)-1] >> (((position) % XC_BIGINT_BITS) + 1)) ) \
    )

#define XC_BigNum_GetWordFromPosition_RSA XC_BigNum_GetWordFromPosition
#define XC_BigNum_GetWordFromPosition_ECC XC_BigNum_GetWordFromPosition
#define XC_BigNum_GetWordFromPosition_Smooth XC_BigNum_GetWordFromPosition


#define XC_BigNum_SetBit(out, bit, length) \
    (out)[bit / XC_BIGINT_BITS] |= (0x1 << (bit % XC_BIGINT_BITS));

#define XC_BigNum_SetBit_RSA XC_BigNum_SetBit
#define XC_BigNum_SetBit_ECC XC_BigNum_SetBit
#define XC_BigNum_SetBit_Smooth XC_BigNum_SetBit


#define XC_BigNum_Copy(out, in, length) \
    { \
        XC_int32 XC_BigNum_Copy_i; \
        for (XC_BigNum_Copy_i=0; XC_BigNum_Copy_i<(length); XC_BigNum_Copy_i++) (out)[XC_BigNum_Copy_i] = (in)[XC_BigNum_Copy_i];\
    }

#define XC_BigNum_Copy_RSA XC_BigNum_Copy
#define XC_BigNum_Copy_ECC XC_BigNum_Copy
#define XC_BigNum_Copy_Smooth XC_BigNum_Copy


#define XC_BigNum_SetZero(out, length) \
    { \
        XC_int32 XC_BigNum_SetZero_i; \
        for (XC_BigNum_SetZero_i=0; XC_BigNum_SetZero_i<(length); XC_BigNum_SetZero_i++) out[XC_BigNum_SetZero_i] = 0x0;\
    }

#define XC_BigNum_SetZero_RSA XC_BigNum_SetZero
#define XC_BigNum_SetZero_ECC XC_BigNum_SetZero
#define XC_BigNum_SetZero_Smooth XC_BigNum_SetZero


static ac_int32 my_BigNum2Octet(XC_Octet* target, XC_BigNum orig, XC_int32 origLen)
{
    XC_int32 my_BigNum2Octet_word = ((XC_uint32) (origLen-1))/4;
    XC_int32 my_BigNum2Octet_byte = ((XC_uint32) (origLen-1))%4;

    while ( ( my_BigNum2Octet_word >= 0) && ( my_BigNum2Octet_byte >= 0 ) )
    {
		XC_int32 targetOffset;
		XC_Octet targetValue;
		XC_uint32 tmpWord;

		targetOffset = origLen - (my_BigNum2Octet_word)*((XC_uint32)sizeof(XC_BigInt)) - my_BigNum2Octet_byte - 1;
		tmpWord = (XC_uint32)orig[my_BigNum2Octet_word];
		targetValue = (XC_Octet)(tmpWord >> ((XC_uint32)my_BigNum2Octet_byte * 8));
		target[targetOffset] = targetValue;
        if (my_BigNum2Octet_byte == 0)
        {
            my_BigNum2Octet_byte = 3;
            my_BigNum2Octet_word--;
        }
        else
        {
            my_BigNum2Octet_byte--;
        }
    }

	return origLen;
}


#define XC_Octet2BigNum( target, targetLen, orig, origLen)  \
    { \
        XC_int32 XC_Octet2BigNum_i = 0; \
         \
        (*targetLen) = ( ((XC_uint32)(origLen) - 1) / ((XC_uint32)sizeof(XC_BigInt)) ) + 1; \
        (*target) = XC_BigNum_Alloc( *targetLen ); \
         \
        for (XC_Octet2BigNum_i = 0; XC_Octet2BigNum_i < (*targetLen) ; XC_Octet2BigNum_i++ ) \
        { \
            (*target)[ XC_Octet2BigNum_i ] = 0; \
        } \
        \
        for ( XC_Octet2BigNum_i = (origLen-1); XC_Octet2BigNum_i >= 0; XC_Octet2BigNum_i-- ) \
        { \
            XC_Octet XC_Octet2BigNum_byte = (orig)[ (origLen) - XC_Octet2BigNum_i - 1]; \
            (*target)[(XC_uint32) XC_Octet2BigNum_i / XC_BIGINT_BYTES] |= XC_Octet2BigNum_byte << ((XC_uint32) (8 * XC_Octet2BigNum_i) % XC_BIGINT_BITS); \
        } \
 \
    }


#define XC_Octet2BigNum_RSA XC_Octet2BigNum
#define XC_Octet2BigNum_ECC XC_Octet2BigNum
#define XC_Octet2BigNum_Smooth XC_Octet2BigNum
    
/*
  the macro below assumes that target, which is a BigNum, has
  already been allocated space.        
*/
#define XC_Octet2BigNum_NoAlloc( target, targetInitLen, targetLen, orig, origLen) \
    { \
        XC_int32 XC_Octet2BigNum_i = 0; \
         \
        (*targetLen) = ( ((XC_uint32)(origLen) - 1) / ((XC_uint32)sizeof(XC_BigInt)) ) + 1; \
         \
        for (XC_Octet2BigNum_i = 0; XC_Octet2BigNum_i < (targetInitLen); XC_Octet2BigNum_i++ ) \
        { \
          (target)[ XC_Octet2BigNum_i ] = 0;    \
        } \
        \
        for ( XC_Octet2BigNum_i = (origLen-1); XC_Octet2BigNum_i >= 0; XC_Octet2BigNum_i-- ) \
        { \
            XC_Octet XC_Octet2BigNum_byte = (orig)[ (origLen) - XC_Octet2BigNum_i - 1]; \
            (target)[(XC_uint32) XC_Octet2BigNum_i / XC_BIGINT_BYTES] |= XC_Octet2BigNum_byte << ((XC_uint32) (8 * XC_Octet2BigNum_i) % XC_BIGINT_BITS); \
        } \
 \
    }

#define XC_Octet2BigNum_NoAlloc_RSA XC_Octet2BigNum_NoAlloc
#define XC_Octet2BigNum_NoAlloc_ECC XC_Octet2BigNum_NoAlloc
#define XC_Octet2BigNum_NoAlloc_Smooth XC_Octet2BigNum_NoAlloc

#define XC_Octet2BigNum_Transform( target, targetLen, orig, origLen)  \
    { \
        XC_int32 XC_Octet2BigNum_i = 0; \
         \
        (*targetLen) = ( ((XC_uint32)(origLen) - 1) / ((XC_uint32)sizeof(XC_BigInt)) ) + 1; \
        (*target) = _xc_transformcast(_xc_transform XC_BigNum) (XC_BigNum_Alloc( *targetLen )); \
         \
        for (XC_Octet2BigNum_i = 0; XC_Octet2BigNum_i < (*targetLen) ; XC_Octet2BigNum_i++ ) \
        { \
            (*target)[ XC_Octet2BigNum_i ] = 0; \
        } \
        \
        for ( XC_Octet2BigNum_i = (origLen-1); XC_Octet2BigNum_i >= 0; XC_Octet2BigNum_i-- ) \
        { \
            XC_Octet XC_Octet2BigNum_byte = (orig)[ (origLen) - XC_Octet2BigNum_i - 1]; \
            (*target)[(XC_uint32) XC_Octet2BigNum_i / XC_BIGINT_BYTES] |= XC_Octet2BigNum_byte << ((XC_uint32) (8 * XC_Octet2BigNum_i) % XC_BIGINT_BITS); \
        } \
 \
    }

#define XC_Octet2BigNum_Transform_RSA XC_Octet2BigNum_Transform
#define XC_Octet2BigNum_Transform_ECC XC_Octet2BigNum_Transform
#define XC_Octet2BigNum_Transform_Smooth XC_Octet2BigNum_Transform


#ifndef XC_RESTRICTED_ISO_32BIT
#define XC_BigNum_MontgomeryMultiplication(product, X, Y, M, A, mPrime, mbits) \
    { \
        XC_uint32 MontMul_M_bits = mbits; \
        XC_uint32 MontMul_M_digits; \
        \
        XC_int32 MontMul_i; \
        XC_int32 MontMul_k; \
        XC_BigInt MontMul_u; \
        XC_BigDblInt MontMul_tmp; \
        XC_BigDblInt MontMul_t = 0; \
        \
        MontMul_M_digits = (MontMul_M_bits - 1)/XC_BIGINT_BITS + 1; \
        MontMul_M_digits = MontMul_M_digits + 1; \
        ac_2(XC_BigNum_SetZero,UTILS_TYPE)((A), MontMul_M_digits+2); \
        \
        for (MontMul_i=0; MontMul_i<MontMul_M_digits; MontMul_i++) \
        { \
            MontMul_tmp = 0; \
            for (MontMul_k = 0; MontMul_k<MontMul_M_digits; MontMul_k++) \
            { \
                MontMul_t = Y[MontMul_k]; \
                MontMul_tmp += (A[MontMul_k]) + MontMul_t * (X[MontMul_i]); \
                (A[MontMul_k]) = (XC_BigInt) MontMul_tmp; \
                MontMul_tmp = HIGH_BN(MontMul_tmp); \
            } \
            MontMul_tmp += (A[MontMul_k]); \
            (A[MontMul_k++]) = (XC_BigInt) MontMul_tmp; \
            (A[MontMul_k])   = (XC_BigInt) HIGH_BN(MontMul_tmp); \
                \
            MontMul_u = (XC_BigInt) ((A[0]) * (mPrime)); \
            MontMul_t = M[0]; \
            MontMul_tmp = (A[0]) + MontMul_t * MontMul_u; \
            MontMul_tmp = HIGH_BN(MontMul_tmp); \
            for (MontMul_k = 1; MontMul_k<MontMul_M_digits; MontMul_k++) \
            { \
                MontMul_t = M[MontMul_k]; \
                MontMul_tmp += (A[MontMul_k]) + MontMul_t * MontMul_u; \
                (A[MontMul_k-1]) = (XC_BigInt) MontMul_tmp; \
                MontMul_tmp = HIGH_BN(MontMul_tmp); \
            } \
            MontMul_tmp += (A[MontMul_k]); \
            (A[MontMul_k-1]) = (XC_BigInt) MontMul_tmp; \
            (A[MontMul_k])   = (XC_BigInt) HIGH_BN(MontMul_tmp) + (A[MontMul_k+1]); \
        } \
        \
        (product)[MontMul_M_digits-1] = 0; \
        ac_2(XC_BigNum_Copy,UTILS_TYPE)((product), (A), MontMul_M_digits - 1); \
    }

#else

#define XC_BigNum_MontgomeryMultiplication(product, X, Y, M, A, mPrime, mbits) \
    { \
        XC_uint32 MontMul_M_bits = mbits; \
        XC_uint32 MontMul_M_digits; \
        \
        XC_int32 MontMul_i; \
        XC_int32 MontMul_k; \
        XC_BigInt MontMul_u; \
        _xc_transform XC_BigNum MontMul_tmp = _xc_transformcast(_xc_transform XC_BigNum) XC_BigNum_Alloc(3); \
        _xc_transform XC_BigNum MontMul_t = _xc_transformcast(_xc_transform XC_BigNum) XC_BigNum_Alloc(2); \
        ac_2(XC_BigNum_SetZero,UTILS_TYPE)((MontMul_tmp), 3); \
        ac_2(XC_BigNum_SetZero,UTILS_TYPE)((MontMul_t), 2); \
        \
        MontMul_M_digits = (MontMul_M_bits - 1)/XC_BIGINT_BITS + 1; \
        MontMul_M_digits = MontMul_M_digits + 1; \
        ac_2(XC_BigNum_SetZero,UTILS_TYPE)((A), MontMul_M_digits+2); \
        \
        for (MontMul_i=0; MontMul_i<MontMul_M_digits; MontMul_i++) \
        { \
            ac_2(XC_BigNum_SetZero,UTILS_TYPE)((MontMul_tmp), 3); \
            for (MontMul_k = 0; MontMul_k<MontMul_M_digits; MontMul_k++) \
            { \
                MontMul_t[0] = Y[MontMul_k]; \
                MontMul_t[1] = 0; \
                ac_2(XC_BigNum_LongMultiply,UTILS_TYPE)(MontMul_t, MontMul_t, (X[MontMul_i]), 1); \
                ac_2(XC_BigNum_LongAdd,UTILS_TYPE)(MontMul_tmp, MontMul_tmp, (A[MontMul_k]), 2); \
                ac_2(XC_BigNum_Add,UTILS_TYPE)(MontMul_tmp, MontMul_tmp, MontMul_t, 2); \
                (A[MontMul_k]) = MontMul_tmp[0]; \
                MontMul_tmp[0] = MontMul_tmp[1]; \
                MontMul_tmp[1] = 0; \
                MontMul_tmp[2] = 0; \
            } \
            ac_2(XC_BigNum_LongAdd,UTILS_TYPE)(MontMul_tmp, MontMul_tmp, (A[MontMul_k]), 2); \
            (A[MontMul_k++]) = MontMul_tmp[0]; \
            (A[MontMul_k]) = MontMul_tmp[1]; \
                \
            MontMul_u = (XC_BigInt) ((A[0]) * (mPrime)); \
            MontMul_t[0] = M[0]; \
            MontMul_t[1] = 0; \
            ac_2(XC_BigNum_SetZero,UTILS_TYPE)((MontMul_tmp), 3); \
            ac_2(XC_BigNum_LongMultiply,UTILS_TYPE)(MontMul_t, MontMul_t, MontMul_u, 1); \
            ac_2(XC_BigNum_LongAdd,UTILS_TYPE)(MontMul_tmp, MontMul_tmp, (A[0]), 2); \
            ac_2(XC_BigNum_Add,UTILS_TYPE)(MontMul_tmp, MontMul_tmp, MontMul_t, 2); \
            MontMul_tmp[0] = MontMul_tmp[1]; \
            MontMul_tmp[1] = 0; \
            MontMul_tmp[2] = 0; \
            for (MontMul_k = 1; MontMul_k<MontMul_M_digits; MontMul_k++) \
            { \
                MontMul_t[0] = M[MontMul_k]; \
                MontMul_t[1] = 0; \
                ac_2(XC_BigNum_LongMultiply,UTILS_TYPE)(MontMul_t, MontMul_t, MontMul_u, 1); \
                ac_2(XC_BigNum_LongAdd,UTILS_TYPE)(MontMul_tmp, MontMul_tmp, (A[MontMul_k]), 2); \
                ac_2(XC_BigNum_Add,UTILS_TYPE)(MontMul_tmp, MontMul_tmp, MontMul_t, 2); \
                (A[MontMul_k-1]) = MontMul_tmp[0]; \
                MontMul_tmp[0] = MontMul_tmp[1]; \
                MontMul_tmp[1] = 0; \
                MontMul_tmp[2] = 0; \
            } \
            ac_2(XC_BigNum_LongAdd,UTILS_TYPE)(MontMul_tmp, MontMul_tmp, (A[MontMul_k]), 2); \
            (A[MontMul_k-1]) = MontMul_tmp[0]; \
            (A[MontMul_k]) = MontMul_tmp[1] + (A[MontMul_k+1]); \
        } \
        \
        (product)[MontMul_M_digits-1] = 0; \
        ac_2(XC_BigNum_Copy,UTILS_TYPE)((product), (A), MontMul_M_digits - 1); \
        \
        if(MontMul_tmp != NULL){ \
            XC_BigNum_Secure_Free(_xc_transformcast (void *)(MontMul_tmp), 3); \
        } \
        if(MontMul_t != NULL){ \
            XC_BigNum_Secure_Free(_xc_transformcast (void *)(MontMul_t), 2); \
        } \
    }

#endif


#ifndef XC_RESTRICTED_ISO_32BIT
/* the following macro requires that mbits == XC_BigNum_BitCount(M, length(M)) */
#define XC_BigNum_MontgomeryMultiplication_64(product, X, Y, M, A, mPrime, mbits) \
    { \
        XC_uint32 MontMul_M_bits = mbits; \
        XC_uint32 MontMul_M_digits; \
        \
        XC_int32 MontMul_i; \
        XC_int32 MontMul_k; \
        _xc_transform XC_BigDblInt MontMul_u = 0; \
        _xc_transform XC_BigDblInt MontMul_tmp = 0; \
        _xc_transform XC_BigDblInt MontMul_t = 0; \
        \
        MontMul_M_digits = (MontMul_M_bits - 1)/XC_BIGINT_BITS + 1; \
        MontMul_M_digits = MontMul_M_digits + 1; \
        ac_2(XC_BigNum_SetZero,UTILS_TYPE)((A), MontMul_M_digits+2); \
        \
        for (MontMul_i=0; MontMul_i<MontMul_M_digits; MontMul_i++) \
        { \
            MontMul_tmp = 0; \
            for (MontMul_k = 0; MontMul_k<MontMul_M_digits; MontMul_k++) \
            { \
                MontMul_t = Y[MontMul_k]; \
                MontMul_tmp += (A[MontMul_k]) + MontMul_t * (X[MontMul_i]); \
                (A[MontMul_k]) =  LOW_BN(MontMul_tmp); \
                MontMul_tmp = HIGH_BN(MontMul_tmp); \
            } \
            MontMul_tmp += (A[MontMul_k]); \
            (A[MontMul_k++]) = LOW_BN(MontMul_tmp); \
            (A[MontMul_k])   = HIGH_BN(MontMul_tmp); \
                \
            MontMul_u = LOW_BN ((A[0]) * (mPrime)); \
            MontMul_t = M[0]; \
            MontMul_tmp = (A[0]) + MontMul_t * MontMul_u; \
            MontMul_tmp = HIGH_BN(MontMul_tmp); \
            for (MontMul_k = 1; MontMul_k<MontMul_M_digits; MontMul_k++) \
            { \
                MontMul_t = M[MontMul_k]; \
                MontMul_tmp += (A[MontMul_k]) + MontMul_t * MontMul_u; \
                (A[MontMul_k-1]) = LOW_BN(MontMul_tmp); \
                MontMul_tmp = HIGH_BN(MontMul_tmp); \
            } \
            MontMul_tmp += (A[MontMul_k]); \
            (A[MontMul_k-1]) = LOW_BN(MontMul_tmp); \
            (A[MontMul_k])   = LOW_BN(HIGH_BN(MontMul_tmp) + (A[MontMul_k+1])); \
        } \
        \
        (product)[MontMul_M_digits-1] = 0; \
        ac_2(XC_BigNum_Copy,UTILS_TYPE)((product), (A), MontMul_M_digits - 1); \
    }

#else

#define XC_BigNum_MontgomeryMultiplication_64(product, X, Y, M, A, mPrime, mbits) \
    { \
        XC_uint32 MontMul_M_bits = mbits; \
        XC_uint32 MontMul_M_digits; \
        \
        XC_int32 MontMul_i; \
        XC_int32 MontMul_k; \
        XC_BigInt MontMul_u; \
        _xc_transform XC_BigNum MontMul_tmp = _xc_transformcast(_xc_transform XC_BigNum) XC_BigNum_Alloc(3); \
        _xc_transform XC_BigNum MontMul_t = _xc_transformcast(_xc_transform XC_BigNum) XC_BigNum_Alloc(2); \
        ac_2(XC_BigNum_SetZero,UTILS_TYPE)((MontMul_tmp), 3); \
        ac_2(XC_BigNum_SetZero,UTILS_TYPE)((MontMul_t), 2); \
        \
        MontMul_M_digits = (MontMul_M_bits - 1)/XC_BIGINT_BITS + 1; \
        MontMul_M_digits = MontMul_M_digits + 1; \
        ac_2(XC_BigNum_SetZero,UTILS_TYPE)((A), MontMul_M_digits+2); \
        \
        for (MontMul_i=0; MontMul_i<MontMul_M_digits; MontMul_i++) \
        { \
            ac_2(XC_BigNum_SetZero,UTILS_TYPE)((MontMul_tmp), 3); \
            for (MontMul_k = 0; MontMul_k<MontMul_M_digits; MontMul_k++) \
            { \
                MontMul_t[0] = Y[MontMul_k]; \
                MontMul_t[1] = 0; \
                ac_2(XC_BigNum_LongMultiply,UTILS_TYPE)(MontMul_t, MontMul_t, (X[MontMul_i]), 1); \
                ac_2(XC_BigNum_LongAdd,UTILS_TYPE)(MontMul_tmp, MontMul_tmp, (A[MontMul_k]), 2); \
                ac_2(XC_BigNum_Add,UTILS_TYPE)(MontMul_tmp, MontMul_tmp, MontMul_t, 2); \
                (A[MontMul_k]) = MontMul_tmp[0]; \
                MontMul_tmp[0] = MontMul_tmp[1]; \
                MontMul_tmp[1] = 0; \
                MontMul_tmp[2] = 0; \
            } \
            ac_2(XC_BigNum_LongAdd,UTILS_TYPE)(MontMul_tmp, MontMul_tmp, (A[MontMul_k]), 2); \
            (A[MontMul_k++]) = MontMul_tmp[0]; \
            (A[MontMul_k]) = MontMul_tmp[1]; \
                \
            MontMul_u = (XC_BigInt) ((A[0]) * (mPrime)); \
            MontMul_t[0] = M[0]; \
            MontMul_t[1] = 0; \
            ac_2(XC_BigNum_SetZero,UTILS_TYPE)((MontMul_tmp), 3); \
            ac_2(XC_BigNum_LongMultiply,UTILS_TYPE)(MontMul_t, MontMul_t, MontMul_u, 1); \
            ac_2(XC_BigNum_LongAdd,UTILS_TYPE)(MontMul_tmp, MontMul_tmp, (A[0]), 2); \
            ac_2(XC_BigNum_Add,UTILS_TYPE)(MontMul_tmp, MontMul_tmp, MontMul_t, 2); \
            MontMul_tmp[0] = MontMul_tmp[1]; \
            MontMul_tmp[1] = 0; \
            MontMul_tmp[2] = 0; \
            for (MontMul_k = 1; MontMul_k<MontMul_M_digits; MontMul_k++) \
            { \
                MontMul_t[0] = M[MontMul_k]; \
                MontMul_t[1] = 0; \
                ac_2(XC_BigNum_LongMultiply,UTILS_TYPE)(MontMul_t, MontMul_t, MontMul_u, 1); \
                ac_2(XC_BigNum_LongAdd,UTILS_TYPE)(MontMul_tmp, MontMul_tmp, (A[MontMul_k]), 2); \
                ac_2(XC_BigNum_Add,UTILS_TYPE)(MontMul_tmp, MontMul_tmp, MontMul_t, 2); \
                (A[MontMul_k-1]) = MontMul_tmp[0]; \
                MontMul_tmp[0] = MontMul_tmp[1]; \
                MontMul_tmp[1] = 0; \
                MontMul_tmp[2] = 0; \
            } \
            ac_2(XC_BigNum_LongAdd,UTILS_TYPE)(MontMul_tmp, MontMul_tmp, (A[MontMul_k]), 2); \
            (A[MontMul_k-1]) = MontMul_tmp[0]; \
            (A[MontMul_k]) = (XC_BigInt) MontMul_tmp[1] + (A[MontMul_k+1]); \
        } \
        \
        (product)[MontMul_M_digits-1] = 0; \
        ac_2(XC_BigNum_Copy,UTILS_TYPE)((product), (A), MontMul_M_digits - 1); \
        \
        if(MontMul_tmp != NULL){ \
            XC_BigNum_Secure_Free(_xc_transformcast(void*) (MontMul_tmp), 3); \
        } \
        if(MontMul_t != NULL){ \
            XC_BigNum_Secure_Free(_xc_transformcast(void*) (MontMul_t), 2); \
        } \
    }
#endif


static XC_int32 cat(XC_BigNum_BitCount,UTILS_TYPE)(_xc_transform XC_BigNum input, XC_int32 inputLength)
{
    XC_int32 count = (inputLength) * XC_BIGINT_BITS;
    XC_int32 word;
    XC_int32 bit = XC_BIGINT_BITS;
    for (word=(inputLength)-1; word>=0; word--)
    {
        if (input[word])
        {
            XC_uint32 tmp = 0x80000000;
            for (bit=XC_BIGINT_BITS-1; bit>=0; bit--)
            {
                if ( tmp & input[word] )
                    return count;
                else
                    count--;
                tmp >>= 1;
            }
        }
        else
        {
            count -= XC_BIGINT_BITS;
        }
    }
    return count;
}

/* the function below is used to shift an array of octets in-place
   (i.e. the input is modified).  This may not be the right place to
   put this */
static XC_int32 cat(XC_Octet_RightShift,UTILS_TYPE)(_xc_transform XC_Octet buf[], 
                                                                 XC_int32 bufLength,
                                                                 XC_int32 shift)
{  
  XC_int32 shift_octets;
  XC_int32 shift_bits;
  XC_Octet mask_values[8] = {0x00, 0x01, 0x03, 0x07, 0x0f, 0x1f, 0x3f, 0x7f};
  XC_Octet mask;
  XC_Octet tmp;
  XC_Octet hbits;
  XC_int32 i;

  if ( buf == NULL )
    return XC_BN_ERR_NULL_INPUT;
  
  if ( (shift < 0) || (shift > 8*bufLength) )
    return XC_BN_ERR_INTERNAL_ERROR;

  shift_bits = shift & 0x7;
  shift_octets = ((XC_uint32)shift) >> 3;

  mask = mask_values[shift_bits];

  /* do octet shift first */
  if ( shift_octets != 0 ) {
    for (i=bufLength-1; i>=shift_octets; i--)
      buf[i] = buf[i-shift_octets];
    for ( ; i>=0; i--)
      buf[i] = 0;
  }

  /* now do bit shift */
  if ( shift_bits != 0 ) {
    hbits = 0;
    for (i=shift_octets; i<bufLength; i++) {
      tmp = buf[i];
      buf[i] = hbits | (tmp >> (XC_uint32) shift_bits);
      hbits = ((XC_uint32)(tmp & mask)) << (8-(XC_uint32)shift_bits);
    }
  }
  

  return 0;
}

static XC_int32 cat(XC_BigNum_LongAdd,UTILS_TYPE)(_xc_transform XC_BigNum sum, _xc_transform XC_BigNum addend, _xc_transform XC_BigInt augend, XC_int32 inputLength)
{

    XC_int32 j;
    XC_int32 h;



    XC_uint32 augendtmp = 0;
    XC_uint16 carry_L = 0;
	XC_uint16 carry_H = 0;    
    
    if ( (addend == ac_NULL) || (sum == ac_NULL)){
        return XC_BN_ERR_NULL_INPUT;
    }

    augendtmp = augend;
    carry_L = (XC_uint16) augendtmp;
	carry_H = (XC_uint16) (HIGH_16(augendtmp));

    for (j=0; (j<inputLength) && ((carry_L != 0) || (carry_H != 0)); j++){

		XC_uint32 addendtmp = addend[j];
		XC_uint16 addend_L = (XC_uint16) addendtmp;
		XC_uint16 addend_H = (XC_uint16) (HIGH_16(addendtmp));

		XC_uint32 sum_low = (XC_uint32)addend_L + carry_L;
		XC_uint32 sum_high = (XC_uint32)addend_H + carry_H;
		
		XC_uint16 sum_low_L = (XC_uint16) sum_low;
		XC_uint16 sum_low_H = (XC_uint16) (HIGH_16(sum_low));
		XC_uint16 sum_high_L = (XC_uint16) sum_high;
		XC_uint16 sum_high_H = (XC_uint16) (HIGH_16(sum_high));

		XC_uint32 tmp_sum = (XC_uint32)sum_low_H + sum_high_L;
		
		XC_uint16 tmp_sum_L = (XC_uint16) tmp_sum;
		XC_uint16 tmp_sum_H = (XC_uint16) (HIGH_16(tmp_sum));

		sum[j] = (XC_uint32)sum_low_L + (((XC_uint32)tmp_sum_L) << XC_INT16_BITS);
		carry_L = (XC_uint16)(sum_high_H + tmp_sum_H);
        carry_H = 0;
    }

    for(h=j; h<inputLength; h++){
        sum[h] = addend[h];
    }

    if(carry_L != 0){
        return XC_BN_ERR_UNMANAGED_CARRY;
    }

    return XC_OK;
}


static XC_int32 cat(XC_BigNum_LongMultiply,UTILS_TYPE)(_xc_transform XC_BigNum product, _xc_transform XC_BigNum multiplicand, _xc_transform XC_BigInt multiplier, XC_int32 inputLength){
    XC_int32 j;


    XC_uint16 carry_L = 0;
	XC_uint16 carry_H = 0;
	XC_BigInt multiplier_tmp = 0;
	XC_uint16 multiplier_L = 0;
	XC_uint16 multiplier_H = 0;

    if ((multiplicand == ac_NULL) || (product == ac_NULL)){
        return XC_BN_ERR_NULL_INPUT;
    }

	multiplier_tmp = multiplier;
	multiplier_L = (XC_uint16) multiplier_tmp;
	multiplier_H = (XC_uint16) (HIGH_16(multiplier_tmp));

	for (j=0; j<inputLength; j++){
        XC_BigInt multiplicand_tmp = 0;
        XC_uint16 multiplicand_L = 0, multiplicand_H = 0;
        XC_BigInt mul_low = 0;
        XC_uint16 mul_low_L = 0;
        XC_uint16 mul_low_H = 0;
        XC_BigInt mul_midA = 0;
        XC_uint16 mul_midA_L = 0, mul_midA_H = 0;
        XC_BigInt mul_midB = 0;
        XC_uint16 mul_midB_L = 0, mul_midB_H = 0;
        XC_BigInt mul_high = 0;
        XC_uint16 mul_high_L = 0, mul_high_H = 0;
        XC_BigInt sum_low = 0;
        XC_uint16 sum_low_L = 0, sum_low_H = 0;
        XC_BigInt sum_high = 0;
        XC_uint16 sum_high_L = 0, sum_high_H = 0;

		multiplicand_tmp = multiplicand[j];
		multiplicand_L = (XC_uint16) multiplicand_tmp;
		multiplicand_H = (XC_uint16) (HIGH_16(multiplicand_tmp));
		
		mul_low = (XC_BigInt) multiplier_L * multiplicand_L;
		mul_low = mul_low + carry_L; 
		mul_low_L = (XC_uint16) mul_low;
		mul_low_H = (XC_uint16) (HIGH_16(mul_low));

		mul_midA = (XC_BigInt) multiplier_L * multiplicand_H;
		mul_midA_L = (XC_uint16) mul_midA;
		mul_midA_H = (XC_uint16) (HIGH_16(mul_midA));

		mul_midB = (XC_BigInt) multiplier_H * multiplicand_L;
		mul_midB_L = (XC_uint16) mul_midB;
		mul_midB_H = (XC_uint16) (HIGH_16(mul_midB));

		mul_high = (XC_BigInt) multiplier_H * multiplicand_H;
		mul_high_L = (XC_uint16) mul_high;
		mul_high_H = (XC_uint16) (HIGH_16(mul_high));

		sum_low = (XC_BigInt) mul_low_H + mul_midA_L + mul_midB_L + carry_H;
		sum_low_L = (XC_uint16) sum_low;
		sum_low_H = (XC_uint16) (HIGH_16(sum_low));
		
		/*Now, mul_low_L is the lower 16-bit of the result, and sum_low_L is the higher 16-bit of the result.*/

		product[j] = ((XC_BigInt) mul_low_L) | (((XC_uint32)sum_low_L) << XC_INT16_BITS);

		sum_high = (XC_BigInt) mul_midA_H + mul_midB_H + mul_high_L + sum_low_H;
		sum_high_L = (XC_uint16) sum_high;
		sum_high_H = (XC_uint16) (HIGH_16(sum_high));

		carry_H = (XC_uint16) (mul_high_H + sum_high_H); /*carry_H can never be greater than 0xFFFF.*/
		carry_L = sum_high_L;
	}
	/*This should be sufficient. */
	product[j] = ((XC_BigInt) carry_L) | (((XC_uint32)carry_H) << XC_INT16_BITS);


    return XC_OK;
}


#if XC_WB_DEBUG_LEVEL > 0
static void cat(XC_BigNum_Dump,UTILS_TYPE)( _xc_transform XC_BigNum data, XC_int32 length, XC_char * description){
    XC_int32 i = 0;

    if (description != ac_NULL)
    {
        XC_printf((char_t *)"%s\n", description);
    }

    if (data != ac_NULL)
    {
        for (i=0; i<length; i++)
        {
            XC_printf((char_t *)" 0x%08x, ", data[i]);
        }
    }
    XC_printf((char_t *)"\n\n");

    if (data != ac_NULL)
    {
        for (i=length; i>0; i--)
        {
            XC_printf((char_t *)"%08x", data[i-1]);
        }
    }
    XC_printf((char_t *)"\n\n");
}
#endif /* XC_WB_DEBUG_LEVEL > 0 */

#if 0
/* jmuir, 30 June 2010  */
#define XC_BigNum_Dump_Words( PTR, WORDS) \
  { \
    XC_int32 i = 0;\
    XC_printf(#PTR (char_t *)": ");\
    for (i=(WORDS)-1; i>=0; i--)                     \
      XC_printf((char_t *)"%0*x ", 2*sizeof(*(PTR)), (PTR)[i]);  \
    XC_printf((char_t *)"\n");\
  }
#endif /* if 0 */

#endif /* defined __XC_BIGNUM_H__ */
/* RISO Converted */
