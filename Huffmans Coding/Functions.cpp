//
//  Functions.cpp
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
// reading from files
const std::string readFile(const std::string fileName) {
    std::ifstream inputFile = std::ifstream(fileName);
    std::vector<char> inputChars = std::vector<char>();
    char currentCharacter = 0;
    while (inputFile.get(currentCharacter)) {
        inputChars.push_back(currentCharacter);
    }
    inputFile.close();
    std::string inputString = std::string(inputChars.begin(), inputChars.end());
    return inputString;
}
// writing from files
void wriringOnFile(const std::vector<char>encodedText, const std::string fileName){
    std::ofstream outputFile = std::ofstream(fileName);
    for (int i = 0; i < encodedText.size();i++){
        outputFile << encodedText[i];
    }
    outputFile.close();
}

void writingTableOnFile (const std::string fileName,int addZeros){
    std::ofstream TableFile = std::ofstream(fileName);
    
    TableFile<<addZeros<<std::endl;
    std::map<char,std::vector<bool>>::iterator iter;
    for (iter = table.begin(); iter != table.end();iter++){
        TableFile << iter->first<<' ';
        for (int i = 0 ; i < iter->second.size(); i++) {
            if (iter->second[i] == true){
                TableFile << "1";
            }else{
                TableFile << "0";
            }
        }
        TableFile << std::endl;
    }
}

//encoding Func
const std::vector<char> encodeData(const std::vector<char> decodedData) {
    const std::size_t length = decodedData.size();
    std::vector<char> encodedData = std::vector<char>();
    
    char lastChar = 0;
    for(std::size_t i = 0; i < length; ++i) {
        const char currentChar = decodedData[i];
        const char encodedChar = currentChar - lastChar;
        encodedData.push_back(encodedChar);
        lastChar = currentChar;
    }
    return encodedData;
}

// decoding Func
const std::vector<char> decodeData(const std::vector<char> encodedData) {
    const std::size_t length = encodedData.size();
    std::vector<char> decodedData = std::vector<char>();
    
    char lastChar = 0;
    for(std::size_t i = 0; i < length; ++i) {
        const char currentChar = encodedData[i];
        const char decodedChar = currentChar + lastChar;
        decodedData.push_back(decodedChar);
        lastChar = decodedChar;
    }
    
    return decodedData;
}
//add chars in array and counting them
const std::map<char,int> counter(const std::string& s){
    std::map<char,int> charsInString;
    for (auto character : s) {
        charsInString[character]++;
    }
    return charsInString;
}

std::list<Node *> creatyNodeList(const std::map<char,int> charsInString){
    
    std::list<Node *> nodeList = std::list<Node *>();
    std::map<char,int>::iterator iter;
    for(auto iter=charsInString.begin(); iter!=charsInString.end(); iter++) {
        Node *branch = new Node();
        branch->character = iter->first;
        branch->qty = iter->second;
        nodeList.push_back(branch);
    }
    return nodeList;
}

Node *creatingTree( std::list<Node *> nodeList){
    
    while (nodeList.size() != 1) {
        nodeList.sort(sorting());
        Node *sonOnLeft = nodeList.front();
        nodeList.pop_front();
        Node *sonOnRight = nodeList.front();
        nodeList.pop_front();
        Node *father = new Node(sonOnLeft, sonOnRight);
        nodeList.push_back(father);
    }
    Node *root = nodeList.front();
    return root;
}

std::vector<bool> code;
std::map<char,std::vector<bool>> table;
/* table view
 m 1010
 g 11100
 t 0
 /n 11101
 */
void createTable(Node *root){
    
    if (root->left != NULL){
        code.push_back(0);
        createTable(root->left);
    }
    if (root->right != NULL){
        code.push_back(1);
        createTable(root->right);
    }
    if (root->character){
        table[root->character] = code;
        /*
         std::cout << "Character is " << root->character << ' ';
         for (int i = 0 ; i<code.size(); i++) {
         std::cout << code[i];
         }
         std::cout<< std::endl;
         */
    }
    code.pop_back();
}

std::string createBitString(const std::string inputString){
    std::string bitString;
    
    for (int i = 0 ; i<inputString.length(); i++) {
        std::vector<bool> tbl = table[inputString[i]];
        
        for (int j = 0; j<tbl.size(); j++) {
            if (tbl[j]==0) {
                bitString += "0";
            }else{
                bitString += "1";
            }
        }
    }
    return bitString;
}

//local func just for reverse std::bitset
std::bitset<8> fliped(std::bitset<8> readibleBits){
    for (int i = 0; i < readibleBits.size()/2; i++){
        bool bits = readibleBits[i];
        readibleBits[i] = readibleBits[readibleBits.size()-i-1];
        readibleBits[readibleBits.size()-i-1] = bits;
    }
    return readibleBits;
}

const int addingMissingZeros (const std::string bitString){
    return bitString.size()%8;
}
//create encoded Text
const std::vector<char> bitWriting(std::string bitString){
    std::vector<char> encodedText;
    std::bitset<8> readibleBits;
    std::cout << bitString<<std::endl;
    bitString += '0' * (bitString.size()%8);
    std::cout << bitString<<std::endl;
    int count = 0;
    for(int i = 0; i < bitString.size(); i++){
        if (bitString[i] =='1'){
            readibleBits.set(count,true);
        }
        count++;
        if (count == 8 ){
            count = 0;
            int controllChar = fliped(readibleBits).to_ulong();
            char encodedChar = controllChar;
            encodedText.push_back(encodedChar);
            readibleBits.reset();
        }
    }
//    char text = encodedText[encodedText.size()-1];

    return encodedText;
}
