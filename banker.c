
#include <stdio.h>

int main()
{
    int n, m;
    int alloc[10][10], max[10][10];
    int need[10][10], avail[10];
    int finish[10] = {0};
    int safe[10];
    int i, j, k, count = 0, found;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &m);

    printf("\nEnter Allocation Matrix:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);
    }

    printf("\nEnter Maximum Matrix:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
            scanf("%d", &max[i][j]);
    }

    printf("\nEnter Available Resources:\n");
    for (j = 0; j < m; j++)
        scanf("%d", &avail[j]);

    // Calculate Need Matrix
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];
    }

    printf("\nNeed Matrix:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
            printf("%d ", need[i][j]);

        printf("\n");
    }

    // Banker's Algorithm
    while (count < n)
    {
        found = 0;

        for (i = 0; i < n; i++)
        {
            if (finish[i] == 0)
            {
                for (j = 0; j < m; j++)
                {
                    if (need[i][j] > avail[j])
                        break;
                }

                if (j == m)
                {
                    for (k = 0; k < m; k++)
                        avail[k] += alloc[i][k];

                    safe[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if (found == 0)
            break;
    }

    // Check Safe State
    if (count == n)
    {
        printf("\nSystem is in SAFE STATE");
        printf("\nSafe Sequence: ");

        for (i = 0; i < n; i++)
            printf("P%d ", safe[i]);
    }
    else
    {
        printf("\nSystem is in UNSAFE STATE");
    }

    printf("\n");

    return 0;
}
