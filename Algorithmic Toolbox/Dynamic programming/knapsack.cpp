//Input Format.The first line of the input contains the capacity 𝑊 of a knapsackand the number 𝑛 of bars
//of gold.The next line contains 𝑛 integers 𝑤0, 𝑤1, . . ., 𝑤𝑛−1 defining the weights of the bars of gold.
//Constraints. 1 ≤ 𝑊 ≤ 10^4; 1 ≤ 𝑛 ≤ 300; 0 ≤ 𝑤0, . . ., 𝑤𝑛−1 ≤ 10^5.
//Output Format.Output the maximum weight of gold that fits into a knapsack of capacity 𝑊.

#include <iostream>
#include <vector>

using std::vector;

int optimal_weight(int W, const vector<int>& w) {
    int n = w.size();
    vector<vector<int>> weights(n + 1, vector<int>(W + 1, 0));

    int current_weight = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= W; ++j)
        {
            weights[i][j] = weights[i - 1][j];
            if (w[i - 1] <= j)
            {
                current_weight = weights[i - 1][j - w[i - 1]] + w[i - 1];
                if (weights[i][j] < current_weight)
                {
                    weights[i][j] = current_weight;
                }
            }
        }
    }
    return weights[n][W];
}

int main() {
    int n, W;
    std::cin >> W >> n;
    vector<int> w(n);
    for (int i = 0; i < n; i++) {
        std::cin >> w[i];
    }
    std::cout << optimal_weight(W, w) << '\n';
}
