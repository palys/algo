#include<iostream>
#include<vector>
#include<utility>
#include<algorithm>

using namespace std;

class directed_graph {
    vector< pair<int, int> > * nodes;
    int n;
    bool topological_sort_dfs(int v, int * state, vector<int> & result);
public:
    directed_graph(int n);
    ~directed_graph();
    void add(int from, int to, int value);
    void add_two_way(int from, int to, int value);
    vector<int> topological_sort();
    vector<int> number_of_paths(int v);
    directed_graph reversed();
    friend ostream & operator<<(ostream & s, const directed_graph & g);
};

directed_graph::directed_graph(int n): n(n) {
    nodes = new vector< pair<int, int> >[n];
}

directed_graph::~directed_graph() {
    delete[] nodes;
}

ostream & operator<<(ostream & s, const directed_graph & g) {
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

bool directed_graph::topological_sort_dfs(int v, int * state, vector<int> & result) {
    if (state[v] == 0) {
        state[v] = 1;
        for (auto & e : nodes[v]) {
            if (!topological_sort_dfs(e.first, state, result)) {
                return false;
            }
        }
        state[v] = 2;
        result.push_back(v);
    } else if (state[v] == 1) {
        return false;
    }
    return true;
}

vector<int> directed_graph::topological_sort() {
    vector<int> result;
    int * state = new int[n];
    for (int i = 0; i < n; i++) {
        state[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        if (!topological_sort_dfs(i, state, result)) {
            delete[] state;
            return vector<int>();
        }
    }
    reverse(result.begin(), result.end());

    delete[] state;
    return result;
}

void test_topological_sort() {
    directed_graph g(6);
    g.add(0, 1);
    g.add(1, 2);
    g.add(2, 5);
    g.add(3, 0);
    g.add(3, 4);
    g.add(4, 1);
    g.add(4, 2);
    vector<int> sorted = g.topological_sort();
    cout << "Topological sort: \n";
    if (sorted.size() == 0) {
        cout << "Has a cycle\n";
    } else {
        for (auto & v : sorted) {
            cout << v << " ";
        }
        cout << "\n";
    }
}

vector<int> directed_graph::number_of_paths(int v) {
    vector<int> count(n, 0);
    count[v] = 1;
    
    for (int u : topological_sort()) {
        for (auto & e : nodes[u]) {
            count[e.first] += count[u];
        }
    }

    return count;
}

void test_number_of_paths() {
    directed_graph g(6);
    g.add(0, 1);
    g.add(1, 2);
    g.add(2, 5);
    g.add(3, 0);
    g.add(3, 4);
    g.add(4, 1);
    g.add(4, 2);
    vector<int> count = g.number_of_paths(3);
    cout << "Number of paths from 3\n";
    for (int i = 0; i < count.size(); i++) {
        cout << i << ": " << count[i] << "\n";
    }
}

directed_graph directed_graph::reversed() {
    directed_graph g(n);
    for (int u = 0; u < n; u++) {
        for (auto & e : nodes[u]) {
            g.add(e.first, u, e.second);
        }
    }
    return g;
}

void test_reversed() {
    directed_graph g(4);
    g.add(0, 1, 2);
    g.add(1, 2, 5);
    g.add(1, 3, 7);
    g.add(2, 3, 11);
    g.add(3, 2, 13);
    cout << g << g.reversed();
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
    test_topological_sort();
    test_number_of_paths();
    test_reversed();
    return 0;
}