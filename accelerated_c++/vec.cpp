#include <iostream>
#include <chrono>
#include <memory>
#include <exception>

using namespace std;

template <class T> class Vec {
    public:
    typedef T* iter; 
    typedef const T* const_iter; 
    typedef T value_type;

    Vec();
    explicit Vec(size_t, const T& = T());
    template <class II> Vec(II, II);
    Vec(const Vec&);
    Vec& operator=(const Vec&);
    ~Vec();

    iter begin() {return start;}
    iter end() {return last_element;}
    const_iter begin() const  {return start;}
    const_iter end() const {return last_element;}
    size_t size(){return last_element - start;}
    size_t size() const {return last_element - start;}

    T& operator[](size_t i);
    void push_back(const T& t);
    iter erase(iter);
    //iter erase(iter, iter);
    void clear();
    
    private:
    iter start, last_element, last;
    allocator<T> alloc;

    void grow();
};

template <class T>
Vec<T>::Vec() {
    Vec(10);
}

template<class T>
Vec<T>::Vec(size_t sz, const T& t) {
    start = alloc.allocate(sz);
    last = start + sz;
    uninitialized_fill(start, start+sz, t);
    if (t != T())
        last_element = start + sz;
    else
        last_element = start;
}

template <class T>
template <class II>
Vec<T>::Vec(II b, II e) {
    cout << "got here";
    Vec();
    copy(b, e, back_inserter(start));
}
template <class T>
Vec<T>::Vec(const Vec& vec) {
    start = alloc.allocate(vec.size());
    last_element = last = start + vec.size(); 
    uninitialized_copy(vec.begin(), vec.end(), start);
}

template <class T>
Vec<T>& Vec<T>::operator=(const Vec& vec) {
    if (this != &vec) {
        clear();
        Vec(vec.size());
        for (auto trav = vec.begin(); trav != vec.end(); ++trav) {
            push_back(*trav);
        }
    }
    return *this;
}
template<class T>
T& Vec<T>::operator[](size_t index) {
    return start[index];
}

template<class T>
Vec<T>::~Vec() {
    if (start) {
        for (int i = 0; i < size(); i++) {
            alloc.destroy(start + i);
        }
        alloc.deallocate(start, size());
    }
    start = last_element = last = 0;
}

template<class T>
void Vec<T>::grow() {
//implement copy previous vec
    size_t sz = size();
    size_t new_sz = sz * 2;
    auto new_start = alloc.allocate(new_sz);
    if (start) {
        for (int i = 0; i != sz; i++) {
            alloc.construct(new_start+ i, *(start + i));
        }
    }
    start = new_start;
    last_element = start + sz; 
    last = start + new_sz; 
}
/*
template<class T, class II>
Vec<T>::Vec(II beg, II end) {

}*/

template<class T>
void Vec<T>::push_back(const T& t) {
    if (last_element == last) {
        grow();
    }
    alloc.construct(last_element, t);
    last_element++;
}

template<class T>
typename Vec<T>::iter Vec<T>::erase(Vec::iter it) {
    if (it >= start && it <= last) {
        auto trav = it;
        while (trav != last) {
            *trav = *++trav;
        }
        last_element--;
        return it;
    }
    else {
        throw invalid_argument("The iterator is invalid.");
    }
}

template<class T>
void Vec<T>::clear() {
    for (auto trav = start; trav != last_element; ++trav) {
        erase(trav);
    }
    alloc.deallocate(start, last-start);
    start = last_element = last = 0;
}
int main() {
    Vec<int> test(10);
    for (int i = 0; i < 10; i++) {
        test.push_back(i);
    }
    Vec<int> test2(test.begin(), test.end());
    return 0;

}