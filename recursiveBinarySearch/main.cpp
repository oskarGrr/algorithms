#include "binarySearch.h"//the binarySearch funtion I made
#include <time.h>//time()
#include <stdlib.h>//qsort()
#include <iostream>//cout

//function given to qsort to compare values
int intCompare(const void*, const void*);

int main()
{
    constexpr size_t size = 40;
    int arr[size];

    //fill array with random integers
    srand((unsigned)time(NULL));
    for(int i=0; i<size; ++i)
        arr[i] = rand() % 1000;

    //sort the array of integers before searching for a specific int
    qsort(arr, size, sizeof(*arr), intCompare);

    //print the array out so the user can see 
    //what random integers are in array
    for(int i=0; i<size; ++i)
        std::cout << arr[i] << '\n';

    //ask user which integer to search for
    std::cout << "enter an integer to search for: ";
    int search;
    std::cin >> search;

    //search for integer in the sorted array
    int foundOrNot = binarySearch(arr, search, 0, size-1);

    //if binarySearch returned -1 the integer wasnt found
    if(foundOrNot == -1)  
    {
        std::cout << "int not found in sorted array of random integers\n";
        return 1;
    }

    //else the integer was found so display an arrow pointing at that element   
    for(int i=0; i<size; ++i)
    {
        std::cout << arr[i];
        if(i == foundOrNot)
            std::cout << "<--- integer searched for is here";

        std::cout << '\n';
    }

    return 0;
}

int intCompare(const void* v0, const void* v1)
{
    if( *(int*)v0 <  *(int*)v1  ) return -1;
    if( *(int*)v0 == *(int*)v1  ) return 0;
    if( *(int*)v0 >  *(int*)v1  ) return 1;
}