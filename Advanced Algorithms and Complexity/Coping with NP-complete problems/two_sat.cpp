//Input Format.The input represents a 2 - CNF formula.The first line contains two integers 𝑉 and 𝐶 —
//the number of variables and the number of clauses respectively.Each of the next 𝐶 lines contains two
//non - zero integers 𝑖 and 𝑗 representing a clause in the CNF form.If 𝑖 > 0, it represents 𝑥𝑖, otherwise
//if 𝑖 < 0, it represents 𝑥−𝑖, and the same goes for 𝑗.For example, a line “2 3” represents a clause
//(𝑥2 𝑂𝑅 𝑥3), line “1 - 4” represents(𝑥1 𝑂𝑅 𝑥4), line “ - 1 - 3” represents(𝑥1 𝑂𝑅 𝑥3), and line “0 2”
//cannot happen, because 𝑖and 𝑗 must be non - zero.
//
//Constraints. 1 ≤ 𝑉, 𝐶 ≤ 1 000 000; −𝑉 ≤ 𝑖, 𝑗 ≤ 𝑉; 𝑖, 𝑗 ̸ = 0.
//
//Output Format.If the 2 - CNF formula in the input is unsatisfiable, output just the word “UNSATISFIABLE”(without quotes, using capital letters).If the 2 - CNF formula in the input is satisfiable, output
//the word “SATISFIABLE”(without quotes, using capital letters) on the first lineand the corresponding
//assignment of variables on the second line.For each 𝑥𝑖 in order from 𝑥1 to 𝑥𝑉, output 𝑖 if 𝑥𝑖 = 1 or
//−𝑖 if 𝑥𝑖 = 0. For example, if a formula is satisfied by assignment 𝑥1 = 0, 𝑥2 = 1, 𝑥3 = 0,
//output “ - 1 2 - 3” on the second line(without quotes).If there are several possible assignments satisfying the input formula,
//output any one of them.

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <set>
using namespace std;


template <typename T>
vector<size_t> sort_indexes(const vector<T>& v) {

    // initialize original index locations
    vector<size_t> idx(v.size());
    iota(idx.begin(), idx.end(), 0);

    // sort indexes based on comparing values in v
    // using std::stable_sort instead of std::sort
    // to avoid unnecessary index re-orderings
    // when v contains elements of equal values 
    stable_sort(idx.begin(), idx.end(),
        [&v](size_t i1, size_t i2) {return v[i1] > v[i2]; });

    return idx;
}

void postvisit(int x, int& clock, vector<int>& post)
{
    post[x] = clock;
    ++clock;
}

void explore(vector<vector<int> >& adj, int x, vector<bool>& visited, vector<int>& post)
{
    static int clock = 1;
    visited[x] = true;
    for (size_t i = 0; i < adj[x].size(); i++)
    {
        if (!visited[adj[x][i]])
            explore(adj, adj[x][i], visited, post);
    }
    postvisit(x, clock, post);
}

void explore_with_cc(vector<vector<int> >& adj, int x, vector<bool>& visited, vector<int>& cc_id, int& cc_number)
{
    visited[x] = true;
    cc_id[x] = cc_number;
    for (size_t i = 0; i < adj[x].size(); i++)
    {
        if (!visited[adj[x][i]])
            explore_with_cc(adj, adj[x][i], visited, cc_id, cc_number);
    }
}

void dfs(vector<vector<int> >& adj, vector<int>& post) {
    vector<bool> visited(adj.size(), false);
    for (size_t i = 0; i < adj.size(); i++)
    {
        if (!visited[i])
        {
            explore(adj, i, visited, post);
        }
    }
}

struct Clause {
    int firstVar;
    int secondVar;
};

struct TwoSatisfiability {
    int numVars;
    vector<Clause> clauses;
    vector<vector<int>> adj;
    vector<vector<int>> adj_rev;

    TwoSatisfiability(int n, int m) :
        numVars(n),
        clauses(m),
        adj(2 * n, vector<int>()),
        adj_rev(2 * n, vector<int>())
    {  }

    void buildGraph()
    {
        for (int i = 0; i < clauses.size(); i++)
        {
            int first_var = clauses[i].firstVar;
            int second_var = clauses[i].secondVar;
            int first_var_neg = first_var >= numVars ? first_var - numVars : first_var + numVars;
            int second_var_neg = second_var >= numVars ? second_var - numVars : second_var + numVars;

            adj[first_var_neg].push_back(second_var);
            adj_rev[second_var].push_back(first_var_neg);

            adj[second_var_neg].push_back(first_var);
            adj_rev[first_var].push_back(second_var_neg);
        }

        // cout << "graph constructed\n";
    }



    bool isSatisfiable(vector<int>& result) {

        buildGraph();

        vector<int> post(adj_rev.size());


        dfs(adj_rev, post);
        vector<size_t> order = sort_indexes(post);

        // cout << "dfs of reverse graph completed\n";

        vector<bool> visited(adj.size(), false);
        vector<int> connected_component_id(2 * numVars);
        int cc_id = 0;
        for (auto v : order)
        {
            if (!visited[v])
            {
                explore_with_cc(adj, v, visited, connected_component_id, cc_id);
                ++cc_id;
            }
        }

        for (int i = 0; i < numVars; i++)
        {
            if (connected_component_id[i] == connected_component_id[i + numVars])
                return false;
        }

        // cout << "no opposite variables in same scc\n";

        vector<set<int>> scc_list(cc_id);

        for (auto v : order)
        {
            scc_list[connected_component_id[v]].insert(v);
        }

        // cout << "defined list of scc\n";

        vector<int> scc_assignment(cc_id, -1);

        for (int i = 0; i < scc_list.size(); i++)
        {
            if (scc_assignment[i] == -1)
            {
                scc_assignment[i] = 1;
                for (auto it = scc_list[i].begin(); it != scc_list[i].end(); it++)
                {
                    int negated = *it < numVars ? *it + numVars : *it - numVars;
                    if (scc_assignment[connected_component_id[negated]] == -1)
                    {
                        scc_assignment[connected_component_id[negated]] = 0;
                    }
                }
            }
        }

        // cout << "assignment done for all scc\n";

        for (int i = 0; i < scc_list.size(); i++)
        {
            int assigned_val = scc_assignment[i];
            for (auto it = scc_list[i].begin(); it != scc_list[i].end(); it++)
            {
                //if (*it < numVars && result[*it] == -1)
                //{
                //    if (assigned_val == 1)
                //        result[*it] = 1;
                //    else
                //        result[*it] = 0;
                //}
                //else if (*it >= numVars && result[*it - numVars] == -1)
                //{
                //    if (assigned_val == 1)
                //        result[*it - numVars] = 0;
                //    else
                //        result[*it - numVars] = 1;
                //}
                if (*it < numVars && result[*it] == -1)
                {
                    result[*it] = assigned_val;
                }
                else if (*it >= numVars && result[*it - numVars] == -1)
                {
                    result[*it - numVars] = !assigned_val;
                }
            }
        }

        return true;
    }
};

int main() {
    ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    TwoSatisfiability twoSat(n, m);
    for (int i = 0; i < m; ++i) {
        int var1, var2;
        cin >> var1 >> var2;
        if (var1 > 0)
            twoSat.clauses[i].firstVar = var1 + n - 1;
        else
            twoSat.clauses[i].firstVar = -var1 - 1;

        if (var2 > 0)
            twoSat.clauses[i].secondVar = var2 + n - 1;
        else
            twoSat.clauses[i].secondVar = -var2 - 1;
    }

    vector<int> result(n, -1);
    if (twoSat.isSatisfiable(result)) {
        cout << "SATISFIABLE" << endl;
        for (int i = 1; i <= n; ++i) {
            if (result[i - 1]) {
                cout << -i;
            }
            else {
                cout << i;
            }
            if (i < n) {
                cout << " ";
            }
            else {
                cout << endl;
            }
        }
    }
    else {
        cout << "UNSATISFIABLE" << endl;
    }

    return 0;
}
