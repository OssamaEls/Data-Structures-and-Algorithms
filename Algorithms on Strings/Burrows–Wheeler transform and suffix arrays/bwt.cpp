//Input Format.A string Text ending with a “$” symbol.
//Constraints. 1 ≤ | Text | ≤ 1 000; except for the last symbol, Text contains symbols A, C, G, T only.
//Output Format.BWT(Text).

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

string BWT(const string& text) {
	string result = "";
	const size_t n = text.size();
	vector<string> BWMatrix;

	for (size_t i = 0; i < n; i++)
	{
		BWMatrix.push_back(text.substr(i) + text.substr(0, i));
	}

	std::sort(BWMatrix.begin(), BWMatrix.end());

	for (size_t i = 0; i < n; i++)
	{
		result += BWMatrix[i][n - 1];
	}

	return result;
}

int main() {
	string text;
	cin >> text;
	cout << BWT(text) << endl;
	return 0;
}
