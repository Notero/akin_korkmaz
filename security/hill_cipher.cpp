//Created by Akin Korkmaz 26 Sep 2024

/*============================================================================
| Assignment: pa01 - Encrypting a plaintext file using the Hill cipher
|
| Author: Akin Korkmaz
| Language: c, c++, Java, go, python, rust
| To Compile: javac pa01.java
| gcc -o pa01 pa01.c
| g++ -o pa01 pa01.cpp
| go build pa01.go
| rustc pa01.rs
| To Execute: java -> java pa01 kX.txt pX.txt
| or c++ -> ./pa01 kX.txt pX.txt
| or c -> ./pa01 kX.txt pX.txt
| or go -> ./pa01 kX.txt pX.txt
| or rust -> ./pa01 kX.txt pX.txt
| or python -> python3 pa01.py kX.txt pX.txt
| where kX.txt is the keytext file
| and pX.txt is plaintext file
| Note:
| All input files are simple 8 bit ASCII input
| All execute commands above have been tested on Eustis
|
| Class: CIS3360 - Security in Computing - Fall 2024
| Instructor: McAlpin
| Due Date: per assignment
+===========================================================================*/

#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>

std::string StrtoLower(const std::string &source) {
    std::string destinationString = source;
    std::transform(destinationString.begin(), destinationString.end(), destinationString.begin(), ::tolower);
    return destinationString;
}

std::string createPad(int padCount) {
    return std::string(padCount, 'x'); // Create a string of 'x' characters
}

int main(int argc, const char *argv[]) {
    // Check for correct number of arguments
    if (argc < 3) {
        std::cerr << "Usage: ./pa01 kX.txt pX.txt" << std::endl;
        return -1;
    }

    int keySize = 0;
    std::string messagepiece;
    std::string Message;

    const char Alphabet[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

    // Open the key file
    std::ifstream keyFile(argv[1]);
    if (!keyFile || !(keyFile >> keySize) || keySize < 2 || keySize > 9) {
        std::cerr << "Invalid key size." << std::endl;
        return -1;
    }

    // Create key matrix
    std::vector<std::vector<int>> Key(keySize, std::vector<int>(keySize));
    for (int i = 0; i < keySize; i++) {
        for (int j = 0; j < keySize; j++) {
            keyFile >> Key[i][j];
        }
    }
    keyFile.close();
    
    std::cout << "Key Matrix:" << std::endl;
    
    for (int i = 0; i < keySize; i++) {
        for (int j = 0; j < keySize; j++) {
            std::cout << Key[i][j] << " ";
        }
        std::cout << std::endl;
    }

    // Open the message file
    std::ifstream messageFile(argv[2]);
    if (!messageFile) {
        std::cerr << "Error opening message file." << std::endl;
        return -1;
    }

    // Read message and remove punctuation
    while (messageFile >> messagepiece) {
        Message += messagepiece;
    }
    messageFile.close();

    // Remove punctuation from message
    Message.erase(std::remove_if(Message.begin(), Message.end(), ::ispunct), Message.end());

    // Lowercase the message
    Message = StrtoLower(Message);
    
    //removes any character other than a - z
    Message.erase(std::remove_if(Message.begin(), Message.end(), [](char c) {
    return !(c >= 'a' && c <= 'z'); // Keep only 'a' to 'z'
    }), Message.end());
    
    int format = 0;
    std::cout << "Plain Text: \n" << std::endl;
    for (auto c : Message) {
        
        std::cout << c;
        format++;
        if (format == 80) {
            std::cout << std::endl;
            format = 0;
        }
    }
    std::cout << std::endl;

    // Pad message if necessary
    int padCount = Message.length() % keySize;
    if (padCount != 0) {
        Message += createPad(keySize - padCount); // Add the necessary padding
    }

    // Encrypt the message in blocks
    std::string encrptBlock(keySize, ' ');
    std::vector<std::string> encryptedMessage;

    for (size_t i = 0; i < Message.length(); i += keySize) {
        int ValBlock[keySize];
        
        // Convert block to numerical values
        for (int j = 0; j < keySize; j++) {
            ValBlock[j] = Message[i + j] - 'a'; // Convert character to index
        }

        // Encrypt the block using the key
        for (int i = 0; i < keySize; i++) {
            int result = 0; // Reset result for each row
            for (int j = 0; j < keySize; j++) {
                result += ValBlock[j] * Key[i][j];
            }
            encrptBlock[i] = Alphabet[result % 26]; // Assign encrypted character
        }

        // Store encrypted block
        encryptedMessage.push_back(encrptBlock);
    }

    // Output the encrypted message
    std::cout << "Cipher Text:" << std::endl;
    Message = "";
    format = 0;
    for (const auto &block : encryptedMessage) {
        Message += block;
    }
    for (auto c : Message) {
        
        std::cout << c;
        format++;
        if (format == 80) {
            std::cout << std::endl;
            format = 0;
        }
    }
    std::cout << std::endl;

    return 0;
}



/*=============================================================================
| I Akin Korkmaz (ak235142) affirm that this program is
| entirely my own work and that I have neither developed my code together with
| any another person, nor copied any code from any other person, nor permitted
| my code to be copied or otherwise used by any other person, nor have I
| copied, modified, or otherwise used programs created by others. I acknowledge
| that any violation of the above terms will be treated as academic dishonesty.
+=============================================================================*/
