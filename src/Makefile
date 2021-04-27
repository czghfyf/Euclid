euclid cli: Euclid.o comm-proc.o yacc-bison.o lex-flex.o cfg.o cli.c
	gcc Euclid.o comm-proc.o yacc-bison.o lex-flex.o cfg.o -lfl -lpthread -o euclid
	gcc cli.c -o cli

Euclid.o: Euclid.c comm-proc.h cfg.h
	gcc -c Euclid.c

cfg.o: cfg.c cfg.h
	gcc -c cfg.c

comm-proc.o: comm-proc.c comm-proc.h
	gcc -c comm-proc.c

lex-flex.o: lex.yy.c statement-grammar.tab.h
	gcc -c lex.yy.c -o lex-flex.o

lex.yy.c: statement-lexical.l
	flex statement-lexical.l

yacc-bison.o: statement-grammar.tab.c statement-grammar.tab.h
	gcc -c statement-grammar.tab.c -o yacc-bison.o

statement-grammar.tab.c statement-grammar.tab.h: statement-grammar.y
	bison -d statement-grammar.y

clean:
	rm -f *.c~
	rm -f *.out
	rm -f euclid
	rm -f cli
	rm -f *.o
	rm -f lex.yy.c
	rm -f *.tab.h
	rm -f *.tab.c
