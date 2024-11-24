// C++ program for LFU cache implementation
#include <bits/stdc++.h>
using namespace std;

// Returns the index of the parent node
inline int parent(int i){   return (i - 1) / 2; }

// Returns the index of the left child node
inline int left(int i)
{
	return 2 * i + 1;
}

// Returns the index of the right child node
inline int right(int i)
{
	return 2 * i + 2;
}

// Self made heap to Rearranges
// the nodes in order to maintain the heap property
void heapify(vector<pair<int, int> >& v,
			unordered_map<int, int>& m, int i, int n)
{
	int l = left(i), r = right(i), minim;
	if (l < n)
		minim = ((v[i].second < v[l].second) ? i : l);
	else
		minim = i;
	if (r < n)
		minim = ((v[minim].second < v[r].second) ? minim : r);
	if (minim != i) {
		m[v[minim].first] = i;
		m[v[i].first] = minim;
		swap(v[minim], v[i]);
		heapify(v, m, minim, n);
	}
}

// Function to Increment the frequency
// of a node and rearranges the heap
void increment(vector<pair<int, int> >& v,
			unordered_map<int, int>& m, int i, int n)
{
	++v[i].second;
	heapify(v, m, i, n);
}

// Function to Insert a new node in the heap
void insert(vector<pair<int, int> >& v,
			unordered_map<int, int>& m, int value, int& n)
{
	
	if (n == v.size()) {
		m.erase(v[0].first);
		cout << "Cache block " << v[0].first << " removed.\n";
		v[0] = v[--n];
		heapify(v, m, 0, n);
	}
	v[n++] = make_pair(value, 1);
	m.insert(make_pair(value, n - 1));
	int i = n - 1;

	// Insert a node in the heap by swapping elements
	while (i && v[parent(i)].second > v[i].second) {
		m[v[i].first] = parent(i);
		m[v[parent(i)].first] = i;
		swap(v[i], v[parent(i)]);
		i = parent(i);
	}
	cout << "Cache block " << value << " inserted.\n";
}

// Function to refer to the block value in the cache
void refer(vector<pair<int, int> >& cache, unordered_map<int,
					int>& indices, int value, int& cache_size)
{
	if (indices.find(value) == indices.end()) insert(cache, indices, value, cache_size);
	else increment(cache, indices, indices[value], cache_size);
}

// Driver Code
int main()
{
	int cache_max_size = 4, cache_size = 0;
	vector<pair<int, int> > cache(cache_max_size);
	unordered_map<int, int> indices;
	refer(cache, indices, 1, cache_size);
	refer(cache, indices, 2, cache_size);
	refer(cache, indices, 1, cache_size);
	refer(cache, indices, 3, cache_size);
	refer(cache, indices, 2, cache_size);
	refer(cache, indices, 4, cache_size);
	refer(cache, indices, 5, cache_size);
	return 0;
}

// LFU Cache Algorithm:

// 1. Initialize the cache with a maximum size (cache_max_size) and set the current size to 0.

// 2. Each cache block is represented as a pair of <value, frequency>, 
    // where value is the cache item and frequency is how often the item has been accessed.

// 3. To access a cache block:
    // a. If the block exists in the cache (check using 'indices'):
        // i. Increment the frequency of the block (by calling 'increment').
        // ii. Rearrange the heap to maintain the least frequent item at the root.
    // b. If the block does not exist:
        // i. Insert the block into the cache (by calling 'insert').
        // ii. If the cache is full, remove the least frequently used item (root of the heap) before insertion.

// 4. When inserting a new item:
    // a. If the cache is full, the root item (the least frequently used item) is removed.
    // b. Insert the new item into the heap with a frequency of 1.
    // c. Rearrange the heap to maintain the heap property using the 'heapify' function.

// 5. During any change in the cache (either an access or insertion), the heap structure is maintained by 
// calling the 'heapify' function which ensures the least frequently used item is always at the root of the heap.

// 6. The cache will contain the most frequently accessed items, and when it is full, the least frequently 
// used items will be evicted first.
