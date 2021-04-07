%{
#include <stdio.h>
int yyerror(const char *, ...);
extern int yylex();
extern int yyparse();
%}

%token SEG

%%

line:
	SEG {}
  |	line SEG {}
;

%%

int main(int argc, char *argv[])
{

    if (my_scan_string("Kubernetes also known as K8s \nis an open-source system \nfor\n automating deployment \nscaling and management of \ncontainerized applications") != 0) {
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

