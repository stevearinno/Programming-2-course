#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int main()
{
    string enc_key;
    string enc_tex;
    int j = 0;
    char d;
    bool char_upper(string str_upper);
    bool char_check(string str_check);
    void swap(char &i2, char &j2);

//   cout << static_cast< int >( 'z' );
    cout << "Enter the encryption key: ";
    getline(cin, enc_key);

    if (enc_key.length() != 26){
        cout << "Error! The encryption key must contain 26 characters." << endl;
    }
    else if (char_upper(enc_key)){
        cout << "Error! The encryption key must contain only lower case characters." << endl;
    }
    else if (char_check(enc_key)){
        cout << "Error! The encryption key must contain all alphabets a-z." << endl;
    }
    else{
        cout << "Enter the text to be encrypted: ";
        getline(cin, enc_tex);
        for (int e = 0; e <= enc_tex.length()-1; ++e){
            d = enc_tex.at(e);
            swap(enc_tex.at(e),enc_key.at(static_cast< int >( d )-97));
        }
        cout << "Encrypted text: " << enc_tex << endl;
    }
    return 0;
}

bool char_upper(string str_upper){
    int i=0;    char c;
    bool result1;
    for (int a = 0; a <= str_upper.length()-1; ++a){
        c = str_upper.at(a);
        if (isupper(c)){
            return 1;
        }
        else{
            result1 = 0;
        }
    }

    return result1;
}

bool char_check(string str_check){
    string::size_type temp = 0;
    bool result;
    for (char letter = 'a'; letter <= 'z'; ++letter){
        temp = str_check.find(letter);
        if (temp != string::npos){
            result = 0;
        }
        else{
            result = 1;
            return result;
        }
    }
    return result;
}

void swap(char &i2, char &j2){
    i2 = j2;
}
