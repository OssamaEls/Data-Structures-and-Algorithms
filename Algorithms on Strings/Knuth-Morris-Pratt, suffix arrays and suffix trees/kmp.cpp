//Input Format.Strings 𝑃 𝑎𝑡𝑡𝑒𝑟𝑛and 𝐺𝑒𝑛𝑜𝑚𝑒.
//Constraints. 1 ≤ | 𝑃 𝑎𝑡𝑡𝑒𝑟𝑛 | ≤ 10^6; 1 ≤ | 𝐺𝑒𝑛𝑜𝑚𝑒 | ≤ 10^6; both strings are over A, C, G, T.
//Output Format.All starting positions in 𝐺𝑒𝑛𝑜𝑚𝑒 where 𝑃 𝑎𝑡𝑡𝑒𝑟𝑛 appears as a substring(using 0 - based
//    indexing as usual).

#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::string;
using std::vector;

vector<size_t> compute_prefix_function(const string& pattern)
{
    const size_t n = pattern.size();
    vector<size_t> s(n);
    size_t border = 0;
    for (size_t i = 1; i < n; i++)
    {
        while (border > 0 && pattern[i] != pattern[border])
            border = s[border - 1];

        if (pattern[i] == pattern[border])
            ++border;
        else
            border = 0;

        s[i] = border;
    }

    return s;
}

// Find all occurrences of the pattern in the text and return a
// vector with all positions in the text (starting from 0) where 
// the pattern starts in the text.
vector<size_t> find_pattern(const string& pattern, const string& text) {
    vector<size_t> result;
    // Implement this function yourself

    const size_t n = pattern.size();
    string pattern_with_text;

    pattern_with_text.append(pattern).append("$").append(text);

    vector<size_t> s = compute_prefix_function(pattern_with_text);
    for (size_t i = n + 1; i < pattern_with_text.size(); i++)
    {
        if (s[i] == n) result.push_back(i - 2 * n);
    }

    return result;
}

int main() {
    string pattern, text;
    cin >> pattern;
    cin >> text;
    vector<size_t> result = find_pattern(pattern, text);
    for (size_t i = 0; i < result.size(); ++i) {
        printf("%d ", result[i]);
    }
    printf("\n");
    return 0;
}
