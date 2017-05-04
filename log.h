#ifndef LOGGING_H
#define LOGGING_H

#include "log_cfg.h"

#if LOGGING == ENABLED

typedef enum {
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARN,
    LOG_LEVEL_ERROR,
}LogLevel;

typedef struct {
    int line; 
    int par1;
    int par2;
}LogMessage;

typedef struct {
    LogMessage messages[NUMBER_OF_MESSAGES]; 
    int read;
    int write;
    int count;
}LogChannel;

void Logging_log(LogChannel* channel, int line_number, int par1, int par2);
void Logging_init(LogChannel* channel);

void Logging_log_callback(int line, int par1, int par2);
void Logging_lost_callback(LogChannel* channel, int lost);

void Logging_dump(LogChannel* channel);

/* create channel */
#define LOGGING_CREATE_CHANNEL(name) LogChannel name;

/* DEBUG */
#if LOGGING_LEVEL == LOGGING_DEBUG
#define LOGGING_DEBUG_0(channel, msg) Logging_log(&channel, __LINE__, 0, 0);
#define LOGGING_DEBUG_1(channel, msg, par1) Logging_log(&channel, __LINE__, par1, 0);
#define LOGGING_DEBUG_2(channel, msg, par1, par2) Logging_log(&channel, __LINE__, par1, par2);;
#endif

#elif LOGGING == DUMP
#else
#endif

#endif /* include guard */
