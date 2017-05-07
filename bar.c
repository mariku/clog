#include "logging.h"

LOGGING_CREATE_CHANNEL(BAR);

void do_bar() {
    int i;
    LOGGING_DEBUG_0(BAR, "+bar");
    for(i=0; i < 7; i++) {
        LOGGING_DEBUG_2(BAR, "bar: i: {}, i*2: {}", i, i * 2);
    }
    LOGGING_DEBUG_0(BAR, "-bar"); 
}
