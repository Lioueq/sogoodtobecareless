#include <bits/stdc++.h>

using namespace std;

vector<pair<char, int>> countSort1(string s) {
    vector<int> c(27, 0);
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '$') {
            c[0]++;
            continue;
        }
        c[s[i] - 'a' + 1]++;
    }
    for (int i = 1; i < c.size(); ++i) {
        c[i] += c[i - 1];
    }
    vector<pair<char, int>> a(s.size());
    for (int i = s.size() - 1; i >= 0; --i) {
        pair<char, int> t = {s[i], i};
        int idx = s[i] == '$' ? 0 : (s[i] - 'a' + 1);
        a[--c[idx]] = t;
    }
    return a;
}

vector<pair<string, int>> countSort2(vector<pair<string, int>> sa, vector<int> eq) {
    vector<int> c(sa.size(), 0);
    for (auto i: sa) {
        c[eq[i.second]]++;
    }
    for (int i = 1; i < c.size(); ++i) {
        c[i] += c[i - 1];
    }
    vector<pair<string, int>> new_sa(sa.size());
    for (int i = sa.size() - 1; i >= 0; --i) {
        new_sa[--c[eq[sa[i].second]]] = sa[i];
    }
    return new_sa;
}

vector<int> buildSA(string s) {
    int n = s.size();
    int start_n = n;
    int c = 1;
    while (pow(2, c) < n) {
        c++;
    }
    for (int i = 0; i < (pow(2, c) - n); ++i) {
        s += "$";
    };
    n = s.size();
    vector<pair<char, int>> a = countSort1(s);
    vector<int> eq(a.size());
    int eq_c = 0;
    eq[a[0].second] = eq_c;
    for (int i = 1; i < a.size(); ++i) {
        if (a[i].first == a[i - 1].first) {
            eq[a[i].second] = eq_c;
        }
        else{
            eq[a[i].second] = ++eq_c;
        }
    }
    int k = 1;
    vector<pair<string, int>> sa;
    for (auto i: a) {
        string ts = "";
        int tidx = (i.second - 1 + n) % n;
        int startidx = tidx;
        for (int c = 0; c < k * 2; ++c) {
            ts += s[tidx]; 
            tidx = (tidx + 1) % n;
        }
        pair<string, int> tp = {ts, startidx};
        sa.push_back(tp);
    }
    sa = countSort2(sa, eq);
    while (k * 2 < n) {
        k *= 2;
        eq_c = 0;
        for (int i = 1; i < sa.size(); ++i) {
            if (sa[i].first == sa[i - 1].first) {
                eq[sa[i].second] = eq_c;
            }
            else {
                eq[sa[i].second] = ++eq_c;
            }
        }
        vector<pair<string, int>> tsa;
        for (auto i: sa) {
            string ts = "";
            int tidx = (i.second - k + n) % n;
            int startidx = tidx;
            for (int c = 0; c < k * 2; ++c) {
                ts += s[tidx]; 
                tidx = (tidx + 1) % n;
            }
            pair<string, int> tp = {ts, startidx};
            tsa.push_back(tp);
        }
        sa = countSort2(tsa, eq);
    }
    vector<int> ans;

    for (int i = n - start_n; i < n; ++i) {
        ans.push_back(sa[i].second);
    }
    return ans;
}

int main() {
    string s;
    cin >> s;
    vector<int> ans = buildSA(s);
    for (int i : ans) {
        cout << i << ' ';
    }
    return 0;
}