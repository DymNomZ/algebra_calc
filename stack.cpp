#include <iostream>
#include <vector>
#include "stack.h"

using namespace std;

Stack::Stack(){

}

bool Stack::is_empty(){
    return stack_e.empty();
}

int Stack::get_size(){
    return stack_e.size();
}

vector<int> Stack::get_e(){
    return stack_e;
}

void Stack::test_print(){
    for(int i = 0; i < stack_e.size(); i++){
        cout << stack_e[i] << " ";
    }
    cout << endl;
}

void Stack::push(int x){
    stack_e.push_back(x);
}

int Stack::pop(){
    int x = stack_e.back();
    stack_e.pop_back();
    return x;
}

int Stack::peek(){
    return stack_e.back();
}