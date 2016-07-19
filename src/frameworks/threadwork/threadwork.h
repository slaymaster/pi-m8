#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <glib.h>

#ifndef MEMWORK_H
#define MEMWORK_H
#include "../memwork/memwork.h"
#endif

memw_dblock *run(void *(*start_routine)(void*), void *arg);
bool stop(pthread_t thread);
