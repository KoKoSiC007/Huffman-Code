//
//  Functions.hpp
//  Huffmans Coding
//
//  Created by Grisha Okin on 04/12/2018.
//  Copyright © 2018 Grisha Okin. All rights reserved.
//

#ifndef Functions_hpp
#define Functions_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <bitset>


class Node {
public:
    char character = NULL;
    int qty = 0;
    Node *left = NULL, *right = NULL;
    
    Node(){};
    
    Node (Node *l, Node *r){
        left = l;
        right = r;
        qty = l->qty + r->qty;
    }
};
struct sorting{
    bool operator()(Node *l, Node *r){
        return l->qty < r->qty;
    }
};

extern std::vector<bool> code;
extern std::map<char,std::vector<bool>> table;
const std::string readFile(const std::string fileName);
void wriringOnFile(const std::vector<char>encodedText, const std::string fileName);
const std::vector<char> encodeData(const std::vector<char> decodedData);
const std::vector<char> decodeData(const std::vector<char> encodedData);
const std::map<char,int> counter(const std::string& s);
std::list<Node *> creatyNodeList(const std::map<char,int> charsInString);
Node *creatingTree( std::list<Node *> nodeList);
void createTable(Node *root);
std::string createBitString(const std::string inputString);
const std::vector<char> bitWriting( std::string bitString);
void writingTableOnFile (const std::string fileName,int addZeros,const std::map<char,int> thesaurus);
const int addingMissingZeros (const std::string bitString);
const std::string writeEncodeText (const std::string inputEncodedString,int uslessZero);
const int readAddZeros(const std::string);
std::map<char,int> readTableOnFile(const std::string fileName);
#endif /* Functions_hpp */
