#include <iostream>
#include <vector>
#include <limits>

using namespace std;

#define el "\n"
#define td "\t"

vector<int> scheduleDiskRequests(vector<int>& requests, int initial_head) {
    vector<int> sequence;
    int total_head_movement = 0;
    int current_head = initial_head;

    sequence.push_back(current_head);

    for (int request : requests) {
        total_head_movement += abs(request - current_head);
        current_head = request;
        sequence.push_back(current_head);
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
    int initial_head;
    vector<int> requests;

    cout << "Enter the initial head position: ";
    cin >> initial_head;

    cout << "Enter the disk requests (terminate with -1): " << el;
    int request;
    while (true) {
        cin >> request;
        if (request == -1) {
            break;
        }
        requests.push_back(request);
    }

    scheduleDiskRequests(requests, initial_head);

    return 0;
}