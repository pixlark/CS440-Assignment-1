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

int main() {
    Deque_int deque;
    Deque_int_ctor(&deque, 0);

    debug_dump(&deque);
    deque.push_back(&deque, 1);
    debug_dump(&deque);
    deque.push_back(&deque, 2);
    debug_dump(&deque);
    deque.push_back(&deque, 3);
    debug_dump(&deque);
    deque.push_front(&deque, -1);
    debug_dump(&deque);
    deque.push_front(&deque, -2);
    debug_dump(&deque);
    
    return 0;
}
