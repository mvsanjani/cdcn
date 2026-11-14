#include <stdio.h>
#include <string.h>

int action[7][3] = {
    {3, 4, 0},
    {0, 0, 9},
    {3, 4, 0},
    {3, 4, 0},
    {-3, -3, -3},
    {0, 0, -1},
    {-2, -2, -2}
};

int goTo[7][2] = {
    {1, 2},
    {-1, -1},
    {-1, 5},
    {-1, 6},
    {-1, -1},
    {-1, -1},
    {-1, -1}
};

char input[100];
int stack[100];
int top = -1;
int pos = 0;

int getColumn(char ch)
{
    if (ch == 'c')
        return 0;
    else if (ch == 'd')
        return 1;
    else if (ch == '$')
        return 2;
    else
        return -1;
}

int main()
{
    int state, col, act, rule, len, row;

    printf("Enter input string: ");
    scanf("%s", input);

    strcat(input, "$");

    stack[++top] = 0;

    while (1)
    {
        state = stack[top];

        col = getColumn(input[pos]);

        if (col == -1)
        {
            printf("Invalid input symbol!\n");
            break;
        }

        act = action[state][col];

        // ACCEPT
        if (act == 9)
        {
            printf("Input Accepted!\n");
            break;
        }

        // ERROR
        if (act == 0)
        {
            printf("Input Rejected!\n");
            break;
        }

        // SHIFT
        if (act > 0)
        {
            printf("Shift %c -> State %d\n", input[pos], act);

            stack[++top] = act;
            pos++;
        }

        // REDUCE
        else
        {
            rule = -act;

            if (rule == 1)
            {
                printf("Reduce using S -> CC\n");
                len = 2;
                row = 0;
            }
            else if (rule == 2)
            {
                printf("Reduce using C -> cC\n");
                len = 2;
                row = 1;
            }
            else
            {
                printf("Reduce using C -> d\n");
                len = 1;
                row = 1;
            }

            // POP states
            top = top - len;

            state = stack[top];

            // GOTO
            state = goTo[state][row];

            if (state == -1)
            {
                printf("Parsing Error!\n");
                break;
            }

            stack[++top] = state;
        }
    }

    return 0;
}