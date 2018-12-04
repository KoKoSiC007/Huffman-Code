//ДОБАВЬИТЬ КОЛИЧЕСТВО НУЛЕЙ КОТОРОЕ ТЫ ДОБАВИЛ!!!!!!!!!

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <list>

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

// reading from files
const std::vector<char> readFile(const std::string fileName) {
	std::ifstream inputFile = std::ifstream(fileName);
	std::vector<char> inputChars = std::vector<char>();
	char currentCharacter = 0;
	while (inputFile.get(currentCharacter)) {
		inputChars.push_back(currentCharacter);
	}
	inputFile.close();
	return inputChars;
}
// writing from files
void wriringOnFile(const std::vector<char>encodedText, const std::string fileName){
    std::ofstream outputFile = std::ofstream(fileName);
    for (int i = 0; i < encodedText.size();i++){
        outputFile << encodedText[i];
    }
    outputFile.close();
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
const std::map<char,int> counter(const std::string& s)
{
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
//        std::cout<<sonOnLeft->character << sonOnLeft->qty <<' '<<sonOnLeft->left << ' '<<sonOnLeft->right<<std::endl;
        nodeList.pop_front();
        Node *sonOnRight = nodeList.front();
//        std::cout << sonOnRight->character << sonOnRight->qty << ' '<< sonOnRight->left << ' ' << sonOnRight->right<<std::endl;
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

std::string printedTable(const std::string inputString){

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

const std::vector<char> bitWriting( std::string bitString){
    std::vector<char> encodedText;
    char zero = 0;
    encodedText.push_back(zero);
    int count = 0;
    int indexInVectorChars = 0;
    
    if(bitString.size() % 8 != 0 ){
        for (int i = 0; bitString.size()%8 != 0 ; i++) {
            bitString = "0" + bitString;
        }
    }
    for (int i = 0 ; i<bitString.size(); i++) {
        if (count == 8){
            encodedText.push_back(0);
            count = 0;
            indexInVectorChars++;
        }
        if (bitString[i] == '0'){
            encodedText[indexInVectorChars] <<=1 ;
            count++;
        }else{
            encodedText[indexInVectorChars] += true;
            count++;
        }
    }
    
    return encodedText;
}

int main(int argc, const char * argv[]) {
	
    const std::string inputPath = "/Users/kokos/Documents/Prog/SuperDifficultProgram/InputText.txt";
    const std::string outputPath ="/Users/kokos/Documents/Prog/SuperDifficultProgram/OutputText.txt";
	const std::string inputFileName = inputPath;
    const std::string outputFileName = outputPath;
	const std::vector<char> inputChars = readFile(inputFileName);
    std::string inputString = std::string(inputChars.begin(), inputChars.end());
    std::cout << inputString << std::endl;
//    const std::vector<char> encodedData = encodeData(inputChars);
//    std::string encodedString = std::string(encodedData.begin(), encodedData.end());
////    std::cout << encodedString << std::endl;
//    const std::vector<char> decodedData = decodeData(encodedData);
//    std::string decodedString = std::string(decodedData.begin(), decodedData.end());
////    std::cout << decodedString << std::endl;
    std::cout << std::endl;
    Node *test = creatingTree(creatyNodeList(counter(inputString)));
    createTable(test);
    std::string bitString = printedTable(inputString);
    std::vector<char> testing = bitWriting(bitString);
    wriringOnFile(testing,outputFileName);
//    std::string bitStrint = printedTable(inputString);
//    std::cout <<"This string of bits: "<< bitStrint;
    
	return 0;
}
