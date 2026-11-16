// criterial :- time quantum
// mode :- preemtive

#include <iostream>
using namespace std;

int main()
{
    int n, quantum;

    cout << "Enter number of processes: ";
    cin >> n;

    int at[n], bt[n], rt[n];
    int ct[n], wt[n], tat[n];

    cout << "Enter Arrival Time and Burst Time:\n";

    for (int i = 0; i < n; i++)
    {
        cout << "P" << i + 1 << ": ";
        cin >> at[i] >> bt[i];

        rt[i] = bt[i];
    }

    cout << "Enter Time Quantum: ";
    cin >> quantum;

    if (n <= 0 || quantum <= 0)
    {
        cout << "Invalid input";
        return 0;
    }

    int q[n];
    int front = 0, rear = 0, count = 0;

    int time = 0, completed = 0, pos = 0;

    while (completed < n)
    {
        // Add arrived processes to ready queue
        while (pos < n && at[pos] <= time)
        {
            q[rear] = pos;
            rear = (rear + 1) % n;
            count++;
            pos++;
        }

        // If no process is available
        if (count == 0)
        {
            time++;
            continue;
        }

        // Select process from front
        int i = q[front];
        front = (front + 1) % n;
        count--;

        // Execute process
        if (rt[i] > quantum)
        {
            time += quantum;
            rt[i] -= quantum;
        }
        else
        {
            time += rt[i];
            rt[i] = 0;

            ct[i] = time;
            completed++;

            tat[i] = ct[i] - at[i];
            wt[i] = tat[i] - bt[i];
        }

        // Add newly arrived processes
        while (pos < n && at[pos] <= time)
        {
            q[rear] = pos;
            rear = (rear + 1) % n;
            count++;
            pos++;
        }

        // Add unfinished process to back
        if (rt[i] > 0)
        {
            q[rear] = i;
            rear = (rear + 1) % n;
            count++;
        }
    }

    int totalWT = 0, totalTAT = 0;

    cout << "\nProcess\tAT\tBT\tCT\tWT\tTAT\n";

    for (int i = 0; i < n; i++)
    {
        totalWT += wt[i];
        totalTAT += tat[i];

        cout << "P" << i + 1 << "\t"
             << at[i] << "\t"
             << bt[i] << "\t"
             << ct[i] << "\t"
             << wt[i] << "\t"
             << tat[i] << endl;
    }

    cout << "\nAverage Waiting Time = "
         << (float)totalWT / n;

    cout << "\nAverage Turnaround Time = "
         << (float)totalTAT / n << endl;

    return 0;
}
