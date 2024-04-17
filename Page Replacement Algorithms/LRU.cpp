#include <iostream>
#include <bits/stdc++.h>

using namespace std;

// Globally declared vector for storing pages
vector<int> page;

// Function to check if a page is present in the frames or not
bool pagePresent(int pageNo, vector<int> page_frames) {
    return find(page_frames.begin(), page_frames.end(), pageNo) != page_frames.end();
}

// Function to find the least recently used page
int findLeastRecentlyUsedPage(vector<int> page_frames, unordered_map<int, int>& page_access_time) {
    int lru_page = -1;
    int min_access_time = INT_MAX;
    for (int page : page_frames) {
        if (page_access_time[page] < min_access_time) {
            min_access_time = page_access_time[page];
            lru_page = page;
        }
    }
    return lru_page;
}

int main() {
    int FRAME_SIZE, PAGES;
    cout << "LRU Page Replacement Algorithm\n ----------------------------------------------------------\n";
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
    unordered_map<int, int> page_access_time;
    int current_time = 0;
    for (int i = 0; i < PAGES; i++) {
        if (!pagePresent(page[i], page_frames)) {
            page_faults++;
            int page_to_replace = findLeastRecentlyUsedPage(page_frames, page_access_time);
            if (page_to_replace != -1) {
                // Replace the least recently used page
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
            page_access_time[page[i]] = current_time++;
        } else {
            page_hits++;
            page_access_time[page[i]] = current_time++;
        }
    }
    cout << "Page Faults: " << page_faults << "\n";
    cout << "Page Hits: " << page_hits << "\n";
    return 0;
}