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
        cout << "Only letters are to be used for variables (a-z), capital letters will be converted to lowercase" << endl;
        cout << "Bug: ascii for operators -+/*^ can result to collision, ie. 47 and / (47)" << endl;
        cout << "If ya'll have solutions for these bugs pls do send me a PR hehe Xp" << endl;
        cout << "Note: use '^' for exponents" << endl << endl;
        cout << "Enter expresion: " << endl;
        getline(cin, exp);

        if(!valid_parenthesis(exp)) cout << "Invalid expression: Unbalanced Parenthesis" << endl << endl;
        else if(!has_contents(exp)) cout << "Invalid express: Expression is empty" << endl << endl;
        else if(!valid_op_layout(exp)) cout << "Invalid expression: Improper arrangement of operation/s" << endl << endl;
        else{
            exp = compress_exp(exp);
            //if(!valid_vars(exp)) cout << "Invalid expression: invalid variable character" << endl << endl;
            //else{
                input_vars(exp);
                cout << "Answer: " << endl;
                cout << eval_exp(exp) << endl << endl;
            //}
        }

        cout << "Press any key to continue, Press e to exit..." << endl;
        cin >> a;
        system("cls");
        cin.ignore();
    }while(a != 'e');
}