//
//  stoogesort.cpp
//  HW1
//
//  Created by Nils Streedain on 4/11/22.
//

#include <iostream>
#include <vector>

// Recursive fucntion to split a list into 3 sublists, sort each sublist, and then recombine.
void stoogesort3(std::vector<int> &v, int min, int max) {
	// If the value at the start of the list is larger than the value at the end, swap them.
	if (v[min] > v[max])
		std::swap(v[min], v[max]);

	if ((max - min + 1) > 2) {
		// Find midpoints for new vectors
		int third = (max - min + 1) / 3;
		
		// Recursively call Mergesort3
		stoogesort3(v, min, max - third);
		stoogesort3(v, min + third, max);
		stoogesort3(v, min, max - third);
	}
}

// Main driver function to convert lines of a txt file into a vector, then sort the vector with a recursive mergesort algorithm
int main(int argc, const char * argv[]) {
	// Print table header
	printf("n\ttime (s)\n");
	
	// seed rng
	srand((int)time(0));
	
	// Loop over different size lists
	for (int i = 200; i <= 2000; i += 200) {
		// Populate current list
		std::vector<int> list;
		list.reserve(i);
		for (int j = 0; j < i; j++)
			list.push_back(rand() % 10000);

		// Initilize & start clock
		clock_t start, end;
		start = clock();
		
		// Sort vector
		stoogesort3(list, 0 , i - 1);
		
		// end clock
		end = clock();
		
		// Calculate & print runtime and size of n
		printf("%d\t%.10fs\n", i, (double)(end - start)/CLOCKS_PER_SEC);
	}
}
