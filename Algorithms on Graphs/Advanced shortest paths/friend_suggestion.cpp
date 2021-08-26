//Input Format.The first line contains two integers 𝑛and 𝑚 — the number of nodesand edges in the
//network, respectively.The nodes are numbered from 1 to 𝑛.Each of the following 𝑚 lines contains
//three integers 𝑢, 𝑣and 𝑙 describing a directed edge(𝑢, 𝑣) of length 𝑙 from the node number 𝑢to the
//node number 𝑣. (Note that some social networks are represented by directed graphs while some other
//correspond naturally to undirected graphs.For example, Twitter is a directed graph(with a directed
//edge(𝑢, 𝑣) meaning that 𝑢 follows 𝑣), while Facebook is an undirected graph(where an undirected
//edge{ 𝑢, 𝑣 } means that 𝑢 and 𝑣 are friends).In this problem, we work with directed graphs only for a
//simple reason.It is easy to turn an undirected graph into a directed one : just replace each undirected
//edge{ 𝑢, 𝑣 } with a pair of directed edges(𝑢, 𝑣) and (𝑣, 𝑢).)
//The next line contains an integer 𝑞 — the number of queries for computing the distance.Each of the
//following 𝑞 lines contains two integers 𝑢and 𝑣 — the numbers of the two nodes to compute the distance
//from 𝑢 to 𝑣.
//Constraints. 1 ≤ 𝑛 ≤ 1 000 000; 1 ≤ 𝑚 ≤ 6 000 000; 1 ≤ 𝑢, 𝑣 ≤ 𝑛; 1 ≤ 𝑙 ≤ 1 000; 1 ≤ 𝑞 ≤ 1 000.
//Output Format.For each query, output one integer on a separate line.If there is no path from 𝑢 to 𝑣,
//output −1.Otherwise, output the distance from 𝑢 to 𝑣.

#include <cstdio>
#include <cassert>
#include <vector>
#include <queue>
#include <limits>
#include <utility>


using namespace std;

// External vector of size 2 - for forward and backward search.
// Internal 2-dimensional vector is vector of adjacency lists for each node.
typedef vector<vector<vector<int>>> Adj;

// Distances can grow out of int type
typedef long long Len;

// Vector of two priority queues - for forward and backward searches.
// Each priority queue stores the closest unprocessed node in its head.
typedef vector<priority_queue<pair<Len, int>, vector<pair<Len, int>>, greater<pair<Len, int>>>> Queue;
typedef pair<Len, int> pi;

const Len INFINIT = numeric_limits<Len>::max() / 4;

class Bidijkstra {
    // Number of nodes
    int n_;
    // Graph adj_[0] and cost_[0] correspond to the initial graph,
    // adj_[1] and cost_[1] correspond to the reversed graph.
    // Graphs are stored as vectors of adjacency lists corresponding
    // to nodes.
    // Adjacency list itself is stored in adj_, and the corresponding
    // edge costs are stored in cost_.
    Adj adj_;
    Adj cost_;
    // distance_[0] stores distances for the forward search,
    // and distance_[1] stores distances for the backward search.
    vector<vector<Len>> distance_;
    // Stores all the nodes visited either by forward or backward search.
    vector<int> workset_;
    // Stores a flag for each node which is True iff the node was visited
    // either by forward or backward search.
    vector<pair<bool, bool>> visited_;

public:
    Bidijkstra(int n, Adj adj, Adj cost)
        : n_(n), adj_(adj), cost_(cost), distance_(2, vector<Len>(n, INFINIT)), visited_(n)
    {
        workset_.reserve(n);
    }

    // Initialize the data structures before new query,
    // clear the changes made by the previous query.
    void clear() {
        for (int i = 0; i < workset_.size(); ++i) {
            int v = workset_[i];
            distance_[0][v] = distance_[1][v] = INFINIT;
            visited_[v] = { false,false };
        }
        workset_.clear();
    }


    void relax(Queue& q, int side, int u)
    {
        for (size_t i = 0; i < adj_[side][u].size(); i++)
        {
            int v = adj_[side][u][i];
            if (distance_[side][v] == INFINIT) workset_.push_back(v);
            if (distance_[side][v] > distance_[side][u] + cost_[side][u][i])
            {
                distance_[side][v] = distance_[side][u] + cost_[side][u][i];
                q[side].push({ distance_[side][v] , v });
            }
        }
    }


    Len shortest()
    {
        Len best_dist = INFINIT;
        for (size_t i = 0; i < workset_.size(); i++)
        {
            if (distance_[0][workset_[i]] + distance_[1][workset_[i]] < best_dist)
            {
                best_dist = distance_[0][workset_[i]] + distance_[1][workset_[i]];
            }
        }
        return best_dist;
    }

    // Returns the distance from s to t in the graph.
    Len query(int s, int t)
    {
        clear();
        Queue q(2);
        distance_[0][s] = 0;
        distance_[1][t] = 0;
        q[0].push({ 0,s });
        q[1].push({ 0,t });
        workset_.push_back(s);
        workset_.push_back(t);

        int u;
        double dist;

        do
        {
            if (q[0].empty()) return -1;
            u = q[0].top().second;
            dist = q[0].top().first;
            if (dist == INFINIT) return -1;
            q[0].pop();
            if (!visited_[u].first)
            {
                relax(q, 0, u);
                distance_[0][u] = dist;
            }

            if (visited_[u].second) return shortest();

            visited_[u].first = true;

            if (q[1].empty()) return -1;
            u = q[1].top().second;
            dist = q[1].top().first;
            if (dist == INFINIT) return -1;
            q[1].pop();
            if (!visited_[u].second)
            {
                relax(q, 1, u);
                distance_[1][u] = dist;
            }

            if (visited_[u].first) return shortest();

            visited_[u].second = true;

        } while (true);

        return -1;
    }
};


int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    Adj adj(2, vector<vector<int>>(n));
    Adj cost(2, vector<vector<int>>(n));
    for (int i = 0; i < m; ++i) {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);
        adj[0][u - 1].push_back(v - 1);
        cost[0][u - 1].push_back(c);
        adj[1][v - 1].push_back(u - 1);
        cost[1][v - 1].push_back(c);
    }

    Bidijkstra bidij(n, adj, cost);

    int t;
    scanf("%d", &t);
    for (int i = 0; i < t; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        printf("%lld\n", bidij.query(u - 1, v - 1));
    }
}
