#include<iostream>
#include<vector>
#include<utility>

using namespace std;

class directed_graph {
    vector< pair<int, int> > * nodes;
    int n;
public:
    directed_graph(int n);
    ~directed_graph();
    void add(int from, int to, int value);
    void add_two_way(int from, int to, int value);
    friend ostream & operator<<(ostream & s, directed_graph & g);
};

directed_graph::directed_graph(int n): n(n) {
    nodes = new vector< pair<int, int> >[n];
}

directed_graph::~directed_graph() {
    delete[] nodes;
}

ostream & operator<<(ostream & s, directed_graph & g) {
    for (int i = 0; i < g.n; i++) {
        s << i << ": ";
        for (auto & e : g.nodes[i]) {
            s << "(" << e.first << ", " << e.second << ") ";
        }
        s << "\n";
    }
    return s;
}

void directed_graph::add(int from, int to, int value = 1) {
    nodes[from].push_back({to, value});
}

void directed_graph::add_two_way(int from, int to, int value = 1) {
    add(from, to, value);
    add(to, from, value);
}

int main() {
    directed_graph g(5);
    g.add_two_way(0, 1);
    g.add_two_way(0, 3);
    g.add_two_way(1, 2);
    g.add_two_way(1, 4);
    g.add_two_way(2, 4);
    g.add_two_way(3, 4);
    cout << g;
    return 0;
}