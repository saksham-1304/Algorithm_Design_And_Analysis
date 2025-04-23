#include <iostream>
#include <queue>
#include <unordered_map>
using namespace std;

class Node {
public:
    char ch;
    int freq;
    Node* left;
    Node* right;

    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

class Compare {
public:
    bool operator()(Node* l, Node* r) {
        return l->freq > r->freq;
    }
};

class HuffmanCoding {
private:
    unordered_map<char, int> freq;
    unordered_map<char, string> huffmanCode;
    Node* root;

    void calculateFrequency(const string& text) {
        for (char ch : text)
            freq[ch]++;
    }

    void buildHuffmanTree() {
        priority_queue<Node*, vector<Node*>, Compare> pq;

        for (auto pair : freq)
            pq.push(new Node(pair.first, pair.second));

        while (pq.size() > 1) {
            Node* left = pq.top(); pq.pop();
            Node* right = pq.top(); pq.pop();

            Node* merged = new Node('\0', left->freq + right->freq);
            merged->left = left;
            merged->right = right;
            pq.push(merged);
        }

        root = pq.top();
    }

    void generateCodes(Node* node, string str) {
        if (!node)
            return;
        if (!node->left && !node->right)
            huffmanCode[node->ch] = str;

        generateCodes(node->left, str + "0");
        generateCodes(node->right, str + "1");
    }

    string encodeText(const string& text) {
        string encoded = "";
        for (char ch : text)
            encoded += huffmanCode[ch];
        return encoded;
    }

    string decodeText(const string& encoded) {
        string decoded = "";
        Node* curr = root;
        for (char bit : encoded) {
            curr = (bit == '0') ? curr->left : curr->right;
            if (!curr->left && !curr->right) {
                decoded += curr->ch;
                curr = root;
            }
        }
        return decoded;
    }

public:
    HuffmanCoding() : root(nullptr) {}

    void encodeAndDecode(const string& text) {
        calculateFrequency(text);
        buildHuffmanTree();
        generateCodes(root, "");

        cout << "Huffman Codes:\n";
        for (auto pair : huffmanCode)
            cout << pair.first << ": " << pair.second << "\n";

        string encoded = encodeText(text);
        cout << "\nEncoded Text: " << encoded << "\n";

        string decoded = decodeText(encoded);
        cout << "Decoded Text: " << decoded << "\n";
    }
};

int main() {
    string text;
    cout << "Enter a string to encode: ";
    getline(cin, text);

    HuffmanCoding huffman;
    huffman.encodeAndDecode(text);

    return 0;
}
