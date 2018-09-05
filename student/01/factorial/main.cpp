#include <iostream>

const unsigned int MAX = 33;

int main()
{
    unsigned int factor = 0;
    unsigned long long result = 1;
    std::cout << "Enter a positive integer (from interval [1.." << MAX << "]): ";
    std::cin >> factor;
    if (factor > MAX){
        std::cout << "Too big number" << std::endl;
    }
    else if (factor <= 1){
        std::cout << "Factorial of " << factor << " is " << 0 << std::endl;
    }
    else{
        for (unsigned int a=1; a <= factor; ++a){
            result *= a;
        }
        std::cout << "Factorial of " << factor << " is " << result << std::endl;
    }
}
