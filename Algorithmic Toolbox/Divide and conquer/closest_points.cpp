//Input Format.The first line contains the number 𝑛 of points.Each of the following 𝑛 lines defines a point
//(𝑥𝑖, 𝑦𝑖).
//Constraints. 2 ≤ 𝑛 ≤ 10^5; −10^9 ≤ 𝑥𝑖, 𝑦𝑖 ≤ 10^9 are integers.
//Output Format.Output the minimum distance.The absolute value of the difference between the answer
//of your program and the optimal value should be at most 10−3.To ensure this, output your answer
//with at least four digits after the decimal point(otherwise your answer, while being computed correctly,
//can turn out to be wrong because of rounding issues).

#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>
#include <limits>

using std::vector;
using std::string;
using std::pair;
using std::min;

typedef std::int64_t big_int;

struct Point {
    big_int x, y;
};

double distance(const Point& a, const Point& b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double minimal_distance(vector<Point> points) {

    if (points.size() == 1) return std::numeric_limits<double>::max();
    if (points.size() == 2) return distance(points[0], points[1]);

    int n = points.size();
    vector<Point> S1(n / 2);
    vector<Point> S2(n - S1.size());
    for (size_t i = 0; i < n / 2; i++)
    {
        S1[i] = points[i];
    }

    for (size_t i = S1.size(); i < n; i++)
    {
        S2[i - n / 2] = points[i];
    }

    double d = min(minimal_distance(S1), minimal_distance(S2));

    double middle = (static_cast<double>(S1[n / 2 - 1].x) + S2[0].x) / 2;
    vector<Point> P;
    for (size_t i = 0; i < S1.size(); ++i)
    {
        if ((S1[i].x + d) >= middle)
        {
            P.push_back(S1[i]);
        }
    }


    for (size_t i = 0; i < S2.size(); i++)
    {
        if ((S2[i].x - d) <= middle)
        {
            P.push_back(S2[i]);
        }

    }

    if (!P.empty())
    {
        std::sort(P.begin(), P.end(), [](const Point& a, const Point& b)
            {return a.y < b.y; }
        );
        int i = 0, j;
        while (i < P.size())
        {
            j = i + 1;
            while (j <= (i + 7) && j < P.size())
            {
                d = min(d, distance(P[i], P[j]));
                ++j;
            }
            ++i;
        }
    }

    return d;
}

int main() {
    size_t n;
    std::cin >> n;
    vector<Point> points(n);
    for (size_t i = 0; i < points.size(); ++i) {
        std::cin >> points[i].x >> points[i].y;
    }

    std::sort(points.begin(), points.end(), [](const Point& a, const Point& b)
        {return a.x < b.x; }
    );

    std::cout << std::fixed;
    std::cout << std::setprecision(9) << minimal_distance(points) << "\n";
}
