#include "log.h"
#include <stdio.h>

LOGGING_CREATE_CHANNEL(FOO);


int main()
{
    int i;
    for(i=0; i < 20; i++)
    {
        LOGGING_DEBUG_0(FOO, "foo");
        LOGGING_DEBUG_1(FOO, "foo", 1);
        LOGGING_DEBUG_2(FOO, "foo", 2, 3);
    }

    Logging_dump(&FOO);

    return 0; 
}

void Logging_log_callback(int line, int par1, int par2) {

    printf("%d, %d, %d\n", line, par1, par2);
}

