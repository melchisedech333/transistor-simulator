
#include "transistor.h"

static transistor_p *create_transistor (void);

transistor_p *get_transistors (int total)
{
    transistor_p *transistors;

    if (!total) {
        printf("Enter a valid number of transistor.");
        exit(0);
    }

    transistors = create_transistor();

    for (int a=0; a<total; a++)
        insert_transistor(transistors, create_transistor());

    return transistors;
}

static transistor_p *create_transistor (void)
{
    transistor_p *transistor = (transistor_p *) malloc (sizeof(transistor_p));

    if (!transistor) {
        printf("Error alloc memory.\n");
        exit(-1);
    }

    memset(transistor, 0, sizeof(transistor_p));

    transistor->base      = 0;
    transistor->collector = 0;
    transistor->emitter   = 0;
    transistor->next      = NULL;

    return transistor;
}

static void insert_transistor (transistor_p *transistors, transistor_p *n_transistor)
{
    transistor_p *transistor = transistors;

    if (!n_transistor) {
        printf("Invalid transistor (insert).\n");
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


