/* recognize tokens for the calculator and print them out */

%{
#include "yacc.tab.h"
extern int yyerror(const char *, ...);
%}

%s FC

%%

[ \t\n]+ {
	;
}

select	{
	printf("...>>> key word %s\n", yytext);
	return TXTSEG;
}

from {
	BEGIN FC;
	printf("...>>> key word %s\n", yytext);
	return TXTSEG;
}

where {
	printf("...>>> key word %s\n", yytext);
	return TXTSEG;
}

<FC>cube {
	printf("...>>> this is a cube\n");
	BEGIN 0;
	return TXTSEG;
}

[a-zA-Z]+ {
	printf("...>>> var = %s\n", yytext);
	return TXTSEG;
}

. {
	printf("...>>> <%s>\n", yytext);
}

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
