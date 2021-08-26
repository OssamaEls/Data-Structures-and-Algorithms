//Input Format.Strings Text1and Text2.
//Constraints. 1 ≤ | Text1 | , | Text2 | ≤ 2 000; strings have equal length(| Text1 | = | Text2 | ), are not equal
//(Text1 ̸ = Text2), and contain symbols A, C, G, T only.
//Output Format.The shortest(non - empty) substring of Text1 that does not appear in Text2. (Multiple
//    solutions may exist, in which case you may return any one.)

#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

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

struct NodeEdge {
    tree t;
    map<int, int> lengths;
    map<int, bool> r_node;
};


NodeEdge ComputeSuffixTreeEdges(const string& text) {

    const int n = text.size();

    tree t;
    map<int, int> lengths;
    map<int, bool> r_node;

    int current_node = 0;
    int new_node = 1;
    int k;
    int match_length;
    int idx;

    t[current_node].push_back({ new_node, 0, n });
    lengths[0] = 0;
    lengths[1] = n;

    for (size_t i = 1; i < n / 2 - 1; i++)
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
                    lengths[new_node] = lengths[current_node] + offset;
                    lengths[new_node + 1] = lengths[new_node] + n - i - idx;
                    r_node[new_node] = false;
                    r_node[new_node + 1] = false;
                    ++new_node;
                    current_node = new_node;
                }

            }
            else
            {
                ++new_node;
                t[current_node].push_back(Edge(new_node, i + idx, n - i - idx));
                lengths[new_node] = lengths[current_node] + n - i - idx;
                r_node[new_node] = false;
                current_node = new_node;
            }
        }

    }

    for (size_t i = n / 2 - 1; i < n; i++)
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
                    r_node[current_node] = true;
                }
                else
                {
                    ++new_node;
                    int adjusted = i + idx - offset;
                    Edge broken = Edge(t[current_node][k]);
                    t[current_node][k] = Edge(new_node, adjusted, offset);
                    t[new_node].push_back(Edge(broken.child, broken.start + offset, broken.length - offset));
                    t[new_node].push_back(Edge(new_node + 1, i + idx, n - i - idx));
                    lengths[new_node] = lengths[current_node] + offset;
                    lengths[new_node + 1] = lengths[new_node] + n - i - idx;
                    r_node[new_node] = true;
                    r_node[new_node + 1] = true;
                    ++new_node;
                    current_node = new_node;
                }

            }
            else
            {
                ++new_node;
                t[current_node].push_back(Edge(new_node, i + idx, n - i - idx));
                lengths[new_node] = lengths[current_node] + n - i - idx;
                r_node[new_node] = true;
                current_node = new_node;
            }
        }
    }

    r_node[0] = true;

    return { t, lengths, r_node };
}

string solve(string p, string q)
{
    string pq = "";
    pq.append(p).append("#").append(q).append("$");
    const int n = p.size();
    NodeEdge ne = ComputeSuffixTreeEdges(pq);

    tree& t = ne.t;
    map<int, int>& lengths = ne.lengths;
    map<int, bool>& r_node = ne.r_node;

    int shortest_length = n;
    int start = 0;
    int current_node;



    for (auto it = t.begin(); it != t.end(); it++)
    {
        if (r_node[it->first] && lengths[it->first] + 1 < shortest_length)
        {
            for (Edge& edge : it->second)
            {
                if (!r_node[edge.child] && edge.length != n + 2)
                {
                    shortest_length = lengths[it->first] + 1;
                    start = edge.start - lengths[it->first];
                    break;
                }
            }
        }
    }

    return p.substr(start, shortest_length);
}

int main(void)
{
    string p;
    cin >> p;
    string q;
    cin >> q;

    string ans = solve(p, q);

    cout << ans << endl;

    return 0;
}