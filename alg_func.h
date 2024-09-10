#include <string>
using namespace std;

bool valid_parenthesis(string);
bool is_number(char);
bool is_op(char);
bool is_paren(char);
bool has_contents(string);
string compress_exp(string);
bool valid_op_layout(string);
bool valid_vars(string);


int perf_op(int);
void eval_parenthesis(int);
void eval_exponent(int);

string eval_exp(string);
void input_vars(string e);