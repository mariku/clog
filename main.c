#include "logging.h"
#include "logging_gen.h"
#include <stdio.h>

void do_foo();
void do_bar();


int main()
{
    Logging_init_all();
    while(1) {
        do_foo(); // create some traffic
        Logging_dump_all();
    }
    printf("Empty dump\n");
    Logging_dump_all();
}
