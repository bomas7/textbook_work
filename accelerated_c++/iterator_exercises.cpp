#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <utility>

using std::string, std::cout, std::vector;

template <class II>
bool equal(II begin1, II end1, II begin2) {
    for (; begin1 != end1;) {
        if (*begin1++ != *begin2++)
            return false;
    }
    return true;
}

template <class II, class T>
II find(II b, II e, T t) {
    for (; b != e; ++b) {
        if (*b == t)
            return b;
    }
    return e;
}

template <class II, class OI>
OI my_copy(II b1, II e1, OI b2) {
    while (b1 != e1) {
        *b2++ = *b1++;
    }
    return b2;
}

template <class II, class OI, class T>
OI remove_copy_if(II b, II e, OI d, bool (*p)(T)) {
    while (b != e) {
        if (!p(*b)) {
            *d++ = *b;
        }
        ++b;
    }
    return d;
}

bool isOdd(int x) {
    return x % 2 != 0;
}

template <class II, class OI, class P>
OI transform(II b, II e, OI d, P p) {
    while (b != e) {
        *d = p(*b);
        d++; b++;
    }
    return d;
}

int x(int n) {
    return n*5;
}

template <class II, class T>
T accumulate(II b, II e, T val) {
    while (b != e) {
        val += *b++;
    }
    return val;
}

template <class II>
bool search(II b1, II e1, II b2, II e2) {
    while (b1 != e1) {
        if (*b1 == *b2) {
            II b3 = b1, b4 = b2;
            while (b4 != e2) {
                if (b3 == e1)
                    break;
                if (*b3 == *b4) {
                    b3++; b4++;
                }
                else {
                    break;
                }
            }
            if (b4 == e2)
                return true;
        }
        b1++;
    }
    return false;
}

template <class II, class P>
II find_if(II b, II e, P p) {
    while (b != e) {
        if (p(*b)) {
            return b;
        }
        b++;
    }
    return e;
}

template <class II, class OI, class T>
OI remove_copy(II b, II e, OI d, T t) {
    while (b != e) {
        if (!(*b == t)) {
            *d++ = *b;
        }
        b++;
    }
    return d;
}

template <class FI, class T>
FI remove(FI beg, FI end, T t) {
    FI trav = beg;
    while (trav != end) {
        if (*trav == t) {
            *trav = T{};
        }
        else {
            *beg = *trav;
            beg++;
        }
        trav++;
    }
    return beg;
}

template <class FI, class P>
FI partition(FI beg, FI end, P p) {
    FI trav = beg;
    while (trav != end) {
        if (p(*trav)) {
            trav++;
            beg++;
        }
        else {
            while (trav != end && !p(*trav)) {
                trav++;
            }
            if (trav != end) {
                std::swap(*trav, *beg);
                beg++;
            }
        }
    }
    return beg;
}
int main() {
    string a = "tes3 test    ";
    string b = "test3";

    vector<int> c = {9, 1, 2, 3, 4 ,5, 6};
    vector<int> d(5);
    auto i = partition(c.begin(), c.end(), isOdd);
    cout << *i << std::endl;
    for (auto i: c) cout << i;
}
