#include "the1.h"


void exchange(unsigned short*arr, int i1, int i2, long& swap, double& avg_dist, double& max_dist)
{
    if( (arr[i1] == arr[i2]) && (i1 != i2) )return;
    
    unsigned short temp = arr[i1];
    arr[i1] = arr[i2];
    arr[i2] = temp;
    
    
    
    double dist = i2-i1;
    if(i1>i2)dist = i1-i2;
    
    double temp1 = avg_dist * double(swap) / double(swap+1);
    double temp2 = dist / double(swap + 1);
    avg_dist = temp1+temp2;
    
    ++swap;
    
    if(dist > max_dist)
        max_dist = dist;
    
}

int med(unsigned short* arr, int size)
{
    
    
    int i = 0;
            
    int mid = (size-1)/2;
    
    if(     (arr[mid] == arr[0]) && 
            (arr[mid] == arr[size-1]) 
        )
        return arr[mid];
    
    else if(     (arr[mid] == arr[0]) || 
                (arr[mid] == arr[size-1]) || 
                (arr[0] == arr[size-1])
        )return -1;
    
    
    if( arr[mid] > arr[size-1] )
    {
        if(arr[i] > arr[mid])
            i = mid;
        else if(arr[size-1] > arr[i])
            i = size-1;
    }    
    else
    {
        if(arr[mid] > arr[i])
            i = mid;
        else if(arr[i] > arr[size-1])
            i = size-1;
    }
    
    
        
    return i;
}

//returns 0_based index of value that partitions array into two
int LomutoPartition(unsigned short* arr, int size, long& swap, double& avg_dist, double& max_dist)
{
    if (size<2)
        return 0;
        
    int x = arr[size-1];
    int i = -1;
    for(int j=0; j < size-1; ++j)
    {
        if(arr[j] > x)
        {
            ++i;
            exchange(arr, i, j , swap, avg_dist, max_dist);
        }
    }

    exchange(arr, i+1, size-1 , swap, avg_dist, max_dist);
    return i+1;
}


//returns 0_based index of value that partitions array into two
int HoarePartition(unsigned short* arr, int size, long& swap, double& avg_dist, double& max_dist)
{
    if (size<2)
        return 0;
    
    int x = arr[(size-1)/2];
    
    int i=-1;
    int j=size;
    
    while(true)
    {
        do
            ++i;
        while(arr[i] > x);
        
        do
            --j;
        while(arr[j] < x);
        
        if(i >= j)
            return j;
        
        exchange(arr, i, j , swap, avg_dist, max_dist);
    }
    
}


int quickSort(unsigned short* arr, long& swap, double& avg_dist, double& max_dist, bool hoare, bool median_of_3, int size)
{
    if(arr==nullptr)
        return 0;
        
    
    
    
    if(size > 1)
    {
        int q;
        int i = med(arr,size);
        
        
        if(median_of_3 && (i != -1) )
        {
            int mid = (size-1)/2;
            
            if(!hoare)
            {
                if(i != size-1)
                    exchange(arr, i, size-1, swap, avg_dist, max_dist);
            }
            else
            { 
                if(i != mid)
                    exchange(arr, i, mid , swap, avg_dist, max_dist);
            }
        }
    
    
        if(!hoare){
            q = LomutoPartition(arr, size, swap, avg_dist, max_dist);
            
            return  quickSort(arr, swap, avg_dist, max_dist, hoare, median_of_3, q)
                    +
                    quickSort(arr+q+1, swap, avg_dist, max_dist, hoare, median_of_3, size-q-1)
                    + 1;
        }
        
        else
        {
            q = HoarePartition(arr, size, swap, avg_dist, max_dist);
    
            return  quickSort(arr, swap, avg_dist, max_dist, hoare, median_of_3, q+1)
                    +
                    quickSort(arr+q+1, swap, avg_dist, max_dist, hoare, median_of_3, size-q-1)
                    + 1;
        }
    }        
    
	return 1;
}
