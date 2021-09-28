//Input Format.The first line of the input contains two integers 𝑛and 𝑘 — the number of stocksand the
//number of points in the year which are common for all of them.Each of the next 𝑛 lines contains 𝑘
//integers.The 𝑖 - th of those 𝑛 lines contains the prices of the 𝑖 - th stock at the corresponding 𝑘 points
//in the year.
//Constraints. 1 ≤ 𝑛 ≤ 100; 1 ≤ 𝑘 ≤ 25. All the stock prices are between 0 and 1 000 000.
//Output Format.Output a single integer — the minimum number of overlaid charts to visualize all the
//stock price data you have.

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using std::vector;
using std::cin;
using std::cout;
using std::pair;
using std::queue;


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

bool compare(const vector<int>& stock1, const vector<int>& stock2) {
    for (int i = 0; i < stock1.size(); ++i)
        if (stock1[i] >= stock2[i])
            return false;
    return true;
}

FlowGraph read_data(int num_stocks, int num_points) {

    int vertex_count = 2 * num_stocks + 2;

    vector<vector<int>> stock_data(num_stocks, vector<int>(num_points));
    for (int i = 0; i < num_stocks; ++i)
        for (int j = 0; j < num_points; ++j) {
            cin >> stock_data[i][j];
        }

    FlowGraph graph(vertex_count);
    for (int i = 0; i < num_stocks; ++i) {
        graph.add_edge(0, i + 1, 1);
        graph.add_edge(num_stocks + i + 1, vertex_count - 1, 1);
    }


    for (int i = 0; i < num_stocks; ++i)
    {
        for (int j = 0; j < num_stocks; ++j)
        {
            if (i != j && compare(stock_data[i], stock_data[j]))
                graph.add_edge(i + 1, num_stocks + j + 1, 1);
        }
    }

    return graph;
}

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

//void print_path(vector<pair<int, int>> path, FlowGraph& graph)
//{
//    std::cout << "path is;
//    for (size_t i = 0; i < path.size(); i++)
//    {
//        std::cout << path[i].first << ' ';
//    }
//    std::cout << graph.size() - 1 << '\n';
//}

int min_charts(FlowGraph& graph) {

    const int n = graph.size();

    while (true)
    {
        vector<pair<int, int>> path = get_path(graph);
        if (path.empty())
        {
            int num_paths = 0;
            int num_stocks = (n - 2) / 2;
            vector<size_t> vertex_edges = graph.get_ids(n - 1);
            for (size_t id = 0; id < vertex_edges.size(); ++id)
            {
                if (vertex_edges[id] % 2 == 1)
                    if (graph.get_edge(vertex_edges[id]).flow < 0)
                        ++num_paths;
            }
            return num_stocks - num_paths;
        }
        else
        {
            for (size_t i = 0; i < path.size(); i++)
            {
                graph.add_flow(path[i].second, 1);
            }
        }

    }

}

int main()
{
    std::ios_base::sync_with_stdio(false);
    int num_stocks, num_points;
    cin >> num_stocks >> num_points;
    FlowGraph graph = read_data(num_stocks, num_points);
    cout << min_charts(graph) << "\n";

    return 0;
}
