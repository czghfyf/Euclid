%{
#include <stdio.h>

// TODO include <stdarg.h>, and then use variable parameters
int yyerror(const char *fmt, ...);

// extern int yylex();
// extern int yyparse();

extern char *yytext;
%}

%token CREATE

%token DIMENSION

%token TXT_PIECE	/* eg: [China_region], 'China_region' is a dimension name. */

%%

create_dimension:
	CREATE DIMENSION TXT_PIECE {
		printf("<create_dimension> : CREATE DIMENSION TXT_PIECE\n");
		// TODO
		printf("bison(yacc) require token %s. at now, yytext literal is %s\n", "TXT_PIECE", yytext);
	}
;

%%

int main(int argc, char *argv[])
{
	char *ddl = "create dimension [China region]";
	scan_comm_stat(ddl);
    yyparse();
	cleanup_yy_str_buff();
    return 0;
}

int yyerror(const char *fmt, ...)
{
	printf("yyerror %s\n", fmt);
    return -1;
}

