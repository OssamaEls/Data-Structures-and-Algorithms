//Input Format.First line : 𝑛. Second line : 𝑎1, 𝑎2, . . ., 𝑎𝑛. Third line : 𝑚. Fourth line : 𝑏1, 𝑏2, . . ., 𝑏𝑚.
// Fifth line :𝑙 .Sixth line : 𝑐1, 𝑐2, . . ., 𝑐𝑙.
//Constraints. 1 ≤ 𝑛, 𝑚, 𝑙 ≤ 100; −10^9 < 𝑎𝑖, 𝑏𝑖, 𝑐𝑖 < 10^9.
//Output Format.Output 𝑝

#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

int lcs3(vector<int>& a, vector<int>& b, vector<int>& c) {
    int n = a.size();
    int m = b.size();
    int p = c.size();
    std::vector<std::vector<std::vector<int>>> D(n + 1, std::vector<std::vector<int>>(m + 1, std::vector<int>(p + 1)));

    for (int i = 0; i <= n; i++)
    {
        D[i][0][0] = 0;
    }

    for (int j = 0; j <= m; j++)
    {
        D[0][j][0] = 0;
    }

    for (int k = 0; k <= p; k++)
    {
        D[0][0][k] = 0;
    }

    int insertion1 = 0, insertion2 = 0, insertion3 = 0, insertion4 = 0, match = 0;
    for (int k = 1; k <= p; k++)
    {
        for (int j = 1; j <= m; j++)
        {
            for (int i = 1; i <= n; i++)
            {
                insertion1 = D[i][j][k - 1];
                insertion2 = D[i][j - 1][k];
                insertion3 = D[i - 1][j][k];
                match = D[i - 1][j - 1][k - 1];
                D[i][j][k] = std::max({ insertion1, insertion2, insertion3, match + ((a[i - 1] == b[j - 1]) && (b[j - 1] == c[k - 1])) });
            }
        }
    }
    return D[n][m][p];

}

int main() {
    size_t an;
    std::cin >> an;
    vector<int> a(an);
    for (size_t i = 0; i < an; i++) {
        std::cin >> a[i];
    }
    size_t bn;
    std::cin >> bn;
    vector<int> b(bn);
    for (size_t i = 0; i < bn; i++) {
        std::cin >> b[i];
    }
    size_t cn;
    std::cin >> cn;
    vector<int> c(cn);
    for (size_t i = 0; i < cn; i++) {
        std::cin >> c[i];
    }
    std::cout << lcs3(a, b, c) << std::endl;
}
