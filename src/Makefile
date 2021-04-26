euclid cli: Euclid.o comm-proc.o yacc-bison.o lex-flex.o cli.c
	gcc Euclid.o comm-proc.o yacc-bison.o lex-flex.o -lfl -lpthread -o euclid
	gcc cli.c -o cli

Euclid.o: Euclid.c command-processor.h
	gcc -c Euclid.c

comm-proc.o: command-processor.c command-processor.h
	gcc -c command-processor.c -o comm-proc.o

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
