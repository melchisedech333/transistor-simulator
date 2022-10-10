
#include "device-arithmetic.h"
#include "gate-construction.h"

static void process_sum (device_arithmetic_t *device);
static half_adder_t *half_adder (int input1, int input2);
static half_adder_t *half_adder_invert (int input1, int input2);
static half_adder_t *create_half_adder (void);

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
    switch (device->operation) {
        case ARITHMETIC_OPERATION_SUM:
            process_sum(device);
            break;
    }
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

static void process_sum (device_arithmetic_t *device)
{
    printf("> %s\n", device->input1);
    printf("> %s\n", device->input2);

    half_adder_t *hf;
    int carry = 0;
    int bit1  = 0;
    int bit2  = 0;

    for (int a=(DEVICE_INPUT_SIZE-1); a>=0; a--) {
        
        // Reset current bit.
        bit1 = bit2 = 0;

        if (device->input1[a] == '1')
            bit1 = 1;
        if (device->input2[a] == '1')
            bit2 = 1;

        // Carry disabled.
        if (carry == 0) {
            hf = half_adder(bit1, bit2);
            carry = hf->carry;
            device->output[a] = hf->output + 48;
            free(hf);
        }

        // Carry enabled.
        else {
            hf = half_adder_invert(bit1, bit2);
            carry = hf->carry;
            device->output[a] = hf->output + 48;
            free(hf);
        }
    }
}

static half_adder_t *half_adder (int input1, int input2)
{
    half_adder_t *hf = create_half_adder();
    gate_t *and = create_gate(GATE_AND);
    gate_t *xor = create_gate(GATE_XOR);

    and->input1 = input1;
    and->input2 = input2;
    xor->input1 = input1;
    xor->input2 = input2;

    run_gate(and);
    run_gate(xor);

    hf->output = xor->output;
    hf->carry  = and->output;

    return hf;
}

static half_adder_t *half_adder_invert (int input1, int input2)
{
    half_adder_t *hf = create_half_adder();
    gate_t *or = create_gate(GATE_OR);
    gate_t *xor = create_gate(GATE_XOR);
    gate_t *not = create_gate(GATE_NOT);

    or->input1  = input1;
    or->input2  = input2;
    xor->input1 = input1;
    xor->input2 = input2;

    run_gate(xor);
    not->input1 = xor->output;
    run_gate(not);
    hf->output = not->output;

    run_gate(or);
    hf->carry = or->output;

    return hf;
}

static half_adder_t *create_half_adder (void)
{
    half_adder_t *hf = (half_adder_t *) malloc(sizeof(half_adder_t));
    
    if (!hf) {
        printf("Error alloc memory.\n");
        exit(-1);
    }

    memset(hf, 0, sizeof(half_adder_t));
    
    hf->output = 0;
    hf->carry = 0;

    return hf;
}


