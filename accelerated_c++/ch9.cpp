#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <exception>

using std::cout, std::vector, std::string, std::endl;

class Student_info {
    string name;
    vector<double> homework;
    double midterm, final;

    public:
    Student_info(): midterm(0), final(0) {}
    Student_info(std::istream&);
    void get_homework();
    double calculate_homework();
    bool isfail();
};

Student_info::Student_info(std::istream& in) {
    in >> name >> midterm >> final;
}

void Student_info::get_homework() {
    homework = {50, 40, 90, 70, 71, 80};
}

double Student_info::calculate_homework() {
    try {
    if (homework.empty())
        throw std::domain_error("No homework grades.");
    }
    catch(std::domain_error&) {
        get_homework(); 
    }
    std::sort(homework.begin(), homework.end());
    vector<double>::size_type sz = homework.size();
    if (sz % 2 == 0)
        return (homework[sz/2] + homework[sz/2-1]) / 2;
    return homework[sz/2];
}

bool Student_info::isfail() {
    return (midterm + final) / 2 > 60;
}

int main() {
    int test[] = {1, 2, 3};
    const char ars[] = "this is a test";
    for (auto i: ars) cout << i;
}