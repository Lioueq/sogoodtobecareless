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

unordered_map<string, int> buildBadChar(vector<string>& P) {
    unordered_map<string,int> last;
    for (int i = 0; i < P.size(); ++i) {
        last[P[i]] = i;
    }
    return last;
}

vector<int> buildGoodSuffix(vector<string> &P) {
    int m = P.size();
    vector<int> goodSuffix(m + 1, m), f(m + 1), g(m + 1);
    int i = m, j = m + 1;
    f[i] = j;
    while (i > 0) {
        while (j <= m && P[i-1] != (j - 1 < m ? P[j - 1] : "")) {
            goodSuffix[j] = min(goodSuffix[j], j - i);
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

    ifstream in("input.txt");
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

    unordered_map<string, int> badChar = buildBadChar(P);
    vector<int> goodSuffix = buildGoodSuffix(P);

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
    ofstream out("output.txt");
    for (auto &p : result) {
        out << p.first << "," << p.second << "\n";
    }
    return 0;
}
