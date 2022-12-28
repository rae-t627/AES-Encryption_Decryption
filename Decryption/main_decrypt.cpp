#include <iostream>
#include <sstream>
#include "keyExpansion.h"
#include "decryption.h"

using namespace std;

int main() {

    string cipherText, key_input;

    cout << "Please enter the encrypted text: ";
    getline(cin, cipherText);

    int cipherText_len = 0;

    for(int i = 0; i < cipherText.length(); i ++){
        if (cipherText [i] == ' ')
            cipherText_len ++;
    }

    cipherText_len ++;

    unsigned char *decryptedText = new unsigned char [cipherText_len];

    istringstream input_stream(cipherText);
    unsigned int x;
    for(int i = 0; i < cipherText_len; i++){
	    input_stream >> hex >> x;
		decryptedText [i] = x; 
	}

    cout << "Please ensure that the key is of 16 characters. Please enter key: ";
    getline (cin, key_input);

    //creating the key. 
    //ADD THE PART WHERE UTF 8 is converted to HEX
    istringstream key_stream(key_input);
    unsigned char key [16];
    
    for(int i = 0; i < 16; i++){
	    key_stream >> hex >> x;
		key [i] = x; 
	}

    //creating 11 keys for the 11 rounds

    unsigned char expandedKey [176];
    key_expansion(key, expandedKey);

    for(int i = 0; i < cipherText_len; i += 16){
        decrypt (decryptedText + i, expandedKey);
    }

    cout << endl;

    cout << "The decrypted text is: ";
    for(int i = 0; i < cipherText_len; i ++){
        cout << decryptedText [i];
    }
    cout << endl << endl;

    return 0;
}