#!/bin/bash

rm -rf machine
cd source

HEADER="-I../header"

gcc -c debug.c                  -o debug.o                  $HEADER
gcc -c utils.c                  -o utils.o                  $HEADER
gcc -c transistor-creation.c    -o transistor-creation.o    $HEADER
gcc -c wire-creation.c          -o wire-creation.o          $HEADER
gcc -c gate-construction.c      -o gate-construction.o      $HEADER
gcc -c gate-machine.c           -o gate-machine.o           $HEADER
gcc -c device-arithmetic.c      -o device-arithmetic.o      $HEADER

OBJECTS="  debug.o utils.o gate-machine.o gate-construction.o "
OBJECTS+=" transistor-creation.o wire-creation.o              "
OBJECTS+=" device-arithmetic.o                                "

gcc main.c $HEADER $OBJECTS -o machine -lm

rm -rf *.o
mv machine ..


