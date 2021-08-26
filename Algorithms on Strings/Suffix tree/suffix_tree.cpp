//Input Format.A string Text ending with a “$” symbol.
//Constraints. 1 ≤ | Text | ≤ 5 000; except for the last symbol, Text contains symbols A, C, G, T only.
//Output Format.The strings labeling the edges of SuffixTree(Text) in any order.

#include <iostream>
#include <map>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::string;
using std::vector;

struct Edge
{
    int child;
    int start;
    int length;

    Edge(int child_, int start_, int length_) :
        child(child_), start(start_), length(length_) {}
    Edge(const Edge& e) : child(e.child), start(e.start), length(e.length) {}
};


typedef map<int, vector<Edge>> tree;

// Build a suffix tree of the string text and return a vector
// with all of the labels of its edges (the corresponding 
// substrings of the text) in any order.
vector<string> ComputeSuffixTreeEdges(const string& text) {
    vector<string> result;
    // Implement this function yourself


    const int n = text.size();

    tree t;

    int current_node = 0;
    int new_node = 1;
    int k;
    int match_length;
    int idx;

    t[current_node].push_back({ new_node, 0, n });

    for (size_t i = 1; i < n; i++)
    {
        current_node = 0;
        idx = 0;

        while (!t[current_node].empty())
        {
            bool match = false;
            int offset = 0;
            for (size_t j = 0; j < t[current_node].size(); j++)
            {
                if (text[t[current_node][j].start] == text[i + idx])
                {
                    match = true;
                    k = j;
                    break;
                }
            }

            if (match)
            {
                match_length = t[current_node][k].length < n - i - idx ? t[current_node][k].length : n - i - idx;
                ++idx;
                ++offset;
                for (size_t j = 1; j < match_length; j++)
                {
                    if (text[t[current_node][k].start + j] != text[i + idx]) break;
                    ++idx;
                    ++offset;
                }
                if (offset == match_length)
                {
                    current_node = t[current_node][k].child;
                }
                else
                {
                    ++new_node;
                    int adjusted = i + idx - offset;
                    Edge broken = Edge(t[current_node][k]);
                    t[current_node][k] = Edge(new_node, adjusted, offset);
                    t[new_node].push_back(Edge(broken.child, broken.start + offset, broken.length - offset));
                    t[new_node].push_back(Edge(new_node + 1, i + idx, n - i - idx));
                    ++new_node;
                    current_node = new_node;
                }

            }
            else
            {
                ++new_node;
                t[current_node].push_back(Edge(new_node, i + idx, n - i - idx));
                current_node = new_node;
            }
        }

    }


    for (auto it = t.begin(); it != t.end(); it++)
    {
        for (size_t i = 0; i < it->second.size(); i++)
        {
            result.push_back(text.substr(it->second[i].start, it->second[i].length));
        }
    }

    return result;
}

int main() {
    string text;
    cin >> text;
    vector<string> edges = ComputeSuffixTreeEdges(text);
    for (int i = 0; i < edges.size(); ++i) {
        cout << edges[i] << endl;
    }
    return 0;
}
