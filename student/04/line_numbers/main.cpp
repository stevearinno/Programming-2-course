#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    string filename = "";
    string outFilename = "";

    ofstream myFile;

    cout << "Input file: ";
    getline(cin, filename);

    cout << "Output file: ";
    getline(cin, outFilename);

    myFile.open(outFilename);

    ifstream file_object(filename);
        if ( not file_object ) {
            cout << "Error! The file " << filename << " cannot be opened." << endl;
        } else {
            int lineNumber = 1;
            string line;
            while ( getline(file_object, line) ) {
                myFile << lineNumber << " " <<line << endl;
                lineNumber += 1;
            }
            file_object.close();
            myFile.close();
        }

}
