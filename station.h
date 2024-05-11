#pragma once

#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <vector>
#include <exception>
#include <cmath>

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



extern bool Initialized;
extern std::map<std::string, int> Priorities;

extern void initialize();

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

std::vector<Token> tokenize(std::string input);
std::queue< Token > sort( std::vector< Token > tks);
extern Token enumerate(std::queue< Token > tks);
bool read_float(float* ptr, Token& tk);

}
