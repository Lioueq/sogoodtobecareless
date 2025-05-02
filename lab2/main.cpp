#include <bits/stdc++.h>

void to_lower(const char* src, char* dst) {
    int i = 0;
    for (; src[i] && i < 256; ++i) {
        dst[i] = tolower((unsigned char)src[i]);
    }
    dst[i] = '\0';
}

struct Node {
    char key[257];
    uint64_t value;
    int height;
    Node* left;
    Node* right;
    Node(const char* key, uint64_t value)
        : value(value), height(1), left(nullptr), right(nullptr) {
        strncpy(this->key, key, 256);
        this->key[256] = '\0';
    }
};

class AVL_Tree {
public:
    AVL_Tree() : root(nullptr) {}

    void Insert(const char* key, uint64_t el) {
        if (Find(key) != -1) {
            std::cout << "Exist\n";
            return;
        }
        char lower_key[257];
        to_lower(key, lower_key);
        root = RecursiveInsert(root, lower_key, el);
        std::cout << "OK\n";
    }

    void Remove(const char* key) {
        if (Find(key) == -1) {
            std::cout << "NoSuchWord\n";
            return;
        }
        char lower_key[257];
        to_lower(key, lower_key);
        root = RecursiveRemove(root, lower_key);
        std::cout << "OK\n";
    }

    void InorderPrint() {
        Inorder(root);
    }

    uint64_t Find(const char* key, int mode=0) {
        char lower_key[257];
        to_lower(key, lower_key);
        Node* res = RecursiveFind(root, lower_key);
        if (mode != 0) {
            if (res != nullptr) {
                std::cout << "OK: " << res->value << '\n';
            }
            else {
                std::cout << "NoSuchWord\n";
            }
            return 0;
        }
        return res ? res->value : -1;
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

    Node* RecursiveInsert(Node* node, const char* key, uint64_t el) {
        if (!node) {
            return new Node(key, el);
        }
        int cmp = strcmp(key, node->key);
        if (cmp > 0) {
            node->right = RecursiveInsert(node->right, key, el);
        } 
        else {
            node->left = RecursiveInsert(node->left, key, el);
        }
        updateHeight(node);
        int bf = getBalance(node);
        if (bf > 1) {
            if (strcmp(key, node->left->key) <= 0) {
                return rotateRight(node);
            } 
            else {
                return bigRotateRight(node);
            }
        }
        else if (bf < -1) {
            if (strcmp(key, node->right->key) > 0) {
                return rotateLeft(node);
            } 
            else {
                return bigRotateLeft(node);
            }
        }
        return node;
    }

    Node* RecursiveFind(Node* node, const char* key) {
        if (!node) {
            return nullptr;
        }
        int cmp = strcmp(key, node->key);
        if (cmp == 0) {
            return node;
        }
        if (cmp < 0) {
            return RecursiveFind(node->left, key);
        }
        return RecursiveFind(node->right, key);
    }

    Node* RecursiveRemove(Node* node, const char* key) {
        if (!node) {
            return nullptr;
        }
        int cmp = strcmp(key, node->key);
        if (cmp < 0) {
            node->left = RecursiveRemove(node->left, key);
        } 
        else if (cmp > 0) {
            node->right = RecursiveRemove(node->right, key);
        } 
        else {
            if (!node->left || !node->right) {
                Node* temp = node->left ? node->left : node->right;
                delete node;
                return temp;
            } 
            else {
                Node* minLarger = node->right;
                while (minLarger->left) minLarger = minLarger->left;
                strncpy(node->key, minLarger->key, 256);
                node->key[256] = '\0';
                node->value = minLarger->value;
                node->right = RecursiveRemove(node->right, minLarger->key);
            }
        }
        updateHeight(node);
        int bf = getBalance(node);
        if (bf > 1) {
            if (getBalance(node->left) >= 0) {
                return rotateRight(node);
            }
            else {
                return bigRotateRight(node);
            }
        }
        if (bf < -1) {
            if (getBalance(node->right) <= 0) {
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
    std::ifstream in("input.txt");
    char line[1024], key[257];
    char op;
    uint64_t value;
    while (in.getline(line, sizeof(line))) {
        std::istringstream iss(line);
        if (line[0] == '+' || line[0] == '-' || line[0] == '!') {
            iss >> op;
            if (op == '+') {
                iss >> key >> value;
                tree.Insert(key, value);
            }
            else if (op == '-') {
                iss >> key;
                tree.Remove(key);
            }
        }
        else {
            iss >> key;
            tree.Find(key, 1);
        }
    }
    return 0;
}
