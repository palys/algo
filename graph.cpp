#include<iostream>
#include<vector>
#include<utility>
#include<tuple>
#include<queue>
#include<algorithm>

using namespace std;

const int INF = 1 << 29;

class FindUnion {
    int n;
    int * t;
    int * size;
public:
    FindUnion(int n);
    ~FindUnion();
    int find(int x);
    void unite(int a, int b);
};

FindUnion::FindUnion(int n): n(n) {
    t = new int[n];
    size = new int[n];
    for (int i = 0; i < n; i++) {
        t[i] = i;
        size[i] = 1;
    }
}

FindUnion::~FindUnion() {
    delete[] t;
    delete[] size;
}

int FindUnion::find(int x) {
    if (t[x] != x) {
        t[x] = find(t[x]);
    }
    return t[x];
}

void FindUnion::unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (size[a] < size[b]) {
        swap(a, b);
    }
    size[a] += size[b];
    t[b] = a;
}

class graph {
    vector< pair<int, int> > * nodes;
    int n;
    bool * visited;
public:
    graph(int n);
    ~graph();
    int size() {
        return n;
    }
    void add(int from, int to, int value);
    void dfs(int start);
    void clear_visited();
    bool is_connected();
    vector<tuple<int, int, int> > edges();
    int * bellman_ford(int start);
    int * dijkstra(int start);
    int ** floyd_warshall();
    vector<pair<int, int> > kruskal();
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

int * graph::bellman_ford(int start) {
    int * t = new int[n];
    for (int i = 0; i < n; i++) {
        t[i] = INF;
    }
    t[start] = 0;

    auto ee = edges();
    for (int i = 0; i < n - 1; i++) {
        for (auto & e : ee) {
            int from, to, value;
            tie(from, to, value) = e;
            t[to] = min(t[to], t[from] + value);
        }
    }
    return t;
}

int * graph::dijkstra(int start) {
    int * t = new int[n];
    bool * processed = new bool[n];
    for (int i = 0; i < n; i++) {
        t[i] = INF;
        processed[i] = false;
    }
    t[start] = 0;

    priority_queue<pair<int, int> > q;
    q.push({0, start});
    while (!q.empty()) {
        int v = q.top().second;
        q.pop();
        if (processed[v]) {
            continue;
        }
        processed[v] = true;

        for (auto & e : nodes[v]) {
            int u = e.first;
            int value = e.second;

            if (t[v] + value < t[u]) {
                t[u] = t[v] + value;
                q.push({-t[u], u});
            }
        }
    }

    delete[] processed;
    return t;
}

int ** graph::floyd_warshall() {
    int ** t = new int * [n];
    for (int i = 0; i < n; i++) {
        t[i] = new int[n];
        for (int j = 0; j < n; j++) {
            t[i][j] = INF;
        }
        t[i][i] = 0;
        for (auto & e : nodes[i]) {
            t[i][e.first] = e.second;
        }
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                t[i][j] = min(t[i][j], t[i][k] + t[k][j]);
            }
        }
    }

    return t;
}

vector<pair<int, int> > graph::kruskal() {
    FindUnion fu(n);
    vector<tuple<int, int, int> > edges;
    for (int i = 0; i < n; i++) {
        for (auto & e : nodes[i]) {
            edges.push_back({e.second, i, e.first});
        }
    }
    sort(edges.begin(), edges.end());

    vector<pair<int, int> > result;
    for (auto & e : edges) {
        int value, u, v;
        tie(value, u, v) = e;
        if (fu.find(u) != fu.find(v)) {
            fu.unite(u, v);
            result.push_back({u, v});
        }
    }

    return result;
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

void print_edges(graph & g) {
    for (auto & e : g.edges()) {
        int from, to, value;
        tie(from, to, value) = e;
        cout << from << " " << to << " " << value << "\n";
    }
}

void test_bellman_ford() {
    graph g(5);
    g.add(0, 1, 5);
    g.add(0, 2, 3);
    g.add(0, 3, 7);
    g.add(1, 3, 3);
    g.add(1, 4, 2);
    g.add(2, 3, 1);
    g.add(3, 4, 2);

    int * dist = g.bellman_ford(0);
    cout << "Dist BF:\n";
    for (int i = 0; i < g.size(); i++) {
        cout << i << " " << dist[i] << "\n";
    }
    delete[] dist;
}

void test_dijkstra() {
    graph g(5);
    g.add(0, 1, 5);
    g.add(0, 2, 3);
    g.add(0, 3, 7);
    g.add(1, 3, 3);
    g.add(1, 4, 2);
    g.add(2, 3, 1);
    g.add(3, 4, 2);

    int * dist = g.dijkstra(0);
    cout << "Dist D:\n";
    for (int i = 0; i < g.size(); i++) {
        cout << i << " " << dist[i] << "\n";
    }
    delete[] dist;
}

void test_floyd_warshall() {
    graph g(5);
    g.add(0, 1, 5);
    g.add(0, 2, 3);
    g.add(0, 3, 7);
    g.add(1, 3, 3);
    g.add(1, 4, 2);
    g.add(2, 3, 1);
    g.add(3, 4, 2);

    int ** dist = g.floyd_warshall();
    cout << "Dist FW:\n";
    for (int i = 0; i < g.size(); i++) {
        for (int j = 0; j < g.size(); j++) {
            cout << dist[i][j] << " ";
        }
        cout << "\n";
        delete[] dist[i];
    }
    delete[] dist;
}

void test_floyd_warshall2() {
    graph g(5);
    g.add(0, 1, 5);
    g.add(0, 3, 9);
    g.add(0, 4, 1);
    g.add(1, 2, 2);
    g.add(2, 3, 7);
    g.add(3, 4, 2);

    int ** dist = g.floyd_warshall();
    cout << "Dist FW2:\n";
    for (int i = 0; i < g.size(); i++) {
        for (int j = 0; j < g.size(); j++) {
            cout << dist[i][j] << " ";
        }
        cout << "\n";
        delete[] dist[i];
    }
    delete[] dist;
}

void test_find_union() {
    FindUnion fu(10);
    fu.unite(1, 4);
    fu.unite(1, 7);

    fu.unite(6, 3);
    fu.unite(8, 2);
    fu.unite(3, 8);
    cout << "FindUnion:\n";
    for (int i = 0; i < 10; i++) {
        cout << fu.find(i) << " ";
    }
    cout << "\n";
}

void test_kruskal() {
    graph g(6);
    g.add(0, 1, 3);
    g.add(0, 4, 5);
    g.add(1, 2, 5);
    g.add(1, 4, 6);
    g.add(2, 3, 9);
    g.add(2, 5, 3);
    g.add(3, 5, 7);
    g.add(4, 5, 2);

    cout << "Kruskal:\n";
    for (auto & e : g.kruskal()) {
        cout << e.first << " " << e.second << "\n";
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
    print_edges(g);
    test_connected();
    test_bellman_ford();
    test_dijkstra();
    test_floyd_warshall();
    test_floyd_warshall2();
    test_find_union();
    test_kruskal();
    return 0;
}
