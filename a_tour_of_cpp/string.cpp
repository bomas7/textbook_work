#include <string>
#include <iostream>
#include <vector>
import std;
using namespace std;
        
template <typename T>
concept Printable = requires(T t) {
        std::cout << t;
};

template<Printable T>
void print_T(T t) {
        std::cout << t;
}

struct Mytype{
        int x;
};
int main() {
        Mytype n;
        print_T(n);
        return 0;
}
