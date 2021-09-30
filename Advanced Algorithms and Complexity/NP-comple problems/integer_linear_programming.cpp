//Input Format.The first line contains two integers 𝑛and 𝑚 — the number of inequalitiesand the number
//of variables.The next 𝑛 lines contain the description of 𝑛×𝑚 matrix 𝐴 with coefficients of inequalities
//(each of the 𝑛 lines contains 𝑚 integers, and at most 3 of them are non - zero), and the last line contains
//the description of the vector 𝑏(𝑛 integers) for the system of inequalities 𝐴𝑥 ≤ 𝑏.You need to determine
//whether there exists a binary vector 𝑥 satisfying all those inequalities.
//
//Constraints. 1 ≤ 𝑛, 𝑚 ≤ 500; −100 ≤ 𝐴𝑖𝑗 ≤ 100; −1 000 000 ≤ 𝑏𝑖 ≤ 1 000 000.
//
//Output Format.You need to output a boolean formula in the CNF form in a specific format.If it is
//possible to accept some of the proposals and decline all the others while satisfying all the constraints,
//the formula must be satisfiable.Otherwise, the formula must be unsatisfiable.The number of variables
//in the formula must not exceed 3000, and the number of clauses must not exceed 5000.
//On the first line, output integers 𝐶and 𝑉 — the number of clauses in the formulaand the number of
//variables respectively.On each of the next 𝐶 lines, output a description of a single clause.Each clause
//has a form(𝑥4 𝑂𝑅 𝑥1 𝑂𝑅 𝑥8).For a clause with 𝑘 terms(in the example, 𝑘 = 3 for 𝑥4, 𝑥1and 𝑥8), output
//first those 𝑘 termsand then number 0 in the end(in the example, output “4 − 1 8 0”).Output each
//term as integer number.Output variables 𝑥1, 𝑥2, . . ., 𝑥𝑉 as numbers 1, 2, . . ., 𝑉 respectively.Output
//negations of variables 𝑥1, 𝑥2, . . ., 𝑥𝑉 as numbers −1, −2, . . ., −𝑉 respectively.Each number other than
//the last one in each line must be a non - zero integer between −𝑉 and 𝑉 where 𝑉 is the total number
//of variables specified in the first line of the output.Ensure that 1 ≤ 𝐶 ≤ 5000 and 1 ≤ 𝑉 ≤ 3000.

#include <ios>
#include <iostream>
#include <vector>


using namespace std;

struct ConvertILPToSat {
    vector< vector<int> > A;
    vector<int> b;

    ConvertILPToSat(int n, int m) : A(n, vector<int>(m)), b(n)
    {}

    void printEquisatisfiableSatFormula() {
        vector<vector<int>> clauses;

        for (int i = 0; i < A.size(); i++)
        {
            vector<int> idx_non_zero;
            for (int j = 0; j < A[i].size(); j++)
            {
                if (A[i][j] != 0)
                    idx_non_zero.push_back(j);
            }

            int rhs = b[i];

            if (idx_non_zero.size() == 1)
            {
                if (A[i][idx_non_zero[0]] > rhs)
                    clauses.push_back({ -idx_non_zero[0] - 1 });
                if (b[i] < 0)
                    clauses.push_back({ idx_non_zero[0] + 1 });
            }
            else if (idx_non_zero.size() == 2)
            {
                if (A[i][idx_non_zero[0]] > rhs)
                    clauses.push_back({ -idx_non_zero[0] - 1,  idx_non_zero[1] + 1 });
                if (A[i][idx_non_zero[1]] > rhs)
                    clauses.push_back({ idx_non_zero[0] + 1 , -idx_non_zero[1] - 1 });
                if (A[i][idx_non_zero[0]] + A[i][idx_non_zero[1]] > rhs)
                    clauses.push_back({ -idx_non_zero[0] - 1, -idx_non_zero[1] - 1 });
                if (rhs < 0)
                    clauses.push_back({ idx_non_zero[0] + 1, idx_non_zero[1] + 1 });
            }
            else if (idx_non_zero.size() == 3)
            {
                if (A[i][idx_non_zero[0]] > rhs)
                    clauses.push_back({ -idx_non_zero[0] - 1,  idx_non_zero[1] + 1 , idx_non_zero[2] + 1 });
                if (A[i][idx_non_zero[1]] > rhs)
                    clauses.push_back({ idx_non_zero[0] + 1, -idx_non_zero[1] - 1, idx_non_zero[2] + 1 });
                if (A[i][idx_non_zero[2]] > rhs)
                    clauses.push_back({ idx_non_zero[0] + 1, idx_non_zero[1] + 1, -idx_non_zero[2] - 1 });

                if (A[i][idx_non_zero[0]] + A[i][idx_non_zero[1]] > rhs)
                    clauses.push_back({ -idx_non_zero[0] - 1, -idx_non_zero[1] - 1, idx_non_zero[2] + 1 });
                if (A[i][idx_non_zero[0]] + A[i][idx_non_zero[2]] > rhs)
                    clauses.push_back({ -idx_non_zero[0] - 1, idx_non_zero[1] + 1, -idx_non_zero[2] - 1 });
                if (A[i][idx_non_zero[1]] + A[i][idx_non_zero[2]] > rhs)
                    clauses.push_back({ idx_non_zero[0] + 1, -idx_non_zero[1] - 1, -idx_non_zero[2] - 1 });

                if (A[i][idx_non_zero[0]] + A[i][idx_non_zero[1]] + A[i][idx_non_zero[2]] > rhs)
                    clauses.push_back({ -idx_non_zero[0] - 1, -idx_non_zero[1] - 1, -idx_non_zero[2] - 1 });

                if (rhs < 0)
                    clauses.push_back({ idx_non_zero[0] + 1, idx_non_zero[1] + 1, idx_non_zero[2] + 1 });
            }
            else
            {
                if (rhs < 0)
                {
                    clauses.push_back({ 1 });
                    clauses.push_back({ -1 });
                }
            }
        }

        int max_var = 0;
        for (int i = 0; i < clauses.size(); i++)
        {
            for (int j = 0; j < clauses[i].size(); j++)
            {
                if (max_var < abs(clauses[i][j])) max_var = abs(clauses[i][j]);
            }
        }

        int num_clauses = clauses.size();
        int num_variables = max_var;

        if (num_clauses > 0) {
            cout << num_clauses << ' ' << num_variables << '\n';

            for (int clause_idx = 0; clause_idx < num_clauses; clause_idx++)
            {
                for (int var_idx = 0; var_idx < clauses[clause_idx].size(); var_idx++)
                {
                    cout << clauses[clause_idx][var_idx] << ' ';
                }
                cout << "0" << '\n';
            }
        }
        else {
            cout << "1 1" << endl;
            cout << "1 -1 0" << endl;
        }


    }



};

int main() {
    ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    ConvertILPToSat converter(n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> converter.A[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        cin >> converter.b[i];
    }

    converter.printEquisatisfiableSatFormula();

    return 0;
}