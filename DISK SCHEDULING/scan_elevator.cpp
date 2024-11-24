#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Function to calculate SCAN disk scheduling with direction reversal
void scanDiskScheduling(vector<int> requests, int head, bool direction, int diskSize) {
    requests.erase(remove(requests.begin(), requests.end(), head), requests.end());
    //remove head if exists in request!
    // Sorting the requests
    sort(requests.begin(), requests.end());
    // Vectors to hold requests greater and lesser than head
    vector<int> left, right;

    for (int req : requests) {
        if (req < head) left.push_back(req);
        else right.push_back(req);
    }

    // Sorting the left and right parts
    sort(left.begin(), left.end()); sort(right.begin(), right.end());

    // Sequence of traversal
    vector<int> traversal;
    if (direction) {
        // Moving up (towards higher tracks)
        traversal.insert(traversal.end(), right.begin(), right.end()); // Move towards last track
        traversal.push_back(diskSize - 1);       // Add the last track boundary
        traversal.insert(traversal.end(), left.rbegin(), left.rend()); // Reverse direction to lower tracks
    } else {
        // Moving down (towards lower tracks)
        traversal.insert(traversal.end(), left.rbegin(), left.rend()); // Move towards first track
        traversal.push_back(0); // Add the first track boundary
        traversal.insert(traversal.end(), right.begin(), right.end()); // Reverse direction to higher tracks
    }

    // Calculating total head movements
    int totalHeadMovement = 0;
    int currentPosition = head;

    cout << "Head movement sequence: " << head << " ";
    for (int track : traversal) {
        cout << track << " ";
        totalHeadMovement += abs(track - currentPosition); currentPosition = track;
    }
    cout << endl;
    // Display total head movement
    cout << "Total head movement: " << totalHeadMovement << " tracks." << endl;
}

// Main function
int main() {
    // Input: Disk size, head position, direction, and request queue
    int diskSize = 200; // Total number of tracks
    int head = 130;      // Initial head position
    bool direction = true; // Initial direction: true for up, false for down
    vector<int> requests = {45, 130, 10, 170, 90, 150, 30}; // Request queue

    cout << "Initial head position: " << head << endl;
    cout << "Disk size: " << diskSize << endl;
    cout << "Request queue: ";
    for (int req : requests) cout << req << " ";
    cout << endl;
    cout << "Initial direction: " << (direction ? "up" : "down") << endl;
    // Call SCAN Disk Scheduling
    scanDiskScheduling(requests, head, direction, diskSize);

    return 0;
}
