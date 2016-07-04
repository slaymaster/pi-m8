/**
 * list.c
 * Doubly linked list implementation
 * Thomas Isaksson
 */

#include "list.h"
#include <string.h>

list *list_empty(memFreeFunc *f) {

    list *l = malloc(sizeof(list));
    l->front = malloc(sizeof(node));
    l->front->data = NULL;
    l->front->next = NULL;
    l->length = 0;
    l->freeFunc = f;

    return l;
}

list_position list_front(list *l) {  
     return l->front;
}

bool list_isEmpty(list *l) {
    bool res = l->length == 0;
    return res;

}

bool list_isEnd(list *l, list_position lp) {
    pthread_mutex_lock(&list_lock);
    bool res = (lp->next == NULL);
    pthread_mutex_unlock(&list_lock);
    return res;
}

list_position list_next(list *l, list_position lp) {
    pthread_mutex_lock(&list_lock);
    list_position lp_res = lp->next;
    pthread_mutex_unlock(&list_lock);

    return lp_res;
}   

list_position list_add(list *l, DATA_TYPE *d, list_position lp) {
    pthread_mutex_lock(&list_lock);
    list_position i = malloc(sizeof(node));

    i->data = d;

    if (lp->next == NULL) {
        i->next = NULL;
        i->prev = lp;
        lp->next = i;
    } else {
        i->next = lp->next;
        lp->next = i;
        i->prev = lp;
    }

    
    l->length++;
    pthread_mutex_unlock(&list_lock);
    return i;

}


list_position list_add_front(list *l, DATA_TYPE *d) {
    pthread_mutex_lock(&list_lock);
    list_position i = malloc(sizeof(node));
    i->data = d;

    if (l->front->next == NULL) {
        l->front->next = i;
        i->prev = NULL;
        i->next = NULL;
    } else {
        i->next = l->front->next;
        i->next->prev = i;
        i->prev = NULL;
        l->front->next = i;
    }

    l->length++;
    pthread_mutex_unlock(&list_lock);
    return i;


}

// REMOVES FIRST INSTANCE OF OBJECT d
void list_remove_obj(list *l, DATA_TYPE *d) {
    pthread_mutex_lock(&list_lock);
    for(node * lp = l->front; lp != NULL; lp = lp->next) {
        if (lp->data == d) {
            list_remove_pos(l, lp);
            printf("DEBUG: Found and removed object\n");
            break;
        }
    }
    pthread_mutex_unlock(&list_lock);
}

list_position list_get_obj(list *l, DATA_TYPE *d) {
    pthread_mutex_lock(&list_lock);
    for(node * lp = l->front; lp != NULL; lp = lp->next) {
        if (lp->data == d) {
            list_position llp = lp;
            pthread_mutex_unlock(&list_lock);
            return llp;
        }
    }
    pthread_mutex_unlock(&list_lock);
    return NULL;

}

void list_remove_pos(list *l, list_position lp) {

    if (lp->next == NULL && lp->prev == NULL) {
        // final object in list, removing this will empty
        l->front->next = NULL;
    } else if (lp->next == NULL && lp->prev != NULL) {
        // tail object
        lp->prev->next = NULL;
    } else if (lp->next != NULL && lp->prev == NULL) {
        // head object
        l->front->next = lp->next;
    } else if (lp->next != NULL && lp->prev != NULL) {
        lp->next->prev = lp->prev;
        lp->prev->next = lp->next;
    }


    l->length--;

    free(lp);

}



void list_free(list *l) {
    list_position lp = list_front(l);
    while (!list_isEnd(l, lp)) {
        lp = list_next(l, lp); 
        list_remove_pos(l, lp); 
    }
    free(l->front);
    free(l);
}
/**queue_length
 * Purpose: To see the length of the queue
 * Parameters: l - a pointer to the queue
 * Returns: The length as an integer
 */
int list_length(list *l) {
    pthread_mutex_lock(&list_lock);
    int lo = l->length;
    pthread_mutex_unlock(&list_lock);
    return lo;

}

