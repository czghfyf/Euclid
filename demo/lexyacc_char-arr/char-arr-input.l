/* recognize tokens for the calculator and print them out */

%{
#include "char-arr-input.tab.h"
extern int yyerror(const char *, ...);
%}

%%
"+"	{ return ADD; }
"-"	{ return SUB; }
"*"	{ return MUL; }
"/"	{ return DIV; }
"(" { return OP; }
")"	{ return CP; }
[0-9]+	{ yylval = atoi(yytext); return NUMBER; }
\n     	{ return EOL; }
"//".*
[ \t]	{ ; /* ignore white space */ }
.		{ yyerror("Mystery character %c\n", *yytext); }
%%
static YY_BUFFER_STATE my_string_buffer;

int my_scan_string(const char *s) {

	printf("---------------------------------------------------sizeof(YY_BUFFER_STATE)  = %d\n", sizeof(YY_BUFFER_STATE));
	printf("---------------------------------------------------sizeof(my_string_buffer) = %d\n", sizeof(my_string_buffer));

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
