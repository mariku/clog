#include "logging.h"
#include "logging_gen.h"
#include <stdio.h>

void do_foo();
void do_bar();

LOGGING_CREATE_CHANNEL(MAIN);

int main()
{
    Logging_init_all();
    LOGGING_DEBUG_0(MAIN, "+main()");
   // while(1) 
    {
        do_foo(); // create some traffic
        Logging_dump_all();
    }
    printf("Empty dump\n");
    LOGGING_DEBUG_0(MAIN, "-main()");
    Logging_dump_all();
}
