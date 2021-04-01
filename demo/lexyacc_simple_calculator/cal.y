/* simplest version of calculator */

%{
#include <stdio.h>
int yyerror(const char *, ...);
extern int yylex();
extern int yyparse();
%}

/* declare tokens */
%token NUMBER
%token ADD SUB MUL DIV ABS
%token OP CP
%token EOL

%%

calclist: /* nothing */
    | calclist exp EOL { printf("= %d\n> ", $2); }
    | calclist EOL { printf("> "); } /* blank line or a comment */
;

exp: factor
    | exp ADD exp { $$ = $1 + $3; }
    | exp SUB factor { $$ = $1 - $3; }
    | exp ABS factor { $$ = $1 | $3; }
;

factor: term
    | factor MUL term { $$ = $1 * $3; }
    | factor DIV term { $$ = $1 / $3; }
;

term: NUMBER
    | ABS term { $$ = $2 >= 0? $2 : - $2; }
    | OP exp CP { $$ = $2; }
;
%%
int main()
{
    printf("> "); 
    yyparse();
    return 0;
}
int yyerror(const char *s, ...)
{
    int ret;
    va_list va;
    va_start(va, s);
    ret = vfprintf(stderr, s, va);
    va_end(va);
    return ret;
}

