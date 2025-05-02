#include <bits/stdc++.h>


struct Node {
    std::string key;
    uint64_t value;
    Node* left;
    Node* right;
    Node(std::string key, uint64_t value) : key(key), value(value), left(nullptr), right(nullptr) {};
};

class AVL_Tree {
    public:
        AVL_Tree() : root(nullptr) {};

        void Insert(std::string key, uint64_t el) {
            if (root == nullptr) {
                root = new Node(key, el);
            }
            else {
                RecursiveInsert(root, key, el);
            }
        }

        void Remove(std::string key) {
            if (root->key == key) {}
        }

        void InorderPrint() {
            Inorder(root);
        }
    private:
        Node* root;

        void RecursiveInsert(Node* root, std::string key, uint64_t el) {
            if (key > root->key) {
                if (root->right == nullptr) {
                    root->right = new Node(key, el);
                }
                else {
                    RecursiveInsert(root->right, key, el);
                }
            }
            else if (key <= root->key) {
                if (root->left == nullptr) {
                    root->left = new Node(key, el);
                }
                else {
                    RecursiveInsert(root->left, key, el);
                }
            }
        }

        void Inorder(Node* root) {
            if (root->left != nullptr) {
                Inorder(root->left);
            }
            std::cout << root->value << ' ';
            if (root->right != nullptr) {
                Inorder(root->right);
            }
        }
};


int main() {
    AVL_Tree root;
    return 0;
}