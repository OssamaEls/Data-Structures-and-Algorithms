//Input Format.The input consists of a single integer 𝑛.
//Constraints. 1 ≤ 𝑛 ≤ 10^9.
//Output Format.In the first line, output the maximum number 𝑘 such that 𝑛 can be represented as a sum
//of 𝑘 pairwise distinct positive integers.In the second line, output 𝑘 pairwise distinct positive integers
//that sum up to 𝑛(if there are many such representations, output any of them).


#include <iostream>
#include <vector>

using std::vector;

vector<int> optimal_summands(int n) {
    vector<int> summands;
    int k{ 1 };
    while ((k + 1) * (k + 2) / 2 <= n)
    {
        summands.push_back(k);
        ++k;
    }
    summands.push_back(n - k * (k - 1) / 2);
    return summands;
}

int main() {
    int n;
    std::cin >> n;
    vector<int> summands = optimal_summands(n);
    std::cout << summands.size() << '\n';
    for (size_t i = 0; i < summands.size(); ++i) {
        std::cout << summands[i] << ' ';
    }
}