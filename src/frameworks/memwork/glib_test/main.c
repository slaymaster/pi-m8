#include <stdio.h>
#include <stdlib.h>
#include <glib.h>


int main(int argc, char *argv[]) {

    

    GList *li = NULL;


/*
    char *s = malloc(sizeof(char));
    *s = 's';

    char *t = malloc(sizeof(char));
    *t = 'x';
*/

    char t[1];
    t[0] = 'x';
    char s[1];
    s[0] = 's';

    li = g_list_append(li, s);
    li = g_list_append(li, t);


    GList *l = g_list_first(li);
    while (l != NULL) {
        // do stuff
        
        printf("found: %c\n", *(char*)l->data);

        l = g_list_next(l);
    }

    g_list_free(li);


    return 0;
}
