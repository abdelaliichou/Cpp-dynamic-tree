#include "shunting_yard.h"

int getPrecedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}

bool isRightAssociative(char op) {
    return op == '^';
}

std::string infixToPostfix(const std::string& expression) {
    std::stack<char> operators;
    std::ostringstream output;
    std::istringstream tokens(expression);
    std::string token;

    while (tokens >> token) {
        if (std::isdigit(token[0]) || (token[0] == '-' && token.size() > 1 && std::isdigit(token[1]))) {
            output << token << ' ';
        } else if (token == "(") {
            operators.push('(');
        } else if (token == ")") {
            while (!operators.empty() && operators.top() != '(') {
                output << operators.top() << ' ';
                operators.pop();
            }
            if (operators.empty()) {
                throw std::runtime_error("Parenthèses mal équilibrées");
            }
            operators.pop();
        } else if (token.size() == 1 && std::string("+-*/^").find(token) != std::string::npos) {
            char op = token[0];
            while (!operators.empty() && operators.top() != '(' &&
                   ((isRightAssociative(op) && getPrecedence(op) < getPrecedence(operators.top())) ||
                    (!isRightAssociative(op) && getPrecedence(op) <= getPrecedence(operators.top())))) {
                output << operators.top() << ' ';
                operators.pop();
            }
            operators.push(op);
        } else {
            throw std::runtime_error("Token invalide");
        }
    }

    while (!operators.empty()) {
        if (operators.top() == '(') {
            throw std::runtime_error("Parenthèses mal équilibrées");
        }
        output << operators.top() << ' ';
        operators.pop();
    }

    return output.str();
}

