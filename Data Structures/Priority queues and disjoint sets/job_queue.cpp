//Input Format.The first line of the input contains integers 𝑛and 𝑚.
//The second line contains 𝑚 integers 𝑡𝑖 — the times in seconds it takes any thread to process 𝑖 - th job.
//The times are given in the same order as they are in the list from which threads take jobs.
//Threads are indexed starting from 0.
//Constraints. 1 ≤ 𝑛 ≤ 10^5; 1 ≤ 𝑚 ≤ 10^5; 0 ≤ 𝑡𝑖 ≤ 10^9.
//Output Format.Output exactly 𝑚 lines.𝑖 - th line(0 - based index is used) should contain
// two space-separated integers — the 0 - based index of the thread which will process the 𝑖 - th job and the time
//in seconds when it will start processing that job.

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <utility>

using std::vector;
using std::cin;
using std::cout;

typedef std::pair<long long, int> pi;

class JobQueue {
private:
    int num_workers_;
    vector<int> jobs_;

    vector<int> assigned_workers_;
    vector<long long> start_times_;

    void WriteResponse() const {
        for (int i = 0; i < jobs_.size(); ++i) {
            cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
        }
    }

    void ReadData() {
        int m;
        cin >> num_workers_ >> m;
        jobs_.resize(m);
        for (int i = 0; i < m; ++i)
            cin >> jobs_[i];
    }

    bool myGreater(const std::pair<long long, int> a, const std::pair<long long, int> b)
    {
        return (a.first != b.first) ? (a.first < b.first) : (a.second < b.second);
    }

    void AssignJobs() {
        // TODO: replace this code with a faster algorithm.

        //assigned_workers_.resize(jobs_.size());
        //start_times_.resize(jobs_.size());
        //vector<long long> next_free_time(num_workers_, 0);
        //for (int i = 0; i < jobs_.size(); ++i) {
        //    int duration = jobs_[i];
        //    int next_worker = 0;
        //    for (int j = 0; j < num_workers_; ++j) {
        //        if (next_free_time[j] < next_free_time[next_worker])
        //            next_worker = j;
        //    }
        //    assigned_workers_[i] = next_worker;
        //    start_times_[i] = next_free_time[next_worker];
        //    next_free_time[next_worker] += duration;
        //}

        assigned_workers_.resize(jobs_.size());
        start_times_.resize(jobs_.size());
        // pq: next_free_time
        std::priority_queue<pi, vector<pi>, std::greater<pi>> pq;
        int i;
        std::pair<long long, int> old_pair;
        for (i = 0; i < std::min(num_workers_, static_cast<int>(jobs_.size())); i++)
        {
            pq.push({ jobs_[i],i });
            assigned_workers_[i] = i;
            start_times_[i] = 0;
        }
        if (i == jobs_.size())
        {
            return;
        }
        else {
            while (i < jobs_.size())
            {
                old_pair = pq.top();
                pq.pop();
                pq.push({ old_pair.first + jobs_[i],old_pair.second });
                assigned_workers_[i] = old_pair.second;
                start_times_[i] = old_pair.first;
                ++i;
            }
        }
    }

public:
    void Solve() {
        ReadData();
        AssignJobs();
        WriteResponse();
    }
};

template<typename T>
void print_queue(T q) { // NB: pass by value so the print uses a copy
    while (!q.empty()) {
        std::cout << q.top() << ' ';
        q.pop();
    }
    std::cout << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    JobQueue job_queue;
    job_queue.Solve();
    return 0;
}