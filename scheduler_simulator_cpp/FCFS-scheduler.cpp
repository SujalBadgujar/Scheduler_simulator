#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process
{
    int pid;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

int main()
{
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);

    for (int i = 0; i < n; i++)
    {
        p[i].pid = i + 1;
        cout << "Enter arrival time for P" << i + 1 << ": ";
        cin >> p[i].arrival_time;
        cout << "Enter burst time for P" << i + 1 << ": ";
        cin >> p[i].burst_time;
    }

    sort(p.begin(), p.end(), [](Process a, Process b)
{
    if (a.arrival_time == b.arrival_time)
        return a.pid < b.pid;  // Break ties using PID (or you can use burst time for SJF)
    return a.arrival_time < b.arrival_time;
});


    int current_time = 0;
    int total_burst = 0;

    for (int i = 0; i < n; i++)
    {
        if (current_time < p[i].arrival_time)
            current_time = p[i].arrival_time;

        p[i].completion_time = current_time + p[i].burst_time;
        p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
        p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;

        current_time = p[i].completion_time;
        total_burst += p[i].burst_time;
    }

    cout << "\nPID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n";
    for (auto &proc : p)
    {
        cout << "P" << proc.pid << "\t" << proc.arrival_time << "\t"
             << proc.burst_time << "\t" << proc.completion_time << "\t\t"
             << proc.turnaround_time << "\t\t" << proc.waiting_time << endl;
    }

    float total_tat = 0, total_wt = 0;
    for (int i = 0; i < n; i++)
    {
        total_tat += p[i].turnaround_time;
        total_wt += p[i].waiting_time;
    }

    float avg_tat = total_tat / n;
    float avg_wt = total_wt / n;

    int total_time = p[n - 1].completion_time - p[0].arrival_time;
    float cpu_util = ((float)total_burst / total_time) * 100;
    float io_util = 100 - cpu_util;

    cout << "\nAverage Turnaround Time: " << avg_tat;
    cout << "\nAverage Waiting Time   : " << avg_wt;
    cout << "\nCPU Utilization        : " << cpu_util << "%";
    cout << "\nI/O Utilization        : " << io_util << "%\n";

    return 0;
}
