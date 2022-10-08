
#ifndef _H_LOGIC_PORT_
#define _H_LOGIC_PORT_

#include "headers.h"

#define PORT_XOR 1

typedef struct logic_port_s {
    int type;
    int input1;
    int input2;
    int output;
} logic_port_t;

logic_port_t *create_port (int type);

#endif


