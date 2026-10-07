%{
#include <stdio.h>
#include <string.h>

#define MAX_ID_LEN 20
%}

%%

[ \t\n]+                    ;       /* Ignore spaces, tabs and newlines */

"//".*                      ;       /* Ignore single-line comments */

"/*"([^*]|\*+[^*/])*\*+"/"  ;       /* Ignore multi-line comments */

"int"|"float"|"char"|"if"|"else"|"while"|"for"|"return"|"void"
                            { printf("%s : KEYWORD\n", yytext); }

[a-zA-Z_][a-zA-Z0-9_]{0,19}
                            { printf("%s : IDENTIFIER\n", yytext); }

[0-9]+(\.[0-9]+)?           { printf("%s : NUMBER\n", yytext); }

"=="|"!="|"<="|">="|"++"|"--"
                            { printf("%s : OPERATOR\n", yytext); }

"+"|"-"|"*"|"/"|"="|"<"|">"|"%"
                            { printf("%s : OPERATOR\n", yytext); }

"("|")"|"{"|"}"|"["|"]"|";"|","
                            { printf("%s : SPECIAL SYMBOL\n", yytext); }

.                           { printf("%s : UNKNOWN SYMBOL\n", yytext); }

%%

int main()
{
    FILE *fp;

    fp = fopen("input.c", "r");

    if (fp == NULL)
    {
        printf("Unable to open input.c\n");
        return 1;
    }

    yyin = fp;

    yylex();

    fclose(fp);

    return 0;
}