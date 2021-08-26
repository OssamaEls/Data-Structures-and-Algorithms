//Input Format.The first line of the input contains two integers 𝑛and 𝑚 — the number of tables in the
//databaseand the number of merge queries to perform, respectively.
//The second line of the input contains 𝑛 integers 𝑟𝑖 — the number of rows in the 𝑖 - th table.
//Then follow 𝑚 lines describing merge queries.Each of them contains two integers 𝑑𝑒𝑠𝑡𝑖𝑛𝑎𝑡𝑖𝑜𝑛𝑖 and
//𝑠𝑜𝑢𝑟𝑐𝑒𝑖 — the numbers of the tables to merge.
//Constraints. 1 ≤ 𝑛, 𝑚 ≤ 100 000; 0 ≤ 𝑟𝑖 ≤ 10 000; 1 ≤ 𝑑𝑒𝑠𝑡𝑖𝑛𝑎𝑡𝑖𝑜𝑛𝑖, 𝑠𝑜𝑢𝑟𝑐𝑒𝑖 ≤ 𝑛.
//Output Format.For each query print a line containing a single integer — the maximum of the sizes of all
//tables(in terms of the number of rows) after the corresponding operation.

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::max;
using std::vector;

struct DisjointSetsElement {
	int size, parent, rank;

	DisjointSetsElement(int size = 0, int parent = -1, int rank = 0) :
		size(size), parent(parent), rank(rank) {}
};

struct DisjointSets {
	int size;
	int max_table_size;
	vector <DisjointSetsElement> sets;

	DisjointSets(int size) : size(size), max_table_size(0), sets(size) {
		for (int i = 0; i < size; i++)
			sets[i].parent = i;
	}

	int getParent(int table) {
		if (table != sets[table].parent)
		{
			sets[table].parent = getParent(sets[table].parent);
		}
		return sets[table].parent;
	}

	void merge(int destination, int source) {
		int realDestination = getParent(destination);
		int realSource = getParent(source);
		if (realDestination != realSource) {
			// merge two components
			// use union by rank heuristic
						// update max_table_size
			sets[realSource].parent = realDestination;
			if (sets[realSource].rank >= sets[realDestination].rank)
			{
				sets[realDestination].rank = sets[realSource].rank + 1;
			}
			sets[realDestination].size += sets[realSource].size;
			sets[realSource].size = 0;
			max_table_size = max(max_table_size, sets[realDestination].size);
		}
	}
};

int main() {
	int n, m;
	cin >> n >> m;

	DisjointSets tables(n);
	for (auto& table : tables.sets) {
		cin >> table.size;
		tables.max_table_size = max(tables.max_table_size, table.size);
	}

	for (int i = 0; i < m; i++) {
		int destination, source;
		cin >> destination >> source;
		--destination;
		--source;

		tables.merge(destination, source);
		cout << tables.max_table_size << endl;
	}

	return 0;
}
