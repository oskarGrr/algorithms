#include <iostream>
#include <vector>

template <class T, class FwdIt> constexpr FwdIt binarySearch(FwdIt, FwdIt const, T const&);
int cStyleBinarySearch(int* arr, int searchFor, int left, int right);

int main()
{
    //a sorted container is needed for binary search!
    std::vector b {10, 20, 22, 30, 31, 40, 41, 47, 51, 90, 100, 101, 110};
    auto it = binarySearch(b.begin(), b.end(), 46);
    std::cout << (it != b.end() ? "found!\n" : "not found :(\n");
}

template <typename T> concept greaterThanComparable = requires(T t0, T t1){ t0 > t1;  };
template <typename T> concept equalityComparable    = requires(T t0, T t1){ t0 == t1; };

//returns an iterator to the T that you are searching for otherwise returns end
template <typename T, typename FwdIt>
requires greaterThanComparable<T> && equalityComparable<T> && std::forward_iterator<FwdIt>
constexpr FwdIt binarySearch(FwdIt begin, FwdIt const end, T const& searchFor)
{
    FwdIt traveler;
    for(auto rangeSize = std::distance(begin, end); rangeSize > 0;)
    {
        traveler = begin;
        auto middle = rangeSize / 2;
        std::advance(traveler, middle);

        //if we found what we are searching for
        if(searchFor == *traveler) return traveler;

        //if the thing we are searching for is to the "right"
        else if(searchFor > *traveler)
        {
            begin = ++traveler;
            rangeSize -= middle + 1;
        }

        //if the thing we are searching for is to the "right"
        else rangeSize = middle;
    }

    //the loop didn't find seachFor so return the given end iterator
    return end;
}

//binary search function takes an array,
//integer to search for, and the bounds in
//the array to search for as indicies into the array
//returns the index into the array where the integer is
//if it cant find the integer then it returns -1
int cStyleBinarySearch(int* arr, int searchFor, int left, int right)
{
    //base case: integer not found
    if(right < left)
        return -1;

    //new middle of sub array
    int middle = (left + right) / 2;

    //base case: integer found return index of where it is
    if(arr[middle] == searchFor)
        return middle;

    //else
    /* integer not found yet keep searching */

    //if the integer we are looking for is to the left of the 
    //(sorted) sub array we are currently looking in
    if(searchFor < arr[middle])
    {
        //look at a smaller (half) sub array 
        //(to left of where we are looking) 
        return cStyleBinarySearch(arr, searchFor, left, middle-1);
    }
    else //if the integer we are looking for is to the right
    {
        //look at a smaller (half) sub array 
        //(to right of where we are looking) 
        return cStyleBinarySearch(arr, searchFor, middle+1, right);
    }
}