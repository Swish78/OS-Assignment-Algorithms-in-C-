#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>

using namespace std;

#define el "\n"
#define td "\t"

int disk_size = 200;

vector<int> scheduleDiskRequests(vector<int>& requests, int initial_head) {
    vector<int> sequence;
    int total_head_movement = 0;
    int current_head = initial_head;

    sequence.push_back(current_head);

    while (!requests.empty()) {
        int shortest_distance = INT_MAX;
        int closest_request_idx = -1;

        for (int i = 0; i < requests.size(); i++) {
            int distance = abs(requests[i] - current_head);
            if (distance < shortest_distance) {
                shortest_distance = distance;
                closest_request_idx = i;
            }
        }

        if (closest_request_idx != -1) {
            int request = requests[closest_request_idx];
            total_head_movement += abs(request - current_head);
            current_head = request;
            sequence.push_back(current_head);
            requests.erase(requests.begin() + closest_request_idx);
        }
    }

    cout << "Total Head Movement: " << total_head_movement << el;
    cout << "Sequence of Disk Head Movements: ";
    for (int position : sequence) {
        cout << position << " ";
    }
    cout << el;

    return sequence;
}

int main() {
    cout << "--------------------------------------------------" << el;
    int initial_head, sequence_size;
    cout << "Enter Number of Track Sequences: ";
    cin >> sequence_size;

    vector<int> sequences(sequence_size);
    cout << "------------------------------" << el;
    cout << "Enter Track Sequence: " << el;
    for (int i = 0; i < sequence_size; i++) {
        cout << "Enter Sequence " << i + 1 << ": " << td;
        cin >> sequences[i];
    }

    cout << "--------------------------------------" << el;
    cout << "Enter Initial Head Position: ";
    cin >> initial_head;

    vector<int> sequence = scheduleDiskRequests(sequences, initial_head);

    return 0;
}
