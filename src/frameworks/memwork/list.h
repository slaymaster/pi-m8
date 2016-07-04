/**
 *  queue.h
 *  queue fronter for double linked list.
 **/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

#ifndef DATA_TYPE
#define DATA_TYPE void
#endif

typedef void *data;
typedef void memFreeFunc(data);

#define list_for_each(item, list) \
    for(node * item = list_front(list); item != NULL && item->data != NULL; item = list_next(list, item))

typedef struct link {
   DATA_TYPE *data;
   struct link* next;
   struct link* prev;
} node;

typedef node *list_position;

typedef struct list {
    node *front;
    node *rear;
    memFreeFunc *freeFunc;
	int length;
} list;


pthread_mutex_t list_lock;

list *list_empty(memFreeFunc *f);
list_position list_front(list *l);
bool list_isEmpty(list *l);
list_position list_add(list *l, DATA_TYPE *d, list_position lp);
void list_remove_pos(list *l, list_position lp);
void list_remove_obj(list *l, DATA_TYPE *d);
void list_free(list *l);
int list_length(list *l);
list_position list_next(list *l, list_position lp);
bool list_isEnd(list *l, list_position lp);
list_position list_first(list *l);
list_position list_get_obj(list *l, DATA_TYPE *d);
list_position list_add_front(list *l, DATA_TYPE *d);
