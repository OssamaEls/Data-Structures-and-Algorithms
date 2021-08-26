//Input Format.A string Text ending with a “$” symbol.
//Constraints. 1 ≤ | Text(Text) | ≤ 10^4; except for the last symbol, Text contains symbols A, C, G, T only.
//Output Format.SuffixArray(Text), that is, the list of starting positions(0 - based) of sorted suffixes separated by spaces.

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <utility>

using std::cin;
using std::cout;
using std::endl;
using std::make_pair;
using std::pair;
using std::string;
using std::vector;

// Build suffix array of the string text and
// return a vector result of the same length as the text
// such that the value result[i] is the index (0-based)
// in text where the i-th lexicographically smallest
// suffix of text starts.
vector<size_t> BuildSuffixArray(const string& text) {

    // Implement this function yourself
    vector<size_t> result;
    vector<string> suffixes;
    const size_t n = text.size();

    for (size_t i = 0; i < n; i++)
    {
        suffixes.push_back(text.substr(i));
        result.push_back(i);
    }

    std::stable_sort(result.begin(), result.end(),
        [&suffixes](size_t i1, size_t i2) {return suffixes[i1] < suffixes[i2]; });


    return result;
}

int main() {
    string text;
    cin >> text;
    vector<size_t> suffix_array = BuildSuffixArray(text);
    for (int i = 0; i < suffix_array.size(); ++i) {
        cout << suffix_array[i] << ' ';
    }
    cout << endl;
    return 0;
}