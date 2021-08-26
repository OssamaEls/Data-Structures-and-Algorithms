//Input Format.A string Transform with a single “$” sign
//Constraints. 1 ≤ | Transform | ≤ 1 000 000; except for the last symbol, Text contains symbols A, C, G, T
//only.
//Output Format.The string Text such that BWT(Text) = Transform. (There exists a unique such string.)

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;


size_t letterToIndex(char letter)
{
	switch (letter)
	{
	case '$': return 0; break;
	case 'A': return 1; break;
	case 'C': return 2; break;
	case 'G': return 3; break;
	case 'T': return 4; break;
	}
}

string InverseBWT(const string& bwt) {
	string text;

	const size_t n = bwt.size();
	// write your code here
	text.resize(n);
	vector<size_t> count(5, 0);


	for (size_t i = 0; i < n; i++)
	{
		++count[letterToIndex(bwt[i])];
	}


	vector<size_t> pos(5, 0);

	for (size_t i = 1; i < 5; i++)
	{
		pos[i] = pos[i - 1] + count[i - 1];
	}

	vector<size_t> idx_in_first_column(n);

	for (size_t i = 0; i < n; i++)
	{
		idx_in_first_column[i] = pos[letterToIndex(bwt[i])];
		++pos[letterToIndex(bwt[i])];
	}


	char letter;
	size_t idx = 0;
	text[n - 1] = '$';
	for (size_t i = 0; i < n - 1; i++)
	{
		letter = bwt[idx];
		text[n - 2 - i] = letter;
		idx = idx_in_first_column[idx];
	}

	return text;
}

int main() {
	string bwt;
	cin >> bwt;
	cout << InverseBWT(bwt) << endl;
	return 0;
}