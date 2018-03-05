#include <stdio.h>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

// file name of LIS question for problem two
const char* lisFileName = "lisInput.txt";
const char* morseCodeFileName = "morseInput.txt";

/// My implementation of LIS includes a vector of vectors to eliminate
/// recursion and dynamically program this function. Each vector within
/// the outer vector stores a potential LIS, which we compute by comparing
/// our current element to all previous elements in a bottom-up approach
/// params:
/// V : the initial array to iterate through
/// n : the size of the initial array
/// return value: the LIS of V
vector<int> lis(vector<int> V, int n)
{
	int  i, j;
	vector<int> maxLIS;

	// contains each potential lis
	vector<vector<int>> candidateLIS = vector<vector<int>>(n);

	// our first sub-sequence is just our first element, since we 
	// have no other elements to compare it to
	candidateLIS[0].push_back(V[0]);

	// this means by default, our max value is the first element in 
	// our vector
	maxLIS = candidateLIS[0];

	// as opposed to recursion, since this is dynamically programmed
	// compute the values in or vector of subsequences in a bottom-up
	// approach, this eliminates recursion and allows us to store the 
	// results of each subsequence
	for (i = 1; i < n; i++)
	{
		for (j = 0; j < i; j++)
		{
			if ((V[i] > V[j]) &&
				(candidateLIS[i].size() < candidateLIS[j].size() + 1))
			{
				// we've found a replacement candidate if we reach here,
				// this works similarly to pushing V[j] however, with just
				// directly assigning the vector we can continuously
				// overwrite the previous value, preventing values no longer
				// in the sequence from persisting
				candidateLIS[i] = candidateLIS[j];
			}
		}
		// to prevent loss of last element
		candidateLIS[i].push_back(V[i]);
	}

	// iterate through, comparing sizes of all candidates to current
	// max, if any of them is larger then it becomes the new max
	for (i = 0; i < n; i++)
	{
		if (maxLIS.size() < candidateLIS[i].size())
		{
			maxLIS = candidateLIS[i];
		}
	}

	return maxLIS;
}

/// My implementation of the morse code algorithm involves a bottom-up
/// approach and two for loops. It should still run in O(n) time
/// however, since the inner loop runs a constant 5 times each
/// iteration. Minor pointer arithmetic is done to determine where
/// to create substrings and what to compare them to.
/// params:
/// V : initial sequence of morse code digits
/// n : length of V
/// retrun value : the combination of subsequences of letters that
/// make up V
int morseCode(char V[], int n)
{
	int i, j;

	// first define an array of values that we care about (only vowels)
	// A, E, I, O, U
	char * vowelArr[] = { (char *)".-", (char *)".", (char *)"..", (char *)"---", (char *)"..-" };
	int vowelArrSize = 5;

	// first, determine if we can even return any values
	// potentially loop through to make sure we don't just have "-"
	vector<int> candidateSizes;

	// assume we have a match to start with
	candidateSizes.push_back(1);

	// iterate through each morse code char and see if any match our
	// set array of vowels
	for (i = 1; i <= n; i++)
	{
		// this is a per-iteration variable, it represents how many
		// "matches" we have for this particular i value
		int count = 0;

		// check if we can build each letter
		for (j = 0; j < vowelArrSize; j++)
		{
			 // be sure we even can build a letter
			if (strlen(vowelArr[j]) > i) continue;

			// take a substring representing our current value 'i'
			// but we then must go back depending on how long our
			// current vowel array value is, once we have our starting
			// index, we index into the array from 'i' to 'i' minus the
			// length of the vowel code we are currently on
			char * subBuffer = new char[i - (i - strlen(vowelArr[j])) + 1];
			memcpy(subBuffer, (V + i) - strlen(vowelArr[j]), (i -(i - strlen(vowelArr[j]))));
			subBuffer[i - (i - strlen(vowelArr[j]))] = '\0';

			if (strcmp(vowelArr[j], subBuffer) == 0)
			{
					count += candidateSizes[i - strlen(vowelArr[j])];
			}

			// free mem of substring
			delete subBuffer;
		}
		
		// always push the value to the back to represent how many 
		// "matches" we got this iteration
		candidateSizes.push_back(count);
	}

	// the last count should be our final count for the algorithm
	return candidateSizes.back();
}

/// main works as the driver for both of our algorithms in this case.
int main()
{
	// initial vectors for i/o
	vector<string> lisInitVecString;
	vector<string> morseInitVecString;

	// final vectors
	vector<int> lisInput;
	char * morseInput;

	// read in lis file
	string line = "";
	ifstream lisFile(lisFileName);

	if (lisFile.is_open())
	{
		while (getline(lisFile, line, ' '))
		{
			lisInitVecString.push_back(line);
		}
	}
	// convert string to int
	for (int i = 0; i < lisInitVecString.size(); i++)
	{
		int num = atoi(lisInitVecString.at(i).c_str());
		lisInput.push_back(num);
	}

	// read in morse code file
	ifstream morseFile(morseCodeFileName);

	if (morseFile.is_open())
	{
		while (getline(morseFile, line, ' '))
		{
			morseInitVecString.push_back(line);
		}
	}

	morseInput = new char[morseInitVecString.size()];

	// translate initial vector into char *
	for (int i = 0; i < morseInitVecString.size(); i++)
	{
		morseInput[i] = morseInitVecString[i].c_str()[0];
	}

	// call LIS function
	vector<int> maxLIS = lis(lisInput, lisInput.size());

	// call morse code function
	int numMorse = morseCode(morseInput, morseInitVecString.size());
	printf("Morse: %d\n", numMorse);

	delete morseInput;
	
	printf("Final LIS:\n");
	for (int i = 0; i < maxLIS.size(); i++)
	{
		printf("%d\n", maxLIS[i]);
	}

	system("pause");

	return 0;
}