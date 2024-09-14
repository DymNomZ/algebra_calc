#include <iostream>
#include <string>
#include <vector>
#include "stack.h"
#include "element.h"

using namespace std;

Stack<Element> sol, eval, mdas;
int has_E = 0, has_MD = 0, has_AS = 0;
//index 0 is unoccupied for simplicity
int vars[27];
//not in here tho XD
int ops[] = {94, 94, 42, 47, 43, 45};

bool has_parenthesis(string e){
    for(int i = 0; i < e.length(); i++) if(e[i] == '(' || e[i] == ')') return true;
    return false;
}

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
        //just included checker for different operators
        if(e[i] == '^') has_E++;
        if(e[i] == '*' || e[i] == '/') has_MD++;
        if(e[i] == '+' || e[i] == '-') has_AS++;
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
    Element ev = eval.pop();
    Element mds = mdas.pop();
    switch(a){
        case '+':
        ans = mds.value + ev.value;
        break;

        case '-':
        ans = mds.value - ev.value;
        break;

        case '*':
        ans = mds.value * ev.value;
        break;

        case '/':
        ans = mds.value / ev.value;
        break;

        case '^':
        og = mds.value;
        ans = og;
        pow = ev.value;
        for(int i = 2; i <= pow; i++){
            ans *= og;
        }
        break;
    }
    return ans;
}

void unload(){
    cout << "Unloading..." << endl;
    Element a = {0, 0};
    while(a.type != 2){
        a = sol.pop();
        cout << "Popped sol unload: " << a.value << endl;
        if(a.type == 0){
            eval.push(a);
            cout << "Pushed eval unload operator: " << a.value << endl;
        }
        else if(a.type == 1){
            eval.push(a);
            cout << "Pushed eval unload number: " << a.value << endl;
        }
        
    }
}

void reload(){
    cout << "Reloading..." << endl;
    Element a = {0, 0};
    while(!mdas.is_empty()){
        a = mdas.pop();
        cout << "Popped mdas reload: " << a.value << endl;
        if(a.type == 0){
            eval.push(a);
            cout << "Pushed eval reload operator: " << a.value << endl;
        }
        else if(a.type == 1){
            eval.push(a);
            cout << "Pushed eval reload number: " << a.value << endl;
        }
        
    }
}

void conduct_EMDAS(int idx){
    cout << "Op nums: Exp: " << has_E << "MD: " << has_MD << "AS: " << has_AS << endl;
    Element a = {0, 0};
    while(!eval.is_empty()){
        a = eval.pop();
        cout << "Popped eval: " << a.value << endl;
        if(a.type == 0 && eval.peek().type == 1 && (a.value == ops[idx] || a.value == ops[idx+1])){
            cout << "Performing " << a.value << endl;
            a.value = perf_op(a.value);
            a.type = 1;
            cout << "After: " << a.value << endl;
            mdas.push(a);
            cout << "Pushed mdas after: " << a.value << endl;
            if(idx == 0) has_E--;
            if(idx == 2) has_MD--;
            if(idx == 4) has_AS--;
            cout << "Op nums: Exp: " << has_E << "MD: " << has_MD << "AS: " << has_AS << endl;
        }
        else if(a.type == 0){
            mdas.push(a);
            cout << "Pushed mdas operator not priority: " << a.value << endl;
        }
        else if(a.type == 1){
            mdas.push(a);
            cout << "Pushed mdas number: " << a.value << endl;
        }
        
    }
    reload();
}

void evaluate(){
    //unload from sol stack to eval stack
    unload();
    if(has_E > 0) conduct_EMDAS(0);
    if(has_MD > 0) conduct_EMDAS(2);
    if(has_AS > 0) conduct_EMDAS(4);
    Element ans = eval.pop();
    sol.push(ans);
    cout << "Pushed sol: " << ans.value << endl;
    eval.stack_clear();
}

string eval_exp(string e){
    for(int i = 0; i < e.length(); i++){
        //start of parenthesis
        if(e[i] == '('){
            Element x = {e[i], 2};
            sol.push(x);
            cout << "Open parenthesis encountered!"<< endl;
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
        }
        else if(is_op(e[i])){
            Element x = {e[i], 0};
            sol.push(x);
            cout << "Pushed sol op: " << x.value << endl;
        }
        else if(e[i] == ')'){
            cout << "Close parenthesis encountered! Evaluating..." << endl;
            evaluate();
            cout << "Parenthesis evaluation complete!" << endl;
        }
    }
    
    return to_string(sol.pop().value);
}