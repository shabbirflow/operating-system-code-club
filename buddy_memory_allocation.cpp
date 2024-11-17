#include <bits/stdc++.h>
using namespace std;

// Define constants
const int MAX_LEVELS = 16; // Maximum levels in the buddy system (2^16 = 65536 size)

class BuddyAllocator {
private:
    // A map to store free blocks available at each level
    map<int, vector<int>> freeList;

public:
    BuddyAllocator(int totalMemorySize) {
        // Calculate the maximum level for the given memory size
        int maxLevel = log2(totalMemorySize);
        
        // Initialize the free list with the entire memory block
        freeList[maxLevel].push_back(0);
    }

    // Function to allocate memory of a given size
    int allocate(int size) {
        // Find the minimum level that can accommodate the requested size
        int level = ceil(log2(size));

        // Check for free blocks at the appropriate level
        for (int i = level; i <= MAX_LEVELS; i++) {
            if (!freeList[i].empty()) {
                int blockStart = freeList[i].back(); // Get the last block in the list
                freeList[i].pop_back(); // Remove it from the free list

                // If the block is larger than needed, split it into buddies
                while (i > level) {
                    i--;
                    int buddy = blockStart + (1 << i); // Calculate the buddy address
                    freeList[i].push_back(buddy); // Add the buddy to the free list
                }

                // Return the starting address of the allocated block
                return blockStart;
            }
        }

        // If no suitable block is found, return -1 (indicating allocation failure)
        return -1;
    }

    // Function to free a previously allocated block
    void free(int address, int size) {
        // Calculate the level of the block to be freed
        int level = ceil(log2(size));

        // Insert the block back into the free list at the appropriate level
        freeList[level].push_back(address);

        // Try to merge with buddy
        while (level < MAX_LEVELS) {
            int buddyAddress = address ^ (1 << level); // Calculate the buddy address

            // Check if the buddy is in the free list
            auto &buddies = freeList[level];
            auto it = find(buddies.begin(), buddies.end(), buddyAddress);

            if (it != buddies.end()) {
                // Buddy found: remove the buddy and merge
                buddies.erase(it);
                address = min(address, buddyAddress); // New block address after merging
                level++; // Move to the next level for further merging
            } else {
                // Buddy not found: stop merging
                break;
            }
        }

        // Add the merged block back to the free list
        freeList[level].push_back(address);
    }

    // Function to print the current state of the buddy system
    void printFreeList() {
        cout << "Free List by Levels:" << endl;
        for (int i = 0; i <= MAX_LEVELS; i++) {
            if (!freeList[i].empty()) {
                cout << "Level " << i << " (" << (1 << i) << " size): ";
                for (int block : freeList[i]) {
                    cout << block << " ";
                }
                cout << endl;
            }
        }
    }
};

int main() {
    int totalMemorySize = 64; // Example memory size of 64 units
    BuddyAllocator allocator(totalMemorySize);

    cout << "Initial state of the buddy system:" << endl;
    allocator.printFreeList();

    // Allocate memory blocks
    int addr1 = allocator.allocate(8);
    int addr2 = allocator.allocate(16);
    int addr3 = allocator.allocate(4);

    cout << "\nAfter allocations:" << endl;
    allocator.printFreeList();

    // Free memory blocks
    allocator.free(addr1, 8);
    allocator.free(addr2, 16);

    cout << "\nAfter freeing some blocks:" << endl;
    allocator.printFreeList();

    return 0;
}
