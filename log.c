#include "log.h"

void Logging_init(LogChannel* channel) {
    channel->read = 0;
    channel->write = 0;
}

void Logging_log(LogChannel* channel, int line, 
                 int par1, int par2) {

    LogMessage* m = &channel->messages[channel->write];
    m->line = line;
    m->par1 = par1;
    m->par2 = par2;

    if(channel->write >= NUMBER_OF_MESSAGES) {
        channel->write = 0;
    }
    else {
        channel->write++;
        channel->read++;
    }
}


void Logging_dump(LogChannel* channel) {
    int i;
    LogMessage* m;
    for(i=0; i < channel->read; i++) {
        m = &channel->messages[i];
        Logging_log_callback(m->line, m->par1, m->par2);
    }
    channel->read = 0;
}
