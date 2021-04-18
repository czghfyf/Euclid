/*

select
{ [dimA].[m000], [dimA].[m001] } on rows,
{ [dimX].[m111], [dimY].[m222] } on columns
from [Cube000]

*/
%{
#include <stdio.h>
#include <time.h>
int yyerror(const char *, ...);

void now_time();

extern int yylex();
extern int yyparse();

int switch_print = 90999;
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
		if (switch_print)
		printf("<mdx> : <select_statement>\n");
	}
;

select_statement:
	SELECT axises_specification FROM cube_specification {
		if (switch_print)
		printf("<select_statement> : select <axises_specification> from <cube_specification>\n");
	}
;

axises_specification:
	axis_specification {
		if (switch_print)
		printf("<axises_specification> : <axis_specification>\n");
	}
  |	axises_specification COMMA axis_specification {
		if (switch_print)
		printf("<axises_specification> : <axises_specification> , <axis_specification>\n");
	}
;

axis_specification:
	CURLY_BRACKET_L member_list CURLY_BRACKET_R ON coordinate {
		if (switch_print)
		printf("<axis_specification> : { <member_list> } on <coordinate>\n");
	}
;

member_list:
	block_list {
		if (switch_print)
		printf("<member_list> : <block_list>\n");
	}
  |	member_list COMMA block_list {
		if (switch_print)
		printf("<member_list> : <member_list> , <block_list>\n");
	}
;

block_list:
	block {
		if (switch_print)
		printf("<block_list> : <block>\n");
	}
  |	block_list DOT block {
		if (switch_print)
		printf("<block_list> : <block_list> . <block>\n");
	}
;

block:
	SQUARE_BRACKET_L SIMPLE_STR SQUARE_BRACKET_R {
		if (switch_print)
		printf("<block> : [ token-SIMPLE_STR ]\n");
	}
;
	

coordinate:
	COLUMNS {
		if (switch_print)
		printf("<coordinate> : columns\n");
	}
  |	ROWS {
		if (switch_print)
		printf("<coordinate> : rows\n");
	}
;

cube_specification:
	block {
		if (switch_print)
		printf("<cube_specification> : <block>\n");
	}
;

%%

int main(int argc, char *argv[])
{
	char *mdx = "select { [d0].[m0], [aaa].[bbb] } on rows,\n{ [dX] } on columns\nfrom [testCube000]";

	// printf("%s\n", mdx);

	unsigned int i;
	for (i = 0; i < 4294967295; i++) {
		if (i % 100000 == 0) {
			switch_print = 1;
			printf("------------------------------------------------------- %d\n", i);
			now_time();
		}
		my_scan_string(mdx);

	    yyparse();
	    my_cleanup();


		switch_print = 0;
	}


    return 0;

}

int yyerror(const char *s, ...)
{
	printf("[yy error] <%s>\n", s);
    return -100;
}

void now_time()
{
  time_t tmpcal_ptr;
  struct tm *tmp_ptr = NULL;
  time (&tmpcal_ptr);
  // printf ("tmpcal_ptr=%d\n", tmpcal_ptr);
  tmp_ptr = gmtime (&tmpcal_ptr);
  // printf ("after gmtime, the time is:%d:%d:%d\n", tmp_ptr->tm_hour,
  //    tmp_ptr->tm_min, tmp_ptr->tm_sec);
  tmp_ptr = localtime (&tmpcal_ptr);
  printf ("after localtime, the time is:%d.%d.%d ", (1900 + tmp_ptr->tm_year),
      (1 + tmp_ptr->tm_mon), tmp_ptr->tm_mday);
  printf ("%d:%d:%d\n", tmp_ptr->tm_hour, tmp_ptr->tm_min, tmp_ptr->tm_sec);


}

