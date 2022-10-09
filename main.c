
#include "headers.h"
#include "machine.h"

int initialization (void)
{
    // // ***
    // gate_t *not = create_gate(GATE_NOT);

    // not->input1 = 0;
    // not->vdd    = 1;
    // show_gate_information(not);

    // reset_gate(not);

    // not->input1 = 1;
    // not->vdd    = 1;
    // show_gate_information(not);

    // // ***
    // gate_t *nand = create_gate(GATE_NAND);

    // nand->input1 = 0;
    // nand->input2 = 0;
    // nand->vdd    = 1;
    // show_gate_information(nand);

    // reset_gate(nand);

    // nand->input1 = 1;
    // nand->input2 = 0;
    // nand->vdd    = 1;
    // show_gate_information(nand);

    // reset_gate(nand);

    // nand->input1 = 0;
    // nand->input2 = 1;
    // nand->vdd    = 1;
    // show_gate_information(nand);

    // reset_gate(nand);

    // nand->input1  = 1;
    // nand->input2  = 1;
    // nand->vdd     = 1;
    // show_gate_information(nand);

    // ***
    gate_t *xor = create_gate(GATE_XOR);
    xor->input1 = 1;
    xor->input2 = 1;
    xor->vdd    = 1;
    
    printf("\n%s:\n"
            "\tInput1: %d\n\tInput2: %d\n\tOutput: %d\n"
            "\tVdd...: %d\n\tGround: %d\n",
                get_gate_name(xor->type),
                xor->input1, xor->input2, 
                xor->output, xor->vdd, xor->ground);

    process_gate(xor);

    printf("\n%s:\n"
            "\tInput1: %d\n\tInput2: %d\n\tOutput: %d\n"
            "\tVdd...: %d\n\tGround: %d\n",
                get_gate_name(xor->type),
                xor->input1, xor->input2, 
                xor->output, xor->vdd, xor->ground);

    return 0;
}


