//Input Format.The first line of the input contains a string Text, the second line contains an integer 𝑛,
//each of the following 𝑛 lines contains a pattern from Patterns = { 𝑝1, . . . , 𝑝𝑛 }.
//Constraints. 1 ≤ | Text | ≤ 10 000; 1 ≤ 𝑛 ≤ 5 000; 1 ≤ | 𝑝𝑖 | ≤ 100 for all 1 ≤ 𝑖 ≤ 𝑛; all strings contain only
//symbols A, C, G, T; no 𝑝𝑖 is a prefix of 𝑝𝑗 for all 1 ≤ 𝑖 ̸ = 𝑗 ≤ 𝑛.
//Output Format.All starting positions in Text where a string from Patterns appears as a substring in
//increasing order(assuming that Text is a 0 - based array of symbols).

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int const Letters = 4;
int const NA = -1;

typedef map<char, int> edges;
typedef vector<edges> trie;

trie build_trie(vector<string>& patterns) {
	trie t;
	// write your code here
	const size_t n = patterns.size();

	size_t current_node;
	size_t new_node = 0;
	t.push_back({});

	for (const auto& pattern : patterns)
	{
		current_node = 0;
		for (const auto& symbol : pattern)
		{
			if (t[current_node].find(symbol) != t[current_node].end())
			{
				current_node = t[current_node][symbol];
			}
			else
			{
				new_node = t.size();
				t[current_node][symbol] = new_node;
				current_node = new_node;
				t.push_back({});
			}
		}
	}

	return t;
}

struct Node
{
	int next[Letters];

	Node()
	{
		fill(next, next + Letters, NA);
	}

	bool isLeaf() const
	{
		return (next[0] == NA && next[1] == NA && next[2] == NA && next[3] == NA);
	}
};

int letterToIndex(char letter)
{
	switch (letter)
	{
	case 'A': return 0; break;
	case 'C': return 1; break;
	case 'G': return 2; break;
	case 'T': return 3; break;
	default: assert(false); return -1;
	}
}

bool prefix_trie_matching(const string& text, trie& a_trie)
{
	size_t pos = 0;
	char symbol = text[0];
	size_t v = 0;

	while (true)
	{
		if (a_trie[v].empty())
		{
			return true;
		}
		else
		{
			if (a_trie[v].find(symbol) != a_trie[v].end() && pos < text.size())
			{
				v = a_trie[v][symbol];
				++pos;
				symbol = text[pos];
			}
			else
			{
				return false;
			}
		}
	}
}

vector <int> solve(const string& text, int n, vector <string>& patterns)
{
	vector <int> result;

	// write your code here
	trie a_trie = build_trie(patterns);


	for (size_t i = 0; i < text.size(); i++)
	{
		if (prefix_trie_matching(text.substr(i), a_trie))
		{
			result.push_back(i);
		}
	}

	return result;
}

int main(void)
{
	string text;
	cin >> text;

	int n;
	cin >> n;

	vector <string> patterns(n);
	for (int i = 0; i < n; i++)
	{
		cin >> patterns[i];
	}

	vector <int> ans;
	ans = solve(text, n, patterns);

	for (int i = 0; i < (int)ans.size(); i++)
	{
		cout << ans[i];
		if (i + 1 < (int)ans.size())
		{
			cout << " ";
		}
		else
		{
			cout << endl;
		}
	}

	return 0;
}
