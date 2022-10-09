
/**
 * I Love Jesus <3
 * The Network is the Machine.
 */

#include "machine.h"
#include "transistor.h"
#include "gate.h"

static void process_transistor (transistor_t *t, int type);
static void process_gate_connection (gate_t *gate, wire_t *w);
static void process_connections (gate_t *gate, wire_t *w, transistor_t *t);
static void process_transistor_source (gate_t *gate, wire_t *w, transistor_t *t);
static void process_transistor_drain (gate_t *gate, wire_t *w, transistor_t *t);
static void process_gate_direct (gate_t *gate);
static void process_gate_elements (gate_t *gate);
static void prepare_subgate_vdd (gate_t *gate);
static void prepare_subgate_input (gate_t *gate);
static void prepare_subgate_ground (gate_t *gate);
static void prepare_gate_connections (gate_t *gate);

void process_gate (gate_t *gate)
{
    if (gate->subgate) 
        process_gate_elements(gate);
    else
        process_gate_direct(gate);
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

static void process_gate_elements (gate_t *gate)
{
    prepare_subgate_vdd(gate);
    prepare_subgate_input(gate);
    prepare_gate_connections(gate);
    prepare_subgate_ground(gate);
}

static void prepare_gate_connections (gate_t *gate)
{
    for (wire_t *w=gate->wires; w != NULL; w=w->next) {
        switch (w->input_id) {
            case GATE_SUB1_OUTPUT: process_gate_direct(gate->sub1); break;
            case GATE_SUB2_OUTPUT: process_gate_direct(gate->sub2); break;
            case GATE_SUB3_OUTPUT: process_gate_direct(gate->sub3); break;
            case GATE_SUB4_OUTPUT: process_gate_direct(gate->sub4); break;
        }

        switch (w->output_id) {
            case GATE_SUB1_INPUT1: attr_transistor_input(gate->sub1->input1); break;
            case GATE_SUB1_INPUT2: attr_transistor_input(gate->sub1->input2); break;
            case GATE_SUB2_INPUT1: attr_transistor_input(gate->sub2->input1); break;
            case GATE_SUB2_INPUT2: attr_transistor_input(gate->sub2->input2); break;
            case GATE_SUB3_INPUT1: attr_transistor_input(gate->sub3->input1); break;
            case GATE_SUB3_INPUT2: attr_transistor_input(gate->sub3->input2); break;
            case GATE_SUB4_INPUT1: attr_transistor_input(gate->sub4->input1); break;
            case GATE_SUB4_INPUT2: attr_transistor_input(gate->sub4->input2); break;
            case GATE_PIN_OUTPUT: attr_transistor_input(gate->output);        break;
        }
    }
}

static void prepare_subgate_ground (gate_t *gate)
{
    for (wire_t *w=gate->wires; w != NULL; w=w->next) {
        switch (w->input_id) {
            case GATE_PIN_GROUND:
                switch (w->output_id) {
                    case GATE_SUB1_GROUND:
                        if (gate->sub1->ground)
                            gate->ground = gate->sub1->ground;
                        break;
                    case GATE_SUB2_GROUND:
                        if (gate->sub2->ground)
                            gate->ground = gate->sub2->ground;
                        break;
                    case GATE_SUB3_GROUND:
                        if (gate->sub3->ground)
                            gate->ground = gate->sub3->ground;
                        break;
                    case GATE_SUB4_GROUND:
                        if (gate->sub4->ground)
                            gate->ground = gate->sub4->ground;
                        break;
                }
                break;
        }
    }
}

static void prepare_subgate_input (gate_t *gate)
{
    for (wire_t *w=gate->wires; w != NULL; w=w->next) {
        if (w->input_id == GATE_PIN_INPUT1 || w->input_id == GATE_PIN_INPUT2) {
            switch (w->output_id) {
                case GATE_SUB1_INPUT1: set_sub(gate->sub1->input1); break;
                case GATE_SUB1_INPUT2: set_sub(gate->sub1->input2); break;
                case GATE_SUB2_INPUT1: set_sub(gate->sub2->input1); break;
                case GATE_SUB2_INPUT2: set_sub(gate->sub2->input2); break;
                case GATE_SUB3_INPUT1: set_sub(gate->sub3->input1); break;
                case GATE_SUB3_INPUT2: set_sub(gate->sub3->input2); break;
                case GATE_SUB4_INPUT1: set_sub(gate->sub4->input1); break;
                case GATE_SUB4_INPUT2: set_sub(gate->sub4->input2); break;
            }
        }
    }
}

static void prepare_subgate_vdd (gate_t *gate)
{
    // O Vdd sempre se conectada com os Vdd dos sub-gates. 

    for (wire_t *w=gate->wires; w != NULL; w=w->next) {        
        if (w->input_id == GATE_PIN_VDD) {
            switch (w->output_id) {
                case GATE_SUB1_VDD:
                    gate->sub1->vdd = gate->vdd;
                    break;
                case GATE_SUB2_VDD:
                    gate->sub2->vdd = gate->vdd;
                    break;
                case GATE_SUB3_VDD:
                    gate->sub3->vdd = gate->vdd;
                    break;
                case GATE_SUB4_VDD:
                    gate->sub4->vdd = gate->vdd;
                    break;
            }
        }
    }
}

static void process_gate_direct (gate_t *gate)
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
                if (w->input_id == t->id)
                   process_connections(gate, w, t);
            }
        }
    }
}

static void process_connections (gate_t *gate, wire_t *w, transistor_t *t)
{
    switch (w->input_pin) {
        case PIN_TRANSISTOR_SOURCE:
            process_transistor_source(gate, w, t);
            break;

        case PIN_TRANSISTOR_DRAIN:
            process_transistor_drain(gate, w, t);
            break;
    }
}

static void process_transistor_source (gate_t *gate, wire_t *w, transistor_t *t)
{
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
}

static void process_transistor_drain (gate_t *gate, wire_t *w, transistor_t *t)
{
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
}


