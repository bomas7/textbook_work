#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cctype>

using namespace std;
typedef string::const_iterator iter;

bool not_resource_char(char c) {
    if (isalnum(c) || c == '/')
        return false;
    return true;
}

iter find_url(iter& i, iter j, const string& str) {
    static const string delim = "://";
    while (i != j) {
        i = search(i, j, delim.begin(), delim.end());
        if (i != j && i != str.begin()) {
            if (isalpha(i[-1]) && i+2 != j && isalnum(i[3])) {
                iter end = i+3;
                while (i != str.begin()) {
                    if (isalpha(i[-1]))
                        i--;
                    else
                        break;
                }
                j = i;
                i = end;
                return j;
            }
        }
    }
    i = str.end();
    return j;

}

iter find_url_end(iter i, iter j, const string& str) {
    return find_if(i, j, not_resource_char);
}

vector<string> url_split(const string& str) {
    vector<string> urls;
    iter i = str.begin(), e = str.end();
    while (i != e) {
        cout << *i << endl;
        iter url_begin = find_url(i, e, str);
        if (url_begin != e) {
            iter url_end = find_url_end(i, e, str);
            i = url_end;
            cout << *url_begin << *url_end << endl;
            urls.push_back(string(url_begin, url_end));
        }
    }
    return urls;
}
int main() {
    string test = "://abcd://efgh asdf ijkl://mnop ";
    vector<string> urls = url_split(test);
}