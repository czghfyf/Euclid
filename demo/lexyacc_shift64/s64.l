/* recognize tokens for the calculator and print them out */

%{
#include "s64.tab.h"
extern int yyerror(const char *, ...);
%}

letter [a-zA-Z][a-zA-Z0-9]

s6 ^{letter}
s4 {letter}$

%%

s6 {
	printf("shift 6 ^ : %s\n", yytext);
	return SEG;
}

letter {

}

s4 {
	printf("shift 4 $ : %s\n", yytext);
	return SEG;

}

[ \t\n]	{ ; /* ignore white space */ }
.		{ yyerror("Mystery character %c\n", *yytext); }

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
