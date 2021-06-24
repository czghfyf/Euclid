OSQE = cfg.o utils.o comm-proc.o ec-grammar.tab.o lex.yy.o conn.o model.o
SRC  = cfg.c utils.c comm-proc.c ec-grammar.tab.c lex.yy.c conn.c model.c

euclid euclid-cli: $(OSQE) Euclid.o Euclid-cli.o $(SRC) Euclid.c Euclid-cli.c
	gcc Euclid.o     $(OSQE) -lfl -lpthread -o euclid
	gcc Euclid-cli.o $(OSQE) -lfl -lpthread -o euclid-cli
	gcc Euclid.c     $(SRC)  -lfl -lpthread -o euclid.out -g
	gcc Euclid-cli.c $(SRC)  -lfl -lpthread -o euclid-cli.out -g

lex.yy.c: ec-lexical.l
	flex $<

ec-grammar.tab.c ec-grammar.tab.h: ec-grammar.y
	bison -d $<

clean:
	rm -f euclid euclid-cli
	rm -f *.o *.out *.c~ *.h~ *.o~
	rm -f lex.yy.c ec-grammar.tab.c ec-grammar.tab.h
	rm -f .*.swp
