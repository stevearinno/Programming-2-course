#include <iostream>
#include <string>

bool palindrome_recursive (const std::string word_){

    int len = word_.size();
    if (len != 0){
        char start = word_.at(0);
        char end = word_.at(len-1);
        if (start == end){
            return true;
        }
        else{
            return false;
        }
        int len = word_.size();
        return palindrome_recursive(word_.substr(1, len-2));
    }

}


int main()
{
    std::cout << "Enter a word: ";
    std::string word;
    std::cin >> word;

    if(palindrome_recursive(word)){
        std::cout << word << " is a palindrome" << std::endl;
    } else {
        std::cout << word << " is not a palindrome" << std::endl;
    }
}
