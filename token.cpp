#include "station.h"

using namespace std;
namespace MySortStation {

vector<Token> tokenize(string input) {
    vector<Token> res;
    string temp = ""; string current;
    for (int i=0; i<input.size(); i++) {
        current = input[i];
        if (current[0] <= 32) {continue;}
        if (Priorities.count(current)) {
            if (!temp.empty()) res.push_back(Token(temp, OPERAND));
            res.push_back(Token(current, OPERATOR));
            temp = "";
        } else {
            temp += current;
        }
    }
    if (!temp.empty()) res.push_back(Token(temp, OPERAND));
    return res;
}

}
