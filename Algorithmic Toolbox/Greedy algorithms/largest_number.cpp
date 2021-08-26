//Input Format.The first line of the input contains an integer 𝑛.The second line contains integers
//𝑎1, 𝑎2, . . ., 𝑎𝑛.
//Constraints. 1 ≤ 𝑛 ≤ 100; 1 ≤ 𝑎𝑖 ≤ 10^3 for all 1 ≤ 𝑖 ≤ 𝑛.
//Output Format.Output the largest number that can be composed out of 𝑎1, 𝑎2, . . ., 𝑎𝑛.

#include <algorithm>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;

bool isGreaterOrEqual(string digit, string maxDigit)
{
    int num1{ std::stoi(digit + maxDigit) };
    int num2{ std::stoi(maxDigit + digit) };
    return (num1 >= num2);
}

string largest_number(vector<string>& a) {
    string result{ "" };
    string max_digit;
    std::stringstream ret;
    int index_max{ 0 };
    while (a.size() > 0)
    {
        max_digit = "0";
        index_max = 0;
        for (size_t i = 0; i < a.size(); i++) {
            if (isGreaterOrEqual(a[i], max_digit))
            {
                max_digit = a[i];
                index_max = i;
            }
        }
        ret << max_digit;
        a.erase(a.begin() + index_max);
    }

    ret >> result;
    return result;
}

int main() {
    int n;
    std::cin >> n;
    vector<string> a(n);
    for (size_t i = 0; i < a.size(); i++) {
        std::cin >> a[i];
    }
    std::cout << largest_number(a);
}