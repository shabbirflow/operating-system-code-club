#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

void fcfs(vector<int> requests, int head) {
    int seek_count = 0;
    cout << "FCFS Disk Scheduling\n";
    cout << "Order of access: " << head << " -> ";
    for (int i = 0; i < requests.size(); i++) {
        seek_count += abs(head - requests[i]);
        head = requests[i];
        cout << head << (i < requests.size() - 1 ? " -> " : "\n");
    }
    cout << "Total Seek Operations: " << seek_count << "\n\n";
}

int main() {
    vector<int> requests = {98, 183, 37, 122, 14, 124, 65, 67};
    int head = 53; // Initial head position
    fcfs(requests, head);
    return 0;
}
