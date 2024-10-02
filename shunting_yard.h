#ifndef SHUNTING_YARD_H
#define SHUNTING_YARD_H

#include <string>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <cctype>
#include <cmath>
#include <unordered_map>

// Fonction pour déterminer la priorité des opérateurs
int getPrecedence(char op);

// Fonction pour déterminer l'associativité des opérateurs
bool isRightAssociative(char op);

// Fonction pour convertir une expression infixée en notation suffixée
std::string infixToPostfix(const std::string& expression);

#endif

