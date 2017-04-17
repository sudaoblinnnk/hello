#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "iso98wrap.h"
#include "DexHeader.h"
#include "dexOperator.h"
#include "dexOptimize.h"
#include "ac_Stdlib_Internal.h"


// The start of the code copied from Android source
/*
 * Switch-statement signatures are a "NOP" followed by a code.  (A true NOP
 * is 0x0000.)
 */
#define kPackedSwitchSignature  0x0100
#define kSparseSwitchSignature  0x0200
#define kArrayDataSignature     0x0300

typedef char boolean;
typedef unsigned int u4;
typedef unsigned short u2;
typedef unsigned char u1;

/*
 * Dalvik opcode list.
 */
typedef enum OpCode {
    OP_NOP                          = 0x00,

    OP_MOVE                         = 0x01,
    OP_MOVE_FROM16                  = 0x02,
    OP_MOVE_16                      = 0x03,
    OP_MOVE_WIDE                    = 0x04,
    OP_MOVE_WIDE_FROM16             = 0x05,
    OP_MOVE_WIDE_16                 = 0x06,
    OP_MOVE_OBJECT                  = 0x07,
    OP_MOVE_OBJECT_FROM16           = 0x08,
    OP_MOVE_OBJECT_16               = 0x09,

    OP_MOVE_RESULT                  = 0x0a,
    OP_MOVE_RESULT_WIDE             = 0x0b,
    OP_MOVE_RESULT_OBJECT           = 0x0c,
    OP_MOVE_EXCEPTION               = 0x0d,

    OP_RETURN_VOID                  = 0x0e,
    OP_RETURN                       = 0x0f,
    OP_RETURN_WIDE                  = 0x10,
    OP_RETURN_OBJECT                = 0x11,

    OP_CONST_4                      = 0x12,
    OP_CONST_16                     = 0x13,
    OP_CONST                        = 0x14,
    OP_CONST_HIGH16                 = 0x15,
    OP_CONST_WIDE_16                = 0x16,
    OP_CONST_WIDE_32                = 0x17,
    OP_CONST_WIDE                   = 0x18,
    OP_CONST_WIDE_HIGH16            = 0x19,
    OP_CONST_STRING                 = 0x1a,
    OP_CONST_STRING_JUMBO           = 0x1b,
    OP_CONST_CLASS                  = 0x1c,

    OP_MONITOR_ENTER                = 0x1d,
    OP_MONITOR_EXIT                 = 0x1e,

    OP_CHECK_CAST                   = 0x1f,
    OP_INSTANCE_OF                  = 0x20,

    OP_ARRAY_LENGTH                 = 0x21,

    OP_NEW_INSTANCE                 = 0x22,
    OP_NEW_ARRAY                    = 0x23,

    OP_FILLED_NEW_ARRAY             = 0x24,
    OP_FILLED_NEW_ARRAY_RANGE       = 0x25,
    OP_FILL_ARRAY_DATA              = 0x26,

    OP_THROW                        = 0x27,
    OP_GOTO                         = 0x28,
    OP_GOTO_16                      = 0x29,
    OP_GOTO_32                      = 0x2a,
    OP_PACKED_SWITCH                = 0x2b,
    OP_SPARSE_SWITCH                = 0x2c,

    OP_CMPL_FLOAT                   = 0x2d,
    OP_CMPG_FLOAT                   = 0x2e,
    OP_CMPL_DOUBLE                  = 0x2f,
    OP_CMPG_DOUBLE                  = 0x30,
    OP_CMP_LONG                     = 0x31,

    OP_IF_EQ                        = 0x32,
    OP_IF_NE                        = 0x33,
    OP_IF_LT                        = 0x34,
    OP_IF_GE                        = 0x35,
    OP_IF_GT                        = 0x36,
    OP_IF_LE                        = 0x37,
    OP_IF_EQZ                       = 0x38,
    OP_IF_NEZ                       = 0x39,
    OP_IF_LTZ                       = 0x3a,
    OP_IF_GEZ                       = 0x3b,
    OP_IF_GTZ                       = 0x3c,
    OP_IF_LEZ                       = 0x3d,

    OP_UNUSED_3E                    = 0x3e,
    OP_UNUSED_3F                    = 0x3f,
    OP_UNUSED_40                    = 0x40,
    OP_UNUSED_41                    = 0x41,
    OP_UNUSED_42                    = 0x42,
    OP_UNUSED_43                    = 0x43,

    OP_AGET                         = 0x44,
    OP_AGET_WIDE                    = 0x45,
    OP_AGET_OBJECT                  = 0x46,
    OP_AGET_BOOLEAN                 = 0x47,
    OP_AGET_BYTE                    = 0x48,
    OP_AGET_CHAR                    = 0x49,
    OP_AGET_SHORT                   = 0x4a,
    OP_APUT                         = 0x4b,
    OP_APUT_WIDE                    = 0x4c,
    OP_APUT_OBJECT                  = 0x4d,
    OP_APUT_BOOLEAN                 = 0x4e,
    OP_APUT_BYTE                    = 0x4f,
    OP_APUT_CHAR                    = 0x50,
    OP_APUT_SHORT                   = 0x51,

    OP_IGET                         = 0x52,
    OP_IGET_WIDE                    = 0x53,
    OP_IGET_OBJECT                  = 0x54,
    OP_IGET_BOOLEAN                 = 0x55,
    OP_IGET_BYTE                    = 0x56,
    OP_IGET_CHAR                    = 0x57,
    OP_IGET_SHORT                   = 0x58,
    OP_IPUT                         = 0x59,
    OP_IPUT_WIDE                    = 0x5a,
    OP_IPUT_OBJECT                  = 0x5b,
    OP_IPUT_BOOLEAN                 = 0x5c,
    OP_IPUT_BYTE                    = 0x5d,
    OP_IPUT_CHAR                    = 0x5e,
    OP_IPUT_SHORT                   = 0x5f,

    OP_SGET                         = 0x60,
    OP_SGET_WIDE                    = 0x61,
    OP_SGET_OBJECT                  = 0x62,
    OP_SGET_BOOLEAN                 = 0x63,
    OP_SGET_BYTE                    = 0x64,
    OP_SGET_CHAR                    = 0x65,
    OP_SGET_SHORT                   = 0x66,
    OP_SPUT                         = 0x67,
    OP_SPUT_WIDE                    = 0x68,
    OP_SPUT_OBJECT                  = 0x69,
    OP_SPUT_BOOLEAN                 = 0x6a,
    OP_SPUT_BYTE                    = 0x6b,
    OP_SPUT_CHAR                    = 0x6c,
    OP_SPUT_SHORT                   = 0x6d,

    OP_INVOKE_VIRTUAL               = 0x6e,
    OP_INVOKE_SUPER                 = 0x6f,
    OP_INVOKE_DIRECT                = 0x70,
    OP_INVOKE_STATIC                = 0x71,
    OP_INVOKE_INTERFACE             = 0x72,

    OP_UNUSED_73                    = 0x73,

    OP_INVOKE_VIRTUAL_RANGE         = 0x74,
    OP_INVOKE_SUPER_RANGE           = 0x75,
    OP_INVOKE_DIRECT_RANGE          = 0x76,
    OP_INVOKE_STATIC_RANGE          = 0x77,
    OP_INVOKE_INTERFACE_RANGE       = 0x78,

    OP_UNUSED_79                    = 0x79,
    OP_UNUSED_7A                    = 0x7a,

    OP_NEG_INT                      = 0x7b,
    OP_NOT_INT                      = 0x7c,
    OP_NEG_LONG                     = 0x7d,
    OP_NOT_LONG                     = 0x7e,
    OP_NEG_FLOAT                    = 0x7f,
    OP_NEG_DOUBLE                   = 0x80,
    OP_INT_TO_LONG                  = 0x81,
    OP_INT_TO_FLOAT                 = 0x82,
    OP_INT_TO_DOUBLE                = 0x83,
    OP_LONG_TO_INT                  = 0x84,
    OP_LONG_TO_FLOAT                = 0x85,
    OP_LONG_TO_DOUBLE               = 0x86,
    OP_FLOAT_TO_INT                 = 0x87,
    OP_FLOAT_TO_LONG                = 0x88,
    OP_FLOAT_TO_DOUBLE              = 0x89,
    OP_DOUBLE_TO_INT                = 0x8a,
    OP_DOUBLE_TO_LONG               = 0x8b,
    OP_DOUBLE_TO_FLOAT              = 0x8c,
    OP_INT_TO_BYTE                  = 0x8d,
    OP_INT_TO_CHAR                  = 0x8e,
    OP_INT_TO_SHORT                 = 0x8f,

    OP_ADD_INT                      = 0x90,
    OP_SUB_INT                      = 0x91,
    OP_MUL_INT                      = 0x92,
    OP_DIV_INT                      = 0x93,
    OP_REM_INT                      = 0x94,
    OP_AND_INT                      = 0x95,
    OP_OR_INT                       = 0x96,
    OP_XOR_INT                      = 0x97,
    OP_SHL_INT                      = 0x98,
    OP_SHR_INT                      = 0x99,
    OP_USHR_INT                     = 0x9a,

    OP_ADD_LONG                     = 0x9b,
    OP_SUB_LONG                     = 0x9c,
    OP_MUL_LONG                     = 0x9d,
    OP_DIV_LONG                     = 0x9e,
    OP_REM_LONG                     = 0x9f,
    OP_AND_LONG                     = 0xa0,
    OP_OR_LONG                      = 0xa1,
    OP_XOR_LONG                     = 0xa2,
    OP_SHL_LONG                     = 0xa3,
    OP_SHR_LONG                     = 0xa4,
    OP_USHR_LONG                    = 0xa5,

    OP_ADD_FLOAT                    = 0xa6,
    OP_SUB_FLOAT                    = 0xa7,
    OP_MUL_FLOAT                    = 0xa8,
    OP_DIV_FLOAT                    = 0xa9,
    OP_REM_FLOAT                    = 0xaa,
    OP_ADD_DOUBLE                   = 0xab,
    OP_SUB_DOUBLE                   = 0xac,
    OP_MUL_DOUBLE                   = 0xad,
    OP_DIV_DOUBLE                   = 0xae,
    OP_REM_DOUBLE                   = 0xaf,

    OP_ADD_INT_2ADDR                = 0xb0,
    OP_SUB_INT_2ADDR                = 0xb1,
    OP_MUL_INT_2ADDR                = 0xb2,
    OP_DIV_INT_2ADDR                = 0xb3,
    OP_REM_INT_2ADDR                = 0xb4,
    OP_AND_INT_2ADDR                = 0xb5,
    OP_OR_INT_2ADDR                 = 0xb6,
    OP_XOR_INT_2ADDR                = 0xb7,
    OP_SHL_INT_2ADDR                = 0xb8,
    OP_SHR_INT_2ADDR                = 0xb9,
    OP_USHR_INT_2ADDR               = 0xba,

    OP_ADD_LONG_2ADDR               = 0xbb,
    OP_SUB_LONG_2ADDR               = 0xbc,
    OP_MUL_LONG_2ADDR               = 0xbd,
    OP_DIV_LONG_2ADDR               = 0xbe,
    OP_REM_LONG_2ADDR               = 0xbf,
    OP_AND_LONG_2ADDR               = 0xc0,
    OP_OR_LONG_2ADDR                = 0xc1,
    OP_XOR_LONG_2ADDR               = 0xc2,
    OP_SHL_LONG_2ADDR               = 0xc3,
    OP_SHR_LONG_2ADDR               = 0xc4,
    OP_USHR_LONG_2ADDR              = 0xc5,

    OP_ADD_FLOAT_2ADDR              = 0xc6,
    OP_SUB_FLOAT_2ADDR              = 0xc7,
    OP_MUL_FLOAT_2ADDR              = 0xc8,
    OP_DIV_FLOAT_2ADDR              = 0xc9,
    OP_REM_FLOAT_2ADDR              = 0xca,
    OP_ADD_DOUBLE_2ADDR             = 0xcb,
    OP_SUB_DOUBLE_2ADDR             = 0xcc,
    OP_MUL_DOUBLE_2ADDR             = 0xcd,
    OP_DIV_DOUBLE_2ADDR             = 0xce,
    OP_REM_DOUBLE_2ADDR             = 0xcf,

    OP_ADD_INT_LIT16                = 0xd0,
    OP_RSUB_INT                     = 0xd1, /* no _LIT16 suffix for this */
    OP_MUL_INT_LIT16                = 0xd2,
    OP_DIV_INT_LIT16                = 0xd3,
    OP_REM_INT_LIT16                = 0xd4,
    OP_AND_INT_LIT16                = 0xd5,
    OP_OR_INT_LIT16                 = 0xd6,
    OP_XOR_INT_LIT16                = 0xd7,

    OP_ADD_INT_LIT8                 = 0xd8,
    OP_RSUB_INT_LIT8                = 0xd9,
    OP_MUL_INT_LIT8                 = 0xda,
    OP_DIV_INT_LIT8                 = 0xdb,
    OP_REM_INT_LIT8                 = 0xdc,
    OP_AND_INT_LIT8                 = 0xdd,
    OP_OR_INT_LIT8                  = 0xde,
    OP_XOR_INT_LIT8                 = 0xdf,
    OP_SHL_INT_LIT8                 = 0xe0,
    OP_SHR_INT_LIT8                 = 0xe1,
    OP_USHR_INT_LIT8                = 0xe2,

    OP_UNUSED_E3                    = 0xe3,
    OP_UNUSED_E4                    = 0xe4,
    OP_UNUSED_E5                    = 0xe5,
    OP_UNUSED_E6                    = 0xe6,
    OP_UNUSED_E7                    = 0xe7,
    OP_UNUSED_E8                    = 0xe8,
    OP_UNUSED_E9                    = 0xe9,
    OP_UNUSED_EA                    = 0xea,
    OP_UNUSED_EB                    = 0xeb,
    OP_UNUSED_EC                    = 0xec,

    /* optimizer output -- these are never generated by "dx" */
    OP_THROW_VERIFICATION_ERROR     = 0xed,
    OP_EXECUTE_INLINE               = 0xee,
    OP_UNUSED_EF                    = 0xef, /* OP_EXECUTE_INLINE_RANGE? */

    OP_INVOKE_DIRECT_EMPTY          = 0xf0,
    OP_UNUSED_F1                    = 0xf1, /* OP_INVOKE_DIRECT_EMPTY_RANGE? */
    OP_IGET_QUICK                   = 0xf2,
    OP_IGET_WIDE_QUICK              = 0xf3,
    OP_IGET_OBJECT_QUICK            = 0xf4,
    OP_IPUT_QUICK                   = 0xf5,
    OP_IPUT_WIDE_QUICK              = 0xf6,
    OP_IPUT_OBJECT_QUICK            = 0xf7,

    OP_INVOKE_VIRTUAL_QUICK         = 0xf8,
    OP_INVOKE_VIRTUAL_QUICK_RANGE   = 0xf9,
    OP_INVOKE_SUPER_QUICK           = 0xfa,
    OP_INVOKE_SUPER_QUICK_RANGE     = 0xfb,
    OP_UNUSED_FC                    = 0xfc, /* OP_INVOKE_DIRECT_QUICK? */
    OP_UNUSED_FD                    = 0xfd, /* OP_INVOKE_DIRECT_QUICK_RANGE? */
    OP_UNUSED_FE                    = 0xfe, /* OP_INVOKE_INTERFACE_QUICK? */
    OP_UNUSED_FF                    = 0xff /* OP_INVOKE_INTERFACE_QUICK_RANGE*/
} OpCode;

#define kNumDalvikInstructions 256

/*
 * Instruction width, a value in the range -3 to 5.
 */
typedef signed char InstructionWidth;

/*
 * Generate a table that holds the width of all instructions.
 *
 * Standard instructions have positive values, optimizer instructions
 * have negative values, unimplemented instructions have a width of zero.
 *
 * I'm doing it with a giant switch statement because it's easier to
 * maintain and update than a static table with 256 unadorned integers,
 * and if we're missing a case gcc emits a "warning: enumeration value not
 * handled" message.
 *
 * (To save space in the binary we could generate a static table with a
 * command-line utility.)
 */
InstructionWidth* dexCreateInstrWidthTable(void)
{
	//TODO consider protecting it with mutex
    static InstructionWidth instrWidth[kNumDalvikInstructions];
    static bool instrWidthTableIsInitalized = false;;
    int i;

    /* Eugene: Android implementation allocates it on heap. I see absolutely no reason to do that,
     * while it can be allocated in the static memory
     * TODO Consider initializing this table with instruction width right away,
     * like it is done in the latest Android version
     *
    instrWidth = malloc(sizeof(InstructionWidth) * kNumDalvikInstructions);
    if (instrWidth == NULL)
        return NULL;
        */
    if(instrWidthTableIsInitalized)
    	return instrWidth;

    memset(instrWidth,0,sizeof(InstructionWidth)*kNumDalvikInstructions);
    for (i = 0; i < kNumDalvikInstructions; i++) {
        OpCode opc = (OpCode) i;
        int width = 0;

        switch (opc) {
        case OP_NOP:    /* note data for e.g. switch-* encoded "inside" a NOP */
        case OP_MOVE:
        case OP_MOVE_WIDE:
        case OP_MOVE_OBJECT:
        case OP_MOVE_RESULT:
        case OP_MOVE_RESULT_WIDE:
        case OP_MOVE_RESULT_OBJECT:
        case OP_MOVE_EXCEPTION:
        case OP_RETURN_VOID:
        case OP_RETURN:
        case OP_RETURN_WIDE:
        case OP_RETURN_OBJECT:
        case OP_CONST_4:
        case OP_MONITOR_ENTER:
        case OP_MONITOR_EXIT:
        case OP_ARRAY_LENGTH:
        case OP_THROW:
        case OP_GOTO:
        case OP_NEG_INT:
        case OP_NOT_INT:
        case OP_NEG_LONG:
        case OP_NOT_LONG:
        case OP_NEG_FLOAT:
        case OP_NEG_DOUBLE:
        case OP_INT_TO_LONG:
        case OP_INT_TO_FLOAT:
        case OP_INT_TO_DOUBLE:
        case OP_LONG_TO_INT:
        case OP_LONG_TO_FLOAT:
        case OP_LONG_TO_DOUBLE:
        case OP_FLOAT_TO_INT:
        case OP_FLOAT_TO_LONG:
        case OP_FLOAT_TO_DOUBLE:
        case OP_DOUBLE_TO_INT:
        case OP_DOUBLE_TO_LONG:
        case OP_DOUBLE_TO_FLOAT:
        case OP_INT_TO_BYTE:
        case OP_INT_TO_CHAR:
        case OP_INT_TO_SHORT:
        case OP_ADD_INT_2ADDR:
        case OP_SUB_INT_2ADDR:
        case OP_MUL_INT_2ADDR:
        case OP_DIV_INT_2ADDR:
        case OP_REM_INT_2ADDR:
        case OP_AND_INT_2ADDR:
        case OP_OR_INT_2ADDR:
        case OP_XOR_INT_2ADDR:
        case OP_SHL_INT_2ADDR:
        case OP_SHR_INT_2ADDR:
        case OP_USHR_INT_2ADDR:
        case OP_ADD_LONG_2ADDR:
        case OP_SUB_LONG_2ADDR:
        case OP_MUL_LONG_2ADDR:
        case OP_DIV_LONG_2ADDR:
        case OP_REM_LONG_2ADDR:
        case OP_AND_LONG_2ADDR:
        case OP_OR_LONG_2ADDR:
        case OP_XOR_LONG_2ADDR:
        case OP_SHL_LONG_2ADDR:
        case OP_SHR_LONG_2ADDR:
        case OP_USHR_LONG_2ADDR:
        case OP_ADD_FLOAT_2ADDR:
        case OP_SUB_FLOAT_2ADDR:
        case OP_MUL_FLOAT_2ADDR:
        case OP_DIV_FLOAT_2ADDR:
        case OP_REM_FLOAT_2ADDR:
        case OP_ADD_DOUBLE_2ADDR:
        case OP_SUB_DOUBLE_2ADDR:
        case OP_MUL_DOUBLE_2ADDR:
        case OP_DIV_DOUBLE_2ADDR:
        case OP_REM_DOUBLE_2ADDR:
            width = 1;
            break;

        case OP_MOVE_FROM16:
        case OP_MOVE_WIDE_FROM16:
        case OP_MOVE_OBJECT_FROM16:
        case OP_CONST_16:
        case OP_CONST_HIGH16:
        case OP_CONST_WIDE_16:
        case OP_CONST_WIDE_HIGH16:
        case OP_CONST_STRING:
        case OP_CONST_CLASS:
        case OP_CHECK_CAST:
        case OP_INSTANCE_OF:
        case OP_NEW_INSTANCE:
        case OP_NEW_ARRAY:
        case OP_CMPL_FLOAT:
        case OP_CMPG_FLOAT:
        case OP_CMPL_DOUBLE:
        case OP_CMPG_DOUBLE:
        case OP_CMP_LONG:
        case OP_GOTO_16:
        case OP_IF_EQ:
        case OP_IF_NE:
        case OP_IF_LT:
        case OP_IF_GE:
        case OP_IF_GT:
        case OP_IF_LE:
        case OP_IF_EQZ:
        case OP_IF_NEZ:
        case OP_IF_LTZ:
        case OP_IF_GEZ:
        case OP_IF_GTZ:
        case OP_IF_LEZ:
        case OP_AGET:
        case OP_AGET_WIDE:
        case OP_AGET_OBJECT:
        case OP_AGET_BOOLEAN:
        case OP_AGET_BYTE:
        case OP_AGET_CHAR:
        case OP_AGET_SHORT:
        case OP_APUT:
        case OP_APUT_WIDE:
        case OP_APUT_OBJECT:
        case OP_APUT_BOOLEAN:
        case OP_APUT_BYTE:
        case OP_APUT_CHAR:
        case OP_APUT_SHORT:
        case OP_IGET:
        case OP_IGET_WIDE:
        case OP_IGET_OBJECT:
        case OP_IGET_BOOLEAN:
        case OP_IGET_BYTE:
        case OP_IGET_CHAR:
        case OP_IGET_SHORT:
        case OP_IPUT:
        case OP_IPUT_WIDE:
        case OP_IPUT_OBJECT:
        case OP_IPUT_BOOLEAN:
        case OP_IPUT_BYTE:
        case OP_IPUT_CHAR:
        case OP_IPUT_SHORT:
        case OP_SGET:
        case OP_SGET_WIDE:
        case OP_SGET_OBJECT:
        case OP_SGET_BOOLEAN:
        case OP_SGET_BYTE:
        case OP_SGET_CHAR:
        case OP_SGET_SHORT:
        case OP_SPUT:
        case OP_SPUT_WIDE:
        case OP_SPUT_OBJECT:
        case OP_SPUT_BOOLEAN:
        case OP_SPUT_BYTE:
        case OP_SPUT_CHAR:
        case OP_SPUT_SHORT:
        case OP_ADD_INT:
        case OP_SUB_INT:
        case OP_MUL_INT:
        case OP_DIV_INT:
        case OP_REM_INT:
        case OP_AND_INT:
        case OP_OR_INT:
        case OP_XOR_INT:
        case OP_SHL_INT:
        case OP_SHR_INT:
        case OP_USHR_INT:
        case OP_ADD_LONG:
        case OP_SUB_LONG:
        case OP_MUL_LONG:
        case OP_DIV_LONG:
        case OP_REM_LONG:
        case OP_AND_LONG:
        case OP_OR_LONG:
        case OP_XOR_LONG:
        case OP_SHL_LONG:
        case OP_SHR_LONG:
        case OP_USHR_LONG:
        case OP_ADD_FLOAT:
        case OP_SUB_FLOAT:
        case OP_MUL_FLOAT:
        case OP_DIV_FLOAT:
        case OP_REM_FLOAT:
        case OP_ADD_DOUBLE:
        case OP_SUB_DOUBLE:
        case OP_MUL_DOUBLE:
        case OP_DIV_DOUBLE:
        case OP_REM_DOUBLE:
        case OP_ADD_INT_LIT16:
        case OP_RSUB_INT:
        case OP_MUL_INT_LIT16:
        case OP_DIV_INT_LIT16:
        case OP_REM_INT_LIT16:
        case OP_AND_INT_LIT16:
        case OP_OR_INT_LIT16:
        case OP_XOR_INT_LIT16:
        case OP_ADD_INT_LIT8:
        case OP_RSUB_INT_LIT8:
        case OP_MUL_INT_LIT8:
        case OP_DIV_INT_LIT8:
        case OP_REM_INT_LIT8:
        case OP_AND_INT_LIT8:
        case OP_OR_INT_LIT8:
        case OP_XOR_INT_LIT8:
        case OP_SHL_INT_LIT8:
        case OP_SHR_INT_LIT8:
        case OP_USHR_INT_LIT8:
            width = 2;
            break;

        case OP_MOVE_16:
        case OP_MOVE_WIDE_16:
        case OP_MOVE_OBJECT_16:
        case OP_CONST:
        case OP_CONST_WIDE_32:
        case OP_CONST_STRING_JUMBO:
        case OP_GOTO_32:
        case OP_FILLED_NEW_ARRAY:
        case OP_FILLED_NEW_ARRAY_RANGE:
        case OP_FILL_ARRAY_DATA:
        case OP_PACKED_SWITCH:
        case OP_SPARSE_SWITCH:
        case OP_INVOKE_VIRTUAL:
        case OP_INVOKE_SUPER:
        case OP_INVOKE_DIRECT:
        case OP_INVOKE_STATIC:
        case OP_INVOKE_INTERFACE:
        case OP_INVOKE_VIRTUAL_RANGE:
        case OP_INVOKE_SUPER_RANGE:
        case OP_INVOKE_DIRECT_RANGE:
        case OP_INVOKE_STATIC_RANGE:
        case OP_INVOKE_INTERFACE_RANGE:
            width = 3;
            break;

        case OP_CONST_WIDE:
            width = 5;
            break;

        /*
         * Optimized instructions.  We return negative size values for these
         * to distinguish them.
         */
        case OP_IGET_QUICK:
        case OP_IGET_WIDE_QUICK:
        case OP_IGET_OBJECT_QUICK:
        case OP_IPUT_QUICK:
        case OP_IPUT_WIDE_QUICK:
        case OP_IPUT_OBJECT_QUICK:
        case OP_THROW_VERIFICATION_ERROR:
            width = -2;
            break;
        case OP_INVOKE_VIRTUAL_QUICK:
        case OP_INVOKE_VIRTUAL_QUICK_RANGE:
        case OP_INVOKE_SUPER_QUICK:
        case OP_INVOKE_SUPER_QUICK_RANGE:
        case OP_EXECUTE_INLINE:
        case OP_INVOKE_DIRECT_EMPTY:
            width = -3;
            break;

        /* these should never appear */
        case OP_UNUSED_3E:
        case OP_UNUSED_3F:
        case OP_UNUSED_40:
        case OP_UNUSED_41:
        case OP_UNUSED_42:
        case OP_UNUSED_43:
        case OP_UNUSED_73:
        case OP_UNUSED_79:
        case OP_UNUSED_7A:
        case OP_UNUSED_E3:
        case OP_UNUSED_E4:
        case OP_UNUSED_E5:
        case OP_UNUSED_E6:
        case OP_UNUSED_E7:
        case OP_UNUSED_E8:
        case OP_UNUSED_E9:
        case OP_UNUSED_EA:
        case OP_UNUSED_EB:
        case OP_UNUSED_EC:
        case OP_UNUSED_EF:
        case OP_UNUSED_F1:
        case OP_UNUSED_FC:
        case OP_UNUSED_FD:
        case OP_UNUSED_FE:
        case OP_UNUSED_FF:
            assert(width == 0);
            break;

        /*
         * DO NOT add a "default" clause here.  Without it the compiler will
         * complain if an instruction is missing (which is desirable).
         */
        }

        instrWidth[opc] = width;
    }
    instrWidthTableIsInitalized = true;

    return instrWidth;
}

/*
 * Return the width of the specified instruction, or 0 if not defined.  Also
 * works for special OP_NOP entries, including switch statement data tables
 * and array data.
 */
int dexGetInstrOrTableWidthAbs(const InstructionWidth* widths, const u2* insns)
{
    int width;

    if (*insns == kPackedSwitchSignature) {
        width = 4 + insns[1] * 2;
    } else if (*insns == kSparseSwitchSignature) {
        width = 2 + insns[1] * 4;
    } else if (*insns == kArrayDataSignature) {
        u2 elemWidth = insns[1];
        u4 len = insns[2] | (((u4)insns[3]) << 16);
        width = 4 + (elemWidth * len + 1) / 2;
    } else {
        width = widths[*(char*)insns];
        if(width < 0)
        	width = -width;
    }
    return width;
}
// The end of the code copied from Android source


int walkByteCode(JNIEnv* env,DexByteCodeRecord* dexByteCodeRecord, const char* bytecode, unsigned int length)
{
	unsigned int offset = 0;
	unsigned int instrsCount = 0;
	const char* p = bytecode;
	unsigned int width;
	InstructionWidth* widths = dexCreateInstrWidthTable();
	while(p - bytecode < length)
	{
		//LOGI("Instruction: 0x%x, size: %d", *p, widths[*p]);
		width = dexGetInstrOrTableWidthAbs(widths,(const u2*)p);
		if(!width)
		{
			DBGWRAP(LOGE("Encountered zero length instruction in %s.%s,opcode 0x%x, MUST NOT HAPPEN!!!! ", dexByteCodeRecord->class_name, dexByteCodeRecord->method_name, *p));
			break;
		}
		p+= width<<1 ;// The size is in 16bit words
		instrsCount++;
	}
	if(p - bytecode != length)
		DBGWRAP(LOGE("Failed bytewalking in %s.%s, the method length %d, counted %d ", dexByteCodeRecord->class_name, dexByteCodeRecord->method_name, length, p-bytecode));
	return instrsCount;
}


typedef struct _Field {
    //ClassObject*    clazz;          /* class in which the field is declared */
    void*           clazz;          /* class in which the field is declared */
    const char*     name;
    const char*     signature;      /* e.g. "I", "[C", "Landroid/os/Debug;" */
    u4              accessFlags;
#ifdef PROFILE_FIELD_ACCESS
    u4              gets;
    u4              puts;
#endif
}Field;

/*
 * Instance field.
 */
typedef struct _InstField {
    Field           field;          /* MUST be first item */

    /*
     * This field indicates the byte offset from the beginning of the
     * (Object *) to the actual instance data; e.g., byteOffset==0 is
     * the same as the object pointer (bug!), and byteOffset==4 is 4
     * bytes farther.
     */
    int             byteOffset;
} InstField;


/*!
 * The structure defines the device providing acces to
 * exported functions of Dalvik VM
 * (Use cautiously!!!, the functions as well as
 * the shared library can be renamed/deleted in a new release of Android
 *
 */
typedef struct _DalvikVMDevice
{
	void* module;
	/*!
	 * Field resolution function
	 * Resolves field id into field offset
	 */
	void* (*dvmOptResolveInstField)(void* , u4 ,void* );
	/*!
	 * Class pointer by classname resolution function
	 */
	void*(*dvmFindLoadedClassSymbol)(const char*);
}DalvikVMDevice;

/*!
 * The struct used to pass parameters required for optimization
 */
typedef struct _OptParams
{
	/*!
	 * The index method data
	 */
	DexByteCodeRecord* dexByteCodeRecord;
	/*!
	 * Pointer to class object
	 */
	void* classObj;
	/*!
	 * Pointer to the instruction being optimized bytecode
	 */
	u2* insns;
}OptParams;


typedef struct _OptConfig
{
	// A flag per instruction.
	// If on the instruction is to be optimized
	char optFlags[kNumDalvikInstructions];
	// The optimization handler for given optimization config
	void (*optHandler)(JNIEnv* ,DalvikVMDevice* , struct _OptConfig* , OptParams* );
}OptConfig;


// The optimizing function does not return anything to save time
// It logs an error and leave an instruction unoptimized if it cant' optimize it
static inline void optimizeIGetObject(JNIEnv* env, DalvikVMDevice* dvmDevice,
		OptParams* params)
{
	u2 fieldIdx = params->insns[1];
	InstField* field = (InstField*) (*dvmDevice->dvmOptResolveInstField)(
			params->classObj, fieldIdx, NULL);
	DBGWRAP(LOGI("Found IGET_OBJECT in %s.%s, field id: 0x%x, field offset: 0x%x ",
			params->dexByteCodeRecord->class_name,
			params->dexByteCodeRecord->method_name, fieldIdx, field->byteOffset));
	if (field->byteOffset < 65536)
	{
		params->insns[0] = (params->insns[0] & 0xff00)
				| (u2) OP_IGET_OBJECT_QUICK;
		params->insns[1] = (u2) field->byteOffset;
	}
	else
	{
		LOGE("Not optimizing...Field offset exceeds 64K (%d)\n",
				field->byteOffset);
	}

}

// The function that does i-get-object optimization only
static inline void optIgetObjectOnly(JNIEnv* env,DalvikVMDevice* dvmDevice, OptConfig* config, OptParams* params)
{
	// we don't check config flags here.
	// if this function is called it means that the
	// config was checked before and OP_IGET_OBJECT will always be optimized
	if(OP_IGET_OBJECT == ((*params->insns) & 0xff) )
	{
		optimizeIGetObject(env, dvmDevice, params);
	}
}

// The function reserved to do generic optimization
// Currently not doing anything
static inline void optGeneric(JNIEnv* env,DalvikVMDevice* dvmDevice, OptConfig* config, OptParams* params)
{
	if(config->optFlags[(*params->insns) & 0xff])
	{
		// Her we'll call a generic optimization function
		DBGWRAP(LOGE("Generic optimization is not implemented yet!!!!"));
	}
}

// Initializes optimization handler
// Currently it is set to create a handler for i-get-object optimization only
static inline void initOptHandler(OptConfig* optConfig)
{
	static char zeroOptFlags[kNumDalvikInstructions];
	// only to ensure static array initialization
	static void* p = memset(zeroOptFlags, 0, kNumDalvikInstructions);

	optConfig->optHandler = optGeneric;
	if(optConfig->optFlags[OP_IGET_OBJECT] )
	{
		optConfig->optFlags[OP_IGET_OBJECT] = 0;
		if(!memcmp(optConfig->optFlags, zeroOptFlags, kNumDalvikInstructions))
		{
			optConfig->optHandler = optIgetObjectOnly;
		}
		optConfig->optFlags[OP_IGET_OBJECT] = 1;
	}
}

static void destroyOptConfig(void* p)
{
	if(p)
		ac_free(p);
}

// OptConfig creator
static void* getIGetObjectOptConfig()
{
	OptConfig* optConfig = (OptConfig*)ac_calloc(1, sizeof(OptConfig));
	optConfig->optFlags[OP_IGET_OBJECT] = 1;
	initOptHandler(optConfig);
	return optConfig;
}

static void destroyDalvikVMDevice(void* p)
{
	if(p)
		ac_free(p);
}

// retuns a pointer to internal loaded class object
// uses a function left exported in Dalvik VM
static void* getClassObject(void* dvm, const char* className)
{
	DalvikVMDevice* dalvikVMDevice = (DalvikVMDevice*)dvm;
	return (*dalvikVMDevice->dvmFindLoadedClassSymbol)(className);
}

// Dalvik VM device initializer
// It loads dalvik vm shared lib and gets
// pointers to exported functions of interest
static void* initDalvikVMDevice(JNIEnv* env)
{
	const char *error;
	DalvikVMDevice* dalvikVMDevice = (DalvikVMDevice*)ac_calloc(1, sizeof(DalvikVMDevice));
	// Typically library is at /system/lib/,
	// However we count on it being in the library path in case it is placed elsewhere
	dalvikVMDevice->module = dlopen("libdvm.so", RTLD_LAZY);
	if (!dalvikVMDevice->module)
	{
		LOGE("Couldn't load libdvm.so: %s", dlerror());
		ac_free(dalvikVMDevice);
		return dalvikVMDevice = NULL;
	}

	dlerror();
	dalvikVMDevice->dvmFindLoadedClassSymbol = (void*(*)(const char*)) dlsym(dalvikVMDevice->module,"dvmFindLoadedClass");
	if (error = dlerror())
	{
		LOGE("Couldn't find dvmFindLoadedClass: %s", error);
		ac_free(dalvikVMDevice);
		return dalvikVMDevice = NULL;
	}

	dlerror();
	dalvikVMDevice->dvmOptResolveInstField = (void* (*)(void*, u4, void*)) dlsym(dalvikVMDevice->module,"dvmOptResolveInstField");
	if (error = dlerror())
	{
		LOGE("Couldn't find dvmOptResolveInstField: %s", error);
		ac_free(dalvikVMDevice);
		return dalvikVMDevice = NULL;
	}

	return dalvikVMDevice;
}

// Teh bytecode optimizer function
static int optimizeBytecode(JNIEnv* env,DexByteCodeRecord* dexByteCodeRecord, const char* bytecode, unsigned int length,
		void* classObj, void* pDvmDevice, void* pOptConfig)
{
	unsigned int offset = 0;
	unsigned int instrsCount = 0;
	const char* p = bytecode;
	unsigned int width;
	InstructionWidth* widths = dexCreateInstrWidthTable();
	OptParams params;
	DalvikVMDevice* dvmDevice = (DalvikVMDevice*)pDvmDevice;
	OptConfig* optConfig = (OptConfig*)pOptConfig;
	params.classObj = classObj;
	params.dexByteCodeRecord = dexByteCodeRecord;
	while(p - bytecode < length)
	{
		width = dexGetInstrOrTableWidthAbs(widths,(const u2*)p);
		if(!width)
		{
			DBGWRAP(LOGE("Encountered zero length instruction in %s.%s,opcode 0x%x, MUST NOT HAPPEN!!!! ", dexByteCodeRecord->class_name, dexByteCodeRecord->method_name, *p));
			break;
		}
		params.insns = (u2*)p;
		optConfig->optHandler(env, dvmDevice, optConfig, &params);

		p+= width<<1 ;// The size is in 16bit words
		instrsCount++;
	}
	if(p - bytecode != length)
		DBGWRAP(LOGE("Failed bytewalking in %s.%s, the method length %d, counted %d ", dexByteCodeRecord->class_name, dexByteCodeRecord->method_name, length, p-bytecode));
	return instrsCount;
}

void initDexOptimizerDevice(JNIEnv* env,DexOptimizerDevice* dexOptimizerDevice)
{
	if(!dexOptimizerDevice)
	{
		DBGWRAP(LOGE("Failed initialize Dex Optimizer. Invalid parameter"));
		return;
	}
	dexOptimizerDevice->initDalvikVMDevice     = initDalvikVMDevice;
	dexOptimizerDevice->destroyDalvikVMDevice  = destroyDalvikVMDevice;
	dexOptimizerDevice->getClassObject         = getClassObject;
	dexOptimizerDevice->getIGetObjectOptConfig = getIGetObjectOptConfig;
	dexOptimizerDevice->destroyOptConfig       = destroyOptConfig;
	dexOptimizerDevice->optimizeBytecode       = optimizeBytecode;
}

