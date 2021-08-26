//Input Format.The first line of the input contains the number 𝑞 of queries.Each of the following 𝑞 lines
//specifies a query of one of the following formats : push v, pop, or max.
//Constraints. 1 ≤ 𝑞 ≤ 400 000, 0 ≤ 𝑣 ≤ 10^5.
//Output Format.For each max query, output(on a separate line) the maximum value of the stack.

#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>
#include <stack>

using std::cin;
using std::string;
using std::vector;
using std::cout;
using std::max_element;


class StackWithMax {
    vector<int> stack;
    std::stack<int> aux;
public:

    void Push(int value) {
        stack.push_back(value);
        if (aux.empty())
        {
            aux.push(value);
        }
        else {
            if (aux.top() <= value) aux.push(value);
        }
    }

    void Pop() {
        assert(stack.size());
        if (aux.top() == stack.back()) aux.pop();
        stack.pop_back();
    }

    int Max() const {
        assert(stack.size());
        return aux.top();
    }
};

int main() {
    int num_queries = 0;
    cin >> num_queries;

    string query;
    string value;

    StackWithMax stack;

    for (int i = 0; i < num_queries; ++i) {
        cin >> query;
        if (query == "push") {
            cin >> value;
            stack.Push(std::stoi(value));
        }
        else if (query == "pop") {
            stack.Pop();
        }
        else if (query == "max") {
            cout << stack.Max() << "\n";
        }
        else {
            assert(0);
        }
    }
    return 0;
}