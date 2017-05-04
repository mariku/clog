#include "log.h"
#include <stdio.h>

LOGGING_CREATE_CHANNEL(FOO);


int main() {
    int i;
    for(i=0; i < 22; i++) {
//       LOGGING_DEBUG_0(FOO, "foo");
        LOGGING_DEBUG_1(FOO, "foo", i);
//        LOGGING_DEBUG_2(FOO, "foo", 2, 3);
    }

    Logging_dump(&FOO);
    printf("Empty dump\n");
    Logging_dump(&FOO);

    for(i=0; i < 10; i++) {
//       LOGGING_DEBUG_0(FOO, "foo");
        LOGGING_DEBUG_1(FOO, "foo", i);
//        LOGGING_DEBUG_2(FOO, "foo", 2, 3);
    }

    Logging_dump(&FOO);
    printf("Empty dump\n");
    Logging_dump(&FOO);

    return 0; 
}

void Logging_log_callback(int line, int par1, int par2) {
    printf("log: %d, %d, %d\n", line, par1, par2);
}

void Logging_lost_callback(LogChannel* channel, int lost) {
    printf("Messages lost: %d\n", lost);
}
