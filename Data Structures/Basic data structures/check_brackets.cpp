//Input Format.Input contains one string 𝑆 which consists of big and small latin letters, digits, punctuation
//marks and brackets from the set[]{}().
//Constraints.The length of 𝑆 is at least 1 and at most 10^5.
//Output Format.If the code in 𝑆 uses brackets correctly, output “Success" (without the quotes). Otherwise,
//output the 1 - based index of the first unmatched closing bracket, and if there are no unmatched closing
//brackets, output the 1 - based index of the first unmatched opening bracket.

#include <iostream>
#include <stack>
#include <string>

struct Bracket {
    Bracket(char type, int position) :
        type(type),
        position(position)
    {}

    bool Matchc(char c) {
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }

    char type;
    int position;
};

int main() {
    std::string text;
    getline(std::cin, text);
    std::string answer = "";
    std::stack <Bracket> opening_brackets_stack;
    for (int position = 0; position < text.length(); ++position) {
        char next = text[position];

        if (next == '(' || next == '[' || next == '{') {
            // Process opening bracket, write your code here
            opening_brackets_stack.push({ next, position + 1 });
        }

        else {
            if (opening_brackets_stack.empty() && (next == ')' || next == ']' || next == '}'))
            {
                // Process closing bracket, write your code here
                answer = std::to_string(position + 1);
                break;
            }

            if (next == ')' || next == ']' || next == '}') {
                Bracket top = opening_brackets_stack.top();
                opening_brackets_stack.pop();
                if (!top.Matchc(next))
                {
                    answer = std::to_string(position + 1);
                    break;
                }
            }
        }
    }

    if (answer.empty())
    {
        if (opening_brackets_stack.empty())
        {
            answer = "Success";
        }
        else
        {
            answer = std::to_string(opening_brackets_stack.top().position);
        }
    }
    // Printing answer, write your code here
    std::cout << answer;
    return 0;
}
