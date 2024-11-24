#include<bits/stdc++.h>
using namespace std;
void sstf(vector<int> requests, int head) {
    int seek_count = 0;
    vector<bool> visited(requests.size(), false);
    cout << "SSTF Disk Scheduling\n";
    cout << "Order of access: " << head << " -> ";

    for (int i = 0; i < requests.size(); i++) {
        int min_distance = INT_MAX, index = -1;
        for (int j = 0; j < requests.size(); j++) {
            if (!visited[j] && abs(head - requests[j]) < min_distance) {
                min_distance = abs(head - requests[j]);
                index = j;
            }
        }
        seek_count += min_distance;
        head = requests[index];
        visited[index] = true;
        cout << head << (i < requests.size() - 1 ? " -> " : "\n");
    }
    cout << "Total Seek Operations: " << seek_count << "\n\n";
}

int main() {
    vector<int> requests = {98, 183, 37, 122, 14, 124, 65, 67};
    int head = 53;
    sstf(requests, head);
    return 0;
}
