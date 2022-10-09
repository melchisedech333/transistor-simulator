#!/bin/bash

gcc -c transistor.c -o transistor.o
gcc -c wire.c       -o wire.o
gcc -c gate.c       -o gate.o

gcc machine.c transistor.o wire.o gate.o -o machine

rm -rf *.o


