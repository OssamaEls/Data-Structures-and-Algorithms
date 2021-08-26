//Input Format.The first line of the input contains an integer 𝑛.The next line contains a sequence of 𝑛
//integers 𝑎0, 𝑎1, . . ., 𝑎𝑛−1.
//Constraints. 1 ≤ 𝑛 ≤ 10^5; 1 ≤ 𝑎𝑖 ≤ 10^9 for all 0 ≤ 𝑖 < 𝑛.
//Output Format.Output this sequence sorted in non - decreasing order.

#include <iostream>
#include <vector>
#include <cstdlib>
#include <tuple>

using std::vector;
using std::swap;
//
//int partition2(vector<int>& a, int l, int r) {
//    int x = a[l];
//    int j = l;
//    for (int i = l + 1; i <= r; i++) {
//        if (a[i] <= x) {
//            j++;
//            swap(a[i], a[j]);
//        }
//    }
//    swap(a[l], a[j]);
//    return j;
//}

//void randomized_quick_sort(vector<int>& a, int l, int r) {
//    if (l >= r) {
//        return;
//    }
//
//    int k = l + rand() % (r - l + 1);
//    swap(a[l], a[k]);
//    int m = partition2(a, l, r);
//
//    randomized_quick_sort(a, l, m - 1);
//    randomized_quick_sort(a, m + 1, r);
//}


std::tuple<int, int> partition3(vector<int>& a, int l, int r) {
    int x = a[l];
    int m1 = l;
    for (int i = l + 1; i <= r; i++) {
        if (a[i] < x) {
            m1++;
            swap(a[i], a[m1]);
        }
    }
    swap(a[l], a[m1]);

    int m2 = m1;
    for (int i = m1 + 1; i <= r; i++) {
        if (a[i] == x) {
            m2++;
            swap(a[i], a[m2]);
        }
    }
    swap(a[m1], a[m2]);
    return std::make_tuple(m1, m2);
}

void randomized_quick_sort(vector<int>& a, int l, int r) {
    if (l >= r) {
        return;
    }

    int k = l + rand() % (r - l + 1);
    swap(a[l], a[k]);
    std::tuple<int, int> m = partition3(a, l, r);

    randomized_quick_sort(a, l, std::get<0>(m) - 1);
    randomized_quick_sort(a, std::get<1>(m) + 1, r);
}


int main() {
    int n;
    std::cin >> n;
    vector<int> a(n);
    for (size_t i = 0; i < a.size(); ++i) {
        std::cin >> a[i];
    }
    randomized_quick_sort(a, 0, a.size() - 1);
    for (size_t i = 0; i < a.size(); ++i) {
        std::cout << a[i] << ' ';
    }
}