#include <cstdlib>
#include <iostream>
#include <vector>


void read_integers(std::vector< int >& ints, int count)
{
    int new_integer = 0;

    for(int i = 0; i < count; ++i)
    {
        std::cin >> new_integer;
        // TODO: Implement your solution here
        //ints.at(i) = new_integer;
        ints.push_back(new_integer);
    }
}

bool same_values(const std::vector<int>& ints )
{
    int counter = 0;
    for(unsigned int j = 1; j < ints.size(); ++j)
    {
        if(ints.at(0) == ints.at(j)){
            ++counter;
        }
    }
    return counter;
}

bool is_ordered_ascending(const std::vector<int>& ints)
{
    for(unsigned int k = 0; k < ints.size()-1; ++k)
    {
        if(ints.at(k) > ints.at(k+1)){
            return 0;
        }
    }
    return 1;
}

bool is_arithmetic_series(const std::vector<int>& ints)
{
    int delta = ints.at(0)-ints.at(1);
    for(unsigned int l = 0; l < ints.size()-1; ++l)
    {
        if((ints.at(l) - ints.at(l+1)) != delta){
            return 0;
        }
    }
    return 1;
}

bool is_geometric_series(const std::vector<int>& ints)
{
    double diff = ints.at(0)/ints.at(1);
    for(unsigned int m = 0; m < ints.size()-1; ++m)
    {
        if(((double)ints.at(m) / ints.at(m+1)) != diff){
            return 0;
        }
    }
    return 1;
}

// TODO: Implement your solution here


int main()
{
    std::cout << "How many integers are there? ";
    int how_many = 0;
    std::cin >> how_many;

    std::cout << "Enter the integers: ";
    std::vector<int> integers;
    read_integers(integers, how_many);

    if(same_values(integers))
        std::cout << "All the integers are the same" << std::endl;
    else
        std::cout << "All the integers are not the same" << std::endl;

    if(is_ordered_ascending(integers))
        std::cout << "The integers are in an ascending order" << std::endl;
    else
        std::cout << "The integers are not in an ascending order" << std::endl;

    if(is_arithmetic_series(integers))
        std::cout << "The integers form an arithmetic series" << std::endl;
    else
        std::cout << "The integers do not form an arithmetic series" << std::endl;

    if(is_geometric_series(integers))
        std::cout << "The integers form a geometric series" << std::endl;
    else
        std::cout << "The integers do not form a geometric series" << std::endl;

    return EXIT_SUCCESS;
}
