
/**
 * I Love Jesus <3
 * The Network is the Machine.
 */

#include "machine.h"
#include "transistor.h"
#include "gate.h"

static void test_gate (gate_t *gate);
static void process_transistor (transistor_t *t, int type);
static void process_gate_connection (gate_t *gate, wire_t *w);
static void process_gate (gate_t *gate);

int initialization (void)
{
    // ***
    gate_t *not = create_gate(GATE_NOT);

    not->input1 = 0;
    not->vdd    = 1;
    test_gate(not);

    reset_gate(not);

    not->input1 = 1;
    not->vdd    = 1;
    test_gate(not);

    // ***
    gate_t *nand = create_gate(GATE_NAND);

    nand->input1 = 0;
    nand->input2 = 0;
    nand->vdd    = 1;
    test_gate(nand);

    reset_gate(nand);

    nand->input1 = 1;
    nand->input2 = 0;
    nand->vdd    = 1;
    test_gate(nand);

    reset_gate(nand);

    nand->input1 = 0;
    nand->input2 = 1;
    nand->vdd    = 1;
    test_gate(nand);

    reset_gate(nand);

    nand->input1  = 1;
    nand->input2  = 1;
    nand->vdd     = 1;
    test_gate(nand);

    return 0;
}

static void test_gate (gate_t *gate)
{
    printf("gate type: %s\n", get_gate_name(gate->type));
    printf("\ntransistors:\n");

    for (transistor_t *t=gate->transistors; t != NULL; t=t->next)
        printf("\tid: %d, type: %s, gate: %d, drain: %d, source: %d\n", 
            t->id, !t->type ? "P-TYPE" : "N-TYPE", t->gate, t->drain, t->source);

    printf("\nwires:\n");
    for (wire_t *w=gate->wires; w != NULL; w=w->next) 
        printf("\tinput id: %d, input pin: %d -> output id: %d, output pin: %d\n",
            w->input_id, w->input_pin, w->output_id, w->output_pin);
    

    printf("\nProcess gate transistors...\n");

    process_gate(gate);

    printf("\ntransistors:\n");
    for (transistor_t *t=gate->transistors; t != NULL; t=t->next)
        printf("\tid: %d, type: %s, gate: %d, drain: %d, source: %d\n", 
            t->id, !t->type ? "P-TYPE" : "N-TYPE", t->gate, t->drain, t->source);

    printf("\n%s:\n"
            "\tInput1: %d\n\tInput2: %d\n\tOutput: %d\n"
            "\tVdd...: %d\n\tGround: %d\n",
                get_gate_name(gate->type),
                gate->input1, gate->input2, 
                gate->output, gate->vdd, gate->ground);

    printf("\n+++++++++++++++++++++++++++\n\n");
}

static void process_transistor (transistor_t *t, int type)
{
    switch (type) {
        case TYPE_P:
            if (t->source == 1 && t->gate == 1)
                t->drain = 0;
            else if (t->source == 1 && t->gate == 0)
                t->drain = 1;
            else if (t->source == 0 && t->gate == 0)
                t->drain = 0;
            else if (t->source == 0 && t->gate == 1)
                t->drain = 0;
            break;

        case TYPE_N:
            if (t->gate == 1 && t->drain == 1)
                t->source = 1;
            else if (t->gate == 1 && t->drain == 0)
                t->source = 0;
            else if (t->gate == 0 && t->drain == 1)
                t->source = 0;
            else if (t->gate == 0 && t->drain == 0)
                t->source = 0;
            break;
    }
}

static void process_gate_connection (gate_t *gate, wire_t *w)
{
    for (transistor_t *t=gate->transistors; t != NULL; t=t->next) {
        if (w->output_id == t->id) {
            switch (w->output_pin) {
                case PIN_TRANSISTOR_GATE:
                    t->gate = 1;
                    break;
            }
        }
    }
}

static void process_gate (gate_t *gate)
{
    for (wire_t *w=gate->wires; w != NULL; w=w->next) {

        // O Vdd apenas se conectará em alguma porta de source ou dreno.
        if (w->input_id == GATE_PIN_VDD) {
            if (gate->vdd == 1) {
                for (transistor_t *t=gate->transistors; t != NULL; t=t->next) {
                    if (w->output_id == t->id) {
                        switch (w->output_pin) {
                            case PIN_TRANSISTOR_SOURCE:
                                t->source = 1;
                                break;
                            case PIN_TRANSISTOR_DRAIN:
                                t->drain = 1;
                                break;
                        }
                    }
                }
            }
        }

        // O input sempre se conectará em algum gate.
        else if (w->input_id == GATE_PIN_INPUT1) {
            if (gate->input1 == 1)
                process_gate_connection(gate, w);
        } else if (w->input_id == GATE_PIN_INPUT2) {
            if (gate->input2 == 1)
                process_gate_connection(gate, w);
        }

        // Conexões que partem dos transistores só podem sair do drain ou do source.
        // E conectarem-se no output, ground, ou um gate de algum outro transistor. 
        else {
            for (transistor_t *t=gate->transistors; t != NULL; t=t->next) {
                if (w->input_id == t->id) {
                    switch (w->input_pin) {
                        case PIN_TRANSISTOR_SOURCE:
                            switch (w->output_id) {

                                case GATE_PIN_GROUND:
                                    switch (t->type) {
                                        case TYPE_N:
                                            process_transistor(t, TYPE_N);
                                            gate->ground = t->source;
                                            break;
                                    }
                                    break;

                                default:
                                    switch (t->type) {
                                        case TYPE_N:
                                            process_transistor(t, TYPE_N);
                                     
                                            for (transistor_t *t2=gate->transistors; t2 != NULL; t2=t2->next) {
                                                if (w->output_id == t2->id) {
                                                    switch (t2->type) {
                                                        case TYPE_N:
                                                            t2->drain = t->source;
                                                            break;
                                                    }
                                                }
                                            }
                                            break;
                                    }
                                    break;
                            }
                            break;

                        case PIN_TRANSISTOR_DRAIN:
                            switch (w->output_id) {

                                case GATE_PIN_OUTPUT:
                                    switch (t->type) {
                                        case TYPE_P:
                                            process_transistor(t, TYPE_P);
                                            
                                            if (t->drain)
                                                gate->output = t->drain;
                                            break;
                                            
                                        case TYPE_N:
                                            t->drain = gate->output;
                                            break;
                                    }
                                    break;

                                case GATE_PIN_GROUND: break;
                                default: break;
                            }
                            break;
                    }
                }
            }
        }
    }
}


