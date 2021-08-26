//Input Format.The first line contains the number of vertices 𝑛.The vertices of the tree are numbered
//from 0 to 𝑛 − 1. Vertex 0 is the root.
//The next 𝑛 lines contain information about vertices 0, 1, ..., 𝑛−1 in order.Each of these lines contains
//three integers 𝑘𝑒𝑦𝑖, 𝑙𝑒𝑓𝑡𝑖and 𝑟𝑖𝑔ℎ𝑡𝑖 — 𝑘𝑒𝑦𝑖 is the key of the 𝑖 - th vertex, 𝑙𝑒𝑓𝑡𝑖 is the index of the left
//child of the 𝑖 - th vertex, and 𝑟𝑖𝑔ℎ𝑡𝑖 is the index of the right child of the 𝑖 - th vertex.If 𝑖 doesn’t have
//left or right child(or both), the corresponding 𝑙𝑒𝑓𝑡𝑖 or 𝑟𝑖𝑔ℎ𝑡𝑖(or both) will be equal to −1.
//Constraints. 0 ≤ 𝑛 ≤ 10^5; −2^31 < 𝑘𝑒𝑦𝑖 < 2^31 − 1; −1 ≤ 𝑙𝑒𝑓𝑡𝑖, 𝑟𝑖𝑔ℎ𝑡𝑖 ≤ 𝑛 − 1. It is guaranteed that the
//input represents a valid binary tree.In particular, if 𝑙𝑒𝑓𝑡𝑖 ̸ = −1 and 𝑟𝑖𝑔ℎ𝑡𝑖 ̸ = −1, then 𝑙𝑒𝑓𝑡𝑖 ̸ = 𝑟𝑖𝑔ℎ𝑡𝑖.
//Also, a vertex cannot be a child of two different vertices.Also, each vertex is a descendant of the root
//vertex.All keys in the input will be different.
//Output Format.If the given binary tree is a correct binary search tree(see the definition in the problem
//description), output one word “CORRECT”(without quotes).Otherwise, output one word “INCORRECT”(without quotes).

#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Node {
    int key;
    int left;
    int right;

    Node() : key(0), left(-1), right(-1) {}
    Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

void in_order_traversal(int i, const vector<Node>& tree, vector<int>& result)
{
    if (i == -1) return;
    in_order_traversal(tree[i].left, tree, result);
    result.push_back(tree[i].key);
    in_order_traversal(tree[i].right, tree, result);
}

bool IsBinarySearchTree(const vector<Node>& tree) {
    // Implement correct algorithm here
    vector<int> result;
    int i = 0;
    if (!tree.empty())
    {
        in_order_traversal(i, tree, result);
        return std::is_sorted(result.begin(), result.end());
    }
    return true;
}

int main() {
    int nodes;
    cin >> nodes;
    vector<Node> tree;
    for (int i = 0; i < nodes; ++i) {
        int key, left, right;
        cin >> key >> left >> right;
        tree.push_back(Node(key, left, right));
    }
    if (IsBinarySearchTree(tree)) {
        cout << "CORRECT" << endl;
    }
    else {
        cout << "INCORRECT" << endl;
    }
    return 0;
}
