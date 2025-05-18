#include <bits/stdc++.h>

const int NUM_LINES = 10'000'000;
const int MAX_KEY_LEN = 256;
const char COMMANDS[] = {'+', '-', '\0'};  // "" в Python — это поиск

char random_char(std::mt19937 &rng) {
    static const char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
    std::uniform_int_distribution<> dist(0, 25);
    return alphabet[dist(rng)];
}

std::string random_key(std::mt19937 &rng, int length) {
    std::string key;
    key.reserve(length);
    for (int i = 0; i < length; ++i) {
        key += random_char(rng);
    }
    return key;
}

int main() {
    std::ofstream fout("test.txt");
    if (!fout) {
        std::cerr << "Failed to open file.\n";
        return 1;
    }

    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<> len_dist(1, MAX_KEY_LEN);
    std::uniform_int_distribution<> cmd_dist(0, 2); // 0: +, 1: -, 2: ""

    std::uniform_int_distribution<uint64_t> val_dist(0, std::numeric_limits<uint64_t>::max());

    for (int i = 0; i < NUM_LINES; ++i) {
        int key_len = len_dist(rng);
        char cmd = COMMANDS[cmd_dist(rng)];
        std::string key = random_key(rng, key_len);

        if (cmd == '+') {
            uint64_t value = val_dist(rng);
            fout << "+ " << key << " " << value << "\n";
        } else if (cmd == '-') {
            fout << "- " << key << "\n";
        } else {
            fout << key << "\n";
        }
    }

    fout.close();
    return 0;
}
