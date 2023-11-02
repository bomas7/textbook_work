#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cctype>

using namespace std;

bool space(char c) {
    return isspace(c);
}
bool not_space(char c) {
    return !isspace(c);
}

//iterator implementation
vector<string> split(const string& str) {
    vector<string> words;
    string::const_iterator i = str.begin(), j;
    while (i != str.end()) {
        i = find_if(i, str.end(), not_space);
        j = find_if(i, str.end(), space);
        if (i != str.end()) {
            words.push_back(string(i, j));
        } 
        i = j;
    }
    return words;
}
int main() {
    string test = "test://link.com asdf test2://link2.com ://";
    return 0;
}