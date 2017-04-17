#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "iso98wrap.h"
#include "dexOperator.h"


int processCookie8(JNIEnv *env,DexOperatorParam* params);
int processCookie9(JNIEnv *env,DexOperatorParam* params);
int processCookie10(JNIEnv *env,DexOperatorParam* params);

 
/*
 * This function is just for testing
 * to be removed (or moved to a unit test) later
 */
/*
JNIEXPORT jint JNICALL Java_com_dexoperator_ProcessData_processCookie (JNIEnv *env, jobject thiz, jint cookie, jint version, jobject myObj1, jobject myObj2)
{
	int retVal = -1;
	int i;


	DexOperatorParam param;
	param.jarsNumber = 1;
	param.cookies   = (int*)malloc(param.jarsNumber * sizeof(*param.cookies));
	param.dexFiles  = (void**)malloc(param.jarsNumber * sizeof(*param.dexFiles));
	param.gameDexData = (CAT_Bytes*)malloc(param.jarsNumber * sizeof(*param.gameDexData));
	{
		int res;
		//const char* REAL_ODEX_FILENAME = "/data/local/txt.txt";
		const char* REAL_ODEX_FILENAME = "/data/local/LunarLander.dex";
		//const char* REAL_ODEX_FILENAME = "/mnt/sdcard/txt.txt");
		FILE* fin = fin = fopen(REAL_ODEX_FILENAME, "r");
		if (!fin)
		{
			fprintf(stderr, "Cannot find input file\n");
			return -1;
		}
		if (fseek(fin, 0, SEEK_END) < 0)
		{
			fprintf(stderr, "fseek failed\n");
			return -1;
		}
		param.gameDexData[0].length = ftell(fin);
		if (param.gameDexData[0].length < 0)
		{
			fprintf(stderr, "ftell failed\n");
			return -1;
		}
		rewind(fin);

		param.gameDexData[0].bytes = (CAT_uint8*)malloc(param.gameDexData[0].length);
		res = fread(param.gameDexData[0].bytes, 1, param.gameDexData[0].length, fin);
		if (res < param.gameDexData[0].length)
		{
			fprintf(stderr,
					"fread failed, expected %d bytes, read %d bytes\n",
					param.gameDexData[0].length, res);
			return -1;
		}

		//LOGI("After overriding \n");
		//dumpMem(stderr, (char*) pDexFile->pOptHeader, 1024);
		fclose(fin);

		param.cookies[0] = cookie;

	}

	processCookie(env, version,&param);

	for(i = param.jarsNumber;i--;)
	{
		free(param.gameDexData[i].bytes);
	}

	free(param.dexFiles);
	free(param.cookies);

    return retVal;
}
*/

int processCookie(JNIEnv *env,int version, DexOperatorParam* params )
{
	int retVal = -1;
	if(version >= 7 && version <= 8)
	{
		retVal = processCookie8(env, params);
	}
	else
	{
		if(version > 8 && version <= 13)
		{
			retVal = processCookie9(env, params);
		}
		else
		{
			if (version > 13)
				retVal = processCookie10(env, params);
		}
	}

	return retVal;
}



