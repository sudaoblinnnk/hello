#ifndef _H_DEXADAPTOR_
#define _H_DEXADAPTOR_

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <assert.h>
#include "iso98wrap.h"
#include "irdetoJavaSecurity.h"



#include "dexOperator.h"

#define CLASSNAME_DEXFILE       "dalvik/system/DexFile"
#define METHOD_LOAD_DEX         "loadDex"
#define SIG_LOAD_DEX            "(Ljava/lang/String;Ljava/lang/String;I)Ldalvik/system/DexFile;"
#define METHOD_GET_CLASS        "getClass"
#define SIG_GET_CLASS           "()Ljava/lang/Class;"

#define CLASSNAME_CLASS         "java/lang/Class"
#define METHOD_GETD             "getDeclaredField"
#define SIG_GETD                "(Ljava/lang/String;)Ljava/lang/reflect/Field;"

#define CLASSNAME_FIELD         "java/lang/reflect/Field"
#define METHOD_SET_ACC          "setAccessible"
#define SIG_SET_ACC             "(Z)V"
#define METHOD_GET_INT          "getInt"
#define SIG_GET_INT             "(Ljava/lang/Object;)I"


#define CLASSNAME_DVMLOADER     "com/ir/app/android/DalvikVMClassLoader"
#define METHOD_GET_DEX          "getDexFile"
#define SIG_GET_DEX             "()[Ldalvik/system/DexFile;"
#define METHOD_LOAD_CLASS       "loadClass"
#define SIG_LOAD_CLASS          "(Ljava/lang/String;)Ljava/lang/Class;"

#define CLASSNAME_APP_MANAGER   "com/ir/app/ApplicationManager"
#define METHOD_GET_LOADER       "getClassLoader"
#define SIG_GET_LOADER          "()Ljava/lang/ClassLoader;"

#define CLASSNAME_THREAD	"java/lang/Thread"
#define METHOD_CUR_THREAD	"currentThread"	
#define SIG_CUR_THREAD		"()Ljava/lang/Thread;"
#define METHOD_SET_CTX_LDR	"setContextClassLoader"
#define SIG_GET_CTX_LDR		"(Ljava/lang/ClassLoader;)V"

#ifdef __cplusplus__
extern "C" {
#endif

ACCESS_STATUS getCookies(JNIEnv* env, int **cookies, int length);
ACCESS_STATUS classWalker(JNIEnv* env, int version, DexOperatorParam* param, int jarN);

#ifdef __cplusplus__
}
#endif



#endif
