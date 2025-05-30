#include <bits/stdc++.h>

using namespace std;

string toLower(const string &s) {
    string r = s;
    for (char &c : r) {
        c = tolower(c);
    }
    return r;
}

vector<string> splitWords(const string &line) {
    istringstream iss(line);
    vector<string> w;
    string x;
    while (iss >> x) {
        w.push_back(toLower(x));
    }
    return w;
}

unordered_map<string,int> buildBadChar(const vector<string> &P) {
    unordered_map<string,int> last;
    for (int i = 0; i < (int)P.size(); i++) {
        last[P[i]] = i;
    }
    return last;
}

vector<int> buildGoodSuffix(const vector<string> &P) {
    int m = P.size();
    vector<int> goodSuffix(m+1, m), f(m+1), g(m+1);
    int i = m, j = m+1;
    f[i] = j;
    while (i > 0) {
        while (j <= m && P[i-1] != (j-1 < m ? P[j-1] : string())) {
            goodSuffix[j] = min(goodSuffix[j], j - i);
            j = f[j];
        }
        i--; j--;
        f[i] = j;
    }
    j = f[0];
    for (int k = 0; k <= m; k++) {
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
    cin.tie(nullptr);

    ifstream in("input.txt");
    ofstream out("output.txt");

    string line;
    if (!getline(in, line)) {
        return 0;
    }

    auto P = splitWords(line);
    int m = P.size();
    if (m == 0) {
        return 0;
    }

    vector<string> T;
    vector<pair<int,int>> pos;
    int lineNo = 0;
    while (getline(in, line)) {
        lineNo++;
        auto w = splitWords(line);
        for (int k = 0; k < (int)w.size(); k++) {
            T.push_back(w[k]);
            pos.emplace_back(lineNo, k+1);
        }
    }
    in.close();
    int n = T.size();
    if (n < m) {
        return 0;
    }

    auto badChar = buildBadChar(P);
    auto goodSuffix = buildGoodSuffix(P);

    vector<pair<int,int>> result;
    int s = 0;
    while (s <= n - m) {
        int j = m - 1;
        while (j >= 0 && P[j] == T[s + j]) {
            j--;
        }
        if (j < 0) {
            result.push_back(pos[s]);
            s += goodSuffix[0];
        }
        else {
            int bcShift = 1;
            auto it = badChar.find(T[s + j]);
            if (it != badChar.end()) {
                bcShift = max(1, j - it->second);
            }
            else {
                bcShift = j + 1;
            }
            s += max(bcShift, goodSuffix[j + 1]);
        }
    }

    for (auto &p : result) {
        out << p.first << "," << p.second << "\n";
    }
    return 0;
}
