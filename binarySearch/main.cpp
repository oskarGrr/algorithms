#include <iostream>
#include <array>

#include "binarySearch.h"

template <class T, class FwdIt> constexpr FwdIt binarySearch(FwdIt, FwdIt const, T const&);
int cStyleBinarySearch(int* arr, int searchFor, int left, int right);

int main()
{
    //a sorted container is needed for binary search!
    std::array b {10, 20, 22, 30, 31, 40, 41, 47, 51, 90, 100, 101, 110};
    auto it = binarySearch(b.begin(), b.end(), 31);
    std::cout << (it != b.end() ? "found!\n" : "not found :(\n");
}