#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <ctype.h>

#ifndef MEMWORK_H
#define MEMWORK_H
#include "../../frameworks/memwork/memwork.h"
#endif

#ifndef THREADWORK_H
#define THREADWORK_H
#include "../../frameworks/threadwork/threadwork.h"
#endif

#define LOG_NAME "log.txt"
#define CFG_NAME "config"
#define EVENT_CREATELOG 0
#define EVENT_CREATECFG 1
#define EVENT_ERROR 2
#define EVENT_SYNC 3
#define EVENT_OPENLOG 4
#define EVENT_CLOSELOG 5
#define EVENT_LOADCFG 6
#define EVENT_SAVECFG 7
#define EVENT_GENERAL 8
#define EVENT_STARTUP 9

extern int log_num;

void init_log();
void log_event(int event_type, char *event);
void create_log();
void synchronise(void *args);
