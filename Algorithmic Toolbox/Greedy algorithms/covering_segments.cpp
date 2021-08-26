//Input Format.The first line of the input contains the number 𝑛 of segments.Each of the following 𝑛 lines
//contains two integers 𝑎𝑖 and 𝑏𝑖(separated by a space) defining the coordinates of endpoints of the 𝑖 - th
//segment.
//Constraints. 1 ≤ 𝑛 ≤ 100; 0 ≤ 𝑎𝑖 ≤ 𝑏𝑖 ≤ 10^9 for all 0 ≤ 𝑖 < 𝑛.
//    Output Format.Output the minimum number 𝑚 of points on the first lineand the integer coordinates
//    of 𝑚 points(separated by spaces) on the second line.You can output the points in any order.If there
//    are many such sets of points, you can output any set. (It is not difficult to see that there always exist
//        a set of points of the minimum size such that all the coordinates of the points are integers.)

#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>

using std::vector;

struct Segment {
    int start, end;
};

vector<int> optimal_points(vector<Segment>& segments) {
    std::sort(segments.begin(), segments.end(), [](const Segment& a, const Segment& b)
        {return a.end <= b.end; }
    );

    vector<int> points;
    size_t current_segment{ 0 };
    size_t last_segment{ 0 };
    while (current_segment < segments.size())
    {
        last_segment = current_segment;
        points.push_back(segments[current_segment].end);
        while (current_segment < segments.size() && segments[current_segment].start <= points.back() && segments[current_segment].end >= points.back())
        {
            ++current_segment;
        }
        if (last_segment == current_segment) ++current_segment;
    }

    return points;
}

int main() {
    int n;
    std::cin >> n;
    vector<Segment> segments(n);
    for (size_t i = 0; i < segments.size(); ++i) {
        std::cin >> segments[i].start >> segments[i].end;
    }
    vector<int> points = optimal_points(segments);
    std::cout << points.size() << "\n";
    for (size_t i = 0; i < points.size(); ++i) {
        std::cout << points[i] << " ";
    }
}