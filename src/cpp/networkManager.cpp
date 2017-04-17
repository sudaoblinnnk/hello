#include "iso98wrap.h"
#include "irdetoJavaSecurityExtension.h"
#include "JACCommonModule.h"
#include "networkManager.h"

#ifndef _JAC_SIGNING

#define NULL_IP		"0.0.0.0"
#define ID_ROOT		0
#define ID_SHELL	2000

union _cm_un {
    struct cmsghdr cm;
    char buffer[CMSG_SPACE(sizeof(int))];
} cm_un;

union _controlAddr {
    struct sockaddr_un  controlAddrUn;
    struct sockaddr     controlAddrPlain;
} controlAddr;

static short tokenNetEntry[] = {27392, 3840,  7424,  7680, 
			        7680,  19200, 3072,  512, 
				3840,  0,     6912,  0, 
				512,   26112, 28416, 29184};

static char tokenJwdp[JDWP_TOKEN_ELEM][JDWP_TOKEN_LEN] = {
        {0x2d,0x58,0x72,0x75,0x6e,0x6a,0x64,0x77,0x70},
        {0x2d,0x61,0x67,0x65,0x6e,0x74,0x6c,0x69,0x62,0x3a,0x6a,0x64,0x77,0x70}};

char JACModule6[]="networkManager.cpp";

static void fcntl_flags(int flags, char *output)
{
    if (flags & O_RDONLY)
        strcat(output, "O_RDONLY ");
    if (flags & O_WRONLY)
        strcat(output, "O_WRONLY ");
    if (flags & O_RDWR)
        strcat(output, "O_RDWR ");
    if (flags & O_CREAT)
        strcat(output, "O_CREAT ");
    if (flags & O_EXCL)
        strcat(output, "O_EXCL ");
    if (flags & O_NOCTTY)
        strcat(output, "O_NOCTTY ");
    if (flags & O_TRUNC)
        strcat(output, "O_TRUNC ");
    if (flags & O_APPEND)
        strcat(output, "O_APPEND ");
    if (flags & O_NONBLOCK)
        strcat(output, "O_NONBLOCK ");
    if (flags & O_SYNC)
        strcat(output, "O_SYNC ");
    if (flags & O_ASYNC)
        strcat(output, "O_ASYNC ");
}

static int pth_util_fd_valid(int fd)
{
    if (fd < 3 || fd >= FD_SETSIZE)
        return 0;
    if (fcntl(fd, F_GETFL) == -1 && errno == EBADF)
        return 0;
    return 1;
}

static void fd_info(int fd, char *msg)
{
    if(fd < 0 || fd >= FD_SETSIZE){
        strcpy(msg, "Out of range");
        return;
    }
    int rv = fcntl(fd, F_GETFL);
    if(rv == -1){
        strcpy(msg, strerror(errno));
    } else{
        fcntl_flags(rv, msg);
    }
}

static void retrieveNetworkData(unsigned char *data)
{
    unsigned char resultToken[SYSTEM_PROPERTY_LEN];

    memcpy(resultToken, NETTOKEN, nelem(tokenNetEntry));
    for(int pos = 0; pos < nelem(tokenNetEntry); pos ++){
        data[pos] = ntohs(tokenNetEntry[pos])^resultToken[pos];
    }
}

static void useStdJdwpApproach(JNIEnv *env, int fd, int *useStdInd)
{
    char fdName[FILE_PATH_LEN];
    char newBuf[MESSAGE_LINE_LEN];
    char msg[MESSAGE_LINE_LEN];
    int bytes;
    FILE *fp = NULL;

    DBGWRAP(JACDebug(env,JACModule6,__FUNCTION__,(char *)"start...\n"));
    if(! *useStdInd) return;
    snprintf(fdName, sizeof(fdName), PROC_INFO, getpid());
    if((fp=fopen(fdName,"rb")) == NULL){
    	DBGWRAP(JACDebug(env,JACModule6,__FUNCTION__,(char *)"NULL fp\n"));
	*useStdInd = 0;
        return;
    }
    if((bytes = fread(msg, 1, MESSAGE_LINE_LEN, fp)) == -1) {
    	DBGWRAP(JACDebug(env,JACModule6,__FUNCTION__,(char *)"Error read\n"));
        fclose(fp);
	*useStdInd = 0;
        return;
    }
    fclose(fp);
    for(int pos =0; pos < bytes; pos++){
        if(msg[pos] == '\0' && pos < bytes - 1){
            newBuf[pos] = ' ';
        } else{
            newBuf[pos] = msg[pos];
        }
    }
    JACDebug(env,JACModule6,__FUNCTION__,(char *)"Bytes read: %d\n", bytes);
    for(int pos =0; pos < JDWP_TOKEN_ELEM; pos++){
        if(strstr(newBuf, tokenJwdp[pos]) != NULL){
    	    DBGWRAP(JACDebug(env,JACModule6,__FUNCTION__,(char *)"cleanup\n"));
	    close(fd);
	    return;
        }
    }
    *useStdInd = 0;
    DBGWRAP(JACDebug(env,JACModule6,__FUNCTION__,(char *)"end\n"));
}

static void checkJdwpResponse(JNIEnv *env, int fd)
{
    struct msghdr    msg;
    struct cmsghdr*  cmsg;
    struct iovec     iov;
    char             dummy = '!';
    int              ret;
    char       	     buff[5];
    unsigned char    netData[SYSTEM_PROPERTY_LEN];

    iov.iov_base       = &dummy;
    iov.iov_len        = 1;
    msg.msg_name       = NULL;
    msg.msg_namelen    = 0;
    msg.msg_iov        = &iov;
    msg.msg_iovlen     = 1;
    msg.msg_flags      = 0;
    msg.msg_control    = cm_un.buffer;
    msg.msg_controllen = sizeof(cm_un.buffer);

    cmsg = CMSG_FIRSTHDR(&msg);
    cmsg->cmsg_len   = msg.msg_controllen;
    cmsg->cmsg_level = SOL_SOCKET;
    cmsg->cmsg_type  = SCM_RIGHTS;
    ((int*)CMSG_DATA(cmsg))[0] = -1;

    snprintf(buff, sizeof(buff), "%04x", getpid());
    buff[4] = 0;
    do {
        ret = send(fd, buff, 4, 0 );
    } while (ret < 0 && errno == EINTR);
    if (ret >= 0) {
    	DBGWRAP(JACDebug(env,JACModule6,__FUNCTION__,(char *)"PID sent as '%.*s' to ADB\n", 4, buff));
    }else{
    	DBGWRAP(JACDebugWarning(env,JACModule6,__FUNCTION__,(char *)"PID %s sent to ADB failed, errno: %d\n", buff, errno));
	return;
    }
    do {
    	ret = recvmsg(fd, &msg, 0);
    }while (ret < 0 && errno == EINTR);
    if(ret == 0){
	DBGWRAP(JACDebug(env,JACModule6,__FUNCTION__,(char *)"connection successful\n"));
    }else{
	JACDebugWarning(env,JACModule6,__FUNCTION__,(char *)" Failed, error code: %d\n", errno);
    }
}

static int processEvent(JNIEnv *env, int fd, int *netFlag)
{
    struct sockaddr_un serv_un_addr;
    char addrStr[UNIX_PATH_MAX];
    struct servent *pServent;
    socklen_t sockLen;
    unsigned char netData[SYSTEM_PROPERTY_LEN];

    JACDebug(env,JACModule6,__FUNCTION__,(char *)" Inspecting: %d\n",fd);
    memset(netData, 0, SYSTEM_PROPERTY_LEN);
    memset(&serv_un_addr, 0, sizeof(serv_un_addr));
    sockLen = sizeof(serv_un_addr);
    if(getpeername(fd,(struct sockaddr*)&(serv_un_addr),&sockLen) != 0){
    	JACDebugWarning(env,JACModule6,__FUNCTION__,(char *)"getpeername, error code: %d\n",errno);
        return 0;
    }
    retrieveNetworkData(netData);
    DBGWRAP(JACDebug(env,JACModule6,__FUNCTION__,(char *)"length: %d, entry: %d\n", sockLen, nelem(tokenNetEntry)));
    if(memcmp(serv_un_addr.sun_path, netData, nelem(tokenNetEntry)) != 0){
	return 0;
    }
    *netFlag = 1;
    close(fd);
    DBGWRAP(JACDebug(env,JACModule6,__FUNCTION__,(char *)"cleanup\n"));
    return 1;
}

static int processEvent2(JNIEnv *env, int fd, struct stat fs, int *netFlag)
{
    struct sockaddr_in servAddr;
    char addrStr[UNIX_PATH_MAX];
    char addrStrRemote[UNIX_PATH_MAX];
    unsigned short service;
    unsigned short serviceRemote;
    socklen_t sockLen;

    JACDebug(env,JACModule6,__FUNCTION__,(char *)" Inspecting: %d\n",fd);
    if(geteuid() == fs.st_uid){
    	DBGWRAP(JACDebug(env,JACModule6,__FUNCTION__,(char *)"ignore\n"));
	return 0;
    }
    memset(&servAddr, 0, sizeof(struct sockaddr_in));
    sockLen = sizeof(servAddr);
    if(getsockname(fd, (struct sockaddr*)&(servAddr),&sockLen) != 0) {
    	JACDebug(env,JACModule6,__FUNCTION__,(char *)"SN Error: %d\n",errno);
        return 0;
    }
    service = ntohs(servAddr.sin_port);
    inet_ntop(AF_INET, &(servAddr.sin_addr), addrStr, UNIX_PATH_MAX);
    memset(&servAddr, 0, sizeof(struct sockaddr_in));
    sockLen = sizeof(servAddr);
    if(getpeername(fd,(struct sockaddr*)&(servAddr),&sockLen) != 0){
    	JACDebug(env,JACModule6,__FUNCTION__,(char *)"PN Error: %d\n",errno);
        return 0;
    }
    serviceRemote = ntohs(servAddr.sin_port);
    inet_ntop(AF_INET, &(servAddr.sin_addr), addrStrRemote, UNIX_PATH_MAX);
    if(*netFlag &&
       servAddr.sin_family == AF_UNIX && service == 0 && serviceRemote == 0 &&
       strcmp(addrStr,NULL_IP) == 0 && strcmp(addrStrRemote,NULL_IP)==0 ){
    	DBGWRAP(JACDebug(env,JACModule6,__FUNCTION__,(char *)"found family, cleanup\n"));
	close(fd);
	*netFlag = 0;
    }
    return 1;
}

static const NetStat netStat = {
    pth_util_fd_valid,
    processEvent,
    processEvent2,
    fd_info,
    checkJdwpResponse,
    useStdJdwpApproach
};

int inspectJavaDebugger(JNIEnv *env) {

    struct stat fileStat;
    char fdInfo[MESSAGE_LINE_LEN];
    int fd_dup;
    int status;
    static int netFlag = 0;
    static int useStdJdwpInd = 1;

    DBGWRAP(JACDebug(env, JACModule6,__FUNCTION__,(char *)"start...\n"));
    for (int i = 0; i < FD_SETSIZE; i++) {
  	if(netStat.validate(i)){
    	    memset(fdInfo, 0, MESSAGE_LINE_LEN);
            fd_dup = dup(i);
            if (fd_dup > 0) {
                close(fd_dup);
		if(fstat(i,&fileStat) == 0 && S_ISSOCK(fileStat.st_mode)){
		    DBGWRAP(JACDebug(env, JACModule6,__FUNCTION__,(char *)"SK %d found, fd uid: %d, inode: %d, uid: %d\n",i,fileStat.st_uid,fileStat.st_ino,geteuid()));
             if (fileStat.st_uid == 0 || fileStat.st_uid == 2000 || fileStat.st_uid >= 10000){
		    netStat.getNetInfo(i, fdInfo);
                    netStat.stdVMCheck(env, i, &useStdJdwpInd);
		    if(!useStdJdwpInd && netStat.execute(env, i, &netFlag)) {
          	    	DBGWRAP(JACDebug(env, JACModule6,__FUNCTION__, (char *)"done. %4i: %4i\n", i, fd_dup));
		    }else if(!useStdJdwpInd){
          	    	DBGWRAP(JACDebug(env, JACModule6,__FUNCTION__, (char *)"%4i: %4i %5i %24s\n", i, fd_dup, fcntl(i, F_GETOWN), fdInfo));
			 netStat.execute2(env, i, fileStat, &netFlag);
		    }
		} 
        }
            }
	}
    }
    DBGWRAP(JACDebug(env, JACModule6,__FUNCTION__,(char *)"done\n"));
    return 1;
}
#endif
