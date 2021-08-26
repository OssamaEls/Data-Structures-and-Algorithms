//Input Format.The first line of the input contains the size 𝑆 of the bufferand the number 𝑛 of incoming
//network packets.Each of the next 𝑛 lines contains two numbers.𝑖 - th line contains the time of arrival
//𝐴𝑖 and the processing time 𝑃𝑖(both in milliseconds) of the 𝑖 - th packet.It is guaranteed that the
//sequence of arrival times is non - decreasing(however, it can contain the exact same times of arrival in
//    milliseconds — in this case the packet which is earlier in the input is considered to have arrived earlier).
//Constraints.All the numbers in the input are integers. 1 ≤ 𝑆 ≤ 10^5; 0 ≤ 𝑛 ≤ 10^5; 0 ≤ 𝐴𝑖 ≤ 10^6;
//0 ≤ 𝑃𝑖 ≤ 10^3; 𝐴𝑖 ≤ 𝐴𝑖 + 1 for 1 ≤ 𝑖 ≤ 𝑛 − 1.
//Output Format.For each packet output either the moment of time(in milliseconds) when the processor
//began processing it or −1 if the packet was dropped(output the answers for the packets in the same
//    order as the packets are given in the input).

#include <iostream>
#include <queue>
#include <vector>

struct Request {
    Request(int arrival_time, int process_time) :
        arrival_time(arrival_time),
        process_time(process_time)
    {}

    int arrival_time;
    int process_time;
};

struct Response {
    Response(bool dropped, int start_time) :
        dropped(dropped),
        start_time(start_time)
    {}

    bool dropped;
    int start_time;
};

class Buffer {
public:
    Buffer(int size) :
        size_(size),
        finish_time_()
    {}

    Response Process(const Request& request) {
        if (finish_time_.empty())
        {
            finish_time_.push(request.arrival_time + request.process_time);
            return { false, request.arrival_time };
        }

        bool finished = true;
        while (finished)
        {
            while (request.arrival_time >= finish_time_.front())
            {
                finish_time_.pop();
                if (finish_time_.empty())
                {
                    finished = false;
                    break;
                }
            }
            finished = false;
        }


        if (finish_time_.size() == size_)
        {
            return { true, -1 };
        }

        if (finish_time_.empty())
        {
            finish_time_.push(request.arrival_time + request.process_time);
            return { false, request.arrival_time };
        }

        finish_time_.push(finish_time_.back() + request.process_time);
        return { false, finish_time_.back() - request.process_time };
    }

private:
    int size_;
    std::queue <int> finish_time_;
};

std::vector <Request> ReadRequests() {
    std::vector <Request> requests;
    int count;
    std::cin >> count;
    for (int i = 0; i < count; ++i) {
        int arrival_time, process_time;
        std::cin >> arrival_time >> process_time;
        requests.push_back(Request(arrival_time, process_time));
    }
    return requests;
}

std::vector <Response> ProcessRequests(const std::vector <Request>& requests, Buffer* buffer) {
    std::vector <Response> responses;
    for (int i = 0; i < requests.size(); ++i)
        responses.push_back(buffer->Process(requests[i]));
    return responses;
}

void PrintResponses(const std::vector <Response>& responses) {
    for (int i = 0; i < responses.size(); ++i)
        std::cout << (responses[i].dropped ? -1 : responses[i].start_time) << std::endl;
}

int main() {
    int size;
    std::cin >> size;
    std::vector <Request> requests = ReadRequests();

    Buffer buffer(size);
    std::vector <Response> responses = ProcessRequests(requests, &buffer);

    PrintResponses(responses);

    return 0;
}
