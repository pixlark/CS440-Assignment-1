#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Deque.hpp"


bool less_than(const int& a, const int& b) {
    return a < b;
}

struct MyClass {
    int id;
    char name[10];
};

Deque_DEFINE(MyClass)
Deque_DEFINE(int)

void debug_dump(Deque_int* deque) {
    printf("front: %u; back: %u; size: %zu; capacity: %u\n", deque->_front, deque->_back, deque->size(deque), deque->_capacity);
    printf("[ ");
    for (size_t i = 0; i < deque->_capacity; i++) {
        printf("%d ", deque->_arr[i]);
    }
    printf("]\n");
}

void debug_dump(Deque_MyClass* deque) {
    printf("front: %u; back: %u; size: %zu; capacity: %u\n", deque->_front, deque->_back, deque->size(deque), deque->_capacity);
    printf("[ ");
    for (size_t i = 0; i < deque->_capacity; i++) {
        printf("(%d %s) ", deque->_arr[i].id, deque->_arr[i].name);
    }
    printf("]\n");
}

bool
MyClass_less_by_id(const MyClass &o1, const MyClass &o2) {
    return o1.id < o2.id;
}

bool
MyClass_less_by_name(const MyClass &o1, const MyClass &o2) {
    return strcmp(o1.name, o2.name) < 0;
}

void
MyClass_print(const MyClass *o) {
    printf("%d\n", o->id);
    printf("%s\n", o->name);
}

int main() {
    enum { AMT = 10 };
    
    Deque_int deq1;
    Deque_int_ctor(&deq1, less_than);

    for (int i=0;i<AMT;i++) {
        deq1.push_back(&deq1, i);
    }

    for (int i=2*AMT;i>=AMT;i--) {
        deq1.push_back(&deq1,i);
    }

    deq1.push_back(&deq1,2*AMT + 1);
      
    auto iter1 =  deq1.end(&deq1);
    iter1.dec(&iter1);	
       
    auto iter2 = deq1.begin(&deq1);
       
    for (int i=0;i<AMT;i++) {
        iter2.inc(&iter2);
    }

    debug_dump(&deq1);
    deq1.sort(&deq1, iter2,iter1);
    debug_dump(&deq1);

    Deque_int deq2;
    Deque_int_ctor(&deq2 , less_than);

    for(int i=0;i<=2*AMT + 1;i++) {
        deq2.push_back(&deq2,i);
    }

    debug_dump(&deq2);

    assert(Deque_int_equal(deq1, deq2)); 

    deq1.dtor(&deq1);
    deq2.dtor(&deq2);

    return 0;
}
