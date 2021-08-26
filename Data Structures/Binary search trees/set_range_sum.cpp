//Input Format.Initially the set 𝑆 is empty.The first line contains 𝑛 — the number of operations.The next
//𝑛 lines contain operations.Each operation is one of the following :
//∙ “ + i" — which means add some integer (not 𝑖, see below) to 𝑆,
//∙ “ - i" — which means del some integer (not 𝑖, see below)from 𝑆,
//∙ “ ? i" — which means find some integer (not 𝑖, see below)in 𝑆,
//∙ “s l r" — which means compute the sum of all elements of 𝑆 within some range of values (not
//from 𝑙 to 𝑟, see below).
//However, to make sure that your solution can work in an online fashion, each request will actually
//depend on the result of the last sum request.Denote 𝑀 = 1 000 000 001. At any moment, let 𝑥 be
//the result of the last sum operation, or just 0 if there were no sum operations before.Then
//∙ “ + i" means add((𝑖 + 𝑥) mod 𝑀),
//∙ “ - i" means del((𝑖 + 𝑥) mod 𝑀),
//∙ “ ? i" means find((𝑖 + 𝑥) mod 𝑀),
//∙ “s l r" means sum((𝑙 + 𝑥) mod 𝑀, (𝑟 + 𝑥) mod 𝑀).
//Constraints. 1 ≤ 𝑛 ≤ 100 000; 0 ≤ 𝑖 ≤ 10^9.
//Output Format.For each find request, just output “Found" or “Not found" (without quotes; note that the
//    first letter is capital) depending on whether(𝑖 + 𝑥) mod 𝑀 is in 𝑆 or not.For each sum query, output
//    the sum of all the values 𝑣 in 𝑆 such that((𝑙 + 𝑥) mod 𝑀) ≤ 𝑣 ≤((𝑟 + 𝑥) mod 𝑀) (it is guaranteed that
//        in all the tests((𝑙 + 𝑥) mod 𝑀) ≤((𝑟 + 𝑥) mod 𝑀)), where 𝑥 is the result of the last sum operation
//    or 0 if there was no previous sum operation.

#include <cstdio>
#include <iostream>

// Splay tree implementation

// Vertex of a splay tree
struct Vertex {
    int key;
    // Sum of all the keys in the subtree - remember to update
    // it after each operation that changes the tree.
    long long sum;
    Vertex* left;
    Vertex* right;
    Vertex* parent;

    Vertex(int key, long long sum, Vertex* left, Vertex* right, Vertex* parent)
        : key(key), sum(sum), left(left), right(right), parent(parent) {}
};

void update(Vertex* v) {
    if (v == NULL) return;
    v->sum = v->key + (v->left != NULL ? v->left->sum : 0ll) + (v->right != NULL ? v->right->sum : 0ll);
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
Vertex* find(Vertex*& root, int key) {
    Vertex* v = root;
    Vertex* last = root;
    Vertex* next = NULL;
    while (v != NULL) {
        if (v->key >= key && (next == NULL || v->key < next->key)) {
            next = v;
        }
        last = v;
        if (v->key == key) {
            break;
        }
        if (v->key < key) {
            v = v->right;
        }
        else {
            v = v->left;
        }
    }
    splay(root, last);
    return next;
}

void split(Vertex* root, int key, Vertex*& left, Vertex*& right) {
    right = find(root, key);
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

// Code that uses splay tree to solve the problem

Vertex* root = NULL;

void insert(int x) {
    Vertex* left = NULL;
    Vertex* right = NULL;
    Vertex* new_vertex = NULL;
    split(root, x, left, right);
    if (right == NULL || right->key != x) {
        new_vertex = new Vertex(x, x, NULL, NULL, NULL);
    }
    root = merge(merge(left, new_vertex), right);
}

void erase(int x) {
    // Implement erase yourself
    Vertex* left = NULL;
    Vertex* right = NULL;
    Vertex* new_right = NULL;
    split(root, x, left, right);

    if (right != NULL)
    {
        if (right->key != x)
        {
            root = merge(left, right);
        }
        else
        {
            new_right = right->right;
            right->right = NULL;
            if (new_right != NULL) {
                new_right->parent = NULL;
            }
            root = merge(left, new_right);
        }
    }
    else
    {
        root = left;
    }
}

bool find(int x) {
    // Implement find yourself
    Vertex* v = find(root, x);
    splay(root, v);
    update(v);
    if (v == NULL) return false;
    return v->key == x;
}

long long sum(int from, int to) {
    Vertex* left = NULL;
    Vertex* middle = NULL;
    Vertex* right = NULL;
    split(root, from, left, middle);
    split(middle, to + 1, middle, right);
    long long ans = 0;
    // Complete the implementation of sum
    if (middle != NULL) ans = middle->sum;
    root = merge(merge(left, middle), right);
    return ans;
}

const int MODULO = 1000000001;

int main() {
    int n;
    scanf("%d", &n);
    int last_sum_result = 0;
    for (int i = 0; i < n; i++) {
        char buffer[10];
        scanf("%s", buffer);
        char type = buffer[0];
        switch (type) {
        case '+': {
            int x;
            scanf("%d", &x);
            insert((x + last_sum_result) % MODULO);
        } break;
        case '-': {
            int x;
            scanf("%d", &x);
            erase((x + last_sum_result) % MODULO);
        } break;
        case '?': {
            int x;
            scanf("%d", &x);
            printf(find((x + last_sum_result) % MODULO) ? "Found\n" : "Not found\n");
        } break;
        case 's': {
            int l, r;
            scanf("%d %d", &l, &r);
            long long res = sum((l + last_sum_result) % MODULO, (r + last_sum_result) % MODULO);
            printf("%lld\n", res);
            last_sum_result = int(res % MODULO);
        }
        }
    }
    return 0;
}