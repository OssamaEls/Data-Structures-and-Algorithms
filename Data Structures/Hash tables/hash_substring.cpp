//Input Format.There are two strings in the input : the pattern 𝑃and the text 𝑇.
//Constraints. 1 ≤ | 𝑃 | ≤ | 𝑇 | ≤ 5 · 10^5. The total length of all occurrences of 𝑃 in 𝑇 doesn’t exceed 10^8. The
//pattern and the text contain only latin letters.
//Output Format.Print all the positions of the occurrences of 𝑃 in 𝑇 in the ascending order.Use 0 - based
//indexing of positions in the the text 𝑇.

#include <iostream>
#include <string>
#include <vector>

using std::vector;
using std::string;
typedef std::int64_t ull;

struct Data {
    string pattern, text;
};

ull hash_func(const string& s) {
    static const ull multiplier = 263;
    static const ull prime = 1000000007;
    unsigned long long hash = 0;
    for (ull i = static_cast<ull>(s.size()) - 1; i >= 0; --i)
        hash = (hash * multiplier + s[i]) % prime;
    return hash;
}

vector<ull> precompute_hashes(string t, ull pl)
{
    static const ull multiplier = 263;
    static const ull prime = 1000000007;
    vector<ull> h(t.size() - pl + 1);
    string s = t.substr(t.size() - pl, pl);
    h[t.size() - pl] = hash_func(s);
    ull y = 1;
    for (ull i = 1; i <= pl; i++)
    {
        y = (y * multiplier) % prime;
    }

    for (ull i = static_cast<ull>(t.size()) - pl - 1; i >= 0; --i)
    {
        h[i] = (((multiplier * h[i + 1] + t[i] - y * t[i + pl]) % prime) + prime) % prime;
    }
    return h;
}

Data read_input() {
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

void print_occurrences(const std::vector<ull>& output) {
    for (ull i = 0; i < output.size(); ++i)
        std::cout << output[i] << " ";
    std::cout << "\n";
}

std::vector<ull> get_occurrences(const Data& input) {
    const string& s = input.pattern, t = input.text;
    std::vector<ull> ans;
    ull p_hash = hash_func(s);
    vector<ull> h = precompute_hashes(t, s.size());
    bool are_equal = false;
    for (ull i = 0; i + s.size() <= t.size(); ++i)
    {
        if (p_hash != h[i])
            continue;
        are_equal = true;
        for (ull j = i; j < i + s.size(); j++)
        {
            if (t[j] != s[j - i])
            {
                are_equal = false;
                break;
            }
        }
        if (are_equal) ans.push_back(i);
    }

    return ans;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    print_occurrences(get_occurrences(read_input()));
    return 0;
}
