#ifndef __POSIX_POSIX_THREAD_H__
#define __POSIX_POSIX_THREAD_H__

#include <pthread.h>

typedef pthread_t thread_t;
typedef pthread_attr_t tattr_t;

int create_thread(
    thread_t* thread,
    tattr_t* attr,
    void *(*func)(void*),
    void* args);

int join_thread(thread_t thread, void** retval);

void exit_thread(void* retval);

#endif  // __POSIX_POSIX_THREAD_H__
