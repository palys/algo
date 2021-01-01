#include <iostream>
#include <vector>
#include <string>

int main() {
    std::vector<std::string> msg {"Hello", "world"};

    for (auto& word : msg) {
        std::cout << word << " ";
    }

    std::cout << "\n";
    return 0;
}