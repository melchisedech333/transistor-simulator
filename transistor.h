
#ifndef _H_TRANSISTOR_
#define _H_TRANSISTOR_

#include "headers.h"

typedef struct transistor_s {

    // Gate control.
    //  1 = enabled.
    //  0 = disabled.
    int base;
    int collector;
    int emitter;

    // Control of transistor array.
    struct  transistor_s *next;
} transistor_p;

transistor_p *get_transistors (int total);

#endif


