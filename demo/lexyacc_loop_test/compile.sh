#!/bin/bash

rm -f *.h *.c *.out

flex loop.l

bison -d loop.y

gcc lex.yy.c loop.tab.c -lfl
