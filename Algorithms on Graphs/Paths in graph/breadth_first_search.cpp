//Input Format.A graph is given in the standard format.The next line contains two vertices 𝑢and 𝑣.
//Constraints. 2 ≤ 𝑛 ≤ 10^5, 0 ≤ 𝑚 ≤ 10^5, 𝑢 ̸ = 𝑣, 1 ≤ 𝑢, 𝑣 ≤ 𝑛.
//Output Format.Output the minimum number of edges in a path from 𝑢 to 𝑣, or −1 if there is no path.

#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

int distance(vector<vector<int> >& adj, int s, int t) {
    vector<int> dist(adj.size(), -1);
    dist[s] = 0;
    queue<int> q;
    q.push(s);
    int u;
    while (!q.empty())
    {
        u = q.front();
        q.pop();
        for (int& v : adj[u])
        {
            if (dist[v] == -1)
            {
                q.push(v);
                dist[v] = dist[u] + 1;
            }
        }
    }

    return dist[t];
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
    int s, t;
    std::cin >> s >> t;
    s--, t--;
    std::cout << distance(adj, s, t);
}