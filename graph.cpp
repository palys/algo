#include<iostream>
#include<vector>
#include<utility>
#include<tuple>

using namespace std;

class graph {
    vector< pair<int, int> > * nodes;
    int n;
    bool * visited;
public:
    graph(int n);
    ~graph();
    void add(int from, int to, int value);
    void dfs(int start);
    void clear_visited();
    bool is_connected();
    vector<tuple<int, int, int> > edges();
    friend ostream & operator<<(ostream & s, graph & g);
};

graph::graph(int n): n(n) {
    nodes = new vector< pair<int, int> >[n];
    visited = new bool[n];
    for (int i = 0; i < n; i++) {
        visited[i] = false;
    }
}

graph::~graph() {
    delete[] nodes;
}

void graph::dfs(int start) {
    if (visited[start]) {
        return;
    }
    visited[start] = true;
    for (auto & edge : nodes[start]) {
        dfs(edge.first);
    }
}

void graph::clear_visited() {
    for (int i = 0; i < n; i++) {
        visited[i] = false;
    }
}

bool graph::is_connected() {
    clear_visited();
    dfs(0);
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            return false;
        }
    }
    return true;
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

void graph::add(int from, int to, int value = 1) {
    nodes[from].push_back({to, value});
    nodes[to].push_back({from, value});
}

vector<tuple<int, int, int> > graph::edges() {
    vector<tuple<int, int, int> > v;
    for (int i = 0; i < n; i++) {
        for (auto & e : nodes[i]) {
            v.push_back({i, e.first, e.second});
        }
    }
    return v;
}

void test_connected() {
    graph g(5);
    g.add(0, 1);
    g.add(0, 3);
    g.add(1, 4);
    g.add(3, 4);
    cout << g.is_connected();
    g.add(0, 2);
    cout << g.is_connected() << "\n";
}

void test_edges(graph & g) {
    for (auto & e : g.edges()) {
        int from, to, value;
        tie(from, to, value) = e;
        cout << from << " " << to << " " << value << "\n";
    }
}

int main() {
    graph g(5);
    g.add(0, 1);
    g.add(0, 3);
    g.add(1, 2);
    g.add(1, 4);
    g.add(2, 4);
    g.add(3, 4);
    cout << g;
    test_edges(g);
    test_connected();
    return 0;
}