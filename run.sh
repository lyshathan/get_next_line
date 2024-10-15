#!/bin/bash

gcc *.c -D BUFFER_SIZE=43
./a.out > test
cat -e test