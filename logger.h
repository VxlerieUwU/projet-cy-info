#ifndef LOGGER_H_   /* Include guard */
#define LOGGER_H_

enum level {
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    CRITICAL,
};

int createLog();

int logMessage(int level, char* message);

int moveLog();

void clearBuf(char * buf);

#endif 