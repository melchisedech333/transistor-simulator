#!/bin/bash

gcc -c debug.c                  -o debug.o
gcc -c transistor-creation.c    -o transistor-creation.o
gcc -c wire-creation.c          -o wire-creation.o
gcc -c gate-construction.c      -o gate-construction.o
gcc -c gate-machine.c           -o gate-machine.o

OBJECTS="  debug.o gate-machine.o gate-construction.o "
OBJECTS+=" transistor-creation.o wire-creation.o      "

gcc main.c $OBJECTS -o machine

rm -rf *.o


