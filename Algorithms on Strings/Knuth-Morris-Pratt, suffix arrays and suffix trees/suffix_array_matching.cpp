//Input Format.The first line contains a string Text).The second line specifies an integer 𝑛.The last line
//gives a collection of 𝑛 strings Patterns = { 𝑝1, . . . , 𝑝𝑛 } separated by spaces.
//Constraints.All strings contain symbols A, C, G, T only; 1 ≤ | Text | ≤ 10^5; 1 ≤ 𝑛 ≤ 10^4; ∑︀𝑛 𝑖 = 1 | 𝑝𝑖 | ≤ 10^5.
//Output Format.All starting positions(in any order) in Text where a pattern appears as a substring(using
//    0 - based indexing as usual).If several patterns occur at the same position of the Text, still output this
//    position only once.

#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
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


vector<int> FindOccurrences(const string& pattern, const string& text, const vector<int>& suffix_array) {
    vector<int> result;

    // write your code here
    const int n = text.size();
    const int p = pattern.size();

    int min_index = 0;
    int max_index = n;
    int mid_index;

    string str;

    while (min_index < max_index)
    {
        mid_index = (min_index + max_index) / 2;

        if (n - suffix_array[mid_index] >= p)
            str = text.substr(suffix_array[mid_index], p);
        else
            str = text.substr(suffix_array[mid_index]);

        if (pattern > str)
            min_index = mid_index + 1;
        else
            max_index = mid_index;
    }

    int start = min_index;
    max_index = n;

    while (min_index < max_index)
    {
        mid_index = (min_index + max_index) / 2;

        if (n - suffix_array[mid_index] >= p)
            str = text.substr(suffix_array[mid_index], p);
        else
            str = text.substr(suffix_array[mid_index]);

        if (pattern < str)
            max_index = mid_index;
        else
            min_index = mid_index + 1;
    }

    int end = max_index;

    for (int i = start; i < end; i++)
    {
        result.push_back(suffix_array[i]);
    }

    return result;
}

int main() {
    char buffer[100001];
    scanf("%s", buffer);
    string text = buffer;
    text += '$';
    vector<int> suffix_array = BuildSuffixArray(text);
    int pattern_count;
    scanf("%d", &pattern_count);
    vector<bool> occurs(text.length(), false);
    for (int pattern_index = 0; pattern_index < pattern_count; ++pattern_index) {
        scanf("%s", buffer);
        string pattern = buffer;
        vector<int> occurrences = FindOccurrences(pattern, text, suffix_array);
        for (int j = 0; j < occurrences.size(); ++j) {
            occurs[occurrences[j]] = true;
        }
    }
    for (int i = 0; i < occurs.size(); ++i) {
        if (occurs[i]) {
            printf("%d ", i);
        }
    }
    printf("\n");
    return 0;
}