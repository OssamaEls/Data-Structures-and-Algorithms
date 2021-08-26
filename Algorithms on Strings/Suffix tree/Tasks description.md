## trie
Construct a trie from a collection of patterns.

## trie_matching
Implement TrieMatching algorithm

## trie_matching_extended
Extend TrieMatching algorithm so that it handles correctly cases when one of the patterns is a
prefix of another one.

## suffix_tree
Construct the suffix tree of a string.
### Note: naive algorithm is sufficient for this challenge.

## non_shared_substring
Find the shortest substring of one string that does not appear in another string.
### Solution idea
Construct the suffix tree of a string Text1#Text2$ (where # and $ are new symbols).
Denote **r_node** a node that is used to define a prefix from Text2 and **l_node** a node that is used to define a prefix from Text1.
Any **l_node** that is not an **r_node** and has an **r_node** parent is a good candidate. 





