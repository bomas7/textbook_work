#include <iostream>
#include <cstring>

class Str{
    public:
    Str();
    Str(const char*);
    Str(const Str&);
    ~Str();

    Str& operator=(const Str&);
    Str& operator+=(const Str&);
    bool operator==(const Str&);
    bool operator!=(const Str&);
    friend std::istream& operator>>(std::istream&, Str);
    friend std::ostream& operator<<(std::ostream&, Str);
    operator bool() {
        return size() != 0;
    }

    void print();
    void append(char);
    size_t size() const {
        return str_end - start;
    }

    char* begin() {return start;}
    char* end() {return str_end;}
    private:
    static const size_t DEFAULT_SIZE = 10; 
    char* start;
    char* str_end;
    char* cap_end;

    void grow();
};

Str::Str() {
    start = new char[DEFAULT_SIZE];
    str_end = start;
    cap_end = start + DEFAULT_SIZE;
}

Str::Str(const char* chars): Str() {
    for (int i = 0; i < std::strlen(chars); ++i) {
        append(chars[i]);
    }
}

Str::Str(const Str& str): Str() {
    for (auto trav = str.start; trav != str.str_end; ++trav) {
        append(*trav);
    }
}

Str& Str::operator=(const Str& str) {
    delete[] start;
    start = new char[DEFAULT_SIZE];
    str_end = start;
    cap_end = start + DEFAULT_SIZE;
    for (auto trav = str.start; trav != str.str_end; ++trav) {
        append(*trav);
    }
    return *this;
}

Str& Str::operator+=(const Str& str) {
    for (auto trav = str.start; trav != str.str_end; ++trav) {
        append(*trav);
    }
    return *this;
}

bool Str::operator==(const Str& str) {
    if (size() != str.size())
        return false;
    for (int i = 0; i < size(); ++i) {
        if (str.start[i] != start[i]) return false;
    }
    return true;
}

bool Str::operator!=(const Str& str) {
    return !operator==(str);
}
void Str::append(char c) {
    if (str_end == cap_end) {
        grow();
    }
    *str_end = c;
    str_end++;
}

void Str::grow() {
    size_t cur_sz = size();
    size_t new_sz = cur_sz * 2;
    char* new_start = new char[new_sz];
    for (int i = 0; i < cur_sz; ++i) {
        new_start[i] = start[i];
    }
    delete[] start;
    start = new_start;
    str_end = start + cur_sz;
    cap_end = start + new_sz;
}

void Str::print() {
    for (auto i: *this) {
        std::cout << i;
    }
    std::cout << std::endl;
}

Str::~Str() {
    delete[] start;
}

std::ostream& operator << (std::ostream& out, Str str) {
    for (auto i: str) {
        out << i;
    }
    return out;
}
int main() {
    Str my_str("this is a test");
    std::cout << my_str << std::endl;
    my_str.print();
    return 0;
}