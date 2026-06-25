#include <iostream>
#include <string>
#include <vector>
#include "RedBlackTree.h"
using namespace std;

void preorder(const RedBlackTree::Node* node, vector<int>& result) {
    if (node->isNil) return;
    result.push_back(node->key);
    preorder(node->left, result);
    preorder(node->right, result);
}

void inorder(const RedBlackTree::Node* node, vector<int>& result) {
    if (node->isNil) return;
    inorder(node->left, result);
    result.push_back(node->key);
    inorder(node->right, result);
}

void postorder(const RedBlackTree::Node* node, vector<int>& result) {
    if (node->isNil) return;
    postorder(node->left, result);
    postorder(node->right, result);
    result.push_back(node->key);
}

void printTraversal(const string& label, const RedBlackTree::Node* root) {
    vector<int> res;
    if (label == "[Preorder]  : ") preorder(root, res);
    else if (label == "[Inorder]   : ") inorder(root, res);
    else postorder(root, res);

    cout << label;
    for (int i = 0; i < (int)res.size(); i++) {
        if (i) cout << " ";
        cout << res[i];
    }
    cout << endl;
}

int main() {
    int N;
    cin >> N;

    RedBlackTree rbt;
    for (int i = 0; i < N; i++) {
        int x; cin >> x;
        if (!rbt.contains(x)) rbt.insert(x);
    }

    int Q;
    cin >> Q;

    vector<string> queries(Q);
    for (int i = 0; i < Q; i++) cin >> queries[i];

    for (int i = 0; i < Q; i++) {
        if (rbt.empty()) {
            cout << "Tree kosong. Tidak ada yang bisa ditampilkan." << endl;
            continue;
        }

        const string& query = queries[i];
        if (query == "PREORDER") {
            printTraversal("[Preorder]  : ", rbt.root());
        } else if (query == "INORDER") {
            printTraversal("[Inorder]   : ", rbt.root());
        } else if (query == "POSTORDER") {
            printTraversal("[Postorder] : ", rbt.root());
        } else if (query == "ALL") {
            printTraversal("[Preorder]  : ", rbt.root());
            printTraversal("[Inorder]   : ", rbt.root());
            printTraversal("[Postorder] : ", rbt.root());
        }
    }

    return 0;
}