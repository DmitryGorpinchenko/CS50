/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    int lo = 0, hi = n;
    
    while(lo <= hi)
    {
        int mid = lo + (hi - lo) / 2;
        
        if (values[mid] == value)
        {
            return true;
        }
        else if (values[mid] < value)
        {
            lo = mid + 1;
        }
        else
        {
            hi = mid - 1;
        }    
    }
    
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    for(int i = 1; i < n; i++)
    {
        int to_insert = values[i];
        int j = i;
        while(values[j - 1] > to_insert && j > 0)
        {
            values[j] = values[j - 1];   
            j--;
        }
        values[j] = to_insert;
    }
}
