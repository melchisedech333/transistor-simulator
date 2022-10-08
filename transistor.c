
#include "transistor.h"

static transistor_t *create_transistor (void);
static void insert_transistor (transistor_t *transistors, transistor_t *n_transistor);

transistor_t *get_transistors (int total)
{
    transistor_t *transistors;

    if (!total) {
        printf("Enter a valid number of transistor.\n");
        exit(0);
    }

    transistors = create_transistor();

    for (int a=1; a<total; a++)
        insert_transistor(transistors, create_transistor());

    return transistors;
}

static transistor_t *create_transistor (void)
{
    transistor_t *transistor = (transistor_t *) malloc (sizeof(transistor_t));

    if (!transistor) {
        printf("Error alloc memory.\n");
        exit(-1);
    }

    memset(transistor, 0, sizeof(transistor_t));

    transistor->base      = 0;
    transistor->collector = 0;
    transistor->emitter   = 0;
    transistor->next      = NULL;

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


