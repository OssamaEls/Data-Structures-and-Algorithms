//Input Format.The first line of the input contains the number 𝑛 of itemsand the capacity 𝑊 of a knapsack.
//The next 𝑛 lines define the valuesand weights of the items.The 𝑖 - th line contains integers 𝑣𝑖 and 𝑤𝑖—the
//value and the weight of 𝑖 - th item, respectively.
//Constraints. 1 ≤ 𝑛 ≤ 10^3, 0 ≤ 𝑊 ≤ 2 · 10^6; 0 ≤ 𝑣𝑖 ≤ 2 · 10^6, 0 < 𝑤𝑖 ≤ 2 · 10^6 for all 1 ≤ 𝑖 ≤ 𝑛.All the
//    numbers are integers.
//    Output Format.Output the maximal value of fractions of items that fit into the knapsack.The absolute
//    value of the difference between the answer of your program and the optimal value should be at most
//    10−3.To ensure this, output your answer with at least four digits after the decimal point

#include <algorithm>
#include <iostream>
#include <vector>
#include <numeric>


using std::vector;

template <typename T>
vector<size_t> sort_indexes(const vector<T>& v) {

    // initialize original index locations
    vector<size_t> idx(v.size());
    std::iota(idx.begin(), idx.end(), 0);

    // sort indexes based on comparing values in v
    // using std::stable_sort instead of std::sort
    // to avoid unnecessary index re-orderings
    // when v contains elements of equal values 
    std::stable_sort(idx.begin(), idx.end(),
        [&v](size_t i1, size_t i2) {return v[i1] > v[i2]; });

    return idx;
}

double get_optimal_value(int& capacity, vector<int>& weights, vector<int>& values) {
    double value = 0.0;

    vector<double> vi_wi(weights.size());
    for (int i = 0; i < weights.size(); i++)
    {
        vi_wi[i] = static_cast<double>(values[i]) / weights[i];
    }

    vector<size_t> idx_greater{ sort_indexes(vi_wi) };

    int budget{ 0 };
    for (int i = 0; i < vi_wi.size(); i++)
    {
        if (capacity == 0) return value;
        budget = std::min(weights[idx_greater[i]], capacity);
        value += budget * vi_wi[idx_greater[i]];
        weights[idx_greater[i]] -= budget;
        capacity -= budget;
    }

    return value;
}

int main() {
    int n;
    int capacity;
    std::cin >> n >> capacity;
    vector<int> values(n);
    vector<int> weights(n);
    for (int i = 0; i < n; i++) {
        std::cin >> values[i] >> weights[i];
    }

    double optimal_value = get_optimal_value(capacity, weights, values);

    std::cout.precision(10);
    std::cout << std::fixed << optimal_value << std::endl;
    return 0;
}