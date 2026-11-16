// criteria first basis
// mode = non-preemptive

#include <iostream>
using namespace std;

// Function to calculate completion time
void findCompletionTime(int n, int at[], int bt[], int ct[])
{
    ct[0] = at[0] + bt[0];

    for (int i = 1; i < n; i++)
        ct[i] = ct[i - 1] + bt[i];
}

// Function to calculate turnaround time
void findTurnAroundTime(int n, int at[], int ct[], int tat[])
{
    for (int i = 0; i < n; i++)
        tat[i] = ct[i] - at[i];
}

// Function to calculate waiting time
void findWaitingTime(int n, int bt[], int tat[], int wt[])
{
    for (int i = 0; i < n; i++)
        wt[i] = tat[i] - bt[i];
}

// Function to calculate averages
void findAverageTime(int n, int at[], int bt[])
{
    int ct[n], wt[n], tat[n];

    findCompletionTime(n, at, bt, ct);
    findTurnAroundTime(n, at, ct, tat);
    findWaitingTime(n, bt, tat, wt);

    int total_wt = 0, total_tat = 0;

    cout << "\nProcess\tAT\tBT\tCT\tWT\tTAT\n";

    for (int i = 0; i < n; i++)
    {
        total_wt += wt[i];
        total_tat += tat[i];

        cout << "P" << i + 1 << "\t"
             << at[i] << "\t"
             << bt[i] << "\t"
             << ct[i] << "\t"
             << wt[i] << "\t"
             << tat[i] << endl;
    }

    cout << "\nAverage Waiting Time = "
         << (float)total_wt / n;

    cout << "\nAverage Turnaround Time = "
         << (float)total_tat / n << endl;
}

int main()
{
    int n;

    cout << "Enter number of processes: ";
    cin >> n;

    int at[n], bt[n];

    // Default arrival times: 0, 1, 2, 3...
    for (int i = 0; i < n; i++)
        at[i] = i;

    cout << "Enter burst times: ";

    for (int i = 0; i < n; i++)
        cin >> bt[i];

    findAverageTime(n, at, bt);

    return 0;
}
