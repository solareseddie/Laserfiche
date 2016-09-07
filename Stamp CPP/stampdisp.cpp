//Stamp Dispenser Program: Laserfiche
//Written by: Eddie Solares

#include <stdexcept>
#include <cstdlib>
#include <iostream>
#include <stdlib.h>
#include<bits/stdc++.h>
using namespace std;

//This snippet is just for making sure is both in descending order, 
//includes a 1, and that the array has at least one value. Otherwise, 
//it will spit out an error either when trying to compile, or run.
int denomCheck(int stampDenominations[], int size)
{
	// This checks that the length of the array has at least one value. 
	if (size < 1)
		throw runtime_error("The number of stamp denominations must be at least 1.");
	
	//This checks to see that the array is arranged in descending order.
	//Does this by making sure the number in front of it and down the list is smaller.
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
	
	cout << "The stamp denomination array is in descending order and includes a 1.\n";
	
	return 0;
	
}

//This is an example of dynamic programming. 
//This algorithm is based on finding the minimum number of coins to make a value.
//The greedy method will not work here for certain cases.
int stampDispenser(int stampDenominations[], int size, int request)
{
	//We create an array to store the numbe of stamps required for certain values.
	//Without this array we would have to repeat multiple calculations. 
	//This drastically reduces our computing time.
    int storeArray[request + 1];
 
	//We always have the null case if the requested number is 0.
    storeArray[0] = 0;
 
	//We, theoretically, set all values as infinite.
	//But since infinite is not allowed in computers we request the maximum integer.
	//This is part of the algorithm that compares the minimum with the max integer.
    for (int i = 1; i <= request; i++)
        storeArray[i] = INT_MAX;
 
	//This computes the minimum number of stamps to be dispense for the request value.
	//We iterate this process for values from 1 to the request.
	//Larger numbers not needed since it will have passed the request value. 
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

//This is the main program that just runs the other two on top.
int main()
{
	//Sets the three variables we will be dealing with.
	//Testing number 48 is a good test number since the greedy method will calculate a minimum of
	//four (30, 10, 6, 2) while the dynamic program will calculate just two (24, 24).
    int stampDenominations[] =  {90, 30, 24, 10, 6, 2, 1};
    int size = sizeof(stampDenominations)/sizeof(stampDenominations[0]);
    int request = 48;
	
	//Calls both denomCheck and stampDispenser functions.
	denomCheck(stampDenominations, size);
    cout << "The minimum number of stamps required is: " << stampDispenser(stampDenominations, size, request);
    return 0;
}