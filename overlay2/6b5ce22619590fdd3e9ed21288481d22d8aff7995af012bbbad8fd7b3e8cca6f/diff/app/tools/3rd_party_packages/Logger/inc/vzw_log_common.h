
#ifndef __VZW_COMMON_H__
#define __VZW_COMMON_H__

#ifdef __cplusplus
EXTERN "C" {
#endif 

#include "vzwCommonDef.h"

#define LOG_CFG_PATH "/home/sanjeev/5g_base/Logger/vzw_config.txt"

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

