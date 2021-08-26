//Input Format.The first line contains two integers 𝑛and 𝑚 — the number of nodesand edges in the
//network, respectively.The nodes are numbered from 1 to 𝑛.Each of the following 𝑛 lines contains the
//coordinates 𝑥 and 𝑦 of the corresponding node.Each of the following 𝑚 lines contains three integers
//𝑢, 𝑣and 𝑙 describing a directed edge(𝑢, 𝑣) of length 𝑙 from the node number 𝑢 to the node number 𝑣.
//It is guaranteed that 𝑙 ≥ √︀(𝑥(𝑢) − 𝑥(𝑣))2 + (𝑦(𝑢) − 𝑦(𝑣))2 where(𝑥(𝑢), 𝑦(𝑢)) are the coordinates of 𝑢
//and (𝑥(𝑣), 𝑦(𝑣)) are the coordinates of 𝑣.The next line contains an integer 𝑞 — the number of queries
//for computing the distance.Each of the following 𝑞 lines contains two integers 𝑢and 𝑣 — the numbers
//of the two nodes to compute the distance from 𝑢 to 𝑣.
//Constraints. 1 ≤ 𝑛 ≤ 110 000; 1 ≤ 𝑚 ≤ 250 000; −10^9 ≤ 𝑥, 𝑦 ≤ 10^9; 1 ≤ 𝑢, 𝑣 ≤ 𝑛; 0 ≤ 𝑙 ≤ 100 000;
//1 ≤ 𝑞 ≤ 10 000.
//Output Format.For each query, output one integer.If there is no path from 𝑢 to 𝑣, output −1.Otherwise,
//output the distance from 𝑢 to 𝑣.

#include <cstdio>
#include <cassert>
#include <vector>
#include <queue>
#include <limits>
#include <utility>
#include <cmath>

using namespace std;

// See the explanations of these typedefs and constants in friend_suggestion
typedef vector<vector<int>> Adj;
typedef long long Len;
typedef priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> Queue;

const double INFINIT = static_cast<double>(numeric_limits<Len>::max() / 4);

class AStar {
    // See the descriptions of these fields in friend_suggestion
    int n_;
    Adj adj_;
    Adj cost_;
    vector<double> distance_;
    vector<int> workset_;
    vector<bool> visited_;
    // Coordinates of the nodes
    std::vector<std::pair<Len, Len>> xy_;

public:
    AStar(int n, Adj adj, Adj cost, std::vector<std::pair<Len, Len>> xy)
        : n_(n), adj_(adj), cost_(cost), distance_(vector<double>(n_, INFINIT)), visited_(n), xy_(xy)
    {
        workset_.reserve(n);
    }

    // See the description of this method in friend_suggestion
    void clear() {
        for (int i = 0; i < workset_.size(); ++i) {
            int v = workset_[i];
            distance_[v] = INFINIT;
            visited_[v] = false;
        }
        workset_.clear();
    }


    double eucl_distance(int v, int t)
    {
        return sqrt(pow(xy_[t].first - xy_[v].first, 2) + pow(xy_[t].second - xy_[v].second, 2));
    }

    void relax(Queue& q, int u, int t)
    {
        double pu = eucl_distance(u, t);
        double pv;
        for (size_t i = 0; i < adj_[u].size(); i++)
        {
            int v = adj_[u][i];
            if (distance_[v] == INFINIT) workset_.push_back(v);
            pv = eucl_distance(v, t);
            if (distance_[v] > distance_[u] + cost_[u][i] - pu + pv)
            {
                distance_[v] = distance_[u] + cost_[u][i] - pu + pv;
                q.push({ distance_[v] , v });
            }
        }
    }


    // Returns the distance from s to t in the graph
    Len query(int s, int t) {
        clear();
        Queue q;
        distance_[s] = 0;
        q.push({ 0,s });
        workset_.push_back(s);

        int u;
        double dist;
        while (!q.empty())
        {
            u = q.top().second;
            dist = q.top().first;
            q.pop();
            if (u == t) break;
            if (!visited_[u])
            {
                distance_[u] = dist;
                relax(q, u, t);
                visited_[u] = true;
            }
        }

        return distance_[t] == INFINIT ? -1 : round(distance_[t] + eucl_distance(s, t));
    }
};

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    std::vector<std::pair<Len, Len>> xy(n);
    for (int i = 0; i < n; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        xy[i] = make_pair(a, b);
    }
    Adj adj(n, vector<int>());
    Adj cost(n, vector<int>());
    for (int i = 0; i < m; ++i) {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);
        adj[u - 1].push_back(v - 1);
        cost[u - 1].push_back(c);
    }

    AStar astar(n, adj, cost, xy);

    int t;
    scanf("%d", &t);
    for (int i = 0; i < t; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        printf("%lld\n", astar.query(u - 1, v - 1));
    }
}