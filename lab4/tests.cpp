#include <bits/stdc++.h>
using namespace std;

vector<string> words = {
    "G", "A", "B", "C", "F", "H", "O", "P", "Q", "R", "S", "T", "Y", "Q", "Z"
};

string generateRandomLine(int numWords, mt19937& gen) {
    string line;
    uniform_int_distribution<int> dist(0, words.size() - 1);
    for (int i = 0; i < numWords; ++i) {
        if (i > 0) line += " ";
        line += words[dist(gen)];
    }
    return line;
}

string generateCats() {
    return "the cat sat on the mat while the dog barked loudly at the moon";
}

int main() {
    mt19937 gen(time(nullptr));

    ofstream in("input.txt");

    // Генерация шаблона
    uniform_int_distribution<int> patternSize(1, 5);
    int m = 15;
    string patternLine = generateRandomLine(m, gen);
    in << patternLine << '\n';

    // Генерация текста
    int nLines = 1'000'000;
    for (int i = 0; i < nLines; ++i) {
        int numWords = 10;
        string line = generateRandomLine(numWords, gen);
        in << line << '\n';
    }
    return 0;
}
