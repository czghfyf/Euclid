/*

with
member &1001[dimension A].[cal mbr] as &1001.[member X] + &1001.[member Y]
set [def-set-001] as members([dimension B])
select
{&1001[dimension A].[cal mbr], &1001.[member X], &1001.[member Y]} on rows,
{ ([dim C].[m000], [dim D].[m000]), ([dim C].[m001], [dim D].[m999]) } on 100,
[def-set-001] on columns
from [Cube-666]
where
( &9010.&9876, [region dimension].[USA].[big apple] )

--------------------------------------------------------------------------------

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

%token COMMA				/* , */
%token SQUARE_BRACKET_L		/* [ */
%token SQUARE_BRACKET_R		/* ] */
%token ROUND_BRACKET_L		/* ( */
%token ROUND_BRACKET_R		/* ) */
%token CURLY_BRACKET_L		/* { */
%token CURLY_BRACKET_R		/* } */

%%

mdx: /* nothing */
  |	select_statement {
		printf("select_statement { $1 = %p }\n", $1);
		$$ = $1;
	}
;

select_statement:
	SELECT axises_specification {
		printf("axises_specification\n");
	}
  |	FROM cube_specification {
		printf("cube_specification\n");
	}
;

axises_specification:
	axis_specification {
		printf("axis_specification\n");
	}
  |	axises_specification COMMA axis_specification {
		printf("axises_specification COMMA axis_specification\n");
	}
;

axis_specification:

;

cube_specification:
	SQUARE_BRACKET_L        xxxxxxxxx cube name xxxxxxxxxx         SQUARE_BRACKET_R
;







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

