//Input Format.The input consists of a single integer 𝑛.
//Constraints. 0 ≤ 𝑛 ≤ 10^7.
//Output Format.Output the last digit of 𝐹𝑛.

#include <iostream>
#include <vector>


int get_fibonacci_last_digit_naive(int n) {
    if (n <= 1)
        return n;

    int previous = 0;
    int current  = 1;

    for (int i = 0; i < n - 1; ++i) {
        int tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
    }

    return current % 10;
}

int get_fibonacci_last_digit_fast(int n)
{
    int a = 0, b = 1, c, i;
    if (n == 0)
        return a;
    for (i = 2; i <= n; i++)
    {
        c = (a + b) % 10;
        a = b;
        b = c;
    }
    return b;
}

int main() {
    int n;
    std::cin >> n;
    int c = get_fibonacci_last_digit_fast(n);
    std::cout << c << '\n';
}
