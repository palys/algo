#include<iostream>

using namespace std;

class segment_tree {
    int * t;
    int n;
    int (*f) (int, int);
public:
    segment_tree(int n, int (*f) (int, int));
    ~segment_tree();
    void add(int k, int x);
    int query(int a, int b);
};

segment_tree::segment_tree(int n, int (*f) (int, int)): n(n), f(f) {
    t = new int[2 * n];
    for (int i = 0; i < 2 * n; i++) {
        t[i] = 0;
    }
}

segment_tree::~segment_tree() {
    delete[] t;
}

void segment_tree::add(int k, int x) {
    k += n;
    t[k] += x;
    for (k >>= 1; k >= 1; k >>= 1) {
        t[k] = f(t[k << 1], t[(k << 1) + 1]);
    }
}

int segment_tree::query(int a, int b) {
    a += n;
    b += n;
    int s = 0;
    while (a <= b) {
        if (a & 1) {
            s = f(s, t[a++]);
        }
        if (!(b & 1)) {
            s = f(s, t[b--]);
        }
        a >>= 1;
        b >>= 1;
    }
    return s;
}

int add(int a, int b) {
    return a + b;
}

int max(int a, int b) {
    return a < b ? b : a;
}

void test(segment_tree & t) {
    cout << t.query(5, 15) << "\n";
    t.add(1, 10);
    t.add(5, 7);
    cout << t.query(1, 20) << " " << t.query(2, 5) << " " << t.query(1, 4) << " " << t.query(8, 15) << "\n";
    t.add(8, 10);
    t.add(1, 2);
    t.add(20, 1);
    cout << t.query(1, 20) << " " << t.query(2, 5) << " " << t.query(1, 4) << " " << t.query(8, 15) << "\n";
}

int main() {
    segment_tree t_sum(32, add), t_max(64, max);
    test(t_sum);
    test(t_max);
    return 0;
}