#include <iostream>
#include <string>
#include <vector>
#include "stack.h"
#include "element.h"

using namespace std;

Stack<Element> sol, eval;
Stack<int> eOp_num;
bool act_paren = false;
int eOp_paren = 0, num_Op_paren = 0;
//index 0 is unoccupied for simplicity
int vars[27];

bool valid_parenthesis(string e){
    Stack<char> s;
    for(int i = 0; i < e.length(); i++){
        if(e[i] == ' ') continue;
        if(e[i] == ')' && s.is_empty()) return false;
        if(e[i] == '(') s.push(e[i]);
        else if(e[i] == ')'){
            if(s.peek() == '(') s.pop();
        }
    }
    if(s.is_empty()) return true;
    return false;
}

bool is_number(char x){
    if(x >= '0' && x <= '9'){
        return true;
    }
    return false;
}

bool is_op(char x){
    if(x == '+' ||  x == '-' ||  x == '*' ||  x == '/' ||  x == '^'){
        return true;
    }
    return false;
}

bool is_paren(char x){
    if(x == '(' || x == ')') return true;
    return false;
}

bool has_contents(string e){
    int count = 0;
    for(int i = 0; i < e.length(); i++){
        if(is_paren(e[i]) || e[i] == ' ') continue;
        count++;
    }
    if(count > 0) return true;
    else return false;
}

string compress_exp(string e){
    string compressed;
    for(int i = 0; i < e.length(); i++){
        if(e[i] == ' ')continue;
        if(isalpha(e[i])) e[i] = tolower(e[i]);
        compressed += e[i];
    }
    return compressed;
}

bool valid_op_layout(string e){
    Stack<char> s;
    for(int i = 0; i < e.length(); i++){
        if(e[i] == ' ') continue;
        s.push(e[i]);
    }
    vector<char> se = s.get_e();
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

//fix
bool valid_vars(string e){
    for(int i = 0; i < e.length(); i++){
        if(!is_number(e[i]) && (e[i] < '0' || e[i] > '9') && (e[i] < 'a' || e[i] > 'z')) return false;
    }
    return true;
}

void input_vars(string e){
    for(int i = 0; i < e.length(); i++){
        if(isalpha(e[i])){
            int x;
            cout << "Input " << e[i] << ": ";
            cin >> x;
            //` is 96
            vars[e[i]-'`'] = x;
            cout << "Placed " << x << " at " << e[i] << endl;
        }
    }
}

int perf_op(int a){
    int ans = 0, pow = 0, og = 0;
    Element s = sol.pop();
    Element ev = eval.pop();
    switch(a){
        case '+':
        ans = s.value + ev.value;
        break;

        case '-':
        ans = s.value - ev.value;
        break;

        case '*':
        ans = s.value * ev.value;
        break;

        case '/':
        ans = s.value / ev.value;
        break;

        case '^':
        og = s.value;
        ans = og;
        pow = ev.value;
        for(int i = 2; i <= pow; i++){
            ans *= og;
        }
        break;
    }
    return ans;
}

void eval_parenthesis(){
    cout << "Elements since open parenthesis: " << eOp_paren << endl;
    Element a;
    while(eOp_paren > 0){
        a = sol.pop();
        cout << "Popped sol paren: " << a.value << endl;
        eOp_paren--;
        cout << "Elements since open parenthesis: " << eOp_paren << endl;
        if(a.type == 0 && sol.peek().type == 1){
            cout << "Performing " << a.value << endl;
            a.value = perf_op(a.value);
            a.type == 1;
            cout << "After: " << a.value << endl;
            eval.push(a);
            cout << "Pushed eval paren after: " << a.value << endl;
            eOp_paren -= 2;
        }
        else if(a.value == 1){
            eval.push(a);
            cout << "Pushed eval paren number: " << a.value << endl;
        }
        
    }
    eOp_paren = eOp_num.pop() + 1;
    Element temp = eval.pop();
    sol.push(temp);
    cout << "Pushed sol paren: " << temp.value << endl;
    eval.stack_clear();
    cout << endl;
    num_Op_paren--;
    cout << "Parenthesis evaluation complete! Paren remaining: " << num_Op_paren << endl;
    if(num_Op_paren == 0) act_paren = false;
}

void eval_no_parenthesis(){
    Element a;
    while(!sol.is_empty()){
        a = sol.pop();
        cout << "Popped sol no paren: " << a.value << endl;
        if(a.type == 1){
            eval.push(a);
            cout << "Pushed eval no paren num: " << a.value << endl;
        }
        else if(a.type == 0 && sol.peek().type == 1){
            a.value = perf_op(a.value);
            a.type == 1;
            eval.push(a);
            cout << "Pushed eval no paren after: " << a.value << endl;
        }
    }
    a = eval.pop();
    cout << "Popped eval no paren: " << a.value << endl;
    sol.push(a);
    cout << "Pushed sol no paren afters: " << a.value << endl;
}

//currently unused 
void eval_exponent(int x){
    cout << "performing expo" << endl;
    cout << x << endl;
    Element a = sol.pop();
    cout << "Popped sol: " << a.value << endl;
    int sum = a.value;
    for(int i = 2; i <= x; i++) sum *= a.value;
    a.value = sum;
    a.type = 1;
    sol.push(a);
    cout << "Pushed sol: " << sum << endl;
}

string eval_exp(string e){
    eOp_paren = 0;
    for(int i = 0; i < e.length(); i++){
        //start of parenthesis
        if(e[i] == '('){
            act_paren = true;
            eOp_num.push(eOp_paren);
            eOp_paren = 0;
            num_Op_paren++;
            cout << "Open parenthesis encountered! count: " << num_Op_paren << endl;
        }
        else if(isalpha(e[i])){
            //if previous is number, then multiply. ie. 5x, x = 6, 5(6) = 30
            if(!sol.is_empty() && sol.peek().type == 1){
                Element x = sol.pop();
                cout << "Multiplying variable " << e[i] << " with " << x.value << "..." << endl;
                x.value *= vars[e[i] - '`'];
                sol.push(x);
                cout << "Pushed sol varXnum: " << x.value << endl;
            }
            //sub value of variable, push normally
            else{
                Element x = {vars[e[i] - '`'], 1};
                sol.push(x);
                cout << "Pushed sol var: " << x.value << endl;
            }
        }
        else if(is_number(e[i])){
            //if number has two or more digits
            if(!sol.is_empty() && sol.peek().type == 1){
                Element x = sol.pop();
                cout << ">1 digits, value is: " << x.value << endl;
                x.value = x.value*10 + (e[i] - '0');
                cout << "New value: " << x.value << endl;
                sol.push(x);
                cout << "Pushed sol >number: " << x.value << endl;
            }
            else if(!sol.is_empty() && sol.peek().type == 0 && sol.peek().value == '-' && is_op(e[i-2])){
                //negative number
                sol.pop();
                int a = e[i]-'0';
                a -= a*2;
                Element x = {a, 1};
                sol.push(x);
                cout << "Pushed sol negative number: " << x.value << endl;
            }
            else{
                //single digit
                Element x = {e[i]-'0', 1};
                sol.push(x);
                cout << "Pushed sol reg number: " << x.value << endl;
            }
            if(act_paren) eOp_paren++;
        }
        else if(is_op(e[i])){
            Element x = {e[i], 0};
            sol.push(x);
            cout << "Pushed sol op: " << x.value << endl;
            if(act_paren) eOp_paren++;
        }
        else if(e[i] == ')') eval_parenthesis();
    }
    if(!sol.is_empty() && sol.get_size() > 1) eval_no_parenthesis();
    
    return to_string(sol.pop().value);
}