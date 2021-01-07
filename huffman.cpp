#include<string>
#include<map>
#include<algorithm>
#include<iostream>
#include<queue>
#include<vector>

typedef std::map<char, std::string> mcs;

class node {
    public:
        char c;
        int count;
        node * left;
        node * right;
        node(char c, int count): c(c), count(count), left(nullptr), right(nullptr) {};
        node(node * left, node * right): c('\0'), count(left -> count + right -> count), left(left), right(right) {};
};

class NodeComparator {
    public:
        bool operator()(const node * left, const node * right) {
            return left -> count > right -> count;
        }
};

template<typename K, typename V>
void print_map(std::map<K, V> m) {
    for (auto & p : m) {
        std::cout << p.first << " " << p.second << "\n";
    }
}

node * build_tree(std::map<char, int> & counts) {
    std::priority_queue<node *, std::vector<node *>, NodeComparator> queue;
    for (auto & p : counts) {
        node * n = new node(p.first, p.second);
        queue.push(n);
    }
    while (!queue.empty()) {
        node * first = queue.top();
        queue.pop();
        if (queue.empty()) {
            return first;
        }
        node * second = queue.top();
        queue.pop();

        node * join = new node(first, second);
        queue.push(join);
    }
    return nullptr;
}

mcs read_codes(node * tree) {
    mcs m;
    if (tree -> c != '\0') {
        m[tree -> c] = "";
    }
    if (tree -> left != nullptr) {
        for (auto & p : read_codes(tree -> left)) {
            m[p.first] = '0' + p.second;
        }
    }
    if (tree -> right != nullptr) {
        for (auto & p : read_codes(tree -> right)) {
            m[p.first] = '1' + p.second;
        }
    }
    return m;
}

std::map<char, int> count(std::string & s) {
    std::map<char, int> counts;
    for (auto & c : s) {
        counts[c]++;
    }
    return counts;
}

mcs generate_codes(std::string & s) {
    auto counts = count(s);
    auto tree = build_tree(counts);
    return read_codes(tree);
}

std::string transform(std::string & s, mcs & codes) {
   std::string result;
   for (auto & c : s) {
       result += codes[c];
   }
   return result;
}

std::string encode(std::string & s) {
    mcs codes = generate_codes(s);
    print_map(codes);
    return transform(s, codes);
}

int main() {
    std::string text = "natalian? tak!";
    std::cout << text << "\n" << encode(text) << "\n";
    return 0;
}
