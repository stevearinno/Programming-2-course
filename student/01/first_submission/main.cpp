#include <iostream>
#include <string>

int main()
{
    std::string name = "";
    std::cout << "Enter your name: ";
    getline(std::cin, name);

    int age = 0;
    std::cout << "Enter your age: ";
    std::cin >> age;

    std::cout << "Pleased to meet you, " << name << "!" << std::endl;
    std::cout << "On your next birthday you will be " << age+1 <<" years old!";


    return EXIT_SUCCESS;
}
