#!/bin/bash

gcc -c transistor.c -o transistor.o
gcc machine.c transistor.o -o machine


