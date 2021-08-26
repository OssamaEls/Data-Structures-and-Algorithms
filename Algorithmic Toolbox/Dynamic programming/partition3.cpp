//Input Format.The first line contains an integer 𝑛.The second line contains integers 𝑣1, 𝑣2, . . ., 𝑣𝑛 separated
//by spaces.
//Constraints. 1 ≤ 𝑛 ≤ 20, 1 ≤ 𝑣𝑖 ≤ 30 for all 𝑖.
//Output Format.Output 1, if it possible to partition 𝑣1, 𝑣2, . . ., 𝑣𝑛 into three subsets with equal sums, and
//0 otherwise.

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::vector;
using std::string;
using std::max;
using std::min;

typedef vector<vector<int>> matrix;

matrix optimal_weight(int W, const vector<int>& w) {
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
    return weights;
}


void previous(const matrix& weights, int i, int ww, const vector<int>& w, vector<string>& paths, int& num_paths)
{
    if (i == 0) return;
    if (ww == 0)
    {
        for (int k = 0; k < i; k++)
        {
            paths[num_paths - 1] = "0" + paths[num_paths - 1];
        }
        return;
    }
    string subpath = "";
    int prev_i, prev_ww;
    if (w[i - 1] <= ww)
    {
        if (weights[i][ww] == (weights[i - 1][ww - w[i - 1]] + w[i - 1]))
        {
            subpath = paths[num_paths - 1];
            paths[num_paths - 1] = "1" + subpath;
            prev_i = i;
            prev_ww = ww;
            ww = ww - w[i - 1];
            --i;
            previous(weights, i, ww, w, paths, num_paths);
            if ((weights[prev_i][prev_ww] == weights[prev_i - 1][prev_ww]))
            {
                ++num_paths;
                paths.push_back("0" + subpath);
                previous(weights, prev_i - 1, prev_ww, w, paths, num_paths);
            }
        }
        else
        {
            paths[num_paths - 1] = "0" + paths[num_paths - 1];
            --i;
            previous(weights, i, ww, w, paths, num_paths);
        }
    }
    else {
        paths[num_paths - 1] = "0" + paths[num_paths - 1];
        --i;
        previous(weights, i, ww, w, paths, num_paths);
    }
}

vector<string> backtrack(const matrix& weights, const vector<int>& w, int n, int W)
{
    int i = n, ww = W;
    vector<string> paths;
    paths.push_back("");
    int num_paths = 1;

    if (weights[n][W] == W)
    {
        previous(weights, i, ww, w, paths, num_paths);
    }

    return paths;
}

bool partition3(vector<int>& A) {
    int sum_elem = 0;
    for (auto& i : A)
    {
        sum_elem += i;
    }

    int p = A.size();
    if ((p < 3) || (sum_elem % 3 != 0) || (*std::max_element(A.begin(), A.end()) > sum_elem / 3)) return false;

    int n = sum_elem / 3;

    matrix weights = optimal_weight(n, A);



    matrix weightsB;
    if (weights[p][n] == n)
    {
        vector<string> paths = backtrack(weights, A, p, n);

        vector<int> B;
        for (int i = 0; i < paths.size(); i++)
        {
            for (int k = 0; k < paths[i].size(); k++)
            {
                if (paths[i][k] == '0')
                {
                    B.push_back(A[k]);
                }
            }
            weightsB = optimal_weight(n, B);
            if (weightsB[B.size()][n] == n)
            {
                return true;
            }
            B.erase(B.begin(), B.end());
        }
    }



    return false;
}

int main() {
    int n;
    std::cin >> n;
    vector<int> A(n);
    for (size_t i = 0; i < A.size(); ++i) {
        std::cin >> A[i];
    }
    std::cout << partition3(A) << '\n';
}


