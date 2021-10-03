//Input Format.The first line contains an integer 𝑛 — the number of people in the company.The next line
//contains 𝑛 numbers 𝑓𝑖 — the fun factors of each of the 𝑛 people in the company.Each of the next 𝑛−1
//lines describes the subordination structure.Everyone but for the CEO of the company has exactly one
//direct boss.There are no cycles : nobody can be a boss of a boss of a ... of a boss of himself.So, the
//subordination structure is a regular tree.Each of the 𝑛 − 1 lines contains two integers 𝑢 and 𝑣, and
//you know that either 𝑢 is the boss of 𝑣 or vice versa(you don’t really need to know which one is the
//boss, but you can invite only one of them or none of them).
//
//Constraints. 1 ≤ 𝑛 ≤ 100 000; 1 ≤ 𝑓𝑖 ≤ 1 000; 1 ≤ 𝑢, 𝑣 ≤ 𝑛; 𝑢 ̸ = 𝑣.
//
//Output Format.Output the maximum possible total fun factor of the party(the sum of fun factors of all
//        the invited people)

#include <iostream>
#include <vector>
#include <sys/resource.h>

struct Vertex {
    int weight;
    std::vector <int> children;
};
typedef std::vector<Vertex> Graph;
typedef std::vector<int> Sum;

using std::vector;

Graph ReadTree() {
    int vertices_count;
    std::cin >> vertices_count;

    Graph tree(vertices_count);

    for (int i = 0; i < vertices_count; ++i)
        std::cin >> tree[i].weight;

    for (int i = 1; i < vertices_count; ++i) {
        int from, to, weight;
        std::cin >> from >> to;
        tree[from - 1].children.push_back(to - 1);
        tree[to - 1].children.push_back(from - 1);
    }

    return tree;
}

void dfs(const Graph& graph, int vertex, int parent, vector<vector<int>>& actual_tree) {
    for (int child : graph[vertex].children)
        if (child != parent)
        {
            actual_tree[vertex].push_back(child);
            dfs(graph, child, vertex, actual_tree);
        }
}

int maximise_total_weight(const Graph& graph, const vector<vector<int>>& tree, vector<int>& max_weights, int vertex)
{
    if (max_weights[vertex] == 0)
    {
        if (tree[vertex].empty())
        {
            max_weights[vertex] = graph[vertex].weight;
        }
        else
        {
            int m1 = graph[vertex].weight;
            for (int child : tree[vertex])
            {
                for (int great_child : tree[child])
                {
                    m1 = m1 + maximise_total_weight(graph, tree, max_weights, great_child);
                }
            }
            int m0 = 0;
            for (int child : tree[vertex])
            {
                m0 = m0 + maximise_total_weight(graph, tree, max_weights, child);
            }
            max_weights[vertex] = m0 < m1 ? m1 : m0;
        }

    }

    return max_weights[vertex];
}

int MaxWeightIndependentTreeSubset(const Graph& graph) {
    size_t size = graph.size();
    if (size == 0)
        return 0;

    vector<vector<int>> tree(size);

    dfs(graph, 0, -1, tree);

    vector<int> max_weights(size, 0);

    return maximise_total_weight(graph, tree, max_weights, 0);
}

int main_with_large_stack_space() {
    Graph tree = ReadTree();
    int weight = MaxWeightIndependentTreeSubset(tree);
    std::cout << weight << std::endl;
    return 0;
}

int main(int argc, char** argv) {
    // This code is here to increase the stack size to avoid stack overflow
    // in depth-first search.

    const rlim_t kStackSize = 64L * 1024L * 1024L;  // min stack size = 64 Mb
    struct rlimit rl;
    int result;
    result = getrlimit(RLIMIT_STACK, &rl);
    if (result == 0)
    {
        if (rl.rlim_cur < kStackSize)
        {
            rl.rlim_cur = kStackSize;
            result = setrlimit(RLIMIT_STACK, &rl);
            if (result != 0)
            {
                fprintf(stderr, "setrlimit returned result = %d\n", result);
            }
        }
    }
    
    return main_with_large_stack_space();
}
