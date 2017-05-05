#include "logging.h"
#include <stdio.h>

void do_foo();
void do_bar();

extern LogChannel FOO;
extern LogChannel BAR;

void Logging_dump_all() {
    Logging_dump(&FOO);
    Logging_dump(&BAR);
}

void Logging_init_all() {
    Logging_init(&FOO, 1);
    Logging_init(&BAR, 2);
}

int main()
{
    Logging_init_all();
    do_foo();
    Logging_dump_all();
    printf("Empty dump\n");
    Logging_dump_all();
}

void Logging_log_callback(int id, int line, int par1, int par2) {
    printf("%d,%d,%d,%d\n", id, line, par1, par2);
}

void Logging_lost_callback(int channel_id, int lost) {
    printf("0,0,%d,%d\n", channel_id, lost);
}
