#include<bits/stdc++.h>
using namespace std;

void look(vector<int> requests, int head, bool direction) {
    // Sort the request queue
    sort(requests.begin(), requests.end());
    int seek_count = 0;
    vector<int> order;

    // Find the position of the first request >= head
    auto it = lower_bound(requests.begin(), requests.end(), head);

    if (direction) { // Moving upwards
        // Service requests in the upward direction
        order.insert(order.end(), it, requests.end());
        // Reverse direction to service remaining requests
        order.insert(order.end(), requests.rbegin() + (requests.end() - it), requests.rend());
    } else { // Moving downwards
        // Service requests in the downward direction
        order.insert(order.end(), requests.rbegin() + (requests.end() - it), requests.rend());
        // Reverse direction to service remaining requests
        order.insert(order.end(), it, requests.end());
    }

    // Calculate seek operations and print the order
    cout << "LOOK Disk Scheduling\n";
    cout << "Order of access: " << head << " -> ";
    for (int pos : order) {
        seek_count += abs(head - pos); // Add seek distance
        head = pos;
        cout << head << " -> ";
    }
    cout << "\nTotal Seek Operations: " << seek_count << "\n\n";
}

int main() {
    vector<int> requests = {98, 183, 37, 122, 14, 124, 65, 67};
    int head = 53;

    // Test LOOK with upward direction
    look(requests, head, true); // true for upward direction

    // Test LOOK with downward direction
    look(requests, head, false); // false for downward direction

    return 0;
}

