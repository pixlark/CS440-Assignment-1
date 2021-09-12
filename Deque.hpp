#ifndef DEQUE_HPP
#define DEQUE_HPP

#define Deque_DEFINE(T) \
    struct Deque_##T; \
    typedef bool (* T##_compare)(const T&, const T&); \
    struct Deque_##T { \
        T* _arr; \
        size_t _size; \
        const char* type_name; \
        T##_compare comparator; \
        size_t(*size)(Deque_##T* self); \
        bool(*empty)(Deque_##T* self); \
    }; \
    size_t Deque_##T##_size(Deque_##T* self) { \
        return self->_size; \
    } \
    bool Deque_##T##_empty(Deque_##T* self) { \
        return self->_size == 0; \
    } \
    void Deque_##T##_ctor( \
        Deque_##T* deque, \
        T##_compare comparator) { \
        deque->_arr = 0; \
        deque->_size = 0; \
        deque->type_name = #T; \
        deque->comparator = comparator; \
        deque->size = Deque_##T##_size; \
        deque->empty = Deque_##T##_empty; \
    }

#endif
