#ifndef __VZW_COMMON_DEFINITIONS_H__
#define __VZW_COMMON_DEFINITIONS_H__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <err.h>

#ifdef __cplusplus
extern "C" {
#endif

#define TRUE 1
#define FALSE 0
#define VZW_SUCCESS 0
#define VZW_FAILURE 1
#define VZW_SKIP 30
#define VZW_INVAL 20
#define VZW_MEM_FAILED 2

#define RETURN(x) return x
#define NULLP NULL
#define PUBLIC 
#define STATIC static
#define EXTERN extern

typedef bool            Bool;     /* boolean */

typedef char            S8;       /* signed - 8 bits */
typedef unsigned char   U8;       /* unsigned - 8 bits */

typedef short int             S16;      /* signed - 16 bits */
typedef unsigned short int    U16;      /* unsigned - 16 bits */

typedef int            S32;      /* signed - 32 bits */
typedef unsigned int   U32;      /* unsigned - 32 bits */
/*VZW_TBD: float*/
typedef long long 	S64;   /* unsigned - 64 bits */
typedef unsigned long long U64;   /* unsigned - 64 bits */

typedef void            Void;

#ifdef HEALTHMGR
#ifdef PUBLIC
#undef PUBLIC
#define PUBLIC                    /* public is c default scope */
#else /* not PUBLIC */
#define PUBLIC
#endif /* PUBLIC */
#ifdef PRIVATE
#undef PRIVATE
#define PRIVATE       static      /* private is c static scope */
#else /* not PRIVATE */
#define PRIVATE       static      /* private is c static scope */
#endif /* PRIVATE */
#endif

#ifdef VZW_MEM_DEBUG
EXTERN U32 vzwGlblMemAllocIndx, vzwGlblMemFreeIndx;
EXTERN FILE *vzwGlblMemAllocFilePtr, *vzwGlblMemFreeFilePtr;
#define MEM_ALLOC_DB_FILE "../Debug/memAllocDbFile.csv"
#define MEM_FREE_DB_FILE "../Debug/memFreeDbFile.csv"
#endif

/*VZW_TBD: Typecasting issue*/
#ifndef VZW_ALLOC
#ifndef VZW_MEM_DEBUG
#define VZW_ALLOC(pptr,size) \
	(*(pptr)) = malloc(size); \
	if(!(*(pptr))) \
	{ \
		printf("L_FATAL""malloc failed"); \
		exit(1); \
	}
#else
#define VZW_ALLOC(pptr,size) \
        (*(pptr)) = malloc(size); \
        if(!(*(pptr))) \
        { \
                printf("L_FATAL""malloc failed"); \
                exit(1); \
        } \
        vzwGlblMemAllocFilePtr = fopen(MEM_ALLOC_DB_FILE, "ab"); \
        if(!vzwGlblMemAllocFilePtr) \
        { \
                perror("fopen"); \
                SAGT_LOG(LOG_ERROR,"Failed to open Memory Alloc Database File"); \
                exit(1); \
        } \
        vzwGlblMemAllocIndx++; \
        if((fprintf(vzwGlblMemAllocFilePtr,"%d,%s,%s,%d,%p,%ld\n",vzwGlblMemAllocIndx,__FILE__,__func__,__LINE__,(*(pptr)),size))<0) \
	{ \
                perror("fprintf"); \
                SAGT_LOG(LOG_ERROR,"Failed to write memory allocation debugging information in Memory Alloc Database File"); \
	} \
        if((fclose(vzwGlblMemAllocFilePtr))!=0) \
	{ \
                perror("fclose"); \
                SAGT_LOG(LOG_ERROR,"Failed to close Memory Alloc Database File"); \
		exit(1); \
	}
#endif
#endif
//VZW_TBD: In the expansion of macro, check ending semicolon

#if 0
#ifndef VZW_ALLOC_PPTR
#define VZW_ALLOC_PPTR(tptr,size) \
	(*(tptr)) = (void **)malloc(size); \
	if(!(*(tptr))) \
	{ \
		printf("L_FATAL""malloc failed"); \
		exit(1); \
	}
#endif
#endif

#ifndef VZW_SET_ZERO
#define VZW_SET_ZERO(_buf, _size) \
	memset((U8 *)(_buf), 0, _size)
#endif

#ifndef VZW_FREE
#ifndef VZW_MEM_DEBUG
#define VZW_FREE(ptr) \
        if(ptr) \
        free((U8 *)(ptr)); \
	ptr = ((void *)0)
#else
#define VZW_FREE(ptr) \
        if(ptr) \
        free((U8 *)(ptr)); \
	ptr = ((void *)0); \
        vzwGlblMemFreeFilePtr = fopen(MEM_FREE_DB_FILE, "ab"); \
        if(!vzwGlblMemFreeFilePtr) \
        { \
                perror("fopen"); \
                SAGT_LOG(LOG_ERROR,"Failed to open Memory Free Database File"); \
                exit(1); \
        } \
        vzwGlblMemFreeIndx++; \
        if((fprintf(vzwGlblMemFreeFilePtr,"%d,%s,%s,%d,%p\n",vzwGlblMemFreeIndx,__FILE__,__func__,__LINE__,ptr))<0) \
	{ \
                perror("fprintf"); \
		SAGT_LOG(LOG_ERROR,"Failed to write memory allocation debugging information in Memory Free Database File"); \
	} \
        if((fclose(vzwGlblMemFreeFilePtr))!=0) \
	{ \
                perror("fclose"); \
		SAGT_LOG(LOG_ERROR,"Failed to close Memory Free Database File"); \
                exit(1); \
        }
#endif
#endif

#ifndef VZW_MEM_CPY
#define VZW_MEM_CPY(_dbuf,_sbuf , _size) \
	memcpy((U8 *)(_dbuf),(U8 *)(_sbuf), _size)
#endif

#if 0
#ifndef VZW_GET_MEM
#define VZW_GET_MEM(mptr,size,aptr) 
#endif
#endif

#ifndef VZW_GET_MEM
#ifndef VZW_MEM_DEBUG
#define VZW_GET_MEM(mptr,size,aptr) \
	(*(aptr)) = malloc(size); \
	if(!(*(aptr))) \
	{ \
		printf("L_FATAL""malloc failed"); \
		exit(1); \
	}
#else
#define VZW_GET_MEM(mptr,size,aptr) \
	(*(aptr)) = malloc(size); \
	if(!(*(aptr))) \
	{ \
		printf("L_FATAL""malloc failed"); \
		exit(1); \
	} 
#endif
#endif


#ifdef __cplusplus
}
#endif

#endif
