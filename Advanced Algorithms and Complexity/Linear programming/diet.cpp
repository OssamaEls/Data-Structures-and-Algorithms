//Input Format.The first line of the input contains integers 𝑛and 𝑚 — the number of restrictions on your
//dietand the number of all available dishesand drinks respectively.The next 𝑛 + 1 lines contain the
//coefficients of the linear inequalities in the standard form 𝐴𝑥 ≤ 𝑏, where 𝑥 = amount is the vector of
//length 𝑚 with amounts of each ingredient, 𝐴 is the 𝑛 × 𝑚 matrix with coefficients of inequalitiesand
//𝑏 is the vector with the right - hand side of each inequality.Specifically, 𝑖 - th of the next 𝑛 lines contains
//𝑚 integers 𝐴𝑖1, 𝐴𝑖2, . . ., 𝐴𝑖𝑚, and the next line after those 𝑛 contains 𝑛 integers 𝑏1, 𝑏2, . . ., 𝑏𝑛.These
//lines describe 𝑛 inequalities of the form 𝐴𝑖1 · amount1 + 𝐴𝑖2 · amount2 + · · · + 𝐴𝑖𝑚 · amount𝑚 ≤ 𝑏𝑖.The
//last line of the input contains 𝑚 integers — the pleasure for consuming one item of each dishand drink
//pleasure1, pleasure2, . . ., pleasure𝑚.
//
//Constraints. 1 ≤ 𝑛, 𝑚 ≤ 8; −100 ≤ 𝐴𝑖𝑗 ≤ 100; −1 000 000 ≤ 𝑏𝑖 ≤ 1 000 000; −100 ≤ cost𝑖 ≤ 100.
//
//Output Format.If there is no diet that satisfies all the restrictions, output “No solution”(without quotes).
//If you can get as much pleasure as you want despite all the restrictions, output “Infinity”(without
//    quotes).If the maximum possible total pleasure is bounded, output two lines.On the first line, output
//    “Bounded solution”(without quotes).On the second line, output 𝑚 real numbers — the optimal amounts
//    for each dishand drink.Output all the numbers with at least 15 digits after the decimal point.

#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdio>
#include <set>
#include <limits>

using namespace std;

const double EPS = 1e-6;
const int PRECISION = 20;

typedef vector<double> Column;
typedef vector<double> Row;
typedef vector<Row> Matrix;

struct Equation {
    Equation(const Matrix& a, const Column& b) :
        a(a),
        b(b)
    {}

    Matrix a;
    Column b;
};

struct Position {
    Position(int column, int row) :
        column(column),
        row(row)
    {}

    int column;
    int row;
};

Equation get_equation(set<int>& m_set, Matrix& A, Column& b) {
    int m = m_set.size();
    int n = A.size();
    Matrix A_m(m, vector<double>(m, 0.0));
    Column b_m(m, 0.0);
    int idx = 0;
    for (auto it = m_set.begin(); it != m_set.end(); it++)
    {
        int row = *it;
        if (row <= n)
        {
            for (size_t column = 0; column < m; column++)
            {
                A_m[idx][column] = A[row - 1][column];
            }
            b_m[idx] = b[row - 1];
        }
        else
        {
            if (row < n + m + 1)
            {
                A_m[idx][row - n - 1] = 1;
            }
            else
            {
                for (size_t column = 0; column < m; column++)
                {
                    A_m[idx][column] = 1;
                }
                b_m[idx] = 1000000000.0;
            }
        }
        ++idx;
    }

    return Equation(A_m, b_m);
}

Position SelectPivotElement(const Matrix& a, int step) {
    Position pivot_element(step, step);
    while (pivot_element.row < a.size() && abs(a[pivot_element.row][step]) < EPS)
        ++pivot_element.row;
    return pivot_element;
}

void SwapLines(Matrix& a, Column& b, Position& pivot_element) {
    std::swap(a[pivot_element.column], a[pivot_element.row]);
    std::swap(b[pivot_element.column], b[pivot_element.row]);
    pivot_element.row = pivot_element.column;
}

void ProcessPivotElement(Matrix& a, Column& b, const Position& pivot_element) {

    int piv_col = pivot_element.column;
    int piv_row = pivot_element.row;
    double piv_coeff = a[piv_row][piv_col];


    for (size_t col = 0; col < a.size(); col++)
    {
        a[piv_row][col] /= piv_coeff;
    }
    b[piv_row] /= piv_coeff;
    a[piv_row][piv_col] = 1.0;

    for (size_t row = 0; row < a.size(); row++)
    {
        if (row != piv_row)
        {
            double to_cancel = a[row][piv_col];
            for (size_t col = 0; col < a.size(); col++)
            {
                a[row][col] -= to_cancel * a[piv_row][col];
            }
            b[row] -= to_cancel * b[piv_row];
            a[row][piv_col] = 0.0;
        }
    }

}


pair<bool, Column> SolveEquation(Equation& equation) {
    Matrix& a = equation.a;
    Column& b = equation.b;
    int size = a.size();

    for (int step = 0; step < size; ++step) {
        Position pivot_element = SelectPivotElement(a, step);
        if (pivot_element.row == size)
            return { false, b };
        SwapLines(a, b, pivot_element);
        ProcessPivotElement(a, b, pivot_element);
    }

    return { true,b };
}

bool verify_equation(Column& solution, Matrix& A, Column& b, int row)
{
    double result = 0.0;
    for (int column = 0; column < solution.size(); column++)
    {
        result += A[row][column] * solution[column];
    }
    return result <= b[row];
}

bool satisfied(Column& solution, set<int>& m_set, Matrix& A, Column& b)
{
    int m = solution.size();
    int n = A.size();

    for (int i = 1; i <= n; i++)
    {
        if (m_set.find(i) == m_set.end())
        {
            if (!verify_equation(solution, A, b, i - 1))
                return false;
        }
    }

    for (int i = n + 1; i <= n + m; i++)
    {
        if (m_set.find(i) == m_set.end())
        {
            if (solution[i - n - 1] < 0)
                return false;
        }
    }

    return true;
}

vector<set<int>> sets_size_m(int n, int m)
{

    vector<set<int>> all_sets = { {} };
    vector<set<int>> result;

    for (size_t i = 1; i <= n + m + 1; i++)
    {
        vector<set<int>> previous_set = all_sets;
        for (size_t j = 0; j < previous_set.size(); j++)
        {
            previous_set[j].insert(i);
            all_sets.push_back(previous_set[j]);
        }
    }

    for (size_t i = 0; i < all_sets.size(); i++)
    {
        if (all_sets[i].size() == m)
            result.push_back(all_sets[i]);
    }

    return result;
}


pair<int, vector<double>> solve_diet_problem(int n, int m, Matrix& A, Column& b, Column& c) {

    vector<set<int>> inequalities_subset = sets_size_m(n, m);
    vector<pair<double, vector<double>>> max_solutions;
    int num_solutions = 0;
    double best_solution = -numeric_limits<double>::max();

    int idx_best_solution = 0;
    for (size_t i = 0; i < inequalities_subset.size(); i++)
    {
        set<int>& m_set = inequalities_subset[i];

        Equation equation = get_equation(m_set, A, b);
        pair<bool, Column> solution = SolveEquation(equation);

        if (solution.first)
        {
            if (satisfied(solution.second, m_set, A, b))
            {
                ++num_solutions;
                max_solutions.push_back({ 0.0, solution.second });
                for (int j = 0; j < m; j++)
                {
                    max_solutions[num_solutions - 1].first += solution.second[j] * c[j];
                }
                if (max_solutions[num_solutions - 1].first > best_solution)
                {
                    best_solution = max_solutions[num_solutions - 1].first;
                    idx_best_solution = m_set.find(n + m + 1) != m_set.end() ? -1 : num_solutions - 1;
                }
            }
        }
    }

    if (num_solutions == 0)
    {
        return { -1, {} };
    }

    if (idx_best_solution == -1)
        return { 1, {} };

    return { 0, max_solutions[idx_best_solution].second };
}

int main() {
    int n, m;
    cin >> n >> m;
    Matrix A(n, vector<double>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> A[i][j];
        }
    }
    vector<double> b(n);
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    vector<double> c(m);
    for (int i = 0; i < m; i++) {
        cin >> c[i];
    }

    pair<int, vector<double>> ans = solve_diet_problem(n, m, A, b, c);

    switch (ans.first) {
    case -1:
        printf("No solution\n");
        break;
    case 0:
        printf("Bounded solution\n");
        for (int i = 0; i < m; i++) {
            printf("%.18f%c", ans.second[i], " \n"[i + 1 == m]);
        }
        break;
    case 1:
        printf("Infinity\n");
        break;
    }

    return 0;
}