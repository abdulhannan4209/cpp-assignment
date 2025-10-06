#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

struct HuffNode {
    char ch;
    int freq;
    HuffNode* left;
    HuffNode* right;

    HuffNode(char c, int f) {
        ch = c;
        freq = f;
        left = right = nullptr;
    }
};

struct CompareFreq {
    bool operator()(HuffNode* a, HuffNode* b) {
        return a->freq > b->freq;
    }
};

HuffNode* createHuffmanTree(const string& symbols, const vector<int>& freq) {
    priority_queue<HuffNode*, vector<HuffNode*>, CompareFreq> pq;

    for (int i = 0; i < (int)symbols.size(); i++) {
        pq.push(new HuffNode(symbols[i], freq[i]));
    }

    while (pq.size() > 1) {
        HuffNode* left = pq.top(); pq.pop();
        HuffNode* right = pq.top(); pq.pop();

        HuffNode* merged = new HuffNode('\0', left->freq + right->freq);
        merged->left = left;
        merged->right = right;
        pq.push(merged);
    }

    return pq.top(); // Root node
}

void getCodes(HuffNode* root, string code, unordered_map<char, string>& codeMap) {
    if (!root) return;

    if (root->ch != '\0') {
        codeMap[root->ch] = code;
        return;
    }

    getCodes(root->left, code + "0", codeMap);
    getCodes(root->right, code + "1", codeMap);
}

void preorderCodes(HuffNode* node, unordered_map<char, string>& codeMap, vector<string>& output) {
    if (!node) return;

    if (node->ch != '\0') {
        output.push_back(codeMap[node->ch]);
    }

    preorderCodes(node->left, codeMap, output);
    preorderCodes(node->right, codeMap, output);
}

int main() {
    string S = "abcdef";
    vector<int> f = {5, 9, 12, 13, 16, 45};

    HuffNode* root = createHuffmanTree(S, f);

    unordered_map<char, string> codeMap;
    getCodes(root, "", codeMap);

    vector<string> preorder;
    preorderCodes(root, codeMap, preorder);

    for (auto &code : preorder) {
        cout << code << " ";
    }
    cout << endl;

    return 0;
}
