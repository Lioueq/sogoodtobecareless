#include <bits/stdc++.h>

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

void to_lower(const char* src, char* dst) {
    for (int i = 0; i < 256 && src[i]; ++i) {
        dst[i] = tolower((unsigned char)src[i]);
    }
    dst[256] = '\0';
}

class AVL_Tree {
    public:
        AVL_Tree() : root(nullptr) {}

        bool Insert(const char* key, uint64_t el) {
            bool existed = false;
            char lkey[257];
            to_lower(key, lkey);
            root = RecursiveInsert(root, lkey, el, existed);
            return !existed;
        }

        bool Remove(const char* key) {
            bool existed = false;
            char lkey[257];
            to_lower(key, lkey);
            root = RecursiveRemove(root, lkey, existed);
            return existed;
        }

        bool Find(const char* key, uint64_t& out) {
            char lkey[257];
            to_lower(key, lkey);
            Node* n = root;
            while (n) {
                int cmp = strcmp(lkey, n->key);
                if (cmp == 0) {
                    out = n->value;
                    return true;
                } 
                else if (cmp < 0) {
                    n = n->left;
                } 
                else {
                    n = n->right;
                }
            }
            return false;
        }

        void InorderPrint() {
            Inorder(root);
        }

        bool SaveToFile(const std::string& filename, std::string& error) {
            try {
                std::ofstream out(filename, std::ios::binary);
                SaveNode(out, root);
                return true;
            } 
            catch (const std::exception& e) {
                error = e.what();
                return false;
            }
        }

        bool LoadFromFile(const std::string& filename, std::string& error) {
            try {
                std::ifstream in(filename, std::ios::binary);
                Node* newRoot = LoadNode(in);
                if (!in.eof() && in.fail()) {
                    error = "File format error";
                    FreeTree(newRoot);
                    return false;
                }
                FreeTree(root);
                root = newRoot;
                return true;
            } 
            catch (const std::exception& e) {
                error = e.what();
                return false;
            }
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

        Node* RecursiveInsert(Node* node, const char* key, uint64_t el, bool& existed) {
            if (!node) {
                return new Node(key, el);
            }
            if (strcmp(key, node->key) == 0) {
                existed = true;
                return node;
            }
            if (strcmp(key, node->key) > 0) {
                node->right = RecursiveInsert(node->right, key, el, existed);
            } 
            else {
                node->left = RecursiveInsert(node->left, key, el, existed);
            }
            updateHeight(node);
            int bf = getBalance(node);
            if (bf > 1) {
                if (strcmp(key, node->left->key) < 0) {
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

        Node* minValueNode(Node* node) {
            Node* current = node;
            while (current && current->left)
                current = current->left;
            return current;
        }

        Node* RecursiveRemove(Node* node, const char* key, bool& existed) {
            if (!node) {
                return nullptr;
            }
            if (strcmp(key, node->key) < 0) {
                node->left = RecursiveRemove(node->left, key, existed);
            } 
            else if (strcmp(key, node->key) > 0) {
                node->right = RecursiveRemove(node->right, key, existed);
            } 
            else {
                existed = true;
                if (!node->left || !node->right) {
                    Node* temp = node->left ? node->left : node->right;
                    delete node;
                    return temp;
                } 
                else {
                    Node* temp = minValueNode(node->right);
                    strncpy(node->key, temp->key, 256);
                    node->key[256] = '\0';
                    node->value = temp->value;
                    node->right = RecursiveRemove(node->right, temp->key, existed);
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
            else if (bf < -1) {
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

        void SaveNode(std::ofstream& out, Node* node) {
            if (!node) {
                uint8_t flag = 0;
                out.write((char*)&flag, sizeof(flag));
                return;
            }
            uint8_t flag = 1;
            out.write((char*)&flag, sizeof(flag));
            uint16_t len = strlen(node->key);
            out.write((char*)&len, sizeof(len));
            out.write(node->key, len);
            out.write((char*)&node->value, sizeof(node->value));
            SaveNode(out, node->left);
            SaveNode(out, node->right);
        }

        Node* LoadNode(std::ifstream& in) {
            uint8_t flag;
            in.read((char*)&flag, sizeof(flag));
            if (!in || flag == 0) {
                return nullptr;
            }    
            uint16_t len;
            in.read((char*)&len, sizeof(len));
            char key[257];
            in.read(key, len);
            key[len] = '\0';
            uint64_t value;
            in.read((char*)&value, sizeof(value));
            Node* node = new Node(key, value);
            node->left = LoadNode(in);
            node->right = LoadNode(in);
            updateHeight(node);
            return node;
        }

        void FreeTree(Node* node) {
            if (!node) {
                return;
            }    
            FreeTree(node->left);
            FreeTree(node->right);
            delete node;
        }
};

int main() {
    AVL_Tree tree;
    std::ifstream in("test.txt");
    std::string line, key;
    uint64_t value;
    while (std::getline(in, line)) {
        try {
            std::istringstream iss(line);
            if (line[0] == '+') {
                iss >> key >> key >> value;
                if (tree.Insert(key.c_str(), value)) {
                    std::cout << "OK" << std::endl;
                } 
                else {
                    std::cout << "Exist" << std::endl;
                }
            } 
            else if (line[0] == '-') {
                iss >> key >> key;
                if (tree.Remove(key.c_str())) {
                    std::cout << "OK" << std::endl;
                } 
                else {
                    std::cout << "NoSuchWord" << std::endl;
                }
            } 
            else if (line[0] == '!') {
                std::string cmd, path;
                iss >> cmd >> cmd >> path;
                std::string error;
                if (cmd == "Save") {
                    if (tree.SaveToFile(path, error)) {
                        std::cout << "OK" << std::endl;
                    } 
                    else {
                        std::cout << "ERROR: " << error << std::endl;
                    }
                } 
                else if (cmd == "Load") {
                    if (tree.LoadFromFile(path, error)) {
                        std::cout << "OK" << std::endl;
                    } 
                    else {
                        std::cout << "ERROR: " << error << std::endl;
                    }
                }
            } 
            else {
                iss >> key;
                uint64_t out;
                if (tree.Find(key.c_str(), out)) {
                    std::cout << "OK: " << out << std::endl;
                } 
                else {
                    std::cout << "NoSuchWord" << std::endl;
                }
            }
        } 
        catch (const std::exception& e) {
            std::cout << "ERROR: " << e.what() << std::endl;
        }
    }
    return 0;
}
