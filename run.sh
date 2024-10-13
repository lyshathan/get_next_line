#!/bin/bash

gcc *.c -D BUFFER_SIZE=10000000
./a.out > test
cat test