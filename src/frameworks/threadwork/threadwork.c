#include "threadwork.h"

memw_dblock *run(void *(*start_routine)(void*), void *args) {

    pthread_t t;
    memw_dblock *pthreadt = memw_alloc(&t, sizeof(pthread_t));
    int res = pthread_create((pthread_t*)pthreadt->data, NULL, start_routine, args);
    if (res != 0) {
        // thread creation failed
        return NULL;
    } else {
        return pthreadt;
    }

    return NULL;

}

bool stop(pthread_t thread) {
    return false;
}
