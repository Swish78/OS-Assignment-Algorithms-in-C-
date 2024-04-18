/*
Criteria = Arrival Time
Mode = Non-Preemption (A process won't be preempted until it is completed)
*/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

#define el "\n"
#define td "\t"

int main() {
    cout << "First-In-First-Out (FIFO) Scheduling Algorithm" << el;
    cout << "------------------------------------------------------" << el;

    int num_processes;
    cout << "Enter the number of processes: ";
    cin >> num_processes;
    cout << "----------------------------------------------" << el;

    vector<int> arrival_times(num_processes);
    vector<int> burst_times(num_processes);

    cout << "Enter the arrival times for each process:" << el;
    for (int i = 0; i < num_processes; i++) {
        cout << "Process " << i + 1 << ": ";
        cin >> arrival_times[i];
    }
    cout << "----------------------------------------------" << el;

    cout << "Enter the burst times for each process:" << el;
    for (int i = 0; i < num_processes; i++) {
        cout << "Process " << i + 1 << ": ";
        cin >> burst_times[i];
    }
    cout << "----------------------------------------------" << el;

    vector<int> completion_times(num_processes);
    vector<int> turnaround_times(num_processes);
    vector<int> waiting_times(num_processes);

    // Logic for FIFO
    int current_time = 0;
    for (int i = 0; i < num_processes; i++) {
        if (arrival_times[i] > current_time) {
            current_time = arrival_times[i];
        }
        completion_times[i] = current_time + burst_times[i];
        turnaround_times[i] = completion_times[i] - arrival_times[i];
        waiting_times[i] = turnaround_times[i] - burst_times[i];
        current_time = completion_times[i];
    }

    cout << "Process" << td << "Arrival Time" << td << "Burst Time" << td << "Completion Time" << td << "Turnaround Time" << td << "Waiting Time" << el;
    cout << "----------------------------------------------" << el;
    for (int i = 0; i < num_processes; i++) {
        cout << "Process " << i + 1 << td << arrival_times[i] << td << burst_times[i] << td << completion_times[i] << td << turnaround_times[i] << td << waiting_times[i] << el;
    }
    cout << "----------------------------------------------" << el;

    return 0;
}