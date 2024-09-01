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
        cout << "Note: use '^' for exponents" << endl << endl;
        cout << "Enter expresion: " << endl;
        getline(cin, exp);

        if(!valid_parenthesis(exp)) cout << "Invalid expression: Unbalanced Parenthesis" << endl << endl;
        else{
            cout << "Answer: " << endl;
            cout << eval_exp(exp) << endl << endl;
        }


        cout << "Press any key to continue, Press e to exit..." << endl;
        cin >> a;
        system("cls");
        cin.ignore();
    }while(a != 'e');
}