## tree-orders
You are given a rooted binary tree. Build and output its in-order, pre-order and post-order traversals.

## is_bst
You are given a binary tree with integers as its keys. You need to test whether it is a correct binary
search tree. The definition of the binary search tree is the following: for any node of the tree, if its
key is 𝑥, then for any node in its left subtree its key must be strictly less than 𝑥, and for any node in
its right subtree its key must be strictly greater than 𝑥. In other words, smaller elements are to the
left, and bigger elements are to the right. You need to check whether the given binary tree structure
satisfies this condition. You are guaranteed that the input contains a valid binary tree. That is, it is a
tree, and each node has at most two children.

## is_bst_advanced
You are given a binary tree with integers as its keys. You need to test whether it is a correct binary
search tree. Note that there can be duplicate integers in the tree, and this is allowed. The definition of
the binary search tree in such case is the following: for any node of the tree, if its key is 𝑥, then for any
node in its left subtree its key must be strictly less than 𝑥, and for any node in its right subtree its key
must be greater than or equal to 𝑥. In other words, smaller elements are to the left, bigger elements
are to the right, and duplicates are always to the right. You need to check whether the given binary
tree structure satisfies this condition. You are guaranteed that the input contains a valid binary tree.
That is, it is a tree, and each node has at most two children.


## set_range_sum
Implement a data structure that stores a set 𝑆 of integers with the following allowed operations:
∙ add(𝑖) — add integer 𝑖 into the set 𝑆 (if it was there already, the set doesn’t change).
∙ del(𝑖) — remove integer 𝑖 from the set 𝑆 (if there was no such element, nothing happens).
∙ find(𝑖) — check whether 𝑖 is in the set 𝑆 or not.
∙ sum(𝑙, 𝑟) — output the sum of all elements 𝑣 in 𝑆 such that 𝑙 ≤ 𝑣 ≤ 𝑟.
### Solution idea: splay tree. 

## rope
You are given a string 𝑆 and you have to process 𝑛 queries. Each query is described by three integers
𝑖, 𝑗, 𝑘 and means to cut substring 𝑆[𝑖..𝑗] (𝑖 and 𝑗 are 0-based) from the string and then insert it after the
𝑘-th symbol of the remaining string (if the symbols are numbered from 1). If 𝑘 = 0, 𝑆[𝑖..𝑗] is inserted
in the beginning.
### Solution idea: use order statistics.
