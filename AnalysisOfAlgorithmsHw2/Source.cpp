#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>

using namespace std;

// define size of array
const int SIZE = 10;

// final longest increasing sequence array
vector<int> lisArr;

void lis(int V[], int n)
{
	int * r = (int*)malloc(sizeof(int) * n);
	//int * s = (int*)malloc(sizeof(int) * n);

	for (int i = 0; i < n; i++)
	{
		r[i] = 1;
	}
	
	lisArr = vector<int>();
	
	for (int i = 1; i < n; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (V[i] > V[j] && r[i] < r[j] + 1)
			{
				r[i] = r[j] + 1;
			}
		}
	}

	delete[] r;
}

int main()
{
	// allocate space for array
	int * initialArray = new int[SIZE];

	// populate array
	for (int i = 0; i < SIZE; i++)
	{
		initialArray[i] = rand() % 10 + 1;
	}

	printf("Initial Array:\n");
	for (int i = 0; i < SIZE; i++)
	{
		printf("%d\n", initialArray[i]);
	}

	// call naive LIS
	lis(initialArray, SIZE);

	// print both
	

	printf("Final LIS Array:\n");
	for (int i = 0; i < lisArr.size(); i++)
	{
		printf("%d\n", lisArr[i]);
	}

	// de-allocate initialArray
	delete[] initialArray;

	system("pause");

	return 0;
}