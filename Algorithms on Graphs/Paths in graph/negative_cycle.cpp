//Input Format.A graph is given in the standard format.
//Constraints. 1 ≤ 𝑛 ≤ 10^3, 0 ≤ 𝑚 ≤ 10^4, edge weights are integers of absolute value at most 10^3.
//Output Format.Output 1 if the graph contains a cycle of negative weight and 0 otherwise.

#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

struct MyDist
{
    long long distance = 0;
    bool infinite = true;
};

bool negative_cycle(vector<vector<int> >& adj, vector<vector<int> >& cost) {
    int n = adj.size();
    int first_non_visited = 0;
    vector<vector<int>> nodes_conn;
    vector<MyDist> dist(n);
    vector<bool> visited(n, false);
    int idx = 0;
    while (first_non_visited < n)
    {
        visited[first_non_visited] = true;
        dist[first_non_visited] = { 0, false };
        nodes_conn.push_back({ first_non_visited });
        queue<int> q;
        q.push(first_non_visited);
        int u;
        while (!q.empty())
        {
            u = q.front();
            q.pop();
            for (size_t j = 0; j < adj[u].size(); j++)
            {
                if (!visited[adj[u][j]])
                {
                    visited[adj[u][j]] = true;
                    q.push(adj[u][j]);
                    nodes_conn[idx].push_back(adj[u][j]);
                }
            }
        }
        while (visited[first_non_visited])
        {
            ++first_non_visited;
            if (first_non_visited > visited.size() - 1) break;
        }
        ++idx;
    }

    bool a_change;
    int u;
    for (size_t i = 0; i < n; i++)
    {
        a_change = false;
        for (size_t j = 0; j < nodes_conn.size(); j++)
        {
            for (size_t m = 0; m < nodes_conn[j].size(); m++)
            {
                u = nodes_conn[j][m];
                for (size_t p = 0; p < adj[u].size(); p++)
                {
                    if (
                        (dist[adj[u][p]].infinite && !dist[u].infinite)
                        ||
                        ((!dist[adj[u][p]].infinite && !dist[u].infinite)
                            && (dist[adj[u][p]].distance > dist[u].distance + cost[u][p]))
                        )
                    {
                        dist[adj[u][p]] = { dist[u].distance + cost[u][p], false };
                        a_change = true;
                    }
                }
            }
        }
    }


    return a_change;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    vector<vector<int> > adj(n, vector<int>());
    vector<vector<int> > cost(n, vector<int>());
    for (int i = 0; i < m; i++) {
        int x, y, w;
        std::cin >> x >> y >> w;
        adj[x - 1].push_back(y - 1);
        cost[x - 1].push_back(w);
    }
    std::cout << negative_cycle(adj, cost);
}
