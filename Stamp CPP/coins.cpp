//Stamp Dispenser Program: Laserfiche
//Written by: Eddie Solares

#include <stdexcept>
#include <cstdlib>
#include <iostream>
#include <stdlib.h>
#include<bits/stdc++.h>
using namespace std;
 
int denomCheck(int stampDenominations[], int size)
{
	// This checks that the length of the array has at least one value. 
	if (size < 1)
		throw runtime_error("The number of stamp denominations must be at least 1.");
	
	//This checks to see that the array is arranged in descending order
	for (int i = 0; i < (size - 1); i++)
	{
		for (int j = i + 1; j < size; j++)
		{
			if (stampDenominations[j] > stampDenominations[i])
			{
				throw runtime_error("Not in descending order.");
			}
		}
	}
	

	//This checks to see if the last number is a one since it must be included.
	//The array is now in descending order if it has reached this far.
	//So the last number must be a 1 since it must be included.
	//This is assuming we are ignoring 0 and negative values which makes sense physically.
	if (stampDenominations[size - 1] != 1)
		throw runtime_error("Final number within length of array is not 1, must be included.");
	
	cout << "Check: Array is in descending order and includes a 1.\n";
	
	return 0;
	
}
 
int stampDispenser(int stampDenominations[], int size, int request)
{
    int storeArray[request + 1];
 
    storeArray[0] = 0;
 
    for (int i = 1; i <= request; i++)
        storeArray[i] = INT_MAX;
 
    for (int i = 1; i <= request; i++)
    {
        for (int j = 0; j< size; j++)
          if (stampDenominations[j] <= i)
          {
              int temp = storeArray[i-stampDenominations[j]];
              if (temp != INT_MAX && temp + 1 < storeArray[i])
                  storeArray[i] = temp + 1;
          }
    }
    return storeArray[request];
}
 
int main()
{
    int stampDenominations[] =  {90, 30, 24, 10, 6, 2, 1};
    int size = sizeof(stampDenominations)/sizeof(stampDenominations[0]);
    int request = 48;
	
	denomCheck(stampDenominations, size);
    cout << "Minimum stamps required is: "
         << stampDispenser(stampDenominations, size, request);
    return 0;
}