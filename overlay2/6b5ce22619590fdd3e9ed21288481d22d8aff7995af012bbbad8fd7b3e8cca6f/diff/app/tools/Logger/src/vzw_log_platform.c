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
@ description: This is source file which has implementaion of logging 
framework.
****************************************************************************/
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
#include <pthread.h>

#include "vzw_log.h"
//#include "vzw_log_interface.h"
#include "vzw_log_platform.h"

/* Thread-specific data key visible to all threads */
//STATIC pthread_key_t    vzw_threadkey;
EXTERN pthread_mutex_t vzw_logmutex, vzw_condmutex;
EXTERN THREAD_DATA* vzw_pCirList[VZW_LOG_MAX_THREADS];

//******************************************************************************************
Void vzwLogFree(void* pMem)
{
        free(pMem);
}

Void* vzwlogAlloc(size_t mem_size)
{
        return malloc(mem_size);
}

Void* vzwlogCalloc(size_t mem_size)
{
        return calloc(mem_size, 1);
}


//******************************************************************************************
//
#ifdef VZW_LOG_USE_CIRCULAR_BUFFER
/*******************************************************************************************
@ description:  This function is called whenever thread is being destroyed. 
		This function will delete thread specific data allocated during thread registration.
********************************************************************************************/
Void deInitThread(Void* pThreadData)
{

        THREAD_DATA* pThrData = (THREAD_DATA*)(pThreadData);

        if( pThreadData == NULL )
                return;

        /* lock the mutex, to make sure no one is accessing this buffer */
        pthread_mutex_lock(&vzw_logmutex);

        vzw_pCirList[pThrData->listIndex]  = NULL;

        if( pThrData->logBuff != NULL )
                vzwLogFree(pThrData->logBuff);

        vzwLogFree(pThreadData);

        /* unlock the mutex */
        pthread_mutex_unlock(&vzw_logmutex);
}
#endif

Void vzwLogInitPlatformSpecific(Void)
{
#ifdef VZW_LOG_USE_CIRCULAR_BUFFER
	//pthread_key_create(&vzw_threadkey, &deInitThread);
#endif
}

