#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

std::vector <std::string> split(std::string line_){

    std::vector <std::string> v;
    std::string v_;
    std::string::size_type len;
    //bool counterSpace = 0;
    int posBegin = 0;
    int countChar = 0;

    len = line_.length();
    v.empty();
    for (unsigned int a = 0; a < len; ++a){
        // checks if the first char is not "space", then prepare to input to the vector
        if (line_.substr(a,1) != " "){
            countChar += 1;
            // checks if this char is at the end of the line
            if (a != len-1){
                // checks if the next char is a "space" and if it is,
                // it means, this is the end of the word and put it into the vector
                if (line_.substr(a+1,1) == " "){
                    v.push_back(line_.substr(posBegin,countChar));
                    //counterSpace = 0;
                }
            }
            // but if it is a "space", directly put into the vector
            else{
                v.push_back(line_.substr(posBegin,countChar));
            }

        }
        // otherwise, if it is a "space"
        else{
            // if this char is not at the end of the line, point to the next char
            // because the next char could be a non "space" char
            if (a != len-1){
                posBegin = a+1;

            }

            //if (ignoreEmpty_ == 0 && (counterSpace == 1 || a == 0 || a == len-1)){
            //    v.push_back(" ");
            //    counterSpace = 1;
            //}
            //if (ignoreEmpty_ == 0 && a == len-1 && line_.substr(a,1) == " "){
            //    v.push_back(" ");
            //}


            countChar = 0;
            //counterSpace = 1;
        }
    }
    return v;
}

int main()
{
    string filename = "";
    string line;
    map <string, vector<int> > word_list;
    vector <int> line_number;
    int line_num = 0;

    cout << "Input file: ";
    getline(cin, filename);

    ifstream file_object(filename);
    if ( not file_object ) {
        cout << "Error! The file " << filename << " cannot be opened." << endl;
        return 1;
    }
    else {
        while ( getline(file_object, line) ){
            std::vector< std::string > parts  = split(line);
            line_num +=1;
            for( auto o : parts ) {
                //std::cout << o << std::endl;
                if ( word_list.find(o) != word_list.end() ) {
                    // The word was found in the map.
                    word_list.at(o).push_back(line_num);
                } else {
                     //The word was not found in the map.
                    word_list[o].push_back(line_num);
                }
            }

        }

    }
    map <string, vector<int>> :: iterator it = word_list.begin();
    for (; it != word_list.end(); it++){
        cout << it -> first <<  " " << it -> second.size() << ": ";
        int row_len = it -> second.size();
        for(int a = 0; a < row_len; a++){
            if (row_len == 1){
                cout << it -> second.at(a) << endl;
            }
            else if (row_len != 1 && a != row_len-1){
                cout << it -> second.at(a) << ", ";
            }
            else if (row_len != 1 && a == row_len-1){
                cout << it -> second.at(a) << endl;
            }
        }
    }
    return 0;
}
