#include "log.h"
#include "bar.h"

LOGGING_CREATE_CHANNEL(FOO);


void do_foo() {
    int i;
    for(i=0; i < 22; i++) {
        LOGGING_DEBUG_1(FOO, "foo", i);
        do_bar();
    }
}
