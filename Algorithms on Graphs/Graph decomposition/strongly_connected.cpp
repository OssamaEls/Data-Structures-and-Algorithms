//Input Format.A graph is given in the standard format.
//Constraints. 1 ≤ 𝑛 ≤ 10^4, 0 ≤ 𝑚 ≤ 10^4.
//Output Format.Output the number of strongly connected components.

#include <algorithm>
#include <iostream>
#include <numeric>      // std::iota
#include <utility>
#include <vector>

using std::vector;
using std::pair;

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
        if (!visited[adj[x][i]]) explore(adj, adj[x][i], visited, post);
    }
    postvisit(x, clock, post);
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


int number_of_strongly_connected_components(vector<vector<int> >& adj, vector<vector<int> >& adj_rev) {
    vector<int> post(adj_rev.size());
    dfs(adj_rev, post);
    vector<size_t> order = sort_indexes(post);

    vector<bool> visited(adj.size(), false);
    int result = 0;
    for (auto v : order)
    {
        if (!visited[v])
        {
            explore(adj, v, visited, post);
            ++result;
        }
    }

    return result;
}

int main() {
    size_t n, m;
    std::cin >> n >> m;
    vector<vector<int> > adj(n, vector<int>());
    vector<vector<int> > adj_rev(n, vector<int>());
    for (size_t i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        adj[x - 1].push_back(y - 1);
        adj_rev[y - 1].push_back(x - 1);
    }
    std::cout << number_of_strongly_connected_components(adj, adj_rev);
}