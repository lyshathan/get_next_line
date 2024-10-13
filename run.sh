#!/bin/bash

gcc *.c -D BUFFER_SIZE=30
./a.out > test
cat test