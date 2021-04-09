#!/bin/bash

rm -f *.h *.c *.out

flex mdx.l

bison -d mdx.y

gcc lex.yy.c mdx.tab.c -lfl
