#include<bits/stdc++.h>
using namespace std;

void clook(vector<int> requests, int head) {
    sort(requests.begin(), requests.end());
    int seek_count = 0;
    vector<int> order;

    auto it = lower_bound(requests.begin(), requests.end(), head);
    order.insert(order.end(), it, requests.end());
    order.insert(order.end(), requests.begin(), it);

    cout << "C-LOOK Disk Scheduling\n";
    cout << "Order of access: " << head << " -> ";
    for (int pos : order) {
        seek_count += abs(head - pos);
        head = pos;
        cout << head << " -> ";
    }
    cout << "\nTotal Seek Operations: " << seek_count << "\n\n";
}

int main() {
    vector<int> requests = {98, 183, 37, 122, 14, 124, 65, 67};
    int head = 53;
    clook(requests, head);
    return 0;
}
