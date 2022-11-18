/*
#(c) Copyright 2021 by Amantya Technologies (Amantya) . All rights reserved.
#
#  This software is confidential and proprietary to Amantya.
#  No part of this software may be reproduced, stored, transmitted,
#  disclosed or used in any form or by any means other than as expressly
#  provided by the written Software License Agreement between Amantya
#  and its licensee.
#
#  AMANTYA MAKES NO OTHER WARRANTIES, EXPRESS OR IMPLIED, INCLUDING
#  WITHOUT LIMITATION WARRANTIES OF MERCHANTABILITY OR FITNESS FOR
#  A PARTICULAR PURPOSE WITH REGARD TO THIS SOFTWARE, SERVICE OR ANY RELATED MATERIALS.
#
#  IN NO EVENT SHALL AMANTYA BE LIABLE FOR ANY INDIRECT, SPECIAL,
#  CONSEQUENTIAL DAMAGES, OR PUNITIVE DAMAGES IN CONNECTION WITH OR ARISING
#  OUT OF THE USE OF, OR INABILITY TO USE, THIS SOFTWARE, WHETHER BASED
#  ON BREACH OF CONTRACT, PRODUCT LIABILITY, OR OTHERWISE, AND WHETHER OR NOT IT HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
#  Before any installation, use or transfer of this software, please
#  consult the written Software License Agreement or contact Amantya at
#  the location set forth below in order to confirm that you are
#  engaging in a permissible use of the software.
#
#  Amantya Technologies, Inc
#  Tel: +1 302 439 6030
#  Fax: +1 302 543 2691
#  Email: connect@amantyatech.com
#  Web: www.amantyatech.com
*/

/*******************************************************************************
@ description: This is source file which has implementaion of logging framework.

*******************************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/resource.h>
#include <fcntl.h>
#include <sys/time.h>
#include <time.h>
#include <stdarg.h>
#include <string.h>
#include <netinet/in.h>
#include <execinfo.h>
#include <dlfcn.h>
#include <dirent.h>
#include <pthread.h>
#include <errno.h>
#include <stdlib.h>
#include "vzw_log.h"
#include "vzw_log_interface.h"
#include "vzw_log_platform.h"
//#include "vzw_log_common.h"

//static pthread_mutex_t mutex;
FILE* vzw_fp = NULL;
S8 vzw_fileName[MAX_FILENAME_LEN];
S8 vzw_logDir[MAX_FILENAME_LEN];
S8 vzw_fileList[VZW_MAX_LOG_FILES][MAX_FILENAME_LEN];
const char* vzw_logStr[] =
{
   "ALWAYS",
   "FATAL",
   "ERROR",
   "WARNING",
   "EVENT",
   "INFO",
   "DEBUG"
};


#if defined(VZW_LOG_ENABLE_TEXT_LOGGING)
STATIC struct tm* getTime(S32* microseconds);
#endif
Void createNewLogFile(Void);
//Void createL2LogFile(Void);
Void* vzwLogServer(Void* arg);
Void closeConnection(S32 sockfd);
Void vzwLogCatchSegViolation(S32 sig);
Void flushData(S32 sig);
Void* cirBufReaderThread(Void* arg);
Void readCircularBuffers(Void);
Void vzwLogPrintConfiguration(Void);

#ifndef VZW_LOG_ENABLE_TEXT_LOGGING
EndianType getCPU_Endian(Void);
Void storeFileHeader(FILE* fp);
#endif

#ifdef VZW_LOG_USE_CIRCULAR_BUFFER

//STATIC THREAD_DATA *vzw_pSingCirBuff = NULL;
//STATIC U16 vzw_prevLogOffset = 0;

#endif

#ifndef VZW_LOG_ENABLE_TEXT_LOGGING
STATIC volatile U32 vzw_logPositionIndex = 0;
U32 vzwIpType = 4;     //CM_IPV4ADDR_TYPE;
#endif

//STATIC U32 numTtiTicks;

Void (*vzwlogSigHandler)(S32);

#ifdef VZW_LOG_USE_CIRCULAR_BUFFER
/* List of thread data pointers */
THREAD_DATA* vzw_pCirList[VZW_LOG_MAX_THREADS];

STATIC S32 vzw_nThreadsRegistered;
/* Mutex to protect circular buffers */
pthread_mutex_t vzw_logmutex, vzw_condmutex;
pthread_cond_t vzw_cond;

STATIC S32 thread_signalled;
#endif

U8 vzw_writeCirBuf = 0;

/* number of times log function is called */
S32  vzw_nWrites = 0;

/* Default circular buffer size 100Kb*/
U32 vzw_cirMaxBufferSize = VZW_LOG_MAX_CIRBUF_SIZE;

/* Socke descriptor if remote client is connected */
S32 vzw_nCliSocket = 0;

/* Remote Logging port */
STATIC U32 vzw_nLogPort = VZW_LOG_REMOTE_LOGGING_PORT;

/* Remote logging flag */
STATIC U8 vzw_bRemoteLoggingDisabled = 1;

/* Max File Size limit for each log file */
U32 vzw_uiMaxFileSizeLimit = MAX_FILE_SIZE;

/* Current File Number index */
U16  vzw_nCurrFileIdx = 0;

/* Global file descriptor for L2 & L3 */
STATIC S32 vzw_fd;

/* Default log level Error */
S32 vzw_logLevel = 0;           //L_MAX_LOG_LEVEL;

/* Default mask for each module is disabled */
U32 vzw_modMask = 0;


/* MAX Log Files 1 */
U16 vzw_nMaxLogFiles = 1;
U32 vzw_maxlogCount  = 50;
U32 vzw_logsDropCnt  = 0;
U32 vzw_logWriteCount = 0;

VZW_LogCntLmt vzw_LogCntLimit = VZW_LOG_COUNT_LIMIT_STOP;


//**********************************************************************
Void vzwSetLogFileSizeLimit(S8* maxFileSize)
{
	U16 maxfilesize;
        maxfilesize = atoi(maxFileSize);	
        vzw_uiMaxFileSizeLimit = (maxfilesize== 0) ? MAX_FILE_SIZE : maxfilesize*1048576;
}
//**********************************************************************
//
//**********************************************************************
Void vzwSetNumOfLogFiles(S8* nMaxFiles)
{
	U16 nmaxfiles;
	nmaxfiles = atoi(nMaxFiles);
        if( nmaxfiles > VZW_MAX_LOG_FILES || nmaxfiles == 0 ) {
                vzw_nMaxLogFiles = VZW_MAX_LOG_FILES;
                return;
        }

       	vzw_nMaxLogFiles = nmaxfiles;
}

//**********************************************************************
//
//**********************************************************************
Void vzwSetLogPath(S8* logDir)
{
        strncpy(vzw_logDir, logDir, MAX_FILENAME_LEN);
}

//*****************************************************************************
//
//*****************************************************************************
Void vzwSetLogFile(const char *fileName)
{
        strncpy(vzw_fileName, fileName, MAX_FILENAME_LEN);

}

//*****************************************************************************
//
//*****************************************************************************
Void vzwSetLogLevel(S8* logLevel)
{

	vzw_logLevel = (strtoul(logLevel, NULL, 0)) + 1;
}

//*****************************************************************************
//
//*****************************************************************************
Void flushData(S32 sig)
{
#ifdef VZW_LOG_USE_CIRCULAR_BUFFER
        readCircularBuffers();
#endif
	vzw_logWriteCount = 0;

        fclose(vzw_fp);

        if(SIGSEGV == sig)
        {
           signal(sig, SIG_DFL);
           kill(getpid(), sig);
        }
        else
        {
           exit(0);
        }

        return;
}

//******************************************************************************
//
//******************************************************************************
Void vzwLogPrintConfiguration(Void)
{
        fprintf(stderr, "Log File:\t\t[%s]\n", vzw_fileName);
       // fprintf(stderr, "Log level:\t\t[%s]\n", vzw_logStr[vzw_logLevel-1]);
        fprintf(stderr, "Module Mask:\t\t[%d]\n", vzw_modMask);
        fprintf(stderr, "File Size Limit:\t[%d]\n", vzw_uiMaxFileSizeLimit);
        fprintf(stderr, "Maximum Log Files:\t[%d]\n", vzw_nMaxLogFiles);
        fprintf(stderr, "Time Zone:\t\t[%s]\n", tzname[0]);

        fprintf(stderr, "Console Logging:\t[Disabled]\n");
        fprintf(stderr, "Binary Logging:\t\t[Enabled]\n");
        fprintf(stderr, "Remote Logging:\t\t[%s]\n", vzw_bRemoteLoggingDisabled ? "Disabled" : "Enabled");
        fprintf(stderr, "Remote Logging Port:\t[%d]\n", vzw_nLogPort);
#ifdef VZW_LOG_USE_CIRCULAR_BUFFER
        fprintf(stderr, "Circular Buffer:\t[Enabled]\n");
        fprintf(stderr, "Circular BufferSize:\t[Actual:%d][Derived:%d]\n",
                        vzw_cirMaxBufferSize/1024, vzw_cirMaxBufferSize);
#else
        fprintf(stderr, "Circular Buffer:\t[Disabled]\n");
#endif  /* VZW_LOG_USE_CIRCULAR_BUFFER */

}
//*****************************************************************************
#ifndef VZW_LOG_ENABLE_TEXT_LOGGING


/*************************************************************************************************
 @description : This is log server thread which listens on configred port. 
		This allows user to connect to log server and view log data live.
*************************************************************************************************/
Void*   vzwLogServer(Void* arg)
{
	CmInetCmnSockAddr serv_addr;
  	CmInetCmnSockAddr cli_addr;
  	S32 sockfd;
  	S32 newsockfd;
  	S32 clilen = 0;
  	S32 domain = AF_INET;
  	memset((Void*)&serv_addr, 0, sizeof(serv_addr));


  	if(vzwIpType == 4)
  	{
     		printf("Initializing VZWLOG for IPV4- %ld\n", vzwIpType);
     		clilen = serv_addr.len = sizeof(struct sockaddr_in);
     		domain = AF_INET;
     		serv_addr.type = 4;//CM_IPV4ADDR_TYPE;
     		serv_addr.u.addr.sin_family = AF_INET;
     		serv_addr.u.addr.sin_addr.s_addr = INADDR_ANY;
     		serv_addr.u.addr.sin_port = htons(vzw_nLogPort);
  	}
  	else
  	{
     		printf("Initializing VZWLOG for IPV6 - %ld\n",vzwIpType);
#ifdef IPV6_SUPPORTED
     		if(vzwIpType == 6)
     		{
        		clilen =  serv_addr.len = sizeof(struct sockaddr_in6);
        		domain = AF_INET6;
        		serv_addr.type = 6;//CM_IPV6ADDR_TYPE;
        		serv_addr.u.addr6.sin6_family = AF_INET6;
        		serv_addr.u.addr6.sin6_addr = in6addr_any;
        		serv_addr.u.addr6.sin6_port = htons(vzw_nLogPort);
     		}
#endif
  	}

	//SAGT_LOG(LOG_INFO,"create socket \n");
        if( (sockfd = socket(domain, SOCK_STREAM, 0)) < 0 ) {
                fprintf(stderr, "VZWLOG: Failed to create socket\n");
                _exit(0);
        }
	if( bind(sockfd, (struct sockaddr*)&(serv_addr.u),serv_addr.len) < 0 ) {
                fprintf(stderr, "VZWLOG: Error in Binding\n");
                perror("VZW_LOG");
                _exit(0);
        }

        listen(sockfd, 5);

        while(1)
        {
		
                newsockfd = accept(sockfd, (struct sockaddr*)&(cli_addr.u), (socklen_t *) &clilen);
                if( newsockfd < 0 ) {
                        fprintf(stderr, "VZWLOG: Error on accept\n");
                        perror("VZW_LOG");
                        return 0;
                }

                /* If remote logging is disabled or there is already 1 client connected */
                if( vzw_bRemoteLoggingDisabled || vzw_nCliSocket ) {
                        /* close the new connection and proceed */
                        closeConnection(newsockfd);
                        continue;
                }

                vzw_nCliSocket = newsockfd;
        }
        return 0;
}

//*************************************************************************************************
//
//*************************************************************************************************
Void closeConnection(S32 sockfd)
{
        shutdown(sockfd, SHUT_RDWR);
        close(sockfd);
}

#endif

#ifdef VZW_LOG_USE_CIRCULAR_BUFFER

#ifdef VZW_LOG_USE_TTI_LOGGING
#define CHECK_FILE_SIZE if( ++vzw_nWrites == 200 ) \
{ \
        vzw_nWrites = 0; \
        binlogLev1(LOG_TIME_REFERENCE, LOG_ALWAYS, (U32)time(NULL));\
}
#else
#define CHECK_FILE_SIZE
#endif /* VZW_LOG_USE_TTI_LOGGING */

#else /* VZW_LOG_USE_CIRCULAR_BUFFER */

#ifdef VZW_LOG_USE_TTI_LOGGING
#define CHECK_FILE_SIZE if( ++vzw_nWrites == 200 ) \
{ \
        if( vzw_fp && ftell(vzw_fp) > vzw_uiMaxFileSizeLimit ) { \
                createNewLogFile(); \
        }\
        vzw_nWrites = 0; \
        binlogLev1(LOG_TIME_REFERENCE, LOG_ALWAYS, (U32)time(NULL));\
}
#else
#define CHECK_FILE_SIZE if( ++vzw_nWrites == 200 ) \
{ \
        if( vzw_fp && ( (U32)(ftell(vzw_fp)) > vzw_uiMaxFileSizeLimit) ) { \
                createNewLogFile(); \
        }\
        vzw_nWrites = 0; \
}
#endif /* VZW_LOG_USE_TTI_LOGGING */
#endif /*  VZW_LOG_USE_CIRCULAR_BUFFER */

#ifdef VZW_LOG_USE_CIRCULAR_BUFFER

#define CHECK_CIRFILE_SIZE if( vzw_fp && ftell(vzw_fp) > vzw_uiMaxFileSizeLimit ) \
        createNewLogFile(); 

/**************************************************************************************************
// @param[in] tasName - Name of registering thread / task
// This function registers the thread for writing logs. It creates thread specific buffers.
***************************************************************************************************/

THREAD_DATA* vzwLogRegisterThread(const char* taskName)
{
        THREAD_DATA* pThrData = (THREAD_DATA*) vzwlogCalloc(sizeof(THREAD_DATA));

        if( pThrData == NULL ) {
                fprintf(stderr, "Failed to allocate memory for thread %s\n", taskName);
                _exit(0);
        }
        pthread_mutex_lock(&vzw_logmutex);

        /* Allocate circular buffer */
        pThrData->logBuff = (U8*) vzwlogAlloc(vzw_cirMaxBufferSize);

        if( pThrData->logBuff == NULL ) {
                fprintf(stderr, "Failed to allocate memory [%d] for thread %s\n",vzw_cirMaxBufferSize, taskName);
                _exit(0);
        }

        /* store task name */
        strcpy(pThrData->szTaskName, taskName);

        //rlSetThreadSpecificData(pThrData);

        pThrData->listIndex = vzw_nThreadsRegistered++;

        /* Store this pointerin global list, to access it later */
        vzw_pCirList[pThrData->listIndex]  = pThrData;

        pthread_mutex_unlock(&vzw_logmutex);

#ifdef VZW_LOG_DEBUG_MODE
        fprintf(stderr, "vzwLogRegisterThread: allocated CIRCULAR BUFFER of size [%d]\n", vzw_cirMaxBufferSize);
        fprintf(stderr, "vzwLogRegisterThread: Total registered threads [%d]\n", vzw_nThreadsRegistered);
#endif

        return pThrData;
}

//**************************************************************************************************
//
/***************************************************************************************************
@ description:  This thread wakes up periodically and transfer logs from thread specific buffer 
		into file system.
		If buffer is going to be full, this thread is signalled asynchrounously to read 
		buffered logs.
****************************************************************************************************/
Void* cirBufReaderThread(Void* arg)
{
	struct timespec timeout;
        S32 retCode;

#ifdef VZW_LOG_DEBUG_MODE
        fprintf(stderr, "Circular Buffer Reader thread started\n");
#endif

        while(1)
        {
                /*this thread is not active and waiting to timeout */
                thread_signalled = 0;

                /* set the thread timeout */
                timeout.tv_sec = time(NULL) + VZW_LOG_CIRBUF_READ_INTERVAL;
                timeout.tv_nsec = 0;

                /* wait for 120 seconds time interval to read buffer */
                retCode = pthread_cond_timedwait(&vzw_cond, &vzw_condmutex, &timeout);

                /* this means, this thread is already active, no need to give any other signal to wake up */
                thread_signalled = 1;

#ifdef VZW_LOG_DEBUG_MODE
                //if(retCode == 0) fprintf(stderr, "cirBufReaderThread: I am signalled to read data\n");
#endif

                /* If someone has given signal or there is timeout */
                if( retCode == 0 || retCode  == ETIMEDOUT ){
                        readCircularBuffers();
                        continue;
                }
                readCircularBuffers();

#ifdef VZW_LOG_DEBUG_MODE
                fprintf(stderr, "System is exiting ??");
                perror("cirBufReaderThread");
#endif
                break;
        }

        return NULL;
}

//*************************************************************************************************
//
//*************************************************************************************************


Void readCircularBuffers()
{
	U32 index, writerPos;

   	/* Check if process is L2. If L2 then return from here */
	/*   if (SFndProcId() == TENB_L2_PROC_ID)
   	{
      		return;
   	}*/

   	vzw_writeCirBuf = 1;

   	/* lock the mutex */
   	pthread_mutex_lock(&vzw_logmutex);

   	for(index = 0; index < vzw_nThreadsRegistered; index++)
   	{
      		THREAD_DATA* pThrData = vzw_pCirList[index];

      		if(pThrData == NULL)
         		continue;

      		writerPos = pThrData->logBufLen;

#ifdef VZW_LOG_DEBUG_MODE
      		fprintf(stderr, "Thread [%d] WritePos:[%d] ReadPos:[%d]\n", index+1, writerPos, pThrData->logReadPos);
#endif

      		if( pThrData->logReadPos < writerPos  )
      		{
        		/* Calculate the delta data to be read from buffer */
         		S32 dataLen = writerPos - pThrData->logReadPos;

        		/* Write the data into file */
         		if( fwrite(pThrData->logBuff+pThrData->logReadPos,1, dataLen, vzw_fp) == -1 )
         		{
#ifdef VZW_LOG_DEBUG_MODE
     		       		fprintf(stderr, "Failed to write data len %d\n", dataLen);
#endif
            			createNewLogFile();
            			continue;
			}
			/* reset log read position to last known position */
			pThrData->logReadPos = writerPos;
      		}
 		else if ( pThrData->logReadPos > writerPos )
      		{
        		/* Calculate the remaining data left in the buffer */
         		S32 dataLen = vzw_cirMaxBufferSize -  pThrData->logReadPos;

         		/* Write from last know position till end */
         		if( fwrite(pThrData->logBuff+pThrData->logReadPos, 1, dataLen, vzw_fp) == -1 )
         		{
#ifdef VZW_LOG_DEBUG_MODE
            			fprintf(stderr, "Failed to write data len %d\n", dataLen);
#endif
            			createNewLogFile();
            			continue;
         		}

         		/* Write from 0 to len position */
         		if( fwrite(pThrData->logBuff, 1, writerPos, vzw_fp) == -1 )
         		{
#ifdef VZW_LOG_DEBUG_MODE
            			fprintf(stderr, "Failed to write data len %d\n", dataLen);
#endif
            			createNewLogFile();
            			continue;
         		}

         		/* reset log read position to last known position */
         		pThrData->logReadPos = writerPos;
      		}
   	}

   	/* unlock the mutex */
   	pthread_mutex_unlock(&vzw_logmutex);

   	CHECK_CIRFILE_SIZE

      	vzw_writeCirBuf = 0;
}

#endif

//*******************************************************************************************
//
//*******************************************************************************************

Void getLogTimeStr(S8* ts)
{
#ifndef SS_LINUX
	struct timespec ptime;
#else
   	struct timeval ptime;
#endif
   	struct tm* tm;
   	S32 microseconds;

#ifndef SS_LINUX
   	clock_gettime(CLOCK_REALTIME, &ptime);
   	microseconds = ptime.tv_nsec / 1000;
#else
   	gettimeofday(&ptime, NULL);
   	microseconds = ptime.tv_usec/1000;
#endif

/* Obtain the time of day, and convert it to a tm struct. --*/
   	tm = localtime (&ptime.tv_sec);

   	if (tm) sprintf(ts,"%d_%d_%d_%d_%d_%d.%03d", tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday, tm->tm_hour, tm->tm_min,tm->tm_sec,microseconds);
}
//**********************************************************************************************
//
//**********************************************************************************************
Void vzwStartNewLogFile(const char* logFileName)
{
   vzwSetLogFile(logFileName);
   createNewLogFile();
}
//**********************************************************************************************
//
//**********************************************************************************************
Void createNewLogFile()
{
	FILE *prev_fp = vzw_fp;
   	char curTime[VZW_LOG_MAX_TIME_STAMP]; 
	int fd;
   	char *temptr;
   	/* get current time, when file is created */
   	getLogTimeStr(curTime);
   	temptr = strchr(curTime, '.');
   	if (temptr != NULLP)
   	{
      		*temptr = 0;
   	}
      	mkdir(vzw_logDir, O_RDWR);
   	/* remove old file from system */
/*   	if( vzw_fileList[vzw_nCurrFileIdx][0] != '\0' )
      	unlink(vzw_fileList[vzw_nCurrFileIdx]);*/

#ifdef VZW_LOG_ENABLE_TEXT_LOGGING
   	/* create file name, Example-> dbglog_2013_08_11_15_30_00 */
   	sprintf(vzw_fileList[vzw_nCurrFileIdx], "%s/%s_%s.txt",vzw_logDir, vzw_fileName, curTime );
   	vzw_fp = fopen(vzw_fileList[vzw_nCurrFileIdx], "w+");
#else
   	sprintf(vzw_fileList[vzw_nCurrFileIdx], "%s/%s_%s.bin",vzw_logDir, vzw_fileName, curTime );
   	vzw_fp = fopen(vzw_fileList[vzw_nCurrFileIdx], "ab+");
#endif

	if(vzw_fp == NULL ) {
      		fprintf(stderr, "Failed to open log file %s\n", vzw_fileList[vzw_nCurrFileIdx]);
   	   	return;
   	}

   	fd = fileno(vzw_fp);
   	vzw_fd = fd;
   	SAGT_LOG(LOG_DEBUG,"%s/%s_%s.txt",vzw_logDir, vzw_fileName, curTime );

   	if( fcntl(vzw_fd, F_SETFL, fcntl(vzw_fd, F_GETFL, 0) | O_NONBLOCK | O_ASYNC ) == -1 ) {
      		fprintf(stderr, "VZW_LOG: Cannot enable Buffer IO or make file non-blocking\n");
   	}

#ifdef VZW_LOG_ENABLE_TEXT_LOGGING
   	setvbuf ( vzw_fp , NULL, _IOLBF, 1024 );
#else
   	setvbuf ( vzw_fp , NULL, _IONBF, 1024 );
#endif

#ifndef VZW_LOG_ENABLE_TEXT_LOGGING
   	storeFileHeader(vzw_fp);
#endif

   	if( prev_fp != NULL )
      		fclose(prev_fp);

   	if( ++vzw_nCurrFileIdx == vzw_nMaxLogFiles )
      		vzw_nCurrFileIdx = 0;

#ifndef VZW_LOG_ENABLE_TEXT_LOGGING
#ifdef VZW_LOG_USE_TTI_LOGGING
   	binlogLev1(L_TIME_REFERENCE, L_ALWAYS, (U32)time(NULL));
#endif
#endif

}
//*******************************************************************************************
#ifndef VZW_LOG_ENABLE_TEXT_LOGGING
//*******************************************************************************************
EndianType getCPU_Endian(Void)
{
	unsigned short x;
    	U8 c;

    	x = 0x0001;;
    	c = *(U8 *)(&x);
    	printf("CHECK: %p\n",c);
    	return ( c == 0x01 ) ? little_endian : big_endian;
}

//********************************************************************************************
//
//********************************************************************************************
Void storeFileHeader(FILE* fp)
{
        FILE_HEADER fileHdr;

        memset(&fileHdr, 0, sizeof(FILE_HEADER));

        fileHdr.endianType = getCPU_Endian();
        fileHdr.dummy32 = 2818049;
        fileHdr.END_MARKER = 0xFFFF;
	printf("endianType = %u dummy =%u marker = %p\n", fileHdr.endianType, fileHdr.dummy32, fileHdr.END_MARKER);
        strncpy(fileHdr.szTimeZone, tzname[0], VZW_LOG_TIME_ZONE_LEN);

   	fileHdr.time_sec = time(NULL);
        if( fwrite((const Void*)&fileHdr, 1, sizeof(FILE_HEADER), fp) ==  -1 )
        {
#ifdef VZW_LOG_DEBUG_MODE
                fprintf(stderr, "Failed to write file header\n");
#endif
                createNewLogFile();
        }
}
#endif


//*******************************************************************************************
//
//********************************************************************************************

Void vzwLogCatchSegViolation(S32 sig)
{
        S32 i, nStrLen, nDepth;

        Void    *stackTraceBuf[VZW_LOG_MAX_STACK_DEPTH];
        const char* sFileNames[VZW_LOG_MAX_STACK_DEPTH];
        const char* sFunctions[VZW_LOG_MAX_STACK_DEPTH];

        S8 **strings; 
	S8 buf[VZW_LOG_MAX_STACK_DEPTH*128];
#ifdef T2K_MEM_LEAK_DBG
   DumpT2kMemLeakInfoToFile();
#endif
#ifdef SSI_STATIC_MEM_LEAK_DETECTION
   DumpStaticMemLeakFiles();
#endif

        nDepth = backtrace(stackTraceBuf, VZW_LOG_MAX_STACK_DEPTH);


        strings = (S8**) backtrace_symbols(stackTraceBuf, nDepth);

        for(i = 0, nStrLen=0; i < nDepth; i++)
        {
                sFunctions[i] = (strings[i]);
                sFileNames[i] = "unknown file";

#ifndef VZW_LOG_ENABLE_TEXT_LOGGING
          binlogLevS(LOG_SIGSEGV, LOG_FATAL, strings[i]);
#endif
     	 printf("BT[%d] : len [%d]: %s\n",i,(int)strlen(sFunctions[i]),strings[i]);
                sprintf(buf+nStrLen, "   in Function %s (from %s)\n", sFunctions[i], sFileNames[i]);
                nStrLen += strlen(sFunctions[i]) + strlen(sFileNames[i]) + 15;
        }

#ifdef VZW_LOG_ENABLE_TEXT_LOGGING
        //txtlogLevS(LOG_FATAL, "VZW_LOG", "NULL", 0, FMTSTR VZW_LOG_SEGFAULT_STR, buf);
        fflush(vzw_fp);
#else
        binlogLevS(LOG_SIGSEGV, LOG_FATAL, buf);
#endif

        flushData(SIGSEGV);
}

//****************************************************************************************
//
/***************************************************************************************

@ Description:  This function creates a log file. 
		If log file name is stdout & text  logging is enabled, 
 		file  pointer is  initialized to  standard output. 	
 		This  function also  creates thread on which remote application 
 		can connect & receive binary logs. 
 		If circular buffer is enabled, it creates thread key, which is 
 		used to store & retrieve thread specific buffers and data.

*****************************************************************************************/
Void vzwInitLog(U8 type)
{
#ifdef SS_VZW_BUF
	/* Initilize the signal handler */
        vzwlogSigHandler = &vzwLogCatchSegViolation;
#else
        signal(SIGSEGV, vzwLogCatchSegViolation);
        signal(SIGBUS, vzwLogCatchSegViolation);
        signal(SIGINT, flushData);
#endif
	/* set rate limit count for L3 Logs */
	vzw_maxlogCount = VZW_LOG_LIMIT_L3_COUNT;

#ifdef VZW_LOG_DEBUG_MODE
        vzwLogPrintConfiguration();
#endif /* VZW_LOG_DEBUG_MODE */
#if VZW_LOG_ALLOW_CONSOLE_LOGS
        if( !strcmp(vzw_fileName, "stdout")) {
                vzw_fp = stderr;
                return;
        }
#endif

#ifndef VZW_LOG_ENABLE_TEXT_LOGGING
        {
		printf("\n IP Type before reader thread spawn [%d]\n",type);
        	// Allocate circular buffer 
      		vzwIpType = type;
                // pthread_t tid;
                //if( pthread_create(&tid, NULL, &vzwLogServer, NULL) != 0 ) {
                //       fprintf(stderr, "Failed to initialize log server thread\n");
                //       _exit(0);
                // }
        }

   //     vzwLogInitPlatformSpecific();
#ifdef VZW_LOG_USE_CIRCULAR_BUFFER
{
    	pthread_t tid;
        pthread_mutex_init(&vzw_logmutex, NULL);
        if( pthread_create(&tid, NULL, &cirBufReaderThread, NULL) != 0 ) {
    	    fprintf(stderr, "Failed to initialize log server thread\n");
            _exit(0);
	}
/* Initialize single circular buffer for all threads */
	vzw_pSingCirBuff = vzwLogRegisterThread("DUMMY");
}

#endif
#endif

        createNewLogFile();
}

//************************************************************************************
//
//************************************************************************************

#ifdef VZW_LOG_ENABLE_TEXT_LOGGING 

#define TIME_PARAMS tm->tm_mday,tm->tm_mon+1,tm->tm_year+1900, tm->tm_hour,tm->tm_min,tm->tm_sec,microseconds

Void txtlogLev(S32 level, PSTR modName, PSTR file, PSTR func, S32 lineno, const char *fmt, ...)
{
	S32 microseconds=0;
        va_list ap;
        va_start(ap, fmt);
	if (level >= vzw_logLevel) return; // Log Lvl turned off
        pthread_mutex_lock(&vzw_logmutex);
	struct tm* tm = getTime(&microseconds);
	if(tm) fprintf(vzw_fp, "\n%d:%d:%d %d:%d:%d.%03d: %s: %s: %s: %s: %d: ", tm->tm_mday, tm->tm_mon+1, tm->tm_year+1900, tm->tm_hour, tm->tm_min, tm->tm_sec, microseconds, vzw_logStr[level], modName, file, func, lineno);
        vfprintf(vzw_fp, fmt, ap);
        pthread_mutex_unlock(&vzw_logmutex);

        va_end(ap);
	CHECK_FILE_SIZE

}

//*****************************************************************************************************
//
//*****************************************************************************************************
#else /* BINARY LOGGING */


Void saveLogData(const Void* buf, U16 len, U32 vzw_logWritePosIndex)
{

   ++vzw_logWriteCount ;

   if((1 == vzw_writeCirBuf) ||
         ((vzw_LogCntLimit == VZW_LOG_COUNT_LIMIT_START) &&
          (vzw_logWriteCount > vzw_maxlogCount)) ||
         (len > VZW_LOG_FIXED_LENGTH_BUFFER_SIZE))
   {
      vzw_logPositionIndex --;
      vzw_logsDropCnt++; 
      return;
   }
   
   /* check for if L2 is going to store logs 
   if (SFndProcId() == TENB_L2_PROC_ID) //to be discuss
   {
      if((vzw_l2LogBufLen + VZW_LOG_FIXED_LENGTH_BUFFER_SIZE) < L2LOG_BUFF_BLOCK_SIZE - sizeof(vzw_l2LogBufLen) )
      {
         // copying logs in shared buffer 
         memcpy(vzw_l2LogBufStartPtr, buf, len);

         vzw_l2LogBufStartPtr += VZW_LOG_FIXED_LENGTH_BUFFER_SIZE;
         // increasing total log length with L2 log length 
         vzw_l2LogBufLen += VZW_LOG_FIXED_LENGTH_BUFFER_SIZE;
      }
      return;
   }*/
#ifdef VZW_LOG_USE_CIRCULAR_BUFFER
   U32 logWritePointerPosition;
   THREAD_DATA* p = (THREAD_DATA*) vzw_pSingCirBuff;

   /* if buffer is about to full, write till end and continue writing from begining */
   if( ((vzw_logWritePosIndex+1) * VZW_LOG_FIXED_LENGTH_BUFFER_SIZE) > vzw_cirMaxBufferSize )
   {
      /* setting this flag to 1 to aVoid other threads
         to write in same circular buffer */
      vzw_writeCirBuf = 1;
      /* Start globalPositionIndex again */
      vzw_logPositionIndex = 0;

      /* if reader has not read initial data, minmum buffer size should be 100Kb */
      if( p->logReadPos < VZW_LOG_READ_POS_THRESHOLD && !thread_signalled ) {
         pthread_cond_signal(&vzw_cond); /* this will wakeup thread */
      }

      /* we are unlikely to hit this condition, but to prevent corruption of binary logs */
      /* we cannot write the data, if we write, data will be corrected forever */
      if( VZW_LOG_FIXED_LENGTH_BUFFER_SIZE > p->logReadPos ) {
         fprintf(stderr, "cannot write data.retune buffer parameters\n");

	  /* Copy data from the start of buffer */
      memcpy(p->logBuff, buf, len);
      /* Store buffer length position */
      p->logBufLen = VZW_LOG_FIXED_LENGTH_BUFFER_SIZE;
      vzw_prevLogOffset = 0;
      /* setting this flag to 0 so that other threads
         will start writing in circular buffer */
      vzw_writeCirBuf = 0;
   }
   }
   else
   {
      /* if reader is far behind and writer is reaching reader position, diff < 5Kb */
      /* its time to wakeup thread if reader has not read much of data */
      if( p->logReadPos > p->logBufLen && (p->logReadPos - p->logBufLen) < VZW_LOG_READ_POS_THRESHOLD )
         pthread_cond_signal(&vzw_cond); /* this will wakeup thread */

      logWritePointerPosition = (vzw_logWritePosIndex * VZW_LOG_FIXED_LENGTH_BUFFER_SIZE) + vzw_prevLogOffset;

      memcpy(p->logBuff + logWritePointerPosition, buf, len);
      p->logBufLen += VZW_LOG_FIXED_LENGTH_BUFFER_SIZE;
   }
#else /* !VZW_LOG_USE_CIRCULAR_BUFFER */
   if( fwrite((const Void*)buf, 1, VZW_LOG_FIXED_LENGTH_BUFFER_SIZE, vzw_fp) == -1 )
   {
#ifdef VZW_LOG_DEBUG_MODE
      fprintf(stderr, "Failed to write log data in file\n");
      perror("LOG");
#endif
      createNewLogFile();
   }
#endif /* VZW_LOG_USE_CIRCULAR_BUFFER */

   CHECK_FILE_SIZE

      /* If post processor connected send logs */
      if( vzw_nCliSocket &&  send(vzw_nCliSocket, buf, VZW_LOG_FIXED_LENGTH_BUFFER_SIZE, 0 ) == -1 ) {
         closeConnection(vzw_nCliSocket);
         vzw_nCliSocket = 0;
      }

#ifdef VZW_LOG_DEBUG_MODE_2
   {
      STATIC S32 maxlen = 0;
      if(len > maxlen) {
         maxlen = len;
         fprintf(stderr, "MAX BUFFER SIZE is binary mode is [%d]\n", maxlen);
      }
  }
#endif

}
//****************************************************************************************************
//
//****************************************************************************************************
#define VZW_LOG_SAVE_TIME(_logTime) _logTime.ms_tti = numTtiTicks

Void binlogLev0( LOGID logId, VZW_LOG_LEVEL logLevel, ...)
{
   //LOGDATA logData;
   ARG4DATA arg;

   VZW_LOG_SAVE_TIME(arg.logData.logTime);

   arg.logData.logId = logId;
   arg.logData.argType = LOG_ARG_STR;
   arg.logData.logLevel = logLevel;
   arg.logData.numOfArgs = 0;
   arg.logData.len = 0;

   saveLogData((const Void*)&arg, sizeof(LOGDATA), vzw_logPositionIndex++);
}

//******************************************************************************************
//
//******************************************************************************************

Void binlogLev1( LOGID logId, VZW_LOG_LEVEL logLevel, U32 arg1, ...)
{
   ARG4DATA arg;
   S32 bufsize;

   VZW_LOG_SAVE_TIME(arg.logData.logTime);

   arg.logData.logId = logId;
   arg.logData.argType = LOG_ARG_INT;
   arg.logData.logLevel = logLevel;
   arg.logData.numOfArgs = 1;
   arg.logData.len = sizeof(U32);

   arg.arg1 = arg1;
   bufsize = sizeof(LOGDATA)+arg.logData.len;

   saveLogData((const Void*)&arg, bufsize, vzw_logPositionIndex++);
}

//******************************************************************************************
//
//******************************************************************************************
Void binlogLev2( LOGID logId, VZW_LOG_LEVEL logLevel, U32 arg1, U32 arg2, ...)
{
   ARG4DATA arg;
   S32 bufsize;

   VZW_LOG_SAVE_TIME(arg.logData.logTime);

   arg.logData.logId = logId;
   arg.logData.argType = LOG_ARG_INT;
   arg.logData.logLevel = logLevel;
   arg.logData.numOfArgs = 2;
   arg.logData.len =  2 * sizeof(U32);

   arg.arg1 = arg1;
   arg.arg2 = arg2;

   bufsize = sizeof(LOGDATA)+arg.logData.len;

   saveLogData((const Void*)&arg, bufsize, vzw_logPositionIndex++);
}

//******************************************************************************************
//
//******************************************************************************************
Void binlogLev3( LOGID logId, VZW_LOG_LEVEL logLevel, U32 arg1, U32 arg2, U32 arg3, ...)
{
   ARG4DATA arg;
   S32 bufsize;

   VZW_LOG_SAVE_TIME(arg.logData.logTime);

   arg.logData.logId = logId;
   arg.logData.argType = LOG_ARG_INT;
   arg.logData.logLevel = logLevel;
   arg.logData.numOfArgs = 3;
   arg.logData.len = 3 * sizeof(U32);

   arg.arg1 = arg1;
   arg.arg2 = arg2;
   arg.arg3 = arg3;

   bufsize = sizeof(LOGDATA)+arg.logData.len;

   saveLogData((const Void*)&arg, bufsize, vzw_logPositionIndex++);
}

//******************************************************************************************
//
//******************************************************************************************
Void binlogLev4( LOGID logId, VZW_LOG_LEVEL logLevel, U32 arg1, U32 arg2, U32 arg3, U32 arg4, ...)
{
   ARG4DATA arg;

   VZW_LOG_SAVE_TIME(arg.logData.logTime);

   arg.logData.logId = logId;
   arg.logData.argType = LOG_ARG_INT;
   arg.logData.logLevel = logLevel;
   arg.logData.numOfArgs = 4;
   saveLogData((const Void*)&arg, sizeof(ARG4DATA), vzw_logPositionIndex++);
}

#endif  /* BINARY LOGGING */
//******************************************************************************************
//
//******************************************************************************************

#if defined(VZW_LOG_ENABLE_TEXT_LOGGING)
struct tm* getTime(S32* microseconds)
{
#ifndef SS_LINUX
   struct timespec ptime;
#else
   struct timeval ptime;
#endif

#ifndef SS_LINUX
   clock_gettime(CLOCK_REALTIME, &ptime);
   *microseconds = ptime.tv_nsec / 1000;
#else
   gettimeofday(&ptime, NULL);
   *microseconds = ptime.tv_usec;
#endif

   /* Obtain the time of day, and convert it to a tm struct. --*/
   return localtime (&ptime.tv_sec);
}

#endif
