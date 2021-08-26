//Input Format.There is a single integer 𝑚 in the first line — the number of buckets you should have.The
//next line contains the number of queries 𝑁.It’s followed by 𝑁 lines, each of them contains one query
//in the format described above.
//Constraints. 1 ≤ 𝑁 ≤ 10^5; 𝑁/5 ≤ 𝑚 ≤ 𝑁.All the strings consist of latin letters.Each of them is non - empty
//and has length at most 15.
//Output Format.Print the result of each of the find and check queries, one result per line, in the same
//order as these queries are given in the input.

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <forward_list>

using std::string;
using std::vector;
using std::cin;

struct Query {
    string type, s;
    size_t ind;
};

class QueryProcessor {
    int bucket_count;
    // store all strings in one vector
    vector<std::forward_list<string>> elems;
    size_t hash_func(const string& s) const {
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return hash % bucket_count;
    }

public:
    explicit QueryProcessor(int bucket_count) : bucket_count(bucket_count) { elems.resize(bucket_count); }

    Query readQuery() const {
        Query query;
        cin >> query.type;
        if (query.type != "check")
            cin >> query.s;
        else
            cin >> query.ind;
        return query;
    }

    void writeSearchResult(bool was_found) const {
        std::cout << (was_found ? "yes\n" : "no\n");
    }

    void processQuery(const Query& query) {
        if (query.type == "check")
        {
            for (auto it = elems[query.ind].begin(); it != elems[query.ind].end(); ++it)
            {
                std::cout << *it << " ";
            }
            std::cout << "\n";
        }
        else
        {
            int idx = hash_func(query.s);
            auto it = std::find(elems[idx].begin(), elems[idx].end(), query.s);
            if (query.type == "find")
                writeSearchResult(it != elems[idx].end());
            else if (query.type == "add")
            {
                if (it == elems[idx].end())
                    elems[idx].push_front(query.s);
            }
            else if (query.type == "del")
            {
                if (it != elems[idx].end())
                    elems[idx].remove(*it);
            }
        }
    }

    void processQueries() {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i)
            processQuery(readQuery());
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    int bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    return 0;
}
