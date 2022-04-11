//
//  mergesort3.cpp
//  CS-325
//
//  Created by Nils Streedain on 4/11/22.
//

#include <iostream>
#include <vector>

// Merge3 function to combine 3 sorted sub lists into an output for the recursive Mergesort3 function.
void merge3(std::vector<int> &left, std::vector<int> &middle, std::vector<int> &right, std::vector<int> &output) {
	int i = 0, l = 0, m = 0, r = 0;
	
	// Loops over each index of output until it is filled
	while (i < output.size()) {
		// Left is moved when is is not empty & middle & right is empty, or not empty but smaller than left
		if ((l < left.size()) &&
			(!(m < middle.size()) || left[l] <= middle[m]) &&
			(!(r < right.size()) || left[l] <= right[r]))
			output[i] = left[l++];
		// Middle is moved when it is not empty & left & right is empty, or not empty but smaller than middle
		else if ((m < middle.size()) &&
				 (!(l < left.size()) || middle[m] <= left[l]) &&
				 (!(r < right.size()) || middle[m] <= right[r]))
			output[i] = middle[m++];
		// Otherwise, right is moved
		else
			output[i] = right[r++];
		i++;
	}
}

// Recursive fucntion to split a list into 3 sublists, sort each sublist, and then recombine.
void mergesort3(std::vector<int> &v) {
	if (v.size() == 2 && v[0] > v[1])
		std::swap(v[0], v[1]);
	
	if (v.size() > 2) {
		// Find midpoints for new vectors
		int loMid = (int)v.size() / 3;
		int hiMid = loMid * 2;
		
		// Create new vectors
		std::vector<int> left;
		std::vector<int> middle;
		std::vector<int> right;
		
		// Allocate correct space in vectors
		left.reserve(loMid);
		middle.reserve(hiMid - loMid);
		right.reserve(v.size() - hiMid);
		
		// Copy vector segement contents to new vectors
		std::copy(std::begin(v), std::begin(v) + loMid, std::back_inserter(left));
		std::copy(std::begin(v) + loMid, std::begin(v) + hiMid, std::back_inserter(middle));
		std::copy(std::begin(v) + hiMid, std::end(v), std::back_inserter(right));
		
		// Recursively call Mergesort3
		mergesort3(left);
		mergesort3(middle);
		mergesort3(right);
		
		// Combine sorted segments
		merge3(left, middle, right, v);
	}
}

// Main driver function to convert lines of a txt file into a vector, then sort the vector with a recursive mergesort algorithm
int main(int argc, const char * argv[]) {
	// Print table header
	printf("n\ttime (s)\n");
	
	// seed rng
	srand((int)time(0));
	
	// Loop over different size lists
	for (int i = 500000; i <= 5000000; i += 500000) {
		// Populate current list
		std::vector<int> list;
		list.reserve(i);
		for (int j = 0; j < i; j++)
			list.push_back(rand() % 10000);

		// Initilize & start clock
		clock_t start, end;
		start = clock();
		
		// Sort vector
		mergesort3(list);
		
		// end clock
		end = clock();
		
		// Calculate & print runtime and size of n
		printf("%d\t%.10fs\n", i, (double)(end - start)/CLOCKS_PER_SEC);
	}
}
