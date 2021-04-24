%{
#include "statement-grammar.tab.h"

extern int yyerror(const char *fmt, ...);
%}

%%

create {
	printf("flex match token: %s, literal is %s\n", "CREATE", yytext);
	return CREATE;
}

dimension {
	printf("flex match token: %s, literal is %s\n", "DIMENSION", yytext);
	return DIMENSION;
}

\[[a-zA-Z0-9_ ]+\] {
	printf("flex match token: %s, literal is %s\n", "TXT_PIECE", yytext);
	return TXT_PIECE;
}

[ \n\t]+ {
	// do nothing. ignore white space.
}

. {
	yyerror(yytext);
}

%%

static YY_BUFFER_STATE str_buff;

int scan_comm_stat(const char *cs) // scan command statement
{
    // insist on cleaning up any existing buffer before setting up a new one
	if (str_buff != NULL)
		return -1;
    // Set up and switch to a buffer for scanning the contents of the
    // specified string.  A copy of the string will be made.
    str_buff = yy_scan_string(cs);
    return str_buff == NULL ? -1 : 0;
}

void cleanup_yy_str_buff()
{
    // No effect if my_string_buffer is NULL
    yy_delete_buffer(str_buff);
    // ... but avoid trying to free the same buffer twice
    str_buff = NULL;
}
