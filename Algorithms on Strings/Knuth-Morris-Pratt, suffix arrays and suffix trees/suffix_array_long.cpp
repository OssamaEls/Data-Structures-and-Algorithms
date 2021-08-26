//Input Format.A string Text ending with a “$” symbol.
//Constraints. 1 ≤ | Text(Text) | ≤ 2·10^5; except for the last symbol, Text contains symbols A, C, G, T only.
//Output Format.SuffixArray(Text), that is, the list of starting positions of sorted suffixes separated by
//spaces.

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

const int NUM_LETTERS = 5;

int letterToIndex(char letter)
{
    switch (letter)
    {
    case '$': return 0; break;
    case 'A': return 1; break;
    case 'C': return 2; break;
    case 'G': return 3; break;
    case 'T': return 4; break;
    default: return -1; break;
    }
}

vector<int> sort_characters(const string& text)
{
    const int n = text.size();
    vector<int> order(n);
    vector<int> count(NUM_LETTERS);

    for (size_t i = 0; i < n; i++)
    {
        count[letterToIndex(text[i])]++;
    }

    for (size_t j = 1; j < NUM_LETTERS; j++)
    {
        count[j] = count[j] + count[j - 1];
    }

    for (int i = n - 1; i > -1; i--)
    {
        --count[letterToIndex(text[i])];
        order[count[letterToIndex(text[i])]] = i;
    }

    return order;
}

vector<int> compute_char_classes(const string& text, vector<int>& order)
{
    const int n = text.size();
    vector<int> c_class(n);
    c_class[order[0]] = 0;
    for (size_t i = 1; i < n; i++)
    {
        c_class[order[i]] = (text[order[i]] != text[order[i - 1]]) ? c_class[order[i - 1]] + 1 : c_class[order[i - 1]];
    }
    return c_class;
}

vector<int> sort_doubled(const string& text, int l, vector<int>& order, vector<int>& c_class)
{
    const int n = text.size();
    vector<int> count(n);
    vector<int> new_order(n);

    for (size_t i = 0; i < n; i++)
    {
        ++count[c_class[i]];
    }

    for (size_t j = 1; j < n; j++)
    {
        count[j] = count[j] + count[j - 1];
    }

    int start, cl;
    for (int i = n - 1; i > -1; i--)
    {
        start = (order[i] - l + n) % n;
        cl = c_class[start];
        --count[cl];
        new_order[count[cl]] = start;
    }

    return new_order;
}

vector<int> update_classes(vector<int>& new_order, vector<int>& c_class, int l)
{
    const int n = new_order.size();
    vector<int> new_class(n);
    new_class[new_order[0]] = 0;

    int cur, prev, mid, mid_prev;
    for (size_t i = 1; i < n; i++)
    {
        cur = new_order[i];
        prev = new_order[i - 1];
        mid = (cur + l) % n;
        mid_prev = (prev + l) % n;

        if (c_class[cur] != c_class[prev] || c_class[mid] != c_class[mid_prev])
        {
            new_class[cur] = new_class[prev] + 1;
        }
        else
        {
            new_class[cur] = new_class[prev];
        }
    }

    return new_class;
}

// Build suffix array of the string text and
// return a vector result of the same length as the text
// such that the value result[i] is the index (0-based)
// in text where the i-th lexicographically smallest
// suffix of text starts.
vector<int> BuildSuffixArray(const string& text) {
    vector<int> order = sort_characters(text);
    // Implement this function yourself
    vector<int> c_class = compute_char_classes(text, order);
    int l = 1;
    const int n = text.size();

    while (l < n)
    {
        order = sort_doubled(text, l, order, c_class);
        c_class = update_classes(order, c_class, l);
        l = 2 * l;
    }

    return order;
}

int main() {
    string text;
    cin >> text;
    vector<int> suffix_array = BuildSuffixArray(text);
    for (int i = 0; i < suffix_array.size(); ++i) {
        cout << suffix_array[i] << ' ';
    }

    cout << endl;
    return 0;
}
