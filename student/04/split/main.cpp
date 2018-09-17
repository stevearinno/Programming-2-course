#include <iostream>
#include <string>
#include <vector>
#include <sstream>


// TODO: Implement split function here
std::vector <std::string> split(std::string line_, char separator_, bool ignoreEmpty_ = false){

    std::vector <std::string> v;
    std::string v_;
    std::string::size_type len;
    int posBegin = 0;
    int countChar = 0;
    while (line_.find(separator_) != std::string::npos){
        int posSep = line_.find(separator_);
        line_.replace(posSep,1," ");
    }

    len = line_.length();
    v.empty();
    for (unsigned int a = 0; a < len; ++a){

        if (line_.substr(a,1) != " "){
            countChar += 1;
            if (a != len-1){
                if (line_.substr(a+1,1) == " "){
                    v.push_back(line_.substr(posBegin,countChar));
                }
            }
            else{
                v.push_back(line_.substr(posBegin,countChar));
            }

        }
        else{
            if (a != len-1){
                posBegin = a+1;

            }
            if (ignoreEmpty_ == 0){
                v.push_back(line_.substr(a,1));
            }

            countChar = 0;
        }

    }
    return v;
}
// Do not change main function


int main()
{
    std::string line = "";
    std::cout << "Enter a string: ";
    getline(std::cin, line);
    std::cout << "Enter the separator character: ";
    char separator = getchar();

    std::vector< std::string > parts  = split(line, separator);
    std::cout << "Splitted string including empty parts: " << std::endl;
    for( auto o : parts ) {
        std::cout << o << std::endl;
    }

    std::vector< std::string > parts_no_empty  = split(line, separator, true);
    std::cout << "Splitted string ignoring empty parts: " << std::endl;
    for( auto o : parts_no_empty ) {
        std::cout << o << std::endl;
    }
}
