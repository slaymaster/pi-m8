#include "pi-m8.h"

GSList *cmd_stack;

int main(int argc, char *argv[]) {


    if (argc < 2) {
        exit(0);
    }


    // needed frameworks:
    // memory-framework
    // thread-framework
    // file-framework


    // initiate modules
        // initiate commandfile
    char *cmd_file = argv[1];
    char cmd_buf[25];
    clear_buf(cmd_buf);


    // load streams
    

    // launch worker threads
    

    // go into standby

    while (read_cmd(cmd_file, cmd_buf)) {
        // read command log
        printf("reading command log\n");
        if (!ie_cmd()) {
            char *c = f_cmd();
            printf("read: %s\n", c);
        }
        // sleep
        sleep(1);
    }



}
bool read_cmd(char *cmd_file, char cmd_buf[25]) {
    FILE *fp;
    fp = fopen(cmd_file, "r");

    if (fp != NULL) {
        if (fgets(cmd_buf, 25, fp) == NULL) {
            // could not read string
        }
    } else {
        // could not open file
        return false;
    }

    fclose(fp);
    if (validate_input(cmd_buf)) {
        e_cmd(cmd_buf);
    }
    clear_buf(cmd_buf);

    return true;

}
void clear_buf(char buf[25]) {
    for (int i = 0; i<25; i++) {
        buf[i]= '\n';
    }
}
bool validate_input(char buf[25]) {
    for (int i = 0; i<25; i++) {
       if (buf[i] == '\n') {
            return false;
       } 
    }
    return true;
}
void parse(char buf[25]) {
    // parse input
}
bool e_cmd(char buf[25]) {
    memw_dblock *data = memw_alloc(buf, sizeof(char)*25);
    cmd_stack = g_slist_append(cmd_stack, data);

    return false;
}
void *f_cmd() {
    GSList *head = cmd_stack;
    cmd_stack = g_slist_remove_link(cmd_stack, head);

    memw_dblock *data = head->data;
    g_slist_free_1(head);

    return data->data;
}
void d_cmd() {
    // TODO: destroy command stack
}
bool ie_cmd() {
    return cmd_stack == NULL;
}

