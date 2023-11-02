#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Node{
    string value;
    Node* next;
    Node* prev;

    Node() {
        value = string{};
        next = nullptr;
        prev = nullptr;
    }
    Node(string val, Node* n, Node* p) {
        value = val;
        next = n;
        prev = p;
    }
};

class String_list {
    public:
    Node head;
    String_list(int n) {
        head = Node("0", nullptr, nullptr);
        Node* trav = &head;
        for (int i = 1; i < n; i++) {
            Node* nnode = new Node(to_string(i), nullptr, trav);
            trav->next = nnode;
            trav = nnode;
        }
    }
    void print_list() {
        SLIterator iter(*this);
        while (iter.value != string{}) {
            cout << iter.next()->value;
        }
    }
};

class SLIterator {
    Node* trav;
    public:
    string value;
    SLIterator(String_list sl) {
        trav = &sl.head; 
        value = trav->value;
    }
    Node* next() {
        if (trav->next == nullptr)
            return nullptr;
        trav = trav->next;
        value = trav->value;
        return trav;
    }
    
};
int main() {
    String_list sl(5);
    sl.print_list();
}