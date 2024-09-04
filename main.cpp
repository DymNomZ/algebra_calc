#include <iostream>
#include <stdlib.h>
#include "stack.h"
#include "alg_func.h"

using namespace std;

int main(){
    char a;
    string exp;

    do{
        cout << "Sample text....." << endl;
        cout << "1 + + 1 will be considered valid while 1++1 is not" << endl;
        cout << "So if you do something like 5 + - 1, the 2nd sign will be ignored" << endl;
        cout << "If you have a much better solution than the shit I came up with, do send me a PR hehe :p" << endl;
        cout << "Note: use '^' for exponents" << endl << endl;
        cout << "Enter expresion: " << endl;
        getline(cin, exp);

        if(!valid_parenthesis(exp)) cout << "Invalid expression: Unbalanced Parenthesis" << endl << endl;
        else if(!has_contents(exp)) cout << "Invalid express: Expression is empty" << endl << endl;
        else if(!valid_op_layout(exp)) cout << "Invalid expression: Improper arrangement of operation/s" << endl << endl;
        else{
            exp = compress_exp(exp);
            cout << "Answer: " << endl;
            cout << eval_exp(exp) << endl << endl;
        }


        cout << "Press any key to continue, Press e to exit..." << endl;
        cin >> a;
        system("cls");
        cin.ignore();
    }while(a != 'e');
}