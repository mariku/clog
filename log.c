#include "log.h"

void Logging_init(LogChannel* channel) {
    channel->read = 0;
    channel->write = 0;
    channel->count = 0;
}

void Logging_log(LogChannel* channel, int line, 
                 int par1, int par2) {

    /* 
       if the buffer is full
       move read cursor to next position 
    */
    if(channel->read == channel->write && channel->count) {
	    channel->read++;
        if(channel->read == NUMBER_OF_MESSAGES) {
            channel->read = 0;
        }
    }

    LogMessage* m = &channel->messages[channel->write];
    m->line = line;
    m->par1 = par1;
    m->par2 = par2;
    channel->write++;

    if(channel->write == NUMBER_OF_MESSAGES) {
        channel->write = 0;
    }
    channel->count++;
}

static int Logging_get_number_of_lost_messsages(LogChannel* channel) {
    int lost;
    if(channel->count > NUMBER_OF_MESSAGES) {
        lost  = channel->count - NUMBER_OF_MESSAGES;
    }
    else {
        lost = 0;
    }
    return lost;
}

static int Logging_get_number_of_messsages(LogChannel* channel) {
    int number_of_messages;
    const int count = channel->count;
    if(count > NUMBER_OF_MESSAGES) {
        number_of_messages  = NUMBER_OF_MESSAGES;
    }
    else {
        number_of_messages = count;
    }
    return number_of_messages;
}

void Logging_dump(LogChannel* channel) {
    int i;
    LogMessage* m;
    int number_of_messages = Logging_get_number_of_messsages(channel);
    int lost = Logging_get_number_of_lost_messsages(channel);

    for(i=0; i < number_of_messages; i++) {
        m = &channel->messages[channel->read];
        channel->read++;
        if(channel->read == NUMBER_OF_MESSAGES) {
            channel->read = 0;
        }
        Logging_log_callback(m->line, m->par1, m->par2);
    }
    channel->read = 0;
    channel->write = 0;
    channel->count = 0;

    if(lost != 0) {
        Logging_lost_callback(channel, lost);
    }
}
