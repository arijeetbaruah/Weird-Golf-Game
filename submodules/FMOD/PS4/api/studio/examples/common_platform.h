/*==============================================================================
FMOD Example Framework
Copyright (c), Firelight Technologies Pty, Ltd 2012-2020.
==============================================================================*/
#include <kernel.h>
#include <scebase.h>
#include <assert.h>

#define COMMON_PLATFORM_SUPPORTS_FOPEN

int FMOD_Main();

void Common_TTY(const char *format, ...);

typedef ScePthreadMutex Common_Mutex;

inline void Common_Mutex_Create(Common_Mutex *mutex)
{
    ScePthreadMutexattr attr;
    int err = scePthreadMutexattrInit(&attr);
    assert(err == SCE_OK);

    err = scePthreadMutexattrSettype(&attr, SCE_PTHREAD_MUTEX_RECURSIVE);
    assert(err == SCE_OK);

    err = scePthreadMutexInit(mutex, &attr, NULL);
    assert(err == SCE_OK);
    
    err = scePthreadMutexattrDestroy(&attr);
    assert(err == SCE_OK);
}

inline void Common_Mutex_Destroy(Common_Mutex *mutex)
{
    int err = scePthreadMutexDestroy(mutex);
    assert(err == SCE_OK);
}


inline void Common_Mutex_Enter(Common_Mutex *mutex)
{
    int err = scePthreadMutexLock(mutex);
    assert(err == SCE_OK);
}

inline void Common_Mutex_Leave(Common_Mutex *mutex)
{
    int err = scePthreadMutexUnlock(mutex);
    assert(err == SCE_OK);
}

