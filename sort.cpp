#include "station.h"

using namespace std;

namespace MySortStation {


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
}