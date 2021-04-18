#!/bin/bash

rm -f *.h *.c *.out

flex lex-stat.l

bison -d yacc.y

gcc lex.yy.c yacc.tab.c -lfl
