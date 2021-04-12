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
		printf("<mdx> : <select_statement>\n");
	}
;

select_statement:
	SELECT axises_specification FROM cube_specification {
		printf("<select_statement> : select <axises_specification> from <cube_specification>\n");
	}
;

axises_specification:
	axis_specification {
		printf("<axises_specification> : <axis_specification>\n");
	}
  |	axises_specification COMMA axis_specification {
		printf("<axises_specification> : <axises_specification> , <axis_specification>\n");
	}
;

axis_specification:
	CURLY_BRACKET_L member_list CURLY_BRACKET_R ON coordinate {
		printf("<axis_specification> : { <member_list> } on <coordinate>\n");
	}
;

member_list:
	block_list {
		printf("<member_list> : <block_list>\n");
	}
  |	member_list COMMA block_list {
		printf("<member_list> : <member_list> , <block_list>\n");
	}
;

block_list:
	block {
		printf("<block_list> : <block>\n");
	}
  |	block_list DOT block {
		printf("<block_list> : <block_list> . <block>\n");
	}
;

block:
	SQUARE_BRACKET_L SIMPLE_STR SQUARE_BRACKET_R {
		printf("<block> : [ token-SIMPLE_STR ]\n");
	}
;
	

coordinate:
	COLUMNS {
		printf("<coordinate> : columns\n");
	}
  |	ROWS {
		printf("<coordinate> : rows\n");
	}
;

cube_specification:
	block {
		printf("<cube_specification> : <block>\n");
	}
;

%%

int main(int argc, char *argv[])
{
	char *mdx = "select { [d0].[m0], [aaa].[bbb] } on rows,\n{ [dX] } on columns\nfrom [testCube000]";

	printf("%s\n", mdx);

	my_scan_string(mdx);

    yyparse();
    my_cleanup();

    return 0;

}

int yyerror(const char *s, ...)
{
	printf("[yy error] <%s>\n", s);
    return -100;
}

