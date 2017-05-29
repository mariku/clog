
#include <stdio.h>
#include "unittest.h"
#include <stdlib.h>

/* test functions declarations */
char* test_test____________test(void);
char* test_read_empty(void);
char* test_read_full(void);
char* test_read_1_element(void);
char* test_read_2_element(void);
char* test_read_n_minus_1_element(void);
char* test_read_n_minus_2_element(void);
char* test_write_n_minus_1(void);
char* test_write_full(void);
char* test_write_empty(void);


int test_run = 0;

/* execute single test */

static char * run_test(int test_id) {
    char* msg;
    switch(test_id) {

    case 1: {
        printf("test_test____________test ");
        test_run++;
        msg = test_test____________test();
        if(msg) {
            printf("[!!]\n");
            return msg;
        }
        else{
            printf("[ok]\n");
        }
        break;
    }

    case 2: {
        printf("test_read_empty ");
        test_run++;
        msg = test_read_empty();
        if(msg) {
            printf("[!!]\n");
            return msg;
        }
        else{
            printf("[ok]\n");
        }
        break;
    }

    case 3: {
        printf("test_read_full ");
        test_run++;
        msg = test_read_full();
        if(msg) {
            printf("[!!]\n");
            return msg;
        }
        else{
            printf("[ok]\n");
        }
        break;
    }

    case 4: {
        printf("test_read_1_element ");
        test_run++;
        msg = test_read_1_element();
        if(msg) {
            printf("[!!]\n");
            return msg;
        }
        else{
            printf("[ok]\n");
        }
        break;
    }

    case 5: {
        printf("test_read_2_element ");
        test_run++;
        msg = test_read_2_element();
        if(msg) {
            printf("[!!]\n");
            return msg;
        }
        else{
            printf("[ok]\n");
        }
        break;
    }

    case 6: {
        printf("test_read_n_minus_1_element ");
        test_run++;
        msg = test_read_n_minus_1_element();
        if(msg) {
            printf("[!!]\n");
            return msg;
        }
        else{
            printf("[ok]\n");
        }
        break;
    }

    case 7: {
        printf("test_read_n_minus_2_element ");
        test_run++;
        msg = test_read_n_minus_2_element();
        if(msg) {
            printf("[!!]\n");
            return msg;
        }
        else{
            printf("[ok]\n");
        }
        break;
    }

    case 8: {
        printf("test_write_n_minus_1 ");
        test_run++;
        msg = test_write_n_minus_1();
        if(msg) {
            printf("[!!]\n");
            return msg;
        }
        else{
            printf("[ok]\n");
        }
        break;
    }

    case 9: {
        printf("test_write_full ");
        test_run++;
        msg = test_write_full();
        if(msg) {
            printf("[!!]\n");
            return msg;
        }
        else{
            printf("[ok]\n");
        }
        break;
    }

    case 10: {
        printf("test_write_empty ");
        test_run++;
        msg = test_write_empty();
        if(msg) {
            printf("[!!]\n");
            return msg;
        }
        else{
            printf("[ok]\n");
        }
        break;
    }

    default:
        return "Invalid test id";
    }
    return 0;
}

/* execute all tests */
static char * run_all_tests() {
    char* msg;

    msg = run_test(1);
    if(msg) {
        return msg;
    }

    msg = run_test(2);
    if(msg) {
        return msg;
    }

    msg = run_test(3);
    if(msg) {
        return msg;
    }

    msg = run_test(4);
    if(msg) {
        return msg;
    }

    msg = run_test(5);
    if(msg) {
        return msg;
    }

    msg = run_test(6);
    if(msg) {
        return msg;
    }

    msg = run_test(7);
    if(msg) {
        return msg;
    }

    msg = run_test(8);
    if(msg) {
        return msg;
    }

    msg = run_test(9);
    if(msg) {
        return msg;
    }

    msg = run_test(10);
    if(msg) {
        return msg;
    }

    return 0;
}

/* main */
int main(int argc, char **argv) {
    char *result;
    int test_id;
    if(argc > 1) {
        test_id = atoi(argv[1]);
        result = run_test(test_id);
    }
    else{
        result = run_all_tests();
    }
    if (result != 0) {
        printf("%s\n", result);
    }
    return result != 0;
}