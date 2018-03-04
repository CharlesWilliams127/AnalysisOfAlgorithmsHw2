#include <stdio.h>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <vector>

using namespace std;

// file name of LIS question for problem two
const char* lisFileName = "something"; // TODO: add file name/reading
const char* morseCodeFileName = "something"; // TODO: add file name/reading

/// My implementation of LIS includes a vector of vectors to eliminate
/// recursion and dynamically program this function. Each vector within
/// the outer vector stores a potential LIS, which we compute by comparing
/// our current element to all previous elements in a bottom-up approach
/// params:
/// V : the initial array to iterate through
/// n : the size of the initial array
/// return value: the LIS of V
vector<int> lis(int V[], int n)
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

int morseCode(char V[], int n)
{
	int i, j;

	// first define an array of values that we care about (only vowels)
	// A, E, I, O, U
	char * vowelArr[] = { ".-", ".", "..", "---", "..-" };
	int vowelArrSize = 5;

	// first, determine if we can even return any values
	// potentially loop through to make sure we don't just have "-"
	vector<int> candidateSizes;

	// assume we have no vowels to start with
	if (V[0] == '.' || n > 2)
		candidateSizes.push_back(1);
	else if (V[0] == '-' && n < 3)
		candidateSizes.push_back(0);


	for (i = 1; i < n; i++)
	{
		int count = 0;

		// check if we can build each letter
		for (j = 0; j < vowelArrSize; j++)
		{
			 // be sure we even can build a letter
			if (strlen(vowelArr[j]) > i) continue;

			// take a substring representing our morse code val
			char * subBuffer = new char[i - (i - strlen(vowelArr[j])) + 1];
			memcpy(subBuffer, V, i - (i - strlen(vowelArr[j])));
			subBuffer[i - (i - strlen(vowelArr[j]))] = '\0';

			//if ((char *)V[i] == vowelArr[j])
			//	count += candidateSizes[i - strlen(vowelArr[j])];

			if (strcmp(vowelArr[j], subBuffer) == 0)
			{
				//if (i - strlen(vowelArr[j]) < 0)
				//	count += candidateSizes[0];
				//else
				//printf("%d\n", candidateSizes[i - strlen(vowelArr[j])]);
				count += candidateSizes[i - strlen(vowelArr[j])];
				//count += 1;
				//count += candidateSizes[abs(j - i)];
			}

			// free mem of substring
			delete subBuffer;
		}
		if (count > 0)
			candidateSizes.push_back(count);
	}

	return candidateSizes.back();
}

/*int stringMorse(string morse_string)
{
	string vowelArr[] = { ".-", ".", "..", "---", "..-" };
	int vowelArrSize = 5;
	vector<long>dp;
	dp.push_back(1);
	for (int i = 0; i<morse_string.size(); i++) {
		long count = 0;
		for (int j = 1; j<vowelArrSize; j++) {
			if (vowelArr[j].size() > i) continue;
			if (vowelArr[j] == morse_string.substr(i - vowelArr[j].size(), i)) {
				count += dp[i - vowelArr[j].size()];
			}
		}
		dp.push_back(count);
	}
	return dp[morse_string.size()];
}*/

/// main works as the driver for both of our algorithms in this case.
int main()
{
	// allocate space for array
	int initialVay[] = { 9, 15, 3, 6, 4, 2, 5, 10, 3};
	char * initMorseArray = "..-";

	// call LIS function
	vector<int> maxLIS = lis(initialVay, 9);

	// call morse code function
	int numMorse = morseCode(initMorseArray, 3);
	printf("Morse: %d\n", numMorse);
	
	printf("Final LIS:\n");
	for (int i = 0; i < maxLIS.size(); i++)
	{
		printf("%d\n", maxLIS[i]);
	}

	system("pause");

	return 0;
}