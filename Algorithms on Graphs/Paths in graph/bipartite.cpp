//Input Format.A graph is given in the standard format.
//Constraints. 1 ≤ 𝑛 ≤ 10^5, 0 ≤ 𝑚 ≤ 10^5.
//Output Format.Output 1 if the graph is bipartite and 0 otherwise.

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using std::vector;
using std::queue;


bool bipartite(vector<vector<int> >& adj) {
    //write your code here
    vector<bool> visited(adj.size(), false);
    vector<int> colors(adj.size(), -1);

    int first_non_visited = 0;
    while (first_non_visited < visited.size())
    {
        visited[first_non_visited] = true;
        colors[first_non_visited] = 0;
        queue<int> q;
        q.push(first_non_visited);
        int u;
        while (!q.empty())
        {
            u = q.front();
            q.pop();
            if (!adj[u].empty())
            {
                for (int& v : adj[u])
                {
                    if (!visited[v])
                    {
                        visited[v] = true;
                        q.push(v);
                        colors[v] = colors[u] == 0 ? 1 : 0;
                    }
                    else
                    {
                        if (colors[v] == colors[u]) return false;
                    }
                }
            }
        }
        while (visited[first_non_visited])
        {
            ++first_non_visited;
            if (first_non_visited > visited.size() - 1) break;
        }
    }
    return true;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    vector<vector<int> > adj(n, vector<int>());
    for (int i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        adj[x - 1].push_back(y - 1);
        adj[y - 1].push_back(x - 1);
    }
    std::cout << bipartite(adj);
}
