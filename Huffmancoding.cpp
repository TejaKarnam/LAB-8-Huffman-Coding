
#include <iostream>
#include <queue>
#include <vector>
#include <string>
using namespace std;

struct Node {
    char ch;
    int freq, order;
    Node *left, *right;

    Node(char c, int f, int o) {
        ch = c;
        freq = f;
        order = o;
        left = right = nullptr;
    }
};

struct Compare {
    bool operator()(Node* a, Node* b) {
        if (a->freq != b->freq)
            return a->freq > b->freq;

        bool ai = (a->left != nullptr);
        bool bi = (b->left != nullptr);

        if (ai != bi)
            return ai;

        return a->order > b->order;
    }
};

void printCodes(Node* root, string code, int& bits) {
    if (root == nullptr)
        return;

    if (root->left == nullptr && root->right == nullptr) {
        cout << root->ch << " : " << code << endl;
        bits += root->freq * code.length();
        return;
    }

    printCodes(root->left, code + "0", bits);
    printCodes(root->right, code + "1", bits);
}

int main() {
    char letters[] = {'a','c','d','e','o','m','s','t','u'};
    int freq[] = {20,11,2,10,15,8,10,22,2};

    priority_queue<Node*, vector<Node*>, Compare> pq;

    for (int i = 0; i < 9; i++)
        pq.push(new Node(letters[i], freq[i], i));

    int order = 9;

    while (pq.size() > 1) {
        Node* left = pq.top();
        pq.pop();

        Node* right = pq.top();
        pq.pop();

        Node* parent = new Node(
            '#', left->freq + right->freq, order++
        );

        parent->left = left;
        parent->right = right;
        pq.push(parent);
    }

    int bits = 0;

    cout << "Huffman Codes:" << endl;
    printCodes(pq.top(), "", bits);

    cout << "Total memory: " << bits * 100 << " bits" << endl;
    cout << "Memory in bytes: " << bits * 100 / 8 << " bytes" << endl;

    return 0;
}
