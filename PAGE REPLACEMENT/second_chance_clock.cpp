#include<iostream>
#include<cstring>
#include<sstream>
using namespace std; 
	
// If page found, updates the second chance bit to true 
static bool findAndUpdate(int x, int arr[], bool second_chance[], int frames) 
{ 
	int i; 
	for(i = 0; i < frames; i++) 
	{ 
		if(arr[i] == x) 
		{ 
			second_chance[i] = true;  // Mark that the page deserves a second chance
			return true;  // Return 'true' i.e. there was a hit  
		} 
	} 
	
	// Return 'false' so that a page for replacement is selected 
	// as he reuested page doesn't exist in memory 
	return false; 
} 


// Updates the page in memory and returns the pointer 
static int replaceAndUpdate(int x,int arr[], bool second_chance[], int frames, int pointer) 
{ 
	while(true) 
	{ 
		if(!second_chance[pointer]) // We found the page to replace 
		{ 
			arr[pointer] = x;  // Replace with new page
			return (pointer + 1) % frames;  // Return updated pointer 
		} 
		
		// Mark it 'false' as it got one chance 
		// and will be replaced next time unless accessed again 
		second_chance[pointer] = false; 
		pointer = (pointer + 1) % frames;  //Pointer updated in round robin manner 
	} 
} 

static void printHitsAndFaults(string reference_string, int frames) 
{ 
	int pointer = 0, i, l=0, x, pf = 0; 
	pointer = 0; //initially we consider frame 0 is to be replaced 
	//pf --- number of page faults
	int arr[frames]; // Create a array to hold page numbers 
	memset(arr, -1, sizeof(arr)); 	// No pages initially in frame indicated by -1 
	bool second_chance[frames]; // Create second chance array. 
	
	// Split the string into page numbers,
	string str[100];
	string word = ""; 
	for (auto x : reference_string) 
	{ 
		if (x == ' ') { 	str[l]=word;  word = ""; l++;	} 
		else{ word = word + x; 	} 
	}
	str[l] = word; l++; // l=the length of array 
	
	for(i = 0; i < l; i++) 
	{ 
		x = stoi(str[i]);
		// Finds if there exists a need to replace  any page at all 
		if(!findAndUpdate(x,arr,second_chance,frames)) 
		{ 
			// Selects and updates a victim page 
			pointer = replaceAndUpdate(x,arr, second_chance, frames, pointer);  
			pf++; // Update page faults
		} 
	} 
	cout << "Total page faults were " << pf << "\n";
}

// Driver code
int main()
{ 
	string reference_string = ""; 
	int frames = 0; 
	// Test 1: 
	reference_string = "0 4 1 4 2 4 3 4 2 4 0 4 1 4 2 4 3 4"; 
	frames = 3; 
	// Output is 9 
	printHitsAndFaults(reference_string,frames); 
	
	// Test 2: 
	reference_string = "2 5 10 1 2 2 6 9 1 2 10 2 6 1 2 1 6 9 5 1"; 
	frames = 4; 
	// Output is 11 
	printHitsAndFaults(reference_string,frames); 
	return 0; 
} 

// This code is contributed by NikhilRathor


// Algorithm for Second-Chance Page Replacement

/*
Algorithm: findAndUpdate(x, arr, second_chance, frames)
1. Iterate over the frame array:
   a. If page 'x' is found:
      - Set its second chance bit to true.
      - Return true (indicating a hit).
2. If not found, return false (indicating a miss).

Algorithm: replaceAndUpdate(x, arr, second_chance, frames, pointer)
1. Loop until a page to replace is found:
   a. If the current page's second chance bit is false:
      - Replace it with page 'x'.
      - Update the pointer to the next frame (round-robin).
      - Return the updated pointer.
   b. Otherwise:
      - Set its second chance bit to false.
      - Move the pointer to the next frame (round-robin).

Algorithm: printHitsAndFaults(reference_string, frames)
1. Initialize variables:
   - Pointer to track the frame to be replaced.
   - Page faults counter (pf).
   - Arrays for frames and second chance bits (all initially empty/false).
2. Split the reference string into page numbers.
3. For each page number:
   a. Check if it exists in frames using findAndUpdate().
      - If yes, continue to the next page.
      - If no, call replaceAndUpdate() to replace a page.
      - Increment the page fault counter (pf).
4. Output the total number of page faults.

Time Complexity:
- findAndUpdate: O(frames) per page.
- replaceAndUpdate: O(frames) per page.
- Overall: O(l * frames), where 'l' is the number of page references.

Space Complexity:
- O(frames) for frames and second chance arrays.
*/