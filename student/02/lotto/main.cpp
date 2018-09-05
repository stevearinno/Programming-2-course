#include <iostream>

using namespace std;

unsigned long int factorial(int factor);

int main()
{
    int total;
    int drawn;
    cout << "Enter the total number of lottery balls: ";
    cin >> total;

    cout << "Enter the number of drawn balls: ";
    cin >> drawn;

    if (total < 0)
    {
        cout << "The number of balls must be a positive number.";
    }
    else if (drawn > total)
    {
        cout << "The maximum number of drawn balls is the total amount of balls.";
    }
    else
    {
        unsigned long int prob = factorial(total)/(factorial(total-drawn)*factorial(drawn));
        cout << "The probability of guessing all " << drawn << " balls correctly is 1/"<< prob << endl;
    }

    return 0;
}

unsigned long int factorial(int factor)
{
    unsigned long int result = 1;
        for (int a=1; a <= factor; ++a){
            result *= a;
        }
        return result;
}


