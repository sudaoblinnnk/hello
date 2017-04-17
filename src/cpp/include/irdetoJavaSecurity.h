#ifndef _H_IRDETOJAVASECURITY_
#define _H_IRDETOJAVASECURITY_

#include "iso98wrap.h"
#include "ac_SecureStore.h"

#define TYPE_JVM_DALVIK		"DalvikVM"
#define TYPE_JVM_STD		"StdVM"

/* #ifdef __ARM_EABI__
#define TYPE_JVM		TYPE_JVM_DALVIK
#else
#define TYPE_JVM		TYPE_JVM_STD
#endif
*/ 
// not sure if the __ARM_EABI__ is the real flag to decide the virtual machine type is delvik 
// and cannot find a flag for anddord x86 to deciede the VM type
// Because the Android only use delvik VM now, so the quick solution is just use it
#define TYPE_JVM		TYPE_JVM_DALVIK

#define		EXIT_CODE_STARTUP	1
#define		EXIT_CODE_APP_IV	20
#define		EXIT_CODE_TBAD		21

#define 	CLASSNAME_LEN		256
#define 	SIGNATURE_LEN		65 
#define 	READ_LINE_LEN		512
#define 	VOUCHER_PATH_LEN	256
#define 	MESSAGE_LINE_LEN	1024
#define 	JNI_RETURN_MESSAGE_LEN	64	
#define 	FILE_PATH_LEN		VOUCHER_PATH_LEN
#define		STATUS_CODE_STR_LEN	10
#define		HANDLE_ID_LEN		128
#define		JVM_TYPE_LEN		20
#define         SYSTEM_PROPERTY_LEN     256

#define 	TOKEN_SH1_HASH		"HmacSHA1"
#define 	TOKEN_SH256_HASH	"HmacSHA256"
#define 	TOKEN_SIGNATURE		"signature"
#define		TOKEN_CLASS_NAME	"Name"
#define		TOKEN_STUB_CLASS_NAME	"StubName"
#define		TOKEN_APK_NAME		"APKName"
#define		TOKEN_POLICY		"POLICY"
#define		TOKEN_JAC_SIGNARURE	"JAC_SIGNARURE"
#define 	VOUCHER_PATH_DEFAULT	"/etc"
#define		VOUCHER_NAME		"irdeto_java_access.dat" 
#define		JAC_DATA_NAME		"jac_store_data.dat"
#define     JAC_ACV_NAME     "jac_store.dat"

#ifdef _JAC_STANDALONE

#define		CLASSNAME_NATIVE_APP	"com/ir/app/NativeAppManager"
#define		CLASSNAME_MYSTUB	"com/ir/app/android/StubInterface"
#else
#define		CLASSNAME_MYSTUB	"com/ir/app/android/system/StubInterface"
#endif
#define		METHOD_GET_APK_NAME	"getAPKName"
#define		SIG_GET_APK_NAME	"()Ljava/lang/String;"
#define		METHOD_GET_VOUCHER_PATH	"getVoucherFullPath"
#define		SIG_GET_VOUCHER_PATH	"()Ljava/lang/String;"
#define 	METHOD_GET_APKPATH	"getAPKPath"
#define		SIG_GET_APKPATH		"()Ljava/lang/String;"
#define 	METHOD_GET_ASSET_DIR	"getAssetDir"
#define		SIG_GET_ASSET_DIR	"()Ljava/lang/String;"

#define		CLASSNAME_LOG		"android/util/Log"
#define		METHOD_DEBUG		"d"
#define		SIG_DEBUG		"(Ljava/lang/String;Ljava/lang/String;)I"
#define		METHOD_DEBUG_WARNING	"w"
#define        	CLASSNAME_CM_SIGN 	"com/irdeto/secureaccess/CryptoManager"
#ifdef _JAC_STANDALONE
#define        	CLASSNAME_CRYPTOMANAGER "com/ir/app/CryptoManager"
#else
#define         CLASSNAME_CRYPTOMANAGER "com/ir/app/android/system/CryptoManager"
#endif
#define         METHOD_HASH_FILE        "hashFileContents"
#define         SIG_HASH_FILE 		"(Ljava/lang/String;)Ljava/lang/String;"
#define         METHOD_GET_DIG_SIG	"getDigitalSignature"
#define		SIG_GET_DIG_SIG		"(Ljava/lang/String;Z)Ljava/lang/String;"
#define		MATHOD_GET_APK_SIG	"getAPKDigitalSignature"
#define 	SIG_GET_APK_SIG		"(Ljava/lang/String;Z)Ljava/lang/String;"
#define		METHOD_GET_APK_BYTES	"getAPKBytes"
#define		SIG_GET_APK_BYTES	"(Ljava/lang/String;)[B"
#define		METHOD_GET_CLASS_BYTES	"getClassBytes"
#define		SIG_GET_CLASS_BYTES	"(Ljava/lang/String;)[B"

#define 	CLASS_STACK_TRACE_ELEM	"java/lang/StackTraceElement"
#define		METHOD_TO_STRING	"toString"
#define		SIG_TO_STRING		"()Ljava/lang/String;"
#define		METHOD_GET_CLASS_NAME	"getClassName"
#define 	SIG_GET_CLASS_NAME	"()Ljava/lang/String;"

#define		CLASS_THROWABLE		"java/lang/Throwable"
#define		METHOD_GET_STACK_TRACE	"getStackTrace"
#define		SIG_GET_STACKTRACE	"()[Ljava/lang/StackTraceElement;"
#define		METHOD_THROWABLE_CONST	"<init>"
#define		SIG_THROWABLE_CONST	"()V"

#define		CLASS_CLASS		"java/lang/Class"
#define 	METHOD_GET_NAME_FOR_CLS	"getName"
#define		SIG_GET_NAME_FOR_CLS	"()Ljava/lang/String;"

#define		CLASS_ARRAY_LIST	"java/util/ArrayList"
#define 	METHOD_ADD		"add"
#define		SIG_ADD			"(Ljava/lang/Object;)Z"

#define 	CLASS_APP_DVM		"com/ir/app/android/ApplicationDalvikVM"
#define		METHOD_SET_LDR_ENV	"setupLoaderEnv"
#define		SIG_SET_LDR_ENV		"(Ljava/lang/String;Ljava/lang/String;)V"
#define 	METHOD_GET_DVM_LDR      "getDVMLoader"
#define 	SIG_GET_DVM_LDR         "()Lcom/ir/app/android/DalvikVMClassLoader;"

#define		CLASS_BOUNDARY_STD_NAME	"android.app.Activity"

#define nelem(x) ((int) (sizeof(x) / sizeof(x[0])))

typedef struct _IRDETO_SECURE_DATA
{
    char **className;
    char **signature;
    char stubClassName[CLASSNAME_LEN];
    char stubSignature[SIGNATURE_LEN];
    char APKName[CLASSNAME_LEN];
    char APKSignature[SIGNATURE_LEN];
    unsigned char **objectBytes;
    unsigned char **objectSerialUIDByes;      
    int elementSize;
    int stubClassIsSet;
    int APKIsSet;
    int boundaryClassIdx;

}IRDETO_SECURE_DATA; 

typedef enum _ACCESS_STATUS
{
    ACCESS_STATUS_SUCCESS = 1,
    ACCESS_STATUS_INVALID_JAVA_CLASS, 
    ACCESS_STATUS_INVALID_JAVA_METHOD,
    ACCESS_STATUS_NO_VOUCHER_FOUND,
    ACCESS_STATUS_EMPTY_VOUCHER,
    ACCESS_STATUS_INVALID_VOUCHER_CLASS_SIGNATURE_MISMATCH,
    ACCESS_STATUS_INVALID_VOUCHER_INVALID_CLASS_SIGNATURE,
    ACCESS_STATUS_INVALID_VOUCHER_INVALID_SIGNATURE,
    ACCESS_STATUS_MEMORY_ALLOCATION_FAILED,
    ACCESS_STATUS_AUTHENTICATION_FAILED,
    ACCESS_STATUS_AUTHENTICATION_FAILED_SIG_MISMATCH,
    ACCESS_STATUS_AUTHENTICATION_FAILED_MISSING_CLASS,
    ACCESS_STATUS_AUTHENTICATION_FAILED_CLASS_NOT_REGISTERED,
    ACCESS_STATUS_AUTHENTICATION_FAILED_STUB_CLASS,
    ACCESS_STATUS_FAILED_STACK_TRACE,
    ACCESS_STATUS_INVALID_JAC_POLITY,
    ACCESS_STATUS_INVALID_VOUCHER_PATH,
    ACCESS_STATUS_INVALID_VOUCHER_APK_SIGNATURE_MISMATCH,
    ACCESS_STATUS_AUTHENTICATION_FAILED_CLASSES_SIGNATURE_MISMATCH,
    ACCESS_STATUS_INVALID_VOUCHER_FROM_IAC,
    ACCESS_STATUS_INVALID_STORAGE_BASE,
    ACCESS_STATUS_INVALID_JAVA_ARCHIVE,
    ACCESS_STATUS_FAILED_TO_ALLOCATE_FUNCTION,
    ACCESS_STATUS_INVALID_JNI_ENV,
    ACCESS_STATUS_INVALID_INVALID_PARAMETER,
    ACCESS_STATUS_SHUTDOWN_ERROR,
    ACCESS_STATUS_IAC_CONTEXT_EXIST,
    ACCESS_STATUS_IAC_CONTEXT_NOT_READY,
    ACCESS_STATUS_INVALID_IAC_CONTEXT,
    ACCESS_STATUS_NO_APK_ENTRY,
    ACCESS_STATUS_GENERIC_ERROR,
    ACCESS_STATUS_NO_THREAD_AVAILABLE,
    ACCESS_STATUS_THREAD_SHUTDOWN,
    ACCESS_STATUS_APP_IV_FAILED

}ACCESS_STATUS;

typedef enum _JAC_SECURITY_POLICY
{
	JAC_SECURITY_POLICY_STATIC_ONLY = 0, 
    JAC_SECURITY_POLICY_NORMAL = 1,
    JAC_SECURITY_POLICY_STRICT_STUB_CHECK,
    JAC_SECURITY_POLICY_HIGHEST

}JAC_SECURITY_POLICY;

typedef enum _JACThreadIndex
{
    JAC_THREAD_INDEX_APP_IV     =       0,
    JAC_THREAD_INDEX_ADBG       =       1,
    JAC_THREAD_INDEX_DYN_IV     =       2,
    JAC_THREAD_INDEX_MAIN_IV    =       3

}JACThreadIndex;

typedef struct _JAC_FUNCTION
{
    char typeJVM[JVM_TYPE_LEN];
    int (*fPtrSearchClasses)(JNIEnv *, IRDETO_SECURE_DATA*);
    ACCESS_STATUS (*fPtrGetClassBytes)(JNIEnv*, char *, unsigned char **, int *, jbyteArray*);
    ACCESS_STATUS (*fPtrInitializeJavaStorage)(JNIEnv *);
}JAC_FUNCTION;

#ifdef __cplusplus__
extern "C" {
#endif

// authenticateAllRegisteredClasses()
ACCESS_STATUS aARC(JNIEnv *env);

ACCESS_STATUS aARC(JNIEnv *env, JavaVM *jvm);
// authenticateCallingClasses()
ACCESS_STATUS aCC(JNIEnv *env, jobject obj);
//This should be called when application exits
ACCESS_STATUS JAC_Shutdown(JNIEnv *env);

ACCESS_STATUS setExternalContext(ac_Context context);

ACCESS_STATUS exportContext(ac_Context *context, ac_SS_Context *sContext);

ACCESS_STATUS checkForCompletion(JNIEnv *env, JACThreadIndex index);

#ifdef __cplusplus__
}
#endif

#endif
