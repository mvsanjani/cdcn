#include <stdio.h>
#include <ctype.h>
#include <string.h>
 
char *keywords[] = {
    "auto", "break", "case", "char", "const",
    "continue", "default", "do", "double", "else",
    "enum", "extern", "float", "for", "goto",
    "if", "int", "long", "register", "return",
    "short", "signed", "sizeof", "static", "struct",
    "switch", "typedef", "union", "unsigned", "void",
    "volatile", "while"
};

int keywordCount = sizeof(keywords) / sizeof(keywords[0]);

// Function to check whether a string is a keyword
int isKeyword(char str[]) {
    for (int i = 0; i < keywordCount; i++) {
        if (strcmp(str, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

int main() {
    FILE *fp;
    char ch, next;
    char buffer[32];
    int i;

    fp = fopen("input.c", "r");

    if (fp == NULL) {
        printf("Error: Cannot open input.c\n");
        return 1;
    }

    printf("------ TOKENS ------\n\n");

    while ((ch = fgetc(fp)) != EOF) {

        // Ignore spaces, tabs and newlines
        if (isspace(ch))
            continue;

        // Ignore comments
        if (ch == '/') {
            next = fgetc(fp);

            // Single-line comment
            if (next == '/') {
                while ((ch = fgetc(fp)) != '\n' && ch != EOF);
                continue;
            }

            // Multi-line comment
            else if (next == '*') {
                char prev = 0;
                while ((ch = fgetc(fp)) != EOF) {
                    if (prev == '*' && ch == '/')
                        break;
                    prev = ch;
                }
                continue;
            }

            // Division operator
            else {
                printf("Operator   : /\n");
                fseek(fp, -1, SEEK_CUR);
                continue;
            }
        } 

        // Identifier or Keyword
        if (isalpha(ch) || ch == '_') {
            i = 0;
            buffer[i++] = ch;

            while ((ch = fgetc(fp)) != EOF &&
                   (isalnum(ch) || ch == '_')) {

                if (i < 31)
                    buffer[i++] = ch;
            }

            buffer[i] = '\0';

            if (ch != EOF)
                fseek(fp, -1, SEEK_CUR);

            if (isKeyword(buffer))
                printf("Keyword    : %s\n", buffer);
            else
                printf("Identifier : %s\n", buffer);

            continue;
        }

        // Number
        if (isdigit(ch)) {
            i = 0;
            buffer[i++] = ch;

            while ((ch = fgetc(fp)) != EOF &&
                   (isdigit(ch) || ch == '.')) {

                if (i < 31)
                    buffer[i++] = ch;
            }

            buffer[i] = '\0';

            if (ch != EOF)
                fseek(fp, -1, SEEK_CUR);

            printf("Number     : %s\n", buffer);
            continue;
        }

        // Operators
        if (strchr("+-*=<>!%&|^~", ch)) {
            printf("Operator   : %c\n", ch);
            continue;
        }

        // Delimiters
        if (strchr(";,(){}[]", ch)) {
            printf("Delimiter  : %c\n", ch);
            continue;
        }

        // String literals
        if (ch == '"') {
            printf("String     : \"");
            while ((ch = fgetc(fp)) != '"' && ch != EOF)
                putchar(ch);
            printf("\"\n");
            continue;
        }

        // Character literals
        if (ch == '\'') {
            printf("Character  : '");
            while ((ch = fgetc(fp)) != '\'' && ch != EOF)
                putchar(ch);
            printf("'\n");
            continue;
        }

        // Invalid characters
        printf("Invalid Character : %c\n", ch);
    }

    fclose(fp);

    return 0;
}










// #include <stdio.h>
// #include <string.h>
// #include <ctype.h>

// #define MAX_ID_LEN 20

// int isKeyword(char word[])
// {
//     char keywords[][20] = {
//         "int", "float", "char", "if", "else",
//         "while", "for", "return", "void"
//     };

//     int n = 9;

//     for (int i = 0; i < n; i++)
//     {
//         if (strcmp(word, keywords[i]) == 0)
//             return 1;
//     }

//     return 0;
// }

// int isOperator(char ch)
// {
//     return (ch == '+' || ch == '-' || ch == '*' ||
//             ch == '/' || ch == '=' || ch == '<' ||
//             ch == '>' || ch == '%');
// }

// int isSpecialSymbol(char ch)
// {
//     return (ch == '(' || ch == ')' ||
//             ch == '{' || ch == '}' ||
//             ch == '[' || ch == ']' ||
//             ch == ';' || ch == ',' ||
//             ch == '.');
// }

// int main()
// {
//     FILE *fp;
//     char ch;

//     fp = fopen("input.c", "r");

//     if (fp == NULL)
//     {
//         printf("Unable to open input.c\n");
//         return 1;
//     }

//     while ((ch = fgetc(fp)) != EOF)
//     {
//         // Ignore spaces, tabs and newlines
//         if (isspace(ch))
//             continue;

//         // Comments
//         if (ch == '/')
//         {
//             char next = fgetc(fp);

//             // Single-line comment
//             if (next == '/')
//             {
//                 while ((ch = fgetc(fp)) != EOF && ch != '\n')
//                     ;

//                 continue;
//             }

//             // Multi-line comment
//             if (next == '*')
//             {
//                 char prev = '\0';

//                 while ((ch = fgetc(fp)) != EOF)
//                 {
//                     if (prev == '*' && ch == '/')
//                         break;

//                     prev = ch;
//                 }

//                 continue;
//             }

//             // If it was just '/', put next character back
//             ungetc(next, fp);
//             printf("/ : OPERATOR\n");
//             continue;
//         }

//         // Identifier or keyword
//         if (isalpha(ch) || ch == '_')
//         {
//             char word[MAX_ID_LEN + 1];
//             int i = 0;

//             do
//             {
//                 if (i < MAX_ID_LEN)
//                     word[i++] = ch;

//                 ch = fgetc(fp);

//             } while (isalnum(ch) || ch == '_');

//             word[i] = '\0';

//             // Put back the character that is not part of the word
//             ungetc(ch, fp);

//             if (isKeyword(word))
//                 printf("%s : KEYWORD\n", word);
//             else
//                 printf("%s : IDENTIFIER\n", word);

//             continue;
//         }

//         // Number
//         if (isdigit(ch))
//         {
//             char number[50];
//             int i = 0;

//             do
//             {
//                 number[i++] = ch;
//                 ch = fgetc(fp);

//             } while (isdigit(ch) || ch == '.');

//             number[i] = '\0';

//             ungetc(ch, fp);

//             printf("%s : NUMBER\n", number);

//             continue;
//         }

//         // Operators
//         if (isOperator(ch))
//         {
//             char next = fgetc(fp);[]

//             if ((ch == '=' && next == '=') ||
//                 (ch == '<' && next == '=') ||
//                 (ch == '>' && next == '=') ||
//                 (ch == '!' && next == '=') ||
//                 (ch == '+' && next == '+') ||
//                 (ch == '-' && next == '-'))
//             {
//                 printf("%c%c : OPERATOR\n", ch, next);
//             }
//             else
//             {
//                 printf("%c : OPERATOR\n", ch);
//                 ungetc(next, fp);
//             }

//             continue;
//         }

//         // Special symbols
//         if (isSpecialSymbol(ch))
//         {
//             printf("%c : SPECIAL SYMBOL\n", ch);
//             continue;
//         }

//         // Unknown symbol
//         printf("%c : UNKNOWN SYMBOL\n", ch);
//     }

//     fclose(fp);

//     return 0;
// }




