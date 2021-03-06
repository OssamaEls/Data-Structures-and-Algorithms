## tree-orders
You are given a rooted binary tree. Build and output its in-order, pre-order and post-order traversals.

## is_bst
You are given a binary tree with integers as its keys. You need to test whether it is a correct binary
search tree. The definition of the binary search tree is the following: for any node of the tree, if its
key is π₯, then for any node in its left subtree its key must be strictly less than π₯, and for any node in
its right subtree its key must be strictly greater than π₯. In other words, smaller elements are to the
left, and bigger elements are to the right. You need to check whether the given binary tree structure
satisfies this condition. You are guaranteed that the input contains a valid binary tree. That is, it is a
tree, and each node has at most two children.

## is_bst_advanced
You are given a binary tree with integers as its keys. You need to test whether it is a correct binary
search tree. Note that there can be duplicate integers in the tree, and this is allowed. The definition of
the binary search tree in such case is the following: for any node of the tree, if its key is π₯, then for any
node in its left subtree its key must be strictly less than π₯, and for any node in its right subtree its key
must be greater than or equal to π₯. In other words, smaller elements are to the left, bigger elements
are to the right, and duplicates are always to the right. You need to check whether the given binary
tree structure satisfies this condition. You are guaranteed that the input contains a valid binary tree.
That is, it is a tree, and each node has at most two children.


## set_range_sum
Implement a data structure that stores a set π of integers with the following allowed operations:
β add(π) β add integer π into the set π (if it was there already, the set doesnβt change).
β del(π) β remove integer π from the set π (if there was no such element, nothing happens).
β find(π) β check whether π is in the set π or not.
β sum(π, π) β output the sum of all elements π£ in π such that π β€ π£ β€ π.
### Solution idea: splay tree. 

## rope
You are given a string π and you have to process π queries. Each query is described by three integers
π, π, π and means to cut substring π[π..π] (π and π are 0-based) from the string and then insert it after the
π-th symbol of the remaining string (if the symbols are numbered from 1). If π = 0, π[π..π] is inserted
in the beginning.
### Solution idea: use order statistics.
