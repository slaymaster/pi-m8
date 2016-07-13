#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <glib.h>
#include "frameworks/memwork/memwork.h"

extern GSList *cmd_stack;

bool read_cmd(char *cmd_file, char cmd_buf[25]);
bool validate_input(char buf[25]);
void parse(char buf[25]);
void clear_buf(char buf[25]);
bool e_cmd(char buf[25]);
void *f_cmd();
void d_cmd();
bool ie_cmd();
