
//binary search function takes an array,
//integer to search for, and the bounds in
//the array to search for as indicies into the array
//returns the index into the array where the integer is
//if it cant find the integer then it returns -1
int binarySearch(int* arr, int search, int left, int right)
{   
    //base case: integer not found
    if(right < left)
        return -1;

    //new middle of sub array
    int middle = (left + right) / 2;

    //integer found return index of where it is
    if(arr[middle] == search)
            return middle;
    //else
    /* integer not found yet keep searching */

    //if the integer we are looking for is to the left of the 
    //(sorted) sub array we are currently looking in
    if(search < arr[middle])
    {
        //look at a smaller (half) sub array 
        //(to left of where we are looking) 
        return binarySearch(arr, search, left, middle-1);
    }
    else //if the integer we are looking for is to the right
    {
        //look at a smaller (half) sub array 
        //(to right of where we are looking) 
        return binarySearch(arr, search, middle+1, right);
    }
}