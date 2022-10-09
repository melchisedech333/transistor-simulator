
#ifndef _H_TRANSISTOR_
#define _H_TRANSISTOR_

#include "headers.h"

#define TYPE_P 0
#define TYPE_N 1

typedef struct transistor_s {
    int id;
    int type;       // 0: N, 1: P.
    int gate;
    int drain;
    int source;
    struct  transistor_s *next;
} transistor_t;

transistor_t *get_transistors (int total_p, int total_n);

#endif


