#include "pi-m8.h"


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


    // load streams
    

    // launch worker threads
    

    // go into standby

    while (read_cmd(cmd_file, cmd_buf)) {
        // read command log
        printf("reading command log\n");
        if (cmd_buf != NULL && validate_input(cmd_buf)) {
            printf("read: %s\n", cmd_buf);
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

    return true;

}

bool validate_input(char buf[25]) {

    if (strlen(buf) != 25) {
        return false;
    } else {
        return true;
    }

    return false;
}

void parse(char buf[25]) {

    // parse input


