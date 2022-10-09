
#include "headers.h"
#include "machine.h"

int initialization (void)
{
    // // ***
    gate_t *not = create_gate(GATE_NOT);

    not->input1 = 0;
    run_gate(not);

    reset_gate(not);
    not->input1 = 1;
    run_gate(not);

    // // ***
    gate_t *nand = create_gate(GATE_NAND);

    nand->input1 = 0;
    nand->input2 = 0;
    run_gate(nand);

    reset_gate(nand);
    nand->input1 = 1;
    nand->input2 = 0;
    run_gate(nand);

    reset_gate(nand);
    nand->input1 = 0;
    nand->input2 = 1;
    run_gate(nand);

    reset_gate(nand);
    nand->input1  = 1;
    nand->input2  = 1;
    run_gate(nand);

    // ***
    gate_t *xor = create_gate(GATE_XOR);
    
    xor->input1 = 1;
    xor->input2 = 1;
    run_gate(xor);

    reset_gate(xor);
    xor->input1 = 0;
    xor->input2 = 0;
    run_gate(xor);

    reset_gate(xor);
    xor->input1 = 0;
    xor->input2 = 1;
    run_gate(xor);

    reset_gate(xor);
    xor->input1 = 1;
    xor->input2 = 0;
    run_gate(xor);

    return 0;
}


