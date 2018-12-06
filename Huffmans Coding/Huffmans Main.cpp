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

char show(Node *Tree,std::string code)
{
    if (Tree->left == NULL && Tree->right == NULL){
        return Tree->character;
    }
    if (code.front()=='0'){
//        std::cout<<code<<std::endl;
        return show(Tree->left, code.substr(1));
    }
    if (code.front()=='1'){
//        std::cout<<code<<std::endl;
        return show(Tree->right, code.substr(1));
    }
    return 0;
}

const std::string decodingText(const std::string encodedBitString,Node *root){
    std::string decodedString;
    std::string buff;
    int index = 0;
    while(index != encodedBitString.size()){
        if (show(root, buff)){
            decodedString += show(root, buff);
//            std::cout << decodedString<<std::endl;
            buff.clear();
        }else{
            std::cout << encodedBitString[index]<<std::endl;
            buff+=encodedBitString[index];
        }
    }
    
    return decodedString;
}

int main(int argc, const char * argv[]) {
    std::string str = "0";
    std::cout << str.substr(1).empty();
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
    /* encoding text part*/
    const std::string inputString = readFile(inputFileName);
    std::cout << inputString;
    Node *test = creatingTree(creatyNodeList(counter(inputString)));
    createTable(test);
    std::string bitString = createBitString(inputString);
    std::cout << bitString << std::endl;
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
    
    //    std::string bitStrint = printedTable(inputString);
    //    std::cout <<"This string of bits: "<< bitStrint;
    
    return 0;
}
