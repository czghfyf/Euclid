/* recognize tokens for the calculator and print them out */

%{
# include "cal.tab.h"
extern int yyerror(const char *, ...);
%}

%%
"+"	{ return ADD; }
"-"	{ return SUB; }
"*"	{ return MUL; }
"/"	{ return DIV; }
"|" { return ABS; }
"(" { return OP; }
")" { return CP; }
[-+]?[0-9]+ { yylval = atoi(yytext); return NUMBER; }

\n      { return EOL; }
"//".*  
[ \t]   { /* ignore white space */ }
.	{ yyerror("Mystery character %c\n", *yytext); }
%%

