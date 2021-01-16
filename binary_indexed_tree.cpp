#include<iostream>
#include<vector>

using namespace std;

class binary_indexed_tree {
    int * t;
    int n;
public:
    binary_indexed_tree(int n);
    ~binary_indexed_tree();
    void add(int k, int x);
    int sum(int a, int b);
};

binary_indexed_tree::binary_indexed_tree(int n): n(n) {
    t = new int[n + 1];
    for (int i = 0; i <= n; i++) {
        t[i] = 0;
    }
}

binary_indexed_tree::~binary_indexed_tree() {
    delete[] t;
}

void binary_indexed_tree::add(int k, int x) {
    while (k <= n) {
        t[k] += x;
        k += (k & -k);
    }
}

int binary_indexed_tree::sum(int a, int b) {
    if (a != 1) {
        return sum(1, b) - sum(1, a - 1);
    }

    int s = 0;
    int k = b;
    while (k >= 1) {
        s += t[k];
        k -= (k & -k);
    }
    return s;
}

int main() {
    binary_indexed_tree t(20);
    cout << t.sum(5, 15) << "\n";
    t.add(1, 10);
    t.add(5, 7);
    cout << t.sum(1, 20) << " " << t.sum(2, 5) << " " << t.sum(1, 4) << " " << t.sum(8, 15) << "\n";
    t.add(8, 10);
    t.add(1, 2);
    t.add(20, 1);
    cout << t.sum(1, 20) << " " << t.sum(2, 5) << " " << t.sum(1, 4) << " " << t.sum(8, 15) << "\n";
    return 0;
}