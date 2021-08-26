//Input Format.The first line of the input contains an integer 𝑛and a sequence 𝑎0 < 𝑎1 < . . . < 𝑎𝑛−1
//    of 𝑛 pairwise distinct positive integers in increasing order.The next line contains an integer 𝑘and 𝑘
//    positive integers 𝑏0, 𝑏1, . . ., 𝑏𝑘−1.
//Constraints. 1 ≤ 𝑘 ≤ 10^5; 1 ≤ 𝑛 ≤ 3 · 10^4; 1 ≤ 𝑎𝑖 ≤ 10^9 for all 0 ≤ 𝑖 < 𝑛; 1 ≤ 𝑏𝑗 ≤ 10^9 for all 0 ≤ 𝑗 < 𝑘;
//Output Format.For all 𝑖 from 0 to 𝑘 − 1, output an index 0 ≤ 𝑗 ≤ 𝑛 − 1 such that 𝑎𝑗 = 𝑏𝑖 or −1 if there
//is no such index.

#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>

using std::vector;

int binary_search(const vector<int>& a, int x) {
    int left = 0, right = (int)a.size() - 1;
    int mid;
    while (left <= right)
    {
        mid = left + (right - left) / 2;
        if (x == a[mid])
        {
            return mid;
        }
        else {
            if (x < a[mid])
            {
                right = mid - 1;
            }
            else
            {
                left = mid + 1;
            }
        }
    }
    return -1;
}

int linear_search(const vector<int>& a, int x) {
    for (size_t i = 0; i < a.size(); ++i) {
        if (a[i] == x) return i;
    }
    return -1;
}

int main() {
    int n;
    std::cin >> n;
    vector<int> a(n);
    for (size_t i = 0; i < a.size(); i++) {
        std::cin >> a[i];
    }
    std::sort(a.begin(), a.end());
    int m;
    std::cin >> m;
    vector<int> b(m);
    for (int i = 0; i < m; ++i) {
        std::cin >> b[i];
    }
    for (int i = 0; i < m; ++i) {
        std::cout << binary_search(a, b[i]) << ' ';
    }
}