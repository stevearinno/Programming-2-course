#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

const std::string HELP_TEXT = "S = store id1 i2\n P = print id\n"
                              "C = count id\n D = depth id";


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

void print(std::string id_, std::map <std::string, std::vector<std::string> >& network_list_, int counter){
    int len = network_list_[id_].size();
    counter += 1;
    for (int b = 0; b < len; b++){
        for (int c = 1; c <= counter; c++){
            std::cout << "..";
        }
        std::cout << network_list_[id_].at(b) << std::endl;
        if ( network_list_.find(network_list_[id_].at(b)) != network_list_.end() ) {
            // The name was found in the map.
            print(network_list_[id_].at(b), network_list_, counter);
        }
    }
}

int count(std::string id_, std::map <std::string, std::vector<std::string> >& network_list_, int counter){
    int len = network_list_[id_].size();
    for (int b = 0; b < len; b++){
        counter += 1;
        if ( network_list_.find(network_list_[id_].at(b)) != network_list_.end() ) {
            // The name was found in the map.
            return count(network_list_[id_].at(b), network_list_, counter)+counter;
        }
        //else{
            //return count(network_list_[id_].at(b), network_list_, counter)+counter;
        //}
    }
    return counter;
}

int depth(std::string id_, std::map <std::string, std::vector<std::string> >& network_list_){
    int len = network_list_[id_].size();
    for (int b = 0; b < len; b++){
        if ( network_list_.find(id_) != network_list_.end() ) {
            // The name was found in the map.
            return depth(network_list_[id_].at(b), network_list_) + 1;
        }
    }
    return 1;
}

int main()
{
    // TODO: Implement the datastructure here
    std::map <std::string, std::vector<std::string> > network_list;

    while(true){
        std::string line;
        std::cout << "> ";
        getline(std::cin, line);
        std::vector<std::string> parts = split(line, ' ', true);        

        std::string command = parts.at(0);

        if(command == "S" or command == "s"){
            if(parts.size() != 3){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
            }
            std::string id1 = parts.at(1);
            std::string id2 = parts.at(2);

            // TODO: Implement the command here!
            if ( network_list.find(id1) != network_list.end() ) {
                // The name was found in the map.
                network_list.at(id1).push_back(id2);

            } else {
                 //The name was not found in the map.
                network_list[id1].push_back(id2);
            }


        } else if(command == "P" or command == "p"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
            if ( network_list.find(id) != network_list.end() ) {
                // The name was found in the map.
                std::cout << id << std::endl;
                print(id, network_list, 0);
            } else {
                //The name was not found in the map.
                std::cout << id << std::endl;
            }

        } else if(command == "C" or command == "c"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
            std::cout << std::to_string(count(id, network_list, 0)) << std::endl;


        } else if(command == "D" or command == "d"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!

                std::cout << std::to_string(depth(id, network_list)) << std::endl;


        } else if(command == "Q" or command == "q"){
           return EXIT_SUCCESS;
        } else {
            std::cout << "Erroneous command!" << std::endl << HELP_TEXT;
        }
    }
}
