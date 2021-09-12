#include <stdlib.h>

#include "Deque.hpp"

Deque_DEFINE(int)

int main() {
    Deque_int deque;

    Deque_int_ctor(&deque);
    
    return 0;
}
