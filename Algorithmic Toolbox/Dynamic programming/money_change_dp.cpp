//Input Format.Integer money.
//Output Format.The minimum number of coins with denominations 1, 3, 4 that changes money.
//Constraints. 1 ≤ money ≤ 10^3.

#include <iostream>
#include <vector>

int get_change(int m) {
	int coins[3]{ 1,3,4 };
	std::vector<int> minNumCoins(m + 1);
	minNumCoins[0] = 0;
	int numCoins;
	for (size_t k = 1; k <= m; k++)
	{
		minNumCoins[k] = m + 1;
		for (size_t i = 0; i < 3; i++)
		{
			if (k >= coins[i])
			{
				numCoins = minNumCoins[k - coins[i]] + 1;
				if (numCoins < minNumCoins[k])
				{
					minNumCoins[k] = numCoins;
				}
			}
		}
	}
	return minNumCoins[m];

}

int main() {
	int m;
	std::cin >> m;
	std::cout << get_change(m) << '\n';
}
