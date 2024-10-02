#include "arbreVAR.h"

// Constructeurs
arbreVAR::arbreVAR() : racine(nullptr) {}
arbreVAR::arbreVAR(noeudVAR* racine) : racine(racine) {}
arbreVAR::arbreVAR(const std::string& expression) {
    // Initialiser l'arbre à partir de l'expression (implémentation non montrée ici)
}

// Destructeur
arbreVAR::~arbreVAR() {
    delete racine;
}


noeudVAR* arbreVAR::dériverNoeud(noeudVAR* n, const std::string& var) {
    if (!n) return nullptr;
    
    if (n->type == 'f') {
        return new noeudVAR(0.0);
    } else if (n->type == 'v') {
        return new noeudVAR(n->var == var ? 1.0 : 0.0);
    } else if (n->type == 'o') {
        noeudVAR* du = n->fg ? dériverNoeud(n->fg, var) : nullptr;
        noeudVAR* dv = n->fd ? dériverNoeud(n->fd, var) : nullptr;
        
        switch (n->ope) {
            case '+':
                return new noeudVAR('+', du, dv);
            case '-':
                if (!n->fg) {
                    // Unary minus case: -X -> -1 * X
                    return new noeudVAR('*', new noeudVAR(-1.0), dv);
                }
                return new noeudVAR('-', du, dv);
            case '*':
                return new noeudVAR('+', new noeudVAR('*', du, n->fd->copier()), new noeudVAR('*', n->fg->copier(), dv));
            case '/':
                return new noeudVAR('/', new noeudVAR('-', new noeudVAR('*', du, n->fd->copier()), new noeudVAR('*', n->fg->copier(), dv)), new noeudVAR('^', n->fd->copier(), new noeudVAR(2.0)));
            case '^':
                if (n->fd && n->fd->type == 'f' && n->fd->val >= 0) {
                    double exponent = n->fd->val;
                    return new noeudVAR('*', new noeudVAR(exponent), new noeudVAR('*', new noeudVAR('^', n->fg->copier(), new noeudVAR(exponent - 1)), du));
                } else {
                    throw std::runtime_error("Derivation of u^v is not supported for v non-constant or negative exponent");
                }
            default:
                throw std::runtime_error("Unknown operator for differentiation");
        }
    }
    return nullptr;
}



// Fonction pour évaluer un nœud
// Fonction pour évaluer un nœud
double arbreVAR::évaluerNoeud(noeudVAR* n, const std::unordered_map<std::string, double>& variables) const {
    if (!n) return 0.0;
    
    if (n->type == 'f') {
        return n->val;
    } else if (n->type == 'v') {
        if (variables.find(n->var) != variables.end()) {
            return variables.at(n->var);
        } else {
            throw std::runtime_error("Variable not found during evaluation: " + n->var);
        }
    } else if (n->type == 'o') {
        double left = n->fg ? évaluerNoeud(n->fg, variables) : 0.0;
        double right = n->fd ? évaluerNoeud(n->fd, variables) : 0.0;
        
        switch (n->ope) {
            case '+':
                return left + right;
            case '-':
                if ( !n->fg ) {
                    return -right;
                }
                return left - right;
            case '*':
                return left * right;
            case '/':
                if (right == 0.0) {
                    throw std::runtime_error("Division by zero");
                }
                return left / right;
            case '^':
                return std::pow(left, right);
            default:
                throw std::runtime_error("Unknown operator during evaluation");
        }
    }
    return 0.0;
}

// Fonction d'évaluation de l'arbre
double arbreVAR::évaluation(const std::unordered_map<std::string, double>& variables) const {
    return évaluerNoeud(racine, variables);
}

// Fonction pour dériver l'arbre
arbreVAR arbreVAR::dérivée(const std::string& var) {
    return arbreVAR(dériverNoeud(racine, var));
}


// Fonction pour afficher l'expression infixée
void arbreVAR::afficherInfixe() const {
    if (racine) {
        afficherInfixe(racine);     
    } else {
        throw std::runtime_error("Arbre vide");
    }
}

// Fonction récursive pour afficher l'expression infixée
void arbreVAR::afficherInfixe(noeudVAR* n) const {
    if (!n) {
        return;
    }

    if (n->type == 'f') {
        std::cout << n->val;
    } else if (n->type == 'v') {
        std::cout << n->var;
    } else {
        if (n->ope == '-' && !n->fg) {
            std::cout << "-";
            afficherInfixe(n->fd);
        } else {
            std::cout << "(";
            afficherInfixe(n->fg);
            std::cout << " " << n->ope << " ";
            afficherInfixe(n->fd);
            std::cout << ")";
        }
    }
}
