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
    Node(const char* key_, uint64_t value) : value(value), height(1), left(nullptr), right(nullptr) {
        strncpy(this->key, key_, 256);
        this->key[256] = '\0';
    }
};

class AVL_Tree {
public:
    AVL_Tree() : root(nullptr) {}

    ~AVL_Tree() {
        FreeNode(root);
    }

    void Insert(const char* key, uint64_t el) {
        char lower_key[257];
        to_lower(key, lower_key);

        if (FindLower(lower_key) != nullptr) {
            // std::cout << "Exist\n";
            return;
        }

        root = RecursiveInsert(root, lower_key, el);
        // std::cout << "OK\n";
    }

    void Remove(const char* key) {
        char lower_key[257];
        to_lower(key, lower_key);
        if (FindLower(lower_key) == nullptr) {
            // std::cout << "NoSuchWord\n";
            return;
        }
        root = RecursiveRemove(root, lower_key);
        // std::cout << "OK\n";
    }

    void InorderPrint() {
        Inorder(root);
    }

    uint64_t Find(const char* key, int mode = 0) {
        char lower_key[257];
        to_lower(key, lower_key);
        Node* res = FindLower(lower_key);
        if (mode != 0) {
            if (res != nullptr) {
                // std::cout << "OK: " << res->value << '\n';
            }
            else {
                // std::cout << "NoSuchWord\n";
            }

            return 0;
        }
        if (res == nullptr) {
            return (uint64_t)-1;
        }
        else {
            return res->value;
        }
    }

    bool SaveToFile(const char* filename) {
        std::ofstream out(filename, std::ios::binary);
        if (!out) {
            return false;
        }
        try {
            SaveNode(out, root);
        }
        catch (...) {
            return false;
        }
        return true;
    }

    bool LoadFromFile(const char* filename, char* errorMsg, size_t errSize) {
        std::ifstream in(filename, std::ios::binary);
        if (!in) {
            snprintf(errorMsg, errSize, "ERROR: %s", std::strerror(errno));
            return false;
        }
        try {
            Node* newRoot = LoadNode(in);
            if (!in.eof() && in.fail()) {
                strncpy(errorMsg, "ERROR: File read error", errSize);
                FreeNode(newRoot);
                return false;
            }
            char extra;
            if (in.read(&extra, 1)) {
                strncpy(errorMsg, "ERROR: File format mismatch", errSize);
                FreeNode(newRoot);
                return false;
            }
            FreeNode(root);
            root = newRoot;
        }
        catch (const std::exception& e) {
            snprintf(errorMsg, errSize, "ERROR: %s", e.what());
            return false;
        }
        catch (...) {
            strncpy(errorMsg, "ERROR: Unknown error", errSize);
            return false;
        }
        return true;
    }

private:
    Node* root;
    int getHeight(Node* n) {
        if (n == nullptr) {
            return 0;
        }
        else {
            return n->height;
        }
    }

    Node* FindLower(const char* lower_key) {
        return RecursiveFind(root, lower_key);
    }

    void updateHeight(Node* n) {
        if (n != nullptr) {
            int hl = getHeight(n->left);
            int hr = getHeight(n->right);
            n->height = 1 + std::max(hl, hr);
        }
    }

    int getBalance(Node* n) {
        if (n == nullptr) {
            return 0;
        }
        return getHeight(n->left) - getHeight(n->right);
    }

    Node* rotateLeft(Node* x) {
        if (x == nullptr) {
            return nullptr;
        }
        Node* y = x->right;
        x->right = y->left;
        y->left = x;
        updateHeight(x);
        updateHeight(y);
        return y;
    }

    Node* rotateRight(Node* y) {
        if (y == nullptr) {
            return nullptr;
        }
        Node* x = y->left;
        y->left = x->right;
        x->right = y;
        updateHeight(y);
        updateHeight(x);
        return x;
    }

    Node* bigRotateLeft(Node* n) {
        if (n == nullptr) {
            return nullptr;
        }
        n->right = rotateRight(n->right);
        return rotateLeft(n);
    }

    Node* bigRotateRight(Node* n) {
        if (n == nullptr) {
            return nullptr;
        }
        n->left = rotateLeft(n->left);
        return rotateRight(n);
    }

    Node* RecursiveInsert(Node* node, const char* key, uint64_t el) {
        if (node == nullptr) {
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
        if (node == nullptr) {
            return nullptr;
        }
        int cmp = strcmp(key, node->key);
        if (cmp == 0) {
            return node;
        }
        else if (cmp < 0) {
            return RecursiveFind(node->left, key);
        }
        else {
            return RecursiveFind(node->right, key);
        }
    }

    Node* RecursiveRemove(Node* node, const char* key) {
        if (node == nullptr) {
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
            if (node->left == nullptr || node->right == nullptr) {
                Node* temp = (node->left != nullptr) ? node->left : node->right;
                delete node;
                return temp;
            }
            else {
                Node* minLarger = node->right;
                while (minLarger->left != nullptr) {
                    minLarger = minLarger->left;
                }
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
        if (root == nullptr) {
            return;
        }
        Inorder(root->left);
        std::cout << root->value << ' ';
        Inorder(root->right);
    }

    void SaveNode(std::ofstream& out, Node* node) {
        if (node == nullptr) {
            char marker = 0;
            out.write(&marker, 1);
            return;
        }
        char marker = 1;
        out.write(&marker, 1);
        out.write(node->key, 257);
        out.write(reinterpret_cast<const char*>(&node->value), sizeof(node->value));
        SaveNode(out, node->left);
        SaveNode(out, node->right);
    }

    void FreeNode(Node* node) {
        if (node == nullptr) {
            return;
        }
        FreeNode(node->left);
        FreeNode(node->right);
        delete node;
    }

    Node* LoadNode(std::ifstream& in) {
        char marker;
        if (!in.read(&marker, 1)) {
            throw std::runtime_error("File format mismatch");
        }
        if (marker == 0) {
            return nullptr;
        }
        else if (marker != 1) {
            throw std::runtime_error("File format mismatch");
        }
        char key[257];
        uint64_t value;
        if (!in.read(key, 257)) {
            throw std::runtime_error("File format mismatch");
        }
        if (!in.read(reinterpret_cast<char*>(&value), sizeof(value))) {
            throw std::runtime_error("File format mismatch");
        }
        Node* node = new Node(key, value);
        node->left = LoadNode(in);
        node->right = LoadNode(in);
        updateHeight(node);
        return node;
    }
};

int main() {
    AVL_Tree tree;
    std::ifstream in("test.txt");
    auto start = std::chrono::high_resolution_clock::now();
    char line[290];
    char key[257];
    char cmd[10];
    char path[260];
    char op;
    uint64_t value;
    char errorMsg[260];
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
            else if (op == '!') {
                iss >> cmd;
                if (strcmp(cmd, "Save") == 0) {
                    iss >> path;
                    if (path[0] == '\0') {
                        std::cout << "ERROR: No file path provided" << std::endl;
                    }
                    else if (tree.SaveToFile(path)) {
                        std::cout << "OK" << std::endl;
                    }
                    else {
                        std::cout << "ERROR: Failed to save file" << std::endl;
                    }
                }
                else if (strcmp(cmd, "Load") == 0) {
                    iss >> path;
                    if (path[0] == '\0') {
                        std::cout << "ERROR: No file path provided" << std::endl;
                    }
                    else {
                        if (tree.LoadFromFile(path, errorMsg, sizeof(errorMsg))) {
                            std::cout << "OK" << std::endl;
                        }
                        else {
                            std::cout << errorMsg << std::endl;
                        }
                    }
                }
            }
        }
        else {
            iss >> key;
            tree.Find(key, 1);
        }
    }
    auto end = std::chrono::high_resolution_clock::now();       
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Elapsed time: " << elapsed.count() << " seconds\n";
    return 0;
}
