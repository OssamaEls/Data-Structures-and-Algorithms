//Input Format.The first line contains two integers 𝑛and 𝑚 — the number of roomsand the number of
//corridors connecting the rooms respectively.Each of the next 𝑚 lines contains two integers 𝑢and 𝑣
//describing the corridor going from room 𝑢 to room 𝑣.The corridors are two - way, that is, you can go
//both from 𝑢 to 𝑣and from 𝑣 to 𝑢.No two corridors have a common part, that is, every corridor only
//allows you to go from one room to one other room.Of course, no corridor connects a room to itself.
//Note that a corridor from 𝑢 to 𝑣 can be listed several times, and there can be listed both a corridor
//from 𝑢 to 𝑣and a corridor from 𝑣 to 𝑢.
//
//Constraints. 1 ≤ 𝑛 ≤ 30; 0 ≤ 𝑚 ≤ 𝑛(𝑛2−1); 1 ≤ 𝑢, 𝑣 ≤ 𝑛.
//
//Output Format.You need to output a boolean formula in the CNF form in a specific format.If it is
//possible to go through all the roomsand visit each one exactly once to clean it, the formula must be
//satisfiable.Otherwise, the formula must be unsatisfiable.The sum of the numbers of variables used in
//each clause of the formula must not exceed 120 000.
//On the first line, output integers 𝐶and 𝑉 — the number of clauses in the formulaand the number of
//variables respectively.On each of the next 𝐶 lines, output a description of a single clause.Each clause
//has a form(𝑥4 𝑂𝑅 𝑥1 𝑂𝑅 𝑥8).For a clause with 𝑘 terms(in the example, 𝑘 = 3 for 𝑥4, 𝑥1and 𝑥8), output
//first those 𝑘 termsand then number 0 in the end(in the example, output “4 − 1 8 0”).Output each
//term as integer number.Output variables 𝑥1, 𝑥2, . . ., 𝑥𝑉 as numbers 1, 2, . . ., 𝑉 respectively.Output
//negations of variables 𝑥1, 𝑥2, . . ., 𝑥𝑉 as numbers −1, −2, . . ., −𝑉 respectively.Each number other than
//the last one in each line must be a non - zero integer between −𝑉 and 𝑉 where 𝑉 is the total number
//of variables specified in the first line of the output.Ensure that the total number of non - zero integers
//in the 𝐶 lines describing the clauses is at most 120 000.

#include <ios>
#include <iostream>
#include <vector>
#include <set>

using namespace std;



struct ConvertHampathToSat {
    int numVertices;
    set<set<int>> edges;

    ConvertHampathToSat(int n) : numVertices(n) {  }

    void printEquisatisfiableSatFormula() {
        vector<vector<int>> clauses;

        // Each vertex belongs to a path
        for (int i = 1; i <= numVertices; i++)
        {
            clauses.push_back(vector<int>(numVertices));
            for (int j = 1; j <= numVertices; j++)
            {
                clauses[i - 1][j - 1] = (i - 1) * numVertices + j;
            }
        }


        // Each vertex appears just once in a path
        for (int i = 1; i <= numVertices; i++)
        {
            for (int j = 1; j < numVertices; j++)
            {
                for (int j_p = j + 1; j_p <= numVertices; j_p++)
                {
                    int neg_i_j = -((i - 1) * numVertices + j);
                    int neg_i_jp = -((i - 1) * numVertices + j_p);
                    clauses.push_back({ neg_i_j, neg_i_jp });
                }
            }
        }

        // Each position in a path is occupied by some vertex
        for (int j = 1; j <= numVertices; j++)
        {
            clauses.push_back({});
            int last = clauses.size() - 1;
            for (int i = 1; i <= numVertices; i++)
            {
                clauses[last].push_back((i - 1) * numVertices + j);
            }
        }

        // No two vertices occupy the same position of a path
        for (int j = 1; j <= numVertices; j++)
        {
            for (int i = 1; i < numVertices; i++)
            {
                for (int i_p = i + 1; i_p <= numVertices; i_p++)
                {
                    int neg_i_j = -((i - 1) * numVertices + j);
                    int neg_ip_j = -((i_p - 1) * numVertices + j);
                    clauses.push_back({ neg_i_j, neg_ip_j });
                }
            }
        }

        // Two successive vertices on a path must be connected by an edge. (In other words, if there is no edge
        // {𝑖, 𝑗} in 𝐸, then for any 𝑘, it cannot be the case that both 𝑥𝑖𝑘 and 𝑥𝑗(𝑘 + 1) are True.)
        for (int i = 1; i < numVertices; i++)
        {
            for (int j = i + 1; j <= numVertices; j++)
            {
                if (edges.find({ i,j }) == edges.end())
                {
                    for (int k = 1; k < numVertices; k++)
                    {
                        int neg_i_k = -((i - 1) * numVertices + k);
                        int neg_j_kp1 = -((j - 1) * numVertices + k + 1);
                        clauses.push_back({ neg_i_k, neg_j_kp1 });

                        int neg_i_kp1 = -((i - 1) * numVertices + k + 1);
                        int neg_j_k = -((j - 1) * numVertices + k);
                        clauses.push_back({ neg_i_kp1, neg_j_k });
                    }
                }
            }
        }

        int num_clauses = clauses.size();
        int num_variables = numVertices * numVertices;

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
};

int main() {
    ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    ConvertHampathToSat converter(n);
    for (int i = 0; i < m; ++i) {
        set<int> edge;
        int from; int to;
        cin >> from >> to;
        edge.insert(from);
        edge.insert(to);
        converter.edges.insert(edge);
    }

    converter.printEquisatisfiableSatFormula();

    return 0;
}