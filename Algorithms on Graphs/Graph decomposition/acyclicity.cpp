//Input Format.A graph is given in the standard format.
//Constraints. 1 ≤ 𝑛 ≤ 10^3, 0 ≤ 𝑚 ≤ 10^3.
//Output Format.Output 1 if the graph contains a cycle and 0 otherwise.

#include <iostream>
#include <vector>

using std::vector;
using std::pair;



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

int acyclic(vector<vector<int> >& adj) {
    vector<int> post(adj.size());
    dfs(adj, post);

    for (size_t i = 0; i < adj.size(); i++)
    {
        for (size_t j = 0; j < adj[i].size(); j++)
        {
            if (post[i] < post[adj[i][j]]) return true;
        }
    }

    return false;
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
    std::cout << acyclic(adj);
}
