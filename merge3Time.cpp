//
//  mergesort3.cpp
//  CS-325
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

// Merge3 function to combine 3 sorted sub lists into an output for the recursive Mergesort3 function.
void merge3(std::vector<int>& left, std::vector<int>& middle, std::vector<int>& right, std::vector<int>& output) {
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
void mergesort3(std::vector<int>& v) {
	if (v.size() == 2 && v[0] > v[1])
		std::swap(v[0], v[1]);
	
	if (v.size() <= 2)
		return;
	
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
	
	return;
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
			while (ss >> currNum)
				list.push_back(currNum);
			
			// Sort vector
			mergesort3(list);
			
			// Print vector
			printVector(list);
		}
		// Close file to end while loop
		is.close();
	}
}
