/* simplest version of calculator */

%{
#include <stdio.h>
int yyerror(const char *, ...);
extern int yylex();
extern int yyparse();
%}

/* declare tokens */
%token TXTSEG

%%

content: TXTSEG
 |	content TXTSEG
;

%%
int main()
{

    if (my_scan_string("\n\t  select cube from cube where cube") != 0) {
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

