//Input Format.A graph is given in the standard format.
//Constraints. 1 ≤ 𝑛 ≤ 10^3, 0 ≤ 𝑚 ≤ 10^4, 1 ≤ 𝑠 ≤ 𝑛, edge weights are integers of absolute value at most 10^9.
//Output Format.For all vertices 𝑖 from 1 to 𝑛 output the following on a separate line :
//∙ “ * ”, if there is no path from 𝑠 to 𝑢;
//∙ “ - ”, if there is a path from 𝑠 to 𝑢, but there is no shortest path from 𝑠 to 𝑢 (that is, the distance
//    from 𝑠 to 𝑢 is −∞);
//∙ the length of a shortest path otherwise.

#include <iostream>
#include <limits>
#include <vector>
#include <queue>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;

void shortest_paths(vector<vector<int> >& adj, vector<vector<int> >& cost, int s, vector<long long>& distance, vector<bool>& changed) {
    const int n = adj.size();
    constexpr long long inf = std::numeric_limits<long long>::max();
    distance[s] = 0;

    for (size_t node = 0; node < n - 1; node++)
    {
        for (size_t u = 0; u < n; u++)
        {
            for (size_t j = 0; j < adj[u].size(); j++)
            {
                if ((distance[adj[u][j]] == inf && distance[u] != inf)
                    || ((distance[adj[u][j]] != inf && distance[u] != inf)
                        && distance[adj[u][j]] > distance[u] + cost[u][j])
                    )
                {
                    distance[adj[u][j]] = distance[u] + cost[u][j];
                }
            }
        }
    }

    queue<int> q;
    for (size_t u = 0; u < n; u++)
    {
        for (size_t j = 0; j < adj[u].size(); j++)
        {
            if ((distance[adj[u][j]] == inf && distance[u] != inf)
                || ((distance[adj[u][j]] != inf && distance[u] != inf)
                    && distance[adj[u][j]] > distance[u] + cost[u][j])
                )
            {
                distance[adj[u][j]] = distance[u] + cost[u][j];
                q.push(adj[u][j]);
                changed[adj[u][j]] = true;
            }
        }
    }

    int u;
    while (!q.empty())
    {
        u = q.front();
        q.pop();
        for (size_t j = 0; j < adj[u].size(); j++)
        {
            if (!changed[adj[u][j]])
            {
                changed[adj[u][j]] = true;
                q.push(adj[u][j]);
            }
        }
    }

}

int main() {
    int n, m, s;
    std::cin >> n >> m;
    vector<vector<int> > adj(n, vector<int>());
    vector<vector<int> > cost(n, vector<int>());
    for (int i = 0; i < m; i++) {
        int x, y, w;
        std::cin >> x >> y >> w;
        adj[x - 1].push_back(y - 1);
        cost[x - 1].push_back(w);
    }
    std::cin >> s;
    s--;
    vector<long long> distance(n, std::numeric_limits<long long>::max());
    vector<bool> changed(n, false);
    shortest_paths(adj, cost, s, distance, changed);
    for (int i = 0; i < n; i++) {
        if (distance[i] == std::numeric_limits<long long>::max()) {
            std::cout << "*\n";
        }
        else if (changed[i]) {
            std::cout << "-\n";
        }
        else {
            std::cout << distance[i] << "\n";
        }
    }
}
