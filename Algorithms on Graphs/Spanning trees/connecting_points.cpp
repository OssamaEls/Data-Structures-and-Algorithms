//Input Format.The first line contains the number 𝑛 of points.Each of the following 𝑛 lines defines a point
//(𝑥𝑖, 𝑦𝑖).
//Constraints. 1 ≤ 𝑛 ≤ 200; −10^3 ≤ 𝑥𝑖, 𝑦𝑖 ≤ 10^3 are integers.All points are pairwise different, no three
//points lie on the same line.
//Output Format.Output the minimum total length of segments.The absolute value of the difference
//between the answer of your programand the optimal value should be at most 10−6.To ensure this,
//output your answer with at least seven digits after the decimal point(otherwise your answer, while
//	being computed correctly, can turn out to be wrong because of rounding issues).

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <set>

using std::vector;
using std::set;
using std::pair;
using std::sqrt;
using std::pow;
typedef std::pair<double, pair<int, int>> pi;

struct DisjointSetsElement {
	int size, parent, rank;

	DisjointSetsElement(int size = 0, int parent = -1, int rank = 0) :
		size(size), parent(parent), rank(rank) {}
};

struct DisjointSets {
	int size;
	vector <DisjointSetsElement> sets;

	DisjointSets(int size) : size(size), sets(size) {
		for (int i = 0; i < size; i++)
			sets[i].parent = i;
	}

	int getParent(int i) {
		if (i != sets[i].parent)
		{
			sets[i].parent = getParent(sets[i].parent);
		}
		return sets[i].parent;
	}

	void merge(int i, int j) {
		int i_id = getParent(i);
		int j_id = getParent(j);
		if (i_id != j_id) {
			// merge two components
			// use union by rank heuristic
						// update max_table_size
			if (sets[i_id].rank > sets[j_id].rank)
			{
				sets[j_id].parent = i_id;
			}
			else
			{
				sets[i_id].parent = j_id;
				if (sets[i_id].rank == sets[j_id].rank) ++sets[j_id].rank;
			}
		}
	}
};

double minimum_distance(vector<int> x, vector<int> y) {
	double result = 0.;
	const int n = x.size();
	vector<pi> distances;
	double dist;
	for (size_t i = 0; i < n - 1; i++)
	{
		for (size_t j = i + 1; j < n; j++)
		{
			dist = sqrt(pow(x[i] - x[j], 2) + pow(y[i] - y[j], 2));
			distances.push_back({ dist, { i,j } });
		}
	}


	std::sort(distances.begin(), distances.end());

	DisjointSets nodes(n);
	int u, v;
	for (size_t i = 0; i < distances.size(); i++)
	{
		u = distances[i].second.first;
		v = distances[i].second.second;
		if (nodes.getParent(u) != nodes.getParent(v))
		{
			result += distances[i].first;
			nodes.merge(u, v);
		}

	}

	return result;
}

int main() {
	size_t n;
	std::cin >> n;
	vector<int> x(n), y(n);
	for (size_t i = 0; i < n; i++) {
		std::cin >> x[i] >> y[i];
	}
	std::cout << std::setprecision(10) << minimum_distance(x, y) << std::endl;

}