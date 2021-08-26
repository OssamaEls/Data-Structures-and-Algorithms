//Input Format.The input consists of a single integer 𝑛.
//Constraints. 0 ≤ 𝑛 ≤ 10^14.
//Output Format.Output the last digit of 𝐹0 + 𝐹1 + · · · + 𝐹𝑛

#include <iostream>
#include <vector>

int fibonacci_sum_naive(long long n) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;
    long long sum      = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
        sum += current;
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

int main() {
    long long n = 0;
    std::cin >> n;
    std::cout << fibonacci_sum_fast(n);
    
}
