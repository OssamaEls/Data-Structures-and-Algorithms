//Input Format.Each of the two lines of the input contains a string consisting of lower case latin letters.
//Constraints.The length of both strings is at least 1 and at most 100.
//Output Format.Output the edit distance between the given two strings.

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::string;

int edit_distance(const string& str1, const string& str2) {
	int n = str1.size();
	int m = str2.size();
	std::vector<std::vector<int>> D(n + 1);

	for (int i = 0; i <= n; i++)
	{
		D[i].resize(m + 1);
	}

	for (int i = 0; i <= n; i++)
	{
		D[i][0] = i;
	}

	for (int j = 0; j <= m; j++)
	{
		D[0][j] = j;
	}


	int insertion = 0, deletion = 0, match = 0, mismatch = 0;
	for (int j = 1; j <= m; j++)
	{
		for (int i = 1; i <= n; i++)
		{
			insertion = D[i][j - 1] + 1;
			deletion = D[i - 1][j] + 1;
			match = D[i - 1][j - 1];
			mismatch = D[i - 1][j - 1] + 1;
			if (str1[i - 1] == str2[j - 1])
			{
				D[i][j] = std::min({ insertion, deletion, match });
			}
			else {
				D[i][j] = std::min({ insertion, deletion, mismatch });
			}
		}
	}
	return D[n][m];
}

int main() {
	string str1;
	string str2;
	std::cin >> str1 >> str2;
	std::cout << edit_distance(str1, str2) << std::endl;
	return 0;
}

