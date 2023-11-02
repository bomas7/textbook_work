#include <iostream>
#include <vector>

struct Graph {
    std::vector<Node*> nodes;
};

struct Node {
    int value;
    std::vector<Node*> children;
};

int main() {
    return 0;
}