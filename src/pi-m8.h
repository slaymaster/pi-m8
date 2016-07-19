#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <glib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include "modules/secretary/secretary.h"

#ifndef MEMWORK_H
#define MEMWORK_H
#include "frameworks/memwork/memwork.h"
#endif

#ifndef THREADWORK_H
#define THREADWORK_H
#include "frameworks/threadwork/threadwork.h"
#endif

#define NUM_THREADS 2
#define CMD_THREAD 0
#define UPDATE_THREAD 1

extern GSList *cmd_stack;
extern GHashTable *thread_table;

bool init_sighant();
void sighandler(int signum);
bool read_cmd(char *cmd_file, char cmd_buf[25]);
void *read_pipe(void *args);
bool validate_input(char buf[25]);
void parse(char buf[25]);
void clear_buf(char buf[25]);
bool e_cmd(char *buf);
void *f_cmd();
void d_cmd();
bool ie_cmd();
void *updater(void *args);
void constr_id();
