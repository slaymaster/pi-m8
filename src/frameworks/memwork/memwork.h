#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <glib.h>

/*
 * Memwork 1.0
 * written by Slaymaster
 * Memwork is a memory management framework written for
 * my own applications. The syntax is rather clumsy however
 * in the end the sacrificed readability is made up for by
 * the added functionality. You'll never have forgotten to free again!
 */


/*
 * The main block structure. It is perfectly fine
 * to directly manipulate struct members.
 */
struct block {

    void *data;
    size_t size;
    bool is_freed;
 
} typedef memw_dblock;

/*
 * A global GList (see GLib) that keeps track of all allocs
 */
extern GList *l;

/*
 * Initiates the framework. Not needed really.
 */
void memw_init();

/*
 * Purpose: Allocates an object
 * Params: v - the object, s - the size of it
 * Returns: A block containing the object
 */
memw_dblock *memw_alloc(void *v, size_t s);

/*
 * Purpose: Deallocates an object
 * Params: block - the object to deallocate
 * Returns: if the deallocation succeeded
 */
bool memw_dealloc(memw_dblock *block);

/*
 * Purpose: Frees EVERYTHING allocated using memwork
 */
void memw_free_all();

/*
 * Purpose: Same as above
 */
void memw_destroy();

/*
 * Purpose: Internal function to free data of a single list object
 * Params: data - the date, user_data - needed to match GLib syntax
 */
void _memw_free_data(gpointer data, gpointer user_data);


