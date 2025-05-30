#include <bits/stdc++.h>

using namespace std;

string toLower(string &s) {
    for (char &c : s) {
        c = tolower(c);
    }
    return s;
}

vector<string> splitWords(string &line) {
    istringstream iss(line);
    vector<string> w;
    string x;
    while (iss >> x) {
        w.push_back(toLower(x));
    }
    return w;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    ifstream in("warandpeace.txt");
    string line;
    getline(in, line);
    vector<string> P = splitWords(line);
    int m = P.size();
    if (m == 0) {
        return 0;
    }
    vector<string> T;
    vector<pair<int,int>> pos;
    int lineN = 0;
    while (getline(in, line)) {
        lineN++;
        vector<string> w = splitWords(line);
        for (int k = 0; k < w.size(); ++k) {
            T.push_back(w[k]);
            pos.emplace_back(lineN, k + 1);
        }
    }
    int n = T.size();
    if (n < m) {
        return 0;
    }
    auto start = std::chrono::high_resolution_clock::now();
    vector<pair<int,int>> result;
    for (int i = 0; i <= n - m; ++i) {
        bool match = true;
        for (int j = 0; j < m; ++j) {
            if (P[j] != T[i + j]) {
                match = false;
                break;
            }
        }
        if (match) {
            result.push_back(pos[i]);
        }
    }

    ofstream out("output.txt");
    for (auto &p : result) {
        out << p.first << "," << p.second << "\n";
    }
    auto end = std::chrono::high_resolution_clock::now();       
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Elapsed time: " << elapsed.count() << " seconds\n";
    return 0;
}
