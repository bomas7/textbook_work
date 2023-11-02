#include <iostream>
#include <vector>
#include <string>

class Core {
public:
    Core(): midterm(0), final(0) {};
    Core(std::istream& is) {read(is);};
    virtual std::istream& read(std::istream&);
    virtual double grade() const;
protected:
    std::istream& read_general(std::istream&);
    std::vector<double> homework;
    double midterm, final;
    std::string name;
};

class Grad: public Core {
public:
    Grad(): thesis(0) {};
    Grad(std::istream& is) {read(is);};
    std::istream& read(std::istream&);
    double grade() const;
private:
    double thesis;
};

std::istream& Core::read(std::istream& is) {
    name = "Core";
    midterm = 20;
    final = 30;
    return is;
}

double Core::grade() const{
    return final + midterm;
}
double Grad::grade() const {
    return thesis;
}

std::istream& Grad::read(std::istream& is) {
    Core::read(is);
    name = "Grad";
    thesis = 40;
    return is;
}

bool compare(const Core& first, const Core& second) {
    return first.grade() < second.grade();
}
int main() {
    Core example1(std::cin);
    Grad example2(std::cin);
    std::cout << example1.grade() << example2.grade();
    return 0;
}