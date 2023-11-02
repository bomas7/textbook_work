#include <iostream>
#include <variant>
#include <string>
#include <vector>
#include <algorithm>

enum class Marble {white, blue, green, red};
//using MyType = std::variant<char, bool, int, double, std::string>;

std::ostream& operator<<(std::ostream& out, const Marble m) {
        switch(m) {
                case (Marble::red):
                        out << "red";
                        break;
                case (Marble::blue):
                        out << "blue";
                        break;
                case (Marble::green):
                        out << "green";
                        break;
                default:
                        out << "white";
        }
        return out;
}

std::istream& operator>>(std::istream& in, Marble& m) {
        int i = -1;
        in >> i;
        if (i >= 1 && i <= 3) {
                m = static_cast<Marble>(i);
        }
        else {
                m = Marble::white;
        }
        return in;
}

struct MarbleVector {
        Marble* elements;
        int size;

        MarbleVector(int sz) {
                elements = new Marble[sz];
                size = sz;
        }

        Marble& operator[](const int i) {
                return elements[i];
        }

        void read_values() {
                Marble input;
                for (int i = 0; i < size; ++i) {
                        std::cin >> input;
                        elements[i] = input;
                }
        }

        void print_values() {
                for (int i = 0; i < size; ++i) {
                        std::cout << elements[i] << " ";
                }
                std::cout << "\n";
        }
        
        ~MarbleVector() {
                delete[] elements;
        }
};

//virtual class with pure virtual functions
class Container {
public:
        virtual double& operator[](int) = 0;
        virtual int size() = 0;
        virtual ~Container() {};
};


class Vector5: public Container {
public:
        Vector5() {};
        Vector5(std::initializer_list<double>);
        void push_back(double);
        int size();
        double& operator[](int);
        ~Vector5() {
                std::cout << "destructor was called" << "\n"; 
        };
private:
        std::vector<double> vec;
};

Vector5::Vector5(std::initializer_list<double> lst) {
        std::copy(lst.begin(), lst.end(), back_inserter(vec));
}

void Vector5::push_back(double d) {
        vec.push_back(d);
}

int Vector5::size() {
        return vec.size();
}

double& Vector5::operator[](int i) {
        return vec[i];
}

std::ostream& print_container(std::ostream& out, Container& c) {
        out << "{";
        for (int i = 0; i < c.size(); ++i) {
                out << c[i];
                if (i != c.size()-1)
                        out << ", ";
        }
        out << "}";
        out << std::endl;
        return out;
}

class List: public Container {

};

int main() {
        Container* c = new Vector5{1, 2, 3};
        if (dynamic_cast<List*>(c))
                std::cout << "true";
        else {
                std::cout << "false";
        }
        print_container(std::cout, *c);
        delete c;

        return 0;
}

/*
MarbleVector vec(5);
vec.print_values();
vec.read_values();
vec[2] = Marble::blue;
vec.print_values();
std::cout << vec[2];
*/
