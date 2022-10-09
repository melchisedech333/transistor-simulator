
/**
 * I Love Jesus <3
 * The Network is the Machine.
 */

#include "machine.h"
#include "transistor.h"
#include "gate.h"

int initialization (void)
{
    gate_t *gate = create_gate(GATE_NOT);
    
    printf("gate type: %s\n", get_gate_name(gate->type));
    printf("\ntransistors:\n");

    for (transistor_t *t=gate->transistors; t != NULL; t=t->next)
        printf("\tid: %d, type: %s, gate: %d, drain: %d, source: %d\n", 
            t->id, !t->type ? "P-TYPE" : "N-TYPE", t->gate, t->drain, t->source);

    printf("\nwires:\n");
    for (wire_t *w=gate->wires; w != NULL; w=w->next) 
        printf("\tinput id: %d, input pin: %d -> output id: %d, output pin: %d\n",
            w->input_id, w->input_pin, w->output_id, w->output_pin);
    
    /**
     * Run gate.
     */
    printf("\nRun gate...\n");

    if (gate->type == GATE_NOT) {

        // Input data (Volts).
        gate->input1 = 1;
        gate->vdd    = 1;

        for (wire_t *w=gate->wires; w != NULL; w=w->next) {

            // Gate entry point.
            if (w->input_id == GATE_PIN_VDD) {
                switch (w->output_id) {
                    case GATE_PIN_OUTPUT:  break;
                    case GATE_PIN_INPUT1:  break;
                    case GATE_PIN_INPUT2:  break;
                    case GATE_PIN_VDD:     break;
                    case GATE_PIN_GROUND:  break;
                    default:
                        if (gate->vdd == 1) {
                            for (transistor_t *t=gate->transistors; t != NULL; t=t->next) {
                                if (w->output_id == t->id) {
                                    switch (w->output_pin) {
                                        case PIN_TRANSISTOR_GATE:
                                            t->gate = 1;
                                            break;
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
                        break;
                }
            }

            else if (w->input_id == GATE_PIN_INPUT1) {
                if (gate->input1 == 1) {
                    switch (w->output_id) {
                        case GATE_PIN_OUTPUT:  break;
                        case GATE_PIN_INPUT1:  break;
                        case GATE_PIN_INPUT2:  break;
                        case GATE_PIN_VDD:     break;
                        case GATE_PIN_GROUND:  break;
                        default:
                            for (transistor_t *t=gate->transistors; t != NULL; t=t->next) {
                                if (w->output_id == t->id) {
                                    switch (w->output_pin) {
                                        case PIN_TRANSISTOR_GATE:
                                            t->gate = 1;
                                            break;
                                        case PIN_TRANSISTOR_SOURCE:
                                            t->source = 1;
                                            break;
                                        case PIN_TRANSISTOR_DRAIN:
                                            t->drain = 1;
                                            break;
                                    }
                                }
                            }
                            break;
                    }
                }
            }

            else {
                for (transistor_t *t=gate->transistors; t != NULL; t=t->next) {
                    switch (w->input_pin) {
                        case PIN_TRANSISTOR_GATE:
                            break;

                        case PIN_TRANSISTOR_SOURCE:
                            switch (w->output_id) {
                                case GATE_PIN_OUTPUT:
                                    
                                    switch (t->type) {
                                        case TYPE_P:
                                            t->source = gate->output;
                                            break;
                                        case TYPE_N:
                                            t->drain = gate->output;
                                            break;
                                    }

                                    break;
                                case GATE_PIN_INPUT1:  break;
                                case GATE_PIN_INPUT2:  break;
                                case GATE_PIN_VDD:     break;
                                case GATE_PIN_GROUND:
                                    
                                    switch (t->type) {
                                        case TYPE_P:
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

                                            gate->ground = t->source;
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
                                            if (t->source == 1 && t->gate == 1)
                                                t->drain = 0;
                                            else if (t->source == 1 && t->gate == 0)
                                                t->drain = 1;
                                            else if (t->source == 0 && t->gate == 0)
                                                t->drain = 0;
                                            else if (t->source == 0 && t->gate == 1)
                                                t->drain = 0;

                                            gate->output = t->drain;
                                            break;
                                            
                                        case TYPE_N:
                                            t->drain = gate->output;
                                            break;
                                    }

                                    break;

                                case GATE_PIN_INPUT1:  break;
                                case GATE_PIN_INPUT2:  break;
                                case GATE_PIN_VDD:     break;
                                case GATE_PIN_GROUND:  break;
                            }
                            break;
                    }
                }
            }
        }

        printf("\ntransistors:\n");
        for (transistor_t *t=gate->transistors; t != NULL; t=t->next)
            printf("\tid: %d, type: %s, gate: %d, drain: %d, source: %d\n", 
                t->id, !t->type ? "P-TYPE" : "N-TYPE", t->gate, t->drain, t->source);

        printf("\nNOT GATE:\n"
               "\tInput.: %d\n"
               "\tOutput: %d\n", gate->input1, gate->output);
        printf("\tVdd...: %d\n", gate->vdd);
        printf("\tGround: %d\n", gate->ground);
    }

    return 0;
}



