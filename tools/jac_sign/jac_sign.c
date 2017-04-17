#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include "ac_common.h"
#include "ac_Crypto.h"

#include <stdio.h>

#define 	SIGNATURE_LEN		33

static ac_uint8 HMAC_HANDLE_ID[] = "YYT76H";

static ac_Context gContext = NULL;
static ac_SS_Context gSSJacVoucherContext = NULL;

int openAndReadFile(char * fileName, unsigned char** pOutputBuffer, unsigned int* pLength)
{
    FILE * file;
    int length = -1;
    int tmp;
        
    if (fileName == NULL)
        return -1;
        
    file = fopen(fileName, "rb");
        
    if (file == NULL)
        return -2;
        
    fseek(file, 0, SEEK_END);
    length = ftell(file);
    fseek(file, 0, SEEK_SET);
        
    *pOutputBuffer = malloc(length);
        
    tmp = fread(*pOutputBuffer, 1, length, file);
    if (length != tmp)
        {
            printf("openAndReadFile: %d, %d\n", tmp, length);
            return -3;
        }
        
    *pLength = length;
        
    fclose(file);   

    return 0;
}

ac_Status setIACSecurityContext(ac_char *storePath)
{
    ac_Status status = AC_OK;
    ac_uint32 isContextExist = 0;

    if(gContext != NULL && gSSJacVoucherContext != NULL){
    	return AC_OK;
    }

    if(gContext == NULL){
        if((EXTRACT_AC_ERROR(status = ac_Initialize(&gContext, storePath, NULL))) != AC_OK){
	        printf("There was an error in ac_Initialize:  Error code = 0x%x\n", status);
	        return AC_FAIL;
    	}	
        
    	if(gContext == NULL){
	        return AC_FAIL;
    	}
    }else{
	    isContextExist = 1;
    }
    
    status=ac_LoadSecureStore(&gSSJacVoucherContext,gContext,storePath);

    if((EXTRACT_AC_ERROR(status)) != AC_OK){
        printf("There was an error in ac_LoadSecureStore:  Error code = 0x%x\n", status);
        return AC_FAIL;
    }
	
    return(EXTRACT_AC_ERROR(status));
}

ac_Status getHmacSha256ByHandle(ac_uint8 *data, ac_uint32 dataLen, ac_char *storePath, ac_uint8 *digest)
{
    ac_Status status;

    ac_Op_Context pOperationContext = NULL;
    ac_SS_Data_Handle myHandle = 0;  //it is size_t

    if((EXTRACT_AC_ERROR(status = setIACSecurityContext(storePath))) != AC_OK){
	    return EXTRACT_AC_ERROR(status);    
    }

    if((EXTRACT_AC_ERROR(status = ac_GetHandleByID(gSSJacVoucherContext, "YYT76H", 6, &myHandle))) != AC_OK)
    {
        printf("There was an error in ac_GetHandleByID:  Error code = 0x%x\n", status);
        return AC_FAIL;
    }
    
    if(myHandle == 0) {
	    return AC_FAIL;
    }
    if((EXTRACT_AC_ERROR(status = ac_HMAC_Init_From_Store(gSSJacVoucherContext,
                                    AC_HASH_SHA256,
                                    myHandle,
                                    &pOperationContext))) != AC_OK){
        printf("There was an error in ac_HMAC_Init_From_Store:  Error code = 0x%x\n", status);
        return AC_FAIL;
    }
    if((EXTRACT_AC_ERROR(status = ac_HMAC_Update(gSSJacVoucherContext, pOperationContext, data, dataLen)))
                != AC_OK){
        printf("There was an error in ac_HMAC_Update:  Error code = 0x%x\n", status);
        return AC_FAIL;
    }
    if((EXTRACT_AC_ERROR(status = ac_HMAC_Finalize(gSSJacVoucherContext, pOperationContext, digest)))
                != AC_OK){
        printf("There was an error in ac_HMAC_Finalize:  Error code = 0x%x\n", status);
        return AC_FAIL;
    }

    return(EXTRACT_AC_ERROR(status));
}

int main(int argc, char **argv)
{
    ac_Status ret = AC_OK;
    ac_uint32 i;
    ac_uint8 * fileData = 0;
    ac_uint32 fileLen = 0;
    ac_uint8 digest[SIGNATURE_LEN];
    FILE *pOutput;
    char *apkname, *classfile, *securestore, *outputfile;
    time_t mytime = time(NULL);

    if (argc != 5) {
	printf("usage: jac_sign <apkname> <classfile> <securestore> <outputfile>\n");
	exit(1);
    }    

    apkname = argv[1];
    classfile = argv[2];	// should be "classes.dex"
    securestore = argv[3];
    outputfile = argv[4];

    printf("./jac_sign %s %s %s %s\n", argv[1], argv[2], argv[3], argv[4]);

    pOutput = fopen (outputfile, "w");

    fprintf(pOutput, "IRDETO JAC Version 2.0, %s", ctime(&mytime));
    fprintf(pOutput, "POLICY: 0\n");
    fprintf(pOutput, "APKName: %s\n", apkname);

    ret = openAndReadFile (classfile, &fileData, &fileLen);
    if ((EXTRACT_AC_ERROR(ret) != AC_OK)) {
        printf("Reading of %s failed.\n", classfile);
        goto EXIT;
    }

    getHmacSha256ByHandle(fileData, fileLen, securestore, digest);
    fprintf(pOutput, "signature: ");
    for (i=0; i<SIGNATURE_LEN-1; i++)
	fprintf(pOutput, "%02x", digest[i]);
    fprintf(pOutput, "\n#EOF\n");

 EXIT:
    if (fileData != 0)
        free(fileData);

    if (pOutput != NULL)
	fclose(pOutput);

    return ret;
}

