//Input Format.The first line contains two non - negative integers 𝑠 and 𝑝 defining the number of segments
//and the number of points on a line, respectively.The next 𝑠 lines contain two integers 𝑎𝑖, 𝑏𝑖 defining
//the 𝑖 - th segment[𝑎𝑖, 𝑏𝑖].The next line contains 𝑝 integers defining points 𝑥1, 𝑥2, . . ., 𝑥𝑝.
//Constraints. 1 ≤ 𝑠, 𝑝 ≤ 50000; −10^8 ≤ 𝑎𝑖 ≤ 𝑏𝑖 ≤ 10^8 for all 0 ≤ 𝑖 < 𝑠; −10^8 ≤ 𝑥𝑗 ≤ 10^8 for all 0 ≤ 𝑗 < 𝑝.
//Output Format.Output 𝑝 non - negative integers 𝑘0, 𝑘1, . . ., 𝑘𝑝−1 where 𝑘𝑖 is the number of segments which
//contain 𝑥𝑖.More formally,
//    𝑘𝑖 = | {𝑗: 𝑎𝑗 ≤ 𝑥𝑖 ≤ 𝑏𝑗} | .

#include <algorithm>
#include <iostream>
#include <numeric>      // std::iota
#include <utility>
#include <vector>

using std::vector;
using std::pair;

template <typename T>
vector<size_t> sort_indexes(const vector<T>& v) {

    // initialize original index locations
    vector<size_t> idx(v.size());
    iota(idx.begin(), idx.end(), 0);

    // sort indexes based on comparing values in v
    // using std::stable_sort instead of std::sort
    // to avoid unnecessary index re-orderings
    // when v contains elements of equal values 
    stable_sort(idx.begin(), idx.end(),
        [&v](size_t i1, size_t i2) {return v[i1] < v[i2]; });

    return idx;
}

vector<int> fast_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {
    vector<int> count(points.size());
    int n = starts.size();
    int m = points.size();
    vector<pair<int, int>> all_p(2 * n + m);

    for (size_t i = 0; i < n; i++)
    {
        all_p[i] = { starts[i],0 };
    }

    for (size_t i = 0; i < n; i++)
    {
        all_p[i + n] = { ends[i],2 };
    }


    for (size_t i = 0; i < m; i++)
    {
        all_p[i + 2 * n] = { points[i],1 };
    }

    vector<size_t> idx = sort_indexes(points);

    std::sort(all_p.begin(), all_p.end(), [](const pair<int, int> a, const pair<int, int> b)
        {
            return (a.first != b.first) ? (a.first < b.first) : (a.second < b.second);
        });

    int num_seg = 0;
    int kth_point = 0;
    for (size_t i = 0; i < all_p.size(); i++)
    {
        if (all_p[i].second == 0)
        {
            ++num_seg;
        }
        else {
            if (all_p[i].second == 2)
            {
                --num_seg;
            }
            else {
                count[idx[kth_point]] = num_seg;
                ++kth_point;
            }
        }
    }

    return count;
}

vector<int> naive_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {
    vector<int> cnt(points.size());
    for (size_t i = 0; i < points.size(); i++) {
        for (size_t j = 0; j < starts.size(); j++) {
            cnt[i] += starts[j] <= points[i] && points[i] <= ends[j];
        }
    }
    return cnt;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    vector<int> starts(n), ends(n);
    for (size_t i = 0; i < starts.size(); i++) {
        std::cin >> starts[i] >> ends[i];
    }
    vector<int> points(m);
    for (size_t i = 0; i < points.size(); i++) {
        std::cin >> points[i];
    }
    //use fast_count_segments
    vector<int> cnt = fast_count_segments(starts, ends, points);
    for (size_t i = 0; i < cnt.size(); i++) {
        std::cout << cnt[i] << ' ';
    }
}
