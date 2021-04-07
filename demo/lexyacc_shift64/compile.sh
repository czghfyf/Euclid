#!/bin/bash

rm -f *.h *.c *.out

flex s64.l

bison -d s64.y

gcc lex.yy.c s64.tab.c -lfl
