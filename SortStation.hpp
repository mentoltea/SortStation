#pragma once

#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <vector>
#include <exception>
#include <cmath>

using namespace std;
namespace MySortStation {

typedef enum {
    UNKNOWN = -1,
    OPERAND,
    OPERATOR
} TokenType;

typedef enum {
    NOTFOUND = -1,
    UNCOUNTABLE = 0,
    COUNATBLE = 1
} CountType;

struct Token {
    std::string  data;
    TokenType type = UNKNOWN;
    CountType counttype = NOTFOUND;
    std::string uncountable_data;
    std::string operand;

    Token() = default;
    Token(std::string data, TokenType type): data(data), type(type) {}
    Token(std::string data, TokenType type, CountType counttype): data(data), type(type), counttype(counttype) {}
    Token(std::string data, TokenType type, CountType counttype, std::string uncountable_data, std::string operand): 
        data(data), type(type), counttype(counttype), uncountable_data(uncountable_data), operand(operand) {}
};



bool Initialized = false;
std::map<std::string, int> Priorities;

void initialize() {
    Priorities["+"] = 1; Priorities["-"] = 1; 
    Priorities["*"] = 2; Priorities["/"] = 2;
    //Priorities["^"] = 3;
    Priorities["("] = 5; Priorities[")"] = 5;

    Initialized = true;
}

bool only_digits(std::string s) {
    for (int i=0; i<s.size(); i++) {
        if (!(std::isdigit(s[i]) || s[i] == '.' || s[i]=='-')) return false;
    }
    return true;
}

bool read_float(float* ptr, Token& tk) {
    if (only_digits(tk.data)) {
        *ptr = std::stof(tk.data);
        tk.counttype = COUNATBLE;
        return true;
    }
    tk.counttype = UNCOUNTABLE;
    return false;
}


template<typename T>
std::queue<T> reverseQueue(std::queue<T> qin) {
    std::stack<T> st;
    std::queue<T> qout;
    while (!qin.empty()) {
        st.push(qin.front());
        qin.pop();
    }
    while (!st.empty()) {
        qout.push(st.top());
        st.pop();
    }
    return qout;   
}

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
queue< Token > sort( vector< Token > tks) {
    queue<Token> operandsQueue;
    stack<Token> opStack;

    Token tk, temp;
    int prior1, prior2;
    for (int i=0; i < tks.size(); i++) {
        tk = tks[i];

        if (tk.type == OPERAND) {
            operandsQueue.push(tk);
            continue;
        }

        if (tk.type == OPERATOR) {
            if (opStack.empty()) {
                opStack.push(tk);
                continue;
            }

            if (tk.data == "(") {
                opStack.push(tk);
                continue;
            }
            else if (tk.data == ")") {
                temp = opStack.top();
                while (temp.data != "(") {
                    operandsQueue.push(temp);
                    opStack.pop();
                    if (opStack.empty()) throw runtime_error("Bad input - no opening bracket");
                    temp = opStack.top();
                }
                opStack.pop();
                continue;
            }

            temp = opStack.top();

            if (temp.data == "(") {
                opStack.push(tk);
                continue;
            }

            prior1 = Priorities[tk.data];
            prior2 = Priorities[temp.data];
            
            while (prior2 > prior1) {
                opStack.pop();
                operandsQueue.push(temp);
                if (opStack.empty()) break;
                temp = opStack.top();
                prior2 = Priorities[temp.data];
            }
            
            if (opStack.empty()) {
                opStack.push(tk);
                continue;
            }

            if (prior1 == prior2) {
                opStack.pop();
                operandsQueue.push(temp);
                opStack.push(tk);
                continue;
            } else { // prior1 > prior2
                opStack.push(tk);
            }
        }
    }

    while (!opStack.empty()) {
        operandsQueue.push(opStack.top());
        opStack.pop();
    }
    
    return operandsQueue;
}
Token enumerate(std::queue< Token > tks) {
    std::stack<Token> st;
    std::cout << "in" << std::endl;
    Token tk, temp1, temp2, temp3;
    float a, b, c;
    std::string strtemp;
    for (; !tks.empty(); tks.pop()) {
        tk = tks.front();
        if (!st.empty()) std::cout << st.top().data + st.top().operand + st.top().uncountable_data << std::endl;
        if (tk.type == OPERAND) {
            st.push(tk);
            continue;
        }
        if (tk.type == OPERATOR) {
            switch (tk.data[0]) {
            case '+':
                temp2 = st.top(); st.pop();
                temp1 = st.top(); st.pop();

                c=0;
                strtemp = "";

                if (temp1.counttype == UNCOUNTABLE) {
                    if (temp1.operand == "+") {
                        read_float(&a, temp1);
                        c += a;
                    } else {
                        strtemp += temp1.data + temp1.operand;
                    }
                    strtemp += temp1.uncountable_data;
                }
                else if (read_float(&a, temp1)) {
                    c += a;
                } else {
                    strtemp += temp1.data;
                }

                if (temp2.counttype == UNCOUNTABLE) {
                    if (!strtemp.empty()) strtemp += "+";

                    if (temp2.operand == "+") {
                        read_float(&a, temp2);
                        c += a;
                    } else {
                        strtemp += temp2.data + temp2.operand;
                    }
                    strtemp += temp2.uncountable_data;
                }
                else if (read_float(&a, temp2)) {
                    c += a;
                } else {
                    if (!strtemp.empty()) strtemp += "+";
                    strtemp += temp2.data;
                }

                temp3 = Token(std::to_string(c), OPERAND, UNCOUNTABLE, strtemp, "+");
                if (strtemp.empty()) {
                    temp3.counttype = COUNATBLE;
                }
                
                st.push(temp3);
                break;

            case '-':
                temp2 = st.top(); st.pop();
                temp1 = st.top(); st.pop();

                c=0;
                strtemp = "";

                if (temp1.counttype == UNCOUNTABLE) {
                    if (temp1.operand == "+") {
                        read_float(&a, temp1);
                        c += a;
                    } else {
                        strtemp += temp1.data + temp1.operand;
                    }
                    strtemp += temp1.uncountable_data;
                }
                else if (read_float(&a, temp1)) {
                    c += a;
                } else {
                    strtemp += temp1.data;
                }

                if (temp2.counttype == UNCOUNTABLE) {
                    strtemp += "-";
                    if (temp2.operand == "+") {
                        read_float(&a, temp2);
                        c -= a;
                    } else {
                        strtemp += temp2.data + temp2.operand;
                    }
                    strtemp += temp2.uncountable_data;
                }
                else if (read_float(&a, temp2)) {
                    c -= a;
                } else {
                    strtemp += "-"+temp2.data;
                }

                temp3 = Token(std::to_string(c), OPERAND, UNCOUNTABLE, strtemp, "+");
                if (strtemp.empty()) {
                    temp3.counttype = COUNATBLE;
                }
                
                st.push(temp3);
                break;

             case '*':
                temp2 = st.top(); st.pop();
                temp1 = st.top(); st.pop();

                c=1;
                strtemp = "";

                if (temp1.counttype == UNCOUNTABLE) {
                    strtemp += "(";
                    if (temp1.operand == "*") {
                        read_float(&a, temp1);
                        c *= a;
                    } else {
                        strtemp += temp1.data + temp1.operand;
                    }
                    strtemp += temp1.uncountable_data + ")";
                }
                else if (read_float(&a, temp1)) {
                    c *= a;
                } else {
                    strtemp += temp1.data;
                }

                if (temp2.counttype == UNCOUNTABLE) {
                    if (!strtemp.empty()) strtemp += "*";
                    strtemp += "(";

                    if (temp2.operand == "*") {
                        read_float(&a, temp2);
                        c *= a;
                    } else {
                        strtemp += temp2.data + temp2.operand;
                    }
                    strtemp += temp2.uncountable_data + ")";
                }
                else if (read_float(&a, temp2)) {
                    c *= a;
                } else {
                    if (!strtemp.empty()) strtemp += "*";
                    strtemp += temp2.data;
                }

                temp3 = Token(std::to_string(c), OPERAND, UNCOUNTABLE, strtemp, "*");
                if (strtemp.empty()) {
                    temp3.counttype = COUNATBLE;
                }
                
                st.push(temp3);
                break;

            case '/':
                temp2 = st.top(); st.pop();
                temp1 = st.top(); st.pop();

                c=1;
                strtemp = "";

                if (temp1.counttype == UNCOUNTABLE) {
                    strtemp += "(";
                    if (temp1.operand == "*") {
                        read_float(&a, temp1);
                        c *= a;
                    } else {
                        strtemp += temp1.data + temp1.operand;
                    }
                    strtemp += temp1.uncountable_data + ")";
                }
                else if (read_float(&a, temp1)) {
                    c *= a;
                } else {
                    strtemp += temp1.data;
                }

                if (temp2.counttype == UNCOUNTABLE) {
                    if (!strtemp.empty()) strtemp += "/";
                    strtemp += "(";

                    if (temp2.operand == "*") {
                        read_float(&a, temp2);
                        c /= a;
                    } else {
                        strtemp += temp2.data + temp2.operand;
                    }
                    strtemp += temp2.uncountable_data + ")";
                }
                else if (read_float(&a, temp2)) {
                    c /= a;
                } else {
                    if (strtemp.empty()) strtemp += "1";
                    strtemp += "/";
                    strtemp += temp2.data;
                }

                temp3 = Token(std::to_string(c), OPERAND, UNCOUNTABLE, strtemp, "*");
                if (strtemp.empty()) {
                    temp3.counttype = COUNATBLE;
                }
                
                st.push(temp3);
                break;
            
            default:
                break;
            }
            continue;
        }
    }

    temp1 = st.top();
    if (temp1.counttype == UNCOUNTABLE) {
        temp1.data = temp1.data + temp1.operand + temp1.uncountable_data;
    }
    return temp1;
}
}
