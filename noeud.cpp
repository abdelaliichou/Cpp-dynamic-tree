#include "noeud.h"

// Constructeur pour un opérateur
noeud::noeud(char operateur) : type('o'), ope(operateur), val(0), fg(nullptr), fd(nullptr) {}

// Constructeur pour une valeur
noeud::noeud(double valeur) : type('f'), ope('\0'), val(valeur), fg(nullptr), fd(nullptr) {}

// Destructeur pour libérer la mémoire
noeud::~noeud() {
    delete fg;
    delete fd;
}

