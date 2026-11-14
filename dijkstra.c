
#include <stdio.h>

#define INF 9999

int main()
{
    int n, source;
    int cost[10][10], dist[10], visited[10];
    int i, j, count, min, next;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter cost adjacency matrix:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            scanf("%d", &cost[i][j]);

            if (cost[i][j] == 0 && i != j)
                cost[i][j] = INF;
        }
    }

    printf("Enter source vertex: ");
    scanf("%d", &source);

    source--;

    for (i = 0; i < n; i++)
    {
        dist[i] = cost[source][i];
        visited[i] = 0;
    }

    dist[source] = 0;
    visited[source] = 1;

    count = 1;

    while (count < n)
    {
        min = INF;

        for (i = 0; i < n; i++)
        {
            if (dist[i] < min && !visited[i])
            {
                min = dist[i];
                next = i;
            }
        }

        visited[next] = 1;

        for (i = 0; i < n; i++)
        {
            if (!visited[i] && min + cost[next][i] < dist[i])
            {
                dist[i] = min + cost[next][i];
            }
        }

        count++;
    }

    printf("\nShortest distances from source %d:\n", source + 1);

    for (i = 0; i < n; i++)
    {
        printf("To vertex %d = %d\n", i + 1, dist[i]);
    }

    return 0;
}
