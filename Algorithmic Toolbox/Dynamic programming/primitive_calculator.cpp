//Input Format.The input consists of a single integer 1 ≤ 𝑛 ≤ 10^6.
//Output Format.In the first line, output the minimum number 𝑘 of operations needed to get 𝑛 from 1.
//In the second line output a sequence of intermediate numbers.That is, the second line should contain
//positive integers 𝑎0, 𝑎2, . . ., 𝑎𝑘−1 such that 𝑎0 = 1, 𝑎𝑘−1 = 𝑛 and for all 0 ≤ 𝑖 < 𝑘 − 1, 𝑎𝑖 + 1 is equal to
//	either 𝑎𝑖 + 1, 2𝑎𝑖, or 3𝑎𝑖.If there are many such sequences, output any one of them.

#include <iostream>
#include <vector>
#include <algorithm>



//vector<int> optimal_sequence(int n) {
//  std::vector<int> sequence;
//  while (n >= 1) {
//    sequence.push_back(n);
//    if (n % 3 == 0) {
//      n /= 3;
//    } else if (n % 2 == 0) {
//      n /= 2;
//    } else {
//      n = n - 1;
//    }
//  }
//  reverse(sequence.begin(), sequence.end());
//  return sequence;
//}

std::vector<int> optimal_sequence(std::vector<int>& previous, std::vector<int>& optimals, int n) {
	int prev = 2;
	for (size_t i = 2; i <= n; i++)
	{
		if ((i % 3 == 0) && (i % 2 == 0)) {
			if (optimals[i / 3] <= optimals[i / 2])
			{
				if (optimals[i / 3] <= optimals[i - 1])
				{
					prev = i / 3;
				}
				else {
					prev = i - 1;
				}
			}
			else {
				if (optimals[i / 2] <= optimals[i - 1])
				{
					prev = i / 2;
				}
				else {
					prev = i - 1;
				}
			}
		}
		else
		{
			if ((i % 3 == 0) && !(i % 2 == 0)) {
				if (optimals[i / 3] <= optimals[i - 1])
				{
					prev = i / 3;
				}
				else {
					prev = i - 1;
				}
			}
			else {
				if (!(i % 3 == 0) && (i % 2 == 0))
				{
					if (optimals[i / 2] <= optimals[i - 1])
					{
						prev = i / 2;
					}
					else {
						prev = i - 1;
					}
				}
				else {
					prev = i - 1;
				}

			}
		}
		previous[i] = prev;
		optimals[i] = optimals[prev] + 1;
	}
	std::vector<int> sequence(optimals[n] + 1);
	sequence[0] = n;
	for (size_t i = 1; i < sequence.size(); ++i) {
		sequence[i] = previous[sequence[i - 1]];
	}
	reverse(sequence.begin(), sequence.end());
	return sequence;
}

int main() {
	int n;
	std::cin >> n;
	std::vector<int> previous(n + 1);
	previous[0] = 0;
	previous[1] = 1;
	std::vector<int> optimals(n + 1);
	optimals[0] = 0;
	optimals[1] = 0;
	std::vector<int> sequence = optimal_sequence(previous, optimals, n);
	std::cout << sequence.size() - 1 << std::endl;
	for (size_t i = 0; i < sequence.size(); ++i) {
		std::cout << sequence[i] << " ";
	}
}