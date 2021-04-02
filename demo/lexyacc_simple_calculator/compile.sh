#!/bin/bash

rm -f *.h *.c *.out

flex cal.l

bison -d cal.y

gcc lex.yy.c cal.tab.c -lfl
