#include <iostream>
#include <cmath>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <vector>
#include <algorithm>

//1.1
bool is_unique(const char str[]) {
    std::unordered_map<char, int> values;
    auto i = str;
    while (*i != '\0') {
        if (values.find(*i) == values.end())
            values[*i] == 1;
        else {
            return false;
        }
        ++i;
    }
    return true;
}

bool is_unique(std::string str) {
    std::unordered_map<char, int> chars;
    for (char c: str) {
        if (chars.find(c) == chars.end()) {
            chars[c] = 1;
        }
        else {
            return false;
        }
    }
    return true;
}

template <class T>
bool is_unique(T arr[], size_t size) {
    std::unordered_map<T, int> vals;
    for (int i = 0; i < size; ++i) {
        auto val = arr[i];
        if (vals.find(val) == vals.end()) {
            vals[val] = 1;
        }
        else {
            return false;
        }
    }
    return true;
}

//if no additional data structures, sort, and then check if next is equal to previous O(n log n)
template <class T>
bool in_unique(std::vector<T> vec) {
    if (!vec.empty()) {
        std::sort(vec.begin(), vec.end());
        for (auto i = vec.begin() + 1; i != vec.end(); ++i) {
            if (*i == *(i-1))
                return false;
        }
    }
    return true; 
}

//1.2
bool check_permutation(std::string str1, std::string str2) {
    if (str1.size() != str2.size()) return false;
    std::unordered_map<char, int> chars;
    for (auto& i: str1) {
        ++chars[i];
    }
    for (auto& i: str2) {
        if (chars.find(i) == chars.end() || chars.find(i) == 0)
            return false;
        --chars[i];
    }
    return true;
}

//1.3
std::string URLify(std::string str) {
    std::string URL;
    for (auto& i: str) {
        if (i == ' ') URL += "%20";
        else URL += i;
    }
        return URL;
}

//in-place on char array
int find(char arr[], int index) {
    while (index >= 0) {
        if (arr[index] == ' ') return index;
        --index;
    }
    return -1;
}
char* URL_inplace(char arr[], int n) {
    int spaces = 2 * std::count(arr, arr+n, ' ');
    --n;
    while (spaces != 0) {
        if (arr[n] == ' ') {
            spaces -= 2;
            int start = n + spaces;
            arr[start] = '%';
            arr[start+1] = '2';
            arr[start+2] = '0';
        }
        else {
            arr[n+spaces] = arr[n];
        }
        --n;
    } 
    return arr;
}

//1.4
//map implementation
bool map_palindrome(std::string a, std::string b) {
    if (a.empty() || b.empty()) return true;
    std::map<char, int> chars;
    std::map<char, int> chars2;
    for (auto i: a) {
        if (std::isalnum(i)) 
            ++chars[i];
    }
    for (auto i: b) {
        if (std::isalnum(i))
            ++chars2[i];
    }
    return chars == chars2;
}

//hash table
bool is_palindrome(const std::string& a, const std::string& b) {
    std::unordered_map<char, int> chars;
    for (auto i: a) {
        if (isalnum(i)) ++chars[i];
    }
    for (auto i: b) {
        if (isalnum(i)) {
            if (!chars.count(i)) return false;
            else --chars[i];
        }
    }
    for (auto i: chars) {
        if (i.second != 0) return false;
    }
    return true;
}

//1.5
bool one_away(std::string a, std::string b) {
    int size_diff = std::abs((int) (a.size() - b.size()));
    if (size_diff > 1) return false;
    if (a.empty() || b.empty()) return true;
    if (b.size() > a.size()) std::swap(a, b);
    auto i = a.begin();
    auto j = b.begin();
    int edits = 0;
    while (i != a.end()) {
        if (*i != *j) {
            if (edits == 1) return false;
            edits++;
        }
        else 
            ++j;
        ++i;
    }
    return true; 
}

//pass by reference
bool clean_one(const std::string& a, const std::string& b) {
    int sz_diff = a.size() - b.size();
    if (std::abs(sz_diff) > 1) return false;
    if (a.empty() || b.empty()) return true;

    auto i = a.begin();
    auto j = b.begin();
    auto end = a.end();
    if (a.size() < b.size()) {
        std::swap(i, j);
        end = b.end(); 
    }

    int edits = 0;
    while (i != end) {
        if (*i != *j) {
            if (edits) return false;
            ++edits;            
        } 
        else 
            ++j;
        ++i;
    }
    return true;
}

//1.6
std::string string_compression(const std::string& str) {
    std::string compressed_str;
    if (str.empty() || str.size() == 1) return str;
    char current = str[0];
    int count = 1;
    for (int i = 1; i != str.length(); ++i) {
        if (str[i] != current) {
            compressed_str.push_back(current);
            compressed_str += std::to_string(count);
            current = str[i];
            count = 1;
        }
        else
            ++count;
    }
    compressed_str.push_back(current);
    compressed_str += std::to_string(count);
    return str.size() < compressed_str.size() ? str: compressed_str;
}

//1.7
using std::vector;

template <class T>
void print2(vector<vector<T>> vec) {
    for (auto row: vec) {
        for (auto c: row) {
            std::cout << c << " ";
        }
        std::cout << std::endl;
    }
}

template <class T>
vector<vector<T>> rotate_matrix(const vector<vector<T>>& matrix) {
    if (matrix.empty()) return matrix;
    vector<vector<T>> rmatrix;
    auto n = matrix.size();
    rmatrix.reserve(n);
    for (int i = 0; i < n; ++i) {
        vector<T> row;
        row.reserve(i);
        for (int j = 0; j < n; ++j) {
            row.push_back(matrix[n-1-j][i]);
        }
        rmatrix.push_back(row);
    }
    return rmatrix;
}

//in place rotation NOT COMPLETED
void ip_matrix(vector<vector<int>>& vec) {
    auto n = vec.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int x = n - 1 - j;
            if (x < i)
                std::swap(vec[i][x], vec[i][j]);
            else 
                std::swap(vec[x][i], vec[i][j]);
        }
    }
}

//1.8
void zero_matrix(vector<vector<int>>& vec) {
    std::unordered_set<int> rows;
    std::unordered_set<int> cols;
    if (vec.empty()) return;
    for (int i = 0; i < vec.size(); ++i) {
        for (int j = 0; j < vec[0].size(); ++j) {
            if (vec[i][j] == 0) {
                rows.insert(i);
                cols.insert(j);
            }
        }
    }
    for (auto i: rows) {
        for (int j = 0; j < vec[0].size(); ++j) {
            vec[i][j] = 0;
        }
    } 
    for (auto i: cols) {
        for (int j = 0; j < vec.size(); ++j) {
            vec[j][i] = 0;
        }
    }
}

//1.9
bool isRotation(std::string str, std::string str2) {
    auto x = str + str;
    return (x.find(str2) != std::string::npos);
}
int main() {
    #ifdef test
    vector<vector<int>> vec = {
        {1, 2, 3, 9},
        {5, 6, 0, 8},
        {9, 0, 11, 12},
        {13, 14, 15, 16}
    };
    zero_matrix(vec);
    print2(vec); 
    #endif
    std::cout << isRotation("waterbottle", "erbottlewae");
    return 0;
}