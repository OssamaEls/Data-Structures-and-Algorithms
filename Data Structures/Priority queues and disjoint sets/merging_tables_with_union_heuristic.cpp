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
	int size, parent, rank, number_with_content;

	DisjointSetsElement(int size = 0, int parent = -1, int rank = 0, int number_with_content = -1) :
		size(size), parent(parent), rank(rank), number_with_content(number_with_content) {}
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
		//if (realDestination != realSource) {
		//	// merge two components
		//	// use union by rank heuristic
		//				// update max_table_size
		if (realDestination == realSource) return;
		if (sets[realDestination].rank > sets[realSource].rank)
		{
			sets[realSource].parent = realDestination;
		}
		else
		{
			sets[realDestination].parent = realSource;
			if (sets[realDestination].rank == sets[realSource].rank)
			{
				++sets[realSource].rank;
			}
		}
		sets[realDestination].size = sets[sets[realDestination].number_with_content].size;
		sets[sets[realDestination].number_with_content].number_with_content = realDestination;
		sets[realDestination].number_with_content = realDestination;
		sets[realDestination].size += sets[sets[realSource].number_with_content].size;
		sets[sets[realSource].number_with_content].size = 0;
		sets[sets[realSource].number_with_content].number_with_content = realDestination;
		sets[realSource].number_with_content = realDestination;
		max_table_size = max(max_table_size, sets[realDestination].size);
	}
};

int main() {
	int n, m;
	cin >> n >> m;

	DisjointSets tables(n);
	int k = 0;
	for (auto& table : tables.sets) {
		cin >> table.size;
		table.number_with_content = k;
		tables.max_table_size = max(tables.max_table_size, table.size);
		++k;
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