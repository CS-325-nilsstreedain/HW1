//
//  stoogesort.cpp
//  HW1
//
//  Created by Nils Streedain on 4/11/22.
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

// Prints a text representation of a vector to the console
void printVector(std::vector<int> const &v) {
	for (int i = 0; i < v.size(); i++)
		std::cout << v.at(i) << ' ';
	std::cout << std::endl;
}

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
	// Create input stream from file
	std::ifstream is("data.txt");
	
	// Loop while file stream is open
	while (is.is_open()) {
		std::string currLine;
		
		// Loop over each line in file
		while (getline(is, currLine)) {
			// Parse line into vector
			std::stringstream ss(currLine);
			int currNum;
			std::vector<int> list;
			ss >> currNum;
			while (ss >> currNum)
				list.push_back(currNum);
			
			stoogesort3(list, 0, list.size() - 1);
			
			// Print vector
			printVector(list);
		}
		// Close file to end while loop
		is.close();
	}
}
