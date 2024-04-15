#include <iostream>
#include <unordered_set>
#include <queue>

using namespace std;

// Function to find page faults using FIFO
int pageFaults(int pages[], int n, int capacity) {
    // To represent the set of current pages, using unordered_set for quick lookups
    unordered_set<int> s;

    // To store the pages in FIFO manner
    queue<int> indexes;

    // Start from the initial page
    int page_faults = 0;
    for (int i = 0; i < n; i++) {
        // Check if the set can hold more pages
        if (s.size() < capacity) {
            // Insert it into the set if not already present, indicating a page fault
            if (s.find(pages[i]) == s.end()) {
                // Insert the current page into the set
                s.insert(pages[i]);

                // Increment page fault
                page_faults++;

                // Push the current page into the queue
                indexes.push(pages[i]);
            }
        } else {
            // If the set is full, perform FIFO
            if (s.find(pages[i]) == s.end()) {
                // Get the oldest page from the queue
                int val = indexes.front();

                // Pop the oldest page from the queue
                indexes.pop();

                // Remove the oldest page from the set
                s.erase(val);

                // Insert the current page into the set
                s.insert(pages[i]);

                // Push the current page into the queue
                indexes.push(pages[i]);

                // Increment page faults
                page_faults++;
            }
        }
    }

    return page_faults;
}

// Driver code
int main() {
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int n = sizeof(pages) / sizeof(pages[0]);
    int capacity = 4;
    cout << "Number of page faults using FIFO: " << pageFaults(pages, n, capacity) << endl;
    return 0;
}
 
