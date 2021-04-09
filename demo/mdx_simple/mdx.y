/*

select
{ [dimA].[m000], [dimA].[m001] } on rows,
{ [dimX].[m111], [dimY].[m222] } on columns
from [Cube000]

*/
%{
#include <stdio.h>
int yyerror(const char *, ...);
extern int yylex();
extern int yyparse();
%}

/* declare tokens */
%token SELECT
%token FROM
%token ON
%token COLUMNS ROWS

%token DOT					/* . */
%token COMMA				/* , */
%token SQUARE_BRACKET_L		/* [ */
%token SQUARE_BRACKET_R		/* ] */
%token CURLY_BRACKET_L		/* { */
%token CURLY_BRACKET_R		/* } */

%token SIMPLE_STR

%%

mdx:
	select_statement {
	}
;

select_statement:
	SELECT axises_specification FROM cube_specification {
	}
;

axises_specification:
	axis_specification {
	}
  |	axises_specification COMMA axis_specification {
	}
;

axis_specification:
	CURLY_BRACKET_L member_list CURLY_BRACKET_R ON coordinate {
	}
;

member_list:
	block_list {
	}
  |	member_list COMMA block_list {
	}
;

block_list:
	block {
	}
  |	block_list DOT block {
	}
;

block:
	SQUARE_BRACKET_L SIMPLE_STR SQUARE_BRACKET_R {
	}
;
	

coordinate:
	COLUMNS {
	}
  |	ROWS {
	}
;

cube_specification:
	block {
	}
;

%%

int main(int argc, char *argv[])
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

