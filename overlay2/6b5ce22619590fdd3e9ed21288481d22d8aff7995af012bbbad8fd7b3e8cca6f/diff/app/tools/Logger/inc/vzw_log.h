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

/****************************************************************************
@ description:  This is header file is used by logging framework module. 
		This file should not be included by any other application. 
		This is internal header file logging framework.
*****************************************************************************/

#ifndef __VZW_H__
#define __VZW_H__

//#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include <sys/types.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
//#include "vzw_log_interface.h"
#include "vzw_log_soc.h"
#include "vzw_log_common.h"

#define MAX_FILE_SIZE                   	3145728 /* 3MB */
#define MAX_LOG_BUF_SIZE                        5000
#define MAX_LOG_LEN                             256
#define MAX_FILENAME_LEN                	300
#define VZW_MAX_LOG_FILES               	260
#define VZW_LOG_MAX_TAX_NAME            	16
#define VZW_LOG_MAX_THREADS             	16
#define VZW_LOG_CIRBUF_READ_INTERVAL       	1       /* 60 seconds read interval */
#define VZW_LOG_MAX_CIRBUF_SIZE                 (1024*100)
#define VZW_LOG_MAX_TIME_STAMP                  80
#define VZW_LOG_TIME_ZONE_LEN                   8
#define VZW_LOG_FIXED_LENGTH_BUFFER_SIZE 	50
#define VZW_LOG_READ_POS_THRESHOLD 		300
#define VZW_LOG_REMOTE_LOGGING_PORT             9099
#define VZW_LOG_MAX_STACK_DEPTH                 24
#define VZW_LOG_MAX_TIME_STAMP                  80


typedef enum _endian {little_endian, big_endian} EndianType;

typedef enum {
	LOG_ARG_INT,
	LOG_ARG_STR,
	LOG_ARG_HEX,
	LOG_ARG_SPL
} LOG_ARG_TYPE;

#ifndef VZW_LOG_ENABLE_TEXT_LOGGING

typedef enum
{
        LOG_TIME_REFERENCE=0,
        LOG_TIME_DELIMITER,
        LOG_SIGSEGV,
        LOG_TIME_TTI_UPDT
} LOGID_TYPE;

typedef struct
{
        U16                     version;
        U32                     dummy32;
        U8                      endianType;
	S8                      szTimeZone[VZW_LOG_TIME_ZONE_LEN+1];
        U16                     END_MARKER;
   time_t      time_sec;
} __attribute__ ((__packed__)) FILE_HEADER;

#endif /* VZW_LOG_ENABLE_TEXT_LOGGING */

typedef struct {
        
        S8    szTaskName[VZW_LOG_MAX_TAX_NAME];
        U8*     logBuff;                	/* LOG Buffer */
        U32     logBufLen;  			/* Data Written till now */
        U32     logReadPos; 			/* Reader thread position */
        U8      listIndex;      		/* Index to global list */
        
} THREAD_DATA;


typedef enum vzw_LogCntLmt
{
   VZW_LOG_COUNT_LIMIT_START = 1,
   VZW_LOG_COUNT_LIMIT_STOP
}VZW_LogCntLmt;


/* Adding a type for socket Address */
typedef struct cmInetCmnSockAddr
{
   U32 type;
   U32 len;
   union
   {
      struct sockaddr_in addr;
#ifdef IPV6_SUPPORTED
      struct sockaddr_in6 addr6;
#endif
   }u;
}CmInetCmnSockAddr;



/* Default log level Error */
EXTERN S32 vzw_logLevel;           //L_MAX_LOG_LEVEL;

/* Default mask for each module is disabled */
EXTERN U32 vzw_modMask;


#ifndef VZW_LOG_ENABLE_TEXT_LOGGING

typedef struct
{
        time_t tv_sec;
        U32     ms_tti;
} __attribute__ ((__packed__)) LOGTIME;

typedef struct
{
        LOGID                   logId;          /* 4 bytes | 32 bits */
        LOGTIME         logTime;                /* 8 bytes */
        U16 argType    :2;
        U16 logLevel   :3;
        U16 numOfArgs  :3;
        U16                     len;
} __attribute__ ((__packed__)) LOGDATA;

typedef struct
{
        LOGDATA logData;
        U32 arg1;
        U32 arg2;
        U32 arg3;
        U32 arg4;
        S8 unusedByte[19]; /* To make it as 50 byte */
}  __attribute__ ((__packed__)) ARG4DATA;

#endif /* VZW_LOG_ENABLE_TEXT_LOGGING */

#endif /* __VZW_H__*/

