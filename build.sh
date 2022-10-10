#!/bin/bash

gcc -c debug.c                  -o debug.o
gcc -c utils.c                  -o utils.o
gcc -c transistor-creation.c    -o transistor-creation.o
gcc -c wire-creation.c          -o wire-creation.o
gcc -c gate-construction.c      -o gate-construction.o
gcc -c gate-machine.c           -o gate-machine.o
gcc -c device-arithmetic.c      -o device-arithmetic.o

OBJECTS="  debug.o utils.o gate-machine.o gate-construction.o "
OBJECTS+=" transistor-creation.o wire-creation.o              "
OBJECTS+=" device-arithmetic.o                                "

gcc main.c $OBJECTS -o machine -lm

rm -rf *.o


