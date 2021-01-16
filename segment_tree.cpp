#include<iostream>

using namespace std;

class segment_tree {
    int * t;
    int n;
public:
    segment_tree(int n);
    ~segment_tree();
    void modify(int k, int x);
    int query(int a, int b);
};

segment_tree::segment_tree(int n): n(n) {
    t = new int[2 * n];
    for (int i = 0; i < 2 * n; i++) {
        t[i] = 0;
    }
}

segment_tree::~segment_tree() {
    delete[] t;
}

void segment_tree::modify(int k, int x) {
    k += n;
    t[k] += x;
    for (k >>= 1; k >= 1; k >>= 1) {
        t[k] = t[k << 1] + t[(k << 1) + 1];
    }
}

int segment_tree::query(int a, int b) {
    a += n;
    b += n;
    int s = 0;
    while (a <= b) {
        if (a & 1) {
            s += t[a++];
        }
        if (!(b & 1)) {
            s += t[b--];
        }
        a >>= 1;
        b >>= 1;
    }
    return s;
}

int main() {
    segment_tree t(32);
    cout << t.query(5, 15) << "\n";
    t.modify(1, 10);
    t.modify(5, 7);
    cout << t.query(1, 20) << " " << t.query(2, 5) << " " << t.query(1, 4) << " " << t.query(8, 15) << "\n";
    t.modify(8, 10);
    t.modify(1, 2);
    t.modify(20, 1);
    cout << t.query(1, 20) << " " << t.query(2, 5) << " " << t.query(1, 4) << " " << t.query(8, 15) << "\n";
    return 0;
}