// WAP to implement Huffman Coding .The program should encode a given input text using Huffman's Algorithm ,generating codes for character.It should also decode Huffman-encoded text back to its orignal form, effiecntly handling fix length and variable length encoding and decoding

#include <bits/stdc++.h>
using namespace std;

struct Node
{
    char data;
    int freq;
    Node *left;
    Node *right;

    Node(char data, int freq)
    {
        this->data = data;
        this->freq = freq;
        left = right = nullptr;
    }
};

struct Compare
{
    bool operator()(Node *a, Node *b)
    {
        return a->freq > b->freq;
    }
};

Node *buildHuffmanTree(map<char, int> &freqMap)
{
    priority_queue<Node *, vector<Node *>, Compare> minHeap;

    for (auto &pair : freqMap)
    {
        minHeap.push(new Node(pair.first, pair.second));
    }

    while (minHeap.size() > 1)
    {
        Node *left = minHeap.top();
        minHeap.pop();
        Node *right = minHeap.top();
        minHeap.pop();

        Node *internalNode = new Node('$', left->freq + right->freq);
        internalNode->left = left;
        internalNode->right = right;

        minHeap.push(internalNode);
    }

    return minHeap.top();
}

void generateCodes(Node *root, string code, map<char, string> &huffmanCodes)
{
    if (!root)
    {
        return;
    }

    if (!root->left && !root->right)
    {
        huffmanCodes[root->data] = code;
    }

    generateCodes(root->left, code + "0", huffmanCodes);
    generateCodes(root->right, code + "1", huffmanCodes);
}

string encode(string &s, map<char, string> &huffmanCodes)
{
    string encodedString = "";
    for (char c : s)
    {
        encodedString += huffmanCodes[c];
    }
    return encodedString;
}

string decode(string &encodedString, Node *root)
{
    string decodedString = "";
    Node *current = root;

    for (char bit : encodedString)
    {
        if (bit == '0')
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }

        if (!current->left && !current->right)
        {
            decodedString += current->data;
            current = root; // Reset to root for next character
        }
    }

    return decodedString;
}

void displayFrequencies(map<char, int> &freqMap)
{
    cout << "\nCharacter Frequencies:\n";
    for (auto &pair : freqMap)
    {
        cout << "'" << pair.first << "': " << pair.second << endl;
    }
}

void displayHuffmanCodes(map<char, string> &huffmanCodes)
{
    cout << "\nHuffman Codes:\n";
    for (auto &pair : huffmanCodes)
    {
        cout << "'" << pair.first << "': " << pair.second << endl;
    }
}

int main()
{
    string s;
    cout << "Enter the string to encode: ";
    cin >> s;

    map<char, int> freqMap;
    for (auto ch : s)
    {
        freqMap[ch]++;
    }

    displayFrequencies(freqMap);

    Node *root = buildHuffmanTree(freqMap);

    map<char, string> huffmanCodes;
    generateCodes(root, "", huffmanCodes);

    displayHuffmanCodes(huffmanCodes);

    string encodedString = encode(s, huffmanCodes);
    cout << "\nEncoded string: " << encodedString << endl;

    string decodedString = decode(encodedString, root);
    cout << "Decoded string: " << decodedString << endl;

    int originalBits = s.length() * 8;
    int compressedBits = encodedString.length();

    cout << "\nOriginal size (bits): " << originalBits << endl;
    cout << "Compressed size (bits): " << compressedBits << endl;

    return 0;
}
