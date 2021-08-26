//Input Format.First line : 𝑛.Second line : 𝑎1, 𝑎2, . . ., 𝑎𝑛.Third line : 𝑚.Fourth line : 𝑏1, 𝑏2, . . ., 𝑏𝑚.
//Constraints. 1 ≤ 𝑛, 𝑚 ≤ 100; −10^9 < 𝑎𝑖, 𝑏𝑖 < 10^9.
//Output Format.Output 𝑝.

#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

//int lcs2(vector<int> &a, vector<int> &b) {
//  //write your code here
//  return std::min(std::min(a.size(), b.size()), c.size());
//}

int lcs2(vector<int>& a, vector<int>& b) {
	int n = a.size();
	int m = b.size();

	std::vector<std::vector<int>> D(n + 1);

	for (int i = 0; i <= n; i++)
	{
		D[i].resize(m + 1);
	}

	for (int i = 0; i <= n; i++)
	{
		D[i][0] = 0;
	}

	for (int j = 0; j <= m; j++)
	{
		D[0][j] = 0;
	}

	int insertion = 0, deletion = 0, match = 0;
	for (int j = 1; j <= m; j++)
	{
		for (int i = 1; i <= n; i++)
		{
			insertion = D[i][j - 1];
			deletion = D[i - 1][j];
			match = D[i - 1][j - 1];
			if (a[i - 1] == b[j - 1])
			{
				D[i][j] = std::max({ insertion, deletion, match +1});
			}
			else {
				D[i][j] = std::max({ insertion, deletion, match });
			}
		}
	}
	return D[n][m];
}

int main() {
	size_t n;
	std::cin >> n;
	vector<int> a(n);
	for (size_t i = 0; i < n; i++) {
		std::cin >> a[i];
	}

	size_t m;
	std::cin >> m;
	vector<int> b(m);
	for (size_t i = 0; i < m; i++) {
		std::cin >> b[i];
	}

	std::cout << lcs2(a, b) << std::endl;
}