#ifndef DEQUE_HPP
#define DEQUE_HPP

#include <stdint.h>

#define Deque_DEFINE(T) \
    struct Deque_##T; \
    typedef bool (* T##_compare)(const T&, const T&); \
    struct Deque_##T { \
        T* _arr; \
        uint32_t _capacity; \
        uint32_t _front; \
        uint32_t _back; \
        const char* type_name; \
        T##_compare comparator; \
        size_t(*size)(Deque_##T*); \
        bool(*empty)(Deque_##T*); \
        void(*grow)(Deque_##T*); \
        void(*push_back)(Deque_##T*, T); \
        void(*push_front)(Deque_##T*, T); \
        T&(*front)(Deque_##T*); \
        T&(*back)(Deque_##T*); \
        void(*pop_back)(Deque_##T*); \
        void(*pop_front)(Deque_##T*); \
    }; \
    size_t Deque_##T##_size(Deque_##T* self) { \
        if (self->_back >= self->_front) { \
            /* If queue is nicely ordered */ \
            return self->_back - self->_front; \
        } \
        /* Otherwise, our queue crosses the boundary */ \
        /* and we have to perform a bit of magic */ \
        /* TODO(Brooke): This is ugly, do better. */ \
        uint32_t end_size = (uint32_t) ((2UL << 32UL) - ((uint64_t) self->_front)); \
        return self->_back + end_size; \
    } \
    bool Deque_##T##_empty(Deque_##T* self) { \
        return self->size(self) == 0; \
    } \
    void Deque_##T##_grow(Deque_##T* self) { \
        /* Determine new capacity */ \
        size_t new_capacity; \
        if (self->_capacity == 0) { \
            new_capacity = 4; \
        } else { \
            new_capacity = self->_capacity * 2; \
        } \
        /* Allocate/reallocate array */ \
        if (self->_capacity == 0) { \
            self->_arr = (T*) malloc(sizeof(T) * new_capacity); \
        } else { \
            T* new_arr = (T*) malloc(sizeof(T) * new_capacity); \
            for (size_t i = 0; i < self->size(self); i++) { \
                new_arr[(i + self->_front) % new_capacity] = self->_arr[(i + self->_front) % self->_capacity]; \
            } \
            free(self->_arr); \
            self->_arr = new_arr; \
        } \
        /* Set capacity */ \
        self->_capacity = new_capacity; \
    } \
    void Deque_##T##_push_back(Deque_##T* self, T x) { \
        if (self->size(self) >= self->_capacity) { \
            self->grow(self); \
        } \
        self->_arr[self->_back % self->_capacity] = x; \
        self->_back += 1; \
    } \
    void Deque_##T##_push_front(Deque_##T* self, T x) { \
        if (self->size(self) >= self->_capacity) { \
            self->grow(self); \
        } \
        self->_front -= 1; \
        self->_arr[self->_front % self->_capacity] = x; \
    } \
    T& Deque_##T##_front(Deque_##T* self) { \
        /* Assumes queue is not empty */ \
        return self->_arr[self->_front % self->_capacity]; \
    } \
    T& Deque_##T##_back(Deque_##T* self) { \
        /* Assumes queue is not empty */ \
        return self->_arr[self->_back % self->_capacity]; \
    } \
    void Deque_##T##_pop_back(Deque_##T* self) { \
        /* Assumes queue is not empty */ \
        self->_back -= 1; \
    } \
    void Deque_##T##_pop_front(Deque_##T* self) { \
        /* Assumes queue is not empty */ \
        self->_front += 1; \
    } \
    void Deque_##T##_ctor( \
        Deque_##T* deque, \
        T##_compare comparator \
    ) { \
        deque->_arr = 0; \
        deque->_capacity = 0; \
        deque->_front = 0; \
        deque->_back = 0; \
        deque->type_name = #T; \
        deque->comparator = comparator; \
        deque->size = Deque_##T##_size; \
        deque->empty = Deque_##T##_empty; \
        deque->grow = Deque_##T##_grow; \
        deque->push_back = Deque_##T##_push_back; \
        deque->push_front = Deque_##T##_push_front; \
        deque->front = Deque_##T##_front; \
        deque->back = Deque_##T##_back; \
        deque->pop_back = Deque_##T##_pop_back; \
        deque->pop_front = Deque_##T##_pop_front; \
    }

#endif
