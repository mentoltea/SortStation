#include "station.h"

namespace MySortStation {

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