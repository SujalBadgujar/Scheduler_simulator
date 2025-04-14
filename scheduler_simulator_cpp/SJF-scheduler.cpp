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
    bool done = false;
};

int main()
{
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);
    vector<int> schedule_order;

    for (int i = 0; i < n; i++)
    {
        p[i].pid = i + 1;
        cout << "Enter arrival time for P" << i + 1 << ": ";
        cin >> p[i].arrival_time;
        cout << "Enter burst time for P" << i + 1 << ": ";
        cin >> p[i].burst_time;
    }

    int completed = 0, current_time = 0, total_burst = 0;
    while (completed < n)
    {
        int idx = -1, min_burst = 1e9;

        for (int i = 0; i < n; i++)
        {
            if (!p[i].done && p[i].arrival_time <= current_time && p[i].burst_time < min_burst)
            {
                min_burst = p[i].burst_time;
                idx = i;
            }
        }

        if (idx == -1)
        {
            current_time++;
            continue;
        }

        p[idx].completion_time = current_time + p[idx].burst_time;
        p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
        p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
        current_time = p[idx].completion_time;
        p[idx].done = true;
        completed++;
        total_burst += p[idx].burst_time;
        schedule_order.push_back(p[idx].pid);
    }

    cout << "\nPID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n";
    for (auto &proc : p)
    {
        cout << "P" << proc.pid << "\t" << proc.arrival_time << "\t"
             << proc.burst_time << "\t" << proc.completion_time << "\t\t"
             << proc.turnaround_time << "\t\t" << proc.waiting_time << endl;
    }
    cout << "\nOrder of execution: ";
    for (int pid : schedule_order)
    {
        cout << "P" << pid << " ";
    }
    cout << endl;

    // Metrics
    float total_tat = 0, total_wt = 0;
    for (auto &proc : p)
    {
        total_tat += proc.turnaround_time;
        total_wt += proc.waiting_time;
    }

    float avg_tat = total_tat / n;
    float avg_wt = total_wt / n;
    int total_time = (*max_element(p.begin(), p.end(), [](auto a, auto b)
                                   { return a.completion_time < b.completion_time; }))
                         .completion_time -
                     (*min_element(p.begin(), p.end(), [](auto a, auto b)
                                   { return a.arrival_time < b.arrival_time; }))
                         .arrival_time;

    float cpu_util = ((float)total_burst / total_time) * 100;
    float io_util = 100 - cpu_util;

    cout << "\nAverage Turnaround Time: " << avg_tat;
    cout << "\nAverage Waiting Time   : " << avg_wt;
    cout << "\nCPU Utilization        : " << cpu_util << "%";
    cout << "\nI/O Utilization        : " << io_util << "%\n";

    return 0;
}
