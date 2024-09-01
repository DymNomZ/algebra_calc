#include <vector>

using namespace std;

class Stack{
    vector<int> stack_e;

    void test_print();

    public:
        Stack();
        void push(int);
        int pop();
        int peek();
        bool is_empty();
        int get_size();
        vector<int> get_e();
};