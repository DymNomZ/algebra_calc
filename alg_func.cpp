#include <iostream>
#include <string>
#include <vector>
#include "stack.h"

using namespace std;

Stack sol, eval;

bool valid_parenthesis(string e){
    Stack s;
    for(int i = 0; i < e.length(); i++){
        if(e[i] == ' ') continue;
        if(e[i] == '(') s.push(e[i]);
        else if(e[i] == ')'){
            if(s.peek() == '(') s.pop();
        }
    }
    if(s.is_empty()) return true;
    return false;
}

bool is_number(int x){
    if(x != '(' && x != ')' &&  x != '+' &&  x != '-' &&  x != '*' &&  x != '/' &&  x != '^'){
        return true;
    }
    return false;
}

bool is_op(int x){
    if(x == '+' ||  x == '-' ||  x == '*' ||  x == '/' ||  x == '^'){
        return true;
    }
    return false;
}

int perf_op(int a){
    int ans = 0, pow = 0, og = 0;
    switch(a){
        case '+':
        ans = sol.pop() + eval.pop();
        break;

        case '-':
        ans = sol.pop() - eval.pop();
        break;

        case '*':
        ans = sol.pop() * eval.pop();
        break;

        case '/':
        ans = sol.pop() / eval.pop();
        break;

        case '^':
        og = sol.pop();
        ans = og;
        pow = eval.pop();
        for(int i = 2; i <= pow; i++){
            ans *= og;
        }
        break;
    }
    return ans;
}

void eval_smol(int x){
    int a = x;
    eval.push(a);
    a = sol.pop();
    char temp = a;
    cout << "Popped: " << temp << endl;
    while(a != '('){
        if(is_op(a) && is_number(sol.peek())){
            cout << "Performing " << temp << endl;
            a = perf_op(a);
            cout << "After: " << a << endl;
            eval.push(a);
            cout << "Pushed: " << a << endl;
        }
        else if(is_number(a)){
            eval.push(a);
            cout << "Pushed: " << a << endl;
        }
        a = sol.pop();
        cout << "Popped: " << temp << endl;
    }
    vector<int> eval_e = eval.get_e();
    for(int i = 0; i < eval_e.size(); i++){
        if(eval_e[i] == '(' || eval_e[i] == ')') eval.pop();
        else sol.push(eval_e[i]);
    }
}

void eval_no_parenthesis(){
    int a;
    while(!sol.is_empty()){
        a = sol.pop();
        if(is_number(a)){
            eval.push(a);
            cout << "Pushed: " << a << endl;
        }
        else if(is_op(a) && is_number(sol.peek())){
            a = perf_op(a);
            eval.push(a);
            cout << "Pushed: " << a << endl;
        }
    }
    a = eval.pop();
    cout << "Popped: " << a << endl;
    sol.push(a);
    cout << "Pushed: " << a << endl;
}

string eval_exp(string e){
    for(int i = 0; i < e.length(); i++){
        if(e[i] == ' ') continue;
        if(e[i] == '(') sol.push(e[i]);
        else if(e[i] >= '0' && e[i] <= '9'){
            if(!sol.is_empty() && is_number(sol.peek())){
                int x = sol.pop();
                cout << ">1 digits, value is: " << x << endl;
                x = x*10 + (e[i] - '0');
                cout << "New value: " << x << endl;
                sol.push(x);
                cout << "Pushed: " << x << endl;
            }else{
                sol.push(e[i]-'0');
                cout << "Pushed: " << e[i]-'0' << endl;
            }
        }
        else if(is_op(e[i])){
            sol.push(e[i]);
            cout << "Pushed: " << e[i] << endl;
        }
        else if(e[i] == ')') eval_smol(e[i]);
    }
    if(!sol.is_empty() && sol.get_size() > 1) eval_no_parenthesis();
    
    return to_string(sol.pop());
}