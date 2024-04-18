/*
Criteria = Burst Time
Mode = Non-Preemption (A process won't be preempted until it is completed)
*/


#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>

using namespace std;

#define el "\n"
#define td "\t"

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int start_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

bool compareArrival(const Process &a, const Process &b) {
    return a.arrival_time < b.arrival_time;
}

bool compareBurst(const Process &a, const Process &b) {
    return a.burst_time < b.burst_time;
}

int main() {
    int num_processes;
    vector<Process> processes;
    cout << "---------------------------------------------------------" << el;

    cout << "Enter the number of processes: ";
    cin >> num_processes;
    cout << "----------------------------------------------" << el;

    processes.resize(num_processes);

    cout << "Enter arrival time and burst time of each process:" << el;
    for(int i = 0; i < num_processes; i++) {
        cout << "Process " << i + 1 << " (Arrival Time Burst Time): ";
        cin >> processes[i].arrival_time >> processes[i].burst_time;
        processes[i].id = i + 1;
    }
    
    cout << "---------------------------------------------------------" << el;

    sort(processes.begin(), processes.end(), compareArrival);

    int current_time = 0;

    for(int i = 0; i < num_processes; i++) {
        current_time = max(current_time, processes[i].arrival_time);
        int shortest_burst_idx = -1;
        int shortest_burst_time = INT_MAX;
        for(int j = i; j < num_processes; j++) {
            if(processes[j].arrival_time <= current_time) {
                if(processes[j].burst_time < shortest_burst_time) {
                    shortest_burst_time = processes[j].burst_time;
                    shortest_burst_idx = j;
                }
            } else {
                break;
            }
        }

        if(shortest_burst_idx != -1) {
            swap(processes[i], processes[shortest_burst_idx]);
        }

        processes[i].start_time = current_time;
        processes[i].completion_time = current_time + processes[i].burst_time;
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;

        current_time = processes[i].completion_time;
    }

    cout << "Process" << td << "Arrival Time" << td << "Burst Time" << td << "Completion Time" << td << "Turnaround Time" << td << "Waiting Time" << el;
    cout << "----------------------------------------------" << el;
    for (int i = 0; i < num_processes; i++) {
        cout << processes[i].id << td << processes[i].arrival_time << td << processes[i].burst_time << td << processes[i].completion_time << td << processes[i].turnaround_time << td << processes[i].waiting_time << el;
    }
    cout << "----------------------------------------------" << el;

    return 0;
}
