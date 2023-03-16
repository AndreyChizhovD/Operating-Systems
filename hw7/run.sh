#!/bin/bash

gcc 1.c; mv a.out 1.out
gcc 2.c; mv a.out 2.out
./1.out & ./2.out && fg
rm 1.out 2.out
