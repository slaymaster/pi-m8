#include "secretary.h"

int log_num = 0;
bool cfg_exists;

// creates the log if not already present
void init_log() {

    // check if settings file exists, if not init settings
    if (access(CFG_NAME, R_OK|W_OK) != -1) {
        // file exists
        // load config values
        cfg_exists = true;
        FILE *f = fopen(CFG_NAME, "r");
        if (f != NULL) {
            char cfg_val[10];
            if (fgets(cfg_val, 10, f) == NULL) {
                // failedA
                printf("Config file exists but was empty\n");
                //log_event(EVENT_ERROR, "Config file exists but was empty?");
            } else {
                // succeded
                // log succesful opening
                //log_event(EVENT_LOADCFG, "Successfully loaded config");
                printf("Successfully loaded config\n");
                char *ptr;
                int ret = 0;
                ret = strtol(cfg_val, &ptr, 10);
                if (ret != 0) {
                    log_num = ret + (log_num==0 ? log_num+1: log_num);
                    //log_event(EVENT_LOADCFG, "Successfully loaded config");
                } else {
                    //log_event(EVENT_ERROR, "Log_num loaded was not a digit");
                    printf("Log_num loaded was not a digit\n");
                }    
            }
        } else {
            // couldn't open
            printf("Could not load config\n");
            log_event(EVENT_ERROR, "Could not load config 0");
        }
        rewind(f);
        fclose(f);
    } else {
        // settings file does not exist
        // it will be created on next sync
        //log_event(EVENT_GENERAL, "No config file found, it will be created on next sync");
        printf("No config file found, it will be created on next sync\n");
        cfg_exists = false;
    }

    // append creation info machine, date, and unique key
    // time/date
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char datetime[64];
    strftime(datetime, sizeof(datetime), "%c", tm);
    // uname
    struct utsname unameData;
    uname(&unameData);
    char uname[strlen(unameData.sysname) + strlen(unameData.version)
    + strlen(unameData.release)];
    sprintf(uname, "%s %s %s", unameData.sysname, unameData.release, unameData.nodename);

    // key
    char *key = "12345abcde";
    char buf[100];
    sprintf(buf, "Pi-m8 started on %s, on %s with key %s", datetime, uname, key);


    // check if log file exists
    if (access(LOG_NAME, R_OK|W_OK) != -1) {
        // file exists
        log_event(EVENT_STARTUP, buf);
        log_event(EVENT_GENERAL, "Previous log found, resuming..");
    } else {
        // create it
        create_log();
        log_event(EVENT_STARTUP, buf);
    }

}

void create_log() {
    // log does not exist
    // create it
    FILE *f = fopen(LOG_NAME, "a");

    // append creation info machine, date, and unique key
    // time/date
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char datetime[64];
    strftime(datetime, sizeof(datetime), "%c", tm);

    char buf[100];
    sprintf(buf, "Log created on %s", datetime);
    log_event(EVENT_CREATELOG, buf);


    fclose(f);
}

void log_event(int event_type, char *event) {

    FILE *f = fopen(LOG_NAME, "a");


    char date[100];
    time_t now = time(NULL);
    struct tm *t = localtime(&now);


    strftime(date, sizeof(date)-1, "%d%m%Y%H%M", t);

    switch (event_type) {
        case EVENT_CREATELOG:
            fprintf(f, "[%d][%s] %s\n", log_num++, date, event);
            break;
        default:
            fprintf(f, "[%d][%s] %s\n", log_num++, date, event);
            break;

    }


    fclose(f);

}

void synchronise(void *args) {
    // store payload to binary 
    
    // synchronise settings
    FILE *fp = fopen(CFG_NAME, "w");
    if (fp != NULL) {
        fprintf(fp, "%d", log_num);
        log_event(EVENT_SYNC, "Synchronising");
        rewind(fp);
        fclose(fp);
    } else {
        log_event(EVENT_ERROR, "Could not open sync cfg, failed to open cfgfile");
    }

}
