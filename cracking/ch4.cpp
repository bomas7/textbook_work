#include <iostream>
#include <vector>
#include <cmath>
#include <stack>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <list>

struct Node {
    int value;
    Node* left;
    Node* right;
    Node(int val): value(val), left(nullptr), right(nullptr) {};
    Node(const Node& other): value(other.value), left(nullptr), right(nullptr) {};
};

void insert_bst(Node*& head, int val) {
    if (head == nullptr) head = new Node(val);
    if (val < head->value) insert_bst(head->left, val);
    else if (val > head->value) insert_bst(head->right, val);
}

Node* generate_bst(std::vector<int> vec) {
    if (vec.empty()) return nullptr;
    Node* head = nullptr;
    for (auto i = vec.begin(); i != vec.end(); ++i) {
        insert_bst(head, *i);
    }
    return head;
}

bool find_bst(Node* head, int val) {
    if (head == nullptr) return false;
    if (val < head->value) return find_bst(head->left, val);
    if (val > head->value) return find_bst(head->right, val);
    else return true;
}

void in_order(Node* head) {
    if (head == nullptr) return;
    in_order(head->left);
    std::cout << head->value;
    in_order(head->right);
}

Node* copy_tree(Node* head) {
    if (head == nullptr) return nullptr;

    Node* new_tree = new Node(*head);
    std::stack<Node*> nodes;
    std::stack<Node*> new_nodes;
    nodes.push(head);
    new_nodes.push(new_tree);
    while (!nodes.empty()) {
        Node* node = nodes.top();
        nodes.pop();
        Node* new_node = new_nodes.top();
        new_nodes.pop();

        if (node->left) {
            nodes.push(node->left);
            new_node->left = new Node(*node->left);
            new_nodes.push(new_node->left);
        }
        if (node->right) {
            nodes.push(node->right);
            new_node->right = new Node(*node->right);
            new_nodes.push(new_node->right);
        }
    }
    return new_tree;
}

Node* copy_tree2(Node* head) {
    if (head == nullptr) return nullptr;
    Node* new_tree = new Node(*head);
    new_tree->left = copy_tree2(head->left);
    new_tree->right = copy_tree2(head->right);
    return new_tree;
}

void delete_tree(Node*& head) {
    if (head == nullptr) return;
    delete_tree(head->left);
    delete_tree(head->right);
    delete head;
    head = nullptr;
}

void delete_tree2(Node*& head) {
    if (head == nullptr) return;

    std::stack<Node*> nodes;
    nodes.push(head);

    while (!nodes.empty()) {
        Node* node = nodes.top();
        nodes.pop();
        if (node->left != nullptr) {
            nodes.push(node->left);
        }
        if (node->right != nullptr) {
            nodes.push(node->right);
        }
        std::cout << "DELETING NODE: " <<  node->value << std::endl;
        delete node;
    }
    head = nullptr;
}

int length_bst(Node* head) {
    if (head == nullptr) return 0;
    int left = length_bst(head->left);
    int right = length_bst(head->right);
    return 1 + left + right;
}

void iter_preorder(Node* head) {
    if (head == nullptr) return;
    std::stack<Node*> nodes;
    nodes.push(head);
    while (!nodes.empty()) {
        auto node = nodes.top();
        nodes.pop();
        std::cout << node->value;
        if (node->right) nodes.push(node->right);
        if (node->left) nodes.push(node->left);
    }
}

bool contains_path(Node* start, Node* destination) {
    std::queue<Node*> nodes;
    std::unordered_set<Node*> visited;
    nodes.push(start); 
    while (!nodes.empty()) {
        Node* node = nodes.front();

        if (node == destination) return true;
        if (visited.count(node) == 1) break;
        
        nodes.pop();
        visited.emplace(node);

        if (node->left) nodes.push(node->left);
        if (node->right) nodes.push(node->right);
    }
    return false;
}

bool contains_route(Node* a, Node* b) {
    if (contains_path(a, b)) return true;
    return contains_path(b, a);
}

Node* generate_helper(const std::vector<int>& vec, Node*& head, 
                        ssize_t start, ssize_t end) {
    if (start > end) return nullptr;
    ssize_t middle = (start + end) / 2;
    head = new Node(vec[middle]);
    generate_helper(vec, head->left, start, middle-1);
    generate_helper(vec, head->right, middle+1, end);
    return head;
}
Node* generate_balanced(const std::vector<int>& vec) {
    if (vec.empty()) return nullptr;
    Node* head = nullptr;
    return generate_helper(vec, head, 0, vec.size()-1);
}

int check_depth(Node* head) {
    if (head == nullptr) return 0;
    std::stack<Node*> nodes;
    nodes.push(head);
    std::unordered_map<Node*, int> depths;
    depths[head] = 1;
    int max = 0;
    while (!nodes.empty()) {
        Node* node = nodes.top();
        nodes.pop();
        if (depths[node] > max) {
            max = depths[node];
        }
        if (node->left) {
            depths[node->left] = depths[node] + 1;
            nodes.push(node->left);
        }
        if (node->right) {
            depths[node->right] = depths[node] + 1;
            nodes.push(node->right);
        }
    }

    return max;
}

std::vector<std::list<Node*>> list_depths(Node* head) {
    std::vector<std::list<Node*>> vec;
    if (head == nullptr) return vec;

    std::queue<Node*> q;
    q.push(head);    
    int depth = 0;
    while (!q.empty()) {
        vec.push_back(std::list<Node*>{});
        size_t sz = q.size();
        for (int i = 0; i < sz; ++i) {
            Node* node = q.front();
            vec[depth].push_back(node);
            if (node->left)
                q.push(node->left);
            if (node->right)
                q.push(node->right);
            q.pop();
        }
        ++depth;
    }
    return vec;
}


void print_list_depths(std::vector<std::list<Node*>> vec) {
    for (int i = 0; i < vec.size(); ++i) {
        std::cout << "DEPTH " << i << ": ";
        auto j = vec[i];
        for (auto k = j.begin(); k != j.end(); ++k) {
            std::cout << (*k)->value << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    std::vector<int> x = {5, 4, 3, 2, 1};
    Node* t = generate_bst(x);
    auto ldepth = list_depths(t);
    print_list_depths(ldepth);
    std::cout << is_bal(t);
    return 0;
}