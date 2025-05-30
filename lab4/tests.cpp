#include <bits/stdc++.h>
using namespace std;

// Параметры генерации теста
static const int VOCAB_SIZE     = 10;
static const int PATTERN_LEN    = 100;
static const int TEXT_LEN       = 1000000;
static const int WORDS_PER_LINE = 20;
static const char* OUTPUT_FILE  = "input.txt";

// Генерирует случайное слово длиной от 3 до 10 символов
string genWord(mt19937 &rng) {
    uniform_int_distribution<int> lenDist(3, 10);
    uniform_int_distribution<char> charDist('a', 'z');
    int len = lenDist(rng);
    string w;
    w.reserve(len);
    for (int i = 0; i < len; ++i) {
        w.push_back(charDist(rng));
    }
    return w;
}

int main() {
    mt19937 rng((uint32_t)chrono::high_resolution_clock::now().time_since_epoch().count());

    // Собираем словарь
    unordered_set<string> vocabSet;
    vector<string> vocab;
    vocab.reserve(VOCAB_SIZE);
    while ((int)vocab.size() < VOCAB_SIZE) {
        string w = genWord(rng);
        if (vocabSet.insert(w).second) {
            vocab.push_back(move(w));
        }
    }

    // Генерируем шаблон
    uniform_int_distribution<int> vid(0, VOCAB_SIZE - 1);
    vector<string> pattern(PATTERN_LEN);
    for (int i = 0; i < PATTERN_LEN; ++i) {
        pattern[i] = vocab[vid(rng)];
    }

    // Генерируем текст
    vector<string> text(TEXT_LEN);
    for (int i = 0; i < TEXT_LEN; ++i) {
        text[i] = vocab[vid(rng)];
    }

    // Записываем в файл input.txt
    ofstream out(OUTPUT_FILE);
    if (!out) {
        cerr << "Error: cannot open '" << OUTPUT_FILE << "' for writing\n";
        return 1;
    }

    // Первая строка: шаблон
    for (int i = 0; i < 1; ++i) {
        out << "foo bar\n";
    }
    // Далее текст: WORDS_PER_LINE слов в строке
    for (int i = 0; i < 1'000'000; ++i) {
        out << "baz" << ' ';
    }
    if (TEXT_LEN % WORDS_PER_LINE != 0) out << '\n';

    out.close();
    return 0;
}
