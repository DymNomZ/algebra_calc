#include <iostream>
#include <stdlib.h>
#include "stack.h"
#include "alg_func.h"

using namespace std;

int main(){
    char a;
    string exp;

    do{
        cout << "This here is my simple C++ algebra expression calculator" << endl;
        cout << "It will evaluate with or without parenthesis or both ie. 1 + 2 or (50 * 3) or 17 / (11 + 2)" << endl;
        cout << "It cannot evaluate perhaps \"advanced\" expressions such as 3x = 15, I made this for learning purposes" << endl;
        cout << "Only letters are to be used for variables (a-z), capital letters will be converted to lowercase" << endl;
        cout << "Therefore, other characters will be ignored" << endl;
        cout << "If anyone cares enough to test and encounter a bug, an issue ticket is appreciated <3" << endl;
        cout << "Note: use '^' for exponents" << endl;
        cout << "_________________________________________________________________________________________________________" << endl;
        cout << "Enter expresion: " << endl;
        getline(cin, exp);

        if(!valid_parenthesis(exp)) cout << "Invalid expression: Unbalanced Parenthesis" << endl << endl;
        else if(!has_contents(exp)) cout << "Invalid express: Expression is empty" << endl << endl;
        else if(!valid_op_layout(exp)) cout << "Invalid expression: Improper arrangement of operation/s" << endl << endl;
        else{
            exp = compress_exp(exp);
            input_vars(exp);
            cout << "Answer: " << endl;
            cout << eval_exp(exp) << endl << endl;
        }

        cout << "Press any key to continue, Press e to exit..." << endl;
        cin >> a;
        system("cls");
        cin.ignore();
    }while(a != 'e');
}