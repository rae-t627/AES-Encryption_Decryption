## AES Encryption and Decryption

In this program, we have implemented 128 bit key AES.

### AES Encryption:
It mainly consists of two parts: Key expansion and Encryption

#### Key Expansion:
For 128 bit key AES encryption, there are 11 rounds. For each round, one key is needed. All the keys need to be of 16 bytes.
From the 16 byte key given by the user, we generate 10 more keys to use in the following rounds. The procedure for generating the keys is as follows:
1. Create a 176 byte array (here, expandedKey) inorder to store the keys. 
2. The first 16 bytes will be used to store the original input key. 
3. The last four bytes of the current key will be passed through the g function (explained below).
4. The output from the g function will be XORed with the first four bytes of the current key to generate the first four bytes of the next key
   The first four bytes of the next key will be XORed with the 5th - 8th bytes of the current key to generate the 5th - 8th bytes of the next key
   The 5th - 8th bytes of the next key will be XORed with the 9th - 12th bytes of the current key to generate the 9th - 12th bytes of the next key
   The 9th - 12th bytes of the next key will be XORed with the last four bytes of the current key to generate the last four bytes of the next key
5. This will be continued until the keys are generated

##### G function:
1. The 4 bytes are shifted one to the left. eg: {B0, B1, B2, B3} becomes {B1, B2, B3, B0}
2. These bytes are substituted using the  forward substitution box for aes encryption.
3. The first byte is then XORed with the round constant.

<img width="407" alt="image" src="https://user-images.githubusercontent.com/105154462/209668441-c7f3f703-3a89-4cff-ab9f-25e660427a14.png">
