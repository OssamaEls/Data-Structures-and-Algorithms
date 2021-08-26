//Input Format.The first line of the input contains a string Text, the second line contains an integer 𝑛,
//each of the following 𝑛 lines contains a pattern from Patterns = { 𝑝1, . . . , 𝑝𝑛 }.
//Constraints. 1 ≤ | Text | ≤ 10 000; 1 ≤ 𝑛 ≤ 5 000; 1 ≤ | 𝑝𝑖 | ≤ 100 for all 1 ≤ 𝑖 ≤ 𝑛; all strings contain only
//symbols A, C, G, T; it can be the case that 𝑝𝑖 is a prefix of 𝑝𝑗 for some 𝑖, 𝑗.
//Output Format.All starting positions in Text where a string from Patterns appears as a substring in
//increasing order(assuming that Text is a 0 - based array of symbols).If more than one pattern
//appears starting at position 𝑖, output 𝑖 once.

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;


int const Letters = 4;
int const NA = -1;

struct Node
{
	size_t next[Letters];
	bool patternEnd;

	Node()
	{
		fill(next, next + Letters, NA);
		patternEnd = false;
	}
};

typedef vector<Node> trie;

size_t letterToIndex(char letter)
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

trie build_trie(vector<string>& patterns) {
	trie t;
	// write your code here
	const size_t n = patterns.size();

	size_t current_node;
	size_t new_node = 0;
	t.push_back(Node());

	for (const auto& pattern : patterns)
	{

		current_node = 0;

		for (const auto& symbol : pattern)
		{

			if (t[current_node].next[letterToIndex(symbol)] != NA)
			{
				current_node = t[current_node].next[letterToIndex(symbol)];
			}
			else
			{
				new_node = t.size();
				t[current_node].next[letterToIndex(symbol)] = new_node;
				current_node = new_node;
				t.push_back(Node());
			}
		}
		t[current_node].patternEnd = true;
	}

	return t;
}

bool prefix_trie_matching(const string& text, trie& a_trie)
{
	size_t pos = 0;
	char symbol = text[0];
	size_t v = 0;

	while (true)
	{
		if (a_trie[v].patternEnd)
		{
			return true;
		}
		else
		{
			if (pos < text.size() && a_trie[v].next[letterToIndex(symbol)] != NA)
			{
				v = a_trie[v].next[letterToIndex(symbol)];
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


vector <int> solve(string text, int n, vector <string> patterns)
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
