#!/bin/bash

rm -f *.h *.c *.out

flex char-arr-input.l

bison -d char-arr-input.y

gcc lex.yy.c char-arr-input.tab.c -lfl
