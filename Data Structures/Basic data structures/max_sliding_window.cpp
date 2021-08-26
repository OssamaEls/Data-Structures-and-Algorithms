//Input Format.The first line contains an integer 𝑛, the second line contains 𝑛 integers 𝑎1, . . ., 𝑎𝑛 separated
//by spaces, the third line contains an integer 𝑚.
//Constraints. 1 ≤ 𝑛 ≤ 10^5, 1 ≤ 𝑚 ≤ 𝑛, 0 ≤ 𝑎𝑖 ≤ 10^5 for all 1 ≤ 𝑖 ≤ 𝑛.
//Output Format.Output max{ 𝑎𝑖, . . . , 𝑎𝑖 + 𝑚−1 } for every 1 ≤ 𝑖 ≤ 𝑛 − 𝑚 + 1.


#include <iostream>
#include <vector>
#include <stack>
#include <cassert>


using std::cin;
using std::cout;
using std::vector;
using std::max;

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

    int Size() const {
        return stack.size();
    }

    int Top() const {
        return stack.back();
    }

};

void max_sliding_window_naive(vector<int> const& A, int w) {
    for (size_t i = 0; i < A.size() - w + 1; ++i) {
        int window_max = A.at(i);
        for (size_t j = i + 1; j < i + w; ++j)
            window_max = max(window_max, A.at(j));

        cout << window_max << " ";
    }

    return;
}


int main() {
    int n = 0;
    cin >> n;

    vector<int> A(n);
    for (size_t i = 0; i < n; ++i)
        cin >> A.at(i);

    int w = 0;
    cin >> w;

    int i;
    int j;
    StackWithMax stack1;
    StackWithMax stack2;

    if (w == 1)
    {
        for (size_t i = 0; i < n; i++)
        {
            cout << A[i] << ' ';
        }
        return 0;
    }

    for (i = 0; i < w; i++)
    {
        stack1.Push(A[w - 1 - i]);
    }
    cout << stack1.Max() << ' ';

    while (i < n)
    {
        if (stack2.Size() < w)
        {
            stack2.Push(A[i]);
            stack1.Pop();
            if (stack2.Size() == w)
            {
                cout << stack2.Max() << ' ';
            }
            else
            {
                cout << max(stack1.Max(), stack2.Max()) << ' ';
            }
        }
        else
        {
            for (j = 0; j < w - 1; ++j)
            {
                stack1.Push(stack2.Top());
                stack2.Pop();
            }
            stack2.Pop();
            stack2.Push(A[i]);
            cout << max(stack1.Max(), stack2.Max()) << ' ';
        }
        ++i;
    }

    return 0;
}