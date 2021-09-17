#ifndef DEQUE_HPP
#define DEQUE_HPP

#include <stdint.h>

#define Deque_DEFINE(T) \
    struct Deque_##T; \
    typedef bool (* T##_compare)(const T&, const T&); \
    struct Deque_##T; \
    struct Deque_##T##_Iterator { \
        Deque_##T* _deque; \
        uint32_t _cursor; \
        T&(*deref)(Deque_##T##_Iterator*); \
        void(*inc)(Deque_##T##_Iterator*); \
        void(*dec)(Deque_##T##_Iterator*); \
    }; \
    static const char Deque_##T##_type_name[] = "Deque_" #T; \
    static const size_t Deque_##T##_type_name_size = sizeof(Deque_##T##_type_name); \
    struct Deque_##T { \
        T* _arr; \
        uint32_t _capacity; \
        uint32_t _front; \
        uint32_t _back; \
        char type_name[Deque_##T##_type_name_size]; \
        T##_compare less_than; \
        size_t(*size)(Deque_##T*); \
        bool(*empty)(Deque_##T*); \
        void(*grow)(Deque_##T*); \
        void(*push_back)(Deque_##T*, T); \
        void(*push_front)(Deque_##T*, T); \
        T&(*front)(Deque_##T*); \
        T&(*back)(Deque_##T*); \
        void(*pop_back)(Deque_##T*); \
        void(*pop_front)(Deque_##T*); \
        Deque_##T##_Iterator(*begin)(Deque_##T*); \
        Deque_##T##_Iterator(*end)(Deque_##T*); \
        T&(*at)(Deque_##T*, size_t cursor); \
        void(*clear)(Deque_##T*); \
        void(*dtor)(Deque_##T*); \
        void(*sort)(Deque_##T*, Deque_##T##_Iterator, Deque_##T##_Iterator); \
    }; \
    bool Deque_##T##_Iterator_equal( \
        Deque_##T##_Iterator a, \
        Deque_##T##_Iterator b \
    ) { \
        return a._cursor == b._cursor; \
    } \
    bool Deque_##T##_equal( \
        Deque_##T& a, \
        Deque_##T& b \
    ) { \
        if (a.size(&a) != b.size(&b)) { \
            return false; \
        } \
        size_t size = a.size(&a); \
        for (size_t i = 0; i < size; i++) { \
            T x = a.at(&a, i), y = b.at(&b, i); \
            if (a.less_than(x, y) || a.less_than(y, x)) { \
                return false; \
            } \
        } \
        /* All elements compared equal */ \
        return true; \
    } \
    T& Deque_##T##_Iterator_deref( \
        Deque_##T##_Iterator* it \
    ) { \
        return it->_deque->at(it->_deque, it->_cursor); \
    } \
    void Deque_##T##_Iterator_inc( \
        Deque_##T##_Iterator* it \
    ) { \
        it->_cursor += 1; \
    } \
    void Deque_##T##_Iterator_dec( \
        Deque_##T##_Iterator* it \
    ) { \
        it->_cursor -= 1; \
    } \
    void Deque_##T##_Iterator_ctor( \
        Deque_##T##_Iterator* it, \
        Deque_##T* deque, \
        uint32_t cursor \
    ) { \
        it->_deque = deque; \
        it->_cursor = cursor; \
        it->deref = Deque_##T##_Iterator_deref; \
        it->inc = Deque_##T##_Iterator_inc; \
        it->dec = Deque_##T##_Iterator_dec; \
    } \
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
        return self->_arr[(self->_back - 1) % self->_capacity]; \
    } \
    void Deque_##T##_pop_back(Deque_##T* self) { \
        /* Assumes queue is not empty */ \
        self->_back -= 1; \
    } \
    void Deque_##T##_pop_front(Deque_##T* self) { \
        /* Assumes queue is not empty */ \
        self->_front += 1; \
    } \
    Deque_##T##_Iterator Deque_##T##_begin( \
        Deque_##T* self \
    ) { \
        Deque_##T##_Iterator it; \
        Deque_##T##_Iterator_ctor(&it, self, 0); \
        return it; \
    } \
    Deque_##T##_Iterator Deque_##T##_end( \
        Deque_##T* self \
    ) { \
        Deque_##T##_Iterator it; \
        Deque_##T##_Iterator_ctor(&it, self, self->size(self)); \
        return it; \
    } \
    T& Deque_##T##_at(Deque_##T* self, size_t cursor) { \
        /* Performs no bounds checking */ \
        size_t effective_front = self->_front % self->_capacity; \
        if (effective_front + cursor >= self->_capacity) { \
            return self->_arr[effective_front + cursor - self->_capacity]; \
        } else { \
            return self->_arr[effective_front + cursor]; \
        } \
    } \
    void Deque_##T##_clear(Deque_##T* self) { \
        free(self->_arr); \
        self->_arr = 0; \
        self->_capacity = 0; \
        self->_front = 0; \
        self->_back = 0; \
    } \
    void Deque_##T##_dtor(Deque_##T* self) { \
        self->clear(self); \
    } \
    int Deque_##T##_qsort_r_compare(const void* a, const void* b, void* context) { \
        Deque_##T* self = (Deque_##T*) context; \
        const T* left = (T*) a; \
        const T* right = (T*) b; \
        bool left_less_than_right = self->less_than(*left, *right); \
        bool right_less_than_left = self->less_than(*right, *left); \
        if (!left_less_than_right && !right_less_than_left) { \
            /* left = right */ \
            return 0; \
        } else if (left_less_than_right) { \
            /* left < right */ \
            return -1; \
        } else { \
            return 1; \
        } \
    } \
    void Deque_##T##_sort(Deque_##T* self, Deque_##T##_Iterator low, Deque_##T##_Iterator high) { \
        /* Copy the deque elements into a buffer */ \
        size_t buffer_size = high._cursor - low._cursor; \
        T* buffer = (T*) malloc(buffer_size * sizeof(T)); \
        size_t i = 0; \
        for (Deque_##T##_Iterator iter = low; \
             !Deque_##T##_Iterator_equal(iter, high); \
             iter.inc(&iter)) { \
            buffer[i] = iter.deref(&iter); \
            i += 1; \
        } \
        /* Sort this buffer */ \
        qsort_r((void*) buffer, buffer_size, sizeof(T), Deque_##T##_qsort_r_compare, (void*) self); \
        /* Copy the buffer back into the deque */ \
        i = 0; \
        for (Deque_##T##_Iterator iter = low; \
             !Deque_##T##_Iterator_equal(iter, high); \
             iter.inc(&iter)) { \
            iter.deref(&iter) = buffer[i]; \
            i += 1; \
        } \
    } \
    void Deque_##T##_ctor( \
        Deque_##T* deque, \
        T##_compare less_than \
    ) { \
        deque->_arr = 0; \
        deque->_capacity = 0; \
        deque->_front = 0; \
        deque->_back = 0; \
        strcpy(deque->type_name, Deque_##T##_type_name); \
        deque->less_than = less_than; \
        deque->size = Deque_##T##_size; \
        deque->empty = Deque_##T##_empty; \
        deque->grow = Deque_##T##_grow; \
        deque->push_back = Deque_##T##_push_back; \
        deque->push_front = Deque_##T##_push_front; \
        deque->front = Deque_##T##_front; \
        deque->back = Deque_##T##_back; \
        deque->pop_back = Deque_##T##_pop_back; \
        deque->pop_front = Deque_##T##_pop_front; \
        deque->begin = Deque_##T##_begin; \
        deque->end = Deque_##T##_end; \
        deque->at = Deque_##T##_at; \
        deque->clear = Deque_##T##_clear; \
        deque->dtor = Deque_##T##_dtor; \
        deque->sort = Deque_##T##_sort; \
    }

#endif
