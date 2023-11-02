#include <iostream>
#include <vector>
#include <string>
#include <list>

//3.1
/*
Split the array into three sections with each section denoted by a pointer to the beginning of the section.
Use section of array to implement individual stack.
If borrowing is allowed (e.g capacity != array_size / 3) then, shift pointers and copy values in available space.
*/

//3.2 + 3.3
template <class T>
class Stack {
    public:
    Stack(): head(nullptr), sz(0) {};
    T pop();
    void push(T item);
    T peek();
    bool empty() {return head == nullptr;}
    T minimum();
    void print();
    size_t size() {return sz;}
    ~Stack() {
        if (empty()) return;
        auto trav = head;
        while (trav != nullptr) {
            auto temp = trav->next;
            delete trav;
            trav = temp;
        }
    }
    private:
    struct Node {
        T value;
        Node* next;
        Node(T n): value(n), next(nullptr) {}
        Node(T n, Node* ne): value(n), next(ne) {}
    };
    Node* head;
    T min;
    size_t sz;
};

template <class T>
T Stack<T>::pop() {
    if (!empty()) {
        T val = head->value;
        auto temp = head;
        head = head->next;
        delete temp;
        --sz;
        return val;
    }
    return 0;
}

template <class T>
void Stack<T>::push(T item) {
    ++sz;
    if (!empty()) {
        Node* node = new Node(item, head);
        head = node;
        if (item < min) min = item;
    }
    else {
        head = new Node(item);
        min = item;
    }

}

template <class T>
T Stack<T>::peek() {
    if (!empty()) {
        return head->value;
    }
    return nullptr;
}

template <class T>
void Stack<T>::print() {
    auto trav = head;
    while (trav != nullptr) {
        std::cout << trav->value << " ";
        trav = trav->next;
    }
    std::cout << std::endl;
}

template <class T>
T Stack<T>::minimum() {
    return min;
}

template <class T>
class SetOfStacks {
    public:
    SetOfStacks(): capacity(5) {};
    SetOfStacks(int n): capacity(n) {};
    bool is_empty() {return stacks.size() == 0;}

    void push(T item);
    T pop();
    T popAt(int index);

    void print() {
        for (auto stack: stacks) {
            stack->print();
        }
    }
    private:
    int capacity;
    std::vector<Stack<T>*> stacks;
};

template <class T>
void SetOfStacks<T>::push(T item) {
    if (is_empty()) {
        auto stack = new Stack<T>;
        stack->push(item);
        stacks.push_back(stack);
    }
    else {
        //check if any current stacks have capacity
        for (auto& stack: stacks) {
            if (stack->size() < capacity) {
                stack->push(item);
                return;
            }
        }
        //if all stacks are at capacity
        stacks.push_back(new Stack<T>);
        stacks[stacks.size()-1]->push(item);
    }
}

template <class T>
T SetOfStacks<T>::pop() {
    return popAt(stacks.size()-1);
}

template <class T>
T SetOfStacks<T>::popAt(int index) {
    if (stacks.size() == 0) return 0;
    if (index > 0 && index <= stacks.size()-1) {
        if (stacks[index]->size() == 1) {
            T val = stacks[index]->pop();
            stacks.erase(stacks.begin() + index); 
            return val;
        }
        return stacks[index]->pop();
    }
    else {
        std::cout << "out of index" << std::endl;
        return 0;
    }
}

class AnimalShelter {
    public:
    std::string pop_any();
    std::string popDog();
    std::string popCat();
    void push(std::string);
    std::string top();
    private:
    std::string pop_animal(std::string);
    std::list<std::string> animals;
};

std::string AnimalShelter::pop_any() {
    if (!animals.empty()) {
        std::string str = animals.front();
        animals.pop_front();
        return str;
    }
    return std::string{};
}

std::string AnimalShelter::pop_animal(std::string animal) {
    for (auto i = animals.begin(); i != animals.end(); ++i) {
        if (i->find(animal) != std::string::npos) {
            std::string str = *i;
            animals.erase(i);
            return str; 
        }
    }
    return std::string{};
}

std::string AnimalShelter::popDog() {
    return pop_animal("dog");
}

std::string AnimalShelter::popCat() {
    return pop_animal("cat");
}

void AnimalShelter::push(std::string animal) {
    animals.push_back(animal);
}

std::string AnimalShelter::top() {
    if (!animals.empty())
        return animals.front();
    return std::string{};
}

int main() {
    AnimalShelter animals;
    for (int i = 0; i < 5; ++i) {
        animals.push("dog"+std::to_string(i));
    }
    for (int i = 0; i < 5; ++i) {
        animals.push("cat"+std::to_string(i));
    }
    std::cout << animals.popCat();
    std::cout << animals.popDog();
    std::cout << animals.pop_any();
}