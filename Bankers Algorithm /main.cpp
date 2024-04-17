#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Number of processes and resources
int num_processes, num_resources;

// Available resources
vector<int> available;

// Maximum resources needed by each process
vector<vector<int>> max_need;

// Resources currently allocated to each process
vector<vector<int>> allocation;

// Resources still needed by each process
vector<vector<int>> need;

// Safety sequence
vector<int> safe_sequence;

// Function to check if the system is in a safe state
bool is_safe() {
    vector<bool> finished(num_processes, false);
    int count = 0;

    while (count < num_processes) {
        bool found = false;
        for (int i = 0; i < num_processes; i++) {
            if (!finished[i]) {
                bool can_allocate = true;
                for (int j = 0; j < num_resources; j++) {
                    if (need[i][j] > available[j]) {
                        can_allocate = false;
                        break;
                    }
                }
                if (can_allocate) {
                    for (int j = 0; j < num_resources; j++) {
                        available[j] += allocation[i][j];
                    }
                    finished[i] = true;
                    safe_sequence.push_back(i);
                    count++;
                    found = true;
                    break;
                }
            }
        }
        if (!found) {
            return false;
        }
    }

    return true;
}

int main() {
    cout << "Banker's Algorithm\n ----------------------------------------------------------\n";

    // Get the number of processes and resources
    cout << "Enter the number of processes: ";
    cin >> num_processes;
    cout << "Enter the number of resources: ";
    cin >> num_resources;

    // Get the available resources
    cout << "Enter the available resources (separated by spaces): ";
    available.resize(num_resources);
    for (int i = 0; i < num_resources; i++) {
        cin >> available[i];
    }

    // Get the maximum resources needed by each process
    max_need.resize(num_processes, vector<int>(num_resources, 0));
    cout << "Enter the maximum resources needed by each process:\n";
    for (int i = 0; i < num_processes; i++) {
        cout << "Process " << i << ": ";
        for (int j = 0; j < num_resources; j++) {
            cin >> max_need[i][j];
        }
    }

    // Get the resources currently allocated to each process
    allocation.resize(num_processes, vector<int>(num_resources, 0));
    cout << "Enter the resources currently allocated to each process:\n";
    for (int i = 0; i < num_processes; i++) {
        cout << "Process " << i << ": ";
        for (int j = 0; j < num_resources; j++) {
            cin >> allocation[i][j];
        }
    }

    // Calculate the resources still needed by each process
    need.resize(num_processes, vector<int>(num_resources, 0));
    for (int i = 0; i < num_processes; i++) {
        for (int j = 0; j < num_resources; j++) {
            need[i][j] = max_need[i][j] - allocation[i][j];
        }
    }

    // Check if the system is in a safe state
    if (is_safe()) {
        cout << "The system is in a safe state.\n";
        cout << "Safe sequence: ";
        for (int i = 0; i < safe_sequence.size(); i++) {
            cout << "P" << safe_sequence[i] << " ";
        }
        cout << "\n";
    } else {
        cout << "The system is not in a safe state.\n";
    }

    return 0;
}

