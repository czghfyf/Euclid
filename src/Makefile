euclid cli: Euclid.o comm-proc.o ec-grammar.o lex.yy.o cfg.o cli.c
	gcc Euclid.o comm-proc.o ec-grammar.o lex.yy.o cfg.o -lfl -lpthread -o euclid
	gcc cli.c -o cli

Euclid.o: Euclid.c comm-proc.h cfg.h
	gcc -c Euclid.c

cfg.o: cfg.c cfg.h
	gcc -c cfg.c

comm-proc.o: comm-proc.c comm-proc.h
	gcc -c comm-proc.c

lex.yy.o: lex.yy.c ec-grammar.tab.h
	gcc -c lex.yy.c -o lex.yy.o

lex.yy.c: ec-lexical.l
	flex ec-lexical.l

ec-grammar.o: ec-grammar.tab.c ec-grammar.tab.h
	gcc -c ec-grammar.tab.c -o ec-grammar.o

ec-grammar.tab.c ec-grammar.tab.h: ec-grammar.y
	bison -d ec-grammar.y

clean:
	rm -f *.c~
	rm -f *.out
	rm -f euclid
	rm -f cli
	rm -f *.o
	rm -f lex.yy.c
	rm -f *.tab.h
	rm -f *.tab.c
