#include <stdio.h>
#include "list.h"


int main (int argc, char *argv[]) {




    list *l = list_empty(free);


    for (int i = 0; i<10; i++) {


        int *v = malloc(sizeof(int));

        *v = i;


        list_add_front(l, v);
 
    
    }




    list_for_each(v, l) {
    

        printf("val, %d\n", *(int*)v);



    }






    return 0;
}
