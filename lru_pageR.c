
#include <stdio.h>

int main()
{
    int n, capacity;
    int pages[50], frames[20], time[20];
    int i, j, pos, min;
    int faults = 0, hits = 0;
    int found, counter = 0;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter reference string: ");
    for (i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &capacity);

    for (i = 0; i < capacity; i++)
    {
        frames[i] = -1;
        time[i] = 0;
    }

    printf("\nPage\tFrames\t\tStatus\n");

    for (i = 0; i < n; i++)
    {
        found = 0;
        counter++;

        for (j = 0; j < capacity; j++)
        {
            if (frames[j] == pages[i])
            {
                found = 1;
                time[j] = counter;
                hits++;
                break;
            }
        }

        if (!found)
        {
            pos = -1;

            for (j = 0; j < capacity; j++)
            {
                if (frames[j] == -1)
                {
                    pos = j;
                    break;
                }
            }

            if (pos == -1)
            {
                min = time[0];
                pos = 0;

                for (j = 1; j < capacity; j++)
                {
                    if (time[j] < min)
                    {
                        min = time[j];
                        pos = j;
                    }
                }
            }

            frames[pos] = pages[i];
            time[pos] = counter;
            faults++;
        }

        printf("%d\t", pages[i]);

        for (j = 0; j < capacity; j++)
        {
            if (frames[j] == -1)
                printf("- ");
            else
                printf("%d ", frames[j]);
        }

        if (found)
            printf("\tHit");
        else
            printf("\tPage Fault");

        printf("\n");
    }

    printf("\nTotal Page Faults = %d", faults);
    printf("\nTotal Page Hits = %d\n", hits);

    return 0;
}
