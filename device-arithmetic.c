
#include "device-arithmetic.h"

device_arithmetic_t *create_device_arithmetic (void)
{
    device_arithmetic_t *device = (device_arithmetic_t *) malloc(sizeof(device_arithmetic_t));

    if (!device) {
        printf("Error alloc memory.\n");
        exit(-1);
    }

    memset(device, 0, sizeof(device_arithmetic_t));
    memset(device->input1, '0', DEVICE_INPUT_SIZE  + 1);
    memset(device->input2, '0', DEVICE_INPUT_SIZE  + 1);
    memset(device->output, '0', DEVICE_OUTPUT_SIZE + 1);
    
    device->input1[DEVICE_INPUT_SIZE]  = '\0';
    device->input2[DEVICE_INPUT_SIZE]  = '\0';
    device->output[DEVICE_OUTPUT_SIZE] = '\0';

    return device;
}

void device_arithmetic_set_data (device_arithmetic_t *device, int input, char *data)
{
    int a, size;

    switch (input) {
        case ARITHMETIC_INPUT1:
        case ARITHMETIC_INPUT2:
            if (strlen(data) > DEVICE_INPUT_SIZE) {
                printf("Error input data (arithmetic device).\n");
                exit(0);
            }

            for (int a=0; data[a]!='\0'; a++) {
                if (data[a] != '0' && data[a] != '1') {
                    printf("Error input data (arithmetic device).\n");
                    exit(0);
                }
            }
            break;
    }

    switch (input) {
        case ARITHMETIC_INPUT1:
            memset(device->input1, '0', DEVICE_INPUT_SIZE  + 1);
            device->input1[DEVICE_INPUT_SIZE] = '\0';

            size = strlen(data) - 1;
            a = (DEVICE_INPUT_SIZE-1) - size;

            for (int b=0; device->input1[a]!='\0'; a++, b++) 
                device->input1[a] = data[b];
            break;

        case ARITHMETIC_INPUT2:
            memset(device->input2, '0', DEVICE_INPUT_SIZE  + 1);
            device->input2[DEVICE_INPUT_SIZE] = '\0';

            size = strlen(data) - 1;
            a = (DEVICE_INPUT_SIZE-1) - size;

            for (int b=0; device->input2[a]!='\0'; a++, b++) 
                device->input2[a] = data[b];
            break;
    }
}

void device_arithmetic_set_operation (device_arithmetic_t *device, int op)
{
    device->operation = ARITHMETIC_OPERATION_SUM;
}

void device_arithmetic_reset (device_arithmetic_t *device)
{
    device->operation = 0;

    memset(device->input1, '0', DEVICE_INPUT_SIZE  + 1);
    memset(device->input2, '0', DEVICE_INPUT_SIZE  + 1);
    memset(device->output, '0', DEVICE_OUTPUT_SIZE + 1);
    
    device->input1[DEVICE_INPUT_SIZE]  = '\0';
    device->input2[DEVICE_INPUT_SIZE]  = '\0';
    device->output[DEVICE_OUTPUT_SIZE] = '\0';
}

void run_device_arithmetic (device_arithmetic_t *device)
{
    
}

char *get_operation_name (int op)
{
    char *strs []= {
        "Iesus Hominum Salvator <3",
        "SUM (+)",
        NULL
    };

    return strs[op];
}

char get_operation_op (int op)
{
    char str[]= "J+";

    return str[op];
}


