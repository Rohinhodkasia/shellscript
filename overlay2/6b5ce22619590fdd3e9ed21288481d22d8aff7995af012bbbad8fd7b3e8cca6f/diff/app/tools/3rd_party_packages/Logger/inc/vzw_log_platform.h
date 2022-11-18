#ifndef __VZW_LOG_PLATFORME_H__
#define __VZW_LOG_PLATFORM_H__

Void vzwLogFree(Void* pMem);
Void deInitThread(Void* pThreadData);
Void vzwLogInitPlatformSpecific(Void);
Void* vzwlogAlloc(size_t memSize);
Void* vzwlogCalloc(size_t memSize);
#endif /* __VZW_LOG_PLATFORME_H__ */

