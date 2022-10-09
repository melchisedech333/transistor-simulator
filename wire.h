
#ifndef _H_WIRE_
#define _H_WIRE_

#include "headers.h"

typedef struct wire_s {
    int input_id;       // Transistor ID.
    int input_pin;      // Transistor PIN:
                        //  Gate..: 1
                        //  Drain.: 2
                        //  Source: 3
    int output_id;
    int output_pin;

    struct wire_s *next;    
} wire_t;

wire_t *get_wires (int total);

#endif


