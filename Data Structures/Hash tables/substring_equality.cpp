//Input Format.The first line contains a string 𝑠 consisting of small Latin letters.The second line contains
//the number of queries 𝑞.Each of the next 𝑞 lines specifies a query by three integers 𝑎, 𝑏, and 𝑙.
//Constraints. 1 ≤ | 𝑠 | ≤ 500 000. 1 ≤ 𝑞 ≤ 100 000. 0 ≤ 𝑎, 𝑏 ≤ | 𝑠 | − 𝑙(hence the indices 𝑎 and 𝑏 are 0 - based).
//Output Format.For each query, output “Yes” if 𝑠𝑎𝑠𝑎 + 1. ..𝑠𝑎 + 𝑙−1 = 𝑠𝑏𝑠𝑏 + 1. ..𝑠𝑏 + 𝑙−1 are equal, and “No”
//otherwise.

#include <iostream>
#include <string>
#include <vector>

using std::vector;
using std::string;
typedef std::int64_t ull;

class Solver {
	string s;
	vector<ull> h1, h2;
	ull multiplier = 263;
	ull m1 = 1000000007, m2 = 1000000009;
	vector<ull> xpow1;
	vector<ull> xpow2;
public:
	Solver(string s) : s(s) {
		ull hash = 0;
		ull n = s.size();
		h1.resize(n + 1), h2.resize(n + 1);
		xpow1.resize(500001);
		xpow2.resize(500001);
		xpow1[0] = 1, xpow2[0] = 1;
		for (size_t i = 1; i < xpow1.size(); i++)
		{
			xpow1[i] = (multiplier * xpow1[i - 1]) % m1;
			xpow2[i] = (multiplier * xpow2[i - 1]) % m2;
		}
		h1[0] = 0, h2[0] = 0;
		for (ull i = 1; i <= n; ++i)
		{
			h1[i] = (h1[i - 1] * multiplier + s[i - 1]) % m1;
			h2[i] = (h2[i - 1] * multiplier + s[i - 1]) % m2;
		}
	}
	bool ask(int a, int b, int l) {
		ull y1 = xpow1[l], y2 = xpow2[l];
		ull ha1 = (((h1[a + l] - y1 * h1[a]) % m1) + m1) % m1;
		ull ha2 = (((h2[a + l] - y2 * h2[a]) % m2) + m2) % m2;
		ull hb1 = (((h1[b + l] - y1 * h1[b]) % m1) + m1) % m1;
		ull hb2 = (((h2[b + l] - y2 * h2[b]) % m2) + m2) % m2;
		return (ha1 == hb1) && (ha2 == hb2);
	}
};

int main() {
	std::ios_base::sync_with_stdio(0), std::cin.tie(0);

	string s;
	int q;
	std::cin >> s >> q;
	Solver solver(s);
	for (int i = 0; i < q; i++) {
		int a, b, l;
		std::cin >> a >> b >> l;
		std::cout << (solver.ask(a, b, l) ? "Yes\n" : "No\n");
	}
}

