//Input Format.An undirected graph with 𝑛 verticesand 𝑚 edges.The next line contains two vertices 𝑢
//and 𝑣 of the graph.
//Constraints. 2 ≤ 𝑛 ≤ 10^3; 1 ≤ 𝑚 ≤ 10^3; 1 ≤ 𝑢, 𝑣 ≤ 𝑛; 𝑢 ̸ = 𝑣.
//Output Format.Output 1 if there is a path between 𝑢and 𝑣 and 0 otherwise.

#include <iostream>
#include <vector>

using std::vector;
using std::pair;


void explore(vector<vector<int> >& adj, int x, vector<bool>& visited)
{
    visited[x] = true;
    for (size_t i = 0; i < adj[x].size(); i++)
    {
        if (!visited[adj[x][i]]) explore(adj, adj[x][i], visited);
    }
}

int reach(vector<vector<int> >& adj, int x, int y, vector<bool>& visited) {
    explore(adj, x, visited);
    return visited[y];
}

int main() {
    size_t n, m;
    std::cin >> n >> m;
    vector<vector<int> > adj(n, vector<int>());
    vector<bool> visited(n, false);
    for (size_t i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        adj[x - 1].push_back(y - 1);
        adj[y - 1].push_back(x - 1);
    }
    int x, y;
    std::cin >> x >> y;
    std::cout << reach(adj, x - 1, y - 1, visited);
}