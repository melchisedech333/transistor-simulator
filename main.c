
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
    gate_t *nand = create_gate(GATE_NAND);

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

    reset_gate(nand);

    nand->input1  = 1;
    nand->input2  = 1;
    nand->vdd     = 1;
    show_gate_information(nand);

    // ***
    gate_t *xor = create_gate(GATE_XOR);
    
    xor->input1 = 1;
    xor->input2 = 1;
    xor->vdd    = 1;
    process_gate(xor);
    show_gate_information(xor);

    // reset_gate(xor);
    // xor->input1 = 0;
    // xor->input2 = 0;
    // xor->vdd    = 1;
    // process_gate(xor);
    // show_gate_information(xor);

    // reset_gate(xor);
    // xor->input1 = 0;
    // xor->input2 = 1;
    // xor->vdd    = 1;
    // process_gate(xor);
    // show_gate_information(xor);

    // reset_gate(xor);
    // xor->input1 = 1;
    // xor->input2 = 0;
    // xor->vdd    = 1;
    // process_gate(xor);
    // show_gate_information(xor);

    return 0;
}


