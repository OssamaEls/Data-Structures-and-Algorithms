//Input Format.The input consists of two integers 𝑛and 𝑚 given on the same line(separated by a space).
//Constraints. 1 ≤ 𝑛 ≤ 10^14, 2 ≤ 𝑚 ≤ 10^3.
//Output Format.Output 𝐹𝑛 mod 𝑚

#include <iostream>
#include <vector>

long long get_fibonacci_huge_naive(long long n, long long m) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
    }

    return current % m;
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



int main() {
    long long n, m;
    std::cin >> n >> m;
    std::cout << get_fibonacci_huge_fast(n, m) << '\n';
}