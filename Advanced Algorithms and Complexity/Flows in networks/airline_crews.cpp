//Input Format.The first line of the input contains integers 𝑛and 𝑚 — the number of flightsand the number
//of crews respectively.Each of the next 𝑛 lines contains 𝑚 binary integers(0 or 1).If the 𝑗 - th integer
//in the 𝑖 - th line is 1, then the crew number 𝑗 can work on the flight number 𝑖, and if it is 0, then it
//cannot.
//
//Constraints. 1 ≤ 𝑛, 𝑚 ≤ 100.
//
//Output Format.Output 𝑛 integers — for each flight, output the 1 - based index of the crew assigned to
//this flight.If no crew is assigned to a flight, output −1 as the index of the crew corresponding to it.
//All the positive indices in the output must be between 1 and 𝑚, and they must be pairwise different,
//but you can output any number of −1’s.If there are several assignments with the maximum possible
//number of flights having a crew assigned, output any of them.

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using std::vector;
using std::cin;
using std::cout;
using std::queue;
using std::pair;

//class MaxMatching {
//public:
//    void Solve() {
//        vector<vector<bool>> adj_matrix = ReadData();
//        vector<int> matching = FindMatching(adj_matrix);
//        WriteResponse(matching);
//    }
//
//private:
//    vector<vector<bool>> ReadData() {
//        int num_left, num_right;
//        cin >> num_left >> num_right;
//        vector<vector<bool>> adj_matrix(num_left, vector<bool>(num_right));
//        for (int i = 0; i < num_left; ++i)
//            for (int j = 0; j < num_right; ++j) {
//                int bit;
//                cin >> bit;
//                adj_matrix[i][j] = (bit == 1);
//            }
//        return adj_matrix;
//    }
//
//    void WriteResponse(const vector<int>& matching) {
//        for (int i = 0; i < matching.size(); ++i) {
//            if (i > 0)
//                cout << " ";
//            if (matching[i] == -1)
//                cout << "-1";
//            else
//                cout << (matching[i] + 1);
//        }
//        cout << "\n";
//    }
//
//    vector<int> FindMatching(const vector<vector<bool>>& adj_matrix) {
//        // Replace this code with an algorithm that finds the maximum
//        // matching correctly in all cases.
//        int num_left = adj_matrix.size();
//        int num_right = adj_matrix[0].size();
//        vector<int> matching(num_left, -1);
//        vector<bool> busy_right(num_right, false);
//        for (int i = 0; i < num_left; ++i)
//            for (int j = 0; j < num_right; ++j)
//                if (matching[i] == -1 && !busy_right[j] && adj_matrix[i][j]) {
//                    matching[i] = j;
//                    busy_right[j] = true;
//                }
//        return matching;
//    }
//};

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

FlowGraph read_data(int num_left, int num_right) {

    int vertex_count = num_left + num_right + 2;

    FlowGraph graph(vertex_count);
    for (int i = 0; i < num_left; ++i) {
        graph.add_edge(0, i + 1, 1);
    }

    for (int i = 0; i < num_right; ++i) {
        graph.add_edge(num_left + i + 1, vertex_count - 1, 1);
    }

    for (int i = 0; i < num_left; ++i)
        for (int j = 0; j < num_right; ++j) {
            int bit;
            cin >> bit;
            if (bit)
                graph.add_edge(i + 1, num_left + j + 1, 1);
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

void print_path(vector<pair<int, int>> path, FlowGraph& graph)
{
    std::cout << "path is: ";
    for (size_t i = 0; i < path.size(); i++)
    {
        std::cout << path[i].first << ' ';
    }
    std::cout << graph.size() - 1 << '\n';
}

vector<int> max_flow(FlowGraph& graph, int num_left) {

    /* your code goes here */
    const int n = graph.size();


    while (true)
    {
        vector<pair<int, int>> path = get_path(graph);
        //print_path(path, graph);
        if (path.empty())
        {
            vector<int> matching(num_left, -1);
            vector<size_t> vertex_edges;
            for (size_t left_vertex = 0; left_vertex < num_left; left_vertex++)
            {
                vertex_edges = graph.get_ids(left_vertex + 1);
                for (size_t edge = 0; edge < vertex_edges.size(); edge++)
                {
                    if (vertex_edges[edge] % 2 == 0)
                    {
                        if (graph.get_edge(vertex_edges[edge]).flow > 0)
                        {
                            matching[left_vertex] = graph.get_edge(vertex_edges[edge]).to - num_left - 1;
                            break;
                        }
                    }
                }
            }
            return matching;
        }
        else
        {
            int kth_vertex = 0;
            for (size_t i = 0; i < path.size(); i++)
            {
                graph.add_flow(path[i].second, 1);
            }
        }

    }

}

void writeResponse(const vector<int>& matching) {
    for (int i = 0; i < matching.size(); ++i) {
        if (i > 0)
            cout << " ";
        if (matching[i] == -1)
            cout << "-1";
        else
            cout << (matching[i] + 1);
    }
    cout << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    // MaxMatching max_matching;
    int num_left, num_right;
    cin >> num_left >> num_right;
    FlowGraph graph = read_data(num_left, num_right);
    vector<int> matching = max_flow(graph, num_left);
    writeResponse(matching);
    //max_matching.Solve();
    return 0;
}