#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define el "\n"
#define td "\t"

int disk_size = 200;

vector<int> scheduleDiskRequests(vector<int>& requests, int initial_head, string direction) {
    vector<int> seek_sequence;
    int seek_count = 0;
    int current_track;

    vector<int> left, right;

    // Append end values for the initial direction
    if (direction == "left") {
        left.push_back(0);
    } else if (direction == "right") {
        right.push_back(disk_size - 1);
    }

    // Divide the requests into left and right vectors
    for (int request : requests) {
        if (request < initial_head) {
            left.push_back(request);
        } else if (request > initial_head) {
            right.push_back(request);
        }
    }

    // Sort the left and right vectors
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    int head = initial_head;

    // Perform two scans: one in the initial direction and one in the opposite direction
    for (int run = 0; run < 2; run++) {
        if (direction == "left") {
            for (int i = left.size() - 1; i >= 0; i--) {
                current_track = left[i];
                seek_sequence.push_back(current_track);
                seek_count += abs(current_track - head);
                head = current_track;
            }
            direction = "right";
        } else if (direction == "right") {
            for (int i = 0; i < right.size(); i++) {
                current_track = right[i];
                seek_sequence.push_back(current_track);
                seek_count += abs(current_track - head);
                head = current_track;
            }
            direction = "left";
        }
    }

    cout << "Total number of seek operations = " << seek_count << el;
    cout << "Seek Sequence is" << el;
    for (int position : seek_sequence) {
        cout << position << el;
    }

    return seek_sequence;
}

int main() {
    int initial_head;
    vector<int> requests;
    string direction;
    int request;

    cout << "Enter the initial head position: ";
    cin >> initial_head;

    cout << "Enter the initial direction (left/right): ";
    cin >> direction;

    cout << "Enter the disk requests (terminate with -1): " << el;
    while (true) {
        cin >> request;
        if (request == -1) {
            break;
        }
        requests.push_back(request);
    }

    scheduleDiskRequests(requests, initial_head, direction);

    return 0;
}