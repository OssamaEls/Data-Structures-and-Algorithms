//Input Format.A graph is given in the standard format.The next line contains two vertices 𝑢and 𝑣.
//Constraints. 1 ≤ 𝑛 ≤ 10^4, 0 ≤ 𝑚 ≤ 10^5, 𝑢 ̸ = 𝑣, 1 ≤ 𝑢, 𝑣 ≤ 𝑛, edge weights are non - negative integers not
//exceeding 108.
//Output Format.Output the minimum weight of a path from 𝑢 to 𝑣, or −1 if there is no path.

#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;

struct MyDist
{
    long long distance = 0;
    bool infinite = true;
};

typedef std::pair<MyDist, int> pi;

struct myComp {
    constexpr bool operator()(
        pi const& a,
        pi const& b)
        const noexcept
    {
        if (!a.first.infinite && !b.first.infinite)
        {
            return a.first.distance > b.first.distance;
        }
        else
        {
            return a.first.infinite && !b.first.infinite;
        }
    }
};


long long distance(vector<vector<int> >& adj, vector<vector<int> >& cost, int s, int t) {
    int n = adj.size();
    vector<MyDist> dist(n);

    dist[s] = { 0, false };

    priority_queue<pi, vector<pi>, myComp> H;
    for (auto i = 0; i < n; ++i)
    {
        H.push({ dist[i],i });
    }
    vector<bool> extracted(n, false);
    int no_extracted = 0;
    while (no_extracted < n)
    {
        pi min_pair = H.top();
        int u = min_pair.second;
        if (dist[u].infinite) break;
        H.pop();
        if (!extracted[u])
        {
            extracted[u] = true;
            ++no_extracted;
            for (int i = 0; i < adj[u].size(); ++i)
            {
                if (dist[adj[u][i]].infinite || (dist[adj[u][i]].distance > dist[u].distance + cost[u][i]))
                {
                    dist[adj[u][i]] = { dist[u].distance + cost[u][i], false };
                    H.push({ dist[adj[u][i]] , adj[u][i] });
                }
            }
        }
    }

    return !dist[t].infinite ? dist[t].distance : -1;
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
    int s, t;
    std::cin >> s >> t;
    s--, t--;
    std::cout << distance(adj, cost, s, t);
}
