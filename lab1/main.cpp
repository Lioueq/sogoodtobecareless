#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const ll SIZE = 100000;

struct ppair {
    char key[33];
    char value[65];
};

struct bucket {
    ppair pairs[SIZE];
    int count;
};

int f(char c) {
    switch(c) {
        case '0': return 0;
        case '1': return 1;
        case '2': return 2;
        case '3': return 3;
        case '4': return 4;
        case '5': return 5;
        case '6': return 6;
        case '7': return 7;
        case '8': return 8;
        case '9': return 9;
        case 'a': return 10;
        case 'b': return 11;
        case 'c': return 12;
        case 'd': return 13;
        case 'e': return 14;
        case 'f': return 15;
    }
}

void radix_sort(vector <pair<vector<char>, string>>& a) {
    for (int p = 31; p >= 0; --p) {
        vector <vector<pair<vector<char>, string>>> buckets(16, vector<pair<vector<char>, string>> (0));
        for (int i = 0; i < a.size(); ++i) {
            buckets[f(a[i].first[p])].push_back(a[i]);
        }
        a.clear();
        for (auto i: buckets) {
            for (auto j: i) {
                a.push_back(j);
            }
        }
    }
}

void radix_sort_ultra(ppair a[], int c) {
    for (int p = 31; p >= 0; --p) {
        bucket buckets[16] = {};
        
        for (int i = 0; i < c; ++i) {
            int bucket_idx = f(a[i].key[p]);
            buckets[bucket_idx].pairs[buckets[bucket_idx].count++] = a[i];
        }

        int pos = 0;
        for (auto &b : buckets) {
            for (int i = 0; i < b.count; ++i) {
                a[pos++] = b.pairs[i];
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    char key[33] = {0};
    char value[65] = {0};
    ppair* a = new ppair[SIZE];
    int c = 0;
    while(scanf("%s\t%s", key, value) != EOF) {
        ppair pp;
        strncpy(pp.key, key, 33);
        strncpy(pp.value, value, 65);
        a[c] = pp;
        c++;
    }

    radix_sort_ultra(a, c);

    for(int i = 0; i < c; ++i) {
        printf("%s\t%s\n", a[i].key, a[i].value);
    }

    // vector <pair<vector<char>, string>> a;
    // string key, value;
    // while (cin >> key >> value) {
    //     pair <vector<char>, string> p;
    //     vector<char> v_c;
    //     for (char i: key) {
    //         v_c.push_back(i);
    //     }
    //     p.first = v_c;
    //     p.second = value;
    //     a.push_back(p);
    // }
    // radix_sort(a);
    // for (auto i: a) {
    //     for (auto j: i.first) {
    //         cout << j;
    //     }
    //     cout << '\t';
    //     cout << i.second << '\n';
    // }
    return 0;
}
