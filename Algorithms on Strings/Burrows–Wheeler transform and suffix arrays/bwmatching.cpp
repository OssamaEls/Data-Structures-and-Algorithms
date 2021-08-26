//Input Format.A string BWT(Text), followed by an integer 𝑛and a collection of 𝑛 strings Patterns =
//{ 𝑝1, . . . , 𝑝𝑛 } (on one line separated by spaces).
//Constraints. 1 ≤ | BWT(Text) | ≤ 10^6; except for the one $ symbol, BWT(Text) contains symbols A, C,
//G, T only; 1 ≤ 𝑛 ≤ 5 000; for all 1 ≤ 𝑖 ≤ 𝑛, 𝑝𝑖 is a string over A, C, G, T; 1 ≤ | 𝑝𝑖 | ≤ 1 000.
//Output Format.A list of integers, where the 𝑖 - th integer corresponds to the number of substring matches
//of the 𝑖 - th member of Patterns in Text.

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using std::cin;
using std::istringstream;
using std::map;
using std::string;
using std::vector;

// Preprocess the Burrows-Wheeler Transform bwt of some text
// and compute as a result:
//   * starts - for each character C in bwt, starts[C] is the first position 
//       of this character in the sorted array of 
//       all characters of the text.
//   * occ_count_before - for each character C in bwt and each position P in bwt,
//       occ_count_before[C][P] is the number of occurrences of character C in bwt
//       from position 0 to position P inclusive.
void PreprocessBWT(const string& bwt,
    map<char, int>& starts,
    map<char, vector<int> >& occ_count_before) {
    // Implement this function yourself

    const size_t n = bwt.size();

    const string possible_chars = "$ACGT";

    for (auto& c : possible_chars)
    {
        occ_count_before[c].resize(n + 1);
    }

    map<char, int> count;

    for (size_t i = 0; i < n; i++)
    {
        ++count[bwt[i]];
        for (auto& c : possible_chars)
        {
            occ_count_before[c][i + 1] = occ_count_before[c][i];
        }
        occ_count_before[bwt[i]][i + 1] = occ_count_before[bwt[i]][i] + 1;
    }

    starts['$'] = 0;
    starts['A'] = 1;
    starts['C'] = starts['A'] + count['A'];
    starts['G'] = starts['C'] + count['C'];
    starts['T'] = starts['G'] + count['G'];
}

// Compute the number of occurrences of string pattern in the text
// given only Burrows-Wheeler Transform bwt of the text and additional
// information we get from the preprocessing stage - starts and occ_counts_before.
int CountOccurrences(const string& pattern,
    const string& bwt,
    const map<char, int>& starts,
    const map<char, vector<int> >& occ_count_before) {
    // Implement this function yourself

    const size_t p = pattern.size();
    const size_t n = bwt.size();
    const string possible_chars = "$ACGT";

    int top = 0;
    int bottom = n - 1;
    char letter;

    for (size_t i = p; i > 0; i--)
    {
        letter = pattern[i - 1];

        if ((occ_count_before.at(letter)[bottom + 1] - occ_count_before.at(letter)[top]) > 0)
        {
            top = starts.at(letter) + occ_count_before.at(letter)[top];
            bottom = starts.at(letter) + occ_count_before.at(letter)[bottom + 1] - 1;
        }
        else
        {
            return 0;
        }
    }

    return bottom - top + 1;
}


int main() {
    string bwt;
    cin >> bwt;
    int pattern_count;
    cin >> pattern_count;
    // Start of each character in the sorted list of characters of bwt,
    // see the description in the comment about function PreprocessBWT
    map<char, int> starts;
    // Occurrence counts for each character and each position in bwt,
    // see the description in the comment about function PreprocessBWT
    map<char, vector<int>> occ_count_before;
    // Preprocess the BWT once to get starts and occ_count_before.
    // For each pattern, we will then use these precomputed values and
    // spend only O(|pattern|) to find all occurrences of the pattern
    // in the text instead of O(|pattern| + |text|).
    PreprocessBWT(bwt, starts, occ_count_before);
    for (int pi = 0; pi < pattern_count; ++pi) {
        string pattern;
        cin >> pattern;
        int occ_count = CountOccurrences(pattern, bwt, starts, occ_count_before);
        printf("%d ", occ_count);
    }
    printf("\n");

    return 0;
}