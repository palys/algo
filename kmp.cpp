#include<string>
#include<iostream>
#include<vector>

int * pref(const std::string & s) {
    int * t = new int[s.length()];
    t[0] = 0;

    for (int i = 1; i < s.length(); ++i) {
        int w = t[i - 1];
        while(w > 0 && s[i] != s[w]) {
            w = t[w - 1];
        }
        if (s[i] == s[w]) {
            ++w;
        }
        t[i] = w;
    }

    return t;
}

std::vector<int> kmp(const std::string & text, const std::string & pattern) {
    int plen = pattern.length();
    int len = plen + text.length() + 1;
    int * t = pref(pattern + "#" + text);
    std::vector<int> result;

    for (int i = 0; i < len; ++i) {
        if (t[i] == plen) {
            result.push_back(i - 2 * plen);
        }
    }

    return result;
}

int main() {
    std::string text = "abcabcabcaxxxaxxxabcxxxxxxxxxxaababcabcc";
    std::string pattern = "abc";
    std::vector<int> f = kmp(text, pattern);
    for (auto & it : f) {
        std::cout << it << " ";
    }
    std::cout << "\n";

    pattern = "xx";
    f = kmp(text, pattern);
    for (auto & it : f) {
        std::cout << it << " ";
    }
    std::cout << "\n";

    pattern = "abca";
    f = kmp(text, pattern);
    for (auto & it : f) {
        std::cout << it << " ";
    }
    std::cout << "\n";

    return 0;
}