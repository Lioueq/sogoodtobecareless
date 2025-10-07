#include <bits/stdc++.h>

using namespace std;

vector<int> countSort1(string& s) {
    vector<int> c(256, 0);
    for (int i = 0; i < s.size(); ++i) {
        c[s[i]]++;
    }
    for (int i = 1; i < c.size(); ++i) {
        c[i] += c[i - 1];
    }
    vector<int> a(s.size());
    for (int i = s.size() - 1; i >= 0; --i) {
        a[--c[s[i]]] = i;
    }
    return a;
}

vector<int> countSort2(vector<int>& idx, vector<int>& eq, int eq_c) {
    vector<int> c(eq_c + 1, 0);
    for (int i = 0; i < idx.size(); ++i) {
        c[eq[idx[i]]]++;
    }
    for (int i = 1; i <= eq_c; ++i) {
        c[i] += c[i - 1];
    }
    vector<int> a(idx.size());
    for (int i = idx.size() - 1; i >= 0; --i) {
        a[--c[eq[idx[i]]]] = idx[i];
    }
    return a;
}

vector<int> buildSA(string s) {
    s += "$";
    int n = s.size();

    vector<int> a = countSort1(s);
    vector<int> eq(n);
    int eq_c = 0;
    eq[a[0]] = 0;
    for (int i = 1; i < n; ++i) {
        if (s[a[i]] != s[a[i - 1]]) {
            eq_c++;
        }
        eq[a[i]] = eq_c;
    }
    
    for (int k = 1; k < n; k *= 2) {
        vector<int> new_idx(n);
        for (int i = 0; i < n; ++i) {
            new_idx[i] = (a[i] - k + n) % n;
        }
        a = countSort2(new_idx, eq, eq_c);
        
        vector<int> eq_new(n);
        eq_new[a[0]] = 0;
        eq_c = 0;
        for (int i = 1; i < n; ++i) {
            pair<int, int> cur = {eq[a[i]], eq[(a[i] + k) % n]};
            pair<int, int> prev = {eq[a[i-1]], eq[(a[i-1] + k) % n]};
            if (cur != prev) {
                eq_c++;
            }
            eq_new[a[i]] = eq_c;
        }
        eq = eq_new;
        
        if (eq_c == n - 1) {
            break;
        }
    }
    a.erase(a.begin());
    return a;
}

int lowerBound(string &s, vector<int> &sa, string &p) {
    int l = 0, r = sa.size();
    while (l < r) {
        int mid = (l + r) / 2;
        int pos = sa[mid];
        int len = min((int)p.size(), (int)s.size() - pos);
        string suffix = s.substr(pos, len);
        if (suffix < p) {
            l = mid + 1;
        } 
        else {
            r = mid;
        }
    }
    return l;
}

int upperBound(string &s, vector<int> &sa, string &p) {
    int l = 0, r = sa.size();
    while (l < r) {
        int mid = (l + r) / 2;
        int pos = sa[mid];
        int len = min((int)p.size(), (int)s.size() - pos);
        string suffix = s.substr(pos, len);
        
        if (suffix <= p) {
            l = mid + 1;
        } 
        else {
            r = mid;
        }
    }
    return l;
}

vector<int> searchPattern(string &s, vector<int> &sa, string &p) {
    if (p.empty()) {
        return {};
    }
    int l = lowerBound(s, sa, p);
    int r = upperBound(s, sa, p);

    if (l >= sa.size()) {
        return {};
    }

    int pos = sa[l];
    if (pos + p.size() > s.size()) {
        return {};
    }

    string suffix = s.substr(pos, p.size());
    if (suffix != p) {
        return {};
    }

    vector<int> ans;
    for (int i = l; i < r; ++i) {
        ans.push_back(sa[i] + 1);
    }
    sort(ans.begin(), ans.end());
    return ans;
}

int main() {
    string s;
    getline(cin, s);
    while (!s.empty() && (s.back() == '\r' || s.back() == '\n')) {
        s.pop_back();
    }
    vector<int> sa = buildSA(s);
    string p;
    int c = 1;
    while (getline(cin, p)) {
        while (!p.empty() && (p.back() == '\r' || p.back() == '\n')) {
            p.pop_back();
        }
        vector<int> ans = searchPattern(s, sa, p);
        if (!ans.empty()) {
            cout << c << ":";
            for (int i = 0; i < ans.size(); ++i) {
                cout << " " << ans[i];
                if (i != ans.size() - 1) {
                    cout << ",";
                }
            }
            cout << '\n';
        }
        c++;
    }
    return 0;
}