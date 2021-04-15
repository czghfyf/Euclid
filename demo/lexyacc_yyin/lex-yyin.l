%{
#include <stdio.h>

%}

%%

^[^ \t\n]+	{
	printf("^^^^^^ %s\n", yytext);
}

[^ \t\n]+ {
	printf(">>> %s\n", yytext);
}

.		{
	;
}

%%
int main(int argc, char *argv[])
{
	if (argc > 1) {
		FILE *file = fopen(argv[1], "r");
		if (!file) {
			printf("can not open file %s\n", argv[1]);
			exit(1);
		}
		yyin = file;
	}

	yylex();
	return 0;

}
