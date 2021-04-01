rm -f *.h
rm -f *.c
rm -f *.out
cp ../../src/utils.* .
flex lex-UTF8.l
gcc lex.yy.c utils.c -lfl
