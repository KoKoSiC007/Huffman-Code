//
//  main.cpp
//  Huffmans Coding
//
//  Created by Grisha Okin on 04/12/2018.
//  Copyright © 2018 Grisha Okin. All rights reserved.
//

//ДОБАВЬИТЬ КОЛИЧЕСТВО НУЛЕЙ КОТОРОЕ ТЫ ДОБАВИЛ!!!!!!!!!

#include "Functions.hpp"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <bitset>


const std::string writeEncodeText (const std::string inputEncodedString,int uslessZero = 6){
    std::string encodedBitString;
    std::bitset<8> readableChar;
    for (int i = 0; i<inputEncodedString.size()-1; i++){
        readableChar = (inputEncodedString[i]);
        encodedBitString += readableChar.to_string();
        readableChar.reset();
    }
    readableChar = (inputEncodedString[inputEncodedString.size()]);
    
    return encodedBitString;
}

int main(int argc, const char * argv[]) {
//    char x = 65;
//    std::cout << x;
//    std::bitset<8> text ('0');
//    int bitstring =  text.to_ulong();
//    char c = bitstring;
//    std::cout << "The set of bits in bitset<8> is: ( "<< text<< " )"<< std::endl;
//    std::cout << bitstring << std::endl;
//    std::cout << c << std::endl;

//
//    char symb = '\x01A';
//    int tr =(int)(symb);
//    printf("%c cahracter",tr);
//    printf("\n");
    //    delta codeing
    //    const std::vector<char> encodedData = encodeData(inputChars);
    //    std::string encodedString = std::string(encodedData.begin(), encodedData.end());
    //   std::cout << encodedString << std::endl;
    //    const std::vector<char> decodedData = decodeData(encodedData);
    //    std::string decodedString = std::string(decodedData.begin(), decodedData.end());
    //   std::cout << decodedString << std::endl;
    
    const std::string inputPath = "/Users/kokos/Desktop/InputText.txt";
    const std::string outputPath ="/Users/kokos/Desktop/OutputText.txt";
    const std::string tablePath = "/Users/kokos/Desktop/Table.txt";
    const std::string inputEncoded = "/Users/kokos/Desktop/OutputText.txt";
    const std::string inputFileName = inputPath;
    const std::string outputFileName = outputPath;
    const std::string tableFileName = tablePath;
    const std::string inputEncodedFileName = inputEncoded;
    
    const std::string inputString = readFile(inputFileName);
    std::cout << inputString;
    
    Node *test = creatingTree(creatyNodeList(counter(inputString)));
    createTable(test);
    std::string bitString = createBitString(inputString);
    std::cout << bitString << std::endl;
    std::vector<char> testing = bitWriting(bitString);
    wriringOnFile(testing,outputFileName);
    writingTableOnFile(tableFileName,addingMissingZeros(bitString));
    
    const std::string inputEncodedString = readFile(inputEncodedFileName);
//    std::cout << inputEncodedString<< std::endl;

    const std::string encodedBitString = writeEncodeText(inputEncodedString);
    std::cout << encodedBitString<< std::endl;
    //    std::string bitStrint = printedTable(inputString);
    //    std::cout <<"This string of bits: "<< bitStrint;
    
    return 0;
}
