//Input Format.The only line of the input contains a string 𝑠 of length 2𝑛 + 1 for some 𝑛, with symbols
//𝑠0, 𝑠1, . . ., 𝑠2𝑛.Each symbol at an even position of 𝑠 is a digit(that is, an integer from 0 to 9) while
//each symbol at an odd position is one of three operations from{ +,-,* }.
//Constraints. 0 ≤ 𝑛 ≤ 14 (hence the string contains at most 29 symbols).
//Output Format.Output the maximum possible value of the given arithmetic expression among different
//orders of applying arithmetic operations.

#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <limits>

using std::vector;
using std::string;
using std::max;
using std::min;

typedef vector<vector<long long>> matrix;

long long eval(long long a, long long b, char op) {
    if (op == '*') {
        return a * b;
    }
    else if (op == '+') {
        return a + b;
    }
    else if (op == '-') {
        return a - b;
    }
    else {
        assert(0);
    }
}

void minmax(int i, int j, const string& ops, matrix& m, matrix& M)
{
    long long mini = std::numeric_limits<long long>::max();
    long long maxi = std::numeric_limits<long long>::min();
    long long a, b, c, d;
    for (int k = i; k < j; k++)
    {
        a = eval(M[i][k], M[k + 1][j], ops[k]);
        b = eval(M[i][k], m[k + 1][j], ops[k]);
        c = eval(m[i][k], M[k + 1][j], ops[k]);
        d = eval(m[i][k], m[k + 1][j], ops[k]);
        //mini = std::min({ mini, a, b, c ,d });
        //maxi = std::max({ maxi, a, b, c ,d });
        mini = min(mini, a);
        mini = min(mini, b);
        mini = min(mini, c);
        mini = min(mini, d);

        maxi = max(maxi, a);
        maxi = max(maxi, b);
        maxi = max(maxi, c);
        maxi = max(maxi, d);
    }
    m[i][j] = mini;
    M[i][j] = maxi;
}

long long get_maximum_value(const string& exp) {
    int p = exp.size();
    int n = (p - 1) / 2 + 1;
    string ops = "";
    for (int i = 1; i < p; i += 2)
    {
        ops = ops + exp[i];
    }

    matrix m(n, vector<long long>(n, 0));
    matrix M(n, vector<long long>(n, 0));

    for (int i = 0; i < n; i++)
    {
        m[i][i] = exp[2 * i] - '0';
        M[i][i] = m[i][i];
    }


    int j;
    for (int s = 1; s < n; s++)
    {
        for (int i = 0; i < n - s; i++)
        {
            j = i + s;
            minmax(i, j, ops, m, M);
        }
    }

    return M[0][n - 1];
}

int main() {
    string s;
    std::cin >> s;
    std::cout << get_maximum_value(s) << '\n';
}

