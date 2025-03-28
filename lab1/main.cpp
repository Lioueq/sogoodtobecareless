#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const ll SIZE = 100000;
const int BUCKETS = 16;

struct ppair {
    char key[33];
    char value[65];
};

struct anivector {
    ppair* data;
    int size;
    int capacity;
};

void anivector_init(anivector* v) {
    v->data = nullptr;
    v->size = 0;
    v->capacity = 0;
}

void reserve(anivector* v, int new_capacity) {
    if (new_capacity <= v->capacity) return;
    
    ppair* new_data = new ppair[new_capacity];
    if (v->data) {
        memcpy(new_data, v->data, v->size * sizeof(ppair));
        delete[] v->data;
    }
    v->data = new_data;
    v->capacity = new_capacity;
}

void push_back(anivector* v, const ppair& item) {
    if (v->size == v->capacity) {
        int new_cap = (v->capacity == 0) ? 16 : v->capacity * 2;
        reserve(v, new_cap);
    }
    v->data[v->size++] = item;
}

void destroy(anivector* v) {
    delete[] v->data;
    v->data = nullptr;
    v->size = 0;
    v->capacity = 0;
}

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

void radix_sort(ppair a[], int n) {
    ppair* tmp = new ppair[n];
    
    for (int p = 31; p >= 0; --p) {
        int count[BUCKETS] = {0};
        
        for (int i = 0; i < n; ++i) {
            int b = f(a[i].key[p]);
            count[b]++;
        }

        int prefix[BUCKETS] = {0};
        prefix[0] = count[0];
        for (int i = 1; i < BUCKETS; ++i) {
            prefix[i] = prefix[i - 1] + count[i];
        }

        for (int i = n - 1; i >= 0; --i) {
            int idx = f(a[i].key[p]);
            tmp[prefix[idx] - 1] = a[i];
            prefix[idx]--;
        }
        memcpy(a, tmp, n * sizeof(ppair));
    }
    delete[] tmp;
}

void generate_random_hex_string(char* str, int len, mt19937& gen) {
    static uniform_int_distribution<> hex_dist(0, 15);
    static const char hex_chars[] = "0123456789abcdef";
    for (int i = 0; i < len; ++i) {
        str[i] = hex_chars[hex_dist(gen)];
    }
    str[len] = '\0';
}

char random_hex_char(mt19937& gen) {
    static uniform_int_distribution<> hex_dist(0, 15);
    int val = hex_dist(gen);
    return (val < 10) ? ('0' + val) : ('a' + val - 10);
}

int main() {
    auto start_time = std::chrono::high_resolution_clock::now();
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    random_device rd;
    mt19937 gen(rd());

    anivector arr;
    anivector_init(&arr);
    char key[33] = {0};
    char value[65] = {0};
    ppair pp;
    while(scanf("%s\t%s", pp.key, pp.value) != EOF) {
        push_back(&arr, pp);
    }
    // while(scanf("%s\t%s", pp.key, pp.value) != EOF) {
    //     vector_push_back(&arr, pp);
    // }

    radix_sort(arr.data, arr.size);

    for(int i = 0; i < arr.size; ++i) {
        printf("%s\t%s\n", arr.data[i].key, arr.data[i].value);
    }

    destroy(&arr);

    return 0;
}
