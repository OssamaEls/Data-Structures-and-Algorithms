//Input Format.The first line contains two integers 𝑛and 𝑚 — the number of verticesand the number of
//edges of the graph.The vertices are numbered from 1 through 𝑛.The next line contains a string of
//length 𝑛 consisting only of letters 𝑅, 𝐺and 𝐵 representing the current color assignments.For each
//position 𝑖(1 - based) in the string, if it is 𝑅, then the vertex 𝑖 is colored red; if it’s 𝐺, the vertex 𝑖 is
//colored green; if it’s 𝐵, the vertex 𝑖 is colored blue.These are the current color assignments, and each
//of them must be changed.Each of the next 𝑚 lines contains two integers 𝑢and 𝑣 — vertices 𝑢and
//𝑣 are connected by an edge(it is possible that 𝑢 = 𝑣).
//
//Constraints. 1 ≤ 𝑛 ≤ 1 000; 0 ≤ 𝑚 ≤ 20 000; 1 ≤ 𝑢, 𝑣 ≤ 𝑛.
//
//Output Format.If it is impossible to reassign the students to the dates of exams in such a way that no two
//friends are going to pass the exam the same day, and each student’s assigned date has changed, output
//just one word “Impossible”(without quotes).Otherwise, output one string consisting of 𝑛 characters
//𝑅, 𝐺and 𝐵 representing the new coloring of the vertices.Note that the color of each vertex must be
//different from the initial color of this vertex.The vertices connected by an edge must have different
//colors.

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <set>
#include <string>
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
using namespace std;

/*
  Arguments:
    * `n` - the number of vertices.
    * `edges` - list of edges, each edge is a pair (u, v), 1 <= u, v <= n.
    * `colors` - string consisting of `n` characters, each belonging to the set {'R', 'G', 'B'}.
  Return value:
    * If there exists a proper recoloring, return value is a string containing new colors, similar to the `colors` argument.
    * Otherwise, return value is an empty string.
*/
//string assign_new_colors(int n, vector<pair<int, int>> edges, string colors) {
//    // Insert your code here.
//    if (n % 3 == 0) {
//        string new_colors;
//        for (int i = 0; i < n; i++) {
//            new_colors.push_back("RGB"[i % 3]);
//        }
//        return new_colors;
//    }
//    else {
//        return "";
//    }
//}

TwoSatisfiability builTwoSat(vector<pair<int, int>>& edges, string& colors)
{
    const int num_vars = 3 * colors.size();
    const int num_clauses = 3 * colors.size() + 3 * edges.size();
    TwoSatisfiability twoSat(num_vars, num_clauses);


    int idx = 0;
    for (int i = 0; i < colors.size(); i++)
    {
        switch (colors[i])
        {
        case 'R':
            twoSat.clauses[idx].firstVar = 3 * i;
            twoSat.clauses[idx].secondVar = 3 * i;
            twoSat.clauses[idx + 1].firstVar = 3 * i + 1 + num_vars;
            twoSat.clauses[idx + 1].secondVar = 3 * i + 2 + num_vars;
            twoSat.clauses[idx + 2].firstVar = 3 * i + 1;
            twoSat.clauses[idx + 2].secondVar = 3 * i + 2;
            idx += 3;
            continue;
        case 'G':
            twoSat.clauses[idx].firstVar = 3 * i + 1;
            twoSat.clauses[idx].secondVar = 3 * i + 1;
            twoSat.clauses[idx + 1].firstVar = 3 * i + num_vars;
            twoSat.clauses[idx + 1].secondVar = 3 * i + 2 + num_vars;
            twoSat.clauses[idx + 2].firstVar = 3 * i;
            twoSat.clauses[idx + 2].secondVar = 3 * i + 2;
            idx += 3;
            continue;
        case 'B':
            twoSat.clauses[idx].firstVar = 3 * i + 2;
            twoSat.clauses[idx].secondVar = 3 * i + 2;
            twoSat.clauses[idx + 1].firstVar = 3 * i + num_vars;
            twoSat.clauses[idx + 1].secondVar = 3 * i + 1 + num_vars;
            twoSat.clauses[idx + 2].firstVar = 3 * i;
            twoSat.clauses[idx + 2].secondVar = 3 * i + 1;
            idx += 3;
            continue;
        }
    }

    for (int i = 0; i < edges.size(); i++)
    {
        int u = edges[i].first - 1;
        int v = edges[i].second - 1;

        for (int j = 0; j <= 2; j++)
        {
            twoSat.clauses[idx].firstVar = 3 * u + j;
            twoSat.clauses[idx].secondVar = 3 * v + j;
            ++idx;
        }
    }

    return twoSat;
}

void print_answer(vector<pair<int, int>>& edges, string& colors)
{
    TwoSatisfiability twoSat = builTwoSat(edges, colors);
    const int num_vars = twoSat.numVars;
    vector<int> result(num_vars, -1);
    if (twoSat.isSatisfiable(result)) {
        for (int i = 0; i < num_vars; ++i) {
            if (!result[i]) {
                cout << "RGB"[i % 3];
            }
        }
    }
    else {
        cout << "Impossible" << endl;
    }
}


int main() {
    int n, m;
    cin >> n >> m;
    string colors;
    cin >> colors;
    vector<pair<int, int> > edges;
    bool maybe_possible = true;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        if (u != v)
            edges.push_back(make_pair(u, v));
        else
            maybe_possible = false;
    }

    if (maybe_possible)
        print_answer(edges, colors);
    else
        cout << "Impossible";

    return 0;
}