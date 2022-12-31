#include <iostream>
#include <sstream>
#include "keyExpansion.h"
#include "decryption.h"

using namespace std;

void convertStr_Hex(string ascii_str, char *hex_str){
    int loop = 0;
    int i = 0;
    for (int i = 0; i < 16; i ++){
        sprintf((char *)(hex_str+loop),"%02X", ascii_str[i]);
        loop += 2;
        if(i == 15) continue;
        sprintf((char *)(hex_str + loop), " ");
        loop ++;
        
    }
}

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
    int len = key_input.length();

    char hex_str [3*len - 1];
    convertStr_Hex(key_input, hex_str);    

    //creating the key. 
    istringstream key_stream(hex_str);
    unsigned char key [16];

    cout << "Key: ";
    for(int i = 0; i < 16; i++){
	    key_stream >> hex >> x;
		key [i] = x; 
        cout << hex << (int) key [i] << " ";
	}
    cout << endl;

    //creating 11 keys for the 11 rounds
    unsigned char expandedKey [176];
    key_expansion(key, expandedKey);

    //decryption
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