
#ifndef _H_DEVICE_ARITHMETIC_
#define _H_DEVICE_ARITHMETIC_

#include "headers.h"

#define ARITHMETIC_INPUT1           1
#define ARITHMETIC_INPUT2           2

// Operations support.
#define ARITHMETIC_OPERATION_SUM    1

/**
 * Deve existir um bit a mais no output, pois o 
 * carry (vai 1) as vezes ocupa esse bit.
 * 
 *  000000000 -> input1
 *  000000000 -> input2
 * 0000000000 -> output (+ final carry)
 */

#define DEVICE_INPUT_SIZE           9
#define DEVICE_OUTPUT_SIZE         10

typedef struct device_arithmetic_s {
    char input1 [DEVICE_INPUT_SIZE  + 1]; // '\0' para string.
    char input2 [DEVICE_INPUT_SIZE  + 1];
    char output [DEVICE_OUTPUT_SIZE + 1];

    int operation;
} device_arithmetic_t;

device_arithmetic_t *create_device_arithmetic (void);
void device_arithmetic_set_data (device_arithmetic_t *device, int input, char *data);
void device_arithmetic_set_operation (device_arithmetic_t *device, int op);
void device_arithmetic_reset (device_arithmetic_t *device);
void run_device_arithmetic (device_arithmetic_t *device);
char *get_operation_name (int op);
char get_operation_op (int op);

#endif


