#include <stdio.h>
#include <time.h>

enum level {
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    CRITICAL,
};

int createLog() { // TODO: renvoyer le nom du fichier log + date heure minute seconde
    FILE* file = fopen("latest.log", "w");
    if (file == NULL) {
        return -1;
    }
    fclose(file);
    return 0;
}

int logMessage(char* filename, int level, char* message) {
    
    char instant[51];
    char niveau[10];
    
    
    time_t t = time(NULL);
    tzset();

    strftime(instant, sizeof(instant) - 1, "%a %b %d %T %Z %Y", localtime(&t));
    
    FILE* file = fopen("latest.log", "a");
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
