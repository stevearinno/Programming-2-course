#include "calculations.hh"
#include <iostream>
#include <iomanip>
#include <sstream>  // for implementing function string_to_double
#include <string>
#include <vector>

using namespace std;

const string GREETING_AT_END = "Thanks and see you later!";

// Utility function to sections a string at delimiters
vector< string > split(const string& s,
                       const char delimiter,
                       bool ignore_empty = false);

// Function string_to_double changes a string comprising a real number
// into a float type value for calculations.
// It returns true, if parameter s comprised a real.
// It returns false, if s was not a valid real number.
// The converted float will be assigned into reference parameter result.
// The implementation of the function uses stringstream for the sake of example.
bool string_to_double(const string& s, double& result);


// TODO: Explore the following data structures!
struct Command {
    string str;
    vector<string>::size_type parameter_number;
    bool exit;
    double(*action)(double, double);
};

const vector<Command> COMMANDS = {
    {"+", 2, false, addition},
    {"-", 2, false, subtraction},
    {"*", 2, false, multiplication},
    {"/", 2, false, division},
    {"PLUS", 2, false, addition},
    {"MINUS", 2, false, subtraction},
    {"TIMES", 2, false, multiplication},
    {"DIVIDED", 2, false, division},
    {"ADDITION", 2, false, addition},
    {"SUBTRACTION", 2, false, subtraction},
    {"MULTIPLICATION", 2, false, multiplication},
    {"DIVISION", 2, false, division},
    {"SUM", 2, false, addition},
    {"DIFFERENCE", 2, false, subtraction},
    {"PRODUCT", 2, false, multiplication},
    {"QUOTIENT", 2, false, division},
    {"ADD", 2, false, addition},
    {"INCREASE", 2, false, addition},
    {"SUBTRACT", 2, false, subtraction},
    {"DECREASE", 2, false, subtraction},
    {"MULTIPLY", 2, false, multiplication},
    {"DIVIDE", 2, false, division},
    {"^", 2, false, exponentiation},
    {"POWER", 2, false, exponentiation},
    {"EXP", 2, false, exponentiation},
    {"STOP", 0, true, nullptr},
    {"QUIT", 0, true, nullptr},
    {"EXIT", 0, true, nullptr},
    {"Q", 0, true, nullptr}
};


int main() {

    // Using precision of two decimals in printing
    cout.precision(2);
    cout << fixed;

    while ( true ) {
        cout << "calculator> ";

        string line = "";
        getline(cin, line);

        if ( line.empty() ) {
            // If the user inputs an empty line, the execution of the program will end.
            cout << GREETING_AT_END << endl;
            break;
        }

        vector<string> pieces = split(line, ' ', true);

        if(pieces.size() == 0){
            continue;
        }

        string command_to_be_executed = pieces.at(0);

        // TODO: Implement command execution here!
        int i=0;
        char c;
        while (command_to_be_executed[i])
        {
            c=command_to_be_executed[i];
            if (islower(c)) c=toupper(c);
            command_to_be_executed[i] = c;
            i++;
        }

        bool non_number_operands = true;
        bool unknown_command = true;
        unsigned int number_of_parameters = pieces.size()-1;
        bool wrong_param_numbers = true;
        bool exit_status = false;
        double calc_result;

        string operand_1 = "";
        string operand_2 = "";

        if (number_of_parameters >= 2){
            operand_1 = pieces.at(1);
            operand_2 = pieces.at(2);
        }



        vector<Command>::iterator it;
        for(auto it = COMMANDS.begin(); it!= COMMANDS.end();it++){
            double var_1;
            double var_2;
            bool isOperand01Double = string_to_double(operand_1, var_1);
            bool isOperand02Double = string_to_double(operand_2, var_2);
            if (it->str == command_to_be_executed){
                unknown_command = false;
            }
            if (it->parameter_number == number_of_parameters){
                wrong_param_numbers = false;
                if (number_of_parameters == 0){
                    non_number_operands = false;
                    exit_status = it->exit;
                }
                else if(isOperand01Double && isOperand02Double){
                //else if(isdigit(operand_1[0]) && isdigit(operand_2[0])){
                    non_number_operands = false;
                    double(*func)(double, double) = it->action;
                    calc_result = func(var_1, var_2);

                    //calc_result = it->action(stod(operand_1),stod(operand_2));
                }
            }

        }

        if (unknown_command){
            cout << "Error: unknown command." << endl;
        }
        else if (wrong_param_numbers){
            cout << "wrong number of parameters." << endl;
        }
        else if (non_number_operands){
            cout << "Error: a non-number operand." << endl;
        }
        else if (exit_status){
            cout << GREETING_AT_END << endl;
            return 0;
        }
        else{
            cout << calc_result << endl;
        }


    }
}





// This function exemplifies istringstreams.
// It would be possible to use function stod of string to convert a string to a double,
// but to recognize all error cases would be more complicated with it at this phase of
// education. It is easier to use the boolean type return value that can be
// examined at calling point as done in the implementation below.
bool string_to_double(const string& s, double& result) {
    // Initializing input stream of istringstream type the string that will scanned
    // with ">>" or getline.
    istringstream stream(s);

    double tmp;

    // Reading input value in a normal way with ">>" operator.
    // You can operate istringstreams with the same operations as cin
    // and other ifstreams.
    stream >> tmp;

    if ( not stream ) {
        return false;
    }

    // ws is special operator that skips all the word delimiters (such as spaces)
    // until it meets something else
    stream >> ws;

    // If parameter s is a string comprising a valid real number, it cannot succeed
    // other characters than spaces.
    // Since previous ">> ws" operation threw the spaces away, at this point
    // the input stream should contain nothing. If it does, then it is erroneous.
    // Let's try to read a character from the input stream.
    // If this fails, because the input stream has no characters left, then all is right.
    // If it succeeds, then string s has something that it should not have.
    stream.get();

    if ( stream ) {
        return false;
    } else {
        result = tmp;
        return true;
    }
}

// Model implementation of good old split function
vector< string > split(const string& s, const char delimiter, bool ignore_empty){
    vector<string> result;
    string tmp = s;

    while(tmp.find(delimiter) != string::npos)
    {
        string word = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and word.empty()))
        {
            result.push_back(word);
        }

    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}
