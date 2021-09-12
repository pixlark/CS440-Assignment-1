#ifndef DEQUE_HPP
#define DEQUE_HPP

#define Deque_DEFINE(T) \
    struct Deque_##T; \
    typedef bool (* T##_compare)(const Deque_##T&, \
                                 const Deque_##T&); \
    struct Deque_##T { \
        T* arr; \
        T##_compare comparator; \
    }; \
    void Deque_##T##_ctor( \
        Deque_##T* deque, \
        T##_compare comparator) { \
        deque->arr = 0; \
        deque->comparator = comparator; \
    }

#endif
