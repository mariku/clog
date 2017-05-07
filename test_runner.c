
#include <stdio.h>
#include "unittest.h"

/* test functions declarations */
char* test_read_empty(void);
char* test_read_full(void);
char* test_read_1_element(void);
char* test_read_2_element(void);
char* test_read_n_minus_1_element(void);
char* test_read_n_minus_2_element(void);
char* test_write_n_minus_1(void);
char* test_write_full(void);
char* test_write_empty(void);


extern int test_run = 0;

/* execute all tests */
static char * all_tests() {
    char* msg;

    printf("starting test test_read_empty\n");
    test_run++;
    msg = test_read_empty();
    if(msg) {
        printf("finished test test_read_empty FAILED\n");
        return msg;
    }
    else{
        printf("finished test test_read_empty SUCCEDED\n");
    }

    printf("starting test test_read_full\n");
    test_run++;
    msg = test_read_full();
    if(msg) {
        printf("finished test test_read_full FAILED\n");
        return msg;
    }
    else{
        printf("finished test test_read_full SUCCEDED\n");
    }

    printf("starting test test_read_1_element\n");
    test_run++;
    msg = test_read_1_element();
    if(msg) {
        printf("finished test test_read_1_element FAILED\n");
        return msg;
    }
    else{
        printf("finished test test_read_1_element SUCCEDED\n");
    }

    printf("starting test test_read_2_element\n");
    test_run++;
    msg = test_read_2_element();
    if(msg) {
        printf("finished test test_read_2_element FAILED\n");
        return msg;
    }
    else{
        printf("finished test test_read_2_element SUCCEDED\n");
    }

    printf("starting test test_read_n_minus_1_element\n");
    test_run++;
    msg = test_read_n_minus_1_element();
    if(msg) {
        printf("finished test test_read_n_minus_1_element FAILED\n");
        return msg;
    }
    else{
        printf("finished test test_read_n_minus_1_element SUCCEDED\n");
    }

    printf("starting test test_read_n_minus_2_element\n");
    test_run++;
    msg = test_read_n_minus_2_element();
    if(msg) {
        printf("finished test test_read_n_minus_2_element FAILED\n");
        return msg;
    }
    else{
        printf("finished test test_read_n_minus_2_element SUCCEDED\n");
    }

    printf("starting test test_write_n_minus_1\n");
    test_run++;
    msg = test_write_n_minus_1();
    if(msg) {
        printf("finished test test_write_n_minus_1 FAILED\n");
        return msg;
    }
    else{
        printf("finished test test_write_n_minus_1 SUCCEDED\n");
    }

    printf("starting test test_write_full\n");
    test_run++;
    msg = test_write_full();
    if(msg) {
        printf("finished test test_write_full FAILED\n");
        return msg;
    }
    else{
        printf("finished test test_write_full SUCCEDED\n");
    }

    printf("starting test test_write_empty\n");
    test_run++;
    msg = test_write_empty();
    if(msg) {
        printf("finished test test_write_empty FAILED\n");
        return msg;
    }
    else{
        printf("finished test test_write_empty SUCCEDED\n");
    }

    return 0;
}

/* main */
int main(int argc, char **argv) {
    char *result = all_tests();
    if (result != 0) {
        printf("%s\n", result);
    }
    else {
        printf("ALL TESTS PASSED\n");
    }
    return result != 0;
    printf("Tests run: %d\n", test_run);
}