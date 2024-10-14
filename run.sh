#!/bin/bash

gcc -Wall -Wextra -Werror *.c -D BUFFER_SIZE=0
./a.out > test
cat test