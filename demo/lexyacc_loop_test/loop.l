/* recognize tokens for the calculator and print them out */

%{
#include "loop.tab.h"
extern int yyerror(const char *, ...);

extern int switch_print;
%}

%%
select	{
	// printf("switch_print = %d\n", switch_print);
	if (switch_print)
	printf("-------> token yytext[%s] yyleng[%d]\n", yytext, yyleng);
	return SELECT; 
}
from	{ 
	if (switch_print)
	printf("-------> token yytext[%s] yyleng[%d]\n", yytext, yyleng);
	return FROM; 
}
on	{ 
	if (switch_print)
	printf("-------> token yytext[%s] yyleng[%d]\n", yytext, yyleng);
	return ON; 
}
columns	{ 
	if (switch_print)
	printf("-------> token yytext[%s] yyleng[%d]\n", yytext, yyleng);
	return COLUMNS; 
}
rows	{ 
	if (switch_print)
	printf("-------> token yytext[%s] yyleng[%d]\n", yytext, yyleng);
	return ROWS; 
}
[a-zA-Z0-9]+	{ 
	if (switch_print)
	printf("-------> token yytext[%s] yyleng[%d]\n", yytext, yyleng);
	return SIMPLE_STR; 
}
"."	{ 
	if (switch_print)
	printf("-------> token yytext[%s] yyleng[%d]\n", yytext, yyleng);
	return DOT; 
}
","	{ 
	if (switch_print)
	printf("-------> token yytext[%s] yyleng[%d]\n", yytext, yyleng);
	return COMMA; 
}
"["	{ 
	if (switch_print)
	printf("-------> token yytext[%s] yyleng[%d]\n", yytext, yyleng);
	return SQUARE_BRACKET_L; 
}
"]"	{ 
	if (switch_print)
	printf("-------> token yytext[%s] yyleng[%d]\n", yytext, yyleng);
	return SQUARE_BRACKET_R; 
}
"{" 	{ 
	if (switch_print)
	printf("-------> token yytext[%s] yyleng[%d]\n", yytext, yyleng);
	return CURLY_BRACKET_L; 
}
"}"	{ 
	if (switch_print)
	printf("-------> token yytext[%s] yyleng[%d]\n", yytext, yyleng);
	return CURLY_BRACKET_R; 
}

[ \n\t]+	{ /* ignore white space */}

.	{ 
	if (switch_print)
	printf("<:%s:>", yytext); 
}
%%
static YY_BUFFER_STATE my_string_buffer;

int my_scan_string(const char *s) {

    // insist on cleaning up any existing buffer before setting up a new one
	if (my_string_buffer != NULL)
		return -1;

    // Set up and switch to a buffer for scanning the contents of the
    // specified string.  A copy of the string will be made.
    my_string_buffer = yy_scan_string(s);
    return my_string_buffer == NULL ? -1 : 0;
}

void my_cleanup() {
    // No effect if my_string_buffer is NULL
    yy_delete_buffer(my_string_buffer);
    // ... but avoid trying to free the same buffer twice
    my_string_buffer = NULL;
}
