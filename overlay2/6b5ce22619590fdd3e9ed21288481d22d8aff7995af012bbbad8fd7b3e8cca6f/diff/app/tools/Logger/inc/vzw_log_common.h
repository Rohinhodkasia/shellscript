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


#ifndef __VZW_COMMON_H__
#define __VZW_COMMON_H__

#ifdef __cplusplus
EXTERN "C" {
#endif 

#include "vzwCommonDef.h"

//#define LOG_CFG_PATH "/home/rajesh/5g_cps/5gCN/src/smf/tools/Logger/vzw_config.txt"

typedef U32 LOGID;

typedef enum {
        LOG_ALWAYS=0,
        LOG_FATAL,
        LOG_ERROR,
        LOG_WARNING,
        LOG_EVENT,
        LOG_INFO,
        LOG_DEBUG,
        LOG_UNUSED,
        LOG_MAX_LOG_LEVEL
} VZW_LOG_LEVEL;

typedef enum {
        DBG_CELLID,
        DBG_PEERID,
        DBG_ENBID,
        DBG_MMEID,
        DBG_CRNTI,
        DBG_UEIDX,
        DBG_UEID,
        DBG_RBID,
        DBG_LCID,
        DBG_LCGID,
        DBG_TRNSID,
        DBG_INSTID,
        DBG_MAX_IDs
} VZW_SPL_ARG;


typedef const char* PSTR;

#ifdef VZW_LOG_ENABLE_TEXT_LOGGING
#include <stdio.h>
EXTERN FILE* vzw_fp;
Void txtlogLev(S32 level, PSTR modName, PSTR file, PSTR func, S32 lineno, const char *fmt, ...);
#else

//Void binlogLevH( LOGID logId, R_LOG_LEVEL logLevel, PSTR hex, S32 hexlen, ...);
Void binlogLev0( LOGID logId, VZW_LOG_LEVEL logLevel, ...);
Void binlogLev1( LOGID logId, VZW_LOG_LEVEL logLevel, U32 arg1, ...);
Void binlogLev2( LOGID logId, VZW_LOG_LEVEL logLevel, U32 arg1, U32 arg2, ...);
Void binlogLev3( LOGID logId, VZW_LOG_LEVEL logLevel, U32 arg1, U32 arg2, U32 arg3, ...);
Void binlogLev4( LOGID logId, VZW_LOG_LEVEL logLevel, U32 arg1, U32 arg2, U32 arg3, U32 arg4, ...);
/*Void binlogLevE(LOGID logId, VZW_LOG_LEVEL logLevel, VZW_SPL_ARG splType, U32 splVal,
U32 arg1, U32 arg2, U32 arg3, U32 arg4, ...);
Void binlogLevS( LOGID logId, VZW_LOG_LEVEL logLevel, const char* str, ...);*/
#endif

Void hextostr(S8* p, PSTR h, S32 hexlen);
EXTERN S32 vzw_logLevel;
EXTERN U32 vzw_modMask;
//EXTERN const char* vzw_logStr[LOG_MAX_LOG_LEVEL];
//EXTERN const char* vzw_splStr[DBG_MAX_IDs];

#define VZW_LOG_SEGFAULT_STR "Segmentation Fault Occurred\n%s"

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __VZW_LOG_COMMON_H__ */

