// Нужно реализовать ДЭК на одно-связном списке push_front/push_back pop_front/pop_back
// + Удалить все четные значения
#include <iostream>
struct Deque {
    int* data;
    int size;
    int capacity;
};

void initDeque(Deque *d) {
    d->capacity = 10;
    d->size = 0;
    d->data = new int[d->capacity];
}

void push_back(Deque *d, int el) {
    d->data[d->size] = el;
    d->size++;
}

void push_front(Deque *d, int el) {
    for (int i = 1; i < d->size; ++i) {
        d->data[i] = d->data[i - 1];
    }
    d->data[0] = el;
    d->size++;
}

int pop_front(Deque *d) {
    int el = d->data[0];
    for (int i = 1; i < d->size; ++i) {
        d->data[i - 1] = d->data[i];
    }
    d->size--;
    return el;
}

int pop_back(Deque *d) {
    int el = d->data[d->size];
    d->size--;
    return el;
}

void delete_before(Deque *d, int c) {
    int arr[c];
    for (int i =0; i < c; ++i) {
        arr[i] = pop_back(d);
    }
    for (int i = 0; i < c - 1; ++i) {
        push_back(d, arr[i]);
    }
}

void del_even(Deque *d) {
    for (int i = 0; i < d->size; ++i) {
        if (d->data[i] % 2 == 0) {
            delete_before(d, d->size - 1 - i);
        }
    }
}

void print(Deque *d) {
    for (int i = 0; i < d->size; ++i) {
        std::cout << d->data[i] << ' ';
    }
}

int main() {
    Deque d;
    initDeque(&d);
    push_back(&d, 1);
    push_back(&d, 2);
    push_back(&d, 3);
    push_back(&d, 4);
    del_even(&d);
    print(&d);
}
