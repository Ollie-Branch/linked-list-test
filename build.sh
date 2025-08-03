#!/usr/bin/env sh
gcc -o main.o main.c -c -g
gcc -o ll.o ll.c -c -g
gcc -o ll main.o ll.o -g
