#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "iso98wrap.h"
#include "irdetoJavaSecurity.h"
#include "JACCommonModule.h"
#include "dexAdaptor.h"


ACCESS_STATUS classWalker8(JNIEnv* env, DexOperatorParam* param, int jarN);
ACCESS_STATUS classWalker9(JNIEnv* env, DexOperatorParam* param, int jarN);


ACCESS_STATUS classWalker(JNIEnv* env, int version, DexOperatorParam* param, int jarN)
{
	ACCESS_STATUS retVal = ACCESS_STATUS_GENERIC_ERROR;
	if(version >= 7 && version <= 8)
		retVal = classWalker8(env, param, jarN);
	else
		if(version > 8)
			retVal = classWalker9(env,param, jarN);
	return retVal;
}

