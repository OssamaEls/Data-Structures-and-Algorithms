//Input Format.Every line of the input contains two strings 𝑠and 𝑡 consisting of lower case Latin letters.
//Constraints.The total length of all 𝑠’s as well as the total length of all 𝑡’s does not exceed 100 000.
//Output Format.For each pair of strings 𝑠 and 𝑡𝑖, find its longest common substringand specify it by
//outputting three integers : its starting position in 𝑠, its starting position in 𝑡(both 0 - based), and its
//length.More formally, output integers 0 ≤ 𝑖 < | 𝑠 | , 0 ≤ 𝑗 < | 𝑡 | , and 𝑙 ≥ 0 such that 𝑠𝑖𝑠𝑖 + 1 · · · 𝑠𝑖 + 𝑙−1 =
//	𝑡𝑗𝑡𝑗 + 1 · · · 𝑡𝑗 + 𝑙−1 and 𝑙 is maximal. (As usual, if there are many such triples with maximal 𝑙, output any
//		of them.)

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;
typedef std::int64_t ull;
typedef unordered_map<ull, int> my_dict;

struct Answer {
	size_t i, j, len;
};

Answer solve(const string& s, const string& t, const vector<ull>& xpow1, const vector<ull>& xpow2, ull multiplier, ull m1, ull m2) {
	Answer ans = { 0, 0, 0 };

	vector<ull> h1s(s.size() + 1);
	vector<ull> h1t(t.size() + 1);
	vector<ull> h2s(s.size() + 1);
	vector<ull> h2t(t.size() + 1);




	h1s[0] = 0, h2s[0] = 0;
	for (ull i = 1; i <= s.size(); ++i)
	{
		h1s[i] = (h1s[i - 1] * multiplier + s[i - 1]) % m1;
		h2s[i] = (h2s[i - 1] * multiplier + s[i - 1]) % m2;
	}

	h1t[0] = 0, h2t[0] = 0;
	for (ull i = 1; i <= t.size(); ++i)
	{
		h1t[i] = (h1t[i - 1] * multiplier + t[i - 1]) % m1;
		h2t[i] = (h2t[i - 1] * multiplier + t[i - 1]) % m2;
	}

	size_t lower_bound = 1, upper_bound = min(s.size(), t.size());


	vector<ull> hashk_1t, hashk_2t;
	my_dict hashk_1s;

	int idx = 0;
	size_t i = 0;
	ull y1, y2;
	size_t k = (upper_bound + lower_bound) / 2;
	size_t j = 0;

	while (upper_bound >= lower_bound)
	{
		y1 = xpow1[k], y2 = xpow2[k];
		for (i = 0; i + k <= min(s.size(), t.size()); i++)
		{
			hashk_1t.push_back((((h1t[i + k] - y1 * h1t[i]) % m1) + m1) % m1);
			hashk_2t.push_back((((h2t[i + k] - y2 * h2t[i]) % m2) + m2) % m2);
			hashk_1s[(((h1s[i + k] - y1 * h1s[i]) % m1) + m1) % m1] = i;
			hashk_1s[(((h2s[i + k] - y2 * h2s[i]) % m2) + m2) % m2] = i;
		}

		--i;

		if (s.size() > (i + k))
		{
			++i;
			while (i + k <= s.size())
			{
				hashk_1s[(((h1s[i + k] - y1 * h1s[i]) % m1) + m1) % m1] = i;
				hashk_1s[(((h2s[i + k] - y2 * h2s[i]) % m2) + m2) % m2] = i;
				++i;
			}
		}

		i = min(s.size(), t.size()) - k;

		if (t.size() > (i + k))
		{
			++i;
			while (i + k <= t.size())
			{
				hashk_1t.push_back((((h1t[i + k] - y1 * h1t[i]) % m1) + m1) % m1);
				hashk_2t.push_back((((h2t[i + k] - y2 * h2t[i]) % m2) + m2) % m2);
				++i;
			}
		}



		j = 0;
		bool found_length_k = false;
		while (!found_length_k && j < hashk_1t.size())
		{
			auto hash1 = hashk_1s.find(hashk_1t[j]);
			auto hash2 = hashk_1s.find(hashk_2t[j]);
			if (hash1 != hashk_1s.end() && hash2 != hashk_1s.end())
			{
				found_length_k = true;
				ans = { static_cast<size_t>(hash1->second), j,k };
			}
			++j;
		}

		if (found_length_k)
		{
			if ((lower_bound + 1) == upper_bound)
			{
				lower_bound = upper_bound;
				k = lower_bound;
			}
			else
			{
				if (lower_bound == upper_bound)
				{
					break;
				}
				else {
					lower_bound = k;
					k = (upper_bound + lower_bound) / 2;
				}
			}
		}
		else
		{
			if ((lower_bound + 1) == upper_bound)
			{
				lower_bound = upper_bound;
				k = lower_bound;
			}
			else
			{
				if (lower_bound == upper_bound)
				{
					break;
				}
				else {
					upper_bound = k;
					k = (upper_bound + lower_bound) / 2;
				}
			}
		}
		hashk_1t.clear();
		hashk_1s.clear();
		hashk_2t.clear();

	}

	return ans;
}

int main() {
	ios_base::sync_with_stdio(false), cin.tie(0);

	ull multiplier = 263;
	ull m1 = 1000000007, m2 = 1000000009;

	vector<ull> xpow1(100001);
	vector<ull> xpow2(100001);

	xpow1[0] = 1, xpow2[0] = 1;
	for (size_t i = 1; i < xpow1.size(); i++)
	{
		xpow1[i] = (multiplier * xpow1[i - 1]) % m1;
		xpow2[i] = (multiplier * xpow2[i - 1]) % m2;
	}

	string s, t;
	while (cin >> s >> t) {
		auto ans = solve(s, t, xpow1, xpow2, multiplier, m1, m2);
		cout << ans.i << " " << ans.j << " " << ans.len << "\n";
	}
}
