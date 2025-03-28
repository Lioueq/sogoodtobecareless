struct anivector {
    ppair* data;
    int size;
    int capacity;
};

void vector_init(anivector* v) {
    v->data = nullptr;
    v->size = 0;
    v->capacity = 0;
}

void vector_reserve(anivector* v, int new_capacity) {
    if (new_capacity <= v->capacity) return;
    
    ppair* new_data = new ppair[new_capacity];
    if (v->data) {
        memcpy(new_data, v->data, v->size * sizeof(ppair));
        delete[] v->data;
    }
    v->data = new_data;
    v->capacity = new_capacity;
}

void vector_push_back(anivector* v, const ppair& item) {
    if (v->size == v->capacity) {
        int new_cap = (v->capacity == 0) ? 4 : v->capacity * 2;
        vector_reserve(v, new_cap);
    }
    v->data[v->size++] = item;
}

void vector_destroy(anivector* v) {
    delete[] v->data;
    v->data = nullptr;
    v->size = v->capacity = 0;
}