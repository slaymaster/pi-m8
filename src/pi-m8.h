#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include "frameworks/memwork/memwork.h"

bool read_cmd(char *cmd_file, char cmd_buf[25]);
bool validate_input(char buf[25]);
void parse(char buf[25]);
