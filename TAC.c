#include <stdio.h>
#include <string.h>
#include <ctype.h>

int temp = 1;

int prec(char op)
{
    if (op == '*' || op == '/')
        return 2;
    if (op == '+' || op == '-')
        return 1;
    return 0;
}

void calculate(char val[][20], int *top, char op)
{
    char a[20], b[20], t[20];

    strcpy(b, val[(*top)--]);
    strcpy(a, val[(*top)--]);

    sprintf(t, "t%d", temp++);

    printf("%s = %s %c %s\n", t, a, op, b);

    strcpy(val[++(*top)], t);
}

void generate(char exp[], char result[])
{
    char val[50][20], op[50];
    int top1 = -1, top2 = -1;
    int i = 0;

    while (exp[i] != '\0')
    {
        if (isalnum(exp[i]))
        {
            char s[20];
            int j = 0;

            while (isalnum(exp[i]))
                s[j++] = exp[i++];

            s[j] = '\0';
            strcpy(val[++top1], s);
        }
        else if (exp[i] == '(')
            op[++top2] = exp[i++];

        else if (exp[i] == ')')
        {
            while (top2 >= 0 && op[top2] != '(')
                calculate(val, &top1, op[top2--]);

            top2--;
            i++;
        }
        else if (exp[i] == '+' || exp[i] == '-' ||
                 exp[i] == '*' || exp[i] == '/')
        {
            while (top2 >= 0 && op[top2] != '(' &&
                   prec(op[top2]) >= prec(exp[i]))
                calculate(val, &top1, op[top2--]);

            op[++top2] = exp[i++];
        }
        else
            i++;
    }

    while (top2 >= 0)
        calculate(val, &top1, op[top2--]);

    if (top1 == 0)
        strcpy(result, val[top1]);
    else
        strcpy(result, "ERROR");
}

int main()
{
    char exp[100], lhs[20] = "", result[20];
    char *p;

    printf("Enter expression: ");
    scanf("%99s", exp);

    printf("\nThree Address Code:\n");

    p = strchr(exp, '=');

    if (p != NULL)
    {
        strncpy(lhs, exp, p - exp);
        lhs[p - exp] = '\0';

        generate(p + 1, result);

        if (strcmp(result, "ERROR") == 0)
            printf("Invalid Expression\n");
        else
            printf("%s = %s\n", lhs, result);
    }
    else
    {
        generate(exp, result);

        if (strcmp(result, "ERROR") == 0)
            printf("Invalid Expression\n");
    }

    return 0;
}
