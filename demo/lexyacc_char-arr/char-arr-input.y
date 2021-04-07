/* simplest version of calculator */

%{
#include <stdio.h>
int yyerror(const char *, ...);
extern int yylex();
extern int yyparse();
%}

/* declare tokens */
%token NUMBER
%token ADD SUB MUL DIV
%token OP CP
%token EOL

%%

calclist: /* nothing */
    | calclist exp EOL { printf("{{{ result = %d }}}\n", $2); }
    | calclist EOL { printf(">>> \n"); } /* blank line or a comment */
;

exp: factor
    | exp ADD exp { $$ = $1 + $3; }
    | exp SUB factor { $$ = $1 - $3; }
;

factor: term
    | factor MUL term { $$ = $1 * $3; }
    | factor DIV term { $$ = $1 / $3; }
;

term: NUMBER
    | OP exp CP { $$ = $2; }
;
%%
int main()
{

    if (my_scan_string("60000000+7888\n") != 0) { // 60,007,888
        printf("error setting up an internal buffer\n");
		return 1;
    }
    yyparse();
    my_cleanup();

	// 999,334
	// -30
	// -998
    if (my_scan_string("1000000-666 \n (23 / 6) + (0-(100002 -99999)* 11) \n\n\n\n 1 + (0 - 999) \n") != 0) {
        printf("error setting up an internal buffer\n");
		return 1;
    }
    yyparse();
    my_cleanup();

    return 0;

}
int yyerror(const char *s, ...)
{
	printf("[yy error] %s\n", s);
    return -100;
}

