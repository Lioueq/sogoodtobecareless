#include <bits/stdc++.h>

using namespace std;

vector<int> countSort1(string& s) {
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
    vector<int> a(s.size());
    for (int i = s.size() - 1; i >= 0; --i) {
        int idx = s[i] == '$' ? 0 : (s[i] - 'a' + 1);
        a[--c[idx]] = i;
    }
    return a;
}

vector<int> countSort2(vector<int>& idx, vector<int>& eq, int& eq_c) {
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

vector<int> buildSA(string& s) {
    int n = s.size();
    int start_n = n;
    int c = 1;
    while (pow(2, c) < n) {
        c++;
    }
    for (int i = 0; i < (pow(2, c) - n); ++i) {
        s += "$";
    }
    n = s.size();
    
    vector<int> a = countSort1(s);
    vector<int> eq(a.size());
    int eq_c = 0;
    eq[a[0]] = eq_c;
    for (int i = 1; i < a.size(); ++i) {
        if (s[a[i]] == s[a[i - 1]]) {
            eq[a[i]] = eq_c;
        } 
        else {
            eq[a[i]] = ++eq_c;
        }
    }

    int k = 1;
    vector<int> eq_new(n);
    while (k < n) {
        vector<int> new_idx(n);
        for (int i = 0; i < n; ++i) {
            new_idx[i] = (a[i] + n - k) % n;
        }
        a = countSort2(new_idx, eq, eq_c);
        eq_new[a[0]] = 0;
        eq_c = 0;
        for (int i = 1; i < n; ++i) {
            pair<int, int> cur = {eq[a[i]], eq[(a[i] + k) % n]};
            pair<int, int> prev = {eq[a[i-1]], eq[(a[i-1] + k) % n]};
            if (cur != prev) {
                ++eq_c;
            }
            eq_new[a[i]] = eq_c;
        }
        if (eq_new[0] == eq_new[eq_new.size() - 1]) {
            break;
        }
        eq = eq_new;
        k *= 2;
    }
    vector<int> res;
    for (int i = n - start_n; i < n; ++i) {
        res.push_back(a[i]);
    }
    return res;
}

int lowerBound(string &s, vector<int> &sa, string &p) {
    int l = 0, r = sa.size() - 1;
    while (l < r) {
        int mid = (l + r) / 2;
        string suffix = s.substr(sa[mid], min(p.size(), s.size() - sa[mid]));
        if (suffix >= p)
            r = mid;
        else
            l = mid + 1;
    }
    return l;
}

int upperBound(string &s, vector<int> &sa, string &p) {
    int l = 0, r = sa.size() - 1;
    while (l < r) {
        int mid = (l + r) / 2;
        string suffix = s.substr(sa[mid], min(p.size(), s.size() - sa[mid]));
        if (suffix > p)
            r = mid;
        else
            l = mid + 1;
    }
    return l;
}

vector<int> searchPattern(string &s, vector<int> &sa, string &p) {
    int l = lowerBound(s, sa, p);
    int r = upperBound(s, sa, p);
    vector<int> ans;
    for (int i = l; i < r; ++i) {
        ans.push_back(sa[i] + 1);
    }
    sort(ans.begin(), ans.end());
    return ans;
}

int main() {
    string s;
    cin >> s;
    vector<int> ans = buildSA(s);
    for (auto i : ans) {
        cout << i << ' ';
    }
    cout << '\n';
    string p;
    cin >> p;
    for (int i : searchPattern(s, ans, p)) {
        cout << i << " ";
    }
    return 0;
}