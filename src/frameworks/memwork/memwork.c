#include "memwork.h"


GList *l;


void memw_init() {

    l = NULL;

}

memw_dblock *memw_alloc(void *v, size_t s) {

    memw_dblock *b = malloc(sizeof(memw_dblock));
        printf("malloc!\n");
    b->data = malloc(s);
       printf("malloc!\n");
    memcpy(b->data, v, s);
    b->size = s;
    b->is_freed = false;

    l = g_list_insert(l, b, g_list_position(l, g_list_first(l)));

    return b;
}


bool memw_dealloc(memw_dblock *block) {

    free(block->data);
        printf("free!\n");
    l = g_list_remove(l, block);
    free(block);
        printf("free!\n");

    return false;
}

void memw_free_all() {

    // loop glist and free all data struct memebers
    g_list_foreach(l, _memw_free_data, NULL);
    
    printf("free %d times!\n", g_list_length(l));
    g_list_free_full(l, free);


}

void _memw_free_data(gpointer data, gpointer user_data) {

    memw_dblock *m = data;
    free(m->data);
        printf("free!\n");
}

void memw_destroy() {
    memw_free_all();

}
