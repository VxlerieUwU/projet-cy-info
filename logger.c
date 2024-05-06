#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <errno.h>

#define FILENAME "latest.log"

/*
 * copyright cy-chomâge valérie 2024
*/

enum level {
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    CRITICAL,
};

int createLog() { // TODO: renvoyer le nom du fichier log + date heure minute seconde
    FILE* file = fopen(FILENAME, "w");
    if (file == NULL) {
        return -1;
    }
    
    fclose(file);
    return 0;
}

int logMessage(int level, char* message) {
    char instant[51];
    char niveau[10];
    
    
    time_t t = time(NULL);
    tzset();

    strftime(instant, sizeof(instant) - 1, "%a %b %d %T %Z %Y", localtime(&t));
    
    FILE* file = fopen(FILENAME, "a");
    if(file == NULL) {
        return -1;
    }
    switch(level) {
        case DEBUG:
            sprintf(niveau, "DEBUG");
            break;
        case INFO:
            sprintf(niveau, "INFO");
            break;
        case WARNING:
            sprintf(niveau, "WARNING");
            break;
        case ERROR:
            sprintf(niveau, "ERROR");
            break;
        case CRITICAL:
            sprintf(niveau, "CRITICAL");
            break;
        default:
            sprintf(niveau, "UNKNOWN");
            break;
    }

    fprintf(file, "[%s] %s %s\n", instant, niveau, message);
    fclose(file);
    return 0;
}

int moveLog() {
    char name[50];
    unsigned short int r;


    time_t t = time(NULL);
    tzset();

    strftime(name, sizeof(name) - 1, "%d/%m/%Y-%H:%M:%S.log", localtime(&t));
    logMessage(DEBUG, "deinit log");

    r = rename(FILENAME, name);
    if(r != 0) {
        return -1;
    }

    return 0;
}