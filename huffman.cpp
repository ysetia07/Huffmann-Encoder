#include <iostream>
#include <unordered_map>
#include <queue>
#include <string>
using namespace std;
class treeNode
{
public:
    char data;
    int freq;
    treeNode *right;
    treeNode *left;

    treeNode(char data, int freq, treeNode *left, treeNode *right)
    {
        this->data = data;
        this->freq = freq;
        this->left = left;
        this->right = right;
    };
};

void getHuffmanCode(unordered_map<char, string> &huffmanCode, treeNode *root, string code)
{
    if (root == NULL)
    {
        return;
    }
    if (root->left == NULL && root->right == NULL)
    {
        huffmanCode[root->data] = code;
    }
    getHuffmanCode(huffmanCode, root->left, code + '0');
    getHuffmanCode(huffmanCode, root->right, code + '1');
}

class compare
{
public:
    bool operator()(treeNode *a, treeNode *b)
    {
        return a->freq > b->freq;
    }
};

string huffmanTree(string input, unordered_map<char, string> &huffmanCode)
{
    unordered_map<char, int> frequencies;
    for (int i = 0; i < input.size(); i++){
        frequencies[input[i]]++;
    }

    priority_queue<treeNode *, vector<treeNode *>, compare> pqFreq;

    unordered_map<char, int>::iterator it = frequencies.begin();

    while (it != frequencies.end()){
        treeNode *newNode = new treeNode(it->first, it->second, NULL, NULL);
        pqFreq.push(newNode);
        it++;
    }

    while (pqFreq.size() != 1){
        treeNode *firstMin = pqFreq.top();
        pqFreq.pop();
        treeNode *secondMin = pqFreq.top();
        pqFreq.pop();
        int sumFreq = firstMin->freq + secondMin->freq;
        treeNode *sumNode = new treeNode('\0', sumFreq, firstMin, secondMin);
        pqFreq.push(sumNode);
    }
    
    treeNode *root = pqFreq.top();

    getHuffmanCode(huffmanCode, root, "");
    string encoded = "";
    for (int i = 0; i < input.size(); i++)
    {
        encoded += huffmanCode[input[i]];
    }
    
    return encoded;
}

int main()
{
    unordered_map<char, string> huffmanCode;
    cout << "Enter the input string: ";
    string input;
    cin >> input ;
    string encoded = huffmanTree(input, huffmanCode);
    cout << "\n----------------------------------------------------\n" << endl;
    cout << "Huffman Codes are: " << endl;
    unordered_map<char, string> :: iterator it = huffmanCode.begin();
    while(it!= huffmanCode.end()){
        cout << it->first << "  :   " <<it->second<< endl;
        it++;
    }
    cout << "\n----------------------------------------------------\n" << endl;

    cout << "Encoded string is: \n"<< encoded << endl;
    cout << "\n----------------------------------------------------\n" << endl;

    cout << "Size before encoding   : "<< input.length()*8 << endl;
    cout << "Size after encoding    : " <<encoded.length() << endl;
    cout << "\n----------------------------------------------------\n" << endl;

}