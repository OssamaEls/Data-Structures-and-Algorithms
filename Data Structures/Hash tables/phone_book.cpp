//Input Format.There is a single integer 𝑁 in the first line — the number of queries.It’s followed by 𝑁
//lines, each of them contains one query in the format described in the tasks description file.
//Constraints. 1 ≤ 𝑁 ≤ 10^5. All phone numbers consist of decimal digits, they don’t have leading zeros, and
//each of them has no more than 7 digits.All names are non - empty strings of latin letters, and each of
//them has length at most 15. It’s guaranteed that there is no person with name “not found".
//Output Format.Print the result of each find query — the name corresponding to the phone number or
//“not found" (without quotes) if there is no person in the phone book with such phone number. Output
//one result per line in the same order as the find queries are given in the input.


#include <iostream>
#include <vector>
#include <string>
#include <array>

using std::string;
using std::vector;
using std::cin;
using std::array;

struct Contact {
    string name;
    int number;
};

struct Query {
    string type, name;
    int number;
};

vector<Query> read_queries() {
    int n;
    cin >> n;
    vector<Query> queries(n);
    for (int i = 0; i < n; ++i) {
        cin >> queries[i].type;
        if (queries[i].type == "add")
            cin >> queries[i].number >> queries[i].name;
        else
            cin >> queries[i].number;
    }
    return queries;
}

void write_responses(const vector<string>& result) {
    for (size_t i = 0; i < result.size(); ++i)
        std::cout << result[i] << "\n";
}

vector<string> process_queries(const vector<Query>& queries) {
    vector<string> result;
    vector<string> contacts(10000000, "not found");

    for (size_t i = 0; i < queries.size(); i++)
    {
        if (queries[i].type == "add")
        {
            contacts[queries[i].number] = queries[i].name;
        }
        else
        {
            if (queries[i].type == "del")
            {
                contacts[queries[i].number] = "not found";
            }
            else
            {
                result.push_back(contacts[queries[i].number]);
            }
        }
    }
    return result;
}

int main() {
    write_responses(process_queries(read_queries()));
    return 0;
}