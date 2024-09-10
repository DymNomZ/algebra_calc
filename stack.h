#pragma once
#include <vector>
#include "element.h" 

using namespace std;

template<typename T>
class Stack{
    vector<T> stack_e;

    public:
        Stack();
        void push(T);
        T pop();
        T peek();
        bool is_empty();
        int get_size();
        vector<T> get_e();
        void test_print();
        void stack_clear();
};

#include "stack.dpp"