
/**
 * I Love Jesus <3
 */

#include "headers.h"
#include "transistor.h"

int main (int argc, char *argv[])
{
    transistor_p *transistors = get_transistors(3);
    transistor_p *t = NULL;
    int a = 1;

    for (t=transistors; t != NULL; t=t->next) {
        printf("Transistor %d\n", a++);
    }

    return 0;
}



