//Input Format.The first line contains the number of vertices 𝑛.The vertices of the tree are numbered
//from 0 to 𝑛 − 1. Vertex 0 is the root.
//The next 𝑛 lines contain information about vertices 0, 1, ..., 𝑛−1 in order.Each of these lines contains
//three integers 𝑘𝑒𝑦𝑖, 𝑙𝑒𝑓𝑡𝑖and 𝑟𝑖𝑔ℎ𝑡𝑖 — 𝑘𝑒𝑦𝑖 is the key of the 𝑖 - th vertex, 𝑙𝑒𝑓𝑡𝑖 is the index of the left
//child of the 𝑖 - th vertex, and 𝑟𝑖𝑔ℎ𝑡𝑖 is the index of the right child of the 𝑖 - th vertex.If 𝑖 doesn’t have
//left or right child(or both), the corresponding 𝑙𝑒𝑓𝑡𝑖 or 𝑟𝑖𝑔ℎ𝑡𝑖(or both) will be equal to −1.
//Constraints. 1 ≤ 𝑛 ≤ 10^5; 0 ≤ 𝑘𝑒𝑦𝑖 ≤ 10^9; −1 ≤ 𝑙𝑒𝑓𝑡𝑖, 𝑟𝑖𝑔ℎ𝑡𝑖 ≤ 𝑛 − 1. It is guaranteed that the input
//represents a valid binary tree.In particular, if 𝑙𝑒𝑓𝑡𝑖 ̸ = −1 and 𝑟𝑖𝑔ℎ𝑡𝑖 ̸ = −1, then 𝑙𝑒𝑓𝑡𝑖 ̸ = 𝑟𝑖𝑔ℎ𝑡𝑖.Also,
//a vertex cannot be a child of two different vertices.Also, each vertex is a descendant of the root vertex.
//Output Format.Print three lines.The first line should contain the keys of the vertices in the in - order
//traversal of the tree.The second line should contain the keys of the vertices in the pre - order traversal
//of the tree.The third line should contain the keys of the vertices in the post - order traversal of the tree.

#include <iostream>
#include <vector>
#include <algorithm>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

using std::vector;
using std::ios_base;
using std::cin;
using std::cout;

class TreeOrders {
    int n;
    vector <int> key;
    vector <int> left;
    vector <int> right;

public:
    void read() {
        cin >> n;
        key.resize(n);
        left.resize(n);
        right.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> key[i] >> left[i] >> right[i];
        }
    }

    void in_order_traversal(int i, vector<int>& result)
    {
        if (i == -1) return;
        in_order_traversal(left[i], result);
        result.push_back(key[i]);
        in_order_traversal(right[i], result);
    }

    vector <int> in_order() {
        vector<int> result;
        // Finish the implementation
        // You may need to add a new recursive method to do that
        int i = 0;
        in_order_traversal(i, result);
        return result;
    }

    void pre_order_traversal(int i, vector<int>& result)
    {
        if (i == -1) return;
        result.push_back(key[i]);
        pre_order_traversal(left[i], result);
        pre_order_traversal(right[i], result);
    }

    vector <int> pre_order() {
        vector<int> result;
        // Finish the implementation
        // You may need to add a new recursive method to do that
        int i = 0;
        pre_order_traversal(i, result);
        return result;
    }

    void post_order_traversal(int i, vector<int>& result)
    {
        if (i == -1) return;
        post_order_traversal(left[i], result);
        post_order_traversal(right[i], result);
        result.push_back(key[i]);
    }

    vector <int> post_order() {
        vector<int> result;
        // Finish the implementation
        // You may need to add a new recursive method to do that
        int i = 0;
        post_order_traversal(i, result);
        return result;
    }
};

void print(vector <int> a) {
    for (size_t i = 0; i < a.size(); i++) {
        if (i > 0) {
            cout << ' ';
        }
        cout << a[i];
    }
    cout << '\n';
}

int main_with_large_stack_space() {
    ios_base::sync_with_stdio(0);
    TreeOrders t;
    t.read();
    print(t.in_order());
    print(t.pre_order());
    print(t.post_order());
    return 0;
}

int main(int argc, char** argv)
{
#if defined(__unix__) || defined(__APPLE__)
    // Allow larger stack space
    const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
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
                std::cerr << "setrlimit returned result = " << result << std::endl;
            }
        }
    }
#endif

    return main_with_large_stack_space();
}

