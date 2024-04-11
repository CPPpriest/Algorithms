#include "the0.h"

void insertionSort(int* arr, long &comparison, long & swap, int size) 
{
    int i=1,j;
    int x;
    
    
    while(i<size)
    {
        x = arr[i];
        j = i-1;
        
        comparison++;
        while(j>=0)
        {
            
            if(arr[j] > x)
            {
                comparison++;
                arr[j+1] = arr[j];
                swap++;
                --j;
            }
            else
                break;
        }
        arr[j+1] = x;
        ++i;
    }
    
}