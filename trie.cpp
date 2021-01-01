#include<iostream>
#include<string>

#include "trie.hpp"

trie::trie() {
    for (int i = 0; i < N; ++i) {
        this->root->children[i] = nullptr;
    }
}

void trie::add(std::string s) {
    node * r = this->root;
    for (auto & c : s) {
        int p = c - 'a';
        if (!r->children[p]) {
            r->children[p] = new node;
            for (int i = 0; i < N; ++i) {
                r->children[p]->children[i] = nullptr;
            }
        }
        r = r->children[p];
    }
    r->endOfWord = true;
}

bool trie::contains(std::string s) {
    node * r = this->root;
    for (auto & c : s) {
        int p = c - 'a';
        if (r->children[p]) {
            r = r->children[p];
        } else {
            return false;
        }
    }
    return r->endOfWord;
}

int main() {
    trie t;
    t.add("test");
    t.add("testabc");
    t.add("testabd");
    std::cout << t.contains("test") 
              << t.contains("testabc") 
              << t.contains("testab") 
              << t.contains("testabd")
              << t.contains("abc")
              << t.contains("testabcdeft")
              << t.contains("xxx");
    return 0;
}