#include <bits/stdc++.h>

int main() {
    std::ifstream input("test.txt");
    if (!input.is_open()) {
        std::cerr << "Ошибка открытия файла!" << std::endl;
        return 1;
    }
    auto start = std::chrono::high_resolution_clock::now();
    std::map<std::string, uint64_t> dictionary;
    std::string line;

    while (std::getline(input, line)) {
        std::istringstream iss(line);
        std::string cmd_or_key, key;
        uint64_t value;

        iss >> cmd_or_key;

        if (cmd_or_key == "+") {
            iss >> key >> value;
            dictionary[key] = value;
        } else if (cmd_or_key == "-") {
            iss >> key;
            dictionary.erase(key);
        } else {
            key = cmd_or_key;
            auto it = dictionary.find(key);
            if (it != dictionary.end()) {
                continue;
            } else {
                continue;
            }
        }
    }
    auto end = std::chrono::high_resolution_clock::now();       
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Elapsed time: " << elapsed.count() << " seconds\n";
    return 0;
}