//
//  main.cpp
//  Huffmans Coding
//
//  Created by Grisha Okin on 04/12/2018.
//  Copyright © 2018 Grisha Okin. All rights reserved.
//



#include "Functions.hpp"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <bitset>

const std::string decodingText(const std::string encodedBitString,Node *root){
    std::string decodedString;
    std::string buff;
    int index = 0;
    Node *point = root;
    while(index != encodedBitString.size()){

        if (encodedBitString[index] =='0'){
            point = point->left;
        }else{
            point = point->right;
        }
        if((point->left==NULL) && (point->right == NULL)){
            decodedString += point->character;
            point = root;
        }
        index++;
    }
    
    return decodedString;
}

int main(int argc, const char * argv[]) {
    const std::string inputPath = "/Users/kokos/Desktop/InputText.txt";
    const std::string outputPath ="/Users/kokos/Desktop/OutputText.txt";
    const std::string tablePath = "/Users/kokos/Desktop/Table.txt";
    const std::string inputEncoded = "/Users/kokos/Desktop/OutputText.txt";
    const std::string inputDecoded = "/Users/kokos/Desktop/Decoded.txt";
    const std::string inputFileName = inputPath;
    const std::string outputFileName = outputPath;
    const std::string tableFileName = tablePath;
    const std::string inputEncodedFileName = inputEncoded;
    const std::string inputDecodedName = inputDecoded;
    /* encoding text part*/
    const std::string inputString = readFile(inputFileName);
    std::cout << inputString;
    Node *test = creatingTree(creatyNodeList(counter(inputString)));
    createTable(test);
    std::string bitString = createBitString(inputString);
    std::vector<char> testing = bitWriting(bitString);
    wriringOnFile(testing,outputFileName);
    writingTableOnFile(tableFileName,addingMissingZeros(bitString),counter(inputString));
    std::cout<<std::endl;
    /* decoding text part*/
    const std::string inputEncodedString = readFile(inputEncodedFileName);
    int localtest = readAddZeros(tableFileName);
    const std::string encodedBitString = writeEncodeText(inputEncodedString, localtest);
    Node *decoding = creatingTree(creatyNodeList(readTableOnFile(tableFileName)));
    std::string decodedTxt = decodingText(encodedBitString, decoding);
    std::cout << decodedTxt<< std::endl;
    wriringOnFile(decodedTxt, inputDecodedName);
    
    return 0;
}
