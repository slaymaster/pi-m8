#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <glib.h>

struct block {

    void *data;
    size_t size;
    bool is_freed;
 
} typedef memw_dblock;


extern GList *l;


void memw_init();
memw_dblock *memw_alloc(void *v, size_t s);
bool memw_dealloc(memw_dblock *block);
void memw_free_all();
void memw_destroy();
void _memw_free_data(gpointer data, gpointer user_data);


