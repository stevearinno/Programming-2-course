#include <iostream>

using namespace std;

int divisible_by_3_or_7 (int value_) {
    if (value_ % 3 == 0|| value_ % 7 == 0) {
        return value_ + divisible_by_3_or_7(value_ - 1);
    }
    else if (value_ == 2) {
        return 0;
    }
    else {
        divisible_by_3_or_7(value_ - 1);
    }
}

int main()
{
    int value;
    cout << "Enter an upper bound: ";
    cin >> value;

    cout << "Sum of non-negative integers between 0 and "<< value << " and divisible by 3 or 7 is " << divisible_by_3_or_7(value) << endl;

    return 0;
}
