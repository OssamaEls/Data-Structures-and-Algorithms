//Input Format.The first line contains an integer 𝑛, the next one contains a sequence of integers
//𝑎0, 𝑎1, . . ., 𝑎𝑛−1.
//Constraints. 1 ≤ 𝑛 ≤ 10^5, 1 ≤ 𝑎𝑖 ≤ 10^9 for all 0 ≤ 𝑖 < 𝑛.
//Output Format.Output the number of inversions in the sequence.

#include <iostream>
#include <vector>
#include <tuple>
#include <iterator>

using std::vector;

long long inversions_sort(vector<int>& a, size_t left, size_t ave, size_t right)
{
	long long inversions = 0;
	vector<int> c(ave - left);
	vector<int> d(right - ave);
	for (size_t i = 0; i < c.size(); i++)
	{
		c[i] = a[left + i];
	}

	for (size_t i = 0; i < d.size(); i++)
	{
		d[i] = a[i + ave];
	}

	size_t i = left;
	while (!c.empty() && !d.empty())
	{
		if (c[0] <= d[0])
		{
			a[i] = c[0];
			c.erase(c.begin());
		}
		else
		{
			a[i] = d[0];
			d.erase(d.begin());
			inversions += c.size();
		}
		++i;
	}


	while (!c.empty())
	{
		a[i] = c[0];
		c.erase(c.begin());
		++i;
	}

	while (!d.empty())
	{
		a[i] = d[0];
		d.erase(d.begin());
		++i;
	}

	return inversions;
}

long long get_number_of_inversions(vector<int>& a, size_t left, size_t right)
{
	long long number_of_inversions = 0;
	if (right <= left + 1) return number_of_inversions;
	size_t ave = left + (right - left) / 2;

	number_of_inversions += get_number_of_inversions(a, left, ave);
	number_of_inversions += get_number_of_inversions(a, ave, right);
	number_of_inversions += inversions_sort(a, left, ave, right);

	return number_of_inversions;
}

int main() {
	int n;
	std::cin >> n;
	vector<int> a(n);
	for (size_t i = 0; i < a.size(); i++) {
		std::cin >> a[i];
	}
	std::cout << get_number_of_inversions(a, 0, a.size()) << '\n';
}
