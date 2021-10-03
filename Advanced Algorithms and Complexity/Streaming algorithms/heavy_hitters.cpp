//Input Format.The first line contains the number of children 𝑁, the second line contains the threshold 𝑡.
//This is followed by list 𝐴 : 𝑁 lines specifying the number of good things each child did during the
//year.For each 𝑖 = 1, . . ., 𝑁 the corresponding line contains the tuple(𝑘𝑖, 𝑔𝑘𝑖(separated by a space).
//The next 𝑁 lines specify list 𝐵 : the number of bad things each child did during the year.For each
//𝑖 = 1, . . ., 𝑁 the corresponding line contains the tuple(𝑘𝑖, 𝑏𝑘𝑖).The next line contains the number of
//queries 𝑞.The last line contains 𝑞 children ids.
//
//Constraints.All the number are integers. 1 ≤ 𝑁 ≤ 5·10^5; 0 ≤ 𝑘𝑖 ≤ 2^31−1; 0 ≤ 𝑏𝑗, 𝑔𝑗 ≤ 2^31−1, 1 ≤ 𝑞 ≤ 10.
//It is guaranteed that the lists 𝐴 and 𝐵 contain the same children ids(though not necessarily in the
//same order), and that each id appears exactly once in 𝐴and exactly once in 𝐵.All the query ids are
//present in 𝐴and 𝐵.
//
//Output Format.For each query id, output 1 if this child is nice, and 0 if the child is naughty.Separate
//these 𝑞 bits by spaces.

#include <iostream>
#include <utility>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <cstdlib> 

using namespace std;

const long long p = 2147483869; // (1LL << 61) - 1;
const int num_buckets = 2048;
const int num_repetitions = 15;

std::vector<std::vector<int>> random_numbers()
{
    std::vector<std::vector<int>> random_list(num_repetitions, std::vector<int>(4));

    std::srand(5323);

    std::rand();

    for (size_t i = 0; i < num_repetitions; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            random_list[i][j] = std::rand();
        }
    }

    return random_list;
}

std::vector<std::vector<int>> random_coeff = random_numbers();


long long hash_value(int a, int b, int id)
{
    return (a * (long long)id + b) % p % num_buckets;
}

long long sign_hash(int c, int d, int id)
{
    long long val = (c * (long long)id + d)  % p % 2;
    return (val == 0) ? -1 : 1;
}

long long median(std::vector<std::vector<long long>>& matrix, int id)
{
    vector<long long> observations(num_repetitions);

    for (size_t i = 0; i < num_repetitions; i++)
    {
        int a = i + 100;
        int b = i + 2000;
        long long h = hash_value(a, b, id);

        int c = num_buckets + i;
        int d = c + 3000;
        long long s = sign_hash(c, d, id);

        observations[i] = matrix[i][h] * s;
    }

    size_t n = observations.size() / 2;
    std::nth_element(observations.begin(), observations.begin() + n, observations.end());
    return observations[n];

}

void fill_matrix(std::vector<std::vector<long long>>& matrix, int id, int num_appearances)
{
    for (size_t i = 0; i < num_repetitions; i++)
    {
        int a = i + 100;
        int b = i + 2000;
        long long h = hash_value(a, b, id);

        int c = num_buckets + i;
        int d = c + 3000;
        long long s = sign_hash(c, d, id);

        matrix[i][h] += s * num_appearances;
    }
}

int main() {


    std::vector<std::vector<long long>> matrix(num_repetitions, std::vector<long long>(num_buckets));

    int n, t;
    //scanf_s("%d %d", &n, &t);
    cin >> n >> t;
    //cout << "n is " << n << '\n';

    int id, value;

    for (int i = 0; i < n; ++i) {
        //scanf_s("%d %d", &id, &value);
        cin >> id >> value;
        fill_matrix(matrix, id, value);
    }

    for (int i = 0; i < n; ++i) {
        //scanf_s("%d %d", &id, &value);
        cin >> id >> value;
        fill_matrix(matrix, id, -value);
    }

    // cout << "written the good deeds\n";

    int num_queries = 0;
    cin >> num_queries;
    //scanf_s("%d", &num_queries);
    for (int q = 0; q < num_queries; ++q) {
        int query = 0;
        //scanf_s("%d", &query);
        cin >> query;
        if (median(matrix, query) < t)
            cout << "0 ";
        else
            cout << "1 ";
    }

    return 0;
}