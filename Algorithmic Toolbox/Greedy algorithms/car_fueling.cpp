//Input Format.The first line contains an integer 𝑑.The second line contains an integer 𝑚.The third line
//specifies an integer 𝑛.Finally, the last line contains integers stop1, stop2, . . ., stop𝑛.
//Output Format. Assuming that the distance between the cities is 𝑑 miles, a car can travel at most 𝑚 miles
//on a full tank, and there are gas stations at distances stop1, stop2, . . ., stop𝑛 along the way, output the
//minimum number of refills needed.Assume that the car starts with a full tank.If it is not possible to
//reach the destination, output −1.
//Constraints. 1 ≤ 𝑑 ≤ 10^5. 1 ≤ 𝑚 ≤ 400. 1 ≤ 𝑛 ≤ 300. 0 < stop1 < stop2 < · · · < stop𝑛 < 𝑑.


#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
using std::max;

int compute_min_refills(int dist, int tank, const vector<int>& stops) {
    int num_refills{ 0 };
    int current_refill{ 0 };
    int n{ static_cast<int>(stops.size()) - 2 };
    int last_refill;
    while (current_refill <= n)
    {
        last_refill = current_refill;
        while (current_refill <= n && (stops[current_refill + 1] - stops[last_refill]) <= tank)
        {
            ++current_refill;
        }
        if (current_refill == last_refill) return -1;
        if (current_refill <= n) ++num_refills;
    }
    return num_refills;
}


int main() {
    int d = 0;
    cin >> d;
    int m = 0;
    cin >> m;
    int n = 0;
    cin >> n;

    vector<int> stops(n + 2);
    stops[0] = 0;
    for (size_t i = 0; i < n; ++i)
        cin >> stops.at(i + 1);
    stops[n + 1] = d;
    cout << compute_min_refills(d, m, stops) << "\n";

    return 0;
}