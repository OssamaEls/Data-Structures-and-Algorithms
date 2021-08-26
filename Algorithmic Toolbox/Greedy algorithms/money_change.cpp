//Input Format.The input consists of a single integer 𝑚.
//Constraints. 1 ≤ 𝑚 ≤ 103.
//Output Format.Output the minimum number of coins with denominations 1, 5, 10 that changes 𝑚.

#include <iostream>

int get_change(int m) {
	return m / 10 + (m % 10) / 5 + m % 5;
}

int main() {
	int m;
	std::cin >> m;
	std::cout << get_change(m) << '\n';
}
