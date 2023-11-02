#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

string substring(const string& str, int i, int j) {
    string sub = "";
    for (; i < j; i++) {
        sub += str[i];
    }
    return sub;
}

bool isDelimiter(char c) {
    if (c == ' ' || c == '\n' || c == '\t' || c == '\\')
        return true;
    return false;
}
vector<string> split(const string& str, bool (*predicate)()){
    vector<string> words;
    int i = 0, j = 0;
    while (i < str.size()) {
        while (isDelimiter(str[i]) && i < str.size()) {
            i++;
        }
        j = i;
        while (j < str.size() && !isDelimiter(str[j]))
            j++;
        if (i != str.size() && i - j != 0) {
            words.push_back(substring(str, i, j));
            i = j;
        }
    }
    return words;
}

string frame(const string& str, int width) {
    width += 2;
    string tops(width, '*');
    string msg = tops;
    vector<string> words = split(str, &isDelimiter);
    string current_line = "*";
    for (int i = 0; i < words.size(); i++) {
        int future_characters = current_line.size() + 1 + words[i].size();
        if (current_line.size() != 1)
            future_characters++;
        if (future_characters > width) {
            if (current_line.size() == 1)
                throw length_error("Width too small");
            if (width - current_line.size() - 1 > 0) {
                string extra_spacing(width - current_line.size() - 1, ' ');
                current_line += extra_spacing;
            }
            current_line += "*";
            msg += "\n" + current_line;
            current_line = "*";
            i--;
        }
        else {
            if (current_line.size() != 1)
                current_line += " ";
            current_line += words[i];
        }
    }
    if (width - current_line.size() - 1 > 0) {
        string extra_spacing(width - current_line.size() - 1, ' ');
        current_line += extra_spacing;
    }
    msg += "\n" + current_line + "*";
    msg += "\n" + tops;
    return msg;
}

vector<string> divide(const string& str, int width) {
    vector<string> lines;
    vector<string> words = split(str);
    string current_line = "";
    for (auto word = words.begin(); word != words.end(); word++) {
        //beginning of current_line
        if (current_line.size() == 0) {
            //width is too small
            if (word->size() > width) {
                throw length_error("The width is too small");
            }
            current_line += *word;
        }
        else {
            //reached line maximum capacity
            if (word->size() + current_line.size() + 1 > width) {
                //add needed spaces
                if (current_line.size() < width) {
                    int spaces = width - current_line.size();
                    current_line += string(spaces, ' ');
                }
                if (word == words.end() - 1) {
                        lines.push_back(current_line);
                        current_line = *word;
                        int spaces = width - current_line.size();
                        current_line += string(spaces, ' ');
                }
                lines.push_back(current_line);
                current_line = *word;

            }
            //add word to current_line
            else {
                if (word == words.end() - 1) {
                    if (current_line.size() < width) {
                        current_line += ' ' + *word;
                        int spaces = width - current_line.size();
                        current_line += string(spaces, ' ');
                        lines.push_back(current_line);
                    }
                }
                current_line += " " + *word;
            }
        }
    }
    return lines;
}
string frame_iter(const string& str, int width) {

    string msg(width + 4, '*');
    for (auto i: divide(str, width)) {
        msg += "\n* " + i + " *";
    }
    msg += "\n" + string(width + 4, '*');
    return msg;
}

void permuted_index(string str) {

}
int main() {
    vector<string> lines;
    string test = "the quick brown fox\njumped over the fence";
    cout << frame_iter(test, 11);
}