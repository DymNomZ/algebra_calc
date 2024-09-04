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
        if(e[i] == ')' && s.is_empty()) return false;
        if(e[i] == '(') s.push(e[i]);
        else if(e[i] == ')'){
            if(s.peek() == '(') s.pop();\
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

bool has_contents(string e){
    int count = 0;
    for(int i = 0; i < e.length(); i++){
        if(e[i] == '(' || e[i] == ')' || e[i] == ' ') continue;
        count++;
    }
    if(count > 0) return true;
    else return false;
}

string compress_exp(string e){
    string compressed;
    for(int i = 0; i < e.length(); i++){
        if(e[i] == ' ')continue;
        compressed += e[i];
    }
    return compressed;
}

bool valid_op_layout(string e){
    Stack s;
    for(int i = 0; i < e.length(); i++){
        if(e[i] == ' ') continue;
        s.push(e[i]);
    }
    vector<int> se = s.get_e();
    int sz = s.get_size();
    for(int i = 0; i < sz; i++){
        if(is_op(se[i])){
            if(sz == 1) return false;
            if(i == 0 && se[i] != '-' && is_number(se[i+1])) return false;
            else if(i == 0 && is_op(se[i+1])) return false;
            if(is_op(se[i+1]) && se[i+1] != '-') return false;
            else if(is_op(se[i+1]) && se[i+1] == '-' && !is_number(se[i+2])) return false;
            if(i == sz-1) return false;
        }
    }
    return true;
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

void eval_parenthesis(int x){
    int a = x;
    a = sol.pop();
    cout << "Popped sol paren: " << a << endl;
    while(a != '('){
        if(is_op(a) && is_number(sol.peek())){
            cout << "Performing " << a << endl;
            a = perf_op(a);
            cout << "After: " << a << endl;
            eval.push(a);
            cout << "Pushed eval paren after: " << a << endl;
        }
        else if(is_number(a)){
            eval.push(a);
            cout << "Pushed eval paren number: " << a << endl;
        }
        a = sol.pop();
        cout << "Popped sol paren: " << a << endl;
    }
    vector<int> eval_e = eval.get_e();
    int z;
    for(int i = 0; i < eval_e.size(); i++){
        cout << eval_e[i] << endl;
        if(eval_e[i] == '(' || eval_e[i] == ')') continue;
        else{
            sol.push(eval_e[i]);
            cout << "Pushed sol afters: " << eval_e[i] << endl;
        }
    }
    eval.stack_clear();
    cout << endl;
}

void eval_no_parenthesis(){
    int a;
    while(!sol.is_empty()){
        a = sol.pop();
        cout << "Popped sol no paren: " << a << endl;
        if(is_number(a)){
            eval.push(a);
            cout << "Pushed eval no paren num: " << a << endl;
        }
        else if(is_op(a) && is_number(sol.peek())){
            a = perf_op(a);
            eval.push(a);
            cout << "Pushed eval no paren after: " << a << endl;
        }
    }
    a = eval.pop();
    cout << "Popped eval no paren: " << a << endl;
    sol.push(a);
    cout << "Pushed sol no paren afters: " << a << endl;
}

void eval_exponent(int x){
    cout << "performing expo" << endl;
    cout << x << endl;
    int a = sol.pop();
    cout << "Popped sol: " << a << endl;
    int sum = a;
    for(int i = 2; i <= x; i++) sum *= a;
    sol.push(sum);
    cout << "Pushed sol: " << sum << endl;
}

string eval_exp(string e){
    for(int i = 0; i < e.length(); i++){
        // ignore space
        if(e[i] == ' ') continue;
        //start of parenthesis
        if(e[i] == '('){
            sol.push(e[i]);
            cout << "Pushed sol: " << e[i] << endl;
        }
        else if(e[i] >= '0' && e[i] <= '9'){
            //if number has two or more digits
            if(!sol.is_empty() && is_number(sol.peek())){
                int x = sol.pop();
                cout << ">1 digits, value is: " << x << endl;
                x = x*10 + (e[i] - '0');
                cout << "New value: " << x << endl;
                sol.push(x);
                cout << "Pushed sol >number: " << x << endl;
            }
            else if(!sol.is_empty() && is_op(sol.peek()) && sol.peek() == '-' && e[i-1] != ' '){
                //negative number
                sol.pop();
                int a = e[i]-'0';
                a -= a*2;
                sol.push(a);
                cout << "Pushed sol negative number: " << endl;
            }
            else{
                //single digit
                sol.push(e[i]-'0');
                cout << "Pushed sol reg number: " << e[i]-'0' << endl;
            }
        }
        //if regular operator
        else if(is_op(e[i])){
            sol.push(e[i]);
            cout << "Pushed sol op: " << e[i] << endl;
        }
        else if(e[i] == ')') eval_parenthesis(e[i]);
    }
    if(!sol.is_empty() && sol.get_size() > 1) eval_no_parenthesis();
    
    return to_string(sol.pop());
}