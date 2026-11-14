#include <stdio.h>

#define N 5
#define P 8

// Non-terminals: E, E', T, T', F
// Terminals: +, *, (, ), id, epsilon, $

char *symbols[] = {"E", "E'", "T", "T'", "F",
                   "+", "*", "(", ")", "id", "ε", "$"};

int first[N][12] = {0};
int follow[N][12] = {0};

struct Production {
    int lhs;
    int rhs[4];
    int len;
};

struct Production grammar[P] = {
    {0, {2, 1}, 2},       // E -> T E'
    {1, {5, 2, 1}, 3},    // E' -> + T E'
    {1, {10}, 1},         // E' -> ε
    {2, {4, 3}, 2},       // T -> F T'
    {3, {6, 4, 3}, 3},    // T' -> * F T'
    {3, {10}, 1},         // T' -> ε
    {4, {7, 0, 8}, 3},    // F -> ( E )
    {4, {9}, 1}           // F -> id
};

int isTerminal(int x) {
    return x >= 5;
}

void computeFirst() {
    int changed, i, j, k;

    do {
        changed = 0;

        for (i = 0; i < P; i++) {
            int lhs = grammar[i].lhs;
            int nullable = 1;

            for (j = 0; j < grammar[i].len; j++) {
                int s = grammar[i].rhs[j];

                if (isTerminal(s)) {
                    if (!first[lhs][s]) {
                        first[lhs][s] = 1;
                        changed = 1;
                    }

                    if (s != 10)
                        nullable = 0;

                    break;
                }

                for (k = 0; k < 12; k++) {
                    if (k != 10 && first[s][k] && !first[lhs][k]) {
                        first[lhs][k] = 1;
                        changed = 1;
                    }
                }

                if (!first[s][10]) {
                    nullable = 0;
                    break;
                }
            }

            if (nullable && !first[lhs][10]) {
                first[lhs][10] = 1;
                changed = 1;
            }
        }

    } while (changed);
}

void computeFollow() {
    int changed, i, j, k;

    follow[0][11] = 1;  // $ in FOLLOW(E)

    do {
        changed = 0;

        for (i = 0; i < P; i++) {
            int lhs = grammar[i].lhs;

            for (j = 0; j < grammar[i].len; j++) {
                int B = grammar[i].rhs[j];

                if (isTerminal(B))
                    continue;

                int nullable = 1;

                for (k = j + 1; k < grammar[i].len; k++) {
                    int s = grammar[i].rhs[k];

                    if (isTerminal(s)) {
                        if (!follow[B][s]) {
                            follow[B][s] = 1;
                            changed = 1;
                        }

                        nullable = (s == 10);
                        break;
                    }

                    int m;
                    for (m = 0; m < 12; m++) {
                        if (m != 10 && first[s][m] && !follow[B][m]) {
                            follow[B][m] = 1;
                            changed = 1;
                        }
                    }

                    if (!first[s][10]) {
                        nullable = 0;
                        break;
                    }
                }

                if (nullable) {
                    for (k = 0; k < 12; k++) {
                        if (follow[lhs][k] && !follow[B][k]) {
                            follow[B][k] = 1;
                            changed = 1;
                        }
                    }
                }
            }
        }

    } while (changed);
}

void display() {
    int i, j;

    printf("\nFIRST SETS:\n");

    for (i = 0; i < N; i++) {
        printf("FIRST(%s) = { ", symbols[i]);

        for (j = 5; j <= 10; j++) {
            if (first[i][j])
                printf("%s ", symbols[j]);
        }

        printf("}\n");
    }

    printf("\nFOLLOW SETS:\n");

    for (i = 0; i < N; i++) {
        printf("FOLLOW(%s) = { ", symbols[i]);

        for (j = 5; j <= 11; j++) {
            if (follow[i][j])
                printf("%s ", symbols[j]);
        }

        printf("}\n");
    }
}

int main() {
    computeFirst();
    computeFollow();
    display();

    return 0;
}