#include <stdio.h>
#include <stdlib.h>

#include "Deque.hpp"

Deque_DEFINE(int)

void debug_dump(Deque_int* deque) {
    printf("front: %u; back: %u; size: %zu; capacity: %u\n", deque->_front, deque->_back, deque->size(deque), deque->_capacity);
    printf("[ ");
    for (size_t i = 0; i < deque->_capacity; i++) {
        printf("%d ", deque->_arr[i]);
    }
    printf("]\n");
}

bool less_than(const int& a, const int& b) {
    return a < b;
}

int main() {
    Deque_int deque;
    Deque_int_ctor(&deque, less_than);

    deque.push_back(&deque, 5);
    deque.push_back(&deque, 3);
    deque.push_back(&deque, 8);
    deque.push_front(&deque, -2);
    deque.push_front(&deque, 10);

    debug_dump(&deque);

    deque.sort(&deque, deque.begin(&deque), deque.end(&deque));

    debug_dump(&deque);
    
    return 0;
}
