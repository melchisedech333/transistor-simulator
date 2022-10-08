#!/bin/bash

gcc -c transistor.c -o transistor.o
gcc -c logic-port.c -o logic-port.o

gcc machine.c transistor.o logic-port.o -o machine


