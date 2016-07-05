#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "../memwork/memwork.h"


memw_dblock *run(void *(*start_routine)(void*), void *arg);
bool stop(pthread_t thread);
