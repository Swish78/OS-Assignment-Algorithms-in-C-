#include <iostream>
#include <bits/stdc++.h>

using namespace std;

// Globally declared vector for storing pages
vector<int> page;

// Function to check if a page is present in the frames or not
bool pagePresent(int pageNo, vector<int> page_frames) {
    return find(page_frames.begin(), page_frames.end(), pageNo) != page_frames.end();
}

// Function to find the page that will not be used for the longest time
int findPageToReplace(vector<int> page_frames, vector<int> pages, int index) {
    int max_time = 0, page_to_replace = -1;
    for (int i = 0; i < page_frames.size(); i++) {
        int time = 0;
        for (int j = index; j < pages.size(); j++) {
            if (pages[j] == page_frames[i]) {
                break;
            }
            time++;
        }
        if (time > max_time) {
            max_time = time;
            page_to_replace = page_frames[i];
        }
    }
    return page_to_replace;
}

int main() {
    int FRAME_SIZE, PAGES;
    cout << "Optimal Page Replacement Algorithm\n ----------------------------------------------------------\n";
    cout << "Enter the number of pages in the process: ";
    cin >> PAGES;
    page.resize(PAGES);
    cout << "-------------\n";
    for (int i = 0; i < PAGES; i++) {
        cout << "Enter the page number: " << i + 1 << ": ";
        cin >> page[i];
    }
    cout << "-------------\n";
    cout << "Enter the number of frames: ";
    cin >> FRAME_SIZE;
    cout << "-------------\n";
    int page_faults = 0, page_hits = 0;
    int frame_to_replace_index = 0;
    vector<int> page_frames(FRAME_SIZE, -1);
    for (int i = 0; i < PAGES; i++) {
        if (!pagePresent(page[i], page_frames)) {
            page_faults++;
            int page_to_replace = findPageToReplace(page_frames, page, i);
            if (page_to_replace != -1) {
                // Replace the page that will not be used for the longest time
                for (int j = 0; j < page_frames.size(); j++) {
                    if (page_frames[j] == page_to_replace) {
                        page_frames[j] = page[i];
                        break;
                    }
                }
            } else {
                // If no page can be replaced, use FIFO
                page_frames[frame_to_replace_index] = page[i];
                frame_to_replace_index = (frame_to_replace_index + 1) % FRAME_SIZE;
            }
        } else {
            page_hits++;
        }
    }
    cout << "Page Faults: " << page_faults << "\n";
    cout << "Page Hits: " << page_hits << "\n";
    return 0;
}