//Input Format.The first line of the input contains integers 𝑛and 𝑚 — the number of citiesand the number
//of roads respectively.Each of the next 𝑚 lines contains three integers 𝑢, 𝑣and 𝑐 describing a particular
//road — start of the road, end of the roadand the number of people that can be transported through
//this road in one hour.𝑢and 𝑣 are the 1 - based indices of the corresponding cities.
//The city from which people are evacuating is the city number 1, and the capital city is the city number
//𝑛.
//Note that all the roads are given as one - directional, that is, you cannot transport people
//from 𝑣 to 𝑢 using a road that connects 𝑢 to 𝑣.Also note that there can be several roads
//connecting the same city 𝑢 to the same city 𝑣, there can be both roads from 𝑢 to 𝑣and
//from 𝑣 to 𝑢, or there can be only roads in one direction, or there can be no roads between
//a pair of cities.Also note that there can be roads going from a city 𝑢 to itself in the
//input.
//When evacuating people, they cannot stop in the middle of the road or in any city other than the
//capital.The number of people per hour entering any city other than the evacuating city 1 and the
//capital city 𝑛 must be equal to the number of people per hour exiting from this city.People who left
//a city 𝑢 through some road(𝑢, 𝑣, 𝑐) are assumed to come immediately after that to the city 𝑣.We
//are interested in the maximum possible number of people per hour leaving the city 1 under the above
//restrictions.
//
//Constraints. 1 ≤ 𝑛 ≤ 100; 0 ≤ 𝑚 ≤ 10 000; 1 ≤ 𝑢, 𝑣 ≤ 𝑛; 1 ≤ 𝑐 ≤ 10 000. It is guaranteed that
//𝑚 · EvacuatePerHour ≤ 2 · 10^8, where EvacuatePerHour is the maximum number of people that can
//be evacuated from the city each hour — the number which you need to output.
//
//Output Format.Output a single integer — the maximum number of people that can be evacuated from
//the city number 1 each hour.

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using std::vector;
using std::queue;
using std::pair;

/* This class implements a bit unusual scheme for storing edges of the graph,
 * in order to retrieve the backward edge for a given edge quickly. */
class FlowGraph {
public:
    struct Edge {
        int from, to, capacity, flow;
    };

private:
    /* List of all - forward and backward - edges */
    vector<Edge> edges;

    /* These adjacency lists store only indices of edges in the edges list */
    vector<vector<size_t> > graph;

public:
    explicit FlowGraph(size_t n) : graph(n) {}

    void add_edge(int from, int to, int capacity) {
        /* Note that we first append a forward edge and then a backward edge,
         * so all forward edges are stored at even indices (starting from 0),
         * whereas backward edges are stored at odd indices in the list edges */
        Edge forward_edge = { from, to, capacity, 0 };
        Edge backward_edge = { to, from, 0, 0 };
        graph[from].push_back(edges.size());
        edges.push_back(forward_edge);
        graph[to].push_back(edges.size());
        edges.push_back(backward_edge);
    }

    size_t size() const {
        return graph.size();
    }

    const vector<size_t>& get_ids(int from) const {
        return graph[from];
    }

    const Edge& get_edge(size_t id) const {
        return edges[id];
    }

    void add_flow(size_t id, int flow) {
        /* To get a backward edge for a true forward edge (i.e id is even), we should get id + 1
         * due to the described above scheme. On the other hand, when we have to get a "backward"
         * edge for a backward edge (i.e. get a forward edge for backward - id is odd), id - 1
         * should be taken.
         *
         * It turns out that id ^ 1 works for both cases. Think this through! */
        edges[id].flow += flow;
        edges[id ^ 1].flow -= flow;
    }
};

vector<pair<int, int>> get_path(FlowGraph& graph) {
    const int n = graph.size();
    vector<int> dist(n, -1);
    vector<pair<int, int>> previous(n, { 0,0 });
    dist[0] = 0;
    queue<int> q;
    q.push(0);
    int u;
    vector<size_t> u_edges;
    int v;
    while (!q.empty())
    {
        u = q.front();
        q.pop();
        u_edges = graph.get_ids(u);
        for (int id = 0; id < u_edges.size(); id++)
        {
            v = graph.get_edge(u_edges[id]).to;
            if (dist[v] == -1 && graph.get_edge(u_edges[id]).flow < graph.get_edge(u_edges[id]).capacity)
            {
                q.push(v);
                dist[v] = dist[u] + 1;
                previous[v] = { u, u_edges[id] };
            }
        }
    }

    if (dist[n - 1] == -1)
    {
        return {};
    }
    else
    {
        u = n - 1;
        vector<pair<int, int>> result;
        while (u != 0)
        {
            result.push_back(previous[u]);
            u = previous[u].first;
        }
        std::reverse(result.begin(), result.end());
        return result;
    }

}

FlowGraph read_data() {
    int vertex_count, edge_count;
    std::cin >> vertex_count >> edge_count;
    FlowGraph graph(vertex_count);
    for (int i = 0; i < edge_count; ++i) {
        int u, v, capacity;
        std::cin >> u >> v >> capacity;
        graph.add_edge(u - 1, v - 1, capacity);
    }
    return graph;
}

void print_path(vector<pair<int, int>> path, FlowGraph& graph)
{
    int min_capacity = graph.get_edge(path[0].second).capacity - graph.get_edge(path[0].second).flow;
    for (size_t i = 1; i < path.size(); i++)
    {
        if (graph.get_edge(path[i].second).capacity - graph.get_edge(path[i].second).flow < min_capacity)
        {
            min_capacity = graph.get_edge(path[i].second).capacity - graph.get_edge(path[i].second).flow;
        }
    }
}

int max_flow(FlowGraph& graph, int from, int to) {
    int flow = 0;
    /* your code goes here */
    const int n = graph.size();


    while (true)
    {
        vector<pair<int, int>> path = get_path(graph);
        if (path.empty())
        {
            return flow;
        }
        else
        {
            int min_capacity = graph.get_edge(path[0].second).capacity - graph.get_edge(path[0].second).flow;
            for (size_t i = 1; i < path.size(); i++)
            {
                if (graph.get_edge(path[i].second).capacity - graph.get_edge(path[i].second).flow < min_capacity)
                {
                    min_capacity = graph.get_edge(path[i].second).capacity - graph.get_edge(path[i].second).flow;
                }
            }

            int kth_vertex = 0;
            for (size_t i = 0; i < path.size(); i++)
            {
                graph.add_flow(path[i].second, min_capacity);
            }

            flow = 0;
            vector<size_t> vertex_edges;
            vertex_edges = graph.get_ids(n - 1);
            for (size_t id = 0; id < vertex_edges.size(); ++id)
            {
                if (vertex_edges[id] % 2 == 1)
                    flow -= graph.get_edge(vertex_edges[id]).flow;
            }
        }

    }

}

int main() {
    std::ios_base::sync_with_stdio(false);
    FlowGraph graph = read_data();

    std::cout << max_flow(graph, 0, graph.size() - 1) << "\n";
    return 0;
}