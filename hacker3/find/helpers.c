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

#define LIMIT 65536

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
    int counts[LIMIT];
    for(int i = 0; i < LIMIT; i++)
    {
        counts[i] = 0;
    }
    for(int i = 0; i < n; i++)
    {
        counts[values[i]]++;
    }
    int k = 0;
    for(int i = 0; i < LIMIT; i++)
    {
        for(int j = 0; j < counts[i]; j++)
        {
            values[k++] = i;
        }
    }
}
