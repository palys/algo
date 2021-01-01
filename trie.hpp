#include<string>

const int N = 'z' - 'a' + 1;

class node {
    public:
        node * children[N];
        bool endOfWord = false;
};

class trie {
    node * root = new node;

    public:
        trie();
        void add(std::string s);
        bool contains(std::string s);
};
