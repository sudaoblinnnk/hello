#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include <zlib.h>


static int compressFile(char *inFileName)
{    
    int bytesHave = 0;
    int bytesRead = 0;
    int ret;
    int destLen = 0;
    unsigned char *pDest = NULL;
    unsigned char *pSrc = NULL;
    char outFileName[100];
    FILE *fp = NULL;

    if((fp = fopen(inFileName, "rb")) == NULL){
        printf("Unable to open file: %s\n", inFileName);
        return -1;
    }    

    fseek(fp, 0, SEEK_END);
    bytesHave = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    pSrc = calloc(bytesHave+10, 1);
    pDest = calloc(bytesHave, 1);
    bytesRead = fread(pSrc, 1, bytesHave, fp);
    fclose(fp);
    if(bytesRead != bytesHave){
        printf("Failed to read file: %s, size doesn't match\n", inFileName);
        return -1;
    }
    printf("byte read: %d\n", bytesRead);
    destLen = bytesRead;
    ret = compress(pDest, &destLen, pSrc, bytesRead);
    if(ret != Z_OK){
        printf("Failed to call zlib's compress(), error code: \n");
        return -1;
    }    
    printf("Compressed file size: %d\n", destLen);
    sprintf(outFileName, "%s_out", inFileName);
    if((fp = fopen(outFileName, "wb+")) == NULL){
        printf("Unable to open file: %s\n", outFileName);
        return -1;
    }
    ret = fwrite (pDest, 1, destLen, fp);
    if(ret != destLen){
         printf("Error in writing to file: %s, size not match\n",outFileName);
         return -1;
    }    
    fclose(fp);
    printf("File compression successful\n");
}

int main(int argc, char** argv)
{
    char inFileName[100];
    char outFileName[100];

    if(argc < 2){
        printf("Invalid parameters\n");
        return 1;
    }    
    strcpy(inFileName, argv[1]);
    if(compressFile(inFileName) == -1) return 2;
    return 0;
}    

