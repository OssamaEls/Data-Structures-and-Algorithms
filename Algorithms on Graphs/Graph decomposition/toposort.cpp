//Input Format.A graph is given in the standard format.
//Constraints. 1 ≤ 𝑛 ≤ 10^5, 0 ≤ 𝑚 ≤ 10^5. The given graph is guaranteed to be acyclic.
//Output Format.Output any topological ordering of its vertices. (Many DAGs have more than just one
//topological ordering.You may output any of them.)

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



vector<size_t> toposort(vector<vector<int> > adj) {
    vector<int> post(adj.size());
    dfs(adj, post);
    vector<size_t> order = sort_indexes(post);

    return order;
}

int main() {
    size_t n, m;
    std::cin >> n >> m;
    vector<vector<int> > adj(n, vector<int>());
    for (size_t i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        adj[x - 1].push_back(y - 1);
    }
    vector<size_t> order = toposort(adj);
    for (size_t i = 0; i < order.size(); i++) {
        std::cout << order[i] + 1 << " ";
    }
}
