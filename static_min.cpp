#include<iostream>
#include<vector>
using namespace std;

class static_min {
    int n;
    vector<vector<int> > tables;

    public:
        static_min(vector<int> t);
        int min(int from, int to);
        void print();
};

static_min::static_min(vector<int> t): n(t.size()) {
    tables.push_back(vector<int>(t));
    int len = 2;
    int i = 1;
    while(len <= n) {
        tables.push_back(vector<int>());

        for (int j = 0; j <= n - len; j++) {
            tables[i].push_back(std::min(tables[i - 1][j], tables[i - 1][j + (len >> 1)]));
        }

        len <<= 1;
        i++;
    }
}

int static_min::min(int from, int to) {
    int i = 0;
    int len = to - from + 1;
    while ((2 << i) <= len) {
        ++i;
    }
    return std::min(tables[i][from], tables[i][to - (1 << i) + 1]);
}

void static_min::print() {
    int len = 1;
    int i = 0;
    while (len <= n) {
        for (int j = 0; j < tables[i].size(); j++) {
            cout << "min[" << j << ", " << j + len - 1 << "] = " << tables[i][j] << "\n";
        }
        len <<= 1;
        ++i;
    }
}

int main() {
    static_min m({1,2,3,4,8,7,6,5});
    m.print();
    cout << m.min(0, 0) << "\n"
         << m.min(0, 3) << "\n"
         << m.min(2, 6) << "\n"
         << m.min(3, 4) << "\n"
         << m.min(0, 7) << "\n"
         << m.min(6, 7) << "\n"
         << m.min(5, 7) << "\n";
    return 0;
}