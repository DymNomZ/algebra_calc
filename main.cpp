#include <iostream>
#include <stdlib.h>
#include "stack.h"
#include "alg_func.h"

using namespace std;

int main(){
    char a;
    string exp;

    do{
        cout << "Enclose your expression with parenthesis ie. (1 + 1), pure 1+1 won't work" << endl;
        cout << "Only letters are to be used for variables (a-z), capital letters will be converted to lowercase" << endl;
        cout << "Therefore, other characters will be ignored" << endl;
        cout << "Note: use '^' for exponents" << endl;
        cout << "Follow my GitHub <3 @DymNomZ" << endl;
        cout << "_________________________________________________________________________________________________________" << endl;
        cout << "Enter expresion: " << endl;
        getline(cin, exp);
        if(!has_parenthesis(exp)) cout << "Put expression inside parenthesis!" << endl << endl;
        else if(!valid_parenthesis(exp)) cout << "Invalid expression: Unbalanced Parenthesis" << endl << endl;
        else if(!has_contents(exp)) cout << "Invalid express: Expression is empty" << endl << endl;
        else if(!valid_op_layout(exp)) cout << "Invalid expression: Improper arrangement of operation/s" << endl << endl;
        else{
            exp = compress_exp(exp);
            input_vars(exp);
            cout << "Answer: " << eval_exp(exp) << endl << endl;
        }

        cout << "Press any key to continue, Press e to exit..." << endl;
        cin >> a;
        system("cls");
        cin.ignore();
    }while(a != 'e');
}