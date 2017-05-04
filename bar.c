#include "log.h"

LOGGING_CREATE_CHANNEL(BAR);

void do_bar() {
    int i;
    for(i=0; i < 22; i++) {
        LOGGING_DEBUG_1(BAR, "bar", i);
    }
}
