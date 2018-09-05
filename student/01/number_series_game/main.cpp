#include <iostream>

using namespace std;

int main()
{   int num = 0;
    cout << "How many numbers would you like to have? ";
    cin >> num;

    for( int a = 1; a <= num; a = a + 1 ) {
        int b = a%3;
        int c = a%7;
        if (b==0 && c!=0){
            cout << "zip" << endl;
        }
        else if(b!=0 && c==0){
            cout << "boing" << endl;
        }
        else if(b==0 && c==0){
            cout << "zip boing" << endl;
        }
        else {
            cout << a << endl;
        }
    }
}
