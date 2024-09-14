#include <string>
using namespace std;

bool has_parenthesis(string);
bool valid_parenthesis(string);
bool is_number(char);
bool is_op(char);
bool is_paren(char);
bool has_contents(string);
string compress_exp(string);
bool valid_op_layout(string);
int perf_op(int);
void unload();
void reload();
void conduct_EMDAS(int);
void evaluate(int);
string eval_exp(string);
void input_vars(string e);