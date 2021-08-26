//Input Format.The first line of the input contains single integer 𝑛.The next line contains 𝑛 space - separated
//integers 𝑎𝑖.
//Constraints. 1 ≤ 𝑛 ≤ 100 000; 0 ≤ 𝑖, 𝑗 ≤ 𝑛 − 1; 0 ≤ 𝑎0, 𝑎1, . . ., 𝑎𝑛−1 ≤ 10^9. All 𝑎𝑖 are distinct.
//Output Format.The first line of the output should contain single integer 𝑚 — the total number of swaps.
//𝑚 must satisfy conditions 0 ≤ 𝑚 ≤ 4𝑛.The next 𝑚 lines should contain the swap operations used
//to convert the array 𝑎 into a heap.Each swap is described by a pair of integers 𝑖, 𝑗 — the 0 - based
//indices of the elements to be swapped.After applying all the swaps in the specified order the array
//must become a heap, that is, for each 𝑖 where 0 ≤ 𝑖 ≤ 𝑛 − 1 the following conditions must be true:
//    1. If 2𝑖 + 1 ≤ 𝑛 − 1, then 𝑎𝑖 < 𝑎2𝑖 + 1.
//    2. If 2𝑖 + 2 ≤ 𝑛 − 1, then 𝑎𝑖 < 𝑎2𝑖 + 2.
//Note that all the elements of the input array are distinct.Note that any sequence of swaps that has
//length at most 4𝑛 and after which your initial array becomes a correct heap will be graded as correct.

#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

class HeapBuilder {
private:
    vector<int> data_;
    vector< pair<int, int> > swaps_;

    void WriteResponse() const {
        cout << swaps_.size() << "\n";
        for (int i = 0; i < swaps_.size(); ++i) {
            cout << swaps_[i].first << " " << swaps_[i].second << "\n";
        }
    }

    void ReadData() {
        int n;
        cin >> n;
        data_.resize(n);
        for (int i = 0; i < n; ++i)
            cin >> data_[i];
    }

    int Parent(int i)
    {
        return (i - 1) / 2;
    }

    int LeftChild(int i)
    {
        return 2 * i + 1;
    }

    int RightChild(int i)
    {
        return 2 * i + 2;
    }

    void SiftDown(int i)
    {
        int minIndex = i;
        int l = LeftChild(i);
        if (l < data_.size() && data_[l] < data_[minIndex]) minIndex = l;
        int r = RightChild(i);
        if (r < data_.size() && data_[r] < data_[minIndex]) minIndex = r;
        if (i != minIndex)
        {
            swap(data_[i], data_[minIndex]);
            swaps_.push_back({ i,minIndex });
            SiftDown(minIndex);
        }
    }

    void GenerateSwaps() {
        swaps_.clear();
        // The following naive implementation just sorts 
        // the given sequence using selection sort algorithm
        // and saves the resulting sequence of swaps.
        // This turns the given array into a heap, 
        // but in the worst case gives a quadratic number of swaps.
        //
        // TODO: replace by a more efficient implementation
        //for (int i = 0; i < data_.size(); ++i)
        //    for (int j = i + 1; j < data_.size(); ++j) {
        //        if (data_[i] > data_[j]) {
        //            swap(data_[i], data_[j]);
        //            swaps_.push_back(make_pair(i, j));
        //        }
        //    }

        for (int i = (data_.size() - 1) / 2; i > -1; --i)
        {
            SiftDown(i);
        }

    }

public:
    void Solve() {
        ReadData();
        GenerateSwaps();
        WriteResponse();
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    HeapBuilder heap_builder;
    heap_builder.Solve();
    return 0;
}
