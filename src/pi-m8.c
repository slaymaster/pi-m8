#include "pi-m8.h"

GSList *cmd_stack = NULL;
bool cmd_reader;
bool cmd_parser;
bool updater_running;

int main(int argc, char *argv[]) {

    if (argc < 2) {
        exit(0);
    }

    // needed frameworks:
    // memory-framework
    // thread-framework
    // file-framework

    // initiate internal modules
        // initiate signal handler
    if(!init_sighant()) {
        // could not initiate sighant, kill everything
        printf("Coudln't init sighant--exiting\n");
        exit(1);
    }

        // initiate controlbools
    cmd_parser = true;
    updater_running = true;

    // initiate modules
        // initiate commandfile
    char *cmd_file = argv[1];
    char cmd_buf[25];
    clear_buf(cmd_buf);
        // initiate secretary
    init_log();

    // load streams
    
    // launch worker threads
        // launch command reader
            // create arr containing cmd_pipe and cmd_buf
            // first index in arr is length of cmd_len, cmd_buf is always 25
    char args[strlen(cmd_file)+25+1];
    args[0] = strlen(cmd_file);
    memcpy(&args[1], cmd_file, strlen(cmd_file));
    memcpy(&args[strlen(cmd_file)+1], cmd_buf, 25);
    cmd_reader = true; 
    memw_dblock *cmd_r_thread = run(read_pipe, args);
    printf("MASTER: Dispatched cmd_reader!\n");
    
        // launch updater
    memw_dblock *updater_r_thread = run(updater, NULL);
    printf("MASTER: Dispatched updater!\n");

    // go into standby

    while (cmd_parser) {
        // read command log
        printf("reading command log\n");
        if (!ie_cmd()) {
            char *c = (char*)f_cmd();
            printf("read: ");
            fwrite(c, sizeof(char), 25, stdout);
            printf("\n");
            char fs[32];
            sprintf(fs, "Received command: %s", c);
            log_event(EVENT_GENERAL, fs);
        }
        // sleep
        sleep(1);
    }

    pthread_join(*(pthread_t*)cmd_r_thread->data, NULL);
    pthread_join(*(pthread_t*)updater_r_thread->data, NULL);
    memw_free_all();
    return 0;
}

bool init_sighant() {
    struct sigaction sa;
    sa.sa_handler = sighandler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART; 
    if (sigaction(SIGINT, &sa, NULL) == -1)
        return false;
    return true;

}
void sighandler(int signum) {
    if (signum == SIGINT) {
        printf("Caught SIGINT--EXITING\n");
        cmd_reader = false;
        cmd_parser = false;
        updater_running = false;
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

void *read_pipe(void *args) {
    //printf("THREAD: cmd_reader started!\n");

    // deconstruct args
    char *argu = (char *)args;
    int cmd_f_l = (int)argu[0];
    //printf("THREAD: args desconstructed\n");

    //char cmd_pipe[cmd_f_l] = argu[1];
    char *cmd_pipe = &argu[1];
    memw_dblock *m_cmd_pipe = memw_alloc(cmd_pipe, sizeof(char)*(argu[1]+1));
    //printf("THREAD: more args desconstructed\n");

    cmd_pipe = m_cmd_pipe->data;
    memcpy(cmd_pipe, &argu[1], cmd_f_l);
   
    cmd_pipe[cmd_f_l] = '\0';
    char cmd_buf[25];
    memcpy(cmd_buf, &argu[cmd_f_l+1], 25);
   
    //printf("THREAD: attempting to pipe %s, with len %d\n", cmd_pipe, cmd_f_l);
    int fd;

    fd = open(cmd_pipe, O_RDONLY | O_NONBLOCK);
    //printf("THREAD: opened pipe\n");
    if (fd == -1) {
        return NULL;
    }

    while (cmd_reader) { 
        read(fd, cmd_buf, 25);
   
        if (validate_input(cmd_buf)) {
            //printf("THREAD: found legit cmd\n");
            e_cmd(cmd_buf);
        }
        clear_buf(cmd_buf);
    }

    close(fd);
    return NULL;
}
void *updater(void *args) {

    while (updater_running) {
        synchronise(NULL);
        sleep(5);
    }
    return NULL;
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
bool e_cmd(char *buf) {
    memw_dblock *data = memw_alloc(buf, (sizeof(char)*26));
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

