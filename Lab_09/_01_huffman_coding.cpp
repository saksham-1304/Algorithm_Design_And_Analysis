#include <iostream>
#include <queue>
#include <unordered_map>
using namespace std;

struct Node
{
    char ch;
    int freq;
    Node *left, *right;
    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

struct Compare
{
    bool operator()(Node *l, Node *r)
    {
        return l->freq > r->freq;
    }
};

void generateCodes(Node *root, string str, unordered_map<char, string> &huffmanCode)
{
    if (!root)
        return;
    if (!root->left && !root->right)
        huffmanCode[root->ch] = str;
    generateCodes(root->left, str + "0", huffmanCode);
    generateCodes(root->right, str + "1", huffmanCode);
}

void encodeAndDecode(const string &text)
{
    unordered_map<char, int> freq;
    for (char ch : text)
        freq[ch]++;

    priority_queue<Node *, vector<Node *>, Compare> pq;
    for (auto pair : freq)
        pq.push(new Node(pair.first, pair.second));

    while (pq.size() > 1)
    {
        Node *left = pq.top();
        pq.pop();
        Node *right = pq.top();
        pq.pop();
        Node *merged = new Node('\0', left->freq + right->freq);
        merged->left = left;
        merged->right = right;
        pq.push(merged);
    }

    Node *root = pq.top();
    unordered_map<char, string> huffmanCode;
    generateCodes(root, "", huffmanCode);

    cout << "Huffman Codes:\n";
    for (auto pair : huffmanCode)
        cout << pair.first << ": " << pair.second << "\n";

    string encoded = "";
    for (char ch : text)
        encoded += huffmanCode[ch];
    cout << "\nEncoded Text: " << encoded << "\n";

    string decoded = "";
    Node *curr = root;
    for (char bit : encoded)
    {
        curr = (bit == '0') ? curr->left : curr->right;
        if (!curr->left && !curr->right)
        {
            decoded += curr->ch;
            curr = root;
        }
    }
    cout << "Decoded Text: " << decoded << "\n";
}

int main()
{
    string text;
    cout << "Enter a string to encode: ";
    getline(cin, text);
    encodeAndDecode(text);
    return 0;
}
