#!/bin/bash

read input
read output
gcc 4.c
./a.out $input $output
rm a.out
