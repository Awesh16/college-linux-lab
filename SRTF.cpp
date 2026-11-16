//preemptive in nature
//criteria = shortest burst time
#include <iostream>
using namespace std;

int main()
{
    int n;

    cout << "Enter number of processes: ";
    cin >> n;

    int processes[n], burstTime[n], arrivalTime[n];
    int remainingTime[n], waitingTime[n];
    int turnAroundTime[n], completionTime[n];

    cout << "Enter arrival time and burst time for each process:\n";

    for (int i = 0; i < n; i++)
    {
        processes[i] = i + 1;

        cout << "P" << processes[i] << " Arrival Time: ";
        cin >> arrivalTime[i];

        cout << "P" << processes[i] << " Burst Time: ";
        cin >> burstTime[i];

        remainingTime[i] = burstTime[i];
        waitingTime[i] = 0;
        turnAroundTime[i] = 0;
        completionTime[i] = 0;
    }

    int completed = 0;
    int currentTime = 0;

    while (completed != n)
    {
        int shortest = -1;
        int minimum = 9999;

        // Find process with shortest remaining time
        for (int i = 0; i < n; i++)
        {
            if (arrivalTime[i] <= currentTime &&
                remainingTime[i] > 0 &&
                remainingTime[i] < minimum)
            {
                minimum = remainingTime[i];
                shortest = i;
            }
        }

        // If no process has arrived
        if (shortest == -1)
        {
            currentTime++;
            continue;
        }

        // Execute process for 1 unit
        remainingTime[shortest]--;
        currentTime++;

        // If process is completed
        if (remainingTime[shortest] == 0)
        {
            completed++;

            // Store completion time
            completionTime[shortest] = currentTime;

            // Calculate turnaround time
            turnAroundTime[shortest] =
                completionTime[shortest] - arrivalTime[shortest];

            // Calculate waiting time
            waitingTime[shortest] =
                turnAroundTime[shortest] - burstTime[shortest];
        }
    }

    int totalWaitingTime = 0;
    int totalTurnAroundTime = 0;

    cout << "\nProcess\tAT\tBT\tCT\tWT\tTAT\n";

    for (int i = 0; i < n; i++)
    {
        totalWaitingTime += waitingTime[i];
        totalTurnAroundTime += turnAroundTime[i];

        cout << "P" << processes[i] << "\t"
             << arrivalTime[i] << "\t"
             << burstTime[i] << "\t"
             << completionTime[i] << "\t"
             << waitingTime[i] << "\t"
             << turnAroundTime[i] << endl;
    }

    cout << "\nAverage Waiting Time = "
         << (float)totalWaitingTime / n;

    cout << "\nAverage Turnaround Time = "
         << (float)totalTurnAroundTime / n << endl;

    return 0;
}
