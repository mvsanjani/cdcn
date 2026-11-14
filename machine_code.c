
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char expr[100];
int pos = 0;
int reg = 0;

struct Node
{
    char data;
    struct Node *left, *right;
};

struct Node* createNode(char ch)
{
    struct Node *n = malloc(sizeof(struct Node));
    n->data = ch;
    n->left = NULL;
    n->right = NULL;
    return n;
}

struct Node* expression();

struct Node* factor()
{
    struct Node *n;

    if (expr[pos] == '(')
    {
        pos++;
        n = expression();
        pos++;
        return n;
    }

    while (isspace(expr[pos]))
        pos++;

    n = createNode(expr[pos]);
    pos++;

    return n;
}

struct Node* term()
{
    struct Node *n = factor();

    while (expr[pos] == '*' || expr[pos] == '/')
    {
        char op = expr[pos++];
        struct Node *temp = createNode(op);

        temp->left = n;
        temp->right = factor();
        n = temp;
    }

    return n;
}

struct Node* expression()
{
    struct Node *n = term();

    while (expr[pos] == '+' || expr[pos] == '-')
    {
        char op = expr[pos++];
        struct Node *temp = createNode(op);

        temp->left = n;
        temp->right = term();
        n = temp;
    }

    return n;
}

int generate(struct Node *root)
{
    if (root->left == NULL && root->right == NULL)
    {
        int r = reg++;
        printf("MOV R%d, %c\n", r, root->data);
        return r;
    }

    int r1 = generate(root->left);
    int r2 = generate(root->right);

    if (root->data == '+')
        printf("ADD R%d, R%d\n", r1, r2);
    else if (root->data == '-')
        printf("SUB R%d, R%d\n", r1, r2);
    else if (root->data == '*')
        printf("MUL R%d, R%d\n", r1, r2);
    else if (root->data == '/')
        printf("DIV R%d, R%d\n", r1, r2);

    reg--;
    return r1;
}

int main()
{
    struct Node *root;
    char result;

   char expr[100];

printf("Enter expression: ");
scanf("%s", expr);

    // Skip spaces
    while (isspace(expr[pos]))
        pos++;

    // Get assignment variable
    result = expr[pos];

    if (expr[pos + 1] == '=')
        pos += 2;

    root = expression();

    printf("\nGenerated Machine Code:\n");

    int r = generate(root);

    printf("MOV %c, R%d\n", result, r);

    return 0;
}
 