#!/bin/bash

gcc -c transistor.c -o transistor.o
gcc -c gate.c -o gate.o

gcc machine.c transistor.o gate.o -o machine


