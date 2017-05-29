#include "unittest.h"
#include "logging.h"

/*****************************************************************************/
char* test_test____________test() {
    LogChannel c;

    return "test failed\n";
}

char* test_read_empty() {
    LogChannel c;


    return 0;
}

/*****************************************************************************/

char* test_read_full() {
    return 0;
}

/*****************************************************************************/

char* test_read_1_element() {
    return 0;
}

/*****************************************************************************/

char* test_read_2_element() {
    return 0;
}

/*****************************************************************************/

char* test_read_n_minus_1_element() {
    return 0;
}

/*****************************************************************************/

char* test_read_n_minus_2_element() {
    return 0;
}

/*****************************************************************************/

char* test_write_n_minus_1() {
    LogChannel c;
    int i;
    Logging_init(&c, 0);
    /* fill buffer */
    for (i = 0; i < NUMBER_OF_MESSAGES - 1; ++i) {
        Logging_log(&c, 0, 0, 0);
    }
    ut_assert("Invalid read index", c.read == 0);
    ut_assert("Invalid write index", c.write == NUMBER_OF_MESSAGES - 1);
    ut_assert("Invalid count", c.count == NUMBER_OF_MESSAGES - 1);
    return 0;
    return 0;
}

/*****************************************************************************/

char* test_write_full() {
    LogChannel c;
    int i;
    Logging_init(&c, 0);
    /* fill buffer */
    for (i = 0; i < NUMBER_OF_MESSAGES; ++i) {
        Logging_log(&c, 0, 0, 0);
    }
    ut_assert("Invalid read index", c.read == 0);
    ut_assert("Invalid write index", c.write == 0);
    ut_assert("Invalid count", c.count == NUMBER_OF_MESSAGES);
    return 0;
    return 0;
}

/*****************************************************************************/

char* test_write_empty() {
    LogChannel c;
    Logging_init(&c, 0);
    Logging_log(&c, 0, 0, 0);
    ut_assert("Invalid read index", c.read == 0);
    ut_assert("Invalid write index", c.write == 1);
    ut_assert("Invalid count", c.count == 1);
    return 0;
}

/*****************************************************************************/
/* Callbacks */
/*****************************************************************************/

void Logging_log_callback(int channel_id, int line, int par1, int par2) {
}

/*****************************************************************************/

void Logging_lost_callback(int channel_id, int lost) {
}

/*****************************************************************************/
