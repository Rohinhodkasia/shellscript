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

/*********************************************************************************************
Description: This is header file is used by applications who want to define LOG Macros. 
	     This file can be refered for integrating log library into any application. 
	     API's defined in the file should be used by the program to modify data at runtime.
**********************************************************************************************/

#ifndef __VZW_LOG_INTERFACE_H__
#define __VZW_LOG_INTERFACE_H__
//#include "vzw_log_common.h"
#include "vzw_log.h"
#ifdef VZW_LOG_ENABLE_TEXT_LOGGING
STATIC const char* const VZW_LOG_MODULE_NAME = "VZW_AGENT";
#else
STATIC const char* VZW_LOG_MODULE_NAME = "VZW_AGENT";
STATIC S32 VZW_LOG_FILE_ID = 6;
STATIC S32 VZW_LOG_MODULE_ID = 16;
#endif

/**********************************************************************************************
Description: This API is used to set logging directory path. 
	     If set after the log initialization API, next file creation will happen in this 
	     directory
**********************************************************************************************/
void vzwSetLogPath(S8* logDir);

/**********************************************************************************************
Description: This API needs to be called after configuring all the required parameters by using 
	     below APIs. This API initializes logging framework.  
	     Log MACRO's should be used  only after calling this API.
**********************************************************************************************/
void vzwInitLog(U8 type);

/**********************************************************************************************
Description: This initializes log file name.  Log file name should be exclusive of extension. 
	     As framework appends ".bin" in case of binary file.
	     If file name is "stdout" and TEXT logging is enabled, logs will be printed in console. 
	     Run time file name can be changed and will be applicable when next file is created.
**********************************************************************************************/
void vzwSetLogFile(const char* fileName);

/***********************************************************************************************
Description: Use this API to set log level. This API supports run time modification of log level.
************************************************************************************************/
void vzwSetLogLevel(S8* logLevel);


/************************************************************************************************
Description: This API is used to set log file size limit for single file.
*************************************************************************************************/
void vzwSetLogFileSizeLimit(S8* maxFileSize);


/************************************************************************************************
Description: This API sets the limit of number of log files  that can be created by logging framework.
*************************************************************************************************/
void vzwSetNumOfLogFiles(S8* nMaxFiles);

EXTERN void vzwStartNewLogFile(const char* logFileName);

#if defined(VZW_LOG_ENABLE_TEXT_LOGGING) 
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define FMTSTR "%d-%d-%d %d:%d:%d.%03d: %s: %s: %d %s: "
#define FMTSTR_S "%d-%d-%d %d:%d:%d.%03d: %s: %s: %d %s: %s: %ld: "

#define SAGT_LOG(_level, args...) txtlogLev(_level, VZW_LOG_MODULE_NAME, __FILENAME__, __func__, __LINE__, args)

#else /* BINARY LOGGING */

#define LOG_ARG0(_level, _fmtStr) \
if( _level < vzw_logLevel || vzw_modMask & VZW_LOG_MODULE_ID)\
{ \
        binlogLev0(0, _level, __FILE__,__LINE__, _fmtStr, VZW_LOG_FILE_ID, VZW_LOG_MODULE_NAME); \
}

#define LOG_ARGN(_N, _level, _fmtStr, ...) \
if( _level < vzw_logLevel || vzw_modMask & VZW_LOG_MODULE_ID)\
{ \
        binlogLev##_N(_N, _level, ##__VA_ARGS__, __FILE__,__LINE__, _fmtStr, VZW_LOG_FILE_ID, VZW_LOG_MODULE_NAME); \
}

#define VZW_LOG0(_level, _lstr)                            LOG_ARG0(_level, _lstr)
#define VZW_LOG1(_level, _lstr, _arg1)                     LOG_ARGN(1, _level, _lstr, _arg1)
#define VZW_LOG2(_level, _lstr, _arg1, _arg2)              LOG_ARGN(2, _level, _lstr, _arg1, _arg2)
#define VZW_LOG3(_level, _lstr, _arg1, _arg2, _arg3)       LOG_ARGN(3, _level, _lstr, _arg1, _arg2, _arg3)
#define VZW_LOG4(_level, _lstr, _arg1, _arg2, _arg3, _arg4)LOG_ARGN(4, _level, _lstr, _arg1, _arg2, _arg3, _arg4)

#endif /* if defined(VZW_LOG_ENABLE_TEXT_LOGGING) */

#endif //__VZW_LOG_INTERFACE_H__
