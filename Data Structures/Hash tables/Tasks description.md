## phone_book
In this task your goal is to implement a simple phone book manager. It should be able to process the
following types of user’s queries:
∙ add number name. It means that the user adds a person with name name and phone number
number to the phone book. If there exists a user with such number already, then your manager
has to overwrite the corresponding name.
∙ del number. It means that the manager should erase a person with number number from the phone
book. If there is no such person, then it should just ignore the query.
∙ find number. It means that the user looks for a person with phone number number. The manager
should reply with the appropriate name, or with string “not found" (without quotes) if there is
no such person in the book.
### Solution idea: direct addressing

## hash_chains
In this task your goal is to implement a hash table with lists chaining. You are already given the
number of buckets 𝑚 and the hash function. It is a polynomial hash function
ℎ(𝑆) = ⎛ ⎝|𝑆∑︁𝑖=0 |−1 𝑆[𝑖]𝑥𝑖 mod 𝑝⎞ ⎠ mod 𝑚 ,
where 𝑆[𝑖] is the ASCII code of the 𝑖-th symbol of 𝑆, 𝑝 = 1 000 000 007 and 𝑥 = 263. Your program
should support the following kinds of queries:
∙ add string — insert string into the table. If there is already such string in the hash table, then
just ignore the query.
∙ del string — remove string from the table. If there is no such string in the hash table, then
just ignore the query.
∙ find string — output “yes" or “no" (without quotes) depending on whether the table contains
string or not.
∙ check 𝑖 — output the content of the 𝑖-th list in the table. Use spaces to separate the elements of
the list. If 𝑖-th list is empty, output a blank line.
When inserting a new string into a hash chain, you must insert it in the beginning of the chain.

## hash_substring
In this problem your goal is to implement the Rabin–Karp’s algorithm for searching the given pattern
in the given text.

## substring_equality
In this problem, you will use hashing to design an algorithm that is able to preprocess a given string 𝑠
to answer any query of the form “are these two substrings of 𝑠 equal?” efficiently. This, in turn, is a basic
building block in many string processing algorithms.

## longest_common_substring
In the longest common substring problem one is given two strings 𝑠 and 𝑡 and the goal is to find a string 𝑤
of maximal length that is a substring of both 𝑠 and 𝑡. This is a natural measure of similarity between two
strings. The problem has applications in text comparison and compression as well as in bioinformatics.
The problem can be seen as a special case of the edit distance problem (where only insertions and
deletions are allowed). Hence, it can be solved in time 𝑂(|𝑠| · |𝑡|) using dynamic programming.
### Solution idea:
For every pair of strings 𝑠 and 𝑡, use binary search to find the length of the longest common substring. To
check whether two strings have a common substring of length 𝑘,
∙ precompute hash values of all substrings of length 𝑘 of 𝑠 and 𝑡;
∙ use a few hash functions (but not just one) to reduce the probability of a collision;
∙ store hash values of all substrings of length 𝑘 of the string 𝑠 in a hash table; then, go through all
substrings of length 𝑘 of the string 𝑡 and check whether the hash value of this substring is present in
the hash table.

## matching_with_mismatches
For an integer parameter 𝑘 and two strings 𝑡 = 𝑡0𝑡1 · · · 𝑡𝑚−1 and 𝑝 = 𝑝0𝑝1 · · · 𝑝𝑛−1, we say that
𝑝 occurs in 𝑡 at position 𝑖 with at most 𝑘 mismatches if the strings 𝑝 and 𝑡[𝑖 : 𝑖 + 𝑝) = 𝑡𝑖𝑡𝑖+1 · · · 𝑡𝑖+𝑛−1
differ in at most 𝑘 positions.
### Solution idea
Start by computing hash values of prefixes of 𝑡 and 𝑝 and their partial sums. This allows you to compare any
two substrings of 𝑡 and 𝑝 in expected constant time. For each candidate position 𝑖, perform 𝑘 steps of the
form “find the next mismatch”. Each such mismatch can be found using binary search. Overall, this gives an
algorithm running in time 𝑂(𝑛𝑘 log 𝑛).
