#include "array_operations.hh"
#include <algorithm>

using namespace std;

int greatest_v1(int* itemptr, int size){
    sort(itemptr, itemptr + size);
    return *(itemptr+size-1);
}

int greatest_v2(int* itemptr, int* endptr){
    sort(itemptr, endptr);
    return *(endptr-1);
}

void copy(int* itemptr, int* endptr, int* targetptr){
    sort(itemptr, endptr);
    while (itemptr < endptr){
        *targetptr = *itemptr;
        targetptr++;
        itemptr++;
    }
}

void reverse(int* leftptr, int* rightptr){
    sort(leftptr, rightptr);
    while (leftptr < (rightptr-1)){
        int temp = *leftptr;
        *leftptr = *(rightptr-1);
        *rightptr = temp;
        leftptr++;
        rightptr--;
    }
}
