#include<iostream>
#include<vector>
#include<utility>

using namespace std;

class graph {
    vector< pair<int, int> > * nodes;
    int n;
public:
    graph(int n);
    ~graph();
    void add_directed(int from, int to, int value);
    void add_indirected(int from, int to, int value);
    friend ostream & operator<<(ostream & s, graph & g);
};

graph::graph(int n): n(n) {
    nodes = new vector< pair<int, int> >[n];
}

graph::~graph() {
    delete[] nodes;
}

ostream & operator<<(ostream & s, graph & g) {
    for (int i = 0; i < g.n; i++) {
        s << i << ": ";
        for (auto & e : g.nodes[i]) {
            s << "(" << e.first << ", " << e.second << ") ";
        }
        s << "\n";
    }
    return s;
}

void graph::add_directed(int from, int to, int value = 1) {
    nodes[from].push_back({to, value});
}

void graph::add_indirected(int from, int to, int value = 1) {
    add_directed(from, to, value);
    add_directed(to, from, value);
}

int main() {
    graph g(5);
    g.add_indirected(0, 1);
    g.add_indirected(0, 3);
    g.add_indirected(1, 2);
    g.add_indirected(1, 4);
    g.add_indirected(2, 4);
    g.add_indirected(3, 4);
    cout << g;
    return 0;
}