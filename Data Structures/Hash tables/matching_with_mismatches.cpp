//Input Format.Every line of the input contains an integer 𝑘and two strings 𝑡and 𝑝 consisting of lower
//case Latin letters.
//Constraints. 0 ≤ 𝑘 ≤ 5, 1 ≤ | 𝑡 | ≤ 200 000, 1 ≤ | 𝑝 | ≤ min{ | 𝑡 | , 100 000 }. The total length of all 𝑡’s does not
//exceed 200 000, the total length of all 𝑝’s does not exceed 100 000.
//Output Format.For each triple(𝑘, 𝑡, 𝑝), find all positions 0 ≤ 𝑖1 < 𝑖2 < · · · < 𝑖𝑙 < | 𝑡 | where 𝑝 occurs in 𝑡
//with at most 𝑘 mismatches.Output 𝑙 and 𝑖1, 𝑖2, . . ., 𝑖𝑙.

#include <iostream>
#include <vector>

using namespace std;
typedef std::int64_t ull;

vector<int> solve(int k, const string& text, const string& pattern, const vector<ull>& xpow1, ull multiplier, ull m1) {
	vector<int> pos;

	vector<ull> h1t(text.size() + 1);
	vector<ull> h1p(pattern.size() + 1);

	h1t[0] = 0;
	for (ull i = 1; i <= text.size(); ++i)
	{
		h1t[i] = (h1t[i - 1] * multiplier + text[i - 1]) % m1;
	}


	h1p[0] = 0;
	for (ull i = 1; i <= pattern.size(); ++i)
	{
		h1p[i] = (h1p[i - 1] * multiplier + pattern[i - 1]) % m1;
	}

	int lower_bound = 0, upper_bound = 0;

	size_t dth_match;
	int middle = 0;
	ull y1;
	ull hash1t, hash1p;
	int length;
	size_t d;
	bool matching;

	for (size_t idx = 0; idx + pattern.size() <= text.size(); idx++)
	{
		y1 = xpow1[pattern.size()];
		hash1t = (((h1t[idx + pattern.size()] - y1 * h1t[idx]) % m1) + m1) % m1;
		hash1p = ((h1p[pattern.size()] % m1) + m1) % m1;
		if (hash1t == hash1p)
		{
			pos.push_back(idx);
			continue;
		}

		if (k == 0) continue;

		dth_match = 0;
		d = 0;
		while (d <= k)
		{
			lower_bound = dth_match + 1;
			upper_bound = pattern.size();
			if (lower_bound > upper_bound) break;
			middle = lower_bound + (upper_bound - lower_bound) / 2;
			length = middle - lower_bound;
			matching = false;
			while (upper_bound >= lower_bound)
			{
				y1 = xpow1[length + 1];
				hash1t = (((h1t[idx + lower_bound + length] - y1 * h1t[idx + lower_bound - 1]) % m1) + m1) % m1;
				hash1p = (((h1p[lower_bound + length] - y1 * h1p[lower_bound - 1]) % m1) + m1) % m1;
				if (hash1t == hash1p)
				{
					lower_bound = middle + 1;
					matching = true;
				}
				else
				{
					upper_bound = middle - 1;
					matching = false;
				}
				if (upper_bound >= lower_bound)
				{
					middle = lower_bound + (upper_bound - lower_bound) / 2;
					length = middle - lower_bound;
				}
			}

			if (!matching) ++d;
			dth_match = middle;
		}


		if (d <= k)
		{
			pos.push_back(idx);
		}

	}


	return pos;
}

int main() {
	ios_base::sync_with_stdio(false), cin.tie(0);

	ull multiplier = 263;
	ull m1 = 1000000007;

	vector<ull> xpow1(200001);

	xpow1[0] = 1;
	for (size_t i = 1; i < xpow1.size(); i++)
	{
		xpow1[i] = (multiplier * xpow1[i - 1]) % m1;
	}

	int k;
	string t, p;
	while (cin >> k >> t >> p) {
		auto a = solve(k, t, p, xpow1, multiplier, m1);
		cout << a.size();
		for (int x : a)
			cout << " " << x;
		cout << "\n";
	}
}