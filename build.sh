#!/bin/bash

gcc -c transistor.c -o transistor.o
gcc -c wire.c       -o wire.o
gcc -c gate.c       -o gate.o
gcc -c machine.c    -o machine.o

gcc main.c machine.o transistor.o wire.o gate.o -o machine

rm -rf *.o


