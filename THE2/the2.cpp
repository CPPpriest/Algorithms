#include "the2.h"


void countSort(std::string* arr, int size, int k, bool ascending, int& count)
{
    int* arr_C = new int[27];
    std::string* arr_B = new std::string[size];
    
    for(int i=0; i < 27; ++i)
        arr_C[i] = 0;

    for(int i=0; i < size; ++i){
        ++count;

        int a;
        if(arr[i].length() > k)
            a = (arr[i])[k] % 65 + 1;
        else
            a = 0;
        arr_C[a] += 1;
        arr_B[i] = arr[i];
    }

    if(ascending){
        for(int i=1; i < 27; ++i){
            ++count;
            
            arr_C[i] =  arr_C[i] + arr_C[i-1];
        }
    }
    // Descending
    else{
        for(int i=25; i >= 0; --i){
            ++count;
            
            arr_C[i] =  arr_C[i] + arr_C[i+1];
        }   
    }
    
    for(int i=size-1; i >= 0; --i){
        ++count;
        ++count;
        int a;
        if(arr_B[i].length() > k)
            a = (arr_B[i])[k] % 65 + 1;
        else
            a = 0;
        arr[ arr_C[a] - 1 ] = arr_B[i];
        arr_C[ a ] -= 1;
    }
    
    delete[] arr_B;
    delete[] arr_C;
}


int radix_string_sort(std::string* arr, int size, bool ascending)
{
    int count = 0;
    
    int maxIndex = 0;
    for(int i=0; i<size; ++i)
    {
        if(arr[i].length()-1 > maxIndex)
            maxIndex = arr[i].length()-1;
    }
    
    
    for(int i=maxIndex; i >= 0; --i)
        countSort(arr, size, i, ascending, count);

    return count;
}
