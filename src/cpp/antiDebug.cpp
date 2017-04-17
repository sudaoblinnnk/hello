#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "iso98wrap.h"
#include "irdetoJavaSecurity.h"
#include "JACCommonModule.h"
#include "irdetoJavaSecurityExtension.h"
#include "antiDebug.h"

static char JACModule5[] ="antiDebug.cpp";

int initADbg(JNIEnv *env, AntiDebugData *input, int collectDelta, int verifyDelta)
{
    initADbgNoJNI(input, collectDelta, verifyDelta);
}

int init2ADbg(JNIEnv *env, AntiDebugData *input, int delta)
{
    initADbg(env,input,delta,delta);
}

int init2ADbgNoJNI(AntiDebugData *input, int delta)
{
    initADbgNoJNI(input,delta,delta);
}

int initADbgNoJNI(AntiDebugData *input, int collectDelta, int verifyDelta)
{
    memset(input, 0, sizeof(AntiDebugData));
    input->pg_ad[0].CID = TBAD_CID_INDEX;
    input->pg_ad[0].VID = TBAD_VID;
    input->pg_ad[0].ts = 0;
    input->pg_ad[0].c_delta = 0;
    input->pg_ad[0].c_delta_max = collectDelta;
    input->pg_ad[0].v_delta_max = verifyDelta;
    XC_ADBTS_INIT_TS(input->pg_ad, TBAD_CID_INDEX);
    XC_ADBTS_COLLECT(input->pg_ad, TBAD_CID_INDEX);

}

int markADbg(JNIEnv *env, AntiDebugData *input)
{
    XC_ADBTS_COLLECT(input->pg_ad, TBAD_CID_INDEX);
}

int verifyADbg(JNIEnv *env, AntiDebugData *input)
{
    unsigned int tval1 = 1;
    unsigned int *tval2;
    int retCode = 0;

    tval2 = (unsigned int *) ac_malloc(sizeof(unsigned int));
    if (tval2 == NULL) {
        return retCode;
    }
    *tval2 = tval1;
    TBAD_VERIFY_BODY(input->pg_ad, tval2);
    if(*tval2 == tval1){
        retCode = 1;
    }else
        printf("Debug activity detected\n\n");
    ac_free(tval2);
    return retCode;
}

int markAndVerifyADbg(JNIEnv *env, AntiDebugData *input, char *caller, int line)
{
    unsigned int tval1 = 1;
    unsigned int *tval2;
    int retCode = 0;
    char message[MESSAGE_LINE_LEN+1];
    char func[] ="markAndVerifyADbg";

    XC_ADBTS_COLLECT(input->pg_ad, TBAD_CID_INDEX);
    tval2 = (unsigned int *) ac_malloc(sizeof(unsigned int));
    if (tval2 == NULL) {
        return retCode;
    }
    *tval2 = tval1;
    TBAD_VERIFY_BODY(input->pg_ad, tval2);
    if(*tval2 == tval1){
        retCode = 1;
    }else{
	snprintf(message, MESSAGE_LINE_LEN, "%s()__line__%d",caller, line);
	JACDebug(env, JACModule5, func, "Debugger detected in function: %s, exiting...\n", message);
	exit(EXIT_CODE_TBAD);
    }
    ac_free(tval2);
    return retCode;
}

int markAndVerifyADbgNoJNI(AntiDebugData *input)
{
    unsigned int tval1 = 1;
    unsigned int *tval2;
    int retCode = 0;

    XC_ADBTS_COLLECT(input->pg_ad, TBAD_CID_INDEX);
    tval2 = (unsigned int *) ac_malloc(sizeof(unsigned int));
    if (tval2 == NULL) {
        return retCode;
    }
    *tval2 = tval1;
    TBAD_VERIFY_BODY(input->pg_ad, tval2);
    if(*tval2 == tval1){
        retCode = 1;
    }else{
        exit(EXIT_CODE_TBAD);
    }
    ac_free(tval2);
    return retCode;
}
