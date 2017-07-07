#include <stdio.h>

void Logging_log_callback(int id, int line, int par1, int par2) {
    printf("%d,%d,%d,%d\n", id, line, par1, par2);
}

void Logging_lost_callback(int channel_id, int lost) {
    printf("0,0,%d,%d\n", channel_id, lost);
}
