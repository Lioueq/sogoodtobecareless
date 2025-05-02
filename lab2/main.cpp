#include <bits/stdc++.h>

struct Node {
    std::string key;
    uint64_t value;
    int height;
    Node* left;
    Node* right;
    Node(std::string key, uint64_t value)
        : key(key), value(value), height(1), left(nullptr), right(nullptr) {}
};

class AVL_Tree {
    public:
        AVL_Tree() : root(nullptr) {}

        void Insert(std::string key, uint64_t el) {
            root = RecursiveInsert(root, key, el);
        }

        void Remove(std::string key) {
            if (root->key == key) {}
        }

        void InorderPrint() {
            Inorder(root);
        }

        int Find(std::string key) {
            
        }

    private:
        Node* root;

        int getHeight(Node* n) {
            return n ? n->height : 0;
        }

        void updateHeight(Node* n) {
            n->height = 1 + std::max(getHeight(n->left), getHeight(n->right));
        }

        int getBalance(Node* n) {
            return n ? getHeight(n->left) - getHeight(n->right) : 0;
        }

        Node* rotateLeft(Node* x) {
            Node* y = x->right;
            x->right = y->left;
            y->left = x;
            updateHeight(x);
            updateHeight(y);
            return y;
        }

        Node* rotateRight(Node* y) {
            Node* x = y->left;
            y->left = x->right;
            x->right = y;
            updateHeight(y);
            updateHeight(x);
            return x;
        }

        Node* bigRotateLeft(Node* n) {
            n->right = rotateRight(n->right);
            return rotateLeft(n);
        }

        Node* bigRotateRight(Node* n) {
            n->left = rotateLeft(n->left);
            return rotateRight(n);
        }

        Node* RecursiveInsert(Node* node, std::string key, uint64_t el) {
            if (!node) {
                return new Node(key, el);
            }
            if (key > node->key) {
                node->right = RecursiveInsert(node->right, key, el);
            }
            else {
                node->left = RecursiveInsert(node->left, key, el);
            }

            updateHeight(node);
            int bf = getBalance(node);

            if (bf > 1) {
                if (key <= node->left->key) {
                    return rotateRight(node);
                } 
                else {
                    return bigRotateRight(node);
                }
            }

            else if (bf < -1) {
                if (key > node->right->key) {
                    return rotateLeft(node);
                } 
                else {
                    return bigRotateLeft(node);
                }
            }

            return node;
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
    AVL_Tree tree;
    std::ifstream in("test.txt");
    std::string line, key;
    uint64_t value;
    while (std::getline(in, line)) {
        std::istringstream iss(line);
        if (line[0] == '+') {
            iss >> key >> value;
            tree.Insert(key, value);
        }
        else if (line[0] == '-') {
            iss >> key;
            tree.Remove(key);
        }
        else {
            iss >> key;
        }
    }
    return 0;
}
