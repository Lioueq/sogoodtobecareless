#include <bits/stdc++.h>

using namespace std;
using ll = long long;

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

// char* htb(string s) {
//     char *ans;
//     for (auto i: s) {
//         strcat(ans, f(i));
//     }
//     return ans;
// }

void radix_sort(vector<vector<char>>& a) {
    for (int p = 31; p >= 0; --p) {
        vector <vector<vector<char>>> buckets(16, vector<vector<char>>(0));
        for (int i = 0; i < a.size(); ++i) {
            buckets[f(a[i][p])].push_back(a[i]);
        }
        a.clear();
        for (auto i: buckets) {
            for (auto j: i) {
                a.push_back(j);
            }
        }
    }
}

void radix_sort_bitmask(vector<int>& a) {
    for (int bit = 0; bit < 128; ++bit) {
        int mask = 1 << bit;
        vector<vector<int>> buckets(2, vector<int>(0));
        for (auto num: a) {
            buckets[(num & mask) != 0].push_back(num);
        }
        a.clear();
        for (auto i: buckets) {
            for (auto j: i) {
                a.push_back(j);
            } 
        }
    }
}

int main() {
    vector <vector<char>> a {{'a', '1'}, {'1', '0'}};
    radix_sort(a);
    for (auto i: a) {
        for (auto j: i) {
            cout << j;
        }
        cout << '\n';
    }

    // ios::sync_with_stdio(false);
    // cin.tie(0); cout.tie(0);
    // vector <pair<uint64_t, string>> a;
    // uint64_t key;
    // string value;
    // while (cin >> hex >> key) {
    //     cin >> value;
    //     pair<uint64_t, string> p {key, value};
    //     a.push_back(p);
    // }
    // for (auto i: a) {
    //     cout << i.first << ' ' << i.second << '\n';
    // }
    // radix_sort(a);
    // cout << x;
    // unsigned char a1 = 0b01001;
    // unsigned char a2 = 0b00110;
    // unsigned char a3 = a1 | a2;
    // while (cin >> s) {
    //     a.push_back(s);
    // }
    // vector <int> bn = dtb(14);
    // for (auto i: bn) {
    //     cout << i;
    // }
    return 0;
}
