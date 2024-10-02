#include "noeudVAR.h"

// Constructeurs
noeudVAR::noeudVAR(char operateur, noeudVAR* gauche, noeudVAR* droite)
    : type('o'), ope(operateur), val(0.0), var(""), fg(gauche), fd(droite) {}

noeudVAR::noeudVAR(char operateur, noeudVAR* unique)
    : type('o'), ope(operateur), val(0.0), var(""), fg(unique), fd(nullptr) {}

noeudVAR::noeudVAR(double valeur)
    : type('f'), ope('\0'), val(valeur), var(""), fg(nullptr), fd(nullptr) {}

noeudVAR::noeudVAR(const std::string& variable)
    : type('v'), ope('\0'), val(0.0), var(variable), fg(nullptr), fd(nullptr) {}

// Destructeur
noeudVAR::~noeudVAR() {
    delete fg;
    delete fd;
}

// Copier un nœud
noeudVAR* noeudVAR::copier() const {
    if (type == 'f') {
        return new noeudVAR(val);
    } else if (type == 'v') {
        return new noeudVAR(var);
    } else {
        return new noeudVAR(ope, fg ? fg->copier() : nullptr, fd ? fd->copier() : nullptr);
    }
}

