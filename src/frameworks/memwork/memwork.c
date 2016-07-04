#include "memwork.h"


GList *l;


void memw_init() {

    l = NULL;

}

memw_dblock *memw_alloc(void *v, size_t s) {

    //TODO

    memw_dblock *b = malloc(sizeof(memw_dblock));

    b->data = malloc(s);

    memcpy(b->data, v, s);

    b->size = s;
    b->is_freed = false;


    l = g_list_insert(l, b, g_list_position(l, g_list_first(l)));

    return b;
}


bool memw_dealloc(memw_dblock *block) {

    //TODO


    free(block->data);
    l = g_list_remove(l, block);
    free(block);

    return false;
}

void memw_free_all() {


    // loop glist and free all data struct memebers
    g_list_foreach(l, _memw_free_data, NULL);

    g_list_free_full(l, free);


}

void _memw_free_data(gpointer data, gpointer user_data) {

    memw_dblock *m = data;
    free(m->data);

}

void memw_destroy() {
    memw_free_all();

}
