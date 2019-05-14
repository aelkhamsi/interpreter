#!/bin/bash

FILE=$1

make
./myml $FILE
gcc test.c -o test

