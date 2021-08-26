//Input Format.The input consists of two non - negative integers 𝑚 and 𝑛 separated by a space.
//Constraints. 0 ≤ 𝑚 ≤ 𝑛 ≤ 10^14.
//Output Format.Output the last digit of 𝐹𝑚 + 𝐹𝑚 + 1 + · · · + 𝐹𝑛.

#include <iostream>
#include <vector>


long long get_fibonacci_partial_sum_naive(long long from, long long to) {
    long long sum = 0;

    long long current = 0;
    long long next  = 1;

    for (long long i = 0; i <= to; ++i) {
        if (i >= from) {
            sum += current;
        }

        long long new_current = next;
        next = next + current;
        current = new_current;
    }

    return sum % 10;
}

std::vector<long long> fibonacci_period(long long m)
{
    long long T = 3;
    std::vector<long long> first_res{ 0,1 };

    long long i;
    for (i = T - 1; i < 2 * T; i++)
    {
        first_res.push_back((first_res[i - 2] + first_res[i - 1]) % m);
    }

    bool periodic = false;

    while (!periodic)
    {
        for (i = 0; i < T; i++)
        {
            if (first_res[i + T] != first_res[i])
            {
                first_res.push_back((first_res[2 * T - 2] + first_res[2 * T - 1]) % m);
                first_res.push_back((first_res[2 * T - 1] + first_res[2 * T]) % m);
                ++T;
                break;
            }
        }
        if (i == T && first_res[i - 1 + T] == first_res[i - 1]) periodic = true;
    }

    return first_res;
}

long long get_fibonacci_huge_fast(long long n, long long m)
{
    if (n <= 1)
        return n;

    std::vector<long long> period{ fibonacci_period(m) };
    auto T{ period.size() };

    return period[(n % T)];
}

int fibonacci_sum_fast(long long n)
{
    if (n <= 1) return n;

    int result{ (get_fibonacci_huge_fast(n + 2, 10) - 1) % 10 };
    return (result >= 0) ? result : result + 10;
}

long long get_fibonacci_partial_sum_fast(long long from, long long to) {
    if (from<=1 ) return fibonacci_sum_fast(to);

    int result{ fibonacci_sum_fast(to) - fibonacci_sum_fast(from - 1) };
    return (result > 0) ? result : (result + 10);
}

int main() {
    long long from, to;
    std::cin >> from >> to;
    std::cout << get_fibonacci_partial_sum_fast(from, to) << '\n';
}
