#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    int nomor = 1;
    cout << "Enter a number: ";
    cin >> nomor;

    int cubed = pow(nomor,3);

    if (cubed/nomor != pow(nomor,2)){
        cout << "Error! The cube of " << nomor << " is not " << cubed << "." << endl;
    }
    else{
        cout << "The cube of " << nomor << " is " << cubed << "." << endl;
    }
    return 0;
}
