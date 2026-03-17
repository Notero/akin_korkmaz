//
//  main.cpp
//  pa02
//
//  Created by Akin Korkmaz on 11/3/24.
//

// Academic Integrity statement - “I Akin Korkmaz ([ak235142]) affirm that
// this program is entirely my own work and that I have neither developed my code with any
// another person, nor copied any code from any other person, nor permitted my code to be copied
// or otherwise used by any other person, nor have I copied, modified, or otherwise used programs
// created by others. I acknowledge that any violation of the above terms will be treated as
// academic dishonesty.”

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
//global count to ensure we add all the needed X for the output
int padCount = 0;

unsigned long long calculate32bitBlock(char c1, char c2, char c3, char c4) {
    // shift ASCII to the correct position to get a decimal value
    unsigned long long block = ((unsigned long long)c1 << 24) | ((unsigned long long)c2 << 16) | ((unsigned long long)c3 << 8) | (unsigned long long)c4;
    return block;
}

unsigned long long calculate32bitChecksum(std::string input){
    
    unsigned long long checksum = 0;
    
    char pad = 'X';
    //puts a LF at the end of the current input
    input += '\n';

    //checks if pad needed
    if (input.length() % 4 != 0) {
        //gets the pad count needed
        int paddin = (4 - (input.length() % 4)) % 4;
        //pads
        for (int i = 0; i < paddin; i++) {
            input += pad;
            padCount++;
        }
    }
    
    unsigned long long block;
    //adds all blocks together
    for (int i = 0; i < input.length(); i+=4) {
        block = calculate32bitBlock(input[i], input[i+1], input[i+2], input[i+3]);
        checksum += block;
    }
    
    //returns checksum without masking
    return checksum;
}

unsigned int calculate16bitBlock(char c1, char c2) {
    // shift ASCII to the correct position to get a decimal value
    unsigned int block = ((unsigned int)c1 << 8) | (unsigned int)c2;
    return block;
}

unsigned int calculate16bitChecksum(std::string input){
    
    unsigned int checksum = 0;
    
    char pad = 'X';
    
    input += '\n';
    //pads 1 X if neccecary
    if (input.length() % 2 != 0) {
        input += pad;
        padCount++;
    }
    


    unsigned int block;
    //calculates the sum of all blocks
    for (int i = 0; i < input.length(); i+=2) {
        block = calculate16bitBlock(input[i], input[i+1]);
        checksum += block;
    }
    //returns all sum without masking
    return checksum;
}

unsigned int calculate8bitChecksum(std::string input){
    
    unsigned int checksum = 0;
    //adds all ascii values in the string
    for (auto i : input) {
        checksum += i;
    }
    //+10 for newline ascii and returns the unmasked checksum
    return checksum + 10;
}

int main(int argc, const char * argv[]) {
    
    std::string message;
    //error handling
    if (argc < 3 || argc > 3) {
        std::cerr << "Commmand Line has too many or too less arguments.\nCorrect usage is pa02.out filename.txt checksumsize" << std::endl;
        return 1;
    }
    //gets the bit size of checksum and converts it to int
    int checksumSize = std::stoi(argv[2]);
    
    //error handling
    if (checksumSize != 8 && checksumSize != 16 && checksumSize != 32) {
        std::cerr << "Valid checksum sizes are 8,16 and 32" << std::endl;
        return 1;
    }
    //opens the file
    std::ifstream file(argv[1], std::ios::binary);
    //checks if file is opened or not
    if (!file.is_open()) {
        std::cerr << "File couldn't be opened" << std::endl;
        return 1;
    }
    //gets whole line from the input.txt
    std::getline(file, message);
    //decleration of checksum
    unsigned int checksum = 0;
    
    //switch to calculate the correct bit checksum
    switch (checksumSize) {
            case 8:
                //gets the unmasked value
                checksum = calculate8bitChecksum(message);
                checksum = checksum & 0xFF; // Mask to 8 bits
                std::cout << message + '\n' << std::endl; // print the message with the LF
                printf("8-bit checksum is %02x for all %zu characters\n", checksum, message.length() + 1); //output
                break;
            case 16:
                //gets the unmasked value
                checksum = calculate16bitChecksum(message);
                checksum = checksum & 0xFFFF; // Mask to 16 bits
                //check if any pad has been added and if so prints the padded massage if not prints the message with added newline char
                if (padCount != 0) {
                    std::cout << message + '\n' + 'X' << std::endl;
                }else{
                    std::cout << message + '\n' << std::endl;
                }
                
                printf("16-bit checksum is %04x for all %zu characters\n", checksum, message.length() + padCount + 1); // output
                break;
            case 32:
                unsigned long long lchecksum = calculate32bitChecksum(message);
                lchecksum = lchecksum & 0xFFFFFFFF; // Mask to 32 bits
                // this part adds newline char and any padding required for output
                message += '\n';
                //pads
                if (padCount != 0) {
                    for (int i = 0; i < padCount; i++) {
                        message += 'X';
                    }
                }
                //echo message
                std::cout << message << std::endl;
                printf("32-bit checksum is %08llx for all %zu characters\n", lchecksum, message.length()); //output
                break;
        }
    
    

    return 0;
}
