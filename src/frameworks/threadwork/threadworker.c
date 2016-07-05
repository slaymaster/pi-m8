#include <stdio.h>
#include "threadwork.h"

void *threadwork(void *args);


int main(int argc, char *argv[]) {

    memw_init();
    pthread_t threads[10];

    int thread_args[10];

    for (int i = 0; i<10; i++) {
        thread_args[i] = i;
        memw_dblock *block = run(threadwork, &thread_args[i]);
        threads[i] = *(pthread_t*)block->data;
    }
    
    for (int i = 0; i<10; i++) {
        pthread_join(threads[i], NULL);
        printf("MASTER joined thread %d!\n", i);
    } 

    memw_free_all();

    return 0;
}

void *threadwork(void *args) {

    for (int i = 0; i<10; i++) {
        printf("THREAD num %d counts %d\n", *(int*)args, i);
        sleep(1); 
    }

    return NULL;

}
