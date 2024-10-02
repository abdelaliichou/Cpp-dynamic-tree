#ifndef ARBRE_H
#define ARBRE_H

#include "shunting_yard.h"
#include "pile.h"
#include <string>
#include <iostream>
#include <stdexcept>
#include <sstream>


class arbre {
private:
    noeud* racine;

    // Fonction récursive pour évaluation
    double evaluerNoeud(noeud* n);

    // Fonction récursive pour afficher l'expression infixée
    void afficherInfixe(noeud* n);

public:
    // Constructeur sans argument
    arbre();

    // Constructeur avec expression arithmétique infixée
    arbre(const std::string& expression);

    // Destructeur
    ~arbre();

    // Fonction d'évaluation de l'arbre
    double evaluation();

    // Fonction pour afficher l'expression infixée
    void afficherInfixe();
};

#endif

