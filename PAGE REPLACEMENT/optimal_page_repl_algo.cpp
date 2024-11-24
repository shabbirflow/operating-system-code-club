// CPP program to demonstrate optimal page
// replacement algorithm.
#include <bits/stdc++.h>
using namespace std;

// Function to check whether a page exists in a frame or not
bool search(int key, vector<int>& fr)
{
	for (int i = 0; i < fr.size(); i++){ if (fr[i] == key) return true; }
	return false;
}

// Function to find the frame that will not be used
// recently in future after given index in pg[0..pn-1]
int predict(int pg[], vector<int>& fr, int pn, int index)
{
	// Store the index of pages which are going
	// to be used recently in future
	int res = -1, farthest = index;
	for (int i = 0; i < fr.size(); i++) {
		int j;
		for (j = index; j < pn; j++) {
			if (fr[i] == pg[j]) {
				if (j > farthest) { farthest = j; res = i; }
				break;
			}
		}
		// If a page is never referenced in future, return it.
		if (j == pn) return i;
	}
	// If all of the frames were not in future, return any of them, we return 0. 
    // Otherwise we return res.
	return (res == -1) ? 0 : res;
}

void optimalPage(int pg[], int pn, int fn)
{
	// Create an array for given number of frames and initialize it as empty.
	vector<int> fr;
	// Traverse through page reference array and check for miss and hit.
	int hit = 0;
	for (int i = 0; i < pn; i++) {
		// Page found in a frame : HIT
		if (search(pg[i], fr)) { hit++; continue; }
		// Page not found in a frame : MISS
		// If there is space available in frames.
		if (fr.size() < fn) fr.push_back(pg[i]);
		else {  // Find the page to be replaced.
			int j = predict(pg, fr, pn, i + 1);
			fr[j] = pg[i];
		}
	}
	cout << "No. of hits = " << hit << endl;
	cout << "No. of misses = " << pn - hit << endl;
}

// Driver Function
int main()
{
	int pg[] = { 7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2 };
	int pn = sizeof(pg) / sizeof(pg[0]);
	int fn = 4;
	optimalPage(pg, pn, fn);
	return 0;
}

// This code is contributed by Karandeep Singh

// Optimal Page Replacement Algorithm

// 1. **Initialize Data Structures**:
//    - Create an array `frames[]` to hold the pages currently loaded in memory, 
        // with a maximum size equal to the number of frames (`fn`).
//    - Initialize `hit` as 0 (to count the number of page hits).
//    - Initialize `miss` as 0 (to count the number of page misses, can be derived as `pn - hit`).
//    - Iterate through each page reference in the page reference array `pg[]` to process each page.

// 2. **Check for Page Hit (Page already in memory)**:
//    - For each page reference `pg[i]`, check if the page exists in `frames[]` 
        // (i.e., check if it's already in memory).
//    - If the page exists in `frames[]`, increment the `hit` counter 
        // and move to the next page reference (continue to the next iteration).
//    - This is a **Page Hit**. No replacement is needed for the page already in memory.

// 3. **Check for Page Miss (Page not in memory)**:
//    - If the page reference `pg[i]` is not found in `frames[]`, this is a **Page Miss**.
//    - If there is space available in memory (i.e., the size of `frames[]` is less than `fn`), 
        // simply add `pg[i]` to `frames[]`.
//    - If there is no space available in memory (i.e., the frames are full), 
        // find the page to replace by using the **Predict Function**.


// 4. **Predict Function (Find the page to replace)**:
//    - The **predict function** determines which page to replace based on future page usage.
//    - For each page in `frames[]`, look ahead in the page reference array `pg[]` 
        // (from the current index `i` onwards) to find when the page will be used again.
//    - Track the **farthest future usage index** for each page in `frames[]`.
//    - If a page is **never referenced again**, it is selected for replacement immediately.
//    - If all pages in `frames[]` are referenced again, the one with the **farthest future reference** 
        // (i.e., the page used the latest) is selected for replacement.
//    - The page chosen by the `predict` function is then replaced with the new page `pg[i]`.


 // 5. **Update the Frames**:
 //    - After replacing the page using the `predict` function, 
        // update the `frames[]` with the newly added page `pg[i]`.

 // 6. **Count Hits and Misses**:
 //    - After processing all page references, print the total number of **hits** and **misses**.
 //    - The **total misses** can be calculated as `pn - hits`, 
        // where `pn` is the total number of page references.

 // 7. **Final Output**:
 //    - Print the results: the total number of **hits** and **misses**.

