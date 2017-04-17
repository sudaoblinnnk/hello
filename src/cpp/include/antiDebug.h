#ifndef _H_AANTIDEBUG_
#define _H_AANTIDEBUG_

#ifndef XC_ADBTS_ENABLED
#define XC_ADBTS_ENABLED 1
#endif

#include "xc/xc_adb.h"

#define TBAD_CID_INDEX 		0
#define TBAD_VID 		1
#define TBAD_STANDARD_TIMESPAN 	2000
#define DELTA_DISABLED 		0x00ffffff

#define C_DELTA_20MS 		20
#define C_DELTA_100MS 		100
#define C_DELTA_1 		1000
#define C_DELTA_2 		2000
#define C_DELTA_3 		3000
#define C_DELTA_4 		4000
#define C_DELTA_5 		5000
#define C_DELTA_10 		10000
#define C_DELTA_15              15000
#define C_DELTA_20 		20000
#define C_DELTA_30 		30000
#define C_DELTA_40 		40000
#define C_DELTA_60 		60000
#define C_DELTA_90 		90000
#define C_DELTA_120 		120000
#define C_DELTA_180 		180000
#define V_DELTA_10 		C_DELTA_10
#define V_DELTA_15              C_DELTA_15
#define V_DELTA_20 		C_DELTA_20
#define V_DELTA_30 		C_DELTA_30
#define V_DELTA_40 		C_DELTA_40
#define V_DELTA_60 		C_DELTA_60
#define V_DELTA_90 		C_DELTA_90
#define V_DELTA_120 		C_DELTA_120
#define V_DELTA_180 		C_DELTA_180
#define V_DELTA_1 		C_DELTA_1
#define V_DELTA_2 		C_DELTA_2
#define V_DELTA_3 		C_DELTA_3
#define V_DELTA_4 		C_DELTA_4
#define V_DELTA_5 		C_DELTA_5
#define V_DELTA_20MS 		C_DELTA_20MS
#define V_DELTA_100MS 		C_DELTA_100MS

typedef struct
{
    XC_ADBTS_DataPointStruct pg_ad[1];
    int number;

}AntiDebugData;

#ifdef __cplusplus
extern "C" {
#endif

static size_t Callback_TBAD(size_t data) {
    return data;
}

#ifdef __cplusplus
}
#endif

#define TBAD_START_BODY(pg_ad, c_delta_val, v_delta_val) { \
       pg_ad[0].CID = TBAD_CID_INDEX; \
       pg_ad[0].VID = TBAD_VID; \
       pg_ad[0].ts = 0; \
       pg_ad[0].c_delta = 0; \
       pg_ad[0].c_delta_max = c_delta_val; /*change this value to adjust time */ \
       pg_ad[0].v_delta_max = v_delta_val; \
       XC_ADBTS_INIT_TS(pg_ad, TBAD_CID_INDEX); \
       XC_ADBTS_COLLECT(pg_ad, TBAD_CID_INDEX); \
}

#define TBAD_STOP_BODY(pg_ad) { \
           XC_ADBTS_COLLECT(pg_ad, TBAD_CID_INDEX);\
}

#define TBAD_STOP_VERIFY_BODY(pg_ad, target) { \
       unsigned int *val = (unsigned int * ) (target); \
       unsigned int startval = *val; \
       XC_ADBTS_COLLECT(pg_ad, TBAD_CID_INDEX); \
       *val = XC_ADBTS_VERIFY(pg_ad, *val, Callback_TBAD, TBAD_VID); \
}

#define TBAD_VERIFY_BODY(pg_ad, target) { \
       unsigned int *val = (unsigned int * ) target; \
       unsigned int startval = *val; \
       *val = XC_ADBTS_VERIFY(pg_ad, *val, Callback_TBAD, TBAD_VID); \
}

#ifdef __cplusplus
extern "C" {
#endif

int initADbg(JNIEnv *env, AntiDebugData *input, int collectDelta, int verifyDelta);
int init2ADbg(JNIEnv *env, AntiDebugData *input, int delta);
int initADbgNoJNI(AntiDebugData *input, int collectDelta, int verifyDelta);
int init2ADbgNoJNI(AntiDebugData *input, int delta);
int markADbg(JNIEnv *env, AntiDebugData *input);
int verifyADbg(JNIEnv *env, AntiDebugData *input);
int markAndVerifyADbg(JNIEnv *env, AntiDebugData *input, char *function, int line);
int markAndVerifyADbgNoJNI(AntiDebugData *input);


#ifdef __cplusplus
}
#endif


#endif
