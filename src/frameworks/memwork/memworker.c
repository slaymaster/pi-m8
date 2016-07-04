#include "memwork.h"




int main(int argc, char *argv[]) {



    memw_init();


    int r = 5;
    memw_dblock *int_i = memw_alloc(&r, sizeof(int));


    printf("our value is %d", *(int*)int_i->data);



    memw_destroy();





    return 0;
}
