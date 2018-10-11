#include "array_operations.hh"
#include <algorithm>

using namespace std;

int greatest_v1(int* itemptr, int size){
    int maxValue = *itemptr;
    int i = 0;
    while (i < size-1){
        if (maxValue < *itemptr){
            maxValue = *itemptr;
        }
        i++;
        itemptr++;
    }

    return maxValue;
}

int greatest_v2(int* itemptr, int* endptr){
    int maxValue = *itemptr;
    int i = 0;
    while (itemptr < endptr){
        if (maxValue < *itemptr){
            maxValue = *itemptr;
        }
        i++;
        itemptr++;
    }

    return maxValue;
}

void copy(int* itemptr, int* endptr, int* targetptr){
    //sort(itemptr, endptr);
    while (itemptr < endptr){
        *targetptr = *itemptr;
        targetptr++;
        itemptr++;
    }
}

void reverse(int* leftptr, int* rightptr){
    //sort(leftptr, rightptr);
    rightptr--;
    while (leftptr < (rightptr)){
        int temp = *leftptr;
        *leftptr = *(rightptr);
        *rightptr = temp;
        leftptr++;
        rightptr--;
    }
}
