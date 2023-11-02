#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <list>

using namespace std;

vector<string> split(const string& str, char delimiter) {
    istringstream ssstr(str);
    vector<string> lines;
    string line;
    while (getline(ssstr, line, delimiter)) {
        lines.push_back(line);
    }
    return lines;
}

vector<string> generate_index(vector<string> line, int index) {
    string first="", second="";
    for (int i = 0; i < line.size(); i++) {
        if (i >= index) {
            if (second.size() != 0) second += " ";
            second += line[i];
        }
        else {
            if (first.size() != 0) first += " ";
            first += line[i];
        }
    }
    vector<string> vec{first, second};
    return vec;
}

//need to add functionality for case sensitivity
bool compare_index(vector<string> a, vector<string> b) {
    return a[1] < b[1];
}

void permuted_index(const string& str) {
    vector<string> lines = split(str, '\n');
   vector<vector<string>> indexes;
    for (string line: lines) {
        vector<string> words = split(line, ' ');
        for (int i = 0; i < words.size(); i++) {
            vector<string> index = generate_index(words, i);
            indexes.push_back(index);
        }
    }
    sort(indexes.begin(), indexes.end(), compare_index);
    for (auto index: indexes) {
        string first = index[0];
        string second = index[1];
        int size = first.size() + second.size();
        cout << right << setw(size) << index[0] << "\t" << setw(size) << left << second << endl;
    }
}

bool isPalindrome(string s) {
    int i = 0;
    int j = s.size()-1;
    while (i < s.size() / 2) {
        cout << s[i] << ":" << s[j] << endl;
        if (isspace(s[i])) {
            i++;
        }
        else if (isspace(s[j])) {
            j--;
        }
        else if (s[i] != s[j]) {
            return false;
        }
        else {
            i++;
            j--;
        }
    }
    return true;
}

int main() {
    string test = "the fox";
    return 0;
}