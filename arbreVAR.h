#ifndef ARBRE_VH
#define ARBRE_VH

#include "noeudVAR.h"
#include <string>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <unordered_map>
#include <cmath>

class arbreVAR {
private:
    noeudVAR* racine;
    
    // Fonction récursive pour afficher l'expression infixée
    void afficherInfixe(noeudVAR* n) const;

    // Fonction récursive pour dériver un nœud
    noeudVAR* dériverNoeud(noeudVAR* n, const std::string& var);
    
    // Fonction récursive pour évaluer un nœud
    double évaluerNoeud(noeudVAR* n, const std::unordered_map<std::string, double>& variables) const;

public:
    // Constructeurs
    arbreVAR();
    arbreVAR(noeudVAR* racine);
    arbreVAR(const std::string& expression);

    // Destructeur
    ~arbreVAR();

    // Fonction pour afficher l'expression infixée
    void afficherInfixe() const;
    
    // Fonction d'évaluation de l'arbre
    double évaluation(const std::unordered_map<std::string, double>& variables) const;

    // Fonction pour dériver l'arbre
    arbreVAR dérivée(const std::string& var);
};

#endif

