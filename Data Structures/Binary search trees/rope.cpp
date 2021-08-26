//Input Format.The first line contains the initial string 𝑆.
//The second line contains the number of queries 𝑞.
//Next 𝑞 lines contain triples of integers 𝑖, 𝑗, 𝑘.
//Constraints. 𝑆 contains only lowercase english letters. 1 ≤ | 𝑆 | ≤ 300 000; 1 ≤ 𝑞 ≤ 100 000; 0 ≤ 𝑖 ≤ 𝑗 ≤
//𝑛 − 1; 0 ≤ 𝑘 ≤ 𝑛 −(𝑗 − 𝑖 + 1).
//Output Format.Output the string after all 𝑞 queries

#include <cstdio>
#include <string>
#include <iostream>

// Splay tree implementation

// Vertex of a splay tree
struct Vertex {
    char key;
    // Sum of all the keys in the subtree - remember to update
    // it after each operation that changes the tree.
    int size;
    Vertex* left;
    Vertex* right;
    Vertex* parent;

    Vertex(char key, int size, Vertex* left, Vertex* right, Vertex* parent)
        : key(key), size(size), left(left), right(right), parent(parent) {}
};

void update(Vertex* v) {
    if (v == NULL) return;
    v->size = 1 + (v->left != NULL ? v->left->size : 0) + (v->right != NULL ? v->right->size : 0);
    if (v->left != NULL) {
        v->left->parent = v;
    }
    if (v->right != NULL) {
        v->right->parent = v;
    }
}

void small_rotation(Vertex* v) {
    Vertex* parent = v->parent;
    if (parent == NULL) {
        return;
    }
    Vertex* grandparent = v->parent->parent;
    if (parent->left == v) {
        Vertex* m = v->right;
        v->right = parent;
        parent->left = m;
    }
    else {
        Vertex* m = v->left;
        v->left = parent;
        parent->right = m;
    }
    update(parent);
    update(v);
    v->parent = grandparent;
    if (grandparent != NULL) {
        if (grandparent->left == parent) {
            grandparent->left = v;
        }
        else {
            grandparent->right = v;
        }
    }
}

void big_rotation(Vertex* v) {
    if (v->parent->left == v && v->parent->parent->left == v->parent) {
        // Zig-zig
        small_rotation(v->parent);
        small_rotation(v);
    }
    else if (v->parent->right == v && v->parent->parent->right == v->parent) {
        // Zig-zig
        small_rotation(v->parent);
        small_rotation(v);
    }
    else {
        // Zig-zag
        small_rotation(v);
        small_rotation(v);
    }
}

// Makes splay of the given vertex and makes
// it the new root.
void splay(Vertex*& root, Vertex* v) {
    if (v == NULL) return;
    while (v->parent != NULL) {
        if (v->parent->parent == NULL) {
            small_rotation(v);
            break;
        }
        big_rotation(v);
    }
    root = v;
}

// Searches for the given key in the tree with the given root
// and calls splay for the deepest visited node after that.
// If found, returns a pointer to the node with the given key.
// Otherwise, returns a pointer to the node with the smallest
// bigger key (next value in the order).
// If the key is bigger than all keys in the tree, 
// returns NULL.
Vertex* find(Vertex*& root, int size) {

    if (root == NULL || size > root->size) return NULL;

    int s = root->left == NULL ? 0 : root->left->size;
    int k = size;
    Vertex* v = root;
    while (k != (s + 1))
    {
        if (k < (s + 1))
        {
            v = v->left;
            s = (v->left == NULL) ? 0 : v->left->size;
        }
        else
        {
            v = v->right;
            k = k - s - 1;
            s = (v->left == NULL) ? 0 : v->left->size;
        }
    }

    splay(root, v);
    return root;
}

void split(Vertex* root, int size, Vertex*& left, Vertex*& right) {
    right = find(root, size);
    splay(root, right);
    if (right == NULL) {
        left = root;
        return;
    }
    left = right->left;
    right->left = NULL;
    if (left != NULL) {
        left->parent = NULL;
    }
    update(left);
    update(right);
}

Vertex* merge(Vertex* left, Vertex* right) {
    if (left == NULL) return right;
    if (right == NULL) return left;
    Vertex* min_right = right;
    while (min_right->left != NULL) {
        min_right = min_right->left;
    }
    splay(right, min_right);
    right->left = left;
    update(right);
    return right;
}

void in_order_traversal(Vertex* v)
{
    if (v == NULL) return;
    in_order_traversal(v->left);
    std::cout << v->key;
    in_order_traversal(v->right);
}




class Rope {
    std::string s;
public:
    Rope(const std::string& s) : s(s) {
    }

    void process(int i, int j, int k) {
        std::string t = s.substr(0, i) + s.substr(j + 1);
        s = t.substr(0, k) + s.substr(i, j - i + 1) + t.substr(k);
    }

    std::string result() {
        return s;
    }
};

int main() {
    std::ios_base::sync_with_stdio(0);

    std::string s;
    std::cin >> s;
    Vertex* root = new Vertex(s[s.size() - 1], s.size(), NULL, NULL, NULL);
    Vertex* v = root;
    if (s.size() > 1)
    {
        for (int i = s.size() - 2; i > -1; --i)
        {
            v->left = new Vertex(s[i], i + 1, NULL, NULL, v);
            v = v->left;
        }
    }

    int actions;
    std::cin >> actions;
    for (int action_index = 0; action_index < actions; ++action_index)
    {
        int i, j, k;
        std::cin >> i >> j >> k;
        Vertex* left = NULL;
        Vertex* middle = NULL;
        Vertex* right = NULL;
        Vertex* left2 = NULL;
        Vertex* right2 = NULL;
        split(root, j + 2, left, right);
        split(left, i + 1, left, middle);
        Vertex* T2 = merge(left, right);
        split(T2, k + 1, left2, right2);
        root = merge(merge(left2, middle), right2);
    }

    in_order_traversal(root);

    //Rope rope(s);
    //int actions;
    //std::cin >> actions;
    //for (int action_index = 0; action_index < actions; ++action_index) {
    //	int i, j, k;
    //	std::cin >> i >> j >> k;
    //	rope.process(i, j, k);
    //}
    //std::cout << rope.result() << std::endl;
    return 0;
}
