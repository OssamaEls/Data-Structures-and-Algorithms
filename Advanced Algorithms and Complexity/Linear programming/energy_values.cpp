//Input Format.The first line of the input contains an integer 𝑛 — the number of dishes in the menu, and
//it happens so that the number of different ingredients is the same.Each of the next 𝑛 lines contains
//description 𝑎1, 𝑎2, . . ., 𝑎𝑛, 𝐸 of a single menu item.𝑎𝑖 is the amount of 𝑖 - th ingredient in the dish, and
//𝐸 is the estimated total energy value of the dish.If the ingredient is not used in the dish, the amount
//will be specified as 𝑎𝑖 = 0; beware that although the amount of any ingredient in any real
//menu would be positive, we will test that your algorithm works even for negative amounts
//𝑎𝑖 < 0.
//
//Constraints. 0 ≤ 𝑛 ≤ 20; −1000 ≤ 𝑎𝑖 ≤ 1000.
//
//Output Format.Output 𝑛 real numbers — for each ingredient, what is its energy value.These numbers
//    can be non - integer, so output them with at least 3 digits after the decimal point.

#include <cmath>
#include <iostream>
#include <vector>

const double EPS = 1e-6;
const int PRECISION = 20;

typedef std::vector<double> Column;
typedef std::vector<double> Row;
typedef std::vector<Row> Matrix;

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

Equation ReadEquation() {
    int size;
    std::cin >> size;
    Matrix a(size, std::vector<double>(size, 0.0));
    Column b(size, 0.0);
    for (int row = 0; row < size; ++row) {
        for (int column = 0; column < size; ++column)
            std::cin >> a[row][column];
        std::cin >> b[row];
    }
    return Equation(a, b);
}

Position SelectPivotElement(const Matrix& a, int step) {
    Position pivot_element(step, step);
    while (std::abs(a[pivot_element.row][step]) < EPS)
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
        }
    }

}


Column SolveEquation(Equation equation) {
    Matrix& a = equation.a;
    Column& b = equation.b;
    int size = a.size();

    std::vector <bool> used_columns(size, false);
    std::vector <bool> used_rows(size, false);
    for (int step = 0; step < size; ++step) {
        Position pivot_element = SelectPivotElement(a, step);
        SwapLines(a, b, pivot_element);
        ProcessPivotElement(a, b, pivot_element);
    }

    return b;
}

void PrintColumn(const Column& column) {
    int size = column.size();
    std::cout.precision(PRECISION);
    for (int row = 0; row < size; ++row)
        std::cout << column[row] << std::endl;
}

int main() {
    Equation equation = ReadEquation();
    Column solution = SolveEquation(equation);
    PrintColumn(solution);
    return 0;
}
