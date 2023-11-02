#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

bool notspace(char c) {
    return !isspace(c);
}
bool is_space(char c) {
    return isspace(c);
}
vector<string> split(const string& str) {
    istringstream ssstr(str);
    vector<string> words;
    string word;
    while (getline(ssstr, word, ' ')) {
        words.push_back(word);
    }
    return words;
}
/*
Input:

<noun> cat
<noun> dog
<noun> table
<noun-phrase> <noun>
<noun-phrase> <adjective> <noun-phrase>
<adjective> large
<adjective> brown
<adjective> absurd
<verb> jumps
<verb> sits
<location> on the stairs
<location> under the sky
<location> wherever it wants
<sentence> the <noun-phrase> <verb> <location>

*/

typedef vector<string> rule;
typedef map<string, vector<rule>> grammar_table;

bool is_bracketed(const string& str) {
    if (str.size() > 2) {
        return str[0] == '<' && str[str.size() - 1] == '>';
    }
    return false;
}
grammar_table get_grammar(istream& in) {
    grammar_table table;
    string line;
    while (getline(in, line)) {
        vector<string> words = split(line);
        if (!line.empty())
            table[words[0]].push_back(vector<string>(words.begin() + 1, words.end()));
    }
    return table;
}

int get_random(int max) {
    return 0;
}

void gen_aux(const grammar_table& gt, const string& r, vector<string>& words) {
    if (!is_bracketed(r)) {
        words.push_back(r);
    }
    else {
        cout << r << endl;
        auto iter = gt.find(r);
        rule ru = iter->second[get_random(iter->second.size())];
        for (auto i = ru.begin(); i < ru.end(); i++) {
            gen_aux(gt, *i, words);
        }
    }
}

vector<string> gen_sentence(const grammar_table& gt) {
    vector<string> words;
    gen_aux(gt, "<sentence>", words);
    return words;
}

int main() {
    grammar_table table = get_grammar(cin);
    vector<string> sentence = gen_sentence(table);
    cout << sentence[0];
    if (sentence.size() > 1) {
        for (auto i = sentence.begin() + 1; i != sentence.end(); i++) {
            cout << " " + *i;
        }
    }
    cout << "." << endl;
}