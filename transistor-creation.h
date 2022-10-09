
#ifndef _H_TRANSISTOR_CREATION_
#define _H_TRANSISTOR_CREATION_

#include "headers.h"

#define TYPE_P 0
#define TYPE_N 1

typedef struct transistor_s {
    int id;
    int type;       // 0: N-TYPE, 1: P-TYPE.
    int gate;
    int drain;
    int source;

    struct  transistor_s *next;
} transistor_t;

transistor_t *get_transistors (int total_p, int total_n);
int get_first_transistor_id (transistor_t *transistors, int type);

#endif


