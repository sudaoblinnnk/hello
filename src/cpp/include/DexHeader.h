#ifndef DEX_HEADER_H
#define DEX_HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>


#include "iso98wrap.h"
#include "dexOperator.h"
#include "irdetoJavaSecurity.h"
#include "JACCommonModule.h"


static const char* strrchr_wrapper(const char* str, char c)
{
	const char* res = strrchr(str, c);
	if(!res)
		res = str;
	return res;
}

#if defined(_JAC_DEBUG_ANDROID) || defined(_JAC_SIGNING)
//#define LOGI(string, par) JACDebug(env, strrchr_wrapper(__FILE__,'/'),__FUNCTION__,__VA_ARGS__)
//#define LOGE(string, par) JACDebugWarning(env, strrchr_wrapper(__FILE__,'/'),__FUNCTION__,__VA_ARGS__)
#define LOGI(string, par) JACDebug(env, strrchr_wrapper(__FILE__,'/'),__FUNCTION__, string, par)
#define LOGE(string, par) JACDebugWarning(env, strrchr_wrapper(__FILE__,'/'),__FUNCTION__, string, par)
#else
#define LOGI(string, par)
#define LOGE(string, par)
#endif



#endif //DEX_HEADER_H
