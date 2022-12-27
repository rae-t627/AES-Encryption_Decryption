#include <iostream>
#include <sstream>
#include "keyExpansion.h"
#include "encryption.h"

using namespace std;

int main() {
    string plaintext, key_input;

    
    cout << "Please enter the text to be encrypted: ";
    getline(cin, plaintext);
    
    //padding the plaintext:
    int plaintext_len = plaintext.length();
    int plaintext_padded_len;

    //creating length of padded plaintext
    if (plaintext_len % 16 != 0){
        plaintext_padded_len = (16 - (plaintext_len % 16)) + plaintext_len;
    }
    else{
        plaintext_padded_len = plaintext_len;
    }

    //allocating memory on the heap for cipherText
    unsigned char * cipherText = new unsigned char[plaintext_padded_len];
    unsigned char * encryptedText = new unsigned char[plaintext_padded_len];

    //creating cipherText with padding
    for (int i = 0; i < plaintext_padded_len; i ++){
        if (i >= plaintext_len){
            cipherText [i] = 0;
        }
        else{
            cipherText[i] = plaintext [i];
        }
        //cout << cipherText[i] << endl;
    }



    cout << "Please ensure that the key is of 16 characters. Please enter key: ";
    getline (cin, key_input);

    //creating the key. 
    // ADD THE PART WHERE UTF 8 is converted to HEX
    istringstream key_stream(key_input);
    unsigned char key [16];
    unsigned int x;
    for(int i = 0; i < 16; i++){
	    key_stream >> hex >> x;
		key [i] = x; 
        //cout << (int) key [i] << endl;
	}

    //creating 11 keys for the 11 rounds

    unsigned char expandedKey [176];

    key_expansion(key, expandedKey);

    for(int i = 0; i < plaintext_padded_len; i += 16 ){

        encrypt(cipherText + i, expandedKey);

    }

    cout << "Encrypted Text" << endl;
    for (int i = 0; i < plaintext_padded_len; i++){
        cout << hex << (int) cipherText [i] << " ";
    }
    cout << endl;
    

    return 0;
}