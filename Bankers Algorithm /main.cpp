/*
Criteria = Resource Allocation
Mode = Banker's Algorithm (Safety Algorithm)
*/

#include <iostream>

using namespace std;

#define el "\n"
#define td "\t"

int main() {
    int maxR[3] = {10, 5, 7};  // Maximum available resources
    int alloc[5][3] = {{0, 1, 0}, {2, 0, 0}, {3, 0, 2}, {2, 1, 1}, {0, 0, 2}};  // Allocated resources
    int max[5][3] = {{7, 5, 3}, {3, 2, 2}, {9, 0, 2}, {2, 2, 2}, {4, 3, 3}};  // Maximum required resources

    int need[5][3];  // Need matrix
    int available[3] = {3, 3, 2};  // Initially available resources

    // Calculate need matrix
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    int vis[5] = {-1, -1, -1, -1, -1};  // Track visited processes
    int seq[5] = {-1, -1, -1, -1, -1};  // Store the safe sequence
    int index = 0;

    // Banker's Algorithm
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (vis[j] == -1 && (need[j][0] <= available[0]) && (need[j][1] <= available[1]) && (need[j][2] <= available[2])) {
                vis[j] = j;
                seq[index++] = j;
                for (int k = 0; k < 3; k++) {
                    available[k] += alloc[j][k];
                }
                break;
            }
        }
    }

    int i = 0;
    for (i = 0; i < 5; i++) {
        if (seq[i] == -1) {
            cout << "Sequence is invalid" << el;
            break;
        }
    }

    if (i == 5) {
        cout << "Sequence is: ";
        for (int i = 0; i < 5; i++) {
            cout << "P" << seq[i] << " ";
        }
        cout << el;
    }

    return 0;
}
