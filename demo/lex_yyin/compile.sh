rm -f *.h
rm -f *.c
rm -f *.out
flex lex-yyin.l
gcc lex.yy.c -lfl
