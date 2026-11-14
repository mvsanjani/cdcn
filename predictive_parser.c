#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char input[100];
int pos = 0;
char lookahead;

void match(char expected)
{
    if (lookahead == expected)
        lookahead = input[++pos];
    else
    {
        printf("String Rejected\n");
        exit(0);
    }
}

void E();
void Eprime();
void T();
void Tprime();
void F();

void E()
{
    T();
    Eprime();
}

void Eprime()
{
    if (lookahead == '+')
    {
        match('+');
        T();
        Eprime();
    }
    else if (lookahead == ')' || lookahead == '$' || lookahead == '\0')
        return;
    else
    {
        printf("String Rejected\n");
        exit(0);
    }
}

void T()
{
    F();
    Tprime();
}

void Tprime()
{
    if (lookahead == '*')
    {
        match('*');
        F();
        Tprime();
    }
    else if (lookahead == '+' || lookahead == ')' || lookahead == '$' || lookahead == '\0')
        return;
    else
    {
        printf("String Rejected\n");
        exit(0);
    }
}

void F()
{
    if (lookahead == '(')
    {
        match('(');
        E();
        match(')');
    }
    else if (isalpha(lookahead))
    {
        while (isalnum(lookahead))
            lookahead = input[++pos];
    }
    else
    {
        printf("String Rejected\n");
        exit(0);
    }
}

int main()
{
    printf("Enter the input expression: ");
    scanf("%99s", input);

    pos = 0;
    lookahead = input[pos];

    E();

    if (lookahead == '\0')
        printf("String Accepted\n");
    else
        printf("String Rejected\n");

    return 0;
}