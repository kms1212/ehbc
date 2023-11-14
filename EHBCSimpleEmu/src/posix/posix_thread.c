#define _POSIX_C_SOURCE 200809L

#include "posix/posix_thread.h"

#include <pthread.h>

int create_thread(
    thread_t* thread,
    tattr_t* attr,
    void *(*func)(void*),
    void* args) {
    return pthread_create(thread, attr, func, args);
}

int join_thread(thread_t thread, void** retval) {
    return pthread_join(thread, retval);
}

void exit_thread(void* retval) {
    pthread_exit(retval);
}
