#include <iostream>

using namespace std;

int main()
{   int num = 0;
    cout << "How many numbers would you like to have? ";
    cin >> num;

    for( int a = 1; a <= num; a = a + 1 ) {
       cout << a << endl;
    }
}
