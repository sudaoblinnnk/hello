#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "iso98wrap.h"
#include "ac_Stdlib_Internal.h"
#include "dexAdaptor.h"
#include "JACCommonModule.h"



static char JACModule4[] ="dexOperator.cpp";

ACCESS_STATUS getCookies(JNIEnv* env, int **cookies, int length)
{
    int dexArrayLength, i;
    char func[]="getCookies";

    jclass classDVMLoader = NULL;
    jclass classDexFile = NULL;
    jclass classClass = NULL;
    jclass classField = NULL;
    jmethodID mid = NULL;
    jobject myDexFileObject = NULL;
    jobject classObject = NULL;
    jobject fieldObject = NULL;
    jobjectArray myDexObjectArray = NULL;
    jstring jcookieName = NULL;
    jint cookie;

    DBGWRAP(JACDebug(env,JACModule4,func,(char *)"trying to get dex\n"));
    classDVMLoader = env->FindClass(CLASSNAME_DVMLOADER);
    mid = env->GetStaticMethodID(classDVMLoader, METHOD_GET_DEX, SIG_GET_DEX);
    DBGWRAP(JACDebug(env,JACModule4,func,(char *)"trying to get array of dexes\n" ));

    myDexObjectArray = (jobjectArray) env->CallStaticObjectMethod(classDVMLoader, mid);
    dexArrayLength = env->GetArrayLength(myDexObjectArray);
    *cookies =(int *) ac_calloc(dexArrayLength, sizeof(int));

  	jcookieName = env->NewStringUTF("mCookie");
    JACDebug(env,JACModule4,func,(char *)"Found %d  dexes\n", dexArrayLength);
    for (i= 0; i < dexArrayLength; i++ ){
    	JACDebug(env,JACModule4,func,(char *)"Processing %d dex\n", i);
       	myDexFileObject = env->GetObjectArrayElement(myDexObjectArray,i);
    	DBGWRAP(JACDebug(env,JACModule4,func,(char *)"Getting class\n"));

     	classDexFile = env->GetObjectClass(myDexFileObject);
    	DBGWRAP(JACDebug(env,JACModule4,func,(char *)"Getting method\n"));
        mid = env->GetMethodID(classDexFile, METHOD_GET_CLASS, SIG_GET_CLASS);
    	classObject = env->CallObjectMethod(myDexFileObject, mid);

    	DBGWRAP(JACDebug(env,JACModule4,func,(char *)"Getting class before getting cookie\n"));
      	classClass = env->FindClass(CLASSNAME_CLASS);
        mid = env->GetMethodID(classClass,METHOD_GETD,SIG_GETD);
    	fieldObject = env->CallObjectMethod(classObject, mid, jcookieName);

    	DBGWRAP(JACDebug(env,JACModule4,func,(char *)"Getting class field \n"));
    	classField = env->GetObjectClass(fieldObject);

    	DBGWRAP(JACDebug(env,JACModule4,func,(char *)"Getting class method \n"));
    	mid = env->GetMethodID(classField,METHOD_SET_ACC,SIG_SET_ACC);
		DBGWRAP(JACDebug(env,JACModule4,func,(char *)"Calling class void method \n"));
   	    env->CallVoidMethod(fieldObject, mid, 1 );

    	DBGWRAP(JACDebug(env,JACModule4,func,(char *)"Getting class int method \n"));
    	mid = env->GetMethodID(classField,METHOD_GET_INT,SIG_GET_INT);
    	DBGWRAP(JACDebug(env,JACModule4,func,(char *)"Calling class int method \n"));
       	cookie = env->CallIntMethod(fieldObject, mid, myDexFileObject);

    	(*cookies)[i] = cookie;
    	JACDebug(env,JACModule4,func,(char *)"Derived Cookie: %d\n", cookie);

        if (myDexFileObject) {
            env->DeleteLocalRef(myDexFileObject);
            myDexFileObject = NULL;
        }

        if (classDexFile) {
            env->DeleteLocalRef(classDexFile);
            classDexFile = NULL;
        }

        if (classObject) {
            env->DeleteLocalRef(classObject);
            classObject = NULL;
        }

        if (classClass) {
            env->DeleteLocalRef(classClass);
            classClass = NULL;
        }

        if (fieldObject) {
            env->DeleteLocalRef(fieldObject);
            fieldObject = NULL;
        }

        if (classField) {
            env->DeleteLocalRef(classField);
            classField = NULL;
        }
    }  


    if (classDVMLoader) {
        env->DeleteLocalRef(classDVMLoader);
    }

    if (myDexObjectArray) {
        env->DeleteLocalRef(myDexObjectArray);
    }

    if (jcookieName) {
        env->DeleteLocalRef(jcookieName);
    }

    if(length != dexArrayLength){
    	DBGWRAP(JACDebugWarning(env, JACModule4, func, (char *)"Cookie size mismatch: %d, %d\n", length, dexArrayLength));
	    return ACCESS_STATUS_GENERIC_ERROR;
    }

    return ACCESS_STATUS_SUCCESS;
}

