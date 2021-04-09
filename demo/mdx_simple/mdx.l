/* recognize tokens for the calculator and print them out */

%{
#include "mdx.tab.h"
extern int yyerror(const char *, ...);
%}

%%
select	{ return SELECT; }
from	{ return FROM; }
on		{ return ON; }
columns	{ return COLUMNS; }
rows	{ return ROWS; }
[a-zA-Z0-9]+	{ return SIMPLE_STR; }
"."	{ return DOT; }
","	{ return COMMA; }
"["	{ return SQUARE_BRACKET_L; }
"]"	{ return SQUARE_BRACKET_R; }
"{" { return CURLY_BRACKET_L; }
"}"	{ return CURLY_BRACKET_R; }
[ \n\t]+	{ /* ignore white space */}
.	{ printf("<:%s:>", yytext); }
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
