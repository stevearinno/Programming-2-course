#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>
#include <cmath>


using namespace std;

// rounds the price to two decimal places. It will return string
std::string rounding( double num )
{
    std::string numString = "";

    num = ((num * 100) + 0.5)/100;          // this is for the rounding (addition of 0.5)
    numString = to_string((int)num) + "." + to_string((int)((num - (int)num) * 100));
    return numString;
}

// splits the input (from the user) and returns the vector of string
std::vector<std::string> split(const std::string& s, const char delimiter, bool ignore_empty = false){
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

struct Product {
    string product_name;
    double price;
};

// checks if the command has sufficient parameter
bool isGoodCommand(std::string command, int split_result){
    if (command == "stores" || command == "cheapest"){
        if (split_result != 2){
            return 0;
        }
    }
    else if (command == "chains" || command == "products"){
        if (split_result != 1){
            return 0;
        }
    }
    else if (command == "selection"){
        if (split_result != 3){
            return 0;
        }
    }
    return 1;
}

// checks all the chains listed in the map
// input: map obtained from the input file
// output: list of available chains (returned as a vector of string)
std::vector <std::string> checkChains(std::map <std::string, std::map<std::string, std::vector<Product>>>& shopping_list){
    std::vector <std::string> chain_list;
    map <std::string, std::map<std::string, std::vector<Product>> > :: iterator it = shopping_list.begin();
    for (; it != shopping_list.end(); it++){
        chain_list.push_back(it -> first);
    }
    return chain_list;
}

// checks all the stores of the particular chain
// input: map of the particular chain
// output: list of available stores (returned as a vector of string)
std::vector <std::string> checkStores(map<std::string, std::vector<Product>>& chain_list){
    std::vector <std::string> store_list;
    map<std::string, std::vector<Product>> :: iterator it = chain_list.begin();
    for (; it != chain_list.end(); it++){
        store_list.push_back(it -> first);
    }
    return store_list;
}

// checks all the products and the prices on a particular chain and store
// input: vector of Product
// output: list of products and prices (returned as a vector of string)
std::vector <std::string> checkProductPrice(std::vector <Product> product_price_list){
    std::vector <std::string> product_price_vector;
    std::string product_price ="";
    std::string price ="";

    for (auto a : product_price_list){
        if (a.price != 0){
            product_price = a.product_name + " " + rounding(a.price);
        }
        else{
            product_price = a.product_name + " out of stock";
        }
        product_price_vector.push_back(product_price);

    }
    return product_price_vector;
}

// checks the lists of chain-store pairs of the cheapest product (from the user input).
// returns the pair of price (as a string and vector of chain-store pairs.
std::pair<std::string, vector<std::string>> checkCheapest(std::string product, map<std::string, std::map<std::string, std::vector<Product>>>& shopping_list){
    string chain = "";
    string store = "";
    map <double, std::vector<std::string>> chain_store_list;
    double compared_price = 100;
    map<std::string, std::map<std::string, std::vector<Product>>> :: iterator it1 = shopping_list.begin();

    for (; it1 != shopping_list.end(); it1++){
        map<std::string, std::vector<Product>> :: iterator it2 = it1 -> second.begin();
        for (; it2 != it1 -> second.end(); it2++){
            chain = it1 -> first;
            store = it2 -> first;

            int vectorSize = shopping_list[chain][store].size();
            bool flag = 1;

            for ( int vectorIndex = 0; vectorIndex < vectorSize; vectorIndex++){
                string current_product = shopping_list[it1 -> first][it2 -> first].at(vectorIndex).product_name;
                double current_price = shopping_list[it1 -> first][it2 -> first].at(vectorIndex).price;
                if (current_product == product && flag == 1){
                    if (current_price <= compared_price && current_price != 0){
                        compared_price = current_price;
                        std::string chain_store = chain + " " + store;
                        chain_store_list[compared_price].push_back(chain_store);
                        flag = 0;
                    }
                    else if (current_price == 0){
                        if (compared_price == 100){
                            compared_price = current_price;
                        }
                        std::string chain_store = chain + " " + store;
                        chain_store_list[compared_price].push_back(chain_store);
                        flag = 0;
                    }
                }
            }


        }
    }

    std::string cheapest_price = rounding(compared_price) + " euros";

    return {cheapest_price, chain_store_list[compared_price]};
}

// checks and return all products (vector of string) available in the map (file input)
std::vector <std::string> checkAllProducts(map<std::string, std::map<std::string, std::vector<Product>>>& shopping_list){
    string chain = "";
    string store = "";
    std::vector <std::string> product_list;
    map<std::string, std::map<std::string, std::vector<Product>>> :: iterator it1 = shopping_list.begin();

    for (; it1 != shopping_list.end(); it1++){
        map<std::string, std::vector<Product>> :: iterator it2 = it1 -> second.begin();
        for (; it2 != it1 -> second.end(); it2++){
            chain = it1 -> first;
            store = it2 -> first;

            int vector_size = shopping_list[chain][store].size();
            for ( int vectorIndex = 0; vectorIndex < vector_size; vectorIndex++){
                string current_product = shopping_list[it1 -> first][it2 -> first].at(vectorIndex).product_name;
                if (std::find(product_list.begin(), product_list.end(), current_product) == product_list.end())
                {
                    product_list.push_back(current_product);
                }
            }
        }
    }
    return product_list;
}

// prints all strings in the input vector
// input: the vector of strings (usually it is the result of a command)
// output: it will not return any value, but it will print the result
void printStringVector(std::vector <std::string>& vectorString){
    int vector_size = vectorString.size();
    for (int a = 0; a < vector_size ; a++){
        cout << vectorString.at(a) << endl;
    }
}

int main()
{
    std::map <std::string, std::map<std::string, std::vector<Product>> > shopping_list;
    
    string filename = "";

    cout << "Input file: ";
    getline(cin, filename);

    ifstream file_object(filename);
        if ( not file_object ) {
            cout << "Error: the input file cannot be opened" << endl;
            return 1;
        }

        else {
            // read the input file line by line
            string line_file;
            while ( getline(file_object, line_file) ) {

                std::vector<std::string> parts = split(line_file, ';', true);
                double amount;
                // checks if the all the lines from input file has correct data
                if (parts.size() != 4){
                    cout << "Error: the file has an erroneous line" << endl;
                    return EXIT_FAILURE;
                }
                else {
                    // checks if any product is "out-of-stock" and price will be stored as 0
                    if (parts.at(3) == "out-of-stock"){
                        amount = 0;
                    }
                    else{
                        amount = std::stod(parts.at(3));
                    }

                    std::string chain = parts.at(0);
                    std::string store = parts.at(1);
                    std::string product = parts.at(2);
                    int vectorSize = shopping_list[chain][store].size();

                    // inserting all the data from input file to the map
                    if (vectorSize == 0){
                        shopping_list[chain][store].push_back({product, amount});
                    }
                    else{
                        bool isNotFound = 1;
                        for ( int vectorIndex = 0; vectorIndex < vectorSize; vectorIndex++){
                            while (isNotFound == 1){
                                if (shopping_list[chain][store].at(vectorIndex).product_name == product){
                                    shopping_list[chain][store].at(vectorIndex).price = amount;
                                    isNotFound = 0;
                                }
                                else{
                                    shopping_list[chain][store].push_back({product, amount});
                                    isNotFound = 0;
                                }
                            }
                        }
                    }
                }
            }
            file_object.close();

            // the input from the user starts from this point
            while (true){

                std::cout << "> ";
                string command_line;
                getline(std::cin, command_line);

                std::vector <std::string> parts_command = split(command_line, ' ', true);
                std::string command = parts_command.at(0);

                bool isCommandOK = isGoodCommand(command, parts_command.size());

                if(command == "chains" && isCommandOK){
                    std::vector <std::string> chain_list = checkChains(shopping_list);

                    printStringVector(chain_list);
                }
                else if(command == "stores" && isCommandOK){
                    string chain = parts_command.at(1);                    
                    std::vector <std::string> store_list = checkStores(shopping_list[chain]);                    

                    // error checking if the chain is valid
                    if (store_list.size() == 0){
                        cout << "Error: an unknown chain" << endl;
                    }
                    else {
                        printStringVector(store_list);
                    }

                }
                else if(command == "selection" && isCommandOK){
                    string chain = parts_command.at(1);
                    string store = parts_command.at(2);

                    std::vector <std::string> store_list = checkStores(shopping_list[chain]);
                    std::vector <std::string> product_price_list = checkProductPrice(shopping_list[chain][store]);
                    sort(product_price_list.begin(), product_price_list.end());

                    // error checking if the chain and store are valid
                    if (store_list.size() == 0){
                        cout << "Error: unknown chain" << endl;
                    }
                    else if (product_price_list.size() == 0){
                        cout << "Error: unknown store" << endl;
                    }
                    else{
                        printStringVector(product_price_list);
                    }

                }
                else if(command == "cheapest" && isCommandOK){
                    string product = parts_command.at(1);

                    std::pair<std::string, vector<std::string>> cheapest_product_list = checkCheapest(product, shopping_list);

                    // error check if the product is on the list/selection
                    if (cheapest_product_list.second.size() == 0){
                        cout << "Product is not part of product selection." << endl;
                    }
                    else if(cheapest_product_list.second.size() != 0 && cheapest_product_list.first.substr(0,3) == "0.0"){
                        cout << "The product is temporarily out of stock everywhere." << endl;
                    }
                    else{
                        cout << cheapest_product_list.first << endl;
                        sort(cheapest_product_list.second.begin(), cheapest_product_list.second.end());
                        printStringVector(cheapest_product_list.second);
                    }

                }
                else if(command == "products" && isCommandOK){

                    std::vector <std::string> product_list = checkAllProducts(shopping_list);

                    sort(product_list.begin(), product_list.end());
                    printStringVector(product_list);

                }
                else if(command == "quit"){
                    return EXIT_SUCCESS;
                }

                else if(!isCommandOK){
                    cout << "Error: error in command " << command << endl;
                }
                else {
                    cout << "Error: unknown command" << endl;
                }

            }
        }
}

