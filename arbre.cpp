#include "arbre.h"

// Fonction récursive pour évaluation
double arbre::evaluerNoeud(noeud* n) {
    if (!n) {
        throw std::runtime_error("Nœud invalide");
    }

    if (n->type == 'f') {
        return n->val;
    } else {
        double gauche = evaluerNoeud(n->fg);
        double droit = evaluerNoeud(n->fd);
        switch (n->ope) {
            case '+': return gauche + droit;
            case '-': return gauche - droit;
            case '*': return gauche * droit;
            case '/': 
                if (droit == 0) {
                    throw std::runtime_error("Division par zéro");
                }
                return gauche / droit;
            case '^': return std::pow(gauche, droit);
            default: throw std::runtime_error("Opérateur inconnu");
        }
    }
}

// Constructeur sans argument
arbre::arbre() : racine(nullptr) {}

// Constructeur avec expression arithmétique infixée
arbre::arbre(const std::string& expression) {
    std::string postfixExpression = infixToPostfix(expression);
    std::cout << "Expression suffixe pile: "<< postfixExpression  << std::endl;
    std::istringstream tokens(postfixExpression);
    Pile<noeud*> pile;
    std::string token;

    while (tokens >> token) {
        if (std::isdigit(token[0]) || (token[0] == '-' && token.size() > 1 && std::isdigit(token[1]))) {
            double value = std::stod(token);
            pile.empiler(new noeud(value));
        } else if (token.size() == 1 && std::string("+-*/^").find(token) != std::string::npos) {
            noeud* node = new noeud(token[0]);
            node->fd = pile.dépiler();
            node->fg = pile.dépiler();
            pile.empiler(node);
        } else {
            throw std::runtime_error("Token invalide dans l'expression postfixée");
        }
    }

    if (pile.vide()) {
        throw std::runtime_error("Expression invalide");
    }

    racine = pile.dépiler();

    if (!pile.vide()) {
        throw std::runtime_error("Expression invalide");
    }
}

// Destructeur pour libérer la mémoire
arbre::~arbre() {
    delete racine;
}

// Fonction d'évaluation de l'arbre
double arbre::evaluation() {
    if (racine) {
        return evaluerNoeud(racine);
    } else {
        throw std::runtime_error("Arbre vide");
    }
}

// Fonction pour afficher l'expression infixée
void arbre::afficherInfixe() {
    if (racine) {
        afficherInfixe(racine);
    } else {
        throw std::runtime_error("Arbre vide");
    }
}

// Fonction récursive pour afficher l'expression infixée
void arbre::afficherInfixe(noeud* n) {
    if (!n) {
        return;
    }

    if (n->type == 'f') {
        std::cout << n->val;
    } else {
        std::cout << "(";
        afficherInfixe(n->fg);
        std::cout << " " << n->ope << " ";
        afficherInfixe(n->fd);
        std::cout << ")";
    }
}

