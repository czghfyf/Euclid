OSQE = Euclid.o cfg.o comm-proc.o ec-grammar.tab.o lex.yy.o

euclid cli: $(OSQE) cli.c
	gcc $(OSQE) -lfl -lpthread -o euclid
	gcc cli.c -o cli

lex.yy.c: ec-lexical.l
	flex $<

ec-grammar.tab.c ec-grammar.tab.h: ec-grammar.y
	bison -d $<

clean:
	rm -f euclid cli
	rm -f *.o *.out *.c~
	rm -f lex.yy.c ec-grammar.tab.c ec-grammar.tab.h
