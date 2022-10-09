
#include "transistor.h"

static transistor_t *create_transistor (int type);
static void insert_transistor (transistor_t *transistors, transistor_t *n_transistor);

transistor_t *get_transistors (int total_p, int total_n)
{
    transistor_t *transistors = NULL, *transistor = NULL;
    int index = 0, i_total_p = total_p, i_total_n = total_n;

    if (!i_total_p && !i_total_n) {
        printf("Enter a valid number of transistor.\n");
        exit(0);
    }

    if (i_total_p) {
        transistors = create_transistor(TYPE_P);
        transistors->id = index++;
        i_total_p--;
    } else if (i_total_n) {
        transistors = create_transistor(TYPE_N);
        transistors->id = index++;
        i_total_n--;
    }

    for (int a=0; a<i_total_p; a++) {
        transistor = create_transistor(TYPE_P);
        transistor->id = index++;
        insert_transistor(transistors, transistor);
    }

    for (int a=0; a<i_total_n; a++) {
        transistor = create_transistor(TYPE_N);
        transistor->id = index++;
        insert_transistor(transistors, transistor);
    }

    return transistors;
}

static transistor_t *create_transistor (int type)
{
    transistor_t *transistor = (transistor_t *) malloc (sizeof(transistor_t));

    if (!transistor) {
        printf("Error alloc memory.\n");
        exit(-1);
    }

    memset(transistor, 0, sizeof(transistor_t));

    transistor->type   = type;
    transistor->id     = 0;
    transistor->gate   = 0;
    transistor->drain  = 0;
    transistor->source = 0;
    transistor->next   = NULL;

    return transistor;
}

static void insert_transistor (transistor_t *transistors, transistor_t *n_transistor)
{
    transistor_t *transistor = transistors;

    if (!transistors || !n_transistor) {
        printf("Invalid transistor input.\n");
        exit(0);
    }

    while (1) {
        if (!transistor->next) {
            transistor->next = n_transistor;
            break;
        }

        transistor = transistor->next;
    }
}


