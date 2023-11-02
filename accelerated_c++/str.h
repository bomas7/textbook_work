#ifndef STR_H
#define STR_H
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

    void print();
    void append(char);
    size_t size() {
        return str_end - start;
    }

    private:
    static const size_t DEFAULT_SIZE = 10; 
    char* start;
    char* str_end;
    char* end;

    void grow();
};
#endif