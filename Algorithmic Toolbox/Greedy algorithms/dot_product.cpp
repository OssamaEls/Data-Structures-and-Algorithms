//Input Format.The first line contains an integer 𝑛, the second one contains a sequence of integers
//𝑎1, 𝑎2, . . ., 𝑎𝑛, the third one contains a sequence of integers 𝑏1, 𝑏2, . . ., 𝑏𝑛.
//Constraints. 1 ≤ 𝑛 ≤ 10^3; −10^5 ≤ 𝑎𝑖, 𝑏𝑖 ≤ 10^5 for all 1 ≤ 𝑖 ≤ 𝑛.
//Output Format.Output the maximum value of
//∑︀𝑎𝑖𝑐𝑖, where 𝑐1, 𝑐2, . . ., 𝑐𝑛 is a permutation of
//𝑏1, 𝑏2, . . ., 𝑏𝑛.


#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;

long long max_dot_product(vector<int>& a, vector<int>& b) {
    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());


  long long result = 0;
  for (size_t i = 0; i < a.size(); i++) {
    result += ((long long) a[i]) * b[i];
  }
  return result;
}

int main() {
  size_t n;
  std::cin >> n;
  vector<int> a(n), b(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> a[i];
  }
  for (size_t i = 0; i < n; i++) {
    std::cin >> b[i];
  }
  std::cout << max_dot_product(a, b) << std::endl;
}
