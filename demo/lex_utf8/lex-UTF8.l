%{
#include <stdio.h>

#include "utils.h"

/*
E4 B8 80  一
E4 B8 81  丁
E4 B8 83  七
E4 B8 87  万
E4 B8 88  丈
E4 B8 89  三
*/
%}

yi	\xE4\xB8\x80
di	\xE4\xB8\x81
qi	\xE4\xB8\x83
wa	\xE4\xB8\x87
zh	\xE4\xB8\x88
sa	\xE4\xB8\x89

utf8	{yi}|{di}|{qi}|{wa}|{zh}|{sa}

%%

{utf8}		{
	char *str = yytext;
	printf("【%s】\n", str);
	do {
		print_byte_binary(str++);
		printf("  ");
	} while (*str != 0);
	printf("\n----------------------------\n");
}

.	{
	printf(">>>>>>>>>>>> %s\n", yytext);
}

\n	{
	printf(">>>>>>>>>>>> Enter\n");
}

%%
int main(int argc, char *argv[])
{
	yylex();
	return 0;
}
