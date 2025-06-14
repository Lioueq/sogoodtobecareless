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

unordered_map<int,int> buildBadCharInt(const vector<int>& pat) {
    unordered_map<int,int> last;
    for (int i = 0; i < pat.size(); ++i) {
        last[pat[i]] = i;
    }
    return last;
}

vector<int> buildGoodSuffixInt(const vector<int> &pat) {
    int m = pat.size();
    vector<int> goodSuffix(m + 1, m), f(m + 1);
    int i = m, j = m + 1;
    f[i] = j;
    while (i > 0) {
        while (j <= m && pat[i-1] != (j - 1 < m ? pat[j - 1] : -1)) {
            if (goodSuffix[j] == m) goodSuffix[j] = j - i;
            j = f[j];
        }
        i--; 
        j--;
        f[i] = j;
    }
    j = f[0];
    for (int k = 0; k <= m; ++k) {
        if (goodSuffix[k] == m) {
            goodSuffix[k] = j;
        }
        if (k == j) {
            j = f[j];
        }
    }
    return goodSuffix;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    ifstream in("warandpeace.txt");
    string line;
    getline(in, line);
    vector<string> pat = splitWords(line);
    int m = pat.size();
    if (m == 0) {
        return 0;
    }

    unordered_map<string, int> wtid;
    int nextId = 0;
    auto getId = [&](const string &w) {
        auto it = wtid.find(w);
        if (it != wtid.end()) return it->second;
        return wtid.emplace(w, nextId++).first->second;
    };

    vector<int> patId(m);
    for (int i = 0; i < m; ++i) {
        patId[i] = getId(pat[i]);
    }

    vector<int> textId;
    textId.reserve(10000000);
    vector<pair<int,int>> pos;
    pos.reserve(10000000);
    int lineN = 0;
    while (getline(in, line)) {
        lineN++;
        vector<string> w = splitWords(line);
        for (int k = 0; k < w.size(); ++k) {
            textId.push_back(getId(w[k]));
            pos.emplace_back(lineN, k + 1);
        }
    }
    int n = textId.size();
    if (n < m) {
        return 0;
    }

    auto badChar = buildBadCharInt(patId);
    auto goodSuffix = buildGoodSuffixInt(patId);
    auto start = std::chrono::high_resolution_clock::now();
    vector<pair<int,int>> result;
    result.reserve(10000000);
    int s = 0;
    while (s <= n - m) {
        int j = m - 1;
        while (j >= 0 && patId[j] == textId[s + j]) {
            j--;
        }
        if (j < 0) {
            result.push_back(pos[s]);
            s += goodSuffix[0];
        }
        else {
            int bcShift = 1;
            auto it = badChar.find(textId[s + j]);
            if (it != badChar.end()) {
                bcShift = max(1, j - it->second);
            }
            else {
                bcShift = j + 1;
            }
            s += max(bcShift, goodSuffix[j + 1]);
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
