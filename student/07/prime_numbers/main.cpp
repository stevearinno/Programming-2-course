#include <iostream>

using namespace std;

int main()
{
    int upperBound;
    cout << "Enter an upper bound: ";
    cin >> upperBound;

    cout << "Prime numbers smaller than " << to_string(upperBound) << ":" << endl;

    bool numbers[upperBound-1];

    numbers[0] = false;
    numbers[1] = false;

    for (int lessThanBound = 2; lessThanBound < upperBound; lessThanBound++){
        int counter = 0;
        for (int numberDivider = 2; numberDivider < lessThanBound; numberDivider++) {
            if (lessThanBound%numberDivider == 0){
                numbers[lessThanBound] = false;
                break;
            }
            else{
                numbers[lessThanBound] = true;
            }
        }
    }

    for (int indexArray = 2; indexArray < upperBound; indexArray++){
        if (numbers[indexArray] == true){
            cout << to_string(indexArray) << " ";
        }
    }

    cout << endl;

    return 0;
}
