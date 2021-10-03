//Input Format.The first line of the input contains integers 𝑛and 𝑚 — the number of verticesand edges in
//the graph.The vertices are numbered from 1 through 𝑛.Each of the next 𝑚 lines contains two integers
//𝑢 and 𝑣 — the numbers of vertices connected by an edge.It is guaranteed that a vertex cannot be
//connected to itself by an edge.
//
//Constraints. 2 ≤ 𝑛 ≤ 500; 1 ≤ 𝑚 ≤ 1000; 1 ≤ 𝑢, 𝑣 ≤ 𝑛; 𝑢 ̸= 𝑣.
//
//Output Format.You need to output a boolean formula in the conjunctive normal form(CNF) in a specific
//format.If it is possible to color the vertices of the input graph in 3 colors such that any two vertices
//connected by an edge are of different colors, the formula must be satisfiable.Otherwise, the formula
//must be unsatisfiable.The number of variables in the formula must be at least 1 and at most 3000.
//The number of clauses must be at least 1 and at most 5000.
//On the first line, output integers 𝐶and 𝑉 — the number of clauses in the formulaand the number of
//variables respectively.On each of the next 𝐶 lines, output a description of a single clause.Each clause
//has a form(𝑥4 𝑂𝑅 𝑥1 𝑂𝑅 𝑥8).For a clause with 𝑘 terms(in the example, 𝑘 = 3 for 𝑥4, 𝑥1and 𝑥8), output
//first those 𝑘 termsand then number 0 in the end(in the example, output “4 − 1 8 0”).Output each
//term as integer number.Output variables 𝑥1, 𝑥2, . . ., 𝑥𝑉 as numbers 1, 2, . . ., 𝑉 respectively.Output negations of variables 𝑥1, 𝑥2, . . ., 𝑥𝑉 as numbers −1, −2, . . ., −𝑉 respectively.Each number other than
//the last one in each line must be a non - zero integer between −𝑉 and 𝑉 where 𝑉 is the total number
//of variables specified in the first line of the output.Ensure that 1 ≤ 𝐶 ≤ 5000 and 1 ≤ 𝑉 ≤ 3000.
//See the examples below for further clarification of the output format.
//If there are many different formulas that satisfy the requirements above, you can output any one of
//them.

#include <ios>
#include <iostream>
#include <vector>

using namespace std;

struct Edge {
    int from;
    int to;
};

struct ConvertGSMNetworkProblemToSat {
    int numVertices;
    vector<Edge> edges;

    ConvertGSMNetworkProblemToSat(int n, int m) :
        numVertices(n),
        edges(m)
    {  }

    void printEquisatisfiableSatFormula() {

        int num_clauses = 4 * numVertices + 3 * edges.size();
        int num_variables = 6 * numVertices;

        cout << num_clauses << ' ' << num_variables << '\n';

        for (int i = 0; i < numVertices; i++)
        {
            cout << 3 * i + 1 << ' ' << 3 * i + 2 << ' ' << 3 * i + 3 << " 0\n";
        }

        for (int i = 0; i < numVertices; i++)
        {
            cout << -(3 * i + 1) << ' ' << -(3 * i + 2) << " 0\n";
            cout << -(3 * i + 1) << ' ' << -(3 * i + 3) << " 0\n";
            cout << -(3 * i + 2) << ' ' << -(3 * i + 3) << " 0\n";
        }

        for (int j = 0; j < edges.size(); j++)
        {
            int from = edges[j].from;
            int to = edges[j].to;
			cout << -(3 * (from - 1) + 1) << ' ' << -(3 * (to - 1) + 1) << " 0\n";
			cout << -(3 * (from - 1) + 2) << ' ' << -(3 * (to - 1) + 2) << " 0\n";
			cout << -(3 * (from - 1) + 3) << ' ' << -(3 * (to - 1) + 3) << " 0\n";
        }
    }
};

int main() {
    ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    ConvertGSMNetworkProblemToSat converter(n, m);
    for (int i = 0; i < m; ++i) {
        cin >> converter.edges[i].from >> converter.edges[i].to;
    }

    converter.printEquisatisfiableSatFormula();

    return 0;
}