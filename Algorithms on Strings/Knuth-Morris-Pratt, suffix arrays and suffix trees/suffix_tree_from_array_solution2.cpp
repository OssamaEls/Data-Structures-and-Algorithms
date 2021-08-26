//Input Format.The first line contains a string Text ending with a “$” symbol, the second line contains
//SuffixArray(Text) as a list of | Text | integers separated by spaces, the last line contains LCP(Text) as
//a list of | Text | − 1 integers separated by spaces.
//
//Constraints. 1 ≤ | Text(Text) | ≤ 2 · 10^5; except for the last symbol, Text contains symbols A, C, G, T only.
//
//Output Format. Output the 𝑇 𝑒𝑥𝑡 from the input on the first line.Then output all the edges of the suffix tree
//in a specific order(see below), each on its own line.Output each edge as a pair of integers
//(start, end), where start is the position in Text corresponding to the start of the edge label substring
//in the Textand end is the position right after the end of the edge label in the Text.Note that start
//must be a valid position in the Text, that is, 0 ≤ 𝑠𝑡𝑎𝑟𝑡 ≤ | Text | − 1, and end must be between 1 and
//| Text | inclusive.Substring Text[start..end − 1] must be equal to the edge label of the corresponding
//edge.For example, if Text = “ACACAA$” and the edge label is “CA”, you can output this edge either
//as(1, 3) corresponding to Text[1..2] = “CA” or as(3, 5) corresponding to Text[3..4] = “CA” — both
//variants will be accepted.

#include <algorithm>
#include <cstdio>
#include <map>
#include <string>
#include <utility>
#include <vector>
#include <iostream>

using std::make_pair;
using std::map;
using std::pair;
using std::string;
using std::vector;


// Data structure to store edges of a suffix tree.
struct Edge {
    // The ending node of this edge.
    int node;
    // Starting position of the substring of the text 
    // corresponding to the label of this edge.
    int start;
    // Position right after the end of the substring of the text 
    // corresponding to the label of this edge.
    int end;

    Edge* prev_edge;
    int string_depth;

    Edge()
    {
        node = -1, start = -1, end = -1, prev_edge = nullptr, string_depth = -1;
    }

    Edge(int node_, int start_, int end_, Edge* prev_edge_, int string_depth_) :
        node(node_), start(start_), end(end_), prev_edge(prev_edge_), string_depth(string_depth_) {}

    Edge(const Edge& e) : node(e.node), start(e.start), end(e.end),
        prev_edge(e.prev_edge), string_depth(e.string_depth) {}
};



// Build suffix tree of the string text given its suffix array suffix_array
// and LCP array lcp_array. Return the tree as a mapping from a node ID
// to the vector of all outgoing edges of the corresponding node. The edges in the
// vector must be sorted in the ascending order by the first character of the edge label.
// Root must have node ID = 0, and all other node IDs must be different
// nonnegative integers.
//
// For example, if text = "ACACAA$", an edge with label "$" from root to a node with ID 1
// must be represented by Edge(1, 6, 7). This edge must be present in the vector tree[0]
// (corresponding to the root node), and it should be the first edge in the vector 
// (because it has the smallest first character of all edges outgoing from the root).
map<int, vector<Edge> > SuffixTreeFromSuffixArray(
    const vector<int>& suffix_array,
    const vector<int>& lcp_array,
    const string& text) {
    map<int, vector<Edge> > tree;
    // Implement this function yourself
    const int n = suffix_array.size();

    tree[0].push_back(Edge(1, n - 1, n, nullptr, 1));

    int lcp_prev = 0;
    Edge* cur_edge = &tree[0][0];


    int suffix;
    int parent;
    int next_id = 1;
    int edge_start;
    int offset;
    int str_depth;

    for (int i = 1; i < n; i++)
    {
        suffix = suffix_array[i];

        while (cur_edge != NULL && cur_edge->string_depth > lcp_prev)
        {
            cur_edge = cur_edge->prev_edge;
        }

        if ((cur_edge == NULL && lcp_prev == 0) || (cur_edge != NULL && cur_edge->string_depth == lcp_prev))
        {
            parent = cur_edge == NULL ? 0 : cur_edge->node;
            str_depth = cur_edge == NULL ? 0 : cur_edge->string_depth;
            ++next_id;


            tree[parent].push_back(Edge(next_id, suffix + str_depth, n, cur_edge, n - suffix));
            cur_edge = &tree[parent].back();

        }
        else
        {
            str_depth = cur_edge == NULL ? 0 : cur_edge->string_depth;
            edge_start = suffix_array[i - 1] + str_depth;
            parent = cur_edge == NULL ? 0 : cur_edge->node;
            offset = lcp_prev - str_depth;
            ++next_id;


            Edge* mid_edge = new Edge(next_id, edge_start, edge_start + offset, cur_edge, str_depth + offset);



            Edge* broken_edge = new Edge(tree[parent].back());

            tree[next_id].push_back(Edge(broken_edge->node, broken_edge->start + offset,
                broken_edge->end, mid_edge, broken_edge->string_depth));


            tree[parent][tree[parent].size() - 1] = *mid_edge;

            tree[next_id].push_back(Edge(next_id + 1, suffix + mid_edge->string_depth, n, mid_edge, n - suffix));


            cur_edge = &tree[next_id].back();

            ++next_id;
        }
        if (i < n - 1) lcp_prev = lcp_array[i];
    }


    return tree;
}


int main() {
    char buffer[200001];
    scanf("%s", buffer);
    string text = buffer;
    vector<int> suffix_array(text.length());
    for (int i = 0; i < text.length(); ++i) {
        scanf("%d", &suffix_array[i]);
    }
    vector<int> lcp_array(text.length() - 1);
    for (int i = 0; i + 1 < text.length(); ++i) {
        scanf("%d", &lcp_array[i]);
    }
    // Build the suffix tree and get a mapping from 
    // suffix tree node ID to the list of outgoing Edges.
    map<int, vector<Edge> > tree = SuffixTreeFromSuffixArray(suffix_array, lcp_array, text);
    printf("%s\n", buffer);
    // Output the edges of the suffix tree in the required order.
    // Note that we use here the contract that the root of the tree
    // will have node ID = 0 and that each vector of outgoing edges
    // will be sorted by the first character of the corresponding edge label.
    //
    // The following code avoids recursion to avoid stack overflow issues.
    // It uses a stack to convert recursive function to a while loop.
    // The stack stores pairs (node, edge_index). 
    // This code is an equivalent of 
    //
    //    OutputEdges(tree, 0);
    //
    // for the following _recursive_ function OutputEdges:
    //
    // void OutputEdges(map<int, vector<Edge> > tree, int node_id) {
    //   const vector<Edge>& edges = tree[node_id];
    //   for (int edge_index = 0; edge_index < edges.size(); ++edge_index) {
    //     printf("%d %d\n", edges[edge_index].start, edges[edge_index].end);
    //     OutputEdges(tree, edges[edge_index].node);
    //   }
    // }
    //
    vector<pair<int, int> > stack(1, make_pair(0, 0));
    while (!stack.empty()) {
        pair<int, int> p = stack.back();
        stack.pop_back();
        int node = p.first;
        int edge_index = p.second;
        if (!tree.count(node)) {
            continue;
        }
        const vector<Edge>& edges = tree[node];
        if (edge_index + 1 < edges.size()) {
            stack.push_back(make_pair(node, edge_index + 1));
        }
        printf("%d %d\n", edges[edge_index].start, edges[edge_index].end);
        stack.push_back(make_pair(edges[edge_index].node, 0));
    }
    return 0;
}





