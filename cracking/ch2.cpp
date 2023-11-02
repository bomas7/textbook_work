#include <iostream>
#include <string>
#include <unordered_set>

struct Node {
    int value;
    Node* next;
    Node(int n): value(n), next(nullptr) {}
    Node(int n, Node* ne): value(n), next(ne) {}
};

void print_node(Node* head) {
    auto trav = head;
    while (trav != nullptr) {
        std::cout << trav->value;
        if (trav->next != nullptr) std::cout << " -> ";
        trav = trav->next;
    }
    std::cout << std::endl;
}

Node* generate_node(int n) {
    Node* head = new Node(0);
    auto trav = head;
    for (int i = n; i > 0; --i) {
        Node* node = new Node(i);
        trav->next = node;
        trav = node;
    }
    return head;
}

Node* gen_node(int n) {
    std::string str = std::to_string(n);
    Node* head = new Node(0);
    auto trav = head;
    for (char i: str) {
        trav->next = new Node(i - '0'); 
        trav = trav->next;
    }
    return head->next;
}
//2.1
void make_unique(Node* head) {
    if (head == nullptr) return;
    std::unordered_set<int> vals{head->value};
    auto prev = head;
    auto trav = head->next;
    while (trav != nullptr) {
        if (vals.count(trav->value)) {
            prev->next = trav->next;
        }
        else {
            vals.insert(trav->value);
            prev = trav;
        }
        trav = trav->next;
    }
}

//2.2
int kth(Node* head, int k) {
    auto trav = head;
    auto run = head;
    for (int i = 0; i < k; ++i) {
        if (run == nullptr) return -1;
        run = run->next;
    }
    while (run != nullptr) {
        trav = trav->next;
        run = run->next;
    }
    return trav->value;
}

//2.3
void delete_mid_node(Node* node) {
    *node = *node->next;
}

//2.4
void stable_partition(Node* head, int val) {
    Node* a = nullptr;
    Node* b = nullptr;
    Node* atrav;
    Node* btrav;

    auto trav = head;
    while (trav != nullptr) {
        if (trav->value < val) {
            if (a) {
                atrav->next = trav;
                atrav = trav;
            }
            else {
                a = trav;
                atrav = a;
            }
        }
        else {
            if (b) {
                btrav->next = trav;
                btrav = trav;
            }
            else {
                b = trav;
                btrav = b;
            }
        }
        trav = trav->next;
    }
    if (a) {
        atrav->next = b;
        *head = *a;
    }
    else 
        *head = *b;
    if (b != nullptr)
    std::cout << b->value << std::endl;
    else
    std::cout << "nullptr" << std::endl;;
}

Node* unstable_partition(Node* head, int val) {
    Node* new_head = head;
    Node* tail = head;
    auto trav = head;
    while (trav != nullptr) {
        Node* temp = trav->next;
        if (trav->value < val) {
            trav->next = new_head;
            new_head = trav;
        }
        else {
            tail->next = trav;
            tail = trav;
            trav->next = nullptr;
        }
        trav = temp;
    }
    return new_head;
}

//2.5
Node* reverse_sum(Node* a, Node* b) {
    if (a == nullptr && b == nullptr) return nullptr;

    Node* sum = new Node(0);
    Node* trav = sum;
    int carry = 0;
    while (a != nullptr || b != nullptr) {
        int iter_a = 0; int iter_b = 0;
        if (a != nullptr) {
            iter_a = a->value;
            a = a->next;
        }
        if (b != nullptr) {
            iter_b = b->value;
            b = b->next;
        }
        int iter_sum = iter_a + iter_b + carry;
        int digit = iter_sum % 10;
        carry = iter_sum >= 10 ? 1: 0;

        Node* new_digit = new Node(digit);
        trav->next = new_digit;
        trav = trav->next;
    }
    return sum->next;
}

Node* reverse_list(Node* head) {
    if (head == nullptr) return nullptr;
    Node* new_head = head;
    Node* trav = head->next;
    new_head->next = nullptr;
    while (trav != nullptr) {
        auto temp = trav->next;
        trav->next = new_head;
        new_head = trav;
        trav = temp;
    }
    return new_head;
}
Node* normal_sum(Node* a, Node* b) {
    a = reverse_list(a);
    b = reverse_list(b);
    Node* c = reverse_sum(a, b);
    return reverse_list(c);
}

//2.6
bool is_palindrome(std::string str) {
    auto sz = str.size();
    for (int i = 0; i < sz / 2; ++i) {
        if (str[i] != str[sz-1-i])
            return false;
    }
    return true;
}

bool is_palindrome(Node* head) {
    std::string str = "";
    auto trav = head;
    while (trav != nullptr) {
        str.push_back(trav->value - '0');
        trav = trav->next;
    }
    return is_palindrome(str);
}

//no buffer
bool is_pali(Node* head) {
    //create a copy of a reverse list
    Node* copy_head = new Node(0);
    auto trav = head;
    auto copy_trav = copy_head;
    while (trav != nullptr) {
        copy_trav->next = new Node(trav->value);
        trav = trav->next;
        copy_trav = copy_trav->next;
    }
    copy_head = copy_head->next;
    copy_head = reverse_list(copy_head);
    
    //check if pali
    trav = head;
    copy_trav = copy_head;
    while (trav != nullptr) {
        if (trav->value != copy_trav->value) {
            return false;
        }
        trav = trav->next;
        copy_trav = copy_trav->next;
    }
    return true; 
}

//2.7
Node* intersecting(Node* a, Node* b) {
    std::unordered_set<Node*> ptrs;
    Node* trav = a;
    while (trav != nullptr) {
        ptrs.insert(trav);
        trav = trav->next;
    }
    trav = b;
    while (trav != nullptr) {
        if (ptrs.count(trav))
            return trav;
        else
            trav = trav->next;
    }
    return nullptr;
}

//2.8
Node* is_loop(Node* head) {
    std::unordered_set<Node*> ptrs;
    auto trav = head;
    while (trav != nullptr) {
        if (ptrs.count(trav))
            return trav;
        ptrs.insert(trav);
        trav = trav->next;
    }
    return nullptr;
}

int main() {
    auto a = gen_node(2);
    auto b = gen_node(617);
    a->next = a; 
    auto c = a;
    #ifdef TEST
    print_node(head);
    make_unique(head);
    print_node(head);
    print_node(head);
    head = unstable_partition(head, 2);
    print_node(head);
    #endif
    if (is_loop(a))
        std::cout << "TRUE";
    return 0;
}