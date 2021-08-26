//Input Format.The first line contains an integer 𝑛, the next one contains a sequence of 𝑛 non - negative
//integers 𝑎0, 𝑎1, . . ., 𝑎𝑛−1.
//Constraints. 1 ≤ 𝑛 ≤ 10^5; 0 ≤ 𝑎𝑖 ≤ 10^9 for all 0 ≤ 𝑖 < 𝑛.
//Output Format.Output 1 if the sequence contains an element that appears strictly more than 𝑛 / 2 times,
//    and 0 otherwise.

#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;

//int get_majority_element(vector<int>& a, int left, int right) {
//    if (left == right) return -1;
//    if (left + 1 == right) return a[left];
//    //write your code here
//    return -1;
//}

int get_majority_element(vector<int>& a) {
    int n{ static_cast<int>(a.size()) };
    if (n == 1) return 1;

    int index{ n / 2 };
    int elem{ a[index] };
    int count{ 0 };

    while (a[index] == elem)
    {
        --index;
        ++count;
        if (index < 0) break;
    }

    index = n / 2 + 1;
    while (a[index] == elem)
    {
        ++index;
        ++count;
        if (index > n) break;
    }

    return (count > n / 2) ? 1 : 0;
}

int main() {
    int n;
    std::cin >> n;
    vector<int> a(n);
    for (size_t i = 0; i < a.size(); ++i) {
        std::cin >> a[i];
    }
    std::sort(a.begin(), a.end());
    //std::cout << (get_majority_element(a, 0, a.size()) != -1) << '\n';
    std::cout << get_majority_element(a) << '\n';
}