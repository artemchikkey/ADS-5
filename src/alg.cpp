// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int priority(char op) {
    if (op == '*' || op == '/') return 2;
    else if (op == '+' || op == '-') return 1;
    else return 0;
}
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}
std::string infx2pstfx(std::string inf) {
    TStack<char, 100> stack;
    std::string post;
    for (char& c : inf) {
        if (isdigit(c)) {
            post += c;
            post += ' ';
        } else if (c == '(') {
            stack.push(c);
        } else if (c == ')') {
            while (stack.get() != '(') {
                post += stack.get();
                post += ' ';
                stack.pop();
            }
            stack.pop();
        } else if (isOperator(c)) {
            while (!stack.isEmpty() && priority(stack.get()) >= priority(c)) {
                post += stack.get();
                post += ' ';
                stack.pop();
            }
            stack.push(c);
        }
    }
    while (!stack.isEmpty()) {
        post += stack.get();
        post += ' ';
        stack.pop();
    }
    return post;
}
int eval(std::string post) {
    TStack<int, 100> stack;
    for (char& c : post) {
        if (isdigit(c)) {
            stack.push(c - '0');
        } else if (isOperator(c)) {
            int operand2 = stack.get();
            stack.pop();
            int operand1 = stack.get();
            stack.pop();
            switch (c) {
                case '+':
                    stack.push(operand1 + operand2);
                    break;
                case '-':
                    stack.push(operand1 - operand2);
                    break;
                case '*':
                    stack.push(operand1 * operand2);
                    break;
                case '/':
                    stack.push(operand1 / operand2);
                    break;
            }
        }
    }
    return stack.get();
}
