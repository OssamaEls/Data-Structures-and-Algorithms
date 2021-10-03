//Input Format.The first line contains two integers 𝑛and 𝑚 — the number of verticesand the number of
//edges in the graph.The vertices are numbered from 1 through 𝑛.Each of the next 𝑚 lines contains
//three integers 𝑢, 𝑣and 𝑡 representing an edge of the graph.This edge connects vertices 𝑢and 𝑣, and
//it takes time 𝑡 to get from 𝑢 to 𝑣.The edges are bidirectional : you can go both from 𝑢 to 𝑣and from
//𝑣 to 𝑢 in time 𝑡 using this edge.No edge connects a vertex to itself.No two vertices are connected by
//more than one edge.
//
//Constraints. 2 ≤ 𝑛 ≤ 17; 1 ≤ 𝑚 ≤ 𝑛(𝑛^2−1); 1 ≤ 𝑢, 𝑣 ≤ 𝑛; 𝑢 ̸ = 𝑣; 1 ≤ 𝑡 ≤ 10^9.
//
//Output Format.If it is possible to start in some vertex, visit each other vertex exactly once in some order
//going by edges of the graphand return to the starting vertex, output two lines.On the first line, output
//the minimum possible time to go through such circular route visiting all vertices exactly once(apart
//from the first vertex which is visited twice — in the beginning and in the end).On the second line,
//output the order in which you should visit the vertices to get the minimum possible time on the route.
//That is, output the numbers from 1 through 𝑛 in the order corresponding to visiting the vertices.Don’t
//output the starting vertex second time.However, account for the time to get from the last vertex back
//to the starting vertex.If there are several solutions, output any one of them.If there is no such circular
//route, output just −1 on a single line.Note that for 𝑛 = 2 it is considered a correct circular route to
//go from one vertex to another by an edge and then return back by the same edge.

#include <iostream>
#include <algorithm>
#include <vector>

using std::vector;
using std::pair;
typedef vector<vector<long long> > Matrix;

const long long INF = 1e15;


pair<int, vector<int>> count_set_bits(int number)
{
    int count = 0;
    vector<int> bits;
    int num_iterations = 0;
    while (number) {
        ++num_iterations;
        if (number & 1)
        {
            bits.push_back(num_iterations);
            count += number & 1;
        }
        number >>= 1;
    }
    return { count, bits };
}

Matrix read_data() {
    int vertex_count, edge_count;
    std::cin >> vertex_count >> edge_count;
    Matrix graph(vertex_count, vector<long long>(vertex_count, INF));
    for (int i = 0; i < edge_count; ++i) {
        int from, to, weight;
        std::cin >> from >> to >> weight;
        --from, --to;
        graph[from][to] = graph[to][from] = weight;
    }
    return graph;
}

std::pair<long long, vector<int> > optimal_path(const Matrix& graph) {

    const int n = graph.size();
    const int number_subsets = (1 << n) - 1;
    vector<vector<long long>> length_with_reduced_set(number_subsets, vector<long long>(n, INF));
    length_with_reduced_set[0][0] = 0;
    vector<vector<pair<int, vector<int>>>> sets_size_m(n);

    for (int i = 1; i <= number_subsets + 1; i++)
    {
        auto set_bits = count_set_bits(i);
        sets_size_m[set_bits.first - 1].push_back({ i, set_bits.second });
    }


    for (int subset_size = 2; subset_size <= n; subset_size++)
    {
        for (auto set_bits : sets_size_m[subset_size - 1])
        {
            int k = set_bits.first;
            for (int i : set_bits.second)
            {
                if (i != 1)
                {
                    for (int j : set_bits.second)
                    {
                        if (j != i)
                        {
                            int removed_i = k ^ (1 << (i - 1));
                            long long candidate = length_with_reduced_set[removed_i - 1][j - 1] + graph[i - 1][j - 1];
                            length_with_reduced_set[k - 1][i - 1] =
                                length_with_reduced_set[k - 1][i - 1] < candidate ?
                                length_with_reduced_set[k - 1][i - 1] : candidate;
                        }
                    }
                }
            }
        }
    }


    long long shortest = INF;
    int idx_shortest = 1;

    for (int i = 1; i < n; i++)
    {
        if (length_with_reduced_set.back()[i] + graph[i][0] < shortest)
        {
            shortest = length_with_reduced_set.back()[i] + graph[i][0];
            idx_shortest = i;
        }
    }

    if (shortest >= INF) return { -1,{} };

    vector<int> best_path(n);
    best_path[n - 1] = idx_shortest + 1;

    int current_set = number_subsets;
    long long shortest_subpath = 0;
    int prev_idx_shortest = 0;

    for (int i = 0; i < n - 1; i++)
    {
        current_set = current_set ^ (1 << idx_shortest);
        shortest_subpath = INF;
        prev_idx_shortest = 0;
        for (int j = 1; j < n; j++)
        {
            if (length_with_reduced_set[current_set - 1][j] + graph[j][idx_shortest] < shortest_subpath)
            {
                shortest_subpath = length_with_reduced_set[current_set - 1][j] + graph[j][idx_shortest];
                prev_idx_shortest = j;
            }
        }
        best_path[n - 2 - i] = prev_idx_shortest + 1;
        idx_shortest = prev_idx_shortest;
    }

    return { shortest,best_path };
}

void print_answer(const std::pair<long long, vector<int> >& answer) {
    std::cout << answer.first << "\n";
    if (answer.first == -1)
        return;
    const vector<int>& path = answer.second;
    for (int i = 0; i < path.size(); ++i)
        std::cout << path[i] << " ";
    std::cout << "\n";
}

int main() {
    print_answer(optimal_path(read_data()));
    return 0;
}